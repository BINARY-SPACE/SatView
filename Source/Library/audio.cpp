// AUDIO.CPP : Audio Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the audio related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/07/24 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAudio

CAudio::CAudio() : CObject()
{
	CoInitialize((LPVOID)NULL);
}

CAudio::~CAudio()
{
	CoUninitialize();
}

INT CAudio::EnumInputDevices(CStringArray &szDevices, CDWordArray &dwFormats) CONST
{
	INT  nDevice;
	INT  nDevices;
	WAVEINCAPS  sInDeviceInfo;

	for (nDevice = 0, nDevices = waveInGetNumDevs(), szDevices.RemoveAll(), dwFormats.RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if (waveInGetDevCaps(nDevice, &sInDeviceInfo, sizeof(WAVEINCAPS)) == MMSYSERR_NOERROR)
		{
			dwFormats.Add(sInDeviceInfo.dwFormats);
			szDevices.Add(sInDeviceInfo.szPname);
		}
	}
	return((INT)szDevices.GetSize());
}

INT CAudio::EnumOutputDevices(CStringArray &szDevices, CDWordArray &dwFormats, CDWordArray &dwFeatures) CONST
{
	INT  nDevice;
	INT  nDevices;
	WAVEOUTCAPS  sOutDeviceInfo;

	for (nDevice = 0, nDevices = waveOutGetNumDevs(), szDevices.RemoveAll(), dwFormats.RemoveAll(), dwFeatures.RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if (waveOutGetDevCaps(nDevice, &sOutDeviceInfo, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR)
		{
			dwFeatures.Add(sOutDeviceInfo.dwSupport);
			dwFormats.Add(sOutDeviceInfo.dwFormats);
			szDevices.Add(sOutDeviceInfo.szPname);
		}
	}
	return((INT)szDevices.GetSize());
}

DWORD CAudio::EnumOutputDeviceFeatures(LPCTSTR pszDevice) CONST
{
	INT  nDevice;
	INT  nDevices;
	CDWordArray  dwFormats;
	CDWordArray  dwFeatures;
	CStringArray  szDevices;

	for (nDevice = 0, nDevices = EnumOutputDevices(szDevices, dwFormats, dwFeatures); nDevice < nDevices; nDevice++)
	{
		if (!szDevices.GetAt(nDevice).Compare(pszDevice)) break;
		continue;
	}
	return((nDevice < nDevices) ? dwFeatures.GetAt(nDevice) : 0);
}

INT CAudio::EnumVoices(CStringArray &szSpeakers, WORD wGender, WORD wAge) CONST
{
	ULONG  nVoice;
	ULONG  nVoices;
	LPTSTR  pszName;
	LPWSTR  pszVoice;
	LPWSTR  pszAttributes;
	CString  szAttributes[3];
	ISpObjectToken  *pIVoice;
	IEnumSpObjectTokens  *pIEnumVoices;

	szSpeakers.RemoveAll();
	szAttributes[0].Format(STRING(IDS_VOICEATTRIBUTES_LANGUAGEINFO), GetLanguageID());
	szAttributes[1].Format(STRING(IDS_VOICEATTRIBUTES_SPEAKERGENDERINFO), STRING(MINVOICEGENDER + wGender));
	szAttributes[2].Format(STRING(IDS_VOICEATTRIBUTES_SPEAKERAGEINFO), STRING(MINVOICEAGE + wAge));
	szAttributes[0] += (wGender >= AUDIO_VOICEGENDER_MALE  &&  wGender <= AUDIO_VOICEGENDER_NEUTRAL) ? (LPCTSTR)(STRING(IDS_VOICEATTRIBUTES_SEPARATOR) + szAttributes[1]) : EMPTYSTRING;
	szAttributes[0] += (wAge >= AUDIO_VOICEAGE_BABY  &&  wAge <= AUDIO_VOICEAGE_SENIOR) ? (LPCTSTR)(STRING(IDS_VOICEATTRIBUTES_SEPARATOR) + szAttributes[2]) : EMPTYSTRING;
	if ((pszAttributes = (LPWSTR)GlobalAlloc(GPTR, (szAttributes[0].GetLength() + 1)*sizeof(WCHAR))))
	{
#ifndef UNICODE
		MultiByteToWideChar(CP_ACP, 0, szAttributes[0], -1, pszAttributes, szAttributes[0].GetLength() + 1);
#else
		wcscpy_s(pszAttributes, szAttributes[0].GetLength() + 1, szAttributes[0]);
#endif
		if (SUCCEEDED(SpEnumTokens(SPCAT_VOICES, pszAttributes, (LPCWSTR)NULL, &pIEnumVoices)))
		{
			for (nVoice = 0, nVoices = (SUCCEEDED(pIEnumVoices->GetCount(&nVoices))) ? nVoices : 0; nVoice < nVoices; nVoice++)
			{
				if (SUCCEEDED(pIEnumVoices->Next(1, &pIVoice, (ULONG *)NULL)))
				{
					if (SUCCEEDED(pIVoice->GetStringValue((LPCWSTR)NULL, &pszVoice)))
					{
						if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (wcslen(pszVoice) + 1)*sizeof(TCHAR))))
						{
#ifndef UNICODE
							WideCharToMultiByte(CP_ACP, 0, pszVoice, -1, pszName, (INT)wcslen(pszVoice) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#else
							wcscpy_s(pszName, wcslen(pszVoice) + 1, pszVoice);
#endif
							szSpeakers.Add(pszName);
							pIVoice->Release();
							GlobalFree(pszName);
							continue;
						}
					}
					pIVoice->Release();
				}
			}
			pIEnumVoices->Release();
		}
		GlobalFree(pszAttributes);
	}
	return((INT)szSpeakers.GetSize());
}

INT CAudio::EnumVoiceGenders(CStringArray &szGenders) CONST
{
	szGenders.RemoveAll();
	szGenders.Add(STRING(IDS_VOICEGENDER_MALE));
	szGenders.Add(STRING(IDS_VOICEGENDER_FEMALE));
	szGenders.Add(STRING(IDS_VOICEGENDER_NEUTRAL));
	return((INT)szGenders.GetSize());
}

INT CAudio::EnumVoiceAges(CStringArray &szAges) CONST
{
	szAges.RemoveAll();
	szAges.Add(STRING(IDS_VOICEAGE_BABY));
	szAges.Add(STRING(IDS_VOICEAGE_TODDLER));
	szAges.Add(STRING(IDS_VOICEAGE_CHILD));
	szAges.Add(STRING(IDS_VOICEAGE_ADOLESCENT));
	szAges.Add(STRING(IDS_VOICEAGE_ADULT));
	szAges.Add(STRING(IDS_VOICEAGE_SENIOR));
	return((INT)szAges.GetSize());
}


/////////////////////////////////////////////////////////////////////////////
// CAudioThread

IMPLEMENT_DYNCREATE(CAudioThread, CThread)

CAudioThread::CAudioThread() : CThread()
{
	m_nDeviceID = -1;
	m_dwPlaybackRate = 0;
	m_dwVolume = 0;
	m_dwPitch = 0;
}

CAudioThread::~CAudioThread()
{
	Stop();
}

BOOL CAudioThread::Start(CAudioDevice *pAudioDevice)
{
	return CreateThread(pAudioDevice);
}

BOOL CAudioThread::Continue()
{
	return((IsThreadActive()) ? SetEvent(m_hObjects[1]) : FALSE);
}

BOOL CAudioThread::Pause()
{
	return((IsThreadActive()) ? ((SetEvent(m_hObject) && WaitForSingleObject(m_hObjects[2], INFINITE) == WAIT_OBJECT_0) ? TRUE : FALSE) : FALSE);
}

BOOL CAudioThread::Stop()
{
	SetEvent(m_hObjects[0]);
	SetEvent(m_hObjects[1]);
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CAudioThread::InitInstance()
{
	CoInitialize((LPVOID)NULL);
	return CThread::InitInstance();
}

int CAudioThread::ExitInstance()
{
	CoUninitialize();
	return CThread::ExitInstance();
}

int CAudioThread::Run()
{
	INT  nDevice;
	INT  nDevices;
	CAudio  cAudio;
	CDWordArray  dwFormats;
	CDWordArray  dwFeatures;
	CStringArray  szDevices;
	CAudioDevice  *pAudioDevice = (CAudioDevice *)GetThreadInfo();

	while (WaitForSingleObject(m_hObjects[0], 0) == WAIT_TIMEOUT)
	{
		for (nDevice = 0, nDevices = cAudio.EnumOutputDevices(szDevices, dwFormats, dwFeatures); nDevice < nDevices; nDevice++)
		{
			if (szDevices.GetAt(nDevice) == pAudioDevice->GetAdapter() || !pAudioDevice->GetAdapter().GetLength())
			{
				if (pAudioDevice->GetAudition() == AUDIO_BEEP_SOUND)
				{
					pAudioDevice->SetDeviceID(nDevice);
					if (PlayBeepSound(pAudioDevice)) break;
					continue;
				}
				if (pAudioDevice->GetAudition() == AUDIO_WAVE_SOUND)
				{
					pAudioDevice->SetDeviceID(nDevice);
					if (PlayWaveSound(pAudioDevice)) break;
					continue;
				}
				if (pAudioDevice->GetAudition() == AUDIO_VOICE_SOUND)
				{
					pAudioDevice->SetDeviceID(nDevice);
					if (PlayVoiceSound(pAudioDevice)) break;
					continue;
				}
			}
		}
		if (nDevice == nDevices)
		{
			if (pAudioDevice->GetAudition() == AUDIO_BEEP_SOUND)
			{
				for (pAudioDevice->SetDeviceID((nDevices <= 0) ? pAudioDevice->GetDeviceID() : 0); nDevices > 0; )
				{
					nDevices = (PlayBeepSound(pAudioDevice)) ? nDevices : 0;
					break;
				}
				if (!nDevices)
				{
					for (Beep(pAudioDevice->GetBeepFrequency(), AUDIO_BEEPDURATION); Wait(AUDIO_BEEPDURATION) == WAIT_TIMEOUT; )
					{
						Beep(pAudioDevice->GetBeepFrequency(), AUDIO_BEEPDURATION);
						continue;
					}
				}
			}
			if (pAudioDevice->GetAudition() == AUDIO_WAVE_SOUND)
			{
				for (pAudioDevice->SetDeviceID((nDevices <= 0) ? pAudioDevice->GetDeviceID() : 0); nDevices > 0; )
				{
					nDevices = (PlayWaveSound(pAudioDevice)) ? nDevices : 0;
					break;
				}
				if (!nDevices)
				{
					for (PlaySound(pAudioDevice->GetWaveSound(), (HMODULE)NULL, SND_FILENAME); Wait(pAudioDevice->GetPlaybackInterval()) == WAIT_TIMEOUT; )
					{
						PlaySound(pAudioDevice->GetWaveSound(), (HMODULE)NULL, SND_FILENAME);
						continue;
					}
				}
			}
			if (pAudioDevice->GetAudition() == AUDIO_VOICE_SOUND)
			{
				for (pAudioDevice->SetDeviceID((nDevices <= 0) ? pAudioDevice->GetDeviceID() : 0); nDevices > 0; )
				{
					nDevices = (PlayVoiceSound(pAudioDevice)) ? nDevices : 0;
					break;
				}
				if (!nDevices)
				{
					for (Beep(AUDIO_DEFAULTBEEPFREQUENCY, AUDIO_BEEPDURATION); Wait(AUDIO_BEEPDURATION) == WAIT_TIMEOUT; )
					{
						Beep(AUDIO_DEFAULTBEEPFREQUENCY, AUDIO_BEEPDURATION);
						continue;
					}
				}
			}
		}
		if (WaitForSingleObject(m_hObjects[0], 0) == WAIT_TIMEOUT)
		{
			if (ResetEvent(m_hObject) && SetEvent(m_hObjects[2]))
			{
				WaitForSingleObject(m_hObjects[1], INFINITE);
				continue;
			}
		}
		break;
	}
	ExitInstance();
	return(((pAudioDevice->GetAudition() == AUDIO_NO_SOUND || pAudioDevice->GetAudition() == AUDIO_STANDARD_SOUND || (pAudioDevice->GetAudition() == AUDIO_BEEP_SOUND  &&  !pAudioDevice->GetAdapter().GetLength())) || nDevice < nDevices) ? 0 : -1);
}

BOOL CAudioThread::PlayBeepSound(CAudioDevice *pAudioDevice)
{
	HWAVEOUT  hDevice;
	DWORD  dwWaitCode;
	DWORD  dwRepCount;
	WAVEHDR  sWaveHeader;
	WAVEFORMATEX  sWaveInfo;

	while (!(hDevice = PrepareDevice(pAudioDevice, &sWaveInfo)))
	{
		if ((dwWaitCode = Wait(0)) == WAIT_TIMEOUT) continue;
		break;
	}
	if (hDevice != (HWAVEOUT)NULL  &&  hDevice != (HWAVEOUT)-1)
	{
		if (PrepareWaveData(&sWaveInfo, pAudioDevice->GetBeepFrequency(), &sWaveHeader))
		{
			if (waveOutPrepareHeader(hDevice, &sWaveHeader, sizeof(WAVEHDR)) == MMSYSERR_NOERROR)
			{
				for (sWaveHeader.dwFlags |= WHDR_BEGINLOOP | WHDR_ENDLOOP, dwRepCount = pAudioDevice->GetPlaybackCount(), dwWaitCode = (DWORD)-1; dwRepCount > 0; dwRepCount = (dwRepCount != (DWORD)-1) ? (dwRepCount - 1) : dwRepCount)
				{
					if (waveOutWrite(hDevice, &sWaveHeader, sizeof(WAVEHDR)) == MMSYSERR_NOERROR)
					{
						if ((dwWaitCode = Wait(2 * AUDIO_BEEPDURATION)) == WAIT_TIMEOUT)
						{
							sWaveHeader.dwLoops = (AUDIO_BEEPDURATION*pAudioDevice->GetBeepFrequency()) / 1000;
							sWaveHeader.dwFlags ^= WHDR_DONE;
							continue;
						}
					}
					break;
				}
				waveOutReset(hDevice);
				if (dwWaitCode != WAIT_TIMEOUT || !dwRepCount)
				{
					waveOutUnprepareHeader(hDevice, &sWaveHeader, sizeof(WAVEHDR));
					ReleaseWaveData(&sWaveHeader);
					ReleaseDevice(hDevice);
					return TRUE;
				}
				waveOutUnprepareHeader(hDevice, &sWaveHeader, sizeof(WAVEHDR));
			}
			ReleaseWaveData(&sWaveHeader);
		}
		ReleaseDevice(hDevice);
		return FALSE;
	}
	return((!hDevice) ? TRUE : FALSE);
}

BOOL CAudioThread::PlayWaveSound(CAudioDevice *pAudioDevice)
{
	HWAVEOUT  hDevice;
	DWORD  dwPlayTime;
	DWORD  dwWaitCode;
	DWORD  dwWaitTime;
	DWORD  dwRepCount;
	WAVEHDR  sWaveHeader;
	WAVEFORMATEX  sWaveInfo;

	while (!(hDevice = PrepareDevice(pAudioDevice, &sWaveInfo)))
	{
		if ((dwWaitCode = Wait(0)) == WAIT_TIMEOUT) continue;
		break;
	}
	if (hDevice != (HWAVEOUT)NULL  &&  hDevice != (HWAVEOUT)-1)
	{
		if (PrepareWaveData(pAudioDevice->GetWaveSound(), &sWaveHeader))
		{
			if (waveOutPrepareHeader(hDevice, &sWaveHeader, sizeof(WAVEHDR)) == MMSYSERR_NOERROR)
			{
				for (sWaveHeader.dwFlags |= WHDR_BEGINLOOP | WHDR_ENDLOOP, dwPlayTime = (DWORD)((1000.0*(double)sWaveHeader.dwBufferLength) / (double)sWaveInfo.nAvgBytesPerSec), dwRepCount = pAudioDevice->GetPlaybackCount(), dwWaitCode = (DWORD)-1; dwRepCount > 0; dwRepCount = (dwRepCount != (DWORD)-1) ? (dwRepCount - 1) : dwRepCount)
				{
					if (waveOutWrite(hDevice, &sWaveHeader, sizeof(WAVEHDR)) == MMSYSERR_NOERROR)
					{
						for (dwWaitTime = 0; TRUE; dwWaitTime += pAudioDevice->GetPlaybackInterval())
						{
							if ((dwWaitCode = Wait(pAudioDevice->GetPlaybackInterval())) == WAIT_TIMEOUT)
							{
								if (dwWaitTime + pAudioDevice->GetPlaybackInterval() > dwPlayTime)
								{
									Sleep(dwPlayTime%pAudioDevice->GetPlaybackInterval());
									sWaveHeader.dwFlags ^= WHDR_DONE;
									sWaveHeader.dwLoops = 1;
									break;
								}
								continue;
							}
							break;
						}
						if (dwWaitCode == WAIT_TIMEOUT) continue;
					}
					break;
				}
				waveOutReset(hDevice);
				if (dwWaitCode != WAIT_TIMEOUT || !dwRepCount)
				{
					waveOutUnprepareHeader(hDevice, &sWaveHeader, sizeof(WAVEHDR));
					ReleaseWaveData(&sWaveHeader);
					ReleaseDevice(hDevice);
					return TRUE;
				}
				waveOutUnprepareHeader(hDevice, &sWaveHeader, sizeof(WAVEHDR));
			}
			ReleaseWaveData(&sWaveHeader);
		}
		ReleaseDevice(hDevice);
		return FALSE;
	}
	return((!hDevice) ? TRUE : FALSE);
}

BOOL CAudioThread::PlayVoiceSound(CAudioDevice *pAudioDevice)
{
	DWORD  dwCount;
	DWORD  dwWaitCode;
	LPWSTR  pszLanguageID;
	LPWSTR  pszAttributes;
	LPWSTR  pszSpokenText;
	CString  szLanguageID;
	CString  szAttributes;
	CString  szSpokenText;
	ISpObjectToken  *pIVoice;
	CComPtr<ISpVoice>  cIVoice;
	CComPtr<ISpMMSysAudio>  cIAudioOut;

	if (SUCCEEDED(cIVoice.CoCreateInstance(CLSID_SpVoice)))
	{
		if (SUCCEEDED(cIAudioOut.CoCreateInstance(CLSID_SpMMAudioOut)))
		{
			if (SUCCEEDED(cIAudioOut->SetDeviceId(pAudioDevice->GetDeviceID())))
			{
				if (SUCCEEDED(cIVoice->SetOutput(cIAudioOut, FALSE)))
				{
					szLanguageID.Format(STRING(IDS_VOICEATTRIBUTES_LANGUAGEINFO), GetLanguageID());
					szAttributes.Format(STRING(IDS_VOICEATTRIBUTES_SPEAKERINFO), (LPCTSTR)pAudioDevice->GetVoiceSpeaker(), STRING(MINVOICEGENDER + pAudioDevice->GetVoiceGender()), STRING(MINVOICEAGE + pAudioDevice->GetVoiceAge()));
					szSpokenText.Format(STRING(IDS_VOICETEXT_FORMAT), (INT)((50 * (LOWORD(pAudioDevice->GetVolume()) + HIWORD(pAudioDevice->GetVolume()))) / 0xFFFF), (pAudioDevice->GetPitch() <= AUDIO_DEFAULTPITCH) ? (INT)(10.0*(((double)pAudioDevice->GetPitch() / (double)AUDIO_DEFAULTPITCH - (double)AUDIO_MINPITCH / (double)AUDIO_DEFAULTPITCH) / (1.0 - (double)AUDIO_MINPITCH / (double)AUDIO_DEFAULTPITCH)) - 10.0) : (INT)(10.0*(1.0 + ((double)pAudioDevice->GetPitch() / (double)AUDIO_DEFAULTPITCH - 1.0) / ((double)AUDIO_DEFAULTPITCH / (double)AUDIO_MINPITCH - 1.0)) - 10.0), (INT)(pAudioDevice->GetPlaybackRate() <= AUDIO_DEFAULTPLAYBACKRATE) ? (INT)(10.0*(((double)pAudioDevice->GetPlaybackRate() / (double)AUDIO_DEFAULTPLAYBACKRATE - (double)AUDIO_MINPLAYBACKRATE / (double)AUDIO_DEFAULTPLAYBACKRATE) / (1.0 - (double)AUDIO_MINPLAYBACKRATE / (double)AUDIO_DEFAULTPLAYBACKRATE)) - 10.0) : (INT)(10.0*(1.0 + ((double)pAudioDevice->GetPlaybackRate() / (double)AUDIO_DEFAULTPLAYBACKRATE - 1.0) / ((double)AUDIO_DEFAULTPLAYBACKRATE / (double)AUDIO_MINPLAYBACKRATE - 1.0)) - 10.0), (LPCTSTR)pAudioDevice->GetVoiceMessage());
					if ((pszLanguageID = (LPWSTR)GlobalAlloc(GPTR, (szLanguageID.GetLength() + 1)*sizeof(WCHAR))))
					{
						if ((pszAttributes = (LPWSTR)GlobalAlloc(GPTR, (szAttributes.GetLength() + 1)*sizeof(WCHAR))))
						{
							if ((pszSpokenText = (LPWSTR)GlobalAlloc(GPTR, (szSpokenText.GetLength() + 1)*sizeof(WCHAR))))
							{
#ifndef UNICODE
								MultiByteToWideChar(CP_ACP, 0, szLanguageID, -1, pszLanguageID, szLanguageID.GetLength() + 1);
								MultiByteToWideChar(CP_ACP, 0, szAttributes, -1, pszAttributes, szAttributes.GetLength() + 1);
								MultiByteToWideChar(CP_ACP, 0, szSpokenText, -1, pszSpokenText, szSpokenText.GetLength() + 1);
#else
								wcscpy_s(pszLanguageID, szLanguageID.GetLength() + 1, szLanguageID);
								wcscpy_s(pszAttributes, szAttributes.GetLength() + 1, szAttributes);
								wcscpy_s(pszSpokenText, szSpokenText.GetLength() + 1, szSpokenText);
#endif
								if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, pszLanguageID, pszAttributes, &pIVoice)))
								{
									if (SUCCEEDED(cIVoice->SetVoice(pIVoice)))
									{
										for (dwCount = pAudioDevice->GetPlaybackCount(); dwCount > 0; dwCount = (dwCount != (DWORD)-1) ? (dwCount - 1) : dwCount)
										{
											if (SUCCEEDED(cIVoice->Speak(pszSpokenText, SPF_ASYNC | SPF_IS_XML, (ULONG *)NULL)))
											{
												if ((dwWaitCode = Wait(cIVoice->SpeakCompleteEvent(), FALSE, INFINITE)) != WAIT_OBJECT_0 + 1) break;
												if ((dwWaitCode = Wait(pAudioDevice->GetPlaybackInterval())) != WAIT_TIMEOUT) break;
												continue;
											}
											if ((dwWaitCode = Wait(pAudioDevice->GetPlaybackInterval())) != WAIT_TIMEOUT) break;
										}
										cIVoice.Release();
										cIAudioOut.Release();
										GlobalFree(pszSpokenText);
										GlobalFree(pszAttributes);
										GlobalFree(pszLanguageID);
										return((dwWaitCode != WAIT_TIMEOUT || !dwCount) ? TRUE : FALSE);
									}
									pIVoice->Release();
								}
								GlobalFree(pszSpokenText);
							}
							GlobalFree(pszAttributes);
						}
						GlobalFree(pszLanguageID);
					}
				}
			}
			cIAudioOut.Release();
		}
		cIVoice.Release();
	}
	return FALSE;
}

HWAVEOUT CAudioThread::PrepareDevice(CAudioDevice *pAudioDevice, WAVEFORMATEX *pWaveInfo)
{
	HWAVEOUT  hDevice;
	MMRESULT  nDeviceResult;
	WAVEFORMATEX  sWaveInfo;
	WAVEOUTCAPS  sWaveCaps;

	switch (pAudioDevice->GetAudition())
	{
	case AUDIO_BEEP_SOUND:
	{ if (!PrepareWaveInfo(pAudioDevice->GetDeviceID(), &sWaveInfo)) return((HWAVEOUT)-1);
	break;
	}
	case AUDIO_WAVE_SOUND:
	{ if (!PrepareWaveInfo(pAudioDevice->GetWaveSound(), &sWaveInfo)) return((HWAVEOUT)-1);
	break;
	}
	default:
	{ return FALSE;
	break;
	}
	}
	if ((nDeviceResult = waveOutOpen(&hDevice, pAudioDevice->GetDeviceID(), &sWaveInfo, 0, 0, CALLBACK_NULL)) == MMSYSERR_NOERROR)
	{
		if (waveOutGetDevCaps(pAudioDevice->GetDeviceID(), &sWaveCaps, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR)
		{
			if ((sWaveCaps.dwSupport & WAVECAPS_VOLUME) || (sWaveCaps.dwSupport & WAVECAPS_LRVOLUME))
			{
				waveOutGetVolume(hDevice, &m_dwVolume);
				waveOutSetVolume(hDevice, pAudioDevice->GetVolume());
			}
			if (sWaveCaps.dwSupport & WAVECAPS_PITCH)
			{
				waveOutGetPitch(hDevice, &m_dwPitch);
				waveOutSetPitch(hDevice, pAudioDevice->GetPitch());
			}
			if (sWaveCaps.dwSupport & WAVECAPS_PLAYBACKRATE)
			{
				waveOutGetPlaybackRate(hDevice, &m_dwPlaybackRate);
				waveOutSetPlaybackRate(hDevice, pAudioDevice->GetPlaybackRate());
			}
			CopyMemory(pWaveInfo, &sWaveInfo, sizeof(WAVEFORMATEX));
			m_nDeviceID = pAudioDevice->GetDeviceID();
			return hDevice;
		}
		waveOutClose(hDevice);
	}
	return((HWAVEOUT)NULL);
}

BOOL CAudioThread::ReleaseDevice(HWAVEOUT hDevice)
{
	WAVEOUTCAPS  sWaveCaps;

	if (waveOutGetDevCaps(m_nDeviceID, &sWaveCaps, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR)
	{
		if ((sWaveCaps.dwSupport & WAVECAPS_VOLUME) || (sWaveCaps.dwSupport & WAVECAPS_LRVOLUME)) waveOutSetVolume(hDevice, m_dwVolume);
		if (sWaveCaps.dwSupport & WAVECAPS_PLAYBACKRATE) waveOutSetPlaybackRate(hDevice, m_dwPlaybackRate);
		if (sWaveCaps.dwSupport & WAVECAPS_PITCH) waveOutSetPitch(hDevice, m_dwPitch);
	}
	return((waveOutClose(hDevice) == MMSYSERR_NOERROR) ? TRUE : FALSE);
}

BOOL CAudioThread::PrepareWaveInfo(UINT nDeviceID, WAVEFORMATEX *pWaveInfo) CONST
{
	WAVEOUTCAPS  sDeviceInfo;

	if (waveOutGetDevCaps(nDeviceID, &sDeviceInfo, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR)
	{
		pWaveInfo->nSamplesPerSec = ((sDeviceInfo.dwFormats & WAVE_FORMAT_4S16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_4S08) || (sDeviceInfo.dwFormats & WAVE_FORMAT_4M16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_4M08)) ? 44100 : (((sDeviceInfo.dwFormats & WAVE_FORMAT_2S16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_2S08) || (sDeviceInfo.dwFormats & WAVE_FORMAT_2M16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_2M08)) ? 22050 : 11025);
		pWaveInfo->wBitsPerSample = ((sDeviceInfo.dwFormats & WAVE_FORMAT_4S16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_4M16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_2S16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_2M16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_1S16) || (sDeviceInfo.dwFormats & WAVE_FORMAT_1M16)) ? 16 : 8;
		pWaveInfo->nBlockAlign = (WORD)((pWaveInfo->wBitsPerSample*(pWaveInfo->nChannels = (sDeviceInfo.dwSupport & WAVECAPS_LRVOLUME) ? 2 : 1)) / 8);
		pWaveInfo->nAvgBytesPerSec = pWaveInfo->nSamplesPerSec*pWaveInfo->nBlockAlign;
		pWaveInfo->wFormatTag = WAVE_FORMAT_PCM;
		pWaveInfo->cbSize = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL CAudioThread::PrepareWaveInfo(LPCTSTR pszSound, WAVEFORMATEX *pWaveInfo) CONST
{
	HMMIO  hmmFile;
	MMCKINFO  mmChunk;
	MMCKINFO  mmSubchunk;
	CFileFindEx  cFileFind;
	WAVEFORMATEX  *pmmFormat;

	for (mmChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E'), mmSubchunk.ckid = mmioFOURCC('f', 'm', 't', ' '); cFileFind.FindFile(pszSound); )
	{
		if ((hmmFile = mmioOpen((LPTSTR)pszSound, (LPMMIOINFO)NULL, MMIO_READ | MMIO_ALLOCBUF)))
		{
			if (mmioDescend(hmmFile, &mmChunk, (LPMMCKINFO)NULL, MMIO_FINDRIFF) == MMSYSERR_NOERROR)
			{
				if (mmioDescend(hmmFile, &mmSubchunk, &mmChunk, MMIO_FINDCHUNK) == MMSYSERR_NOERROR)
				{
					if ((pmmFormat = (WAVEFORMATEX *)GlobalAlloc(GPTR, (SIZE_T)mmSubchunk.cksize)))
					{
						if (mmioRead(hmmFile, (HPSTR)pmmFormat, mmSubchunk.cksize) == (LONG)mmSubchunk.cksize)
						{
							for (ZeroMemory(pWaveInfo, sizeof(WAVEFORMATEX)); pmmFormat->wFormatTag == WAVE_FORMAT_PCM; )
							{
								CopyMemory(pWaveInfo, pmmFormat, mmSubchunk.cksize);
								GlobalFree(pmmFormat);
								mmioClose(hmmFile, 0);
								cFileFind.Close();
								return TRUE;
							}
						}
						GlobalFree(pmmFormat);
					}
				}
			}
			mmioClose(hmmFile, 0);
		}
		cFileFind.Close();
		break;
	}
	return FALSE;
}

BOOL CAudioThread::PrepareWaveData(CONST WAVEFORMATEX *pWaveInfo, DWORD dwFrequency, WAVEHDR *pWaveHeader) CONST
{
	INT  nSample;
	INT  nSamples;
	USHORT  mmSample;
	WAVEHDR  sWaveHeader;

	if ((sWaveHeader.lpData = (LPSTR)GlobalAlloc(GPTR, (sWaveHeader.dwBufferLength = pWaveInfo->nAvgBytesPerSec / dwFrequency))))
	{
		for (nSample = 0, nSamples = pWaveInfo->nSamplesPerSec / dwFrequency, sWaveHeader.dwFlags = 0, sWaveHeader.dwUser = 0, sWaveHeader.dwBytesRecorded = 0, sWaveHeader.dwLoops = (AUDIO_BEEPDURATION*dwFrequency) / 1000; nSample < nSamples; nSample++)
		{
			if (pWaveInfo->wBitsPerSample == 8 && pWaveInfo->nChannels == 1)
			{
				sWaveHeader.lpData[nSample] = (UCHAR)(sin(((double)nSample*2.0*M_PI) / (double)nSamples)*(((double)(1 << pWaveInfo->wBitsPerSample)) / 2.0));
				continue;
			}
			if (pWaveInfo->wBitsPerSample == 8 && pWaveInfo->nChannels == 2)
			{
				sWaveHeader.lpData[((pWaveInfo->wBitsPerSample*pWaveInfo->nChannels) / 8)*nSample] = (UCHAR)(sin(((double)nSample*2.0*M_PI) / (double)nSamples)*(((double)(1 << pWaveInfo->wBitsPerSample)) / 2.0));
				sWaveHeader.lpData[((pWaveInfo->wBitsPerSample*pWaveInfo->nChannels) / 8)*nSample + sizeof(UCHAR)] = sWaveHeader.lpData[nSample];
				continue;
			}
			if (pWaveInfo->wBitsPerSample == 16 && pWaveInfo->nChannels == 1)
			{
				mmSample = (USHORT)(sin(((double)nSample*2.0*M_PI) / (double)nSamples)*(((double)(1 << pWaveInfo->wBitsPerSample)) / 2.0));
				CopyMemory(&sWaveHeader.lpData[((pWaveInfo->wBitsPerSample*pWaveInfo->nChannels) / 8)*nSample], &mmSample, sizeof(USHORT));
				continue;
			}
			if (pWaveInfo->wBitsPerSample == 16 && pWaveInfo->nChannels == 2)
			{
				mmSample = (USHORT)(sin(((double)nSample*2.0*M_PI) / (double)nSamples)*(((double)(1 << pWaveInfo->wBitsPerSample)) / 2.0));
				CopyMemory(&sWaveHeader.lpData[((pWaveInfo->wBitsPerSample*pWaveInfo->nChannels) / 8)*nSample], &mmSample, sizeof(USHORT));
				CopyMemory(&sWaveHeader.lpData[((pWaveInfo->wBitsPerSample*pWaveInfo->nChannels) / 8)*nSample + sizeof(USHORT)], &mmSample, sizeof(USHORT));
				continue;
			}
		}
		CopyMemory(pWaveHeader, &sWaveHeader, sizeof(WAVEHDR));
		return TRUE;
	}
	return FALSE;
}
BOOL CAudioThread::PrepareWaveData(LPCTSTR pszSound, WAVEHDR *pWaveHeader) CONST
{
	HMMIO  hmmFile;
	LPBYTE  pmmData;
	MMCKINFO  mmChunk;
	MMCKINFO  mmSubchunk;
	CFileFindEx  cFileFind;

	for (mmChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E'), mmSubchunk.ckid = mmioFOURCC('d', 'a', 't', 'a'); cFileFind.FindFile(pszSound); )
	{
		if ((hmmFile = mmioOpen((LPTSTR)pszSound, (LPMMIOINFO)NULL, MMIO_READ | MMIO_ALLOCBUF)))
		{
			if (mmioDescend(hmmFile, &mmChunk, (LPMMCKINFO)NULL, MMIO_FINDRIFF) == MMSYSERR_NOERROR)
			{
				if (mmioDescend(hmmFile, &mmSubchunk, &mmChunk, MMIO_FINDCHUNK) == MMSYSERR_NOERROR)
				{
					if ((pmmData = (LPBYTE)GlobalAlloc(GPTR, mmSubchunk.cksize)) != (LPBYTE)NULL)
					{
						if (mmioRead(hmmFile, (HPSTR)pmmData, mmSubchunk.cksize) == (LONG)mmSubchunk.cksize)
						{
							pWaveHeader->dwBufferLength = mmSubchunk.cksize;
							pWaveHeader->lpData = (LPSTR)pmmData;
							pWaveHeader->dwBytesRecorded = 0;
							pWaveHeader->dwFlags = 0;
							pWaveHeader->dwLoops = 1;
							pWaveHeader->dwUser = 0;
							mmioClose(hmmFile, 0);
							cFileFind.Close();
							return TRUE;
						}
						GlobalFree(pmmData);
					}
				}
			}
			mmioClose(hmmFile, 0);
		}
		cFileFind.Close();
		break;
	}
	return FALSE;
}

BOOL CAudioThread::ReleaseWaveData(WAVEHDR *pWaveHeader) CONST
{
	return((!GlobalFree(pWaveHeader->lpData)) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CAudioThread, CThread)
	//{{AFX_MSG_MAP(CAudioThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CAudioDevice

CAudioDevice::CAudioDevice() : CObject()
{
	SetAudition(AUDIO_NO_SOUND);
}

VOID CAudioDevice::SetAdapter(LPCTSTR pszAdapter)
{
	m_szAdapter = pszAdapter;
}

CString CAudioDevice::GetAdapter() CONST
{
	return m_szAdapter;
}

VOID CAudioDevice::SetDeviceID(UINT nDeviceID)
{
	m_nDeviceID = nDeviceID;
}

UINT CAudioDevice::GetDeviceID() CONST
{
	return m_nDeviceID;
}

VOID CAudioDevice::SetAudition(INT nAudition)
{
	m_nAudition = nAudition;
}

INT CAudioDevice::GetAudition() CONST
{
	return m_nAudition;
}

VOID CAudioDevice::SetVolume(DWORD dwVolume)
{
	m_dwVolume = dwVolume;
}

DWORD CAudioDevice::GetVolume() CONST
{
	return m_dwVolume;
}

VOID CAudioDevice::SetPitch(DWORD dwPitch)
{
	m_dwPitch = dwPitch;
}

DWORD CAudioDevice::GetPitch() CONST
{
	return m_dwPitch;
}

VOID CAudioDevice::SetPlaybackRate(DWORD dwPlaybackRate)
{
	m_dwPlaybackRate = dwPlaybackRate;
}

DWORD CAudioDevice::GetPlaybackRate() CONST
{
	return m_dwPlaybackRate;
}

VOID CAudioDevice::SetPlaybackCount(DWORD dwPlaybackCount)
{
	m_dwPlaybackCount = dwPlaybackCount;
}

DWORD CAudioDevice::GetPlaybackCount() CONST
{
	return m_dwPlaybackCount;
}

VOID CAudioDevice::SetPlaybackInterval(DWORD dwPlaybackInterval)
{
	m_dwPlaybackInterval = dwPlaybackInterval;
}

DWORD CAudioDevice::GetPlaybackInterval() CONST
{
	return m_dwPlaybackInterval;
}

VOID CAudioDevice::SetBeepFrequency(DWORD dwFrequency)
{
	m_dwFrequency = dwFrequency;
}

DWORD CAudioDevice::GetBeepFrequency() CONST
{
	return m_dwFrequency;
}

VOID CAudioDevice::SetWaveSound(LPCTSTR pszSound)
{
	m_szSound = pszSound;
}

CString CAudioDevice::GetWaveSound() CONST
{
	return m_szSound;
}

VOID CAudioDevice::SetVoiceSpeaker(LPCTSTR pszSpeaker)
{
	m_szSpeaker = pszSpeaker;
}

CString CAudioDevice::GetVoiceSpeaker() CONST
{
	return m_szSpeaker;
}

VOID CAudioDevice::SetVoiceGender(WORD wGender)
{
	m_dwVoice = MAKELONG(wGender, HIWORD(m_dwVoice));
}

WORD CAudioDevice::GetVoiceGender() CONST
{
	return LOWORD(m_dwVoice);
}

VOID CAudioDevice::SetVoiceAge(WORD wAge)
{
	m_dwVoice = MAKELONG(LOWORD(m_dwVoice), wAge);
}

WORD CAudioDevice::GetVoiceAge() CONST
{
	return HIWORD(m_dwVoice);
}

VOID CAudioDevice::SetVoiceMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CAudioDevice::GetVoiceMessage() CONST
{
	return m_szMessage;
}

BOOL CAudioDevice::StartSound(INT nAudition)
{
	return((nAudition == AUDIO_STANDARD_SOUND) ? PlaySound((LPCTSTR)SND_ALIAS_SYSTEMDEFAULT, (HMODULE)NULL, SND_ALIAS_ID) : FALSE);
}
BOOL CAudioDevice::StartSound(LPCTSTR pszAdapter, INT nAudition, DWORD dwVolume, DWORD dwPitch, DWORD dwFrequency, DWORD dwPlaybackCount, DWORD dwPlaybackInterval)
{
	for (StopSound(); nAudition == AUDIO_BEEP_SOUND;)
	{
		SetAdapter(pszAdapter);
		SetAudition(nAudition);
		SetVolume(dwVolume);
		SetPitch(dwPitch);
		SetBeepFrequency(dwFrequency);
		SetPlaybackCount(dwPlaybackCount);
		SetPlaybackInterval(dwPlaybackInterval);
		return((!m_thrdSound[1].IsThreadActive()) ? m_thrdSound[1].Start(this) : m_thrdSound[1].Continue());
	}
	return FALSE;
}
BOOL CAudioDevice::StartSound(LPCTSTR pszAdapter, INT nAudition, DWORD dwVolume, DWORD dwPitch, DWORD dwPlaybackRate, LPCTSTR pszSound, DWORD dwPlaybackCount, DWORD dwPlaybackInterval)
{
	for (StopSound(); nAudition == AUDIO_WAVE_SOUND;)
	{
		SetAdapter(pszAdapter);
		SetAudition(nAudition);
		SetVolume(dwVolume);
		SetPitch(dwPitch);
		SetWaveSound(pszSound);
		SetPlaybackRate(dwPlaybackRate);
		SetPlaybackCount(dwPlaybackCount);
		SetPlaybackInterval(dwPlaybackInterval);
		return((!m_thrdSound[1].IsThreadActive()) ? m_thrdSound[1].Start(this) : m_thrdSound[1].Continue());
	}
	return FALSE;
}
BOOL CAudioDevice::StartSound(LPCTSTR pszAdapter, INT nAudition, DWORD dwVolume, DWORD dwPitch, DWORD dwPlaybackRate, LPCTSTR pszSpeaker, WORD wGender, WORD wAge, LPCTSTR pszMessage, DWORD dwPlaybackCount, DWORD dwPlaybackInterval)
{
	for (StopSound(); nAudition == AUDIO_VOICE_SOUND;)
	{
		SetAdapter(pszAdapter);
		SetAudition(nAudition);
		SetVolume(dwVolume);
		SetPitch(dwPitch);
		SetVoiceAge(wAge);
		SetVoiceGender(wGender);
		SetVoiceSpeaker(pszSpeaker);
		SetVoiceMessage(pszMessage);
		SetPlaybackRate(dwPlaybackRate);
		SetPlaybackCount(dwPlaybackCount);
		SetPlaybackInterval(dwPlaybackInterval);
		return((!m_thrdSound[1].IsThreadActive()) ? m_thrdSound[1].Start(this) : m_thrdSound[1].Continue());
	}
	return FALSE;
}

BOOL CAudioDevice::StopSound(INT nAudition)
{
	if ((nAudition == AUDIO_NO_SOUND && (GetAudition() == AUDIO_STANDARD_SOUND || GetAudition() == AUDIO_BEEP_SOUND || GetAudition() == AUDIO_WAVE_SOUND || GetAudition() == AUDIO_VOICE_SOUND)) || (nAudition != AUDIO_NO_SOUND && (GetAudition() == AUDIO_STANDARD_SOUND || nAudition == GetAudition())))
	{
		if (GetAudition() == AUDIO_STANDARD_SOUND || nAudition == AUDIO_STANDARD_SOUND)
		{
			SetAudition(AUDIO_NO_SOUND);
			return TRUE;
		}
		m_thrdSound[1].Pause();
		SetAudition(AUDIO_NO_SOUND);
		return TRUE;
	}
	return FALSE;
}

BOOL CAudioDevice::AlertBySound(DWORD dwSoundAlias)
{
	return PlaySound((LPCTSTR)((DWORD_PTR)dwSoundAlias), (HMODULE)NULL, SND_ALIAS_ID | SND_ASYNC);
}
