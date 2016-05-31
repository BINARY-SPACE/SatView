// AUDIO.H : Audio Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the audio related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/07/24 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "thread.h"


/////////////////////////////////////////////////////////////////////////////
// CAudio

class AFX_EXT_CLASS CAudio : public CObject
{
	// Construction
public:
	CAudio();
	~CAudio();

	// Attributes
public:

	// Operations
public:
	INT EnumInputDevices(CStringArray &szDevices, CDWordArray &dwFormats) CONST;
	INT EnumOutputDevices(CStringArray &szDevices, CDWordArray &dwFormats, CDWordArray &dwFeatures) CONST;

	DWORD EnumOutputDeviceFeatures(LPCTSTR pszDevice) CONST;

	INT EnumVoices(CStringArray &szSpeakers, WORD wGender = -1, WORD wAge = -1) CONST;
	INT EnumVoiceGenders(CStringArray &szGenders) CONST;
	INT EnumVoiceAges(CStringArray &szAges) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAudioThread thread

class AFX_EXT_CLASS CAudioThread : public CThread
{
	DECLARE_DYNCREATE(CAudioThread)

	// Construction
public:
	CAudioThread();
	~CAudioThread();

	// Attributes
private:
	UINT  m_nDeviceID;
	DWORD  m_dwPitch;
	DWORD  m_dwVolume;
	DWORD  m_dwPlaybackRate;
	CEvent  m_hObjects[3];

	// Operations
public:
	BOOL Start(class CAudioDevice *pAudioDevice);
	BOOL Continue();
	BOOL Pause();
	BOOL Stop();

private:
	BOOL PlayBeepSound(class CAudioDevice *pAudioDevice);
	BOOL PlayWaveSound(class CAudioDevice *pAudioDevice);
	BOOL PlayVoiceSound(class CAudioDevice *pAudioDevice);

	HWAVEOUT PrepareDevice(class CAudioDevice *pAudioDevice, WAVEFORMATEX *pWaveInfo);
	BOOL ReleaseDevice(HWAVEOUT hDevice);

	BOOL PrepareWaveInfo(UINT nDeviceID, WAVEFORMATEX *pWaveInfo) CONST;
	BOOL PrepareWaveInfo(LPCTSTR pszSound, WAVEFORMATEX *pWaveInfo) CONST;
	BOOL PrepareWaveData(CONST WAVEFORMATEX *pWaveInfo, DWORD dwFrequency, WAVEHDR *pWaveHeader) CONST;
	BOOL PrepareWaveData(LPCTSTR pszSound, WAVEHDR *pWaveHeader) CONST;
	BOOL ReleaseWaveData(WAVEHDR *pWaveHeader) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudioThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAudioThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAudioDevice

// Specify the audio device sound types
#define AUDIO_NO_SOUND   (1<<0)
#define AUDIO_BEEP_SOUND   (1<<1)
#define AUDIO_WAVE_SOUND   (1<<2)
#define AUDIO_VOICE_SOUND   (1<<3)
#define AUDIO_STANDARD_SOUND   (1<<4)
// Specify the audio device characteristics
#define AUDIO_MINPITCH   0x04000
#define AUDIO_MAXPITCH   0x40000
#define AUDIO_DEFAULTPITCH   0x10000
#define AUDIO_MINPLAYBACKRATE   0x04000
#define AUDIO_MAXPLAYBACKRATE   0x40000
#define AUDIO_DEFAULTPLAYBACKRATE   0x10000
// Specify the audio device beep information
#define AUDIO_BEEPDURATION   500
#define AUDIO_MINBEEPFREQUENCY   200
#define AUDIO_MAXBEEPFREQUENCY   2000
#define AUDIO_DEFAULTBEEPFREQUENCY   1000
// Specify the audio device voice characteristics
#define AUDIO_VOICEGENDER_MALE   0
#define AUDIO_VOIVEGENDER_FEMALE   1
#define AUDIO_VOICEGENDER_NEUTRAL   2
#define AUDIO_VOICEAGE_BABY   0
#define AUDIO_VOICEAGE_TODDLER   1
#define AUDIO_VOICEAGE_CHILD   2
#define AUDIO_VOICEAGE_ADOLESCENT   3
#define AUDIO_VOICEAGE_ADULT   4
#define AUDIO_VOICEAGE_SENIOR   5
// Specify the audio device pause duration
#define AUDIO_DEFAULTPAUSEDURATION   500

class AFX_EXT_CLASS CAudioDevice : public CObject
{
	// Construction
public:
	CAudioDevice();

	// Attributes
private:
	INT  m_nAudition;
	UINT  m_nDeviceID;
	DWORD  m_dwVoice;
	DWORD  m_dwPitch;
	DWORD  m_dwVolume;
	DWORD  m_dwPlaybackRate;
	DWORD  m_dwPlaybackCount;
	DWORD  m_dwPlaybackInterval;
	DWORD  m_dwFrequency;
	CString  m_szAdapter;
	CString  m_szSpeaker;
	CString  m_szMessage;
	CString  m_szSound;
private:
	CAudioThread  m_thrdSound[2];

	// Operations
public:
	VOID SetAdapter(LPCTSTR pszAdapter);
	CString GetAdapter() CONST;
	VOID SetDeviceID(UINT nDeviceID);
	UINT GetDeviceID() CONST;
	VOID SetAudition(INT nAudition);
	INT GetAudition() CONST;
	VOID SetVolume(DWORD dwVolume);
	DWORD GetVolume() CONST;
	VOID SetPitch(DWORD dwPitch);
	DWORD GetPitch() CONST;
	VOID SetPlaybackRate(DWORD dwPlaybackRate);
	DWORD GetPlaybackRate() CONST;
	VOID SetPlaybackCount(DWORD dwPlaybackCount);
	DWORD GetPlaybackCount() CONST;
	VOID SetPlaybackInterval(DWORD dwPlaybackInterval);
	DWORD GetPlaybackInterval() CONST;
	VOID SetBeepFrequency(DWORD dwFrequency);
	DWORD GetBeepFrequency() CONST;
	VOID SetWaveSound(LPCTSTR pszSound);
	CString GetWaveSound() CONST;
	VOID SetVoiceSpeaker(LPCTSTR pszSpeaker);
	CString GetVoiceSpeaker() CONST;
	VOID SetVoiceGender(WORD wGender);
	WORD GetVoiceGender() CONST;
	VOID SetVoiceAge(WORD wAge);
	WORD GetVoiceAge() CONST;
	VOID SetVoiceMessage(LPCTSTR pszMessage);
	CString GetVoiceMessage() CONST;

	BOOL StartSound(INT nAudition);
	BOOL StartSound(LPCTSTR pszAdapter, INT nAudition, DWORD dwVolume, DWORD dwPitch, DWORD dwFrequency, DWORD dwPlaybackCount = -1, DWORD dwPlaybackInterval = AUDIO_DEFAULTPAUSEDURATION);
	BOOL StartSound(LPCTSTR pszAdapter, INT nAudition, DWORD dwVolume, DWORD dwPitch, DWORD dwPlaybackRate, LPCTSTR pszSound, DWORD dwPlaybackCount = -1, DWORD dwPlaybackInterval = AUDIO_DEFAULTPAUSEDURATION);
	BOOL StartSound(LPCTSTR pszAdapter, INT nAudition, DWORD dwVolume, DWORD dwPitch, DWORD dwPlaybackRate, LPCTSTR pszSpeaker, WORD wGender, WORD wAge, LPCTSTR pszMessage, DWORD dwPlaybackCount = -1, DWORD dwPlaybackInterval = AUDIO_DEFAULTPAUSEDURATION);
	BOOL StopSound(INT nAudition = AUDIO_NO_SOUND);

public:
	static BOOL AlertBySound(DWORD dwSoundAlias = SND_ALIAS_SYSTEMDEFAULT);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __AUDIO_H__
