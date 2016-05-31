// LOGFILE.CPP : Logfile Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the logfile related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/01/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLogFile

CLogFile::CLogFile() : CFileEx()
{
	m_nItemCount = 0;
	m_nRetention = 0;
	m_tRetention = 0;
	m_fRetention = LOGFILE_DEFAULT_SIZE;
	m_nPolicy = LOGFILE_POLICY_CYCLICMODE | LOGFILE_POLICY_RETENTIONBYSIZE;
	m_cbRecord = LOGFILE_DEFAULT_RECORDSIZE;
	m_hWatchEvent = (HANDLE)NULL;
	m_fPosition = sizeof(HEADER);
	m_fFirstPosition = 0;
	m_fLastPosition = 0;
	m_fWatchPosition = 0;
	m_pCriticalSection = new CCriticalSection;
	m_nLocks = 0;
}

CLogFile::~CLogFile()
{
	if (IsWatched())
	{
		FindCloseChangeNotification(m_hWatchEvent);
		m_hWatchEvent = (HANDLE)NULL;
	}
	delete m_pCriticalSection;
}

BOOL CLogFile::Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, LPCTSTR pszType, UINT nFlags, BOOL bWait)
{
	return Open(pszFileName, pszSpacecraft, pszType, (LPCTSTR)NULL, nFlags, bWait);
}
BOOL CLogFile::Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, LPCTSTR pszType, LPCTSTR pszAlternateType, UINT nFlags, BOOL bWait)
{
	OVERLAPPED  fOverlapped = { 0,0,0,0,0 };

	if (Lock())
	{
		if (CFileEx::Open(pszFileName, (nFlags & ~(typeText | shareDenyRead | shareDenyWrite | shareExclusive)) | typeBinary | shareDenyNone))
		{
			if (LockFileEx(m_hFile, ((nFlags & CFileEx::modeWrite) || (nFlags & CFileEx::modeReadWrite)) ? (LOCKFILE_EXCLUSIVE_LOCK | ((!bWait) ? LOCKFILE_FAIL_IMMEDIATELY : 0)) : 0, 0, MAXDWORD, MAXDWORD, &fOverlapped))
			{
				if ((GetSize() < sizeof(HEADER) && Initialize(pszSpacecraft, pszType)) || (GetSize() >= sizeof(HEADER) && LoadHeader() && CheckHeaderInfo(pszSpacecraft, pszType, pszAlternateType))) return TRUE;
				UnlockFileEx(m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
			}
			CFileEx::Close();
		}
		Unlock();
	}
	return FALSE;
}

BOOL CLogFile::Initialize(LPCTSTR pszSpacecraft, LPCTSTR pszType)
{
	if (IsLocked())
	{
		m_nItemCount = 0;
		m_fFirstPosition = 0;
		m_fLastPosition = 0;
		m_fPosition = sizeof(HEADER);
		m_szText = ConstructHeaderInfo(pszSpacecraft, pszType);
		return SetSize(m_fPosition) && SaveHeader();
	}
	return FALSE;
}

BOOL CLogFile::Compress(BOOL bEnable)
{
	DWORD  cbCompression;
	USHORT  nCompression;

	return((IsLocked()) ? (DeviceIoControl((HANDLE)m_hFile, FSCTL_GET_COMPRESSION, (LPVOID)NULL, 0, &nCompression, sizeof(nCompression), &cbCompression, (LPOVERLAPPED)NULL) && ((nCompression == COMPRESSION_FORMAT_NONE  &&  !bEnable) || (nCompression != COMPRESSION_FORMAT_NONE  &&  bEnable) || DeviceIoControl((HANDLE)m_hFile, FSCTL_SET_COMPRESSION, &(nCompression = (bEnable) ? COMPRESSION_FORMAT_DEFAULT : COMPRESSION_FORMAT_NONE), sizeof(nCompression), (LPVOID)NULL, 0, &cbCompression, (LPOVERLAPPED)NULL))) : FALSE);
}

BOOL CLogFile::Reset()
{
	if (IsLocked())
	{
		m_nItemCount = 0;
		m_fFirstPosition = 0;
		m_fLastPosition = 0;
		m_fPosition = sizeof(HEADER);
		return SetSize(m_fPosition) && SaveHeader();
	}
	return FALSE;
}

VOID CLogFile::Close()
{
	OVERLAPPED  fOverlapped = { 0,0,0,0,0 };

	if (IsLocked())
	{
		UnlockFileEx(m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
		CFileEx::Close();
		Unlock();
	}
}

BOOL CLogFile::SetMode(UINT nMode)
{
	UINT  nPolicy;

	if (IsLocked())
	{
		if (nMode == LOGFILE_POLICY_CYCLICMODE || nMode == LOGFILE_POLICY_NONCYCLICMODE)
		{
			if ((nPolicy = (m_nPolicy & ~(LOGFILE_POLICY_CYCLICMODE | LOGFILE_POLICY_NONCYCLICMODE)) | nMode) != m_nPolicy)
			{
				m_nPolicy = nPolicy;
				return SaveHeader();
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLogFile::GetMode(UINT &nMode) CONST
{
	if (IsLocked())
	{
		nMode = m_nPolicy & (LOGFILE_POLICY_CYCLICMODE | LOGFILE_POLICY_NONCYCLICMODE);
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::SetPolicy(UINT nPolicy)
{
	if (IsLocked())
	{
		m_nPolicy = nPolicy;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::GetPolicy(UINT &nPolicy) CONST
{
	if (IsLocked())
	{
		nPolicy = m_nPolicy;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::SetRecordSize(INT cbRecord)
{
	if (IsLocked())
	{
		if (cbRecord >= LOGFILE_DEFAULT_RECORDSIZE)
		{
			if (cbRecord != m_cbRecord)
			{
				m_cbRecord = cbRecord;
				return Reset();
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLogFile::GetRecordSize(INT &cbRecord) CONST
{
	if (IsLocked())
	{
		cbRecord = m_cbRecord;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::SetTime(CONST FILETIME *pTime)
{
	return((IsLocked()) ? SetFileTime((HANDLE)m_hFile, pTime, (LPFILETIME)NULL, (LPFILETIME)NULL) : FALSE);
}

BOOL CLogFile::GetTime(LPFILETIME pTime) CONST
{
	return((IsLocked()) ? GetFileTime((HANDLE)m_hFile, pTime, (LPFILETIME)NULL, (LPFILETIME)NULL) : FALSE);
}

BOOL CLogFile::SetSize(DWORDLONG fSize)
{
	return((IsLocked()) ? SeekPosition(fSize) && SetEndOfFile((HANDLE)m_hFile) : FALSE);
}

DWORDLONG CLogFile::GetSize() CONST
{
	DWORDLONG  dwSize;
	LARGE_INTEGER  nSize;

	if (IsLocked())
	{
		if (GetFileSizeEx((HANDLE)m_hFile, &nSize))
		{
			dwSize = nSize.QuadPart;
			return dwSize;
		}
	}
	return 0;
}

BOOL CLogFile::IsEmpty() CONST
{
	return((IsLocked()) ? ((GetSize() <= sizeof(HEADER)) ? TRUE : FALSE) : FALSE);
}

BOOL CLogFile::SetType(LPCTSTR pszType)
{
	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_TYPE), pszType) : FALSE);
}

BOOL CLogFile::GetType(CString &szType) CONST
{
	return((IsLocked()) ? ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_TYPE), szType) : FALSE);
}

BOOL CLogFile::SetSpacecraft(LPCTSTR pszSpacecraft)
{
	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_SPACECRAFT), pszSpacecraft) : FALSE);
}

BOOL CLogFile::GetSpacecraft(CString &szSpacecraft) CONST
{
	return((IsLocked()) ? ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_SPACECRAFT), szSpacecraft) : FALSE);
}

BOOL CLogFile::SetCopyrightProduct(LPCTSTR pszProduct)
{
	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_PRODUCT), pszProduct) : FALSE);
}

BOOL CLogFile::GetCopyrightProduct(CString &szProduct) CONST
{
	return((IsLocked()) ? ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_PRODUCT), szProduct) : FALSE);
}

BOOL CLogFile::SetCopyrightVersion(DWORD dwVersion)
{
	CStringTools  cStringTools;

	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_VERSION), cStringTools.ConvertUIntToString(dwVersion)) : FALSE);
}

BOOL CLogFile::GetCopyrightVersion(DWORD &dwVersion) CONST
{
	CString  szVersion;

	return((IsLocked()) ? (((dwVersion = (ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_VERSION), szVersion)) ? (DWORD)_ttoi(szVersion) : -1) != (DWORD)-1) ? TRUE : FALSE) : FALSE);
}

BOOL CLogFile::SetCopyrightCompany(LPCTSTR pszCompany)
{
	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_COMPANY), pszCompany) : FALSE);
}

BOOL CLogFile::GetCopyrightCompany(CString &szCompany) CONST
{
	return((IsLocked()) ? ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_COMPANY), szCompany) : FALSE);
}

BOOL CLogFile::SetCopyrightTrademark(LPCTSTR pszTrademark)
{
	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_TRADEMARK), pszTrademark) : FALSE);
}

BOOL CLogFile::GetCopyrightTrademark(CString &szTrademark) CONST
{
	return((IsLocked()) ? ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_TRADEMARK), szTrademark) : FALSE);
}

BOOL CLogFile::SetCopyrightCreationTime(CONST CTimeKey &tTime)
{
	CStringTools  cStringTools;

	return((IsLocked()) ? WriteHeaderInfo(STRING(IDS_LOGFILEHEADER_CREATIONTIME), cStringTools.ConvertLongIntToString(tTime.GetTime())) : FALSE);
}

BOOL CLogFile::GetCopyrightCreationTime(CTimeKey &tTime) CONST
{
	CString  szTime;

	if (IsLocked())
	{
		if (ReadHeaderInfo(STRING(IDS_LOGFILEHEADER_CREATIONTIME), szTime))
		{
			tTime = _ttoi64(szTime);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLogFile::SetRetentionByItem(INT nRetention)
{
	if (IsLocked())
	{
		if (!(m_nPolicy & LOGFILE_POLICY_RETENTIONBYITEM) || nRetention != m_nRetention)
		{
			m_nPolicy = (nRetention > 0) ? (m_nPolicy | LOGFILE_POLICY_RETENTIONBYITEM) : (m_nPolicy & ~LOGFILE_POLICY_RETENTIONBYITEM);
			return(((m_nRetention = nRetention) > 0) ? ((m_nItemCount <= nRetention) ? SaveHeader() : Reset()) : SaveHeader());
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::GetRetentionByItem(INT &nRetention) CONST
{
	if (IsLocked())
	{
		nRetention = m_nRetention;
		return((m_nPolicy & LOGFILE_POLICY_RETENTIONBYITEM) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CLogFile::SetRetentionBySize(DWORDLONG fRetention)
{
	if (IsLocked())
	{
		if (!(m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE) || fRetention != m_fRetention)
		{
			m_nPolicy = (fRetention > 0) ? (m_nPolicy | LOGFILE_POLICY_RETENTIONBYSIZE) : (m_nPolicy & ~LOGFILE_POLICY_RETENTIONBYSIZE);
			return(((m_fRetention = fRetention) > 0) ? ((GetSize() <= fRetention) ? SaveHeader() : Reset()) : SaveHeader());
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::GetRetentionBySize(DWORDLONG &fRetention) CONST
{
	if (IsLocked())
	{
		fRetention = m_fRetention;
		return((m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CLogFile::SetRetentionByTime(CONST CTimeSpan &tRetention)
{
	RECORDHEADER  fHeader[2];

	if (IsLocked())
	{
		if (!(m_nPolicy & LOGFILE_POLICY_RETENTIONBYTIME) || tRetention != m_tRetention)
		{
			m_nPolicy = (tRetention > 0) ? (m_nPolicy | LOGFILE_POLICY_RETENTIONBYTIME) : (m_nPolicy & ~LOGFILE_POLICY_RETENTIONBYTIME);
			return(((m_tRetention = tRetention) > 0) ? ((GetSize() > sizeof(HEADER) && ReadRecordHeader(m_fFirstPosition, &fHeader[0]) && ReadRecordHeader(m_fLastPosition, &fHeader[1]) && fHeader[1].tTimeKey - fHeader[0].tTimeKey <= tRetention.GetTotalSeconds()) ? SaveHeader() : Reset()) : SaveHeader());
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::GetRetentionByTime(CTimeSpan &tRetention) CONST
{
	if (IsLocked())
	{
		tRetention = m_tRetention;
		return((m_nPolicy & LOGFILE_POLICY_RETENTIONBYTIME) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CLogFile::Write(CONST CTimeKey &tTimeKey, CONST CByteArray &nInfo)
{
	INT  cbData;
	INT  cbRecordData;
	BOOL  bRecordDataHeader;
	BOOL  bRetentionSize;
	DWORDLONG  fPosition;
	DWORDLONG  fFirstPosition;
	DWORDLONG  fLastPosition;
	DWORDLONG  fCalcPosition;
	RECORDHEADER  fHeader;
	RECORDDATAHEADER  fDataHeader;
	CTimeKey  tTime;

	if (IsLocked())
	{
		if (Check((tTime = tTimeKey), (fPosition = m_fPosition), (INT)nInfo.GetSize(), bRetentionSize))
		{
			for (cbData = 0, fHeader.tTimeKey = fDataHeader.tTimeKey = tTime.GetTime(), fHeader.fPosition = (IsHeaderPosition((fPosition = AdjustPosition(fPosition)))) ? (fPosition + sizeof(RECORDHEADER)) : fPosition, fDataHeader.nCount = m_nItemCount, fDataHeader.cbInfo = (INT)nInfo.GetSize(), bRecordDataHeader = FALSE; cbData < fDataHeader.cbInfo; )
			{
				if (IsHeaderPosition(AdjustPosition(fPosition)))
				{
					if (m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE)
					{
						if (fPosition + m_cbRecord > m_fRetention)
						{
							SetSize(fPosition);
							fPosition = sizeof(HEADER);
							fHeader.fPosition = (!bRecordDataHeader) ? (fPosition + sizeof(RECORDHEADER)) : fHeader.fPosition;
						}
					}
					if (bRetentionSize)
					{
						SetSize(fPosition);
						fPosition = sizeof(HEADER);
						fHeader.fPosition = (!bRecordDataHeader) ? (fPosition + sizeof(RECORDHEADER)) : fHeader.fPosition;
						bRetentionSize = FALSE;
					}
					if (!WriteRecordHeader(fPosition, &fHeader)) break;
					fPosition += sizeof(RECORDHEADER);
				}
				if (!bRecordDataHeader)
				{
					if (!WriteRecordDataHeader((fLastPosition = fPosition), &fDataHeader)) break;
					fPosition += sizeof(RECORDDATAHEADER);
					bRecordDataHeader = TRUE;
				}
				if (SeekPosition(fPosition) && Write((LPSTR)nInfo.GetData() + cbData, (cbRecordData = min(CalculateRecordDataSize(fPosition), fDataHeader.cbInfo - cbData))))
				{
					fPosition += cbRecordData;
					cbData += cbRecordData;
					continue;
				}
				break;
			}
			if (fDataHeader.cbInfo > 0 && cbData == fDataHeader.cbInfo)
			{
				for (fFirstPosition = ((m_fPosition < fPosition && m_fPosition <= m_fFirstPosition && fPosition > m_fFirstPosition) || (fPosition < m_fPosition && (fPosition > m_fFirstPosition || m_fPosition <= m_fFirstPosition))) ? (((fFirstPosition = FindHeaderPosition(fPosition + m_cbRecord)) < GetSize()) ? fFirstPosition : sizeof(HEADER)) : ((!m_fFirstPosition) ? (sizeof(HEADER) + sizeof(RECORDHEADER)) : m_fFirstPosition); (m_fPosition < fPosition && m_fPosition <= m_fFirstPosition && fPosition > m_fFirstPosition) || (fPosition < m_fPosition && (fPosition > m_fFirstPosition || m_fPosition <= m_fFirstPosition)); fFirstPosition = ((fFirstPosition = FindHeaderPosition(fFirstPosition + m_cbRecord)) < GetSize()) ? fFirstPosition : sizeof(HEADER))
				{
					if (FindHeaderPosition(fFirstPosition) != FindHeaderPosition(fPosition) && ReadRecordHeader(fFirstPosition, &fHeader))
					{
						if (((fPosition < fFirstPosition  &&  fPosition <= fHeader.fPosition) || fPosition >= fFirstPosition) && fFirstPosition >= fHeader.fPosition - sizeof(RECORDHEADER))
						{
							fFirstPosition = (ReadRecordDataHeader(fHeader.fPosition, &fDataHeader) && ((m_fPosition < fPosition && ((fCalcPosition = ProgressPosition(fHeader.fPosition, fDataHeader.cbInfo)) <= m_fPosition || fCalcPosition > fPosition)) || (m_fPosition > fPosition && (fCalcPosition = ProgressPosition(fHeader.fPosition, fDataHeader.cbInfo)) <= m_fPosition  &&  fCalcPosition > fPosition))) ? fHeader.fPosition : fLastPosition;
							break;
						}
						continue;
					}
					fFirstPosition = fLastPosition;
					break;
				}
				m_fPosition = fPosition;
				m_fLastPosition = fLastPosition;
				m_fFirstPosition = fFirstPosition;
				m_fFirstPosition = ((m_nPolicy & LOGFILE_POLICY_RETENTIONBYTIME) && SeekTo(CTimeKey(tTime.GetTime() - m_tRetention.GetTotalSeconds()), TRUE)) ? GetPosition() : m_fFirstPosition;
				m_fFirstPosition = ((m_nPolicy & LOGFILE_POLICY_RETENTIONBYITEM) && ReadRecordDataHeader(m_fFirstPosition, &fDataHeader) && m_nRetention <= ((m_nItemCount > fDataHeader.nCount) ? (m_nItemCount - fDataHeader.nCount) : (INT_MAX - fDataHeader.nCount + m_nItemCount + 1))) ? ProgressPosition(m_fFirstPosition, fDataHeader.cbInfo) : m_fFirstPosition;
				m_nItemCount = (m_nItemCount < INT_MAX) ? (m_nItemCount + 1) : 0;
				return SaveHeader() && SeekToLast();
			}
		}
	}
	return FALSE;
}

BOOL CLogFile::Read(CTimeKey &tTimeKey, CByteArray &nInfo) CONST
{
	INT  cbData;
	INT  cbRecordData;
	DWORDLONG  fPosition;
	RECORDDATAHEADER  fDataHeader;

	if (IsLocked())
	{
		if (CheckPosition((fPosition = GetPosition())) && ReadRecordDataHeader(fPosition, &fDataHeader))
		{
			for (cbData = 0, tTimeKey = fDataHeader.tTimeKey, nInfo.RemoveAll(), nInfo.SetSize(fDataHeader.cbInfo); cbData < fDataHeader.cbInfo && nInfo.GetSize() == fDataHeader.cbInfo; cbData += cbRecordData)
			{
				if (SeekPosition((fPosition = ProgressRecordData((!cbData) ? GetPosition() : fPosition, 0))) && Read((LPSTR)nInfo.GetData() + cbData, (cbRecordData = min(CalculateRecordDataSize(fPosition), fDataHeader.cbInfo - cbData))))
				{
					fPosition += cbRecordData;
					continue;
				}
				break;
			}
			return((cbData == fDataHeader.cbInfo  &&  SeekPosition(((fPosition = ProgressRecordData(AdjustPosition(fPosition), 0)) != m_fFirstPosition) ? fPosition : 0)) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CLogFile::SeekToFirst() CONST
{
	return((IsLocked()) ? ((!IsEmpty() && SeekPosition(m_fFirstPosition)) ? TRUE : FALSE) : FALSE);
}

BOOL CLogFile::SeekToLast() CONST
{
	return((IsLocked()) ? ((!IsEmpty() && SeekPosition(m_fLastPosition)) ? TRUE : FALSE) : FALSE);
}

BOOL CLogFile::SeekTo(CONST CTimeKey &tTimeKey, BOOL bNotBefore) CONST
{
	DWORDLONG  fPosition;
	DWORDLONG  fMinPosition;
	DWORDLONG  fMaxPosition;
	RECORDHEADER  fHeader;
	RECORDDATAHEADER  fDataHeader[2];

	if (IsLocked())
	{
		if (SeekToFirst() && ReadRecordDataHeader(GetPosition(), &fDataHeader[0]) && SeekToLast() && ReadRecordDataHeader(GetPosition(), &fDataHeader[1]))
		{
			if (fDataHeader[0].tTimeKey < tTimeKey.GetTime() && fDataHeader[1].tTimeKey >= tTimeKey.GetTime())
			{
				if (m_fFirstPosition <= m_fLastPosition || ReadRecordHeader(sizeof(HEADER), &fHeader))
				{
					fMinPosition = (m_fFirstPosition <= m_fLastPosition || fHeader.tTimeKey >= tTimeKey.GetTime()) ? m_fFirstPosition : sizeof(HEADER);
					fMaxPosition = (m_fFirstPosition > m_fLastPosition  &&  fHeader.tTimeKey >= tTimeKey.GetTime()) ? GetSize() : m_fLastPosition;
					for (fPosition = (fMinPosition + fMaxPosition) / 2; fMaxPosition - fMinPosition > m_cbRecord; fPosition = (fMinPosition + fMaxPosition) / 2)
					{
						if (ReadRecordHeader(fPosition, &fHeader))
						{
							if (fHeader.tTimeKey < tTimeKey.GetTime())
							{
								fMinPosition = fPosition;
								continue;
							}
							fMaxPosition = fPosition;
							continue;
						}
						break;
					}
					for (fMinPosition = (fMaxPosition - fMinPosition <= m_cbRecord && ReadRecordHeader(fMinPosition, &fHeader)) ? ((m_fFirstPosition <= m_fLastPosition && (fHeader.fPosition < m_fFirstPosition || fHeader.fPosition > m_fLastPosition)) ? ((fHeader.fPosition < m_fFirstPosition) ? m_fFirstPosition : m_fLastPosition) : fHeader.fPosition) : 0, fMinPosition = (fMinPosition > 0) ? ((m_fFirstPosition > m_fLastPosition && fHeader.fPosition < m_fFirstPosition && fHeader.fPosition > m_fLastPosition) ? ((fHeader.tTimeKey - fDataHeader[0].tTimeKey <= fDataHeader[1].tTimeKey - fHeader.tTimeKey) ? m_fFirstPosition : m_fLastPosition) : fHeader.fPosition) : 0, fPosition = 0; fMinPosition > 0; )
					{
						if (fMinPosition != m_fLastPosition  &&  ReadRecordDataHeader(fMinPosition, &fDataHeader[0]) && ReadRecordDataHeader((fPosition = ProgressPosition(fMinPosition, fDataHeader[0].cbInfo)), &fDataHeader[1]))
						{
							if (fDataHeader[0].tTimeKey < tTimeKey.GetTime() && fDataHeader[1].tTimeKey <= tTimeKey.GetTime())
							{
								fMinPosition = fPosition;
								continue;
							}
							break;
						}
						fPosition = (fMinPosition == m_fLastPosition) ? fMinPosition : 0;
						break;
					}
					return((fPosition) ? ((bNotBefore) ? SeekPosition(fPosition) : SeekPosition(fMinPosition)) : FALSE);
				}
				SeekToFirst();
				return FALSE;
			}
			return((fDataHeader[0].tTimeKey >= tTimeKey.GetTime()) ? SeekToFirst() : SeekToLast());
		}
		SeekToFirst();
	}
	return FALSE;
}

BOOL CLogFile::SeekFromPosition(DWORDLONG fStartPosition, INT nCount) CONST
{
	INT  nItem;
	DWORDLONG  fPosition;
	RECORDHEADER  fHeader;
	RECORDDATAHEADER  fDataHeader;

	if (IsLocked())
	{
		if (((fPosition = FindHeaderPosition(fStartPosition)) != FindHeaderPosition(m_fFirstPosition) || m_fFirstPosition > m_fLastPosition) && ReadRecordHeader(fPosition, &fHeader))
		{
			for (nItem = -1; (m_fFirstPosition < m_fLastPosition && fHeader.fPosition > m_fFirstPosition && fHeader.fPosition <= m_fLastPosition) || (m_fFirstPosition > m_fLastPosition && (fHeader.fPosition <= m_fLastPosition || fHeader.fPosition > m_fFirstPosition)); fPosition = FindHeaderPosition((fPosition >= sizeof(HEADER) + m_cbRecord) ? (fPosition - m_cbRecord) : (GetSize() - 1)))
			{
				if (ReadRecordHeader(fPosition, &fHeader) && ReadRecordDataHeader(fHeader.fPosition, &fDataHeader))
				{
					if (((nItem = (nItem < 0) ? fDataHeader.nCount : nItem) >= fDataHeader.nCount  &&  nItem - fDataHeader.nCount >= nCount) || (nItem < fDataHeader.nCount  &&  INT_MAX - fDataHeader.nCount + nItem + 1 >= nCount))
					{
						fPosition = fHeader.fPosition;
						break;
					}
					continue;
				}
				break;
			}
			return SeekPosition((!IsHeaderPosition(fPosition)) ? fPosition : m_fFirstPosition);
		}
		return SeekToFirst();
	}
	return FALSE;
}

BOOL CLogFile::SeekFromEnd(INT nCount) CONST
{
	return SeekFromPosition(m_fLastPosition, nCount);
}

HANDLE CLogFile::BeginWatch()
{
	INT  nPos;
	CString  szRoot;
	CLogicalDrives  cDrives;

	if (IsLocked())
	{
		if (!IsWatched())
		{
			for (nPos = (!_tcsnicmp(GetFilePath(), STRING(IDS_LOCALNET_DELIMITER), lstrlen(STRING(IDS_LOCALNET_DELIMITER)))) ? (GetFilePath().GetLength() - 1) : 0; nPos > 0; nPos--)
			{
				if (GetFilePath()[nPos] == cDrives.GetPathDelimiter())
				{
					szRoot = GetFilePath().Left(nPos + 1);
					break;
				}
			}
			if ((m_hWatchEvent = FindFirstChangeNotification((szRoot = (szRoot.IsEmpty()) ? (GetFilePath().Left(GetFilePath().GetLength() - GetFileName().GetLength())) : szRoot), FALSE, FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE)) != INVALID_HANDLE_VALUE)
			{
				m_fWatchPosition = m_fPosition;
				return m_hWatchEvent;
			}
		}
	}
	return((HANDLE)NULL);
}

BOOL CLogFile::IsWatched() CONST
{
	return((m_hWatchEvent != INVALID_HANDLE_VALUE  &&  m_hWatchEvent != (HANDLE)NULL) ? TRUE : FALSE);
}

BOOL CLogFile::Watch(CByteArray &nInfo)
{
	CTimeKey  tTimeKey;

	if (IsLocked())
	{
		if (IsWatched())
		{
			if (WaitForSingleObject(m_hWatchEvent, 0) == WAIT_OBJECT_0)
			{
				if (CheckPosition(ProgressRecordData(AdjustPosition(m_fWatchPosition), 0)) && Read(tTimeKey, nInfo))
				{
					if (m_fWatchPosition == m_fLastPosition)
					{
						FindNextChangeNotification(m_hWatchEvent);
						m_fWatchPosition = m_fPosition;
						return TRUE;
					}
					m_fWatchPosition = GetPosition();
					return TRUE;
				}
				FindNextChangeNotification(m_hWatchEvent);
				m_fWatchPosition = m_fPosition;
			}
		}
	}
	return FALSE;
}

BOOL CLogFile::EndWatch()
{
	if (IsLocked())
	{
		if (IsWatched())
		{
			if (FindCloseChangeNotification(m_hWatchEvent))
			{
				m_hWatchEvent = (HANDLE)NULL;
				m_fWatchPosition = 0;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CLogFile::Rename(LPCTSTR pszFileName, LPCTSTR pszNewFileName, BOOL bHide)
{
	DWORD  dwTime[2];
	DWORD  dwTimeInterval;
	CFileFindEx  cFileFind;

	if (cFileFind.FindFile(pszFileName))
	{
		for (dwTime[0] = GetTickCount(); cFileFind.FindFile(pszFileName); dwTimeInterval = ((dwTime[1] = GetTickCount()) >= dwTime[0]) ? ((dwTime[1] - dwTime[0]) / 10) : 0, Sleep(dwTimeInterval), dwTime[0] = dwTime[1])
		{
			if (CFileEx::Move(pszFileName, pszNewFileName))
			{
				cFileFind.Close();
				break;
			}
			cFileFind.Close();
		}
		return SetFileAttributes(pszNewFileName, (bHide) ? (GetFileAttributes(pszNewFileName) | FILE_ATTRIBUTE_HIDDEN) : (GetFileAttributes(pszNewFileName) & ~FILE_ATTRIBUTE_HIDDEN));
	}
	return FALSE;
}

BOOL CLogFile::Remove(LPCTSTR pszFileName)
{
	DWORD  dwTime[2];
	DWORD  dwTimeInterval;
	CFileFindEx  cFileFind;

	if (cFileFind.FindFile(pszFileName))
	{
		for (dwTime[0] = GetTickCount(); cFileFind.FindFile(pszFileName); dwTimeInterval = ((dwTime[1] = GetTickCount()) >= dwTime[0]) ? ((dwTime[1] - dwTime[0]) / 10) : 0, Sleep(dwTimeInterval), dwTime[0] = dwTime[1])
		{
			if (CFileEx::Remove(pszFileName))
			{
				cFileFind.Close();
				break;
			}
			cFileFind.Close();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::SeekPosition(DWORDLONG fPosition) CONST
{
	DWORD  dwPositionLow;
	LONG  dwPositionHigh;

	if (fPosition != (DWORDLONG)-1)
	{
		dwPositionLow = (DWORD)fPosition;
		dwPositionHigh = (LONG)(fPosition >> 32);
		return(((dwPositionLow = SetFilePointer(m_hFile, dwPositionLow, &dwPositionHigh, FILE_BEGIN)) != (DWORD)-1 || GetLastError() == NO_ERROR) ? ((((DWORDLONG)dwPositionHigh << 32) + (DWORDLONG)dwPositionLow == fPosition) ? TRUE : FALSE) : FALSE);
	}
	return FALSE;
}

BOOL CLogFile::CheckPosition(DWORDLONG fPosition) CONST
{
	LONGLONG  cbPos;
	DWORDLONG  fPos;
	RECORDHEADER  fHeader;
	RECORDDATAHEADER  fDataHeader;

	if (fPosition >= sizeof(HEADER) && fPosition != (DWORDLONG)-1)
	{
		if (fPosition != m_fFirstPosition  &&  fPosition != m_fLastPosition)
		{
			if (((m_fFirstPosition < m_fLastPosition  &&  fPosition >= m_fFirstPosition  &&  fPosition <= m_fLastPosition) || (m_fFirstPosition > m_fLastPosition && (fPosition >= m_fFirstPosition || fPosition <= m_fLastPosition))) && ReadRecordHeader(fPosition, &fHeader))
			{
				for (fPos = fHeader.fPosition, cbPos = (fPos < fPosition) ? (fPosition - fPos) : (fPosition + (GetSize() - fPos)); fPos != fPosition && cbPos >= 0 && ReadRecordDataHeader(fPos, &fDataHeader) && fDataHeader.cbInfo > 0; fPos = ProgressPosition(fPos, fDataHeader.cbInfo), cbPos -= fDataHeader.cbInfo);
				return((fPos == fPosition) ? SeekPosition(fPosition) : FALSE);
			}
			return FALSE;
		}
		return SeekPosition(fPosition);
	}
	return FALSE;
}

DWORDLONG CLogFile::AdjustPosition(DWORDLONG fPosition) CONST
{
	DWORDLONG  fAdjustPosition;

	return((fPosition >= sizeof(HEADER)) ? (((fAdjustPosition = m_cbRecord - (fPosition - sizeof(HEADER)) % m_cbRecord) < sizeof(RECORDDATAHEADER)) ? (fPosition + fAdjustPosition) : fPosition) : fPosition);
}

DWORDLONG CLogFile::CalculatePosition(DWORDLONG fPosition, INT cbInfo) CONST
{
	DWORDLONG  fSize;
	DWORDLONG  fCalculatePosition;

	fSize = (fPosition >= FindHeaderPosition(fPosition) + sizeof(RECORDHEADER)) ? (sizeof(RECORDDATAHEADER) + ((sizeof(RECORDDATAHEADER) + fPosition - FindHeaderPosition(fPosition) - sizeof(RECORDHEADER) + cbInfo - 1) / (m_cbRecord - sizeof(RECORDHEADER)))*sizeof(RECORDHEADER) + cbInfo) : (sizeof(RECORDDATAHEADER) + ((sizeof(RECORDDATAHEADER) + cbInfo - 1) / (m_cbRecord - sizeof(RECORDHEADER)))*sizeof(RECORDHEADER) + cbInfo);
	fSize += (IsHeaderPosition((fCalculatePosition = AdjustPosition(fPosition)))) ? sizeof(RECORDHEADER) : 0;
	return fCalculatePosition + fSize;
}

DWORDLONG CLogFile::ProgressPosition(DWORDLONG fPosition, INT cbInfo) CONST
{
	DWORDLONG  fSize;
	DWORDLONG  fProgressPosition;

	return(((fSize = GetSize()) > 0) ? ((fPosition != m_fPosition || m_fFirstPosition == m_fPosition) ? (((fProgressPosition = (IsHeaderPosition((fProgressPosition = AdjustPosition((fProgressPosition = CalculatePosition(fPosition, cbInfo)))))) ? (fProgressPosition + sizeof(RECORDHEADER)) : fProgressPosition) >= fSize &&  fProgressPosition != m_fPosition) ? (sizeof(HEADER) + fProgressPosition%fSize) : fProgressPosition) : 0) : -1);
}

DWORDLONG CLogFile::FindHeaderPosition(DWORDLONG fPosition) CONST
{
	return((fPosition >= sizeof(HEADER)) ? (fPosition - (fPosition - sizeof(HEADER)) % m_cbRecord) : sizeof(HEADER));
}

BOOL CLogFile::IsHeaderPosition(DWORDLONG fPosition) CONST
{
	return((fPosition >= sizeof(HEADER) && (fPosition - sizeof(HEADER)) % m_cbRecord == 0) ? TRUE : FALSE);
}

BOOL CLogFile::IsEOFPosition(DWORDLONG fPosition) CONST
{
	return((ProgressRecordData(AdjustPosition(fPosition), 0) == ProgressRecordData(AdjustPosition(m_fPosition), 0)) ? TRUE : FALSE);
}

DWORDLONG CLogFile::ProgressRecordData(DWORDLONG fPosition, INT cbData) CONST
{
	DWORDLONG  fSize;
	DWORDLONG  fProgressPosition;

	return(((fSize = GetSize()) > 0) ? ((fPosition != m_fPosition) ? (((fProgressPosition = (IsHeaderPosition((fProgressPosition = fPosition + cbData))) ? (fProgressPosition + sizeof(RECORDHEADER)) : fProgressPosition) >= fSize  &&  fProgressPosition != m_fPosition  &&  m_fFirstPosition > m_fPosition) ? (sizeof(HEADER) + fProgressPosition%fSize) : fProgressPosition) : fPosition) : -1);
}

INT CLogFile::CalculateRecordDataSize(DWORDLONG fPosition) CONST
{
	return((fPosition >= sizeof(HEADER) && !IsHeaderPosition(fPosition)) ? (INT)(m_cbRecord - (fPosition - sizeof(HEADER)) % m_cbRecord) : 0);
}

BOOL CLogFile::SaveHeader()
{
	HEADER  fHeader;

	SeekToBegin();
	fHeader.sData.nPolicy = m_nPolicy;
	fHeader.sData.cbRecord = m_cbRecord;
	fHeader.sData.nItemCount = m_nItemCount;
	fHeader.sData.nRetention = m_nRetention;
	fHeader.sData.fRetention = m_fRetention;
	fHeader.sData.tRetention = m_tRetention.GetTotalSeconds();
	fHeader.sData.fPosition = m_fPosition;
	fHeader.sData.fFirstPosition = m_fFirstPosition;
	fHeader.sData.fLastPosition = m_fLastPosition;
	ZeroMemory(fHeader.szText, sizeof(fHeader.szText));
	CopyMemory(fHeader.szText, (LPCTSTR)m_szText, (m_szText.GetLength() + 1)*sizeof(TCHAR));
	return((!(m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE) || m_fRetention >= sizeof(fHeader)) ? Write(&fHeader, sizeof(fHeader)) : FALSE);
}

BOOL CLogFile::LoadHeader()
{
	HEADER  fHeader;

	SeekToBegin();
	if (Read(&fHeader, sizeof(fHeader)))
	{
		m_nPolicy = fHeader.sData.nPolicy;
		m_cbRecord = fHeader.sData.cbRecord;
		m_nItemCount = fHeader.sData.nItemCount;
		m_nRetention = fHeader.sData.nRetention;
		m_fRetention = fHeader.sData.fRetention;
		m_tRetention = fHeader.sData.tRetention;
		m_fPosition = fHeader.sData.fPosition;
		m_fFirstPosition = fHeader.sData.fFirstPosition;
		m_fLastPosition = fHeader.sData.fLastPosition;
		m_szText = fHeader.szText;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::WriteHeaderInfo(LPCTSTR pszInfo, LPCTSTR pszText)
{
	INT  nPos[3];

	if ((nPos[0] = m_szText.Find(pszInfo)) >= 0)
	{
		nPos[1] = nPos[0] + lstrlen(pszInfo);
		nPos[2] = m_szText.Mid(nPos[1]).Find(EOL);
		if (nPos[1] + nPos[2] < m_szText.GetLength() && nPos[2] > 0)
		{
			m_szText = m_szText.Mid(nPos[1]) + pszText + m_szText.Mid(nPos[1] + nPos[2]);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLogFile::ReadHeaderInfo(LPCTSTR pszInfo, CString &szText) CONST
{
	INT  nPos[3];

	if ((nPos[0] = m_szText.Find(pszInfo)) >= 0)
	{
		for (nPos[1] = nPos[0] + lstrlen(pszInfo), nPos[2] = m_szText.Mid(nPos[1]).Find(EOL); nPos[1] + nPos[2] < m_szText.GetLength() && nPos[2] > 0; )
		{
			szText = m_szText.Mid(nPos[1], nPos[2]);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CLogFile::CheckHeaderInfo(LPCTSTR pszSpacecraft, LPCTSTR pszType, LPCTSTR pszAlternateType) CONST
{
	CString  szType;
	CString  szProduct[2];
	CString  szSpacecraft;
	CVersionInfo  cVersionInfo;

	for (GetCopyrightProduct(szProduct[0]), szProduct[1] = cVersionInfo.QueryProductName(); szProduct[0] == szProduct[1] && (!AfxIsValidString(pszSpacecraft) || !lstrlen(pszSpacecraft) || (GetSpacecraft(szSpacecraft) && szSpacecraft == pszSpacecraft)) && ((!AfxIsValidString(pszType) || !lstrlen(pszType) || (GetType(szType) && szType == pszType)) || (AfxIsValidString(pszAlternateType) && GetType(szType) && szType == pszAlternateType)); ) return TRUE;
	return FALSE;
}

CString CLogFile::ConstructHeaderInfo(LPCTSTR pszSpacecraft, LPCTSTR pszType) CONST
{
	CString  szText[8];
	CStringTools  cStringTools;
	CVersionInfo  cVersionInfo;

	szText[1].Format(STRING(IDS_LOGFILEHEADER_INFO), (LPCTSTR)cVersionInfo.QueryProductName());
	szText[2].Format(STRING(IDS_LOGFILEHEADER_INFO), (LPCTSTR)cStringTools.ConvertUIntToString(LOGFILE_DEFAULT_VERSION));
	szText[3].Format(STRING(IDS_LOGFILEHEADER_INFO), (LPCTSTR)cVersionInfo.QueryLegalCopyright());
	szText[4].Format(STRING(IDS_LOGFILEHEADER_INFO), (LPCTSTR)cVersionInfo.QueryLegalTrademark());
	szText[5].Format(STRING(IDS_LOGFILEHEADER_INFO), pszSpacecraft);
	szText[6].Format(STRING(IDS_LOGFILEHEADER_INFO), pszType);
	szText[7].Format(STRING(IDS_LOGFILEHEADER_INFO), (LPCTSTR)cStringTools.ConvertLongIntToString(CTime::GetCurrentTime().GetTime()));
	szText[0] = STRING(IDS_LOGFILEHEADER_PRODUCT) + szText[1];
	szText[0] += STRING(IDS_LOGFILEHEADER_VERSION) + szText[2];
	szText[0] += STRING(IDS_LOGFILEHEADER_COMPANY) + szText[3];
	szText[0] += STRING(IDS_LOGFILEHEADER_TRADEMARK) + szText[4];
	szText[0] += STRING(IDS_LOGFILEHEADER_SPACECRAFT) + szText[5];
	szText[0] += STRING(IDS_LOGFILEHEADER_TYPE) + szText[6];
	szText[0] += STRING(IDS_LOGFILEHEADER_CREATIONTIME) + szText[7];
	return szText[0];
}

BOOL CLogFile::WriteRecordHeader(DWORDLONG fPosition, CONST PRECORDHEADER pfHeader)
{
	return SeekPosition(fPosition) && Write(pfHeader, sizeof(RECORDHEADER));
}

BOOL CLogFile::ReadRecordHeader(DWORDLONG fPosition, PRECORDHEADER pfHeader) CONST
{
	RECORDDATAHEADER  fDataHeader;

	if (FindHeaderPosition(m_fFirstPosition) == FindHeaderPosition(fPosition) && m_fFirstPosition > m_fLastPosition  &&  m_fFirstPosition <= fPosition)
	{
		if (ReadRecordDataHeader(m_fFirstPosition, &fDataHeader))
		{
			pfHeader->tTimeKey = fDataHeader.tTimeKey;
			pfHeader->fPosition = m_fFirstPosition;
			return TRUE;
		}
		return FALSE;
	}
	return SeekPosition(FindHeaderPosition(fPosition)) && Read(pfHeader, sizeof(RECORDHEADER));
}

BOOL CLogFile::WriteRecordDataHeader(DWORDLONG fPosition, CONST PRECORDDATAHEADER pfDataHeader)
{
	return SeekPosition(fPosition) && Write(pfDataHeader, sizeof(RECORDDATAHEADER));
}

BOOL CLogFile::ReadRecordDataHeader(DWORDLONG fPosition, PRECORDDATAHEADER pfDataHeader) CONST
{
	return SeekPosition(fPosition) && Read(pfDataHeader, sizeof(RECORDDATAHEADER));
}

BOOL CLogFile::Check(CTimeKey &tTimeKey, DWORDLONG fPosition, INT cbInfo, BOOL &bRetention) CONST
{
	DWORDLONG  dwDiskInfo;
	DWORDLONG  dwFileSize;
	DWORDLONG  dwCalcPosition;
	RECORDDATAHEADER  fDataHeader;
	ULARGE_INTEGER  nDiskInfo[3];
	CLogicalDrives  cDrives;

	if (IsLocked())
	{
		if ((CalculatePosition(fPosition, cbInfo) <= m_fRetention - (m_fRetention - sizeof(HEADER)) % m_cbRecord || !(m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE) || !(m_nPolicy & LOGFILE_POLICY_NONCYCLICMODE)) && (CalculatePosition(sizeof(HEADER), cbInfo) <= m_fRetention - (m_fRetention - sizeof(HEADER)) % m_cbRecord || !(m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE)))
		{
			if ((m_nPolicy & LOGFILE_POLICY_CYCLICMODE) && !(m_nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE))
			{
				if (GetDiskFreeSpaceEx(cDrives.ExtractDrive(GetFilePath()), &nDiskInfo[0], &nDiskInfo[1], &nDiskInfo[2]))
				{
					for (CopyMemory(&dwDiskInfo, &nDiskInfo[0], sizeof(DWORDLONG)); sizeof(HEADER) + m_cbRecord*((CalculatePosition(sizeof(HEADER), cbInfo) - sizeof(HEADER) + m_cbRecord) / m_cbRecord) <= dwDiskInfo + (dwFileSize = GetSize()); )
					{
						for (bRetention = ((dwCalcPosition = CalculatePosition(fPosition, cbInfo)) > dwFileSize && sizeof(HEADER) + m_cbRecord*((dwCalcPosition - sizeof(HEADER) + m_cbRecord) / m_cbRecord) - dwFileSize > dwDiskInfo) ? TRUE : FALSE; IsEmpty() || (SeekToLast() && ReadRecordDataHeader(GetPosition(), &fDataHeader)); )
						{
							tTimeKey = (!IsEmpty()) ? max(fDataHeader.tTimeKey, tTimeKey.GetTime()) : tTimeKey.GetTime();
							return TRUE;
						}
						break;
					}
				}
				return FALSE;
			}
			if (IsEmpty() || (SeekToLast() && ReadRecordDataHeader(GetPosition(), &fDataHeader)))
			{
				tTimeKey = (!IsEmpty()) ? max(fDataHeader.tTimeKey, tTimeKey.GetTime()) : tTimeKey.GetTime();
				bRetention = FALSE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CLogFile::Write(LPCVOID pInfo, DWORD cbInfo)
{
	DWORD  dwInfo;

	return((WriteFile(m_hFile, pInfo, cbInfo, &dwInfo, (LPOVERLAPPED)NULL) && cbInfo == dwInfo) ? TRUE : FALSE);
}

BOOL CLogFile::Read(LPVOID pInfo, DWORD cbInfo) CONST
{
	DWORD  dwInfo;

	return((ReadFile(m_hFile, pInfo, cbInfo, &dwInfo, (LPOVERLAPPED)NULL) && cbInfo == dwInfo) ? TRUE : FALSE);
}

BOOL CLogFile::Lock()
{
	if (m_pCriticalSection->Lock())
	{
		m_nLocks++;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogFile::IsLocked() CONST
{
	return((m_nLocks > 0) ? TRUE : FALSE);
}

BOOL CLogFile::Unlock()
{
	if (IsLocked())
	{
		m_nLocks--;
		m_pCriticalSection->Unlock();
		return TRUE;
	}
	return FALSE;
}
