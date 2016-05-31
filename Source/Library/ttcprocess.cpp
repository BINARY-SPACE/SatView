// TTCPROCESS.CPP : TT&C Data Processing Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telemetry and
// telecommand data processing related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTMUnit

IMPLEMENT_DYNCREATE(CTMUnit, CObject)

CTMUnit::CTMUnit() : CObject()
{
	m_tTimeTag = 0;
	m_wQuality = TMUNIT_DATAQUALITY_NONE;
	m_nUnitID = -1;
	m_tRetention = -1;
}
CTMUnit::CTMUnit(LPCTSTR pszTag) : CObject()
{
	m_szTag = pszTag;
	m_tTimeTag = 0;
	m_wQuality = TMUNIT_DATAQUALITY_NONE;
	m_nUnitID = -1;
	m_tRetention = -1;
}

VOID CTMUnit::SetTag(LPCTSTR pszTag)
{
	m_szTag = (!pszTag) ? STRING(IDS_TMUNIT_UNKNOWN) : pszTag;
}

CString CTMUnit::GetTag() CONST
{
	return m_szTag;
}

VOID CTMUnit::SetTimeTag(CONST CTimeTag &tTimeTag)
{
	m_tTimeTag = tTimeTag;
}

CTimeTag CTMUnit::GetTimeTag() CONST
{
	return m_tTimeTag;
}

VOID CTMUnit::SetUnitID(UINT nID)
{
	m_nUnitID = nID;
}

UINT CTMUnit::GetUnitID() CONST
{
	return m_nUnitID;
}

VOID CTMUnit::SetQuality(WORD wCode)
{
	m_wQuality = wCode;
}

WORD CTMUnit::GetQuality() CONST
{
	return m_wQuality;
}

BOOL CTMUnit::SetData(CONST CByteArray &nData, BOOL bExtra)
{
	m_nData[(bExtra) ? TRUE : FALSE].Copy(nData);
	return TRUE;
}

INT CTMUnit::GetData(CByteArray &nData, BOOL bExtra) CONST
{
	nData.Copy(m_nData[(bExtra) ? TRUE : FALSE]);
	return((INT)nData.GetSize());
}
BOOL CTMUnit::GetData(INT nBytePos, BYTE &nValue) CONST
{
	return Extract(m_nData[0], nBytePos, nValue);
}
BOOL CTMUnit::GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue, BOOL bLittleEndian) CONST
{
	return Extract(m_nData[0], nBytePos, nBitPos, nLength, nValue, bLittleEndian);
}

INT CTMUnit::GetSize() CONST
{
	return((INT)m_nData[0].GetSize());
}

BOOL CTMUnit::IsValid() CONST
{
	return((!m_szTag.IsEmpty() && m_nData[0].GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTMUnit::IsUnknown() CONST
{
	return((m_szTag == STRING(IDS_TMUNIT_UNKNOWN)) ? TRUE : FALSE);
}

BOOL CTMUnit::HasBadData() CONST
{
	return((IsValid() && (LOBYTE(m_wQuality) & (TMUNIT_DATAQUALITY_BAD | TMUNIT_SEQUENCEQUALITY_BAD))) ? TRUE : FALSE);
}

VOID CTMUnit::SetRetention(CONST CTimeSpan &tRetention)
{
	m_tRetention = tRetention;
}

CTimeSpan CTMUnit::GetRetention() CONST
{
	return m_tRetention;
}

VOID CTMUnit::Reset()
{
	m_szTag.Empty();
	m_tTimeTag = 0;
	m_nData[0].RemoveAll();
	m_nData[1].RemoveAll();
	m_wQuality = TMUNIT_DATAQUALITY_NONE;
	m_nUnitID = -1;
}

VOID CTMUnit::Copy(CONST CTMUnit *pTMUnit)
{
	m_szTag = pTMUnit->m_szTag;
	m_tTimeTag = pTMUnit->m_tTimeTag;
	m_nUnitID = pTMUnit->m_nUnitID;
	m_nData[0].Copy(pTMUnit->m_nData[0]);
	m_nData[1].Copy(pTMUnit->m_nData[1]);
	m_wQuality = pTMUnit->m_wQuality;
}

BOOL CTMUnit::Compare(CONST CTMUnit *pTMUnit) CONST
{
	return((pTMUnit->m_szTag == m_szTag  &&  pTMUnit->m_tTimeTag == m_tTimeTag  &&  pTMUnit->m_nUnitID == m_nUnitID  &&  pTMUnit->m_nData[0].GetSize() == m_nData[0].GetSize() && !memcmp(pTMUnit->m_nData[0].GetData(), m_nData[0].GetData(), m_nData[0].GetSize()) && pTMUnit->m_nData[1].GetSize() == m_nData[1].GetSize() && !memcmp(pTMUnit->m_nData[1].GetData(), m_nData[1].GetData(), m_nData[1].GetSize()) && pTMUnit->m_wQuality == m_wQuality) ? TRUE : FALSE);
}

BOOL CTMUnit::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	sData.cbData = (INT)(m_nData[0].GetSize()*sizeof(BYTE));
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbTag + sData.cbData + (INT)m_nData[1].GetSize()*sizeof(BYTE))), sData.tTimeTag = m_tTimeTag.GetTime(), sData.nUnitID = m_nUnitID, sData.wQuality = m_wQuality; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szTag, sData.cbTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTag), m_nData[0].GetData(), sData.cbData);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbData), m_nData[1].GetData(), m_nData[1].GetSize()*sizeof(BYTE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTMUnit::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize >= (INT) sizeof(DATA) + sData.cbTag + sData.cbData && sData.cbTag > 0 && sData.cbData >= 0; )
	{
		for (m_nData[0].SetSize(sData.cbData), m_nData[1].SetSize(sData.cbSize - sizeof(DATA) - sData.cbTag - sData.cbData); m_nData[0].GetSize() == sData.cbData && m_nData[1].GetSize() == sData.cbSize - sizeof(DATA) - sData.cbTag - sData.cbData; )
		{
			CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbTag));
			CopyMemory(m_nData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbTag), sData.cbData);
			CopyMemory(m_nData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbData), m_nData[1].GetSize()*sizeof(BYTE));
			m_tTimeTag = sData.tTimeTag;
			m_nUnitID = sData.nUnitID;
			m_wQuality = sData.wQuality;
			m_szTag.ReleaseBuffer();
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CTMUnit::Extract(CONST CByteArray &nData, INT nBytePos, BYTE &nValue) CONST
{
	if (nData.GetSize() > nBytePos  &&  nBytePos >= 0)
	{
		nValue = nData.GetAt(nBytePos);
		return TRUE;
	}
	return FALSE;
}
BOOL CTMUnit::Extract(CONST CByteArray &nData, INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue, BOOL bLittleEndian) CONST
{
	INT  nByte;
	INT  nBytes;
	ULONGLONG  nRawValue;

	if (nData.GetSize() > nBytePos + (nBitPos + nLength - 1) / 8 && nBytePos >= 0 && nBitPos >= 0 && nLength > 0 && nBitPos + nLength <= (INT)8 * sizeof(nValue))
	{
		for (nByte = 0, nBytes = sizeof(nValue), nValue = 0; nByte < nBytes; nByte++)
		{
			if (nData.GetSize() > nBytePos + nByte) nValue += nData.GetAt(nBytePos + nByte);
			if (nByte < nBytes - 1) nValue <<= 8;
		}
		for (nValue = (nValue >> (8 * sizeof(nValue) - nBitPos - nLength)) & (((ULONGLONG)-1) >> (8 * sizeof(nValue) - nLength)); nLength > 8 && bLittleEndian; )
		{
			for (nByte = 0, nBytes = (nLength + 7) / 8, nRawValue = nValue, nValue = 0; nByte < nBytes; nByte++)
			{
				nValue += ((nRawValue >> (8 * nByte)) & 0xFF) << (8 * (nBytes - nByte - 1));
				continue;
			}
			break;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTMUnits

CTMUnits::CTMUnits() : CPtrArray()
{
	return;
}

CTMUnits::~CTMUnits()
{
	RemoveAll();
}

INT CTMUnits::Add(CTMUnit *pTMUnit)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTMUnit->GetTimeTag(), TRUE)) >= 0) InsertAt(nIndex, pTMUnit, 1);
	return nIndex;
}

INT CTMUnits::Find(CONST CTimeTag &tTimeTag) CONST
{
	return FindIndex(tTimeTag);
}

CTMUnit *CTMUnits::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMUnit *)CPtrArray::GetAt(nIndex) : (CTMUnit *)NULL);
}

CTMUnit *CTMUnits::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMUnit *)CPtrArray::GetAt(nIndex) : (CTMUnit *)NULL);
}

VOID CTMUnits::RemoveAll()
{
	INT  nUnit;
	INT  nUnits;
	CTMUnit  *pTMUnit;

	for (nUnit = 0, nUnits = (INT)GetSize(); nUnit < nUnits; nUnit++)
	{
		if ((pTMUnit = GetAt(nUnit))) delete pTMUnit;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTMUnits::Copy(CONST CTMUnits *pTMUnits)
{
	INT  nUnit;
	INT  nUnits;
	CTMUnit  *pTMUnit;

	for (nUnit = 0, nUnits = (INT)pTMUnits->GetSize(), RemoveAll(); nUnit < nUnits; nUnit++)
	{
		if ((pTMUnit = new CTMUnit) != (CTMUnit *)NULL)
		{
			pTMUnit->Copy(pTMUnits->GetAt(nUnit));
			InsertAt(nUnit, pTMUnit, 1);
			continue;
		}
		break;
	}
	return((nUnit == nUnits) ? TRUE : FALSE);
}

BOOL CTMUnits::Compare(CONST CTMUnits *pTMUnits) CONST
{
	INT  nUnit;
	INT  nUnits;

	for (nUnit = 0, nUnits = (pTMUnits->GetSize() == GetSize()) ? (INT)GetSize() : -1; nUnit < nUnits; nUnit++)
	{
		if (!pTMUnits->GetAt(nUnit)->Compare(GetAt(nUnit))) break;
		continue;
	}
	return((nUnit == nUnits) ? TRUE : FALSE);
}

BOOL CTMUnits::Map(CByteArray &nInfo) CONST
{
	INT  nUnit;
	INT  nUnits;
	CTMUnit  *pTMUnit;
	CByteArray  nUnitData;

	for (nUnit = 0, nUnits = (INT)GetSize(), nInfo.RemoveAll(); nUnit < nUnits; nUnit++)
	{
		if ((pTMUnit = GetAt(nUnit)) && pTMUnit->Map(nUnitData) && nInfo.Append(nUnitData) >= 0) continue;
		break;
	}
	return((nUnit == nUnits) ? TRUE : FALSE);
}

BOOL CTMUnits::Unmap(CONST CByteArray &nInfo)
{
	INT  cbUnit;
	INT  cbUnits;
	CTMUnit  *pTMUnit;
	CByteArray  nUnitData;

	for (cbUnits = 0, RemoveAll(); cbUnits < nInfo.GetSize(); cbUnits += cbUnit)
	{
		for (CopyMemory(&cbUnit, nInfo.GetData() + cbUnits, sizeof(cbUnit)), nUnitData.SetSize(max(min(cbUnit, nInfo.GetSize() - cbUnits), 0)); nUnitData.GetSize() >= 0; )
		{
			CopyMemory(nUnitData.GetData(), nInfo.GetData() + cbUnits, nUnitData.GetSize());
			break;
		}
		if ((pTMUnit = new CTMUnit))
		{
			if (pTMUnit->Unmap(nUnitData))
			{
				if (Add(pTMUnit) >= 0) continue;
				delete pTMUnit;
				break;
			}
			delete pTMUnit;
		}
		break;
	}
	return((cbUnits == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTMUnits::FindIndex(CONST CTimeTag &tTimeTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTMUnit  *pTMUnit;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pTMUnit = GetAt(nIndex[0]))) ? ((nIndex[1] = ((!bInsert  &&  pTMUnit->GetTimeTag() < tTimeTag) || (bInsert  &&  pTMUnit->GetTimeTag() <= tTimeTag))) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert  &&  nIndex[0] >= 0 && nIndex[0] < GetSize()) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && tTimeTag > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTMUnitCache

CTMUnitCache::CTMUnitCache() : CTMUnits()
{
	return;
}

CTMUnitCache::~CTMUnitCache()
{
	RemoveAll();
}

INT CTMUnitCache::Add(CTMUnit *pTMUnit)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTMUnit->GetTag(), TRUE)) >= 0)
	{
		pTMUnit->SetRetention(GetRetention(pTMUnit->GetTag()));
		InsertAt(nIndex, pTMUnit, 1);
	}
	return nIndex;
}

INT CTMUnitCache::Find(LPCTSTR pszTag) CONST
{
	return FindIndex(pszTag);
}

VOID CTMUnitCache::SetRetention(LPCTSTR pszTag, CONST CTimeSpan &tRetention)
{
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	CString  szTag;
	CStringTools  cStringTools;

	for (nIndex = 0, nCount = (INT)m_szRetentions.GetSize(); nIndex < nCount; nIndex++)
	{
		if (!lstrcmp((szTag = ((nPos = m_szRetentions.GetAt(nIndex).Find(TAB)) >= 0) ? m_szRetentions.GetAt(nIndex).Left(nPos) : m_szRetentions.GetAt(nIndex)), pszTag))
		{
			m_szRetentions.SetAt(nIndex, pszTag + (TAB + cStringTools.ConvertLongIntToString(tRetention.GetTotalSeconds())));
			break;
		}
		if (szTag.Compare(pszTag) > 0)
		{
			m_szRetentions.InsertAt(nIndex, pszTag + (TAB + cStringTools.ConvertLongIntToString(tRetention.GetTotalSeconds())));
			break;
		}
	}
	for (; nIndex == nCount; )
	{
		m_szRetentions.Add(pszTag + (TAB + cStringTools.ConvertLongIntToString(tRetention.GetTotalSeconds())));
		break;
	}
}

CTimeSpan CTMUnitCache::GetRetention(LPCTSTR pszTag) CONST
{
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	CString  szTag;

	for (nIndex = 0, nCount = (INT)m_szRetentions.GetSize(); nIndex < nCount; nIndex++)
	{
		if (!lstrcmp((szTag = ((nPos = m_szRetentions.GetAt(nIndex).Find(TAB)) >= 0) ? m_szRetentions.GetAt(nIndex).Left(nPos) : m_szRetentions.GetAt(nIndex)), pszTag)) return _ttoi64(m_szRetentions.GetAt(nIndex).Mid(nPos + 1));
		continue;
	}
	return((lstrlen(pszTag) > 0 && nCount > 0) ? GetRetention(EMPTYSTRING) : -1);
}

VOID CTMUnitCache::RemoveAllRetentions()
{
	m_szRetentions.RemoveAll();
}

BOOL CTMUnitCache::Copy(CONST CTMUnitCache *pCache)
{
	INT  nTMUnit;
	INT  nTMUnits;
	CTMUnit  *pTMUnit;

	for (nTMUnit = 0, nTMUnits = (INT)pCache->GetSize(), RemoveAll(); nTMUnit < nTMUnits; nTMUnit++)
	{
		if ((pTMUnit = new CTMUnit) != (CTMUnit *)NULL)
		{
			pTMUnit->Copy(pCache->GetAt(nTMUnit));
			InsertAt(nTMUnit, pTMUnit, 1);
			continue;
		}
		break;
	}
	return((nTMUnit == nTMUnits) ? TRUE : FALSE);
}

BOOL CTMUnitCache::Compare(CONST CTMUnitCache *pCache) CONST
{
	INT  nTMUnit;
	INT  nTMUnits;

	for (nTMUnit = 0, nTMUnits = (pCache->GetSize() == GetSize()) ? (INT)GetSize() : -1; nTMUnit < nTMUnits; nTMUnit++)
	{
		if (!pCache->GetAt(nTMUnit)->Compare(GetAt(nTMUnit))) break;
		continue;
	}
	return((nTMUnit == nTMUnits) ? TRUE : FALSE);
}

BOOL CTMUnitCache::Map(CByteArray &nInfo, CONST CTimeTag &tRetention) CONST
{
	INT  nTMUnit;
	INT  nTMUnits;
	CTMUnit  *pTMUnit;
	CByteArray  nTMUnitData;

	for (nTMUnit = 0, nTMUnits = (INT)GetSize(), nInfo.RemoveAll(); nTMUnit < nTMUnits; nTMUnit++)
	{
		if ((pTMUnit = GetAt(nTMUnit)) && ((pTMUnit->GetRetention() != (TIMEKEY)-1 && tRetention != (TIMETAG)-1 && (!pTMUnit->GetRetention().GetTotalSeconds() || tRetention.GetTimeInSeconds() - pTMUnit->GetTimeTag().GetTimeInSeconds() > pTMUnit->GetRetention().GetTotalSeconds())) || (pTMUnit->Map(nTMUnitData) && nInfo.Append(nTMUnitData) >= 0))) continue;
		break;
	}
	return((nTMUnit == nTMUnits) ? TRUE : FALSE);
}

BOOL CTMUnitCache::Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention)
{
	INT  nIndex;
	INT  cbTMUnit;
	INT  cbTMUnits;
	CTMUnit  *pTMUnit;
	CByteArray  nTMUnitData;

	for (cbTMUnits = 0, RemoveAll(); cbTMUnits < nInfo.GetSize(); cbTMUnits += cbTMUnit)
	{
		for (CopyMemory(&cbTMUnit, nInfo.GetData() + cbTMUnits, sizeof(cbTMUnit)), nTMUnitData.SetSize(max(min(cbTMUnit, nInfo.GetSize() - cbTMUnits), 0)); nTMUnitData.GetSize() >= 0; )
		{
			CopyMemory(nTMUnitData.GetData(), nInfo.GetData() + cbTMUnits, nTMUnitData.GetSize());
			break;
		}
		if ((pTMUnit = new CTMUnit))
		{
			if (pTMUnit->Unmap(nTMUnitData))
			{
				if (pTMUnit->GetRetention() == (TIMEKEY)-1 || tRetention == (TIMETAG)-1 || tRetention.GetTimeInSeconds() - pTMUnit->GetTimeTag().GetTimeInSeconds() <= pTMUnit->GetRetention().GetTotalSeconds())
				{
					if ((nIndex = FindIndex(pTMUnit->GetTag())) >= 0)
					{
						if (pTMUnit->GetTimeTag() < GetAt(nIndex)->GetTimeTag())
						{
							delete pTMUnit;
							continue;
						}
						delete GetAt(nIndex);
						RemoveAt(nIndex);
					}
					if (Add(pTMUnit) >= 0) continue;
					delete pTMUnit;
					break;
				}
				delete pTMUnit;
				continue;
			}
			delete pTMUnit;
		}
		break;
	}
	return((cbTMUnits == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTMUnitCache::FindIndex(LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTMUnit  *pTMUnit;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pTMUnit = GetAt(nIndex[0]))) ? ((nIndex[1] = (pTMUnit->GetTag() <= pszTag)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pTMUnit = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pTMUnit->GetTag() == pszTag) || (bInsert && (((pTMUnit = GetAt(max(nIndex[0] - 1, 0))) && pTMUnit->GetTag() != pszTag && (pTMUnit = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pTMUnit->GetTag() != pszTag) || !GetSize()))) && lstrlen(pszTag) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTMPacket

IMPLEMENT_DYNCREATE(CTMPacket, CTMUnit)

CTMPacket::CTMPacket() : CTMUnit()
{
	m_nTMTypePos[0] = 0;
	m_nTMTypePos[1] = 0;
	m_nTMTypePos[2] = 0;
	m_nTMIDPos[0] = 0;
	m_nTMIDPos[1] = 0;
	m_nTMIDPos[2] = 0;
	m_n3DiscPos[0] = 0;
	m_n3DiscPos[1] = 0;
	m_n3DiscPos[2] = 0;
	m_nTimestampPos[0] = 0;
	m_nTimestampPos[1] = 0;
	m_nTimestampPos[2] = 0;
	m_nVirtualChannel = -1;
}
CTMPacket::CTMPacket(LPCTSTR pszTag) : CTMUnit()
{
	m_szTag = pszTag;
	m_nTMTypePos[0] = 0;
	m_nTMTypePos[1] = 0;
	m_nTMTypePos[2] = 0;
	m_nTMIDPos[0] = 0;
	m_nTMIDPos[1] = 0;
	m_nTMIDPos[2] = 0;
	m_n3DiscPos[0] = 0;
	m_n3DiscPos[1] = 0;
	m_n3DiscPos[2] = 0;
	m_nTimestampPos[0] = 0;
	m_nTimestampPos[1] = 0;
	m_nTimestampPos[2] = 0;
	m_nVirtualChannel = -1;
}

VOID CTMPacket::SetTMTypePosition(INT nByte, INT nBit, INT nLength)
{
	m_nTMTypePos[0] = nByte;
	m_nTMTypePos[1] = nBit;
	m_nTMTypePos[2] = nLength;
}

BOOL CTMPacket::GetTMTypePosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	nByte = m_nTMTypePos[0];
	nBit = m_nTMTypePos[1];
	nLength = m_nTMTypePos[2];
	return((nLength != 0) ? TRUE : FALSE);
}

VOID CTMPacket::SetTMIDPosition(INT nByte, INT nBit, INT nLength)
{
	m_nTMIDPos[0] = nByte;
	m_nTMIDPos[1] = nBit;
	m_nTMIDPos[2] = nLength;
}

BOOL CTMPacket::GetTMIDPosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	nByte = m_nTMIDPos[0];
	nBit = m_nTMIDPos[1];
	nLength = m_nTMIDPos[2];
	return((nLength != 0) ? TRUE : FALSE);
}

VOID CTMPacket::Set3DiscPosition(INT nByte, INT nBit, INT nLength)
{
	m_n3DiscPos[0] = nByte;
	m_n3DiscPos[1] = nBit;
	m_n3DiscPos[2] = nLength;
}

BOOL CTMPacket::Get3DiscPosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	nByte = m_n3DiscPos[0];
	nBit = m_n3DiscPos[1];
	nLength = m_n3DiscPos[2];
	return((nLength != 0) ? TRUE : FALSE);
}

VOID CTMPacket::SetTimestampPosition(INT nByte, INT nBit, INT nLength)
{
	m_nTimestampPos[0] = nByte;
	m_nTimestampPos[1] = nBit;
	m_nTimestampPos[2] = nLength;
}

BOOL CTMPacket::GetTimestampPosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	nByte = m_nTimestampPos[0];
	nBit = m_nTimestampPos[1];
	nLength = m_nTimestampPos[2];
	return((nLength != 0) ? TRUE : FALSE);
}

VOID CTMPacket::SetVirtualChannel(INT nChannel)
{
	m_nVirtualChannel = nChannel;
}

INT CTMPacket::GetVirtualChannel() CONST
{
	return((HasHeader() && IsValid()) ? m_nVirtualChannel : -1);
}

INT CTMPacket::GetType() CONST
{
	ULONGLONG  nType;

	return((Extract(m_nData[0], 0, 3, 1, nType)) ? (INT)nType : -1);
}

INT CTMPacket::GetAPID() CONST
{
	ULONGLONG  nAPID;

	return((Extract(m_nData[0], 0, 5, 11, nAPID)) ? (INT)nAPID : -1);
}

INT CTMPacket::GetTMType() CONST
{
	ULONGLONG  nTMType;

	return((Extract(m_nData[0], TMPACKET_HEADER_SIZE + m_nTMTypePos[0], m_nTMTypePos[1], m_nTMTypePos[2], nTMType) && m_nTMTypePos[2] > 0 && IsValid()) ? (INT)nTMType : -1);
}

INT CTMPacket::GetTMID() CONST
{
	ULONGLONG  nTMID;

	return((Extract(m_nData[0], TMPACKET_HEADER_SIZE + m_nTMIDPos[0], m_nTMIDPos[1], m_nTMIDPos[2], nTMID) && m_nTMIDPos[2] > 0 && IsValid()) ? (INT)nTMID : -1);
}

INT CTMPacket::Get3Disc() CONST
{
	ULONGLONG  n3Disc;

	return((Extract(m_nData[0], TMPACKET_HEADER_SIZE + m_n3DiscPos[0], m_n3DiscPos[1], m_n3DiscPos[2], n3Disc) && m_n3DiscPos[2] > 0 && IsValid()) ? (INT)n3Disc : -1);
}

INT CTMPacket::GetVersion() CONST
{
	ULONGLONG  nVersion;

	return((Extract(m_nData[0], 0, 0, 3, nVersion)) ? (INT)nVersion : -1);
}

INT CTMPacket::GetSequenceFlags() CONST
{
	ULONGLONG  nFlags;

	return((Extract(m_nData[0], 2, 0, 2, nFlags)) ? (INT)nFlags : -1);
}

INT CTMPacket::GetSequenceCount() CONST
{
	ULONGLONG  nCount;

	return((Extract(m_nData[0], 2, 2, 14, nCount)) ? (INT)nCount : -1);
}

INT CTMPacket::GetDataFieldLength() CONST
{
	ULONGLONG  nLength;

	return((Extract(m_nData[0], 4, 0, 16, nLength)) ? (INT)nLength : -1);
}

UINT CTMPacket::GetTimestamp() CONST
{
	ULONGLONG  nTimestamp;

	return((Extract(m_nData[0], TMPACKET_HEADER_SIZE + m_nTimestampPos[0], m_nTimestampPos[1], m_nTimestampPos[2], nTimestamp) && m_nTimestampPos[2] > 0 && IsValid()) ? (UINT)nTimestamp : -1);
}

BOOL CTMPacket::HasHeader() CONST
{
	return((m_nData[0].GetSize() >= TMPACKET_HEADER_SIZE) ? TRUE : FALSE);
}

BOOL CTMPacket::HasDataFieldHeader() CONST
{
	ULONGLONG  bHeader;

	return((Extract(m_nData[0], 0, 4, 1, bHeader)) ? (BOOL)bHeader : FALSE);
}

BOOL CTMPacket::HasTimestamp() CONST
{
	ULONGLONG  nTimestamp;

	return((Extract(m_nData[0], TMPACKET_HEADER_SIZE + m_nTimestampPos[0], m_nTimestampPos[1], m_nTimestampPos[2], nTimestamp)) ? IsValid() : FALSE);
}

INT CTMPacket::GetData(CByteArray &nData, BOOL bExtra) CONST
{
	nData.Copy(m_nData[(bExtra) ? TRUE : FALSE]);
	return((INT)nData.GetSize());
}
BOOL CTMPacket::GetData(INT nBytePos, BYTE &nValue) CONST
{
	return Extract(m_nData[0], TMPACKET_HEADER_SIZE + nBytePos, nValue);
}
BOOL CTMPacket::GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue, BOOL bLittleEndian) CONST
{
	return Extract(m_nData[0], TMPACKET_HEADER_SIZE + nBytePos, nBitPos, nLength, nValue, bLittleEndian);
}

VOID CTMPacket::Reset()
{
	m_nTMTypePos[0] = 0;
	m_nTMTypePos[1] = 0;
	m_nTMTypePos[2] = 0;
	m_nTMIDPos[0] = 0;
	m_nTMIDPos[1] = 0;
	m_nTMIDPos[2] = 0;
	m_n3DiscPos[0] = 0;
	m_n3DiscPos[1] = 0;
	m_n3DiscPos[2] = 0;
	m_nTimestampPos[0] = 0;
	m_nTimestampPos[1] = 0;
	m_nTimestampPos[2] = 0;
	m_nVirtualChannel = -1;
	CTMUnit::Reset();
}

VOID CTMPacket::Copy(CONST CTMUnit *pTMUnit)
{
	CTMPacket  *pTMPacket;

	if ((pTMPacket = (pTMUnit->IsKindOf(RUNTIME_CLASS(CTMPacket))) ? (CTMPacket *)pTMUnit : (CTMPacket *)NULL))
	{
		m_nTMTypePos[0] = pTMPacket->m_nTMTypePos[0];
		m_nTMTypePos[1] = pTMPacket->m_nTMTypePos[1];
		m_nTMTypePos[2] = pTMPacket->m_nTMTypePos[2];
		m_nTMIDPos[0] = pTMPacket->m_nTMIDPos[0];
		m_nTMIDPos[1] = pTMPacket->m_nTMIDPos[1];
		m_nTMIDPos[2] = pTMPacket->m_nTMIDPos[2];
		m_n3DiscPos[0] = pTMPacket->m_n3DiscPos[0];
		m_n3DiscPos[1] = pTMPacket->m_n3DiscPos[1];
		m_n3DiscPos[2] = pTMPacket->m_n3DiscPos[2];
		m_nTimestampPos[0] = pTMPacket->m_nTimestampPos[0];
		m_nTimestampPos[1] = pTMPacket->m_nTimestampPos[1];
		m_nTimestampPos[2] = pTMPacket->m_nTimestampPos[2];
		m_nVirtualChannel = pTMPacket->m_nVirtualChannel;
	}
	CTMUnit::Copy(pTMUnit);
}

BOOL CTMPacket::Compare(CONST CTMUnit *pTMUnit) CONST
{
	CTMPacket  *pTMPacket;

	return(((pTMPacket = (pTMUnit->IsKindOf(RUNTIME_CLASS(CTMPacket))) ? (CTMPacket *)pTMUnit : (CTMPacket *)NULL)) ? ((pTMPacket->m_nTMTypePos[0] == m_nTMTypePos[0] && pTMPacket->m_nTMTypePos[1] == m_nTMTypePos[1] && pTMPacket->m_nTMTypePos[2] == m_nTMTypePos[2] && pTMPacket->m_nTMIDPos[0] == m_nTMIDPos[0] && pTMPacket->m_nTMIDPos[1] == m_nTMIDPos[1] && pTMPacket->m_nTMIDPos[2] == m_nTMIDPos[2] && pTMPacket->m_n3DiscPos[0] == m_n3DiscPos[0] && pTMPacket->m_n3DiscPos[1] == m_n3DiscPos[1] && pTMPacket->m_n3DiscPos[2] == m_n3DiscPos[2] && pTMPacket->m_nTimestampPos[0] == m_nTimestampPos[0] && pTMPacket->m_nTimestampPos[1] == m_nTimestampPos[1] && pTMPacket->m_nTimestampPos[2] == m_nTimestampPos[2] && (pTMPacket->m_nVirtualChannel == m_nVirtualChannel || pTMPacket->m_nVirtualChannel == -1 || m_nVirtualChannel == -1)) ? CTMUnit::Compare(pTMUnit) : FALSE) : CTMUnit::Compare(pTMUnit));
}


/////////////////////////////////////////////////////////////////////////////
// CTMTransferUnit

IMPLEMENT_DYNCREATE(CTMTransferUnit, CTMUnit)

CTMTransferUnit::CTMTransferUnit() : CTMUnit()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTMTransferUnits

CTMTransferUnits::CTMTransferUnits() : CPtrArray()
{
	return;
}

CTMTransferUnits::~CTMTransferUnits()
{
	RemoveAll();
}

INT CTMTransferUnits::Add(CTMTransferUnit *pTMTransferUnit)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTMTransferUnit->GetTimeTag(), TRUE)) >= 0) InsertAt(nIndex, pTMTransferUnit, 1);
	return nIndex;
}

INT CTMTransferUnits::Find(LPCTSTR pszTag, INT nIndex) CONST
{
	INT  nCount;
	CTMTransferUnit  *pTMTransferUnit;

	for (nIndex = max(nIndex, 0), nCount = (INT)GetSize(); nIndex < nCount; nIndex++)
	{
		if ((pTMTransferUnit = GetAt(nIndex)) && pTMTransferUnit->GetTag() == pszTag) break;
		continue;
	}
	return((nIndex < nCount) ? nIndex : -1);
}
INT CTMTransferUnits::Find(CONST CTimeTag &tTimeTag) CONST
{
	return FindIndex(tTimeTag);
}

CTMTransferUnit *CTMTransferUnits::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMTransferUnit *)CPtrArray::GetAt(nIndex) : (CTMTransferUnit *)NULL);
}

CTMTransferUnit *CTMTransferUnits::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMTransferUnit *)CPtrArray::GetAt(nIndex) : (CTMTransferUnit *)NULL);
}

VOID CTMTransferUnits::RemoveAll()
{
	INT  nTransferUnit;
	INT  nTransferUnits;
	CTMTransferUnit  *pTMTransferUnit;

	for (nTransferUnit = 0, nTransferUnits = (INT)GetSize(); nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if ((pTMTransferUnit = GetAt(nTransferUnit))) delete pTMTransferUnit;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTMTransferUnits::Copy(CONST CTMTransferUnits *pTMTransferUnits)
{
	INT  nTransferUnit;
	INT  nTransferUnits;
	CTMTransferUnit  *pTMTransferUnit;

	for (nTransferUnit = 0, nTransferUnits = (INT)pTMTransferUnits->GetSize(), RemoveAll(); nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if ((pTMTransferUnit = new CTMTransferUnit) != (CTMTransferUnit *)NULL)
		{
			pTMTransferUnit->Copy(pTMTransferUnits->GetAt(nTransferUnit));
			InsertAt(nTransferUnit, pTMTransferUnit, 1);
			continue;
		}
		break;
	}
	return((nTransferUnit == nTransferUnits) ? TRUE : FALSE);
}

BOOL CTMTransferUnits::Compare(CONST CTMTransferUnits *pTMTransferUnits) CONST
{
	INT  nTransferUnit;
	INT  nTransferUnits;

	for (nTransferUnit = 0, nTransferUnits = (pTMTransferUnits->GetSize() == GetSize()) ? (INT)GetSize() : -1; nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if (!pTMTransferUnits->GetAt(nTransferUnit)->Compare(GetAt(nTransferUnit))) break;
		continue;
	}
	return((nTransferUnit == nTransferUnits) ? TRUE : FALSE);
}

BOOL CTMTransferUnits::Map(CByteArray &nInfo) CONST
{
	INT  nTransferUnit;
	INT  nTransferUnits;
	CByteArray  nTransferUnitData;
	CTMTransferUnit  *pTMTransferUnit;

	for (nTransferUnit = 0, nTransferUnits = (INT)GetSize(), nInfo.RemoveAll(); nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if ((pTMTransferUnit = GetAt(nTransferUnit)) && pTMTransferUnit->Map(nTransferUnitData) && nInfo.Append(nTransferUnitData) >= 0) continue;
		break;
	}
	return((nTransferUnit == nTransferUnits) ? TRUE : FALSE);
}

BOOL CTMTransferUnits::Unmap(CONST CByteArray &nInfo)
{
	INT  cbTransferUnit;
	INT  cbTransferUnits;
	CByteArray  nTransferUnitData;
	CTMTransferUnit  *pTMTransferUnit;

	for (cbTransferUnits = 0, RemoveAll(); cbTransferUnits < nInfo.GetSize(); cbTransferUnits += cbTransferUnit)
	{
		for (CopyMemory(&cbTransferUnit, nInfo.GetData() + cbTransferUnits, sizeof(cbTransferUnit)), nTransferUnitData.SetSize(max(min(cbTransferUnit, nInfo.GetSize() - cbTransferUnits), 0)); nTransferUnitData.GetSize() >= 0; )
		{
			CopyMemory(nTransferUnitData.GetData(), nInfo.GetData() + cbTransferUnits, nTransferUnitData.GetSize());
			break;
		}
		if ((pTMTransferUnit = new CTMTransferUnit))
		{
			if (pTMTransferUnit->Unmap(nTransferUnitData))
			{
				if (Add(pTMTransferUnit) >= 0) continue;
				delete pTMTransferUnit;
				break;
			}
			delete pTMTransferUnit;
		}
		break;
	}
	return((cbTransferUnits == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTMTransferUnits::FindIndex(CONST CTimeTag &tTimeTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTMTransferUnit  *pTMTransferUnit;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pTMTransferUnit = GetAt(nIndex[0]))) ? ((nIndex[1] = ((!bInsert  &&  pTMTransferUnit->GetTimeTag() < tTimeTag) || (bInsert  &&  pTMTransferUnit->GetTimeTag() <= tTimeTag))) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert  &&  nIndex[0] >= 0 && nIndex[0] < GetSize()) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && tTimeTag > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTMTransferFrame

IMPLEMENT_DYNCREATE(CTMTransferFrame, CTMTransferUnit)

CTMTransferFrame::CTMTransferFrame() : CTMTransferUnit()
{
	return;
}

UINT CTMTransferFrame::GetSyncMarker() CONST
{
	ULONGLONG  nSyncMarker;

	return((Extract(m_nData[0], 0, 0, 8 * TMTRANSFERFRAME_SYNCMARKER_SIZE, nSyncMarker)) ? (UINT)nSyncMarker : (UINT)-1);
}

BYTE CTMTransferFrame::GetVersion() CONST
{
	ULONGLONG  nVersion;

	return((Extract(m_nData[0], 4, 0, 2, nVersion)) ? (BYTE)nVersion : (BYTE)-1);
}

UINT CTMTransferFrame::GetSpacecraftID() CONST
{
	ULONGLONG  nID;

	return((Extract(m_nData[0], 4, 2, 10, nID)) ? (UINT)nID : (UINT)-1);
}

BYTE CTMTransferFrame::GetVirtualChannel() CONST
{
	ULONGLONG  nChannel;

	return((Extract(m_nData[0], 5, 4, 3, nChannel)) ? (BYTE)nChannel : (BYTE)-1);
}

BOOL CTMTransferFrame::GetOperationalControlFieldFlag() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 5, 7, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BYTE CTMTransferFrame::GetMasterChannelFrameCounter() CONST
{
	BYTE  nCounter;

	return((Extract(m_nData[0], 6, nCounter)) ? nCounter : (BYTE)-1);
}

UINT CTMTransferFrame::GetVirtualChannelFrameCounter() CONST
{
	BYTE  nCounter;

	return((Extract(m_nData[0], 7, nCounter)) ? nCounter : (UINT)-1);
}

UINT CTMTransferFrame::GetFirstHeaderPointer() CONST
{
	ULONGLONG  nPointer;

	return((Extract(m_nData[0], 8, 5, 11, nPointer)) ? (UINT)nPointer : (UINT)-1);
}

BOOL CTMTransferFrame::GetSynchronizationFlag() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 8, 1, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BYTE CTMTransferFrame::GetSegmentationFlag() CONST
{
	ULONGLONG  nFlag;

	return((Extract(m_nData[0], 8, 3, 2, nFlag)) ? (BYTE)nFlag : (BYTE)-1);
}

BOOL CTMTransferFrame::GetPacketOrderFlag() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 8, 2, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BOOL CTMTransferFrame::GetSecondaryHeaderFlag() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 8, 0, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BYTE CTMTransferFrame::GetSecondaryHeaderVersion() CONST
{
	ULONGLONG  nVersion;

	return((GetSecondaryHeaderFlag() && Extract(m_nData[0], 10, 0, 2, nVersion)) ? (BYTE)nVersion : (BYTE)-1);
}

BYTE CTMTransferFrame::GetSecondaryHeaderLength() CONST
{
	ULONGLONG  nLength;

	return((GetSecondaryHeaderFlag() && Extract(m_nData[0], 10, 2, 6, nLength)) ? (BYTE)nLength : (BYTE)-1);
}

UINT CTMTransferFrame::GetSecondaryHeaderData() CONST
{
	ULONGLONG  nCount;

	return((GetSecondaryHeaderFlag() && Extract(m_nData[0], 11, 0, 24, nCount)) ? (UINT)nCount : (UINT)-1);
}

BOOL CTMTransferFrame::GetFrameData(CTMPacket *pTMPacket) CONST
{
	CByteArray  nData;

	for (pTMPacket->Reset(); GetFrameData(nData) > 0; )
	{
		pTMPacket->CTMUnit::Copy(this);
		pTMPacket->SetData(nData);
		return TRUE;
	}
	return FALSE;
}
INT CTMTransferFrame::GetFrameData(CByteArray &nData) CONST
{
	UINT  nOffset;
	ULONGLONG  nValue;

	for (nData.RemoveAll(); Extract(m_nData[0], TMTRANSFERFRAME_SYNCMARKER_SIZE + TMTRANSFERFRAME_PRIMARYHEADER_SIZE + GetSecondaryHeaderFlag()*TMTRANSFERFRAME_SECONDARYHEADER_SIZE + 4, 0, 16, nValue) && nValue > TMPACKET_HEADER_SIZE; )
	{
		for (nData.Copy(m_nData[0]), nData.RemoveAt(0, TMTRANSFERFRAME_SYNCMARKER_SIZE + TMTRANSFERFRAME_PRIMARYHEADER_SIZE + GetSecondaryHeaderFlag()*TMTRANSFERFRAME_SECONDARYHEADER_SIZE); TMPACKET_HEADER_SIZE + nValue < (ULONGLONG)nData.GetSize(); )
		{
			nData.RemoveAt((INT_PTR)(TMPACKET_HEADER_SIZE + nValue + 1), (INT_PTR)(nData.GetSize() - TMPACKET_HEADER_SIZE - nValue - 1));
			break;
		}
		if ((nOffset = GetFirstHeaderPointer()) > 0 && nOffset < (UINT)nData.GetSize())
		{
			nData.RemoveAt(0, nOffset);
			nOffset = 0;
		}
		if (nOffset > 0) nData.RemoveAll();
		break;
	}
	return((INT)nData.GetSize());
}

INT CTMTransferFrame::GetFrameTrailer(CByteArray &nData) CONST
{
	ULONGLONG  nValue;

	for (nData.RemoveAll(); Extract(m_nData[0], TMTRANSFERFRAME_SYNCMARKER_SIZE + TMTRANSFERFRAME_PRIMARYHEADER_SIZE + GetSecondaryHeaderFlag()*TMTRANSFERFRAME_SECONDARYHEADER_SIZE + 4, 0, 16, nValue) && nValue > TMPACKET_HEADER_SIZE; )
	{
		for (nData.Copy(m_nData[0]), nData.RemoveAt(0, TMTRANSFERFRAME_SYNCMARKER_SIZE + TMTRANSFERFRAME_PRIMARYHEADER_SIZE + GetSecondaryHeaderFlag()*TMTRANSFERFRAME_SECONDARYHEADER_SIZE); TMPACKET_HEADER_SIZE + nValue < (ULONGLONG)nData.GetSize(); )
		{
			nData.RemoveAt(0, (INT_PTR)(TMPACKET_HEADER_SIZE + nValue + 1));
			return((INT)nData.GetSize());
		}
		nData.RemoveAll();
		break;
	}
	return((INT)nData.GetSize());
}


/////////////////////////////////////////////////////////////////////////////
// CTCUnit

IMPLEMENT_DYNCREATE(CTCUnit, CObject)

CTCUnit::CTCUnit() : CObject()
{
	m_tTimeTag = 0;
}
CTCUnit::CTCUnit(LPCTSTR pszTag) : CObject()
{
	m_szTag = pszTag;
	m_tTimeTag = 0;
}

VOID CTCUnit::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CTCUnit::GetTag() CONST
{
	return m_szTag;
}

VOID CTCUnit::SetTimeTag(CONST CTimeTag &tTimeTag)
{
	m_tTimeTag = tTimeTag;
}

CTimeTag CTCUnit::GetTimeTag() CONST
{
	return m_tTimeTag;
}

VOID CTCUnit::SetSize(INT nSize, BOOL bReset)
{
	for (m_nData[0].SetSize(nSize); bReset; )
	{
		ZeroMemory(m_nData[0].GetData(), m_nData[0].GetSize());
		break;
	}
}

INT CTCUnit::GetSize() CONST
{
	return((INT)m_nData[0].GetSize());
}

BOOL CTCUnit::SetData(CONST CByteArray &nData, BOOL bExtra)
{
	m_nData[(bExtra) ? TRUE : FALSE].Copy(nData);
	return TRUE;
}
BOOL CTCUnit::SetData(BYTE nValue, INT nBytePos)
{
	return Collect(m_nData[0], nValue, nBytePos);
}
BOOL CTCUnit::SetData(ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength)
{
	return Collect(m_nData[0], nValue, nBytePos, nBitPos, nLength);
}

INT CTCUnit::GetData(CByteArray &nData, BOOL bExtra) CONST
{
	nData.Copy(m_nData[(bExtra) ? TRUE : FALSE]);
	return((INT)nData.GetSize());
}
BOOL CTCUnit::GetData(INT nBytePos, BYTE &nValue) CONST
{
	return Extract(m_nData[0], nBytePos, nValue);
}
BOOL CTCUnit::GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST
{
	return Extract(m_nData[0], nBytePos, nBitPos, nLength, nValue);
}

BOOL CTCUnit::IsValid() CONST
{
	return((!m_szTag.IsEmpty() && m_nData[0].GetSize() + m_nData[1].GetSize() > 0) ? TRUE : FALSE);
}

VOID CTCUnit::Reset()
{
	m_szTag.Empty();
	m_tTimeTag = 0;
	m_nData[0].RemoveAll();
	m_nData[1].RemoveAll();
}

VOID CTCUnit::Copy(CONST CTCUnit *pTCUnit)
{
	m_szTag = pTCUnit->m_szTag;
	m_tTimeTag = pTCUnit->m_tTimeTag;
	m_nData[0].Copy(pTCUnit->m_nData[0]);
	m_nData[1].Copy(pTCUnit->m_nData[1]);
}

BOOL CTCUnit::Compare(CONST CTCUnit *pTCUnit) CONST
{
	return((pTCUnit->m_szTag == m_szTag  &&  pTCUnit->m_tTimeTag == m_tTimeTag  &&  pTCUnit->m_nData[0].GetSize() == m_nData[0].GetSize() && pTCUnit->m_nData[1].GetSize() == m_nData[1].GetSize() && !memcmp(pTCUnit->m_nData[0].GetData(), m_nData[0].GetData(), m_nData[0].GetSize()) && !memcmp(pTCUnit->m_nData[1].GetData(), m_nData[1].GetData(), m_nData[1].GetSize())) ? TRUE : FALSE);
}

BOOL CTCUnit::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	sData.cbData = (INT)(m_nData[0].GetSize()*sizeof(BYTE));
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbTag + sData.cbData + (INT)m_nData[1].GetSize()*sizeof(BYTE))), sData.tTimeTag = m_tTimeTag.GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szTag, sData.cbTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTag), m_nData[0].GetData(), sData.cbData);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbData), m_nData[1].GetData(), m_nData[1].GetSize()*sizeof(BYTE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCUnit::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize >= (INT) sizeof(DATA) + sData.cbTag + sData.cbData && sData.cbTag > 0 && sData.cbData >= 0; )
	{
		for (m_nData[0].SetSize(sData.cbData), m_nData[1].SetSize(sData.cbSize - sizeof(DATA) - sData.cbTag - sData.cbData); m_nData[0].GetSize() == sData.cbData && m_nData[1].GetSize() == sData.cbSize - sizeof(DATA) - sData.cbTag - sData.cbData; )
		{
			CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbTag));
			CopyMemory(m_nData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbTag), sData.cbData);
			CopyMemory(m_nData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbData), m_nData[1].GetSize()*sizeof(BYTE));
			m_tTimeTag = sData.tTimeTag;
			m_szTag.ReleaseBuffer();
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CTCUnit::Collect(CByteArray &nData, BYTE nValue, INT nBytePos) CONST
{
	if (nData.GetSize() > nBytePos  &&  nBytePos >= 0)
	{
		nData.SetAt(nBytePos, nValue);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCUnit::Collect(CByteArray &nData, ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength) CONST
{
	INT  nByte;
	INT  nBytes;
	ULONGLONG  nBitMask;
	ULONGLONG  nRawValue;

	if (nData.GetSize() > nBytePos + (nBitPos + nLength - 1) / 8 && nBytePos >= 0 && nBitPos >= 0 && nLength > 0 && nBitPos + nLength <= (INT)8 * sizeof(nValue))
	{
		for (nByte = nBytePos, nBytes = min((INT)(nByte + sizeof(nValue)), (INT)nData.GetSize()), nBitMask = 0, nBitMask = (~nBitMask >> nBitPos) & (~nBitMask << (8 * sizeof(nValue) - nLength - nBitPos)), nRawValue = (nValue << (8 * sizeof(nValue) - nLength - nBitPos)) & nBitMask, nBitMask = ~nBitMask; nByte < nBytes; nByte++)
		{
			nData.SetAt(nByte, (BYTE)((nData.GetAt(nByte) & (nBitMask >> (8 * (sizeof(nValue) - nByte + nBytePos - 1)))) | (nRawValue >> (8 * (sizeof(nValue) - nByte + nBytePos - 1)))));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCUnit::Extract(CONST CByteArray &nData, INT nBytePos, BYTE &nValue) CONST
{
	if (nData.GetSize() > nBytePos  &&  nBytePos >= 0)
	{
		nValue = nData.GetAt(nBytePos);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCUnit::Extract(CONST CByteArray &nData, INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST
{
	INT  nByte;
	INT  nBytes;

	if (nData.GetSize() > nBytePos + (nBitPos + nLength - 1) / 8 && nBytePos >= 0 && nBitPos >= 0 && nLength > 0 && nBitPos + nLength <= (INT)8 * sizeof(nValue))
	{
		for (nByte = 0, nBytes = sizeof(nValue), nValue = 0; nByte < nBytes; nByte++)
		{
			if (nData.GetSize() > nBytePos + nByte) nValue += nData.GetAt(nBytePos + nByte);
			if (nByte < nBytes - 1) nValue <<= 8;
		}
		nValue = (nValue >> (8 * sizeof(nValue) - nBitPos - nLength)) & (((ULONGLONG)-1) >> (8 * sizeof(nValue) - nLength));
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCUnits

CTCUnits::CTCUnits() : CPtrArray()
{
	return;
}

CTCUnits::~CTCUnits()
{
	RemoveAll();
}

INT CTCUnits::Add(CTCUnit *pTCUnit)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTCUnit->GetTimeTag(), TRUE)) >= 0) InsertAt(nIndex, pTCUnit, 1);
	return nIndex;
}

INT CTCUnits::Find(CONST CTimeTag &tTimeTag) CONST
{
	return FindIndex(tTimeTag);
}

CTCUnit *CTCUnits::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCUnit *)CPtrArray::GetAt(nIndex) : (CTCUnit *)NULL);
}

CTCUnit *CTCUnits::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCUnit *)CPtrArray::GetAt(nIndex) : (CTCUnit *)NULL);
}

VOID CTCUnits::RemoveAll()
{
	INT  nUnit;
	INT  nUnits;
	CTCUnit  *pTCUnit;

	for (nUnit = 0, nUnits = (INT)GetSize(); nUnit < nUnits; nUnit++)
	{
		if ((pTCUnit = GetAt(nUnit))) delete pTCUnit;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCUnits::Copy(CONST CTCUnits *pTCUnits)
{
	INT  nUnit;
	INT  nUnits;
	CTCUnit  *pTCUnit;

	for (nUnit = 0, nUnits = (INT)pTCUnits->GetSize(), RemoveAll(); nUnit < nUnits; nUnit++)
	{
		if ((pTCUnit = new CTCUnit) != (CTCUnit *)NULL)
		{
			pTCUnit->Copy(pTCUnits->GetAt(nUnit));
			InsertAt(nUnit, pTCUnit, 1);
			continue;
		}
		break;
	}
	return((nUnit == nUnits) ? TRUE : FALSE);
}

BOOL CTCUnits::Compare(CONST CTCUnits *pTCUnits) CONST
{
	INT  nUnit;
	INT  nUnits;

	for (nUnit = 0, nUnits = (pTCUnits->GetSize() == GetSize()) ? (INT)GetSize() : -1; nUnit < nUnits; nUnit++)
	{
		if (!pTCUnits->GetAt(nUnit)->Compare(GetAt(nUnit))) break;
		continue;
	}
	return((nUnit == nUnits) ? TRUE : FALSE);
}

BOOL CTCUnits::Map(CByteArray &nInfo) CONST
{
	INT  nUnit;
	INT  nUnits;
	CTCUnit  *pTCUnit;
	CByteArray  nUnitData;

	for (nUnit = 0, nUnits = (INT)GetSize(), nInfo.RemoveAll(); nUnit < nUnits; nUnit++)
	{
		if ((pTCUnit = GetAt(nUnit)) && pTCUnit->Map(nUnitData) && nInfo.Append(nUnitData) >= 0) continue;
		break;
	}
	return((nUnit == nUnits) ? TRUE : FALSE);
}

BOOL CTCUnits::Unmap(CONST CByteArray &nInfo)
{
	INT  cbUnit;
	INT  cbUnits;
	CTCUnit  *pTCUnit;
	CByteArray  nUnitData;

	for (cbUnits = 0, RemoveAll(); cbUnits < nInfo.GetSize(); cbUnits += cbUnit)
	{
		for (CopyMemory(&cbUnit, nInfo.GetData() + cbUnits, sizeof(cbUnit)), nUnitData.SetSize(max(min(cbUnit, nInfo.GetSize() - cbUnits), 0)); nUnitData.GetSize() >= 0; )
		{
			CopyMemory(nUnitData.GetData(), nInfo.GetData() + cbUnits, nUnitData.GetSize());
			break;
		}
		if ((pTCUnit = new CTCUnit))
		{
			if (pTCUnit->Unmap(nUnitData))
			{
				if (Add(pTCUnit) >= 0) continue;
				delete pTCUnit;
				break;
			}
			delete pTCUnit;
		}
		break;
	}
	return((cbUnits == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCUnits::FindIndex(CONST CTimeTag &tTimeTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTCUnit  *pTCUnit;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pTCUnit = GetAt(nIndex[0]))) ? ((nIndex[1] = ((!bInsert  &&  pTCUnit->GetTimeTag() < tTimeTag) || (bInsert  &&  pTCUnit->GetTimeTag() <= tTimeTag))) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert  &&  nIndex[0] >= 0 && nIndex[0] < GetSize()) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && tTimeTag > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCPacket

IMPLEMENT_DYNCREATE(CTCPacket, CTCUnit)

CTCPacket::CTCPacket() : CTCUnit()
{
	m_nMapID = 0;
	m_bControlFrame = FALSE;
	m_bControlSegment = FALSE;
	m_bSLEThrowEvent = FALSE;
	m_bNISThrowEvent = FALSE;
}
CTCPacket::CTCPacket(LPCTSTR pszTag) : CTCUnit()
{
	m_szTag = pszTag;
	m_nMapID = 0;
	m_bControlFrame = FALSE;
	m_bControlSegment = FALSE;
	m_bSLEThrowEvent = FALSE;
	m_bNISThrowEvent = FALSE;
}

BOOL CTCPacket::SetType(INT nType)
{
	return Collect(m_nData[0], nType, 0, 3, 1);
}

INT CTCPacket::GetType() CONST
{
	ULONGLONG  nType;

	return((Extract(m_nData[0], 0, 3, 1, nType)) ? (INT)nType : -1);
}

BOOL CTCPacket::SetAPID(INT nAPID)
{
	return Collect(m_nData[0], nAPID, 0, 5, 11);
}

INT CTCPacket::GetAPID() CONST
{
	ULONGLONG  nAPID;

	return((Extract(m_nData[0], 0, 5, 11, nAPID)) ? (INT)nAPID : -1);
}

BOOL CTCPacket::SetTCID(INT nTCID)
{
	return Collect(m_nData[0], nTCID, 7, 0, 8);
}

INT CTCPacket::GetTCID() CONST
{
	ULONGLONG  nTCID;

	return((Extract(m_nData[0], 7, 0, 8, nTCID)) ? (INT)nTCID : -1);
}

BOOL CTCPacket::SetTCType(INT nTCType)
{
	return Collect(m_nData[0], nTCType, 6, 2, 2);
}

INT CTCPacket::GetTCType() CONST
{
	ULONGLONG  nTCType;

	return((Extract(m_nData[0], 6, 2, 2, nTCType)) ? (INT)nTCType : -1);
}

BOOL CTCPacket::SetVersion(INT nVersion)
{
	return Collect(m_nData[0], nVersion, 0, 0, 3);
}

INT CTCPacket::GetVersion() CONST
{
	ULONGLONG  nVersion;

	return((Extract(m_nData[0], 0, 0, 3, nVersion)) ? (INT)nVersion : -1);
}

BOOL CTCPacket::SetDataFieldHeaderFlag(INT nFlag)
{
	return Collect(m_nData[0], nFlag, 0, 4, 1);
}

INT CTCPacket::GetDataFieldHeaderFlag() CONST
{
	ULONGLONG  nFlag;

	return((Extract(m_nData[0], 0, 4, 1, nFlag)) ? (INT)nFlag : -1);
}

BOOL CTCPacket::SetSequenceFlags(INT nFlags)
{
	return Collect(m_nData[0], nFlags, 2, 0, 2);
}

INT CTCPacket::GetSequenceFlags() CONST
{
	ULONGLONG  nFlags;

	return((Extract(m_nData[0], 2, 0, 2, nFlags)) ? (INT)nFlags : -1);
}

BOOL CTCPacket::SetSequenceCount(INT nCount)
{
	return Collect(m_nData[0], nCount, 2, 2, 14);
}

INT CTCPacket::GetSequenceCount() CONST
{
	ULONGLONG  nCount;

	return((Extract(m_nData[0], 2, 2, 14, nCount)) ? (INT)nCount : -1);
}

BOOL CTCPacket::SetCUCTimeTagFlag(INT nFlag)
{
	return Collect(m_nData[0], nFlag, 6, 0, 2);
}

INT CTCPacket::GetCUCTimeTagFlag() CONST
{
	ULONGLONG  nFlag;

	return((Extract(m_nData[0], 6, 0, 2, nFlag)) ? (INT)nFlag : -1);
}

BOOL CTCPacket::SetCUCTimeTag(UINT nTimeTag)
{
	return(Collect(m_nData[0], nTimeTag, 10, 0, 32) && Collect(m_nData[0], TCPACKET_TFIELDTIMECODE, 8, 0, 8) && Collect(m_nData[0], 0, 9, 0, 8));
}

UINT CTCPacket::GetCUCTimeTag() CONST
{
	ULONGLONG  nTimeTag;

	return((Extract(m_nData[0], 10, 0, 32, nTimeTag)) ? (UINT)nTimeTag : -1);
}

BOOL CTCPacket::SetCRCFlag(INT nFlag)
{
	return Collect(m_nData[0], nFlag, 6, 3, 1);
}

INT CTCPacket::GetCRCFlag() CONST
{
	ULONGLONG  nFlag;

	return((Extract(m_nData[0], 6, 3, 1, nFlag)) ? (INT)nFlag : -1);
}

BOOL CTCPacket::SetSize(INT nSize, BOOL bReset)
{
	if (nSize >= TCPACKET_HEADER_SIZE)
	{
		for (m_nData[0].SetSize(nSize); bReset; )
		{
			ZeroMemory(m_nData[0].GetData(), m_nData[0].GetSize());
			break;
		}
		return Collect(m_nData[0], max(nSize - TCPACKET_HEADER_SIZE - 1, 0), 4, 0, 16);
	}
	return FALSE;
}

INT CTCPacket::GetSize() CONST
{
	ULONGLONG  nSize;

	return((Extract(m_nData[0], 4, 0, 16, nSize)) ? (INT)(nSize + TCPACKET_HEADER_SIZE + 1) : -1);
}

BOOL CTCPacket::HasHeader() CONST
{
	return((m_nData[0].GetSize() >= TCPACKET_HEADER_SIZE) ? TRUE : FALSE);
}

BOOL CTCPacket::HasDataFieldHeader() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 0, 4, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BOOL CTCPacket::SetData(CONST CByteArray &nData, BOOL bExtra)
{
	m_nData[(bExtra) ? TRUE : FALSE].Copy(nData);
	return TRUE;
}
BOOL CTCPacket::SetData(BYTE nValue, INT nBytePos)
{
	return Collect(m_nData[0], nValue, TCPACKET_HEADER_SIZE + nBytePos);
}
BOOL CTCPacket::SetData(ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength)
{
	return Collect(m_nData[0], nValue, TCPACKET_HEADER_SIZE + nBytePos, nBitPos, nLength);
}

INT CTCPacket::GetData(CByteArray &nData, BOOL bExtra) CONST
{
	nData.Copy(m_nData[(bExtra) ? TRUE : FALSE]);
	return((INT)nData.GetSize());
}
BOOL CTCPacket::GetData(INT nBytePos, BYTE &nValue) CONST
{
	return Extract(m_nData[0], TCPACKET_HEADER_SIZE + nBytePos, nValue);
}
BOOL CTCPacket::GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST
{
	return Extract(m_nData[0], TCPACKET_HEADER_SIZE + nBytePos, nBitPos, nLength, nValue);
}

VOID CTCPacket::SetMapID(BYTE nMapID)
{
	m_nMapID = nMapID;
}

BYTE CTCPacket::GetMapID() CONST
{
	return m_nMapID;
}

VOID CTCPacket::MarkAsControlFrame(BOOL bEnable)
{
	m_bControlFrame = bEnable;
}

BOOL CTCPacket::IsControlFrame() CONST
{
	return m_bControlFrame;
}

VOID CTCPacket::MarkAsControlSegment(BOOL bEnable)
{
	m_bControlSegment = bEnable;
}

BOOL CTCPacket::IsControlSegment() CONST
{
	return m_bControlSegment;
}

VOID CTCPacket::MarkAsSLEThrowEvent(BOOL bEnable)
{
	m_bSLEThrowEvent = bEnable;
}

BOOL CTCPacket::IsSLEThrowEvent() CONST
{
	return m_bSLEThrowEvent;
}

VOID CTCPacket::MarkAsNISThrowEvent(BOOL bEnable)
{
	m_bNISThrowEvent = bEnable;
}

BOOL CTCPacket::IsNISThrowEvent() CONST
{
	return m_bNISThrowEvent;
}

VOID CTCPacket::Reset()
{
	m_nMapID = 0;
	m_bControlFrame = FALSE;
	m_bControlSegment = FALSE;
	m_bSLEThrowEvent = FALSE;
	m_bNISThrowEvent = FALSE;
	CTCUnit::Reset();
}

VOID CTCPacket::Copy(CONST CTCUnit *pTCUnit)
{
	CTCPacket  *pTCPacket;

	if ((pTCPacket = (pTCUnit->IsKindOf(RUNTIME_CLASS(CTCPacket))) ? (CTCPacket *)pTCUnit : (CTCPacket *)NULL))
	{
		m_nMapID = pTCPacket->m_nMapID;
		m_bControlFrame = pTCPacket->m_bControlFrame;
		m_bControlSegment = pTCPacket->m_bControlSegment;
		m_bSLEThrowEvent = pTCPacket->m_bSLEThrowEvent;
		m_bNISThrowEvent = pTCPacket->m_bNISThrowEvent;
	}
	CTCUnit::Copy(pTCPacket);
}

BOOL CTCPacket::Compare(CONST CTCUnit *pTCUnit) CONST
{
	CTCPacket  *pTCPacket;

	return(((pTCPacket = (pTCUnit->IsKindOf(RUNTIME_CLASS(CTCPacket))) ? (CTCPacket *)pTCUnit : (CTCPacket *)NULL)) ? ((pTCPacket->m_nMapID == m_nMapID  &&  pTCPacket->m_bControlFrame == m_bControlFrame  &&  pTCPacket->m_bControlSegment == m_bControlSegment  &&  pTCPacket->m_bSLEThrowEvent == m_bSLEThrowEvent  &&  pTCPacket->m_bNISThrowEvent == m_bNISThrowEvent) ? CTCUnit::Compare(pTCPacket) : FALSE) : CTCUnit::Compare(pTCUnit));
}


/////////////////////////////////////////////////////////////////////////////
// CTCTransferUnit

IMPLEMENT_DYNCREATE(CTCTransferUnit, CTCUnit)

CTCTransferUnit::CTCTransferUnit() : CTCUnit()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTCTransferUnits

CTCTransferUnits::CTCTransferUnits() : CPtrArray()
{
	return;
}

CTCTransferUnits::~CTCTransferUnits()
{
	RemoveAll();
}

INT CTCTransferUnits::Add(CTCTransferUnit *pTCTransferUnit)
{
	return((INT)CPtrArray::Add(pTCTransferUnit));
}

CTCTransferUnit *CTCTransferUnits::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCTransferUnit *)CPtrArray::GetAt(nIndex) : (CTCTransferUnit *)NULL);
}

CTCTransferUnit *CTCTransferUnits::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCTransferUnit *)CPtrArray::GetAt(nIndex) : (CTCTransferUnit *)NULL);
}

VOID CTCTransferUnits::RemoveAll()
{
	INT  nTransferUnit;
	INT  nTransferUnits;
	CTCTransferUnit  *pTCTransferUnit;

	for (nTransferUnit = 0, nTransferUnits = (INT)GetSize(); nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if ((pTCTransferUnit = GetAt(nTransferUnit))) delete pTCTransferUnit;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCTransferUnits::Copy(CONST CTCTransferUnits *pTCTransferUnits)
{
	INT  nTransferUnit;
	INT  nTransferUnits;
	CTCTransferUnit  *pTCTransferUnit;

	for (nTransferUnit = 0, nTransferUnits = (INT)pTCTransferUnits->GetSize(), RemoveAll(); nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if ((pTCTransferUnit = new CTCTransferUnit) != (CTCTransferUnit *)NULL)
		{
			pTCTransferUnit->Copy(pTCTransferUnits->GetAt(nTransferUnit));
			InsertAt(nTransferUnit, pTCTransferUnit, 1);
			continue;
		}
		break;
	}
	return((nTransferUnit == nTransferUnits) ? TRUE : FALSE);
}

BOOL CTCTransferUnits::Compare(CONST CTCTransferUnits *pTCTransferUnits) CONST
{
	INT  nTransferUnit;
	INT  nTransferUnits;

	for (nTransferUnit = 0, nTransferUnits = (pTCTransferUnits->GetSize() == GetSize()) ? (INT)GetSize() : -1; nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if (!pTCTransferUnits->GetAt(nTransferUnit)->Compare(GetAt(nTransferUnit))) break;
		continue;
	}
	return((nTransferUnit == nTransferUnits) ? TRUE : FALSE);
}

BOOL CTCTransferUnits::Map(CByteArray &nInfo) CONST
{
	INT  nTransferUnit;
	INT  nTransferUnits;
	CByteArray  nTransferUnitData;
	CTCTransferUnit  *pTCTransferUnit;

	for (nTransferUnit = 0, nTransferUnits = (INT)GetSize(), nInfo.RemoveAll(); nTransferUnit < nTransferUnits; nTransferUnit++)
	{
		if ((pTCTransferUnit = GetAt(nTransferUnit)) && pTCTransferUnit->Map(nTransferUnitData) && nInfo.Append(nTransferUnitData) >= 0) continue;
		break;
	}
	return((nTransferUnit == nTransferUnits) ? TRUE : FALSE);
}

BOOL CTCTransferUnits::Unmap(CONST CByteArray &nInfo)
{
	INT  cbTransferUnit;
	INT  cbTransferUnits;
	CByteArray  nTransferUnitData;
	CTCTransferUnit  *pTCTransferUnit;

	for (cbTransferUnits = 0, RemoveAll(); cbTransferUnits < nInfo.GetSize(); cbTransferUnits += cbTransferUnit)
	{
		for (CopyMemory(&cbTransferUnit, nInfo.GetData() + cbTransferUnits, sizeof(cbTransferUnit)), nTransferUnitData.SetSize(max(min(cbTransferUnit, nInfo.GetSize() - cbTransferUnits), 0)); nTransferUnitData.GetSize() >= 0; )
		{
			CopyMemory(nTransferUnitData.GetData(), nInfo.GetData() + cbTransferUnits, nTransferUnitData.GetSize());
			break;
		}
		if ((pTCTransferUnit = new CTCTransferUnit))
		{
			if (pTCTransferUnit->Unmap(nTransferUnitData))
			{
				if (Add(pTCTransferUnit) >= 0) continue;
				delete pTCTransferUnit;
				break;
			}
			delete pTCTransferUnit;
		}
		break;
	}
	return((cbTransferUnits == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCTransferFrame

IMPLEMENT_DYNCREATE(CTCTransferFrame, CTCTransferUnit)

CTCTransferFrame::CTCTransferFrame() : CTCTransferUnit()
{
	return;
}

BOOL CTCTransferFrame::SetVersion(BYTE nVersion)
{
	return Collect(m_nData[0], nVersion, 0, 0, 2);
}

BYTE CTCTransferFrame::GetVersion() CONST
{
	ULONGLONG  nVersion;

	return((Extract(m_nData[0], 0, 0, 2, nVersion)) ? (BYTE)nVersion : (BYTE)-1);
}

BOOL CTCTransferFrame::SetBypassFlag(BOOL bFlag)
{
	return Collect(m_nData[0], bFlag, 0, 2, 1);
}

BOOL CTCTransferFrame::GetBypassFlag() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 0, 2, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BOOL CTCTransferFrame::SetControlCommandFlag(BOOL bFlag)
{
	return Collect(m_nData[0], bFlag, 0, 3, 1);
}

BOOL  CTCTransferFrame::GetControlCommandFlag() CONST
{
	ULONGLONG  bFlag;

	return((Extract(m_nData[0], 0, 3, 1, bFlag)) ? (BOOL)bFlag : FALSE);
}

BOOL CTCTransferFrame::SetSpacecraftID(UINT nID)
{
	return Collect(m_nData[0], nID, 0, 6, 10);
}

UINT CTCTransferFrame::GetSpacecraftID() CONST
{
	ULONGLONG  nID;

	return((Extract(m_nData[0], 0, 6, 10, nID)) ? (UINT)nID : (UINT)-1);
}

BOOL CTCTransferFrame::SetVirtualChannel(BYTE nChannel)
{
	return Collect(m_nData[0], nChannel, 2, 0, 6);
}

BYTE CTCTransferFrame::GetVirtualChannel() CONST
{
	ULONGLONG  nChannel;

	return((Extract(m_nData[0], 2, 0, 6, nChannel)) ? (BYTE)nChannel : (BYTE)-1);
}

BOOL CTCTransferFrame::SetFrameLength(BYTE nLength, BOOL bReset)
{
	if (nLength > TCTRANSFERFRAME_HEADER_SIZE)
	{
		for (m_nData[0].SetSize(nLength + 1); bReset; )
		{
			ZeroMemory(m_nData[0].GetData(), m_nData[0].GetSize());
			break;
		}
		return Collect(m_nData[0], nLength, 3, 0, 8);
	}
	return FALSE;
}

BYTE CTCTransferFrame::GetFrameLength() CONST
{
	ULONGLONG  nLength;

	return((Extract(m_nData[0], 3, 0, 8, nLength)) ? (BYTE)nLength : (BYTE)-1);
}

BOOL CTCTransferFrame::SetFrameSequenceNumber(BYTE nNumber)
{
	return Collect(m_nData[0], nNumber, 4, 0, 8);
}

BYTE CTCTransferFrame::GetFrameSequenceNumber() CONST
{
	ULONGLONG  nNumber;

	return((Extract(m_nData[0], 4, 0, 8, nNumber)) ? (BYTE)nNumber : (BYTE)-1);
}

BOOL CTCTransferFrame::SetFrameData(CONST CTCPacket *pTCPacket)
{
	CByteArray  nData;

	return((pTCPacket->GetData(nData) > 0) ? SetFrameData(nData) : FALSE);
}
BOOL CTCTransferFrame::SetFrameData(CONST CByteArray &nData)
{
	if (nData.GetSize() > 0)
	{
		if (m_nData[0].GetSize() > TCTRANSFERFRAME_HEADER_SIZE + TCTRANSFERFRAME_TRAILER_SIZE)
		{
			for (m_nData[0].RemoveAt(TCTRANSFERFRAME_HEADER_SIZE, m_nData[0].GetSize() - TCTRANSFERFRAME_HEADER_SIZE - TCTRANSFERFRAME_TRAILER_SIZE), m_nData[0].InsertAt(TCTRANSFERFRAME_HEADER_SIZE, 0, nData.GetSize()); SetFrameLength((BYTE)(TCTRANSFERFRAME_HEADER_SIZE + nData.GetSize() + TCTRANSFERFRAME_TRAILER_SIZE - 1), FALSE); )
			{
				CopyMemory(m_nData[0].GetData() + TCTRANSFERFRAME_HEADER_SIZE, nData.GetData(), nData.GetSize());
				return TRUE;
			}
			return FALSE;
		}
		if (SetFrameLength((BYTE)(TCTRANSFERFRAME_HEADER_SIZE + nData.GetSize() + TCTRANSFERFRAME_TRAILER_SIZE - 1)))
		{
			CopyMemory(m_nData[0].GetData() + TCTRANSFERFRAME_HEADER_SIZE, nData.GetData(), nData.GetSize());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCTransferFrame::GetFrameData(CTCPacket *pTCPacket) CONST
{
	CByteArray  nData;

	for (pTCPacket->Reset(); GetFrameData(nData) > 0; )
	{
		pTCPacket->CTCUnit::Copy(this);
		pTCPacket->SetData(nData);
		return TRUE;
	}
	return FALSE;
}
INT CTCTransferFrame::GetFrameData(CByteArray &nData) CONST
{
	for (nData.Copy(m_nData[0]); nData.GetSize() > TCTRANSFERFRAME_HEADER_SIZE + TCTRANSFERFRAME_TRAILER_SIZE; )
	{
		nData.RemoveAt(nData.GetSize() - TCTRANSFERFRAME_TRAILER_SIZE, TCTRANSFERFRAME_TRAILER_SIZE);
		nData.RemoveAt(0, TCTRANSFERFRAME_HEADER_SIZE);
		return((INT)nData.GetSize());
	}
	nData.RemoveAll();
	return 0;
}

BOOL CTCTransferFrame::SetFrameErrorControlWord(WORD wFECW)
{
	return((m_nData[0].GetSize() > TCTRANSFERFRAME_HEADER_SIZE + TCTRANSFERFRAME_TRAILER_SIZE) ? Collect(m_nData[0], wFECW, (INT)(m_nData[0].GetSize() - sizeof(WORD)), 0, 8 * sizeof(WORD)) : FALSE);
}

WORD CTCTransferFrame::GetFrameErrorControlWord() CONST
{
	return((m_nData[0].GetSize() > TCTRANSFERFRAME_HEADER_SIZE + TCTRANSFERFRAME_TRAILER_SIZE) ? MAKEWORD(m_nData[0].GetAt(m_nData[0].GetUpperBound()), m_nData[0].GetAt(m_nData[0].GetUpperBound() - 1)) : 0);
}


/////////////////////////////////////////////////////////////////////////////
// CTCTransferFrames

CTCTransferFrames::CTCTransferFrames() : CPtrArray()
{
	return;
}

CTCTransferFrames::~CTCTransferFrames()
{
	RemoveAll();
}

INT CTCTransferFrames::Add(CTCTransferFrame *pTCTransferFrame)
{
	return((INT)CPtrArray::Add(pTCTransferFrame));
}

CTCTransferFrame *CTCTransferFrames::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCTransferFrame *)CPtrArray::GetAt(nIndex) : (CTCTransferFrame *)NULL);
}

CTCTransferFrame *CTCTransferFrames::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCTransferFrame *)CPtrArray::GetAt(nIndex) : (CTCTransferFrame *)NULL);
}

VOID CTCTransferFrames::RemoveAll()
{
	INT  nTransferFrame;
	INT  nTransferFrames;
	CTCTransferFrame  *pTCTransferFrame;

	for (nTransferFrame = 0, nTransferFrames = (INT)GetSize(); nTransferFrame < nTransferFrames; nTransferFrame++)
	{
		if ((pTCTransferFrame = GetAt(nTransferFrame))) delete pTCTransferFrame;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCTransferFrames::Copy(CONST CTCTransferFrames *pTCTransferFrames)
{
	INT  nTransferFrame;
	INT  nTransferFrames;
	CTCTransferFrame  *pTCTransferFrame;

	for (nTransferFrame = 0, nTransferFrames = (INT)pTCTransferFrames->GetSize(), RemoveAll(); nTransferFrame < nTransferFrames; nTransferFrame++)
	{
		if ((pTCTransferFrame = new CTCTransferFrame) != (CTCTransferFrame *)NULL)
		{
			pTCTransferFrame->Copy(pTCTransferFrames->GetAt(nTransferFrame));
			InsertAt(nTransferFrame, pTCTransferFrame, 1);
			continue;
		}
		break;
	}
	return((nTransferFrame == nTransferFrames) ? TRUE : FALSE);
}

BOOL CTCTransferFrames::Compare(CONST CTCTransferFrames *pTCTransferFrames) CONST
{
	INT  nTransferFrame;
	INT  nTransferFrames;

	for (nTransferFrame = 0, nTransferFrames = (pTCTransferFrames->GetSize() == GetSize()) ? (INT)GetSize() : -1; nTransferFrame < nTransferFrames; nTransferFrame++)
	{
		if (!pTCTransferFrames->GetAt(nTransferFrame)->Compare(GetAt(nTransferFrame))) break;
		continue;
	}
	return((nTransferFrame == nTransferFrames) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameter

CTMParameter::CTMParameter() : CObject()
{
	m_nAttributes = 0;
	m_wPastSamples[0] = 0;
	m_wPastSamples[1] = 0;
	m_tPacket[0] = 0;
	m_tPacket[1] = 0;
	m_tRetention = -1;
	m_szOolUnit.Empty();
	m_tOolTime = 0;
	m_wOolInfo[0] = -1;
	m_wOolInfo[1] = -1;
	m_nOolFlags = 0;
	m_nOolCount = 0;
	m_pDerivationProcedure = (DERIVATIONPROCEDURE)NULL;
}

VOID CTMParameter::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CTMParameter::GetTag() CONST
{
	return m_szTag;
}

VOID CTMParameter::SetAttributes(ULONGLONG nAttributes)
{
	m_nAttributes = nAttributes;
}

ULONGLONG CTMParameter::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CTMParameter::Initialize(CTMParameter *pTMParameter, BOOL bBadData)
{
	Update(pTMParameter, bBadData);
}

BOOL CTMParameter::IsInitialized() CONST
{
	return(((GetAttributes() & TMPARAMETER_NATURE_CONSTANT) || (!m_szPacket[0].IsEmpty() && !m_szPacket[1].IsEmpty())) ? TRUE : FALSE);
}

BOOL CTMParameter::Update(CONST CTMParameter *pTMParameter)
{
	if (pTMParameter->m_nValues.GetSize() == pTMParameter->m_tValues.GetSize() && pTMParameter->m_nValues.GetSize() == pTMParameter->m_nStatus.GetSize() && pTMParameter->m_nValues.GetSize() == pTMParameter->m_szCalTables.GetSize())
	{
		m_szPacket[0] = pTMParameter->m_szPacket[0];
		m_szPacket[1] = pTMParameter->m_szPacket[1];
		m_tPacket[0] = pTMParameter->m_tPacket[0];
		m_tPacket[1] = pTMParameter->m_tPacket[1];
		m_nValues.Copy(pTMParameter->m_nValues);
		m_tValues.Copy(pTMParameter->m_tValues);
		m_nStatus.Copy(pTMParameter->m_nStatus);
		m_szCalTables.Copy(pTMParameter->m_szCalTables);
		if (pTMParameter->m_wPastSamples[1] > m_wPastSamples[1])
		{
			m_nValues.RemoveAt(0, pTMParameter->m_wPastSamples[1] - m_wPastSamples[1]);
			m_tValues.RemoveAt(0, pTMParameter->m_wPastSamples[1] - m_wPastSamples[1]);
			m_nStatus.RemoveAt(0, pTMParameter->m_wPastSamples[1] - m_wPastSamples[1]);
			m_szCalTables.RemoveAt(0, pTMParameter->m_wPastSamples[1] - m_wPastSamples[1]);
		}
		m_wPastSamples[1] = min(pTMParameter->m_wPastSamples[1], m_wPastSamples[1]);
		m_szOolUnit = pTMParameter->m_szOolUnit;
		m_tOolTime = pTMParameter->m_tOolTime;
		m_wOolInfo[0] = pTMParameter->m_wOolInfo[0];
		m_wOolInfo[1] = pTMParameter->m_wOolInfo[1];
		m_nOolCount = pTMParameter->m_nOolCount;
		return TRUE;
	}
	return FALSE;
}
BOOL CTMParameter::Update(CONST CTMParameter *pTMParameter, BOOL bBadData)
{
	INT  nSample;
	INT  nSamples;
	UINT  nOccurrence;
	UINT  nOccurrences;

	if (pTMParameter->m_nValues.GetSize() == pTMParameter->m_tValues.GetSize() && pTMParameter->m_nValues.GetSize() == pTMParameter->m_nStatus.GetSize() && pTMParameter->m_nValues.GetSize() == pTMParameter->m_szCalTables.GetSize())
	{
		if (pTMParameter->m_szPacket[1] != m_szPacket[1] || pTMParameter->m_tPacket[1] != m_tPacket[1])
		{
			if ((nSamples = (INT)(m_nValues.GetSize() - m_wPastSamples[0])) > 0)
			{
				if (!m_wPastSamples[0])
				{
					m_szPacket[0].Empty();
					m_szPacket[1].Empty();
					m_tPacket[0] = 0;
					m_tPacket[1] = 0;
				}
				m_nValues.RemoveAt(0, nSamples);
				m_tValues.RemoveAt(0, nSamples);
				m_nStatus.RemoveAt(0, nSamples);
				m_szCalTables.RemoveAt(0, nSamples);
			}
			if (!bBadData)
			{
				for (nOccurrence = pTMParameter->m_wPastSamples[1], nOccurrences = (UINT)pTMParameter->m_nValues.GetSize(), nSamples = (INT)m_nValues.GetSize(); nOccurrence < nOccurrences; nOccurrence++)
				{
					if (pTMParameter->m_nStatus.GetAt(nOccurrence) & TMPARAMETER_STATUS_GOOD)
					{
						m_szPacket[0] = pTMParameter->m_szPacket[0];
						m_szPacket[1] = pTMParameter->m_szPacket[1];
						m_tPacket[0] = pTMParameter->m_tPacket[0];
						m_tPacket[1] = pTMParameter->m_tPacket[1];
						m_nValues.SetAtGrow((nSample = nSamples + nOccurrence - pTMParameter->m_wPastSamples[1]), pTMParameter->m_nValues.GetAt(nOccurrence));
						m_tValues.SetAtGrow(nSample, pTMParameter->m_tValues.GetAt(nOccurrence));
						m_nStatus.SetAtGrow(nSample, pTMParameter->m_nStatus.GetAt(nOccurrence));
						m_szCalTables.SetAtGrow(nSample, pTMParameter->m_szCalTables.GetAt(nOccurrence));
					}
				}
			}
			else
			{
				m_szPacket[0] = pTMParameter->m_szPacket[0];
				m_szPacket[1] = pTMParameter->m_szPacket[1];
				m_tPacket[0] = pTMParameter->m_tPacket[0];
				m_tPacket[1] = pTMParameter->m_tPacket[1];
				m_nValues.Append(pTMParameter->m_nValues);
				m_tValues.Append(pTMParameter->m_tValues);
				m_nStatus.Append(pTMParameter->m_nStatus);
				m_szCalTables.Append(pTMParameter->m_szCalTables);
			}
			m_wPastSamples[1] = (m_wPastSamples[0] > 0) ? (WORD)(m_nValues.GetSize() - (pTMParameter->m_nValues.GetSize() - pTMParameter->m_wPastSamples[1])) : 0;
			m_szOolUnit = pTMParameter->m_szOolUnit;
			m_tOolTime = pTMParameter->m_tOolTime;
			m_wOolInfo[0] = pTMParameter->m_wOolInfo[0];
			m_wOolInfo[1] = pTMParameter->m_wOolInfo[1];
			m_nOolCount = pTMParameter->m_nOolCount;
			return TRUE;
		}
		else
		{
			if (m_wPastSamples[1] < m_nValues.GetSize())
			{
				m_nValues.RemoveAt(m_wPastSamples[1], m_nValues.GetSize() - m_wPastSamples[1]);
				m_tValues.RemoveAt(m_wPastSamples[1], m_tValues.GetSize() - m_wPastSamples[1]);
				m_nStatus.RemoveAt(m_wPastSamples[1], m_nStatus.GetSize() - m_wPastSamples[1]);
				m_szCalTables.RemoveAt(m_wPastSamples[1], m_szCalTables.GetSize() - m_wPastSamples[1]);
			}
			m_nValues.Append(pTMParameter->m_nValues);
			m_tValues.Append(pTMParameter->m_tValues);
			m_nStatus.Append(pTMParameter->m_nStatus);
			m_szCalTables.Append(pTMParameter->m_szCalTables);
			m_nValues.RemoveAt(m_wPastSamples[1], pTMParameter->m_wPastSamples[1]);
			m_tValues.RemoveAt(m_wPastSamples[1], pTMParameter->m_wPastSamples[1]);
			m_nStatus.RemoveAt(m_wPastSamples[1], pTMParameter->m_wPastSamples[1]);
			m_szCalTables.RemoveAt(m_wPastSamples[1], pTMParameter->m_wPastSamples[1]);
			return TRUE;
		}
	}
	return FALSE;
}

VOID CTMParameter::Reset()
{
	for (m_szPacket[0].Empty(), m_szPacket[1].Empty(), m_tPacket[0] = m_tPacket[1] = 0; (GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT; )
	{
		m_nValues.RemoveAll();
		m_tValues.RemoveAll();
		m_nStatus.RemoveAll();
		m_szCalTables.RemoveAll();
		m_wPastSamples[1] = 0;
		break;
	}
	m_szOolUnit.Empty();
	m_tOolTime = 0;
	m_wOolInfo[0] = -1;
	m_wOolInfo[1] = -1;
	m_nOolFlags = 0;
	m_nOolCount = 0;
}

BOOL CTMParameter::SetRawValue(CONST CTMUnit *pTMUnit, INT nSample, ULONGLONG nRawValue, UINT nStatus, LPCTSTR pszCalTable)
{
	if (nSample >= 0)
	{
		if (m_nValues.GetSize() <= nSample + m_wPastSamples[1] || m_nStatus.GetSize() <= nSample + m_wPastSamples[1] || m_nStatus.GetAt(nSample + m_wPastSamples[1]) == TMPARAMETER_STATUS_NONE || m_nValues.GetAt(nSample + m_wPastSamples[1]) != nRawValue)
		{
			m_szPacket[0] = pTMUnit->GetTag();
			m_tPacket[0] = pTMUnit->GetTimeTag();
		}
		if (pTMUnit->GetTag() != m_szPacket[1] || pTMUnit->GetTimeTag() != m_tPacket[1])
		{
			m_wPastSamples[1] = (WORD)min(m_nValues.GetSize(), m_wPastSamples[0]);
			m_nValues.RemoveAt(0, m_nValues.GetSize() - m_wPastSamples[1]);
			m_tValues.RemoveAt(0, m_tValues.GetSize() - m_wPastSamples[1]);
			m_nStatus.RemoveAt(0, m_nStatus.GetSize() - m_wPastSamples[1]);
			m_szCalTables.RemoveAt(0, m_szCalTables.GetSize() - m_wPastSamples[1]);
		}
		m_szPacket[1] = pTMUnit->GetTag();
		m_tPacket[1] = pTMUnit->GetTimeTag();
		m_nValues.SetAtGrow(nSample + m_wPastSamples[1], nRawValue);
		m_tValues.SetAtGrow(nSample + m_wPastSamples[1], pTMUnit->GetTimeTag());
		m_nStatus.SetAtGrow(nSample + m_wPastSamples[1], (nStatus == TMPARAMETER_STATUS_NONE) ? ((nSample + m_wPastSamples[1] < m_nStatus.GetSize()) ? m_nStatus.GetAt(nSample + m_wPastSamples[1]) : (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID)) : nStatus);
		m_szCalTables.SetAtGrow(nSample + m_wPastSamples[1], (!AfxIsValidString(pszCalTable)) ? ((nSample + m_wPastSamples[1] < m_szCalTables.GetSize()) ? (LPCTSTR)m_szCalTables.GetAt(nSample + m_wPastSamples[1]) : EMPTYSTRING) : pszCalTable);
		return((m_nValues.GetSize() == m_tValues.GetSize() && m_nValues.GetSize() == m_nStatus.GetSize() && m_nValues.GetSize() == m_szCalTables.GetSize()) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTMParameter::GetRawValue(INT nSample, ULONGLONG &nRawValue, UINT &nStatus, CString &szCalTable, BOOL bPast) CONST
{
	INT  nOccurrence;

	if ((nOccurrence = (!bPast  &&  nSample >= 0) ? (nSample + m_wPastSamples[1]) : (m_wPastSamples[1] - abs(nSample))) >= 0 && nOccurrence < m_nValues.GetSize() && m_nStatus.GetAt(nOccurrence) != TMPARAMETER_STATUS_NONE)
	{
		nRawValue = m_nValues.GetAt(nOccurrence);
		nStatus = m_nStatus.GetAt(nOccurrence);
		szCalTable = m_szCalTables.GetAt(nOccurrence);
		return TRUE;
	}
	return FALSE;
}
BOOL CTMParameter::GetRawValue(INT nSample, ULONGLONG &nRawValue, UINT &nStatus, BOOL bPast) CONST
{
	INT  nOccurrence;

	if ((nOccurrence = (!bPast  &&  nSample >= 0) ? (nSample + m_wPastSamples[1]) : (m_wPastSamples[1] - abs(nSample))) >= 0 && nOccurrence < m_nValues.GetSize() && m_nStatus.GetAt(nOccurrence) != TMPARAMETER_STATUS_NONE)
	{
		nRawValue = m_nValues.GetAt(nOccurrence);
		nStatus = m_nStatus.GetAt(nOccurrence);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMParameter::Calibrate(CONST CDatabaseEngine *pDatabase, ULONGLONG nFlags, ULONGLONG nRawValue, LPCTSTR pszCalTable, double &fValue, BOOL &bOut) CONST
{
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	for (fValue = 0.0, bOut = FALSE; (nFlags & TMPARAMETER_CODING_SIGNEDINTEGER) || (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX) || (nFlags & TMPARAMETER_CODING_INVERSEBITPATTERN); )
	{
		if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(m_szTag))))
		{
			nRawValue = CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, pDatabaseTMParameter->GetWidth(), nRawValue, FALSE);
			break;
		}
		return FALSE;
	}
	if (nFlags & TMPARAMETER_CALIBRATION_NUMERICAL)
	{
		if ((pDatabaseTMNumCalTable = pDatabase->GetTMNumCalTables()->GetAt(pDatabase->GetTMNumCalTables()->Find(pszCalTable))))
		{
			if ((nFlags & TMPARAMETER_CODING_SIGNEDINTEGER) == TMPARAMETER_CODING_SIGNEDINTEGER || (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX) == TMPARAMETER_CODING_COMPLEMENTCOMPLEX)
			{
				fValue = pDatabaseTMNumCalTable->Calibrate((double)(LONGLONG)nRawValue, (nFlags & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? TRUE : FALSE, bOut);
				return TRUE;
			}
			if (nFlags & TMPARAMETER_CODING_FLOATINGPOINT)
			{
				fValue = pDatabaseTMNumCalTable->Calibrate(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue, FALSE), (nFlags & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? TRUE : FALSE, bOut);
				return TRUE;
			}
			fValue = pDatabaseTMNumCalTable->Calibrate((double)nRawValue, (nFlags & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? TRUE : FALSE, bOut);
			return TRUE;
		}
	}
	if ((nFlags & TMPARAMETER_CODING_BITPATTERN) || (nFlags & TMPARAMETER_CODING_INVERSEBITPATTERN))
	{
		fValue = (double)nRawValue;
		return TRUE;
	}
	if (nFlags & TMPARAMETER_CODING_SIGNEDINTEGER)
	{
		fValue = (double)(LONGLONG)nRawValue;
		return TRUE;
	}
	if (nFlags & TMPARAMETER_CODING_UNSIGNEDINTEGER)
	{
		fValue = (double)nRawValue;
		return TRUE;
	}
	if (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)
	{
		fValue = (double)(LONGLONG)nRawValue;
		return TRUE;
	}
	if (nFlags & TMPARAMETER_CODING_FLOATINGPOINT)
	{
		fValue = CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue, FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue, BOOL bPast) CONST
{
	BOOL  bOut;

	return GetValue(pDatabase, nSample, GetAttributes(), fValue, bOut, bPast);
}
BOOL CTMParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue, BOOL &bOut, BOOL bPast) CONST
{
	return GetValue(pDatabase, nSample, GetAttributes(), fValue, bOut, bPast);
}
BOOL CTMParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue, BOOL bPast) CONST
{
	BOOL  bOut;

	return GetValue(pDatabase, nSample, nFlags, fValue, bOut, bPast);
}
BOOL CTMParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue, BOOL &bOut, BOOL bPast) CONST
{
	UINT  nStatus;
	CString  szCalTable;
	ULONGLONG  nRawValue;

	return((GetRawValue(nSample, nRawValue, nStatus, szCalTable, bPast)) ? Calibrate(pDatabase, nFlags, nRawValue, szCalTable, fValue, bOut) : FALSE);
}

BOOL CTMParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue, BOOL bPast) CONST
{
	BOOL  bOut;

	return GetValueAsText(pDatabase, nSample, GetAttributes(), -1, szValue, bOut, bPast);
}
BOOL CTMParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue, BOOL &bOut, BOOL bPast) CONST
{
	return GetValueAsText(pDatabase, nSample, GetAttributes(), -1, szValue, bOut, bPast);
}
BOOL CTMParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue, BOOL bPast) CONST
{
	BOOL  bOut;

	return GetValueAsText(pDatabase, nSample, nFlags, -1, szValue, bOut, bPast);
}
BOOL CTMParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue, BOOL &bOut, BOOL bPast) CONST
{
	return GetValueAsText(pDatabase, nSample, nFlags, -1, szValue, bOut, bPast);
}
BOOL CTMParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue, BOOL bPast) CONST
{
	BOOL  bOut;

	return GetValueAsText(pDatabase, nSample, nFlags, nDigits, szValue, bOut, bPast);
}
BOOL CTMParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue, BOOL &bOut, BOOL bPast) CONST
{
	UINT  nStatus;
	CString  szCalTable;
	ULONGLONG  nRawValue;
	CStringTools  cStringTools;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (szValue.Empty(), bOut = FALSE; GetRawValue(nSample, nRawValue, nStatus, szCalTable, bPast); )
	{
		for (; (nFlags & TMPARAMETER_CODING_SIGNEDINTEGER) || (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX) || (nFlags & TMPARAMETER_CODING_INVERSEBITPATTERN); )
		{
			if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(m_szTag))))
			{
				nRawValue = CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, pDatabaseTMParameter->GetWidth(), nRawValue, FALSE);
				break;
			}
			return FALSE;
		}
		if (nFlags & TMPARAMETER_CALIBRATION_NUMERICAL)
		{
			if ((pDatabaseTMNumCalTable = pDatabase->GetTMNumCalTables()->GetAt(pDatabase->GetTMNumCalTables()->Find(szCalTable))))
			{
				if ((nFlags & TMPARAMETER_CODING_SIGNEDINTEGER) == TMPARAMETER_CODING_SIGNEDINTEGER || (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX) == TMPARAMETER_CODING_COMPLEMENTCOMPLEX)
				{
					szValue = pDatabaseTMNumCalTable->CalibrateAsText((double)(LONGLONG)nRawValue, nDigits, (nFlags & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? TRUE : FALSE, bOut);
					return TRUE;
				}
				if (nFlags & TMPARAMETER_CODING_FLOATINGPOINT)
				{
					szValue = pDatabaseTMNumCalTable->CalibrateAsText(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue, FALSE), nDigits, (nFlags & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? TRUE : FALSE, bOut);
					return TRUE;
				}
				szValue = pDatabaseTMNumCalTable->CalibrateAsText((double)nRawValue, nDigits, (nFlags & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? TRUE : FALSE, bOut);
				return TRUE;
			}
		}
		if (nFlags & TMPARAMETER_CALIBRATION_STATUS)
		{
			if ((pDatabaseTMTxtCalTable = pDatabase->GetTMTxtCalTables()->GetAt(pDatabase->GetTMTxtCalTables()->Find(szCalTable))))
			{
				if ((nFlags & TMPARAMETER_CODING_SIGNEDINTEGER) || (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
				{
					szValue = pDatabaseTMTxtCalTable->Translate((double)(LONGLONG)nRawValue, -1, bOut);
					return TRUE;
				}
				if (nFlags & TMPARAMETER_CODING_FLOATINGPOINT)
				{
					szValue = pDatabaseTMTxtCalTable->Translate(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue, FALSE), -1, bOut);
					return TRUE;
				}
				szValue = pDatabaseTMTxtCalTable->Translate((double)nRawValue, -1, bOut);
				return TRUE;
			}
		}
		if (nFlags & TMPARAMETER_CALIBRATION_NONE)
		{
			if (GetAttributes() & TMPARAMETER_NATURE_CONSTANT)
			{
				if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(m_szTag))))
				{
					szValue = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? cStringTools.ConvertFloatToString(_ttof(pDatabaseTMParameter->GetConstValueAsText()), nDigits) : pDatabaseTMParameter->GetConstValueAsText();
					return TRUE;
				}
				return FALSE;
			}
		}
		if (((nFlags & TMPARAMETER_CODING_UNSIGNEDINTEGER) && (nFlags & (TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL))) || (nFlags & TMPARAMETER_CODING_BITPATTERN) || (nFlags & TMPARAMETER_CODING_INVERSEBITPATTERN))
		{
			if ((nFlags & TMPARAMETER_RADIX_BINARY) || (nFlags & (TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) == 0)
			{
				szValue = cStringTools.ConvertLongUIntToString(nRawValue, 2);
				return TRUE;
			}
			if (nFlags & TMPARAMETER_RADIX_OCTAL)
			{
				szValue = cStringTools.ConvertLongUIntToString(nRawValue, 8);
				return TRUE;
			}
			if (nFlags & TMPARAMETER_RADIX_DECIMAL)
			{
				szValue = cStringTools.ConvertLongUIntToString(nRawValue, 10);
				return TRUE;
			}
			if (nFlags & TMPARAMETER_RADIX_HEXADECIMAL)
			{
				szValue = cStringTools.ConvertLongUIntToString(nRawValue, 16);
				return TRUE;
			}
		}
		if ((nFlags & TMPARAMETER_CODING_SIGNEDINTEGER) || (nFlags & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
		{
			szValue = cStringTools.ConvertLongIntToString(nRawValue, 10);
			return TRUE;
		}
		if (nFlags & TMPARAMETER_CODING_UNSIGNEDINTEGER)
		{
			szValue = cStringTools.ConvertLongUIntToString(nRawValue, 10);
			return TRUE;
		}
		if (nFlags & TMPARAMETER_CODING_FLOATINGPOINT)
		{
			szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue, FALSE), nDigits);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

CTimeTag CTMParameter::GetValueTime(INT nSample, BOOL bPast) CONST
{
	INT  nOccurrence;

	return(((nOccurrence = (!bPast  &&  nSample >= 0) ? (nSample + m_wPastSamples[1]) : (m_wPastSamples[1] - abs(nSample))) >= 0 && nOccurrence < m_tValues.GetSize() && m_nStatus.GetAt(nOccurrence) != TMPARAMETER_STATUS_NONE) ? m_tValues.GetAt(nOccurrence) : 0);
}

INT CTMParameter::GetValueCount() CONST
{
	return((INT)m_nValues.GetSize() - m_wPastSamples[1]);
}

VOID CTMParameter::SetPastValueSamples(WORD wSamples)
{
	m_wPastSamples[0] = wSamples;
}

WORD CTMParameter::GetPastValueSamples() CONST
{
	return m_wPastSamples[0];
}

BOOL CTMParameter::GetPastRawValue(INT nSample, ULONGLONG &nValue, UINT &nStatus) CONST
{
	return GetRawValue(nSample, nValue, nStatus, TRUE);
}

BOOL CTMParameter::GetPastValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue) CONST
{
	return GetValue(pDatabase, nSample, fValue, TRUE);
}

BOOL CTMParameter::GetPastValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue) CONST
{
	return GetValueAsText(pDatabase, nSample, szValue, TRUE);
}

INT CTMParameter::GetPastValueCount() CONST
{
	return m_wPastSamples[1];
}

VOID CTMParameter::SetOolInfo()
{
	m_szOolUnit.Empty();
	m_tOolTime = 0;
	m_wOolInfo[0] = -1;
	m_wOolInfo[1] = -1;
}
VOID CTMParameter::SetOolInfo(LPCTSTR pszUnit, CONST CTimeTag &tUnit, WORD wTable, WORD wLimit)
{
	m_szOolUnit = pszUnit;
	m_tOolTime = tUnit;
	m_wOolInfo[0] = wTable;
	m_wOolInfo[1] = wLimit;
}

BOOL CTMParameter::GetOolInfo(CString &szUnit, CTimeTag &tUnit, WORD &wTable, WORD &wLimit) CONST
{
	szUnit = m_szOolUnit;
	tUnit = m_tOolTime;
	wTable = m_wOolInfo[0];
	wLimit = m_wOolInfo[1];
	return((!szUnit.IsEmpty() || tUnit > 0 || wTable != (WORD)-1 || wLimit != (WORD)-1) ? TRUE : FALSE);
}

VOID CTMParameter::SetOolFlags(UINT nFlags)
{
	m_nOolFlags = nFlags;
}

UINT CTMParameter::GetOolFlags() CONST
{
	return m_nOolFlags;
}

VOID CTMParameter::SetOolCount(INT nCount)
{
	m_nOolCount = nCount;
}

INT CTMParameter::GetOolCount() CONST
{
	return m_nOolCount;
}

BOOL CTMParameter::SetOolStatus(INT nSample, UINT nStatus)
{
	if (m_wPastSamples[1] + nSample < (INT)m_nStatus.GetSize())
	{
		m_nStatus.SetAt(m_wPastSamples[1] + nSample, (m_nStatus.GetAt(m_wPastSamples[1] + nSample) & ~(TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_EVENTLIMIT)) | (nStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_EVENTLIMIT)));
		return TRUE;
	}
	return FALSE;
}

UINT CTMParameter::GetOolStatus(INT nSample) CONST
{
	return((m_wPastSamples[1] + nSample < (INT)m_nStatus.GetSize()) ? (m_nStatus.GetAt(m_wPastSamples[1] + nSample) & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_EVENTLIMIT)) : TMPARAMETER_STATUS_NONE);
}

BOOL CTMParameter::SetValidityStatus(UINT nStatus)
{
	INT  nSample;
	INT  nSamples;

	for (nSample = m_wPastSamples[1], nSamples = (INT)m_nStatus.GetSize(); nSample < nSamples; nSample++)
	{
		m_nStatus.SetAt(nSample, (m_nStatus.GetAt(nSample) & ~(TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) | (nStatus & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)));
		continue;
	}
	return(m_wPastSamples[1] < nSamples);
}

UINT CTMParameter::GetValidityStatus() CONST
{
	return((m_nStatus.GetSize() > 0) ? (m_nStatus.GetAt(m_nStatus.GetUpperBound()) & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) : TMPARAMETER_STATUS_NONE);
}

VOID CTMParameter::SetRetention(CONST CTimeSpan &tRetention)
{
	m_tRetention = tRetention;
}

CTimeSpan CTMParameter::GetRetention() CONST
{
	return m_tRetention;
}

CString CTMParameter::GetLastChangeTMUnit() CONST
{
	return m_szPacket[0];
}

CString CTMParameter::GetLastUpdateTMUnit() CONST
{
	return m_szPacket[1];
}

CTimeTag CTMParameter::GetLastChangeTime() CONST
{
	return m_tPacket[0];
}

CTimeTag CTMParameter::GetLastUpdateTime() CONST
{
	return m_tPacket[1];
}

VOID CTMParameter::SetDerivationProcedure(DERIVATIONPROCEDURE pDerivationProcedure)
{
	m_pDerivationProcedure = pDerivationProcedure;
}

DERIVATIONPROCEDURE CTMParameter::GetDerivationProcedure() CONST
{
	return m_pDerivationProcedure;
}

BOOL CTMParameter::Copy(CONST CTMParameter *pTMParameter)
{
	m_szTag = pTMParameter->m_szTag;
	m_szPacket[0] = pTMParameter->m_szPacket[0];
	m_szPacket[1] = pTMParameter->m_szPacket[1];
	m_tPacket[0] = pTMParameter->m_tPacket[0];
	m_tPacket[1] = pTMParameter->m_tPacket[1];
	m_nValues.Copy(pTMParameter->m_nValues);
	m_tValues.Copy(pTMParameter->m_tValues);
	m_nStatus.Copy(pTMParameter->m_nStatus);
	m_szCalTables.Copy(pTMParameter->m_szCalTables);
	m_wPastSamples[0] = pTMParameter->m_wPastSamples[0];
	m_wPastSamples[1] = pTMParameter->m_wPastSamples[1];
	m_nAttributes = pTMParameter->m_nAttributes;
	m_szOolUnit = pTMParameter->m_szOolUnit;
	m_tOolTime = pTMParameter->m_tOolTime;
	m_wOolInfo[0] = pTMParameter->m_wOolInfo[0];
	m_wOolInfo[1] = pTMParameter->m_wOolInfo[1];
	m_nOolFlags = pTMParameter->m_nOolFlags;
	m_nOolCount = pTMParameter->m_nOolCount;
	return TRUE;
}

BOOL CTMParameter::Compare(CONST CTMParameter *pTMParameter) CONST
{
	INT  nOccurrence;
	INT  nOccurrences;

	for (nOccurrence = 0, nOccurrences = (pTMParameter->m_szTag == m_szTag && pTMParameter->m_nAttributes == m_nAttributes && pTMParameter->m_wPastSamples[0] == m_wPastSamples[0] && pTMParameter->m_wPastSamples[1] == m_wPastSamples[1] && pTMParameter->m_szPacket[0] == m_szPacket[0] && pTMParameter->m_szPacket[1] == m_szPacket[1] && pTMParameter->m_tPacket[0] == m_tPacket[0] && pTMParameter->m_tPacket[1] == m_tPacket[1] && pTMParameter->m_nValues.GetSize() == m_nValues.GetSize() && pTMParameter->m_tValues.GetSize() == m_tValues.GetSize() && pTMParameter->m_nStatus.GetSize() == m_nStatus.GetSize() && m_nValues.GetSize() == m_tValues.GetSize() && m_nValues.GetSize() == m_nStatus.GetSize() && pTMParameter->m_szCalTables.GetSize() == m_szCalTables.GetSize() && m_nValues.GetSize() == m_szCalTables.GetSize() && pTMParameter->m_szOolUnit == m_szOolUnit && pTMParameter->m_tOolTime == m_tOolTime && pTMParameter->m_wOolInfo[0] == m_wOolInfo[0] && pTMParameter->m_wOolInfo[1] == m_wOolInfo[1] && pTMParameter->m_nOolFlags == m_nOolFlags && pTMParameter->m_nOolCount == m_nOolCount) ? (INT)m_nValues.GetSize() : -1; nOccurrence < nOccurrences; nOccurrence++)
	{
		if (pTMParameter->m_nValues.GetAt(nOccurrence) != m_nValues.GetAt(nOccurrence) || pTMParameter->m_tValues.GetAt(nOccurrence) != m_tValues.GetAt(nOccurrence) || pTMParameter->m_nStatus.GetAt(nOccurrence) != m_nStatus.GetAt(nOccurrence) || pTMParameter->m_szCalTables.GetAt(nOccurrence) != m_szCalTables.GetAt(nOccurrence)) break;
		continue;
	}
	return((nOccurrence == nOccurrences) ? TRUE : FALSE);
}

BOOL CTMParameter::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nTable;
	INT  nTables;
	CByteArray  nTablesData;
	CByteArray  nValuesData;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	sData.cbPacket[0] = (m_szPacket[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbPacket[1] = (m_szPacket[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbPacket[2] = (m_szOolUnit.GetLength() + 1)*sizeof(TCHAR);
	for (nTable = 0, nTables = (INT)m_szCalTables.GetSize(), sData.cbCalTables = 0, sData.cbValues[0] = (INT)m_nValues.GetSize()*sizeof(ULONGLONG), sData.cbValues[1] = m_tValues.Map(nValuesData), sData.cbStatus = (INT)m_nStatus.GetSize()*sizeof(UINT); nTable < nTables; nTable++, sData.cbCalTables += cbData)
	{
		nTablesData.SetSize(sData.cbCalTables + (cbData = (m_szCalTables.GetAt(nTable).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nTablesData.GetData() + sData.cbCalTables, (LPCTSTR)m_szCalTables.GetAt(nTable), cbData);
	}
	for (nInfo.SetSize((sData.cbSize[0] = sizeof(DATA) + sData.cbTag + sData.cbPacket[0] + sData.cbPacket[1] + sData.cbPacket[2] + sData.cbValues[0] + sData.cbValues[1] + sData.cbStatus + sData.cbCalTables)), sData.cbSize[1] = sizeof(DATA), sData.tPacket[0] = m_tPacket[0].GetTime(), sData.tPacket[1] = m_tPacket[1].GetTime(), sData.tPacket[2] = m_tOolTime.GetTime(), sData.wOolInfo[0] = m_wOolInfo[0], sData.wOolInfo[1] = m_wOolInfo[1], sData.nOolCount = m_nOolCount, sData.wPastSamples[0] = m_wPastSamples[0], sData.wPastSamples[1] = m_wPastSamples[1]; nInfo.GetSize() == sData.cbSize[0]; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szTag, sData.cbTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTag), (LPCTSTR)m_szPacket[0], sData.cbPacket[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPacket[0]), (LPCTSTR)m_szPacket[1], sData.cbPacket[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPacket[1]), (LPCTSTR)m_szOolUnit, sData.cbPacket[2]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPacket[2]), m_nValues.GetData(), sData.cbValues[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbValues[0]), nValuesData.GetData(), sData.cbValues[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbValues[1]), m_nStatus.GetData(), sData.cbStatus);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbStatus), nTablesData.GetData(), sData.cbCalTables);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMParameter::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbTable;
	INT  cbTables;
	CByteArray  nTablesData;
	CByteArray  nValuesData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize[0] && sData.cbSize[1] == sizeof(DATA) && sData.cbSize[0] == sizeof(DATA) + sData.cbTag + sData.cbPacket[0] + sData.cbPacket[1] + sData.cbPacket[2] + sData.cbValues[0] + sData.cbValues[1] + sData.cbStatus + sData.cbCalTables && sData.cbTag > 0 && sData.cbPacket[0] > 0 && sData.cbPacket[1] > 0 && sData.cbPacket[2] > 0 && sData.cbValues[0] >= 0 && sData.cbValues[1] >= 0 && sData.cbStatus >= 0 && sData.cbCalTables >= 0; )
	{
		CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbTag));
		CopyMemory(m_szPacket[0].GetBufferSetLength(STRINGCHARS(sData.cbPacket[0])), nInfo.GetData() + (cbData = cbData + sData.cbTag), STRINGBYTES(sData.cbPacket[0]));
		CopyMemory(m_szPacket[1].GetBufferSetLength(STRINGCHARS(sData.cbPacket[1])), nInfo.GetData() + (cbData = cbData + sData.cbPacket[0]), STRINGBYTES(sData.cbPacket[1]));
		CopyMemory(m_szOolUnit.GetBufferSetLength(STRINGCHARS(sData.cbPacket[2])), nInfo.GetData() + (cbData = cbData + sData.cbPacket[1]), STRINGBYTES(sData.cbPacket[2]));
		for (m_nValues.SetSize(sData.cbValues[0] / sizeof(ULONGLONG)), m_nStatus.SetSize(sData.cbStatus / sizeof(UINT)), nValuesData.SetSize(sData.cbValues[1]), nTablesData.SetSize(sData.cbCalTables / sizeof(BYTE)), CopyMemory(m_nValues.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbPacket[2]), sData.cbValues[0]), CopyMemory(nValuesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbValues[0]), sData.cbValues[1]), CopyMemory(m_nStatus.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbValues[1]), sData.cbStatus), CopyMemory(nTablesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbStatus), sData.cbCalTables), m_tPacket[0] = sData.tPacket[0], m_tPacket[1] = sData.tPacket[1], m_tOolTime = sData.tPacket[2], m_wOolInfo[0] = sData.wOolInfo[0], m_wOolInfo[1] = sData.wOolInfo[1], m_nOolCount = sData.nOolCount, m_wPastSamples[0] = sData.wPastSamples[0], m_wPastSamples[1] = sData.wPastSamples[1], m_tValues.Unmap(nValuesData), m_szTag.ReleaseBuffer(), m_szPacket[0].ReleaseBuffer(), m_szPacket[1].ReleaseBuffer(), m_szOolUnit.ReleaseBuffer(), m_szCalTables.RemoveAll(), cbTable = cbTables = 0; cbTables < sData.cbCalTables; cbTables += (cbTable = (m_szCalTables.GetAt(m_szCalTables.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szCalTables.Add((LPCTSTR)(nTablesData.GetData() + cbTables));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameters

CTMParameters::CTMParameters() : CPtrArray()
{
	return;
}

CTMParameters::~CTMParameters()
{
	RemoveAll();
}

BOOL CTMParameters::Create(CONST CDatabaseEngine *pDatabase)
{
	INT  nParameter;
	INT  nParameters;
	CTMUnit  cTMUnit;
	CUIntArray  nCalTableRefs;
	CUIntArray  nCalValidityRefs;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (nParameter = 0, nParameters = (INT)pDatabase->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(nParameter))) ? new CTMParameter : (CTMParameter *)NULL))
		{
			for (pTMParameter->SetTag(pDatabaseTMParameter->GetTag()), pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes()); pDatabaseTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
			{
				pTMParameter->SetRawValue(&cTMUnit, 0, pDatabaseTMParameter->GetConstValue(), TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID, (pDatabaseTMParameter->GetCalTableRefs(nCalTableRefs, nCalValidityRefs) > 0) ? ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (((pDatabaseTMNumCalTable = pDatabase->GetTMNumCalTables()->GetAt(nCalTableRefs.GetAt(0)))) ? (LPCTSTR)pDatabaseTMNumCalTable->GetName() : EMPTYSTRING) : (((pDatabaseTMTxtCalTable = pDatabase->GetTMTxtCalTables()->GetAt(nCalTableRefs.GetAt(0)))) ? (LPCTSTR)pDatabaseTMTxtCalTable->GetName() : EMPTYSTRING)) : EMPTYSTRING);
				break;
			}
			if (Add(pTMParameter) >= 0) continue;
			delete pTMParameter;
		}
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTMParameters::Update(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CONST CTMParameters *pTMParameters, BOOL bBadData)
{
	INT  nIndex;
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter[3];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	BOOL  bUpdate = FALSE;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter[1] = ((pTMParameter[0] = GetAt(nParameter))) ? pTMParameters->GetAt((nIndex = pTMParameters->Find(pTMParameter[0]->GetTag()))) : (CTMParameter *)NULL) && (pTMUnit->GetTag() == STRING(IDS_TMUNIT_INTERACTIVE) || pTMParameter[1]->IsInitialized()))
		{
			if (!pTMUnit->IsValid() || !pTMParameter[0]->IsInitialized() || (pTMParameter[1]->GetLastUpdateTMUnit() == pTMUnit->GetTag() && pTMParameter[1]->GetLastUpdateTime() == pTMUnit->GetTimeTag()))
			{
				bUpdate = (!pTMUnit->IsValid() || !pTMUnit->HasBadData() || bBadData) ? (pTMParameter[0]->Update(pTMParameter[1], bBadData) || bUpdate) : bUpdate;
				continue;
			}
			if ((pTMParameter[2] = ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(nIndex)) && pDatabaseTMParameter->GetValidityParameterRef() >= 0) ? pTMParameters->GetAt(pDatabaseTMParameter->GetValidityParameterRef()) : (CTMParameter *)NULL) && pTMParameter[2]->GetLastUpdateTMUnit() == pTMUnit->GetTag() && pTMParameter[2]->GetLastUpdateTime() == pTMUnit->GetTimeTag() && pTMParameter[0]->GetValueCount() + pTMParameter[0]->GetPastValueSamples() > 0)
			{
				bUpdate = (!pTMUnit->HasBadData() || bBadData) ? (pTMParameter[0]->Update(pTMParameter[1], bBadData) || bUpdate) : bUpdate;
				continue;
			}
		}
	}
	return bUpdate;
}

INT CTMParameters::Add(CTMParameter *pTMParameter)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTMParameter->GetTag(), TRUE)) >= 0) InsertAt(nIndex, pTMParameter, 1);
	return nIndex;
}

INT CTMParameters::Find(LPCTSTR pszTag) CONST
{
	return FindIndex(pszTag);
}

CTMParameter *CTMParameters::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMParameter *)CPtrArray::GetAt(nIndex) : (CTMParameter *)NULL);
}

CTMParameter *CTMParameters::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMParameter *)CPtrArray::GetAt(nIndex) : (CTMParameter *)NULL);
}

VOID CTMParameters::Reset()
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = GetAt(nParameter)))
		{
			pTMParameter->Reset();
			continue;
		}
	}
}

VOID CTMParameters::RemoveAll()
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = GetAt(nParameter))) delete pTMParameter;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTMParameters::Copy(CONST CTMParameters *pTMParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter;

	for (nParameter = 0, nParameters = (INT)pTMParameters->GetSize(), RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = new CTMParameter) != (CTMParameter *)NULL)
		{
			pTMParameter->Copy(pTMParameters->GetAt(nParameter));
			InsertAt(nParameter, pTMParameter, 1);
			continue;
		}
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTMParameters::Compare(CONST CTMParameters *pTMParameters) CONST
{
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (pTMParameters->GetSize() == GetSize()) ? (INT)GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if (!pTMParameters->GetAt(nParameter)->Compare(GetAt(nParameter))) break;
		continue;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTMParameters::Map(CByteArray &nInfo, CONST CTimeTag &tRetention, BOOL bAll) CONST
{
	INT  nParameter;
	INT  nParameters;
	CByteArray  nParameterData;
	CTMParameter  *pTMParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(), nInfo.RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = GetAt(nParameter)) && ((!bAll  &&  !pTMParameter->IsInitialized()) || (pTMParameter->GetRetention() != (TIMEKEY)-1 && tRetention != (TIMETAG)-1 && (!pTMParameter->GetRetention().GetTotalSeconds() || tRetention.GetTimeInSeconds() - pTMParameter->GetLastUpdateTime().GetTimeInSeconds() > pTMParameter->GetRetention().GetTotalSeconds())) || (pTMParameter->Map(nParameterData) && nInfo.Append(nParameterData) >= 0))) continue;
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTMParameters::Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention, BOOL bAll)
{
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nParameterData;
	CTMParameter  *pTMParameter[2];

	for (cbParameters = 0, Reset(); cbParameters < nInfo.GetSize(); cbParameters += cbParameter)
	{
		for (CopyMemory(&cbParameter, nInfo.GetData() + cbParameters, sizeof(cbParameter)), nParameterData.SetSize(max(min(cbParameter, nInfo.GetSize() - cbParameters), 0)); nParameterData.GetSize() >= 0; )
		{
			CopyMemory(nParameterData.GetData(), nInfo.GetData() + cbParameters, nParameterData.GetSize());
			break;
		}
		if ((pTMParameter[0] = new CTMParameter))
		{
			if (pTMParameter[0]->Unmap(nParameterData))
			{
				if (pTMParameter[0]->GetRetention() == (TIMEKEY)-1 || tRetention == (TIMETAG)-1 || tRetention.GetTimeInSeconds() - pTMParameter[0]->GetLastUpdateTime().GetTimeInSeconds() <= pTMParameter[0]->GetRetention().GetTotalSeconds())
				{
					if ((pTMParameter[1] = GetAt(FindIndex(pTMParameter[0]->GetTag()))))
					{
						pTMParameter[1]->Update(pTMParameter[0]);
						delete pTMParameter[0];
						continue;
					}
					if (bAll  &&  Add(pTMParameter[0]) >= 0) continue;
				}
				delete pTMParameter[0];
				continue;
			}
			delete pTMParameter[0];
		}
		break;
	}
	return((cbParameters == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTMParameters::FindIndex(LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTMParameter  *pTMParameter;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pTMParameter = GetAt(nIndex[0]))) ? ((nIndex[1] = (pTMParameter->GetTag() <= pszTag)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pTMParameter = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pTMParameter->GetTag() == pszTag) || (bInsert && (((pTMParameter = GetAt(max(nIndex[0] - 1, 0))) && pTMParameter->GetTag() != pszTag && (pTMParameter = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pTMParameter->GetTag() != pszTag) || !GetSize()))) && lstrlen(pszTag) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// COolParameter

VOID COolParameter::SetOolTMUnit(LPCTSTR pszUnit)
{
	m_szOolUnit = pszUnit;
}

CString COolParameter::GetOolTMUnit() CONST
{
	return m_szOolUnit;
}

VOID COolParameter::SetOolTime(CONST CTimeTag &tTime)
{
	m_tOolTime = tTime;
}

CTimeTag COolParameter::GetOolTime() CONST
{
	return m_tOolTime;
}


/////////////////////////////////////////////////////////////////////////////
// COolParameters

COolParameters::COolParameters() : CTMParameters()
{
	return;
}

COolParameters::~COolParameters()
{
	RemoveAll();
}

INT COolParameters::Add(COolParameter *pOolParameter)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pOolParameter)) >= 0)
	{
		InsertAt(nIndex, pOolParameter, 1);
		return nIndex;
	}
	if (abs(nIndex) < GetSize())
	{
		delete GetAt(abs(nIndex));
		SetAt(abs(nIndex), pOolParameter);
		return abs(nIndex);
	}
	return -1;
}

INT COolParameters::Find(LPCTSTR pszTag) CONST
{
	INT  nParameter;
	INT  nParameters;
	COolParameter  *pOolParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter = GetAt(nParameter)) && pOolParameter->GetTag() == pszTag) break;
		continue;
	}
	return((nParameter < nParameters) ? nParameter : -1);
}

COolParameter *COolParameters::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COolParameter *)CPtrArray::GetAt(nIndex) : (COolParameter *)NULL);
}

COolParameter *COolParameters::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COolParameter *)CPtrArray::GetAt(nIndex) : (COolParameter *)NULL);
}

VOID COolParameters::RemoveAll()
{
	INT  nParameter;
	INT  nParameters;
	COolParameter  *pOolParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter = GetAt(nParameter))) delete pOolParameter;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL COolParameters::Copy(CONST COolParameters *pOolParameters)
{
	INT  nParameter;
	INT  nParameters;
	COolParameter  *pOolParameter;

	for (nParameter = 0, nParameters = (INT)pOolParameters->GetSize(), RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter = new COolParameter) != (COolParameter *)NULL)
		{
			pOolParameter->Copy(pOolParameters->GetAt(nParameter));
			InsertAt(nParameter, pOolParameter, 1);
			continue;
		}
		RemoveAll();
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL COolParameters::Compare(CONST COolParameters *pOolParameters) CONST
{
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (pOolParameters->GetSize() == GetSize()) ? (INT)GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if (!pOolParameters->GetAt(nParameter)->Compare(GetAt(nParameter))) break;
		continue;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

INT COolParameters::FindIndex(COolParameter *pOolParameter) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if ((GetAt(nIndex)->GetOolTime() == pOolParameter->GetOolTime() && GetAt(nIndex)->GetTag() < pOolParameter->GetTag()) || GetAt(nIndex)->GetOolTime() < pOolParameter->GetOolTime())
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return((nIndex < GetSize()) ? ((GetAt(nIndex)->GetTag() == pOolParameter->GetTag()) ? -nIndex : nIndex) : nIndex);
}


/////////////////////////////////////////////////////////////////////////////
// COversamplingParameter

COversamplingParameter::COversamplingParameter() : CTMParameter()
{
	return;
}

BOOL COversamplingParameter::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	CByteArray  nData;

	sData.cbData = (CTMParameter::Map(nData)) ? (INT)nData.GetSize() : -1;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + max(sData.cbData, 0))), sData.nAttributes = m_nAttributes; nInfo.GetSize() == sData.cbSize && sData.cbData >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), nData.GetData(), sData.cbData);
		return TRUE;
	}
	return FALSE;
}

BOOL COversamplingParameter::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	CByteArray  nData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbData && sData.cbData >= 0; )
	{
		for (nData.SetSize(sData.cbData), CopyMemory(nData.GetData(), nInfo.GetData() + sizeof(DATA), sData.cbData), m_nAttributes = sData.nAttributes; CTMParameter::Unmap(nData); ) return TRUE;
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// COversamplingParameters

COversamplingParameters::COversamplingParameters() : CTMParameters()
{
	m_tTimeTag = 0;
	m_fSamplingRate = 0.0;
}

COversamplingParameters::~COversamplingParameters()
{
	RemoveAll();
}

VOID COversamplingParameters::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString COversamplingParameters::GetTag() CONST
{
	return m_szTag;
}

VOID COversamplingParameters::SetTimeTag(CONST CTimeTag &tTimeTag)
{
	m_tTimeTag = tTimeTag;
}

CTimeTag COversamplingParameters::GetTimeTag() CONST
{
	return m_tTimeTag;
}

VOID COversamplingParameters::SetData(CONST CByteArray &nData)
{
	m_nData.Copy(nData);
}

INT COversamplingParameters::GetData(CByteArray &nData) CONST
{
	nData.Copy(m_nData);
	return((INT)nData.GetSize());
}

VOID COversamplingParameters::SetSamplingRate(double fRate)
{
	m_fSamplingRate = fRate;
}

double COversamplingParameters::GetSamplingRate() CONST
{
	return m_fSamplingRate;
}

INT COversamplingParameters::Add(COversamplingParameter *pOversamplingParameter)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pOversamplingParameter->GetTag(), TRUE)) >= 0) InsertAt(nIndex, pOversamplingParameter, 1);
	return nIndex;
}

INT COversamplingParameters::Find(LPCTSTR pszTag) CONST
{
	return FindIndex(pszTag);
}

COversamplingParameter *COversamplingParameters::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COversamplingParameter *)CPtrArray::GetAt(nIndex) : (COversamplingParameter *)NULL);
}

COversamplingParameter *COversamplingParameters::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COversamplingParameter *)CPtrArray::GetAt(nIndex) : (COversamplingParameter *)NULL);
}

VOID COversamplingParameters::RemoveAll()
{
	INT  nParameter;
	INT  nParameters;
	COversamplingParameter  *pOversamplingParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(), m_szTag.Empty(), m_tTimeTag = 0, m_nData.RemoveAll(), m_fSamplingRate = 0.0; nParameter < nParameters; nParameter++)
	{
		if ((pOversamplingParameter = GetAt(nParameter))) delete pOversamplingParameter;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL COversamplingParameters::Copy(CONST COversamplingParameters *pOversamplingParameters)
{
	INT  nParameter;
	INT  nParameters;
	COversamplingParameter  *pOversamplingParameter;

	for (nParameter = 0, nParameters = (INT)pOversamplingParameters->GetSize(), RemoveAll(), m_szTag = pOversamplingParameters->m_szTag, m_tTimeTag = pOversamplingParameters->m_tTimeTag, m_nData.Copy(pOversamplingParameters->m_nData), m_fSamplingRate = pOversamplingParameters->m_fSamplingRate; nParameter < nParameters; nParameter++)
	{
		if ((pOversamplingParameter = new COversamplingParameter) != (COversamplingParameter *)NULL)
		{
			pOversamplingParameter->Copy(pOversamplingParameters->GetAt(nParameter));
			InsertAt(nParameter, pOversamplingParameter, 1);
			continue;
		}
		RemoveAll();
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL COversamplingParameters::Compare(CONST COversamplingParameters *pOversamplingParameters) CONST
{
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (pOversamplingParameters->m_szTag == m_szTag && pOversamplingParameters->m_tTimeTag == m_tTimeTag && pOversamplingParameters->m_nData.GetSize() == m_nData.GetSize() && !memcmp(pOversamplingParameters->m_nData.GetData(), m_nData.GetData(), m_nData.GetSize()) && pOversamplingParameters->m_fSamplingRate == m_fSamplingRate && pOversamplingParameters->GetSize() == GetSize()) ? (INT)GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if (!pOversamplingParameters->GetAt(nParameter)->Compare(GetAt(nParameter))) break;
		continue;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL COversamplingParameters::Map(CByteArray &nInfo, CONST CTimeTag &tRetention) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nParameterData;
	COversamplingParameter  *pOversamplingParameter;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	sData.cbData = (INT)(m_nData.GetSize()*sizeof(BYTE));
	for (nParameter = 0, nParameters = (INT)GetSize(), nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbTag + sData.cbData + (sData.cbParameters = 0))), sData.tTimeTag = m_tTimeTag.GetTime(), sData.fSamplingRate = m_fSamplingRate; nParameter < nParameters; nParameter++)
	{
		if ((pOversamplingParameter = GetAt(nParameter)) && ((pOversamplingParameter->GetRetention() != (TIMEKEY)-1 && tRetention != (TIMETAG)-1 && (!pOversamplingParameter->GetRetention().GetTotalSeconds() || tRetention.GetTimeInSeconds() - pOversamplingParameter->GetLastUpdateTime().GetTimeInSeconds() > pOversamplingParameter->GetRetention().GetTotalSeconds())) || (pOversamplingParameter->Map(nParameterData) && nInfo.Append(nParameterData) >= 0)))
		{
			sData.cbParameters += (INT)nParameterData.GetSize();
			sData.cbSize += (INT)nParameterData.GetSize();
			nParameterData.RemoveAll();
			continue;
		}
		break;
	}
	if (nParameter == nParameters)
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szTag, sData.cbTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTag), m_nData.GetData(), sData.cbData);
		return TRUE;
	}
	nInfo.RemoveAll();
	return FALSE;
}

BOOL COversamplingParameters::Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention)
{
	DATA  sData;
	INT  cbData;
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nParameterData;
	COversamplingParameter  *pOversamplingParameter;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0), RemoveAll(); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbTag + sData.cbData + sData.cbParameters && sData.cbTag > 0 && sData.cbData >= 0 && sData.cbParameters >= 0; )
	{
		for (m_nData.SetSize(sData.cbData / sizeof(BYTE)), CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbTag)), CopyMemory(m_nData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbTag), sData.cbData), cbParameters = cbData + sData.cbData, m_tTimeTag = sData.tTimeTag, m_fSamplingRate = sData.fSamplingRate, m_szTag.ReleaseBuffer(); cbParameters < nInfo.GetSize(); cbParameters += cbParameter)
		{
			for (CopyMemory(&cbParameter, nInfo.GetData() + cbParameters, sizeof(cbParameter)), nParameterData.SetSize(max(min(cbParameter, nInfo.GetSize() - cbParameters), 0)); nParameterData.GetSize() >= 0; )
			{
				CopyMemory(nParameterData.GetData(), nInfo.GetData() + cbParameters, nParameterData.GetSize());
				break;
			}
			if ((pOversamplingParameter = new COversamplingParameter))
			{
				if (pOversamplingParameter->Unmap(nParameterData))
				{
					if (pOversamplingParameter->GetRetention() == (TIMEKEY)-1 || tRetention == (TIMETAG)-1 || tRetention.GetTimeInSeconds() - pOversamplingParameter->GetLastUpdateTime().GetTimeInSeconds() <= pOversamplingParameter->GetRetention().GetTotalSeconds())
					{
						InsertAt(GetSize(), pOversamplingParameter, 1);
						continue;
					}
					delete pOversamplingParameter;
					continue;
				}
				delete pOversamplingParameter;
			}
		}
		break;
	}
	return((cbParameters == nInfo.GetSize()) ? TRUE : FALSE);
}

INT COversamplingParameters::FindIndex(LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	COversamplingParameter  *pOversamplingParameter;

	for (nIndex = nMinIndex = 0, nMaxIndex = (lstrlen(pszTag) > 0) ? (INT)GetSize() : -1; nIndex < nMaxIndex; nIndex++)
	{
		if ((pOversamplingParameter = GetAt(nIndex)) && pOversamplingParameter->GetTag() == pszTag) break;
		continue;
	}
	return((((bInsert  &&  nIndex == nMaxIndex) || (!bInsert  &&  nIndex < nMaxIndex)) && nMaxIndex >= 0) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameter

CTCParameter::CTCParameter() : CObject()
{
	m_nAttributes = 0;
	m_tTime[0] = 0;
	m_tTime[1] = 0;
	m_tOolTime = 0;
	m_wOolInfo[0] = -1;
	m_wOolInfo[1] = -1;
	m_nOolCount = 0;
}

VOID CTCParameter::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CTCParameter::GetTag() CONST
{
	return m_szTag;
}

VOID CTCParameter::SetAttributes(ULONGLONG nAttributes)
{
	m_nAttributes = nAttributes;
}

ULONGLONG CTCParameter::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CTCParameter::Initialize(CTCParameter *pTCParameter)
{
	Update(pTCParameter);
}

BOOL CTCParameter::IsInitialized() CONST
{
	return((m_tTime[0] > 0 && m_tTime[1] > 0) ? TRUE : FALSE);
}

BOOL CTCParameter::Update(CONST CTCParameter *pTCParameter)
{
	if (pTCParameter->m_nValues.GetSize() == pTCParameter->m_nStatus.GetSize() || pTCParameter->m_tValues.GetSize() == pTCParameter->m_nStatus.GetSize())
	{
		m_tTime[0] = pTCParameter->m_tTime[0];
		m_tTime[1] = pTCParameter->m_tTime[1];
		m_nValues.Copy(pTCParameter->m_nValues);
		m_tValues.Copy(pTCParameter->m_tValues);
		m_nStatus.Copy(pTCParameter->m_nStatus);
		m_tOolTime = pTCParameter->m_tOolTime.GetTime();
		m_wOolInfo[0] = pTCParameter->m_wOolInfo[0];
		m_wOolInfo[1] = pTCParameter->m_wOolInfo[1];
		m_nOolCount = pTCParameter->m_nOolCount;
		return TRUE;
	}
	return FALSE;
}

VOID CTCParameter::Reset()
{
	m_tTime[0] = 0;
	m_tTime[1] = 0;
	m_nValues.RemoveAll();
	m_tValues.RemoveAll();
	m_nStatus.RemoveAll();
	m_tOolTime = 0;
	m_wOolInfo[0] = -1;
	m_wOolInfo[1] = -1;
	m_nOolCount = 0;
}

BOOL CTCParameter::SetRawValue(INT nSample, ULONGLONG nRawValue, UINT nStatus)
{
	CTimeTag  tTime;

	if (nSample >= 0)
	{
		for (; m_nValues.GetSize() <= nSample || m_nStatus.GetSize() <= nSample || m_nStatus.GetAt(nSample) == TCPARAMETER_STATUS_NONE || m_nValues.GetAt(nSample) != nRawValue; )
		{
			m_tTime[0] = tTime;
			break;
		}
		m_tTime[1] = tTime;
		m_nValues.SetAtGrow(nSample, nRawValue);
		m_nStatus.SetAtGrow(nSample, (nStatus == TCPARAMETER_STATUS_NONE) ? ((nSample < m_nStatus.GetSize()) ? m_nStatus.GetAt(nSample) : TCPARAMETER_STATUS_NOLIMIT) : nStatus);
		return((m_nValues.GetSize() == m_nStatus.GetSize()) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL CTCParameter::SetRawValue(INT nSample, CONST CTimeTag &tRawValue, UINT nStatus)
{
	CTimeTag  tTime;

	if (nSample >= 0)
	{
		for (; m_tValues.GetSize() <= nSample || m_nStatus.GetSize() <= nSample || m_nStatus.GetAt(nSample) == TCPARAMETER_STATUS_NONE || m_tValues.GetAt(nSample) != tRawValue; )
		{
			m_tTime[0] = tTime;
			break;
		}
		m_tTime[1] = tTime;
		m_tValues.SetAtGrow(nSample, tRawValue);
		m_nStatus.SetAtGrow(nSample, (nStatus == TCPARAMETER_STATUS_NONE) ? ((nSample < m_nStatus.GetSize()) ? m_nStatus.GetAt(nSample) : TCPARAMETER_STATUS_NOLIMIT) : nStatus);
		return((m_tValues.GetSize() == m_nStatus.GetSize()) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCParameter::GetRawValue(INT nSample, ULONGLONG &nRawValue, UINT &nStatus) CONST
{
	if (nSample >= 0 && nSample < m_nValues.GetSize() && m_nStatus.GetAt(nSample) != TCPARAMETER_STATUS_NONE)
	{
		nRawValue = m_nValues.GetAt(nSample);
		nStatus = m_nStatus.GetAt(nSample);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCParameter::GetRawValue(INT nSample, CTimeTag &tRawValue, UINT &nStatus) CONST
{
	if (nSample >= 0 && nSample < m_tValues.GetSize() && m_nStatus.GetAt(nSample) != TCPARAMETER_STATUS_NONE)
	{
		tRawValue = m_tValues.GetAt(nSample);
		nStatus = m_nStatus.GetAt(nSample);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCParameter::Calibrate(CONST CDatabaseEngine *pDatabase, ULONGLONG nFlags, ULONGLONG nRawValue, double &fValue, BOOL &bOut) CONST
{
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	for (fValue = 0.0, bOut = FALSE; nFlags & TCPARAMETER_CODING_SIGNEDINTEGER; )
	{
		if ((pDatabaseTCParameter = pDatabase->GetTCParameters()->GetAt(pDatabase->GetTCParameters()->Find(m_szTag))))
		{
			nRawValue = CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, pDatabaseTCParameter->GetWidth(), nRawValue);
			break;
		}
		return FALSE;
	}
	if ((nFlags & TCPARAMETER_CALIBRATION_DISABLED) == 0)
	{
		if (nFlags & TCPARAMETER_CALIBRATION_NUMERICAL)
		{
			if ((pDatabaseTCParameter = pDatabase->GetTCParameters()->GetAt(pDatabase->GetTCParameters()->Find(m_szTag))))
			{
				if ((pDatabaseTCNumCalTable = pDatabase->GetTCNumCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef())))
				{
					if ((nFlags & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
					{
						fValue = pDatabaseTCNumCalTable->Calibrate((double)(LONGLONG)nRawValue, ((nFlags & TCPARAMETER_INTERPRETATION_FULL) != TCPARAMETER_INTERPRETATION_FULL) ? TRUE : FALSE, bOut);
						return TRUE;
					}
					if (nFlags & TCPARAMETER_CODING_FLOATINGPOINT)
					{
						fValue = pDatabaseTCNumCalTable->Calibrate(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue), ((nFlags & TCPARAMETER_INTERPRETATION_FULL) != TCPARAMETER_INTERPRETATION_FULL) ? TRUE : FALSE, bOut);
						return TRUE;
					}
					fValue = pDatabaseTCNumCalTable->Calibrate((double)nRawValue, ((nFlags & TCPARAMETER_INTERPRETATION_FULL) != TCPARAMETER_INTERPRETATION_FULL) ? TRUE : FALSE, bOut);
					return TRUE;
				}
			}
		}
	}
	if (nFlags & TCPARAMETER_CODING_BITPATTERN)
	{
		fValue = (double)nRawValue;
		return TRUE;
	}
	if (nFlags & TCPARAMETER_CODING_SIGNEDINTEGER)
	{
		fValue = (double)(LONGLONG)nRawValue;
		return TRUE;
	}
	if (nFlags & TCPARAMETER_CODING_UNSIGNEDINTEGER)
	{
		fValue = (double)nRawValue;
		return TRUE;
	}
	if (nFlags & TCPARAMETER_CODING_FLOATINGPOINT)
	{
		fValue = CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue) CONST
{
	BOOL  bOut;

	return GetValue(pDatabase, nSample, GetAttributes(), fValue, bOut);
}
BOOL CTCParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue, BOOL &bOut) CONST
{
	return GetValue(pDatabase, nSample, GetAttributes(), fValue, bOut);
}
BOOL CTCParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue) CONST
{
	BOOL  bOut;

	return GetValue(pDatabase, nSample, nFlags, fValue, bOut);
}
BOOL CTCParameter::GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue, BOOL &bOut) CONST
{
	UINT  nStatus;
	ULONGLONG  nRawValue;

	return((GetRawValue(nSample, nRawValue, nStatus)) ? Calibrate(pDatabase, nFlags, nRawValue, fValue, bOut) : FALSE);
}

BOOL CTCParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue) CONST
{
	BOOL  bOut;

	return GetValueAsText(pDatabase, nSample, GetAttributes(), -1, szValue, bOut);
}
BOOL CTCParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue, BOOL &bOut) CONST
{
	return GetValueAsText(pDatabase, nSample, GetAttributes(), -1, szValue, bOut);
}
BOOL CTCParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue) CONST
{
	BOOL  bOut;

	return GetValueAsText(pDatabase, nSample, nFlags, -1, szValue, bOut);
}
BOOL CTCParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue, BOOL &bOut) CONST
{
	return GetValueAsText(pDatabase, nSample, nFlags, -1, szValue, bOut);
}
BOOL CTCParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue) CONST
{
	BOOL  bOut;

	return GetValueAsText(pDatabase, nSample, nFlags, nDigits, szValue, bOut);
}
BOOL CTCParameter::GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue, BOOL &bOut) CONST
{
	UINT  nStatus;
	CString  szFormat;
	CTimeTag  tRawValue;
	ULONGLONG  nRawValue;
	CStringTools  cStringTools;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	for (szValue.Empty(), bOut = FALSE; GetRawValue(nSample, nRawValue, nStatus); )
	{
		for (; (nFlags & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER; )
		{
			if ((pDatabaseTCParameter = pDatabase->GetTCParameters()->GetAt(pDatabase->GetTCParameters()->Find(m_szTag))))
			{
				nRawValue = CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, pDatabaseTCParameter->GetWidth(), nRawValue);
				break;
			}
			return FALSE;
		}
		if ((nFlags & TCPARAMETER_CALIBRATION_DISABLED) == 0)
		{
			if (nFlags & TCPARAMETER_CALIBRATION_NUMERICAL)
			{
				if ((pDatabaseTCParameter = pDatabase->GetTCParameters()->GetAt(pDatabase->GetTCParameters()->Find(m_szTag))))
				{
					if ((pDatabaseTCNumCalTable = pDatabase->GetTCNumCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef())))
					{
						if ((nFlags & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
						{
							szValue = pDatabaseTCNumCalTable->CalibrateAsText((double)(LONGLONG)nRawValue, nDigits, ((nFlags & TCPARAMETER_INTERPRETATION_FULL) != TCPARAMETER_INTERPRETATION_FULL) ? TRUE : FALSE, bOut);
							return TRUE;
						}
						if (nFlags & TCPARAMETER_CODING_FLOATINGPOINT)
						{
							szValue = pDatabaseTCNumCalTable->CalibrateAsText(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue), nDigits, ((nFlags & TCPARAMETER_INTERPRETATION_FULL) != TCPARAMETER_INTERPRETATION_FULL) ? TRUE : FALSE, bOut);
							return TRUE;
						}
						szValue = pDatabaseTCNumCalTable->CalibrateAsText((double)nRawValue, nDigits, ((nFlags & TCPARAMETER_INTERPRETATION_FULL) != TCPARAMETER_INTERPRETATION_FULL) ? TRUE : FALSE, bOut);
						return TRUE;
					}
				}
			}
			if (nFlags & TCPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTCParameter = pDatabase->GetTCParameters()->GetAt(pDatabase->GetTCParameters()->Find(m_szTag))))
				{
					if ((pDatabaseTCTxtCalTable = pDatabase->GetTCTxtCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? pDatabase->GetTCTxtCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef())))
					{
						if ((nFlags & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
						{
							szValue = pDatabaseTCTxtCalTable->Translate((double)(LONGLONG)nRawValue, nDigits, bOut);
							return TRUE;
						}
						if (nFlags & TCPARAMETER_CODING_FLOATINGPOINT)
						{
							szValue = pDatabaseTCTxtCalTable->Translate(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue), nDigits, bOut);
							return TRUE;
						}
						szValue = pDatabaseTCTxtCalTable->Translate((double)nRawValue, nDigits, bOut);
						return TRUE;
					}
				}
			}
		}
		if (((nFlags & TCPARAMETER_CODING_UNSIGNEDINTEGER) && (nFlags & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL))) || (nFlags & TCPARAMETER_CODING_BITPATTERN))
		{
			if ((nFlags & TCPARAMETER_RADIX_BINARY) || (nFlags & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0)
			{
				for (szValue = cStringTools.ConvertLongUIntToString(nRawValue, 2); nDigits < szValue.GetLength() && nDigits > 0; )
				{
					szValue = szValue.Left(nDigits);
					break;
				}
				return TRUE;
			}
			if (nFlags & TCPARAMETER_RADIX_OCTAL)
			{
				for (szValue = cStringTools.ConvertLongUIntToString(nRawValue, 8); nDigits < szValue.GetLength() && nDigits > 0; )
				{
					szValue = szValue.Left(nDigits);
					break;
				}
				return TRUE;
			}
			if (nFlags & TCPARAMETER_RADIX_DECIMAL)
			{
				for (szValue = cStringTools.ConvertLongUIntToString(nRawValue, 10); nDigits < szValue.GetLength() && nDigits > 0; )
				{
					szValue = szValue.Left(nDigits);
					break;
				}
				return TRUE;
			}
			if (nFlags & TCPARAMETER_RADIX_HEXADECIMAL)
			{
				for (szValue = cStringTools.ConvertLongUIntToString(nRawValue, 16); nDigits < szValue.GetLength() && nDigits > 0; )
				{
					szValue = szValue.Left(nDigits);
					break;
				}
				return TRUE;
			}
		}
		if (nFlags & TCPARAMETER_CODING_SIGNEDINTEGER)
		{
			for (szValue = cStringTools.ConvertLongIntToString(nRawValue, 10); nDigits < szValue.GetLength() && nDigits > 0; )
			{
				szValue = szValue.Left(nDigits);
				break;
			}
			return TRUE;
		}
		if (nFlags & TCPARAMETER_CODING_UNSIGNEDINTEGER)
		{
			for (szValue = cStringTools.ConvertLongUIntToString(nRawValue, 10); nDigits < szValue.GetLength() && nDigits > 0; )
			{
				szValue = szValue.Left(nDigits);
				break;
			}
			return TRUE;
		}
		if (nFlags & TCPARAMETER_CODING_FLOATINGPOINT)
		{
			szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::DecodeValue(pDatabase->GetType(), nFlags, nRawValue), nDigits);
			return TRUE;
		}
		break;
	}
	if (GetRawValue(nSample, tRawValue, nStatus))
	{
		szValue = ((szFormat = szValue).GetLength() > 0) ? tRawValue.FormatGmt(szFormat) : tRawValue.FormatGmt();
		return TRUE;
	}
	return FALSE;
}

INT CTCParameter::GetValueCount() CONST
{
	return((INT)max(m_nValues.GetSize(), m_tValues.GetSize()));
}

VOID CTCParameter::SetOolInfo()
{
	m_tOolTime = 0;
	m_wOolInfo[0] = -1;
	m_wOolInfo[1] = -1;
}
VOID CTCParameter::SetOolInfo(CONST CTimeTag &tOolTime, WORD wTable, WORD wLimit)
{
	m_tOolTime = tOolTime;
	m_wOolInfo[0] = wTable;
	m_wOolInfo[1] = wLimit;
}

BOOL CTCParameter::GetOolInfo(CTimeTag &tOolTime, WORD &wTable, WORD &wLimit) CONST
{
	tOolTime = m_tOolTime;
	wTable = m_wOolInfo[0];
	wLimit = m_wOolInfo[1];
	return((tOolTime > 0 || wTable != (WORD)-1 || wLimit != (WORD)-1) ? TRUE : FALSE);
}

VOID CTCParameter::SetOolCount(INT nCount)
{
	m_nOolCount = nCount;
}

INT CTCParameter::GetOolCount() CONST
{
	return m_nOolCount;
}

CTimeTag CTCParameter::GetLastChangeTime() CONST
{
	return m_tTime[0];
}

CTimeTag CTCParameter::GetLastUpdateTime() CONST
{
	return m_tTime[1];
}

BOOL CTCParameter::Copy(CONST CTCParameter *pTCParameter)
{
	m_szTag = pTCParameter->m_szTag;
	m_tTime[0] = pTCParameter->m_tTime[0];
	m_tTime[1] = pTCParameter->m_tTime[1];
	m_nValues.Copy(pTCParameter->m_nValues);
	m_tValues.Copy(pTCParameter->m_tValues);
	m_nStatus.Copy(pTCParameter->m_nStatus);
	m_nAttributes = pTCParameter->m_nAttributes;
	m_tOolTime = pTCParameter->m_tOolTime;
	m_wOolInfo[0] = pTCParameter->m_wOolInfo[0];
	m_wOolInfo[1] = pTCParameter->m_wOolInfo[1];
	m_nOolCount = pTCParameter->m_nOolCount;
	return TRUE;
}

BOOL CTCParameter::Compare(CONST CTCParameter *pTCParameter) CONST
{
	INT  nOccurrence;
	INT  nOccurrences;

	for (nOccurrence = 0, nOccurrences = (pTCParameter->m_szTag == m_szTag && pTCParameter->m_nAttributes == m_nAttributes && pTCParameter->m_tTime[0] == m_tTime[0] && pTCParameter->m_tTime[1] == m_tTime[1] && pTCParameter->m_nValues.GetSize() == m_nValues.GetSize() && pTCParameter->m_tValues.GetSize() == m_tValues.GetSize() && pTCParameter->m_tValues.Compare(m_tValues) && pTCParameter->m_nStatus.GetSize() == m_nStatus.GetSize() && (m_nValues.GetSize() == m_nStatus.GetSize() || m_tValues.GetSize() == m_nStatus.GetSize()) && pTCParameter->m_tOolTime == m_tOolTime && pTCParameter->m_wOolInfo[0] == m_wOolInfo[0] && pTCParameter->m_wOolInfo[1] == m_wOolInfo[1] && pTCParameter->m_nOolCount == m_nOolCount) ? (INT)m_nValues.GetSize() : -1; nOccurrence < nOccurrences; nOccurrence++)
	{
		if (pTCParameter->m_nValues.GetAt(nOccurrence) != m_nValues.GetAt(nOccurrence) || pTCParameter->m_nStatus.GetAt(nOccurrence) != m_nStatus.GetAt(nOccurrence)) break;
		continue;
	}
	return((nOccurrence == nOccurrences) ? TRUE : FALSE);
}

BOOL CTCParameter::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nValuesData;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	sData.cbStatus = (INT)m_nStatus.GetSize()*sizeof(UINT);
	sData.cbValues[0] = (INT)m_nValues.GetSize()*sizeof(ULONGLONG);
	sData.cbValues[1] = (INT)m_tValues.Map(nValuesData)*sizeof(BYTE);
	for (nInfo.SetSize((sData.cbSize[0] = sizeof(DATA) + sData.cbTag + sData.cbValues[0] + sData.cbValues[1] + sData.cbStatus)), sData.cbSize[1] = sizeof(DATA), sData.nAttributes = m_nAttributes, sData.tTime[0] = m_tTime[0].GetTime(), sData.tTime[1] = m_tTime[1].GetTime(), sData.tTime[2] = m_tOolTime.GetTime(), sData.wOolInfo[0] = m_wOolInfo[0], sData.wOolInfo[1] = m_wOolInfo[1], sData.nOolCount = m_nOolCount; nInfo.GetSize() == sData.cbSize[0] && sData.cbValues[0] >= 0 && sData.cbValues[1] >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szTag, sData.cbTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTag), m_nValues.GetData(), sData.cbValues[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbValues[0]), nValuesData.GetData(), sData.cbValues[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbValues[1]), m_nStatus.GetData(), sData.cbStatus);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCParameter::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nValuesData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize[0] && sData.cbSize[1] == sizeof(DATA) && sData.cbSize[0] == sizeof(DATA) + sData.cbTag + sData.cbValues[0] + sData.cbValues[1] + sData.cbStatus && sData.cbTag > 0 && sData.cbValues[0] >= 0 && sData.cbValues[1] >= 0 && sData.cbStatus >= 0; )
	{
		for (m_nValues.SetSize(sData.cbValues[0] / sizeof(ULONGLONG)), nValuesData.SetSize(sData.cbValues[1] / sizeof(BYTE)), m_nStatus.SetSize(sData.cbStatus / sizeof(UINT)); m_nValues.GetSize() == sData.cbValues[0] / sizeof(UINT) && m_nStatus.GetSize() == sData.cbStatus / sizeof(UINT); )
		{
			CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbTag));
			CopyMemory(m_nValues.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbTag), sData.cbValues[0]);
			CopyMemory(nValuesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbValues[0]), sData.cbValues[1]);
			CopyMemory(m_nStatus.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbValues[1]), sData.cbStatus);
			m_nAttributes = sData.nAttributes;
			m_tTime[0] = sData.tTime[0];
			m_tTime[1] = sData.tTime[1];
			m_tOolTime = sData.tTime[2];
			m_wOolInfo[0] = sData.wOolInfo[0];
			m_wOolInfo[1] = sData.wOolInfo[1];
			m_nOolCount = sData.nOolCount;
			m_szTag.ReleaseBuffer();
			return m_tValues.Unmap(nValuesData);
		}
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameters

CTCParameters::CTCParameters() : CPtrArray()
{
	return;
}

CTCParameters::~CTCParameters()
{
	RemoveAll();
}

BOOL CTCParameters::Create(CONST CDatabaseEngine *pDatabase)
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  *pDatabaseTCParameter;

	for (nParameter = 0, nParameters = (INT)pDatabase->GetTCParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTCParameter = pDatabase->GetTCParameters()->GetAt(nParameter)))
		{
			if ((pTCParameter = new CTCParameter) != (CTCParameter *)NULL)
			{
				pTCParameter->SetTag(pDatabaseTCParameter->GetTag());
				pTCParameter->SetAttributes(pDatabaseTCParameter->GetAttributes());
				if (Add(pTCParameter) >= 0) continue;
				delete pTCParameter;
			}
		}
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

INT CTCParameters::Add(CTCParameter *pTCParameter)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTCParameter->GetTag(), TRUE)) >= 0) InsertAt(nIndex, pTCParameter, 1);
	return nIndex;
}

INT CTCParameters::Find(LPCTSTR pszTag) CONST
{
	return FindIndex(pszTag);
}

CTCParameter *CTCParameters::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCParameter *)CPtrArray::GetAt(nIndex) : (CTCParameter *)NULL);
}

CTCParameter *CTCParameters::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCParameter *)CPtrArray::GetAt(nIndex) : (CTCParameter *)NULL);
}

VOID CTCParameters::Reset()
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTCParameter = GetAt(nParameter)))
		{
			pTCParameter->Reset();
			continue;
		}
	}
}

VOID CTCParameters::RemoveAll()
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTCParameter = GetAt(nParameter))) delete pTCParameter;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCParameters::Copy(CONST CTCParameters *pTCParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter;

	for (nParameter = 0, nParameters = (INT)pTCParameters->GetSize(), RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pTCParameter = new CTCParameter) != (CTCParameter *)NULL)
		{
			pTCParameter->Copy(pTCParameters->GetAt(nParameter));
			InsertAt(nParameter, pTCParameter, 1);
			continue;
		}
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTCParameters::Compare(CONST CTCParameters *pTCParameters) CONST
{
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (pTCParameters->GetSize() == GetSize()) ? (INT)GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if (!pTCParameters->GetAt(nParameter)->Compare(GetAt(nParameter))) break;
		continue;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTCParameters::Map(CByteArray &nInfo, BOOL bAll) CONST
{
	INT  nParameter;
	INT  nParameters;
	CByteArray  nParameterData;
	CTCParameter  *pTCParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(), nInfo.RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pTCParameter = GetAt(nParameter)) && ((!bAll  &&  !pTCParameter->IsInitialized()) || (pTCParameter->Map(nParameterData) && nInfo.Append(nParameterData) >= 0))) continue;
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTCParameters::Unmap(CONST CByteArray &nInfo, BOOL bAll)
{
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nParameterData;
	CTCParameter  *pTCParameter[2];

	for (cbParameters = 0, Reset(); cbParameters < nInfo.GetSize(); cbParameters += cbParameter)
	{
		for (CopyMemory(&cbParameter, nInfo.GetData() + cbParameters, sizeof(cbParameter)), nParameterData.SetSize(max(min(cbParameter, nInfo.GetSize() - cbParameters), 0)); nParameterData.GetSize() >= 0; )
		{
			CopyMemory(nParameterData.GetData(), nInfo.GetData() + cbParameters, nParameterData.GetSize());
			break;
		}
		if ((pTCParameter[0] = new CTCParameter))
		{
			if (pTCParameter[0]->Unmap(nParameterData))
			{
				if ((pTCParameter[1] = GetAt(FindIndex(pTCParameter[0]->GetTag()))))
				{
					pTCParameter[1]->Update(pTCParameter[0]);
					delete pTCParameter[0];
					continue;
				}
				if (bAll  &&  Add(pTCParameter[0]) >= 0) continue;
				delete pTCParameter[0];
				continue;
			}
			delete pTCParameter[0];
		}
		break;
	}
	return((cbParameters == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCParameters::FindIndex(LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTCParameter  *pTCParameter;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pTCParameter = GetAt(nIndex[0]))) ? ((nIndex[1] = (pTCParameter->GetTag() <= pszTag)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pTCParameter = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pTCParameter->GetTag() == pszTag) || (bInsert && (((pTCParameter = GetAt(max(nIndex[0] - 1, 0))) && pTCParameter->GetTag() != pszTag && (pTCParameter = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pTCParameter->GetTag() != pszTag) || !GetSize()))) && lstrlen(pszTag) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CMemoryDump

CMemoryDump::CMemoryDump() : CObject()
{
	m_nFileFormats[0] = 0;
	m_nFileFormats[1] = 0;
	m_nDataSource[0] = 0;
	m_nDataSource[1] = 0;
	m_nDataAddress[0][0] = 0;
	m_nDataAddress[0][1] = 0;
	m_nDataAddress[1][0] = 0;
	m_nDataAddress[1][1] = 0;
	m_nDataBitWidth[0] = 0;
	m_nDataBitWidth[1] = 0;
	m_nRetentionOptions[0] = 0;
	m_nRetentionOptions[1] = 0;
	m_nRetentionCount[0] = 0;
	m_nRetentionCount[1] = 0;
	m_nRetentionCount[2] = 0;
	m_nRetentionCount[3] = 0;
	m_tRetention[0] = 0;
	m_tRetention[1] = 0;
	m_bAudition = FALSE;
	m_tDumpTime[0] = 0;
	m_tDumpTime[1] = 0;
	m_wDumpQuality = MEMORYDUMP_DATAQUALITY_NONE;
	m_nDumpStatus = MEMORYDUMP_STATUS_EMPTY;
	m_nFTPPort = 0;
	m_nFTPRetries[0] = 0;
	m_nFTPRetries[1] = 0;
	m_tFTPRetryTime = 0;
	m_tFTPRetryInterval = 0;
	m_nFTPAudition = 0;
	m_bFTPQueue = FALSE;
}

VOID CMemoryDump::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CMemoryDump::GetName() CONST
{
	return m_szName;
}

VOID CMemoryDump::SetFileName(LPCTSTR pszFileName)
{
	m_szFileName = pszFileName;
}

CString CMemoryDump::GetFileName() CONST
{
	return m_szFileName;
}

BOOL CMemoryDump::SetFileExtension(UINT nFormat, LPCTSTR pszFileExtension)
{
	if (nFormat == MEMORYDUMP_FILEFORMAT_NORMAL)
	{
		m_szFileExtensions[0] = pszFileExtension;
		return TRUE;
	}
	if (nFormat == MEMORYDUMP_FILEFORMAT_DESCRIPTIVE)
	{
		m_szFileExtensions[1] = pszFileExtension;
		return TRUE;
	}
	if (nFormat == MEMORYDUMP_FILEFORMAT_DELIMITED)
	{
		m_szFileExtensions[2] = pszFileExtension;
		return TRUE;
	}
	return FALSE;
}

BOOL CMemoryDump::GetFileExtension(UINT nFormat, CString &szFileExtension) CONST
{
	if (nFormat == MEMORYDUMP_FILEFORMAT_NORMAL)
	{
		szFileExtension = m_szFileExtensions[0];
		return TRUE;
	}
	if (nFormat == MEMORYDUMP_FILEFORMAT_DESCRIPTIVE)
	{
		szFileExtension = m_szFileExtensions[1];
		return TRUE;
	}
	if (nFormat == MEMORYDUMP_FILEFORMAT_DELIMITED)
	{
		szFileExtension = m_szFileExtensions[2];
		return TRUE;
	}
	return FALSE;
}

VOID CMemoryDump::SetOutputFiles(LPCTSTR pszFiles)
{
	m_szOutputFiles = pszFiles;
}

CString CMemoryDump::GetOutputFiles() CONST
{
	return m_szOutputFiles;
}

VOID CMemoryDump::SetFTPServer(LPCTSTR pszServer)
{
	m_szFTPServer = pszServer;
}

CString CMemoryDump::GetFTPServer() CONST
{
	return m_szFTPServer;
}

VOID CMemoryDump::SetFTPDirectory(LPCTSTR pszDirectory)
{
	m_szFTPDirectory = pszDirectory;
}

CString CMemoryDump::GetFTPDirectory() CONST
{
	return m_szFTPDirectory;
}

VOID CMemoryDump::SetFTPUserName(LPCTSTR pszUserName)
{
	m_szFTPUserName = pszUserName;
}

CString CMemoryDump::GetFTPUserName() CONST
{
	return m_szFTPUserName;
}

VOID CMemoryDump::SetFTPPassword(LPCTSTR pszPassword)
{
	m_szFTPPassword = pszPassword;
}

CString CMemoryDump::GetFTPPassword() CONST
{
	return m_szFTPPassword;
}

VOID CMemoryDump::SetFTPPort(UINT nPort)
{
	m_nFTPPort = nPort;
}

UINT CMemoryDump::GetFTPPort() CONST
{
	return m_nFTPPort;
}

VOID CMemoryDump::SetDataSource(UINT nSource)
{
	m_nDataSource[0] = nSource;
}

UINT CMemoryDump::GetDataSource() CONST
{
	return m_nDataSource[0];
}

VOID CMemoryDump::SetDataSourceSubSystem(UINT nSubSystem)
{
	m_nDataSource[1] = nSubSystem;
}

UINT CMemoryDump::GetDataSourceSubSystem() CONST
{
	return m_nDataSource[1];
}

BOOL CMemoryDump::SetDataAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress)
{
	m_nDataAddress[0][0] = nStartPage;
	m_nDataAddress[0][1] = nStartAddress;
	m_nDataAddress[1][0] = nEndPage;
	m_nDataAddress[1][1] = nEndAddress;
	return((nStartPage < nEndPage || (nStartPage == nEndPage  &&  nStartAddress <= nEndAddress)) ? TRUE : FALSE);
}

BOOL CMemoryDump::GetDataAddressRange(UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST
{
	nStartPage = m_nDataAddress[0][0];
	nStartAddress = m_nDataAddress[0][1];
	nEndPage = m_nDataAddress[1][0];
	nEndAddress = m_nDataAddress[1][1];
	return((nStartPage < nEndPage || (nStartPage == nEndPage  &&  nStartAddress <= nEndAddress)) ? TRUE : FALSE);
}

VOID CMemoryDump::SetDataAddressBitWidth(UINT nWidth)
{
	m_nDataBitWidth[0] = nWidth;
}

UINT CMemoryDump::GetDataAddressBitWidth() CONST
{
	return m_nDataBitWidth[0];
}

VOID CMemoryDump::SetDataBitWidth(UINT nWidth)
{
	m_nDataBitWidth[1] = nWidth;
}

UINT CMemoryDump::GetDataBitWidth() CONST
{
	return m_nDataBitWidth[1];
}

VOID CMemoryDump::SetAuditionFlag(BOOL bFlag)
{
	m_bAudition = bFlag;
}

BOOL CMemoryDump::GetAuditionFlag() CONST
{
	return m_bAudition;
}

VOID CMemoryDump::SetArchivingFileFormats(UINT nFormats)
{
	m_nFileFormats[0] = nFormats;
}

UINT CMemoryDump::GetArchivingFileFormats() CONST
{
	return m_nFileFormats[0];
}

VOID CMemoryDump::SetArchivingRetentionOptions(UINT nOptions)
{
	m_nRetentionOptions[0] = nOptions;
}

UINT CMemoryDump::GetArchivingRetentionOptions() CONST
{
	return m_nRetentionOptions[0];
}

VOID CMemoryDump::SetArchivingRetentionByCount(UINT nCount)
{
	m_nRetentionCount[0] = nCount;
	m_nRetentionCount[1] = nCount;
}

UINT CMemoryDump::GetArchivingRetentionByCount() CONST
{
	return m_nRetentionCount[0];
}

VOID CMemoryDump::SetArchivingRetentionByTime(CONST CTimeKey &tTime)
{
	m_tRetention[0] = tTime;
}

CTimeKey CMemoryDump::GetArchivingRetentionByTime() CONST
{
	return m_tRetention[0];
}

VOID CMemoryDump::SetArchivingRetentionCount(UINT nCount)
{
	m_nRetentionCount[1] = nCount;
}

UINT CMemoryDump::GetArchivingRetentionCount() CONST
{
	return m_nRetentionCount[1];
}

VOID CMemoryDump::SetNotificationsFileFormats(UINT nFormats)
{
	m_nFileFormats[1] = nFormats;
}

UINT CMemoryDump::GetNotificationsFileFormats() CONST
{
	return m_nFileFormats[1];
}

VOID CMemoryDump::SetNotificationsRetentionOptions(UINT nOptions)
{
	m_nRetentionOptions[1] = nOptions;
}

UINT CMemoryDump::GetNotificationsRetentionOptions() CONST
{
	return m_nRetentionOptions[1];
}

VOID CMemoryDump::SetNotificationsRetentionByCount(UINT nCount)
{
	m_nRetentionCount[2] = nCount;
	m_nRetentionCount[3] = nCount;
}

UINT CMemoryDump::GetNotificationsRetentionByCount() CONST
{
	return m_nRetentionCount[2];
}

VOID CMemoryDump::SetNotificationsRetentionByTime(CONST CTimeKey &tTime)
{
	m_tRetention[1] = tTime;
}

CTimeKey CMemoryDump::GetNotificationsRetentionByTime() CONST
{
	return m_tRetention[1];
}

VOID CMemoryDump::SetNotificationsRetentionCount(UINT nCount)
{
	m_nRetentionCount[3] = nCount;
}

UINT CMemoryDump::GetNotificationsRetentionCount() CONST
{
	return m_nRetentionCount[3];
}

BOOL CMemoryDump::SetDumpInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, CONST CByteArray &nData, WORD wQuality)
{
	return SetDumpInfo(pszTag, m_szDumpVersion, tTag, m_nDataAddress[0][0], m_nDataAddress[0][1], nData, wQuality);
}
BOOL CMemoryDump::SetDumpInfo(LPCTSTR pszTag, LPCTSTR pszVersion, CONST CTimeTag &tTag, CONST CByteArray &nData, WORD wQuality)
{
	return SetDumpInfo(pszTag, pszVersion, tTag, m_nDataAddress[0][0], m_nDataAddress[0][1], nData, wQuality);
}
BOOL CMemoryDump::SetDumpInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nPage, UINT nAddress, CONST CByteArray &nData, WORD wQuality)
{
	return SetDumpInfo(pszTag, m_szDumpVersion, tTag, nPage, nAddress, nData, wQuality);
}
BOOL CMemoryDump::SetDumpInfo(LPCTSTR pszTag, LPCTSTR pszVersion, CONST CTimeTag &tTag, UINT nPage, UINT nAddress, CONST CByteArray &nData, WORD wQuality)
{
	CByteArray  nDumpData;

	if ((m_nDumpStatus == MEMORYDUMP_STATUS_EMPTY || m_nDumpStatus == MEMORYDUMP_STATUS_COMPLETE || m_nDumpStatus == MEMORYDUMP_STATUS_INCOMPLETE) && nPage == m_nDataAddress[0][0] && nAddress == m_nDataAddress[0][1])
	{
		for (m_szDumpTag = pszTag, m_szDumpVersion.Empty(), m_tDumpTime[0] = m_tDumpTime[1] = tTag, m_nDumpData[0].Copy(nData), m_nDumpData[1].InsertAt(0, MEMORYDUMP_DATATYPE_NORMAL, m_nDumpData[0].GetSize()), m_nDumpData[1].SetSize(m_nDumpData[0].GetSize()), m_wDumpQuality = ((LOBYTE(wQuality) & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? MAKEWORD(MEMORYDUMP_DATAQUALITY_GOOD | ((LOBYTE(wQuality) & TMUNIT_TIMECORRELATION_GOOD) ? MEMORYDUMP_TIMECORRELATION_GOOD : MEMORYDUMP_TIMECORRELATION_BAD), HIBYTE(wQuality)) : MAKEWORD(MEMORYDUMP_DATAQUALITY_BAD | ((LOBYTE(wQuality) & TMUNIT_TIMECORRELATION_GOOD) ? MEMORYDUMP_TIMECORRELATION_GOOD : MEMORYDUMP_TIMECORRELATION_BAD), HIBYTE(wQuality)), m_nDumpStatus = (((ULONGLONG)m_nDataAddress[0][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[0][1] + (ULONGLONG)((m_nDumpData[0].GetSize() + max(m_nDataBitWidth[1] / 8 - 1, 0)) / max(m_nDataBitWidth[1] / 8, 1)) >= ((ULONGLONG)m_nDataAddress[1][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[1][1] + 1) ? MEMORYDUMP_STATUS_COMPLETE : MEMORYDUMP_STATUS_COLLECTING; m_nDumpStatus == MEMORYDUMP_STATUS_COMPLETE; )
		{
			for (m_szDumpVersion = pszVersion, m_nDumpData[0].SetSize((INT)((((ULONGLONG)m_nDataAddress[1][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[1][1] - ((ULONGLONG)m_nDataAddress[0][0] << m_nDataBitWidth[0]) - (ULONGLONG)m_nDataAddress[0][1] + 1)*max(m_nDataBitWidth[1] / 8, 1))), m_nDumpData[1].SetSize(m_nDumpData[0].GetSize()); memchr(m_nDumpData[1].GetData(), MEMORYDUMP_DATATYPE_ILLEGAL, m_nDumpData[1].GetSize()); )
			{
				m_nDumpStatus = MEMORYDUMP_STATUS_INCOMPLETE;
				break;
			}
			break;
		}
		return TRUE;
	}
	if (m_szDumpTag == pszTag  &&  m_nDumpStatus == MEMORYDUMP_STATUS_COLLECTING && ((nPage > m_nDataAddress[0][0] || (nPage == m_nDataAddress[0][0] && nAddress > m_nDataAddress[0][1])) && (nPage < m_nDataAddress[1][0] || (nPage == m_nDataAddress[1][0] && nAddress <= m_nDataAddress[1][1]))))
	{
		for (m_tDumpTime[1] = tTag, m_nDumpData[0].SetSize((INT)((((ULONGLONG)nPage << m_nDataBitWidth[0]) + (ULONGLONG)nAddress - ((ULONGLONG)m_nDataAddress[0][0] << m_nDataBitWidth[0]) - (ULONGLONG)m_nDataAddress[0][1])*max(m_nDataBitWidth[1] / 8, 1))), memset(m_nDumpData[0].GetData() + m_nDumpData[1].GetSize(), MEMORYDUMP_DATATYPE_TEMPLATE, max(m_nDumpData[0].GetSize() - m_nDumpData[1].GetSize(), 0)), nDumpData.SetSize(max(m_nDumpData[0].GetSize() - m_nDumpData[1].GetSize(), 0)), memset(nDumpData.GetData(), MEMORYDUMP_DATATYPE_ILLEGAL, nDumpData.GetSize()), m_nDumpData[1].Append(nDumpData), m_nDumpData[1].SetSize(m_nDumpData[0].GetSize()), m_nDumpData[0].Append(nData), m_nDumpData[1].InsertAt(m_nDumpData[1].GetSize(), MEMORYDUMP_DATATYPE_NORMAL, nData.GetSize()), m_wDumpQuality = (LOBYTE(m_wDumpQuality) & MEMORYDUMP_DATAQUALITY_GOOD) ? (((LOBYTE(wQuality) & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? MAKEWORD(MEMORYDUMP_DATAQUALITY_GOOD | (((LOBYTE(wQuality) & TMUNIT_TIMECORRELATION_GOOD) && (LOBYTE(m_wDumpQuality) & MEMORYDUMP_TIMECORRELATION_GOOD)) ? MEMORYDUMP_TIMECORRELATION_GOOD : MEMORYDUMP_TIMECORRELATION_BAD), HIBYTE(wQuality)) : MAKEWORD(MEMORYDUMP_DATAQUALITY_BAD | (((LOBYTE(wQuality) & TMUNIT_TIMECORRELATION_GOOD) && (LOBYTE(m_wDumpQuality) & MEMORYDUMP_TIMECORRELATION_GOOD)) ? MEMORYDUMP_TIMECORRELATION_GOOD : MEMORYDUMP_TIMECORRELATION_BAD), HIBYTE(wQuality))) : m_wDumpQuality, m_nDumpStatus = (((ULONGLONG)m_nDataAddress[0][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[0][1] + (ULONGLONG)((m_nDumpData[0].GetSize() + max(m_nDataBitWidth[1] / 8 - 1, 0)) / max(m_nDataBitWidth[1] / 8, 1)) >= ((ULONGLONG)m_nDataAddress[1][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[1][1] + 1) ? MEMORYDUMP_STATUS_COMPLETE : MEMORYDUMP_STATUS_COLLECTING; m_nDumpStatus == MEMORYDUMP_STATUS_COMPLETE; )
		{
			for (m_szDumpVersion = pszVersion, m_nDumpData[0].SetSize((INT)((((ULONGLONG)m_nDataAddress[1][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[1][1] - ((ULONGLONG)m_nDataAddress[0][0] << m_nDataBitWidth[0]) - (ULONGLONG)m_nDataAddress[0][1] + 1)*max(m_nDataBitWidth[1] / 8, 1))), m_nDumpData[1].SetSize(m_nDumpData[0].GetSize()); memchr(m_nDumpData[1].GetData(), MEMORYDUMP_DATATYPE_ILLEGAL, m_nDumpData[1].GetSize()); )
			{
				m_nDumpStatus = MEMORYDUMP_STATUS_INCOMPLETE;
				break;
			}
			break;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CMemoryDump::SetDumpInfo(CONST CMemoryDump *pMemoryDump, UINT nStatus)
{
	if (nStatus != MEMORYDUMP_STATUS_EMPTY)
	{
		m_szDumpTag = pMemoryDump->m_szDumpTag;
		m_szDumpVersion = pMemoryDump->m_szDumpVersion;
		m_tDumpTime[0] = pMemoryDump->m_tDumpTime[0];
		m_tDumpTime[1] = pMemoryDump->m_tDumpTime[1];
		m_nDumpData[0].Copy(pMemoryDump->m_nDumpData[0]);
		m_nDumpData[1].Copy(pMemoryDump->m_nDumpData[1]);
		m_wDumpQuality = pMemoryDump->m_wDumpQuality;
		m_nDumpStatus = pMemoryDump->m_nDumpStatus;
		return TRUE;
	}
	Copy(pMemoryDump);
	return SetDumpInfo(nStatus);
}
BOOL CMemoryDump::SetDumpInfo(UINT nStatus)
{
	ULONGLONG  cbDumpData;
	CByteArray  nDumpData[2];

	if ((m_nDumpStatus = nStatus) == MEMORYDUMP_STATUS_EMPTY)
	{
		m_szDumpTag.Empty();
		m_szDumpVersion.Empty();
		m_tDumpTime[0] = 0;
		m_tDumpTime[1] = 0;
		m_nDumpData[0].RemoveAll();
		m_nDumpData[1].RemoveAll();
		m_wDumpQuality = MEMORYDUMP_DATAQUALITY_NONE;
		return TRUE;
	}
	if (nStatus == MEMORYDUMP_STATUS_INCOMPLETE)
	{
		if ((cbDumpData = (((ULONGLONG)m_nDataAddress[1][0] << m_nDataBitWidth[0]) + (ULONGLONG)m_nDataAddress[1][1] - ((ULONGLONG)m_nDataAddress[0][0] << m_nDataBitWidth[0]) - (ULONGLONG)m_nDataAddress[0][1] + 1)*max(m_nDataBitWidth[1] / 8, 1)) > (ULONGLONG)m_nDumpData[0].GetSize())
		{
			nDumpData[0].SetSize((INT_PTR)cbDumpData - m_nDumpData[0].GetSize());
			nDumpData[1].SetSize((INT_PTR)cbDumpData - m_nDumpData[1].GetSize());
			memset(nDumpData[0].GetData(), MEMORYDUMP_DATATYPE_TEMPLATE, nDumpData[0].GetSize());
			memset(nDumpData[1].GetData(), MEMORYDUMP_DATATYPE_ILLEGAL, nDumpData[1].GetSize());
			m_nDumpData[0].Append(nDumpData[0]);
			m_nDumpData[1].Append(nDumpData[1]);
		}
	}
	return((nStatus == MEMORYDUMP_STATUS_COLLECTING || nStatus == MEMORYDUMP_STATUS_COMPLETE || nStatus == MEMORYDUMP_STATUS_INCOMPLETE) ? TRUE : FALSE);
}

CString CMemoryDump::GetDumpTag() CONST
{
	return m_szDumpTag;
}

CString CMemoryDump::GetDumpVersion() CONST
{
	return m_szDumpVersion;
}

CTimeTag CMemoryDump::GetDumpTime(BOOL bStart) CONST
{
	return((bStart) ? m_tDumpTime[0] : m_tDumpTime[1]);
}

INT CMemoryDump::GetDumpData(CByteArray &nData) CONST
{
	nData.Copy(m_nDumpData[0]);
	return((INT)nData.GetSize());
}

INT CMemoryDump::GetDumpMask(CByteArray &nMask) CONST
{
	nMask.Copy(m_nDumpData[1]);
	return((INT)nMask.GetSize());
}

WORD CMemoryDump::GetDumpQuality() CONST
{
	return m_wDumpQuality;
}

UINT CMemoryDump::GetDumpStatus() CONST
{
	return m_nDumpStatus;
}

BOOL CMemoryDump::SetFTPRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval)
{
	m_nFTPRetries[0] = nRetries;
	m_nFTPRetries[1] = nRetries;
	m_tFTPRetryInterval = tInterval;
	return(((!nRetries  &&  tInterval.GetTotalSeconds() == 0) || (nRetries > 0 && tInterval.GetTotalSeconds() > 0)) ? TRUE : FALSE);
}

BOOL CMemoryDump::GetFTPRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST
{
	nRetries = m_nFTPRetries[0];
	tInterval = m_tFTPRetryInterval;
	return(((!nRetries  &&  tInterval.GetTotalSeconds() == 0) || (nRetries > 0 && tInterval.GetTotalSeconds() > 0)) ? TRUE : FALSE);
}

VOID CMemoryDump::SetFTPRetryTime(CONST CTimeKey &tTime)
{
	m_tFTPRetryTime = tTime;
}

CTimeKey CMemoryDump::GetFTPRetryTime() CONST
{
	return m_tFTPRetryTime;
}

VOID CMemoryDump::SetFTPRetryCount(UINT nCount)
{
	m_nFTPRetries[1] = nCount;
}

UINT CMemoryDump::GetFTPRetryCount() CONST
{
	return m_nFTPRetries[1];
}

VOID CMemoryDump::SetFTPAudition(UINT nAudition)
{
	m_nFTPAudition = nAudition;
}

UINT CMemoryDump::GetFTPAudition() CONST
{
	return m_nFTPAudition;
}

VOID CMemoryDump::SetFTPQueueFlag(BOOL bFlag)
{
	m_bFTPQueue = bFlag;
}

BOOL CMemoryDump::GetFTPQueueFlag() CONST
{
	return m_bFTPQueue;
}

BOOL CMemoryDump::CheckFTPAddress() CONST
{
	DWORD  dwType;
	CString  szServer;
	CString  szAddress;
	CString  szDirectory;
	INTERNET_PORT  nPort;

	return(((szAddress = STRING(IDS_INTERNET_PROTOCOL_FTP) + m_szFTPServer + m_szFTPDirectory) != STRING(IDS_INTERNET_PROTOCOL_FTP) + m_szFTPDirectory  &&  AfxParseURL(szAddress, dwType, szServer, szDirectory, nPort) && dwType == AFX_INET_SERVICE_FTP) ? TRUE : FALSE);
}

VOID CMemoryDump::Empty()
{
	m_szName.Empty();
	m_szFileName.Empty();
	m_szFileExtensions[0].Empty();
	m_szFileExtensions[1].Empty();
	m_szFileExtensions[2].Empty();
	m_szOutputFiles.Empty();
	m_szDumpTag.Empty();
	m_szDumpVersion.Empty();
	m_szFTPServer.Empty();
	m_szFTPDirectory.Empty();
	m_szFTPUserName.Empty();
	m_szFTPPassword.Empty();
	m_nFileFormats[0] = 0;
	m_nFileFormats[1] = 0;
	m_nDataSource[0] = 0;
	m_nDataSource[1] = 0;
	m_nDataAddress[0][0] = 0;
	m_nDataAddress[0][1] = 0;
	m_nDataAddress[1][0] = 0;
	m_nDataAddress[1][1] = 0;
	m_nDataBitWidth[0] = 0;
	m_nDataBitWidth[1] = 0;
	m_nRetentionOptions[0] = 0;
	m_nRetentionOptions[1] = 0;
	m_nRetentionCount[0] = 0;
	m_nRetentionCount[1] = 0;
	m_nRetentionCount[2] = 0;
	m_nRetentionCount[3] = 0;
	m_tRetention[0] = 0;
	m_tRetention[1] = 0;
	m_bAudition = FALSE;
	m_tDumpTime[0] = 0;
	m_tDumpTime[1] = 0;
	m_nDumpData[0].RemoveAll();
	m_nDumpData[1].RemoveAll();
	m_nDumpStatus = MEMORYDUMP_STATUS_EMPTY;
	m_wDumpQuality = MEMORYDUMP_DATAQUALITY_NONE;
	m_nFTPPort = 0;
	m_nFTPRetries[0] = 0;
	m_nFTPRetries[1] = 0;
	m_tFTPRetryTime = 0;
	m_tFTPRetryInterval = 0;
	m_nFTPAudition = 0;
	m_bFTPQueue = FALSE;
}

VOID CMemoryDump::Copy(CONST CMemoryDump *pMemoryDump, BOOL bData)
{
	m_szName = pMemoryDump->m_szName;
	m_szFileName = pMemoryDump->m_szFileName;
	m_szFileExtensions[0] = pMemoryDump->m_szFileExtensions[0];
	m_szFileExtensions[1] = pMemoryDump->m_szFileExtensions[1];
	m_szFileExtensions[2] = pMemoryDump->m_szFileExtensions[2];
	m_szOutputFiles = pMemoryDump->m_szOutputFiles;
	m_szFTPServer = pMemoryDump->m_szFTPServer;
	m_szFTPDirectory = pMemoryDump->m_szFTPDirectory;
	m_szFTPUserName = pMemoryDump->m_szFTPUserName;
	m_szFTPPassword = pMemoryDump->m_szFTPPassword;
	m_nFileFormats[0] = pMemoryDump->m_nFileFormats[0];
	m_nFileFormats[1] = pMemoryDump->m_nFileFormats[1];
	m_nDataSource[0] = pMemoryDump->m_nDataSource[0];
	m_nDataSource[1] = pMemoryDump->m_nDataSource[1];
	m_nDataAddress[0][0] = pMemoryDump->m_nDataAddress[0][0];
	m_nDataAddress[0][1] = pMemoryDump->m_nDataAddress[0][1];
	m_nDataAddress[1][0] = pMemoryDump->m_nDataAddress[1][0];
	m_nDataAddress[1][1] = pMemoryDump->m_nDataAddress[1][1];
	m_nDataBitWidth[0] = pMemoryDump->m_nDataBitWidth[0];
	m_nDataBitWidth[1] = pMemoryDump->m_nDataBitWidth[1];
	m_nRetentionOptions[0] = pMemoryDump->m_nRetentionOptions[0];
	m_nRetentionOptions[1] = pMemoryDump->m_nRetentionOptions[1];
	m_nRetentionCount[0] = pMemoryDump->m_nRetentionCount[0];
	m_nRetentionCount[1] = pMemoryDump->m_nRetentionCount[1];
	m_nRetentionCount[2] = pMemoryDump->m_nRetentionCount[2];
	m_nRetentionCount[3] = pMemoryDump->m_nRetentionCount[3];
	m_tRetention[0] = pMemoryDump->m_tRetention[0];
	m_tRetention[1] = pMemoryDump->m_tRetention[1];
	m_bAudition = pMemoryDump->m_bAudition;
	m_nFTPPort = pMemoryDump->m_nFTPPort;
	m_nFTPRetries[0] = pMemoryDump->m_nFTPRetries[0];
	m_nFTPRetries[1] = pMemoryDump->m_nFTPRetries[1];
	m_tFTPRetryTime = pMemoryDump->m_tFTPRetryTime;
	m_tFTPRetryInterval = pMemoryDump->m_tFTPRetryInterval;
	m_nFTPAudition = pMemoryDump->m_nFTPAudition;
	m_bFTPQueue = pMemoryDump->m_bFTPQueue;
	m_szDumpTag = (bData) ? pMemoryDump->m_szDumpTag : m_szDumpTag;
	m_szDumpVersion = (bData) ? pMemoryDump->m_szDumpVersion : m_szDumpVersion;
	m_tDumpTime[0] = (bData) ? pMemoryDump->m_tDumpTime[0] : m_tDumpTime[0];
	m_tDumpTime[1] = (bData) ? pMemoryDump->m_tDumpTime[1] : m_tDumpTime[1];
	m_wDumpQuality = (bData) ? pMemoryDump->m_wDumpQuality : m_wDumpQuality;
	m_nDumpStatus = (bData) ? pMemoryDump->m_nDumpStatus : m_nDumpStatus;
	m_nDumpData[0].SetSize((bData) ? pMemoryDump->m_nDumpData[0].GetSize() : m_nDumpData[0].GetSize());
	m_nDumpData[1].SetSize((bData) ? pMemoryDump->m_nDumpData[1].GetSize() : m_nDumpData[1].GetSize());
	CopyMemory(m_nDumpData[0].GetData(), pMemoryDump->m_nDumpData[0].GetData(), (bData) ? pMemoryDump->m_nDumpData[0].GetSize() : 0);
	CopyMemory(m_nDumpData[1].GetData(), pMemoryDump->m_nDumpData[1].GetData(), (bData) ? pMemoryDump->m_nDumpData[1].GetSize() : 0);
}

BOOL CMemoryDump::Compare(CONST CMemoryDump *pMemoryDump, BOOL bData) CONST
{
	return((pMemoryDump->m_szName == m_szName  &&  !pMemoryDump->m_szFileName.CompareNoCase(m_szFileName) && !pMemoryDump->m_szFileExtensions[0].CompareNoCase(m_szFileExtensions[0]) && !pMemoryDump->m_szFileExtensions[1].CompareNoCase(m_szFileExtensions[1]) && !pMemoryDump->m_szFileExtensions[2].CompareNoCase(m_szFileExtensions[2]) && !pMemoryDump->m_szOutputFiles.CompareNoCase(m_szOutputFiles) && pMemoryDump->m_szFTPServer == m_szFTPServer  &&  pMemoryDump->m_szFTPDirectory == m_szFTPDirectory  &&  pMemoryDump->m_szFTPUserName == m_szFTPUserName  &&  pMemoryDump->m_szFTPPassword == m_szFTPPassword  &&  pMemoryDump->m_nFTPPort == m_nFTPPort  &&  pMemoryDump->m_nFileFormats[0] == m_nFileFormats[0] && pMemoryDump->m_nFileFormats[1] == m_nFileFormats[1] && pMemoryDump->m_nDataSource[0] == m_nDataSource[0] && pMemoryDump->m_nDataSource[1] == m_nDataSource[1] && pMemoryDump->m_nDataAddress[0][0] == m_nDataAddress[0][0] && pMemoryDump->m_nDataAddress[0][1] == m_nDataAddress[0][1] && pMemoryDump->m_nDataAddress[1][0] == m_nDataAddress[1][0] && pMemoryDump->m_nDataAddress[1][1] == m_nDataAddress[1][1] && pMemoryDump->m_nDataBitWidth[0] == m_nDataBitWidth[0] && pMemoryDump->m_nDataBitWidth[1] == m_nDataBitWidth[1] && pMemoryDump->m_nRetentionOptions[0] == m_nRetentionOptions[0] && pMemoryDump->m_nRetentionOptions[1] == m_nRetentionOptions[1] && pMemoryDump->m_nRetentionCount[0] == m_nRetentionCount[0] && pMemoryDump->m_nRetentionCount[2] == m_nRetentionCount[2] && pMemoryDump->m_tRetention[0] == m_tRetention[0] && pMemoryDump->m_tRetention[1] == m_tRetention[1] && pMemoryDump->m_bAudition == m_bAudition  &&  pMemoryDump->m_nFTPRetries[0] == m_nFTPRetries[0] && pMemoryDump->m_tFTPRetryInterval == m_tFTPRetryInterval  &&  pMemoryDump->m_nFTPAudition == m_nFTPAudition  &&  pMemoryDump->m_bFTPQueue == m_bFTPQueue && (!bData || (pMemoryDump->m_szDumpTag == m_szDumpTag  &&  pMemoryDump->m_szDumpVersion == m_szDumpVersion  &&  pMemoryDump->m_tDumpTime[0] == m_tDumpTime[0] && pMemoryDump->m_tDumpTime[1] == m_tDumpTime[1] && pMemoryDump->m_nDumpData[0].GetSize() == m_nDumpData[0].GetSize() && pMemoryDump->m_nDumpData[1].GetSize() == m_nDumpData[1].GetSize() && !memcmp(pMemoryDump->m_nDumpData[0].GetData(), m_nDumpData[0].GetData(), m_nDumpData[0].GetSize()) && !memcmp(pMemoryDump->m_nDumpData[1].GetData(), m_nDumpData[1].GetData(), m_nDumpData[1].GetSize()) && pMemoryDump->m_wDumpQuality == m_wDumpQuality  &&  pMemoryDump->m_nDumpStatus == m_nDumpStatus))) ? TRUE : FALSE);
}

BOOL CMemoryDump::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nPasswordData;
	CCryptographyTools  cCryptographyTools;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileName = (m_szFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileExtensions[0] = (m_szFileExtensions[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileExtensions[1] = (m_szFileExtensions[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileExtensions[2] = (m_szFileExtensions[2].GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPServer = (m_szFTPServer.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPDirectory = (m_szFTPDirectory.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPUserName = (m_szFTPUserName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPPassword = ((sData.cbFTPPassword = cCryptographyTools.EncryptText(m_szFTPPassword, nPasswordData)) <= 0) ? ((m_szFTPPassword.GetLength() + 1)*sizeof(TCHAR)) : sData.cbFTPPassword;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbFileName + sData.cbFileExtensions[0] + sData.cbFileExtensions[1] + sData.cbFileExtensions[2] + sData.cbFTPServer + sData.cbFTPDirectory + sData.cbFTPUserName + sData.cbFTPPassword + (sData.cbDumpTag = (m_bFTPQueue) ? ((m_szDumpTag.GetLength() + 1)*sizeof(TCHAR)) : sizeof(TCHAR)) + (sData.cbDumpVersion = (m_bFTPQueue) ? ((m_szDumpVersion.GetLength() + 1)*sizeof(TCHAR)) : sizeof(TCHAR)) + (sData.cbDumpData[0] = (m_bFTPQueue) ? (INT)m_nDumpData[0].GetSize() : 0) + (sData.cbDumpData[1] = (m_bFTPQueue) ? (INT)m_nDumpData[1].GetSize() : 0))), sData.nDataSource[0] = m_nDataSource[0], sData.nDataSource[1] = m_nDataSource[1], sData.nDataAddress[0][0] = m_nDataAddress[0][0], sData.nDataAddress[0][1] = m_nDataAddress[0][1], sData.nDataAddress[1][0] = m_nDataAddress[1][0], sData.nDataAddress[1][1] = m_nDataAddress[1][1], sData.nDataBitWidth[0] = m_nDataBitWidth[0], sData.nDataBitWidth[1] = m_nDataBitWidth[1], sData.nFileFormats[0] = m_nFileFormats[0], sData.nFileFormats[1] = m_nFileFormats[1], sData.nRetentionOptions[0] = m_nRetentionOptions[0], sData.nRetentionOptions[1] = m_nRetentionOptions[1], sData.nRetentionCount[0] = m_nRetentionCount[0], sData.nRetentionCount[1] = m_nRetentionCount[1], sData.nRetentionCount[2] = m_nRetentionCount[2], sData.nRetentionCount[3] = m_nRetentionCount[3], sData.tRetention[0] = m_tRetention[0].GetTime(), sData.tRetention[1] = m_tRetention[1].GetTime(), sData.bAudition = m_bAudition, sData.nFTPPort = m_nFTPPort, sData.nFTPAudition = m_nFTPAudition, sData.nFTPRetries[0] = m_nFTPRetries[0], sData.nFTPRetries[1] = m_nFTPRetries[1], sData.tFTPRetryTime = m_tFTPRetryTime.GetTime(), sData.tFTPRetryInterval = m_tFTPRetryInterval.GetTotalSeconds(), sData.bFTPQueue = m_bFTPQueue, sData.tDumpTime = (m_bFTPQueue) ? m_tDumpTime[0].GetTime() : 0, sData.nDumpStatus = (m_bFTPQueue) ? m_nDumpStatus : 0, sData.wDumpQuality = (m_bFTPQueue) ? m_wDumpQuality : MEMORYDUMP_DATAQUALITY_NONE; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szFileName, sData.cbFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileName), (LPCTSTR)m_szFileExtensions[0], sData.cbFileExtensions[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileExtensions[0]), (LPCTSTR)m_szFileExtensions[1], sData.cbFileExtensions[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileExtensions[1]), (LPCTSTR)m_szFileExtensions[2], sData.cbFileExtensions[2]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileExtensions[2]), (LPCTSTR)m_szFTPServer, sData.cbFTPServer);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPServer), (LPCTSTR)m_szFTPDirectory, sData.cbFTPDirectory);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPDirectory), (LPCTSTR)m_szFTPUserName, sData.cbFTPUserName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPUserName), (nPasswordData.GetSize() > 0) ? nPasswordData.GetData() : (LPCVOID)(LPCTSTR)m_szFTPPassword, sData.cbFTPPassword);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPPassword), (LPCTSTR)m_szDumpTag, sData.cbDumpTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDumpTag), (LPCTSTR)m_szDumpVersion, sData.cbDumpVersion);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDumpVersion), m_nDumpData[0].GetData(), sData.cbDumpData[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDumpData[0]), m_nDumpData[1].GetData(), sData.cbDumpData[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CMemoryDump::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nPasswordData;
	CCryptographyTools  cCryptographyTools;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbFileName + sData.cbFileExtensions[0] + sData.cbFileExtensions[1] + sData.cbFileExtensions[2] + sData.cbFTPServer + sData.cbFTPDirectory + sData.cbFTPUserName + sData.cbFTPPassword + sData.cbDumpTag + sData.cbDumpVersion + sData.cbDumpData[0] + sData.cbDumpData[1] && sData.cbName > 0 && sData.cbFileName > 0 && sData.cbFileExtensions[0] > 0 && sData.cbFileExtensions[1] > 0 && sData.cbFileExtensions[2] > 0 && sData.cbFTPServer > 0 && sData.cbFTPDirectory > 0 && sData.cbFTPUserName > 0 && sData.cbFTPPassword > 0 && sData.cbDumpTag > 0 && sData.cbDumpVersion > 0 && sData.cbDumpData[0] >= 0 && sData.cbDumpData[1] >= 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szFileName.GetBufferSetLength(STRINGCHARS(sData.cbFileName)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbFileName));
		CopyMemory(m_szFileExtensions[0].GetBufferSetLength(STRINGCHARS(sData.cbFileExtensions[0])), nInfo.GetData() + (cbData = cbData + sData.cbFileName), STRINGBYTES(sData.cbFileExtensions[0]));
		CopyMemory(m_szFileExtensions[1].GetBufferSetLength(STRINGCHARS(sData.cbFileExtensions[1])), nInfo.GetData() + (cbData = cbData + sData.cbFileExtensions[0]), STRINGBYTES(sData.cbFileExtensions[1]));
		CopyMemory(m_szFileExtensions[2].GetBufferSetLength(STRINGCHARS(sData.cbFileExtensions[2])), nInfo.GetData() + (cbData = cbData + sData.cbFileExtensions[1]), STRINGBYTES(sData.cbFileExtensions[2]));
		CopyMemory(m_szFTPServer.GetBufferSetLength(STRINGCHARS(sData.cbFTPServer)), nInfo.GetData() + (cbData = cbData + sData.cbFileExtensions[2]), STRINGBYTES(sData.cbFTPServer));
		CopyMemory(m_szFTPDirectory.GetBufferSetLength(STRINGCHARS(sData.cbFTPDirectory)), nInfo.GetData() + (cbData = cbData + sData.cbFTPServer), STRINGBYTES(sData.cbFTPDirectory));
		CopyMemory(m_szFTPUserName.GetBufferSetLength(STRINGCHARS(sData.cbFTPUserName)), nInfo.GetData() + (cbData = cbData + sData.cbFTPDirectory), STRINGBYTES(sData.cbFTPUserName));
		for (nPasswordData.SetSize(sData.cbFTPPassword), m_nDumpData[0].SetSize(sData.cbDumpData[0]), m_nDumpData[1].SetSize(sData.cbDumpData[1]); nPasswordData.GetSize() == sData.cbFTPPassword && m_nDumpData[0].GetSize() == sData.cbDumpData[0] && m_nDumpData[1].GetSize() == sData.cbDumpData[1]; )
		{
			for (CopyMemory(nPasswordData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFTPUserName), sData.cbFTPPassword), CopyMemory(m_szDumpTag.GetBufferSetLength(STRINGCHARS(sData.cbDumpTag)), nInfo.GetData() + (cbData = cbData + sData.cbFTPPassword), STRINGBYTES(sData.cbDumpTag)), CopyMemory(m_szDumpVersion.GetBufferSetLength(STRINGCHARS(sData.cbDumpVersion)), nInfo.GetData() + (cbData = cbData + sData.cbDumpTag), STRINGBYTES(sData.cbDumpVersion)), CopyMemory(m_nDumpData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDumpVersion), sData.cbDumpData[0]), CopyMemory(m_nDumpData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDumpData[0]), sData.cbDumpData[1]), m_nDataSource[0] = sData.nDataSource[0], m_nDataSource[1] = sData.nDataSource[1], m_nDataAddress[0][0] = sData.nDataAddress[0][0], m_nDataAddress[0][1] = sData.nDataAddress[0][1], m_nDataAddress[1][0] = sData.nDataAddress[1][0], m_nDataAddress[1][1] = sData.nDataAddress[1][1], m_nDataBitWidth[0] = sData.nDataBitWidth[0], m_nDataBitWidth[1] = sData.nDataBitWidth[1], m_nFileFormats[0] = sData.nFileFormats[0], m_nFileFormats[1] = sData.nFileFormats[1], m_nRetentionOptions[0] = sData.nRetentionOptions[0], m_nRetentionOptions[1] = sData.nRetentionOptions[1], m_nRetentionCount[0] = sData.nRetentionCount[0], m_nRetentionCount[1] = sData.nRetentionCount[1], m_nRetentionCount[2] = sData.nRetentionCount[2], m_nRetentionCount[3] = sData.nRetentionCount[3], m_tRetention[0] = sData.tRetention[0], m_tRetention[1] = sData.tRetention[1], m_bAudition = sData.bAudition, m_nFTPPort = sData.nFTPPort, m_nFTPAudition = sData.nFTPAudition, m_nFTPRetries[0] = sData.nFTPRetries[0], m_nFTPRetries[1] = sData.nFTPRetries[1], m_tFTPRetryTime = sData.tFTPRetryTime, m_tFTPRetryInterval = sData.tFTPRetryInterval; !cCryptographyTools.DecryptText(nPasswordData, m_szFTPPassword); )
			{
				m_szFTPPassword = (LPCTSTR)nPasswordData.GetData();
				break;
			}
			for (m_bFTPQueue = sData.bFTPQueue, m_tDumpTime[0] = m_tDumpTime[1] = 0, m_wDumpQuality = MEMORYDUMP_DATAQUALITY_NONE, m_nDumpStatus; m_bFTPQueue; )
			{
				m_tDumpTime[0] = m_tDumpTime[1] = sData.tDumpTime;
				m_wDumpQuality = sData.wDumpQuality;
				m_nDumpStatus = sData.nDumpStatus;
				break;
			}
			m_szName.ReleaseBuffer();
			m_szFileName.ReleaseBuffer();
			m_szFileExtensions[0].ReleaseBuffer();
			m_szFileExtensions[1].ReleaseBuffer();
			m_szFileExtensions[2].ReleaseBuffer();
			m_szFTPServer.ReleaseBuffer();
			m_szFTPDirectory.ReleaseBuffer();
			m_szFTPUserName.ReleaseBuffer();
			m_szDumpTag.ReleaseBuffer();
			m_szDumpVersion.ReleaseBuffer();
			return TRUE;
		}
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CMemoryDumps

CMemoryDumps::CMemoryDumps() : CMutexArray()
{
	return;
}

CMemoryDumps::~CMemoryDumps()
{
	RemoveAll();
}

INT CMemoryDumps::Add(CMemoryDump *pMemoryDump)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pMemoryDump->GetName(), TRUE)) >= 0) InsertAt(nIndex, pMemoryDump, 1);
	return nIndex;
}

INT CMemoryDumps::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CMemoryDumps::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CMemoryDump  *pMemoryDump;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pMemoryDump = GetAt(nProfile)) != (CMemoryDump *)NULL)
		{
			szNames.Add(pMemoryDump->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CMemoryDump *CMemoryDumps::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMemoryDump *)CMutexArray::GetAt(nIndex) : (CMemoryDump *)NULL);
}

CMemoryDump *CMemoryDumps::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMemoryDump *)CMutexArray::GetAt(nIndex) : (CMemoryDump *)NULL);
}

VOID CMemoryDumps::RemoveAll()
{
	INT  nDump;
	INT  nDumps;
	CMemoryDump  *pMemoryDump;

	for (nDump = 0, nDumps = (INT)GetSize(); nDump < nDumps; nDump++)
	{
		if ((pMemoryDump = GetAt(nDump))) delete pMemoryDump;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CMemoryDumps::Copy(CONST CMemoryDumps *pMemoryDumps, BOOL bData)
{
	INT  nDump;
	INT  nDumps;
	CMemoryDump  *pMemoryDump;

	for (nDump = 0, nDumps = (INT)pMemoryDumps->GetSize(), RemoveAll(); nDump < nDumps; nDump++)
	{
		if ((pMemoryDump = new CMemoryDump) != (CMemoryDump *)NULL)
		{
			pMemoryDump->Copy(pMemoryDumps->GetAt(nDump), bData);
			InsertAt(GetSize(), pMemoryDump, 1);
			continue;
		}
		break;
	}
	return((nDump == nDumps) ? TRUE : FALSE);
}

BOOL CMemoryDumps::Compare(CONST CMemoryDumps *pMemoryDumps, BOOL bData) CONST
{
	INT  nDump;
	INT  nDumps;

	for (nDump = 0, nDumps = (pMemoryDumps->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDump < nDumps; nDump++)
	{
		if (!pMemoryDumps->GetAt(nDump)->Compare(GetAt(nDump), bData)) break;
		continue;
	}
	return((nDump == nDumps) ? TRUE : FALSE);
}

BOOL CMemoryDumps::Map(CByteArray &nInfo) CONST
{
	INT  nDump;
	INT  nDumps;
	CByteArray  nDumpData;
	CMemoryDump  *pMemoryDump;

	for (nDump = 0, nDumps = (INT)GetSize(), nInfo.RemoveAll(); nDump < nDumps; nDump++)
	{
		if ((pMemoryDump = GetAt(nDump)) && (!pMemoryDump->GetDataSource() || (pMemoryDump->Map(nDumpData) && nInfo.Append(nDumpData) >= 0))) continue;
		break;
	}
	return((nDump == nDumps) ? TRUE : FALSE);
}

BOOL CMemoryDumps::Unmap(CONST CByteArray &nInfo)
{
	INT  cbDump;
	INT  cbDumps;
	CByteArray  nDumpData;
	CMemoryDump  *pMemoryDump;

	for (cbDumps = 0, RemoveAll(); cbDumps < nInfo.GetSize(); cbDumps += cbDump)
	{
		for (CopyMemory(&cbDump, nInfo.GetData() + cbDumps, sizeof(cbDump)), nDumpData.SetSize(max(min(cbDump, nInfo.GetSize() - cbDumps), 0)); nDumpData.GetSize() >= 0; )
		{
			CopyMemory(nDumpData.GetData(), nInfo.GetData() + cbDumps, nDumpData.GetSize());
			break;
		}
		if ((pMemoryDump = new CMemoryDump))
		{
			if (pMemoryDump->Unmap(nDumpData))
			{
				if (!pMemoryDump->GetDataSource())
				{
					delete pMemoryDump;
					continue;
				}
				if (Add(pMemoryDump) >= 0) continue;
			}
			delete pMemoryDump;
		}
		break;
	}
	return((cbDumps == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CMemoryDumps::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CMemoryDump  *pMemoryDump;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pMemoryDump = GetAt(nIndex[0]))) ? ((nIndex[1] = (pMemoryDump->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pMemoryDump = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pMemoryDump->GetName() == pszName) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPConnection

CTPEPConnection::CTPEPConnection() : CObject()
{
	Reset();
}

BOOL CTPEPConnection::SetType(UINT nType)
{
	if (nType == TPEP_TYPE_PACKETS || nType == TPEP_TYPE_PARAMETERS)
	{
		m_nType = nType;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetType() CONST
{
	return m_nType;
}

BOOL CTPEPConnection::SetDataMode(UINT nDataMode)
{
	if (nDataMode == TPEP_DATAMODE_REALTIME || nDataMode == TPEP_DATAMODE_HISTORY || nDataMode == TPEP_DATAMODE_RANDOM)
	{
		m_nDataMode = nDataMode;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetDataMode() CONST
{
	return m_nDataMode;
}

BOOL CTPEPConnection::SetDataLink(UINT nDataLink)
{
	if (nDataLink == TPEP_DATALINK_COLD || nDataLink == TPEP_DATALINK_HOT)
	{
		m_nDataLink = nDataLink;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetDataLink() CONST
{
	return m_nDataLink;
}

BOOL CTPEPConnection::SetDataType(UINT nDataType)
{
	if (nDataType == TPEP_DATATYPE_RAW || (nDataType >= TPEP_DATATYPE_PIE1  &&  nDataType <= TPEP_DATATYPE_PIE3))
	{
		m_nDataType = nDataType;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetDataType() CONST
{
	return m_nDataType;
}

BOOL CTPEPConnection::SetTriggerMode(UINT nTriggerMode)
{
	if (nTriggerMode == TPEP_TRIGGERMODE_UPDATE || nTriggerMode == TPEP_TRIGGERMODE_CHANGE)
	{
		m_nTriggerMode = nTriggerMode;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetTriggerMode() CONST
{
	return m_nTriggerMode;
}

BOOL CTPEPConnection::SetSampleLimit(INT nSampleLimit)
{
	if (nSampleLimit >= 0)
	{
		m_nSampleLimit = nSampleLimit;
		return TRUE;
	}
	return FALSE;
}

INT CTPEPConnection::GetSampleLimit() CONST
{
	return m_nSampleLimit;
}

VOID CTPEPConnection::SetPackets(CONST CStringArray &szPackets)
{
	m_szPackets.Copy(szPackets);
}

INT CTPEPConnection::GetPackets(CStringArray &szPackets) CONST
{
	szPackets.Copy(m_szPackets);
	return((INT)szPackets.GetSize());
}

VOID CTPEPConnection::SetParameters(CONST CStringArray &szParameters)
{
	m_szParameters.Copy(szParameters);
}

INT CTPEPConnection::GetParameters(CStringArray &szParameters) CONST
{
	szParameters.Copy(m_szParameters);
	return((INT)szParameters.GetSize());
}

VOID CTPEPConnection::SetRetrieveStartTime(CONST CTimeKey &tRetrieveStartTime)
{
	m_tRetrieveStartTime = tRetrieveStartTime;
}

CTimeKey CTPEPConnection::GetRetrieveStartTime() CONST
{
	return m_tRetrieveStartTime;
}

VOID CTPEPConnection::SetRetrieveStopTime(CONST CTimeKey &tRetrieveStopTime)
{
	m_tRetrieveStopTime = tRetrieveStopTime;
}

CTimeKey CTPEPConnection::GetRetrieveStopTime() CONST
{
	return m_tRetrieveStopTime;
}

BOOL CTPEPConnection::SetRetrieveSpeed(UINT nRetrieveSpeed)
{
	if (nRetrieveSpeed == 0 || (nRetrieveSpeed >= TPEP_RETRIEVESPEED_MINIMUM  &&  nRetrieveSpeed <= TPEP_RETRIEVESPEED_MAXIMUM))
	{
		m_nRetrieveSpeed = nRetrieveSpeed;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CTPEPConnection::SetSpacecraftID(UINT nSpacecraftID)
{
	if (nSpacecraftID >= 0)
	{
		m_nSpacecraftID = nSpacecraftID;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPConnection::GetSpacecraftID() CONST
{
	return m_nSpacecraftID;
}

VOID CTPEPConnection::SetStatistics(CONST CTimeKey &tConnect, CONST CTimeKey &tLastUse, UINT nCount)
{
	m_tConnection[0] = tConnect;
	m_tConnection[1] = tLastUse;
	m_nMessageCount = nCount;
}

VOID CTPEPConnection::GetStatistics(CTimeKey &tConnect, CTimeKey &tLastUse, UINT &nCount) CONST
{
	tConnect = m_tConnection[0];
	tLastUse = m_tConnection[1];
	nCount = m_nMessageCount;
}

BOOL CTPEPConnection::IsInitialized() CONST
{
	return((((m_nType == TPEP_TYPE_PACKETS  &&  m_szPackets.GetSize() > 0) || (m_nType == TPEP_TYPE_PARAMETERS  &&  m_szParameters.GetSize() > 0)) && m_nSpacecraftID > 0 && (m_nDataMode == TPEP_DATAMODE_REALTIME || m_nDataMode == TPEP_DATAMODE_HISTORY || m_nDataMode == TPEP_DATAMODE_RANDOM) && ((m_nType == TPEP_TYPE_PACKETS  &&  m_nDataType == TPEP_DATATYPE_RAW) || m_nDataType == TPEP_DATATYPE_PIE1 || m_nDataType == TPEP_DATATYPE_PIE2 || m_nDataType == TPEP_DATATYPE_PIE3) && (m_nDataLink == TPEP_DATALINK_COLD || m_nDataLink == TPEP_DATALINK_HOT) && (m_nTriggerMode == TPEP_TRIGGERMODE_UPDATE || m_nTriggerMode == TPEP_TRIGGERMODE_CHANGE) && m_nSampleLimit >= 0 && ((m_tConnection[0].GetTime() == m_tConnection[1].GetTime() && !m_nMessageCount) || (m_tConnection[0] > 0 && m_tConnection[0] <= m_tConnection[1] && m_nMessageCount > 0))) ? TRUE : FALSE);
}

VOID CTPEPConnection::Reset()
{
	m_nType = 0;
	m_nDataMode = 0;
	m_nDataLink = 0;
	m_nDataType = 0;
	m_nTriggerMode = 0;
	m_nSampleLimit = 0;
	m_nSpacecraftID = 0;
	m_nMessageCount = 0;
	m_nRetrieveSpeed = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	m_tConnection[0] = 0;
	m_tConnection[1] = 0;
	m_szPackets.RemoveAll();
	m_szParameters.RemoveAll();
}

VOID CTPEPConnection::Copy(CONST CTPEPConnection *pConnection, BOOL bStatistics)
{
	m_nType = pConnection->m_nType;
	m_nDataMode = pConnection->m_nDataMode;
	m_nDataLink = pConnection->m_nDataLink;
	m_nDataType = pConnection->m_nDataType;
	m_nTriggerMode = pConnection->m_nTriggerMode;
	m_nSampleLimit = pConnection->m_nSampleLimit;
	m_nSpacecraftID = pConnection->m_nSpacecraftID;
	m_nRetrieveSpeed = pConnection->m_nRetrieveSpeed;
	m_tRetrieveStartTime = pConnection->m_tRetrieveStartTime;
	m_tRetrieveStopTime = pConnection->m_tRetrieveStopTime;
	m_tConnection[0] = (bStatistics) ? pConnection->m_tConnection[0] : m_tConnection[0];
	m_tConnection[1] = (bStatistics) ? pConnection->m_tConnection[1] : m_tConnection[1];
	m_nMessageCount = (bStatistics) ? pConnection->m_nMessageCount : m_nMessageCount;
	m_szPackets.Copy(pConnection->m_szPackets);
	m_szParameters.Copy(pConnection->m_szParameters);
}

BOOL CTPEPConnection::Compare(CONST CTPEPConnection *pConnection, BOOL bStatistics) CONST
{
	INT  nPacket[2];
	INT  nPackets[2];
	INT  nParameter[2];
	INT  nParameters[2];

	for (nPacket[0] = 0, nPackets[0] = (pConnection->m_nType == m_nType && pConnection->m_szPackets.GetSize() == m_szPackets.GetSize() && pConnection->m_szParameters.GetSize() == m_szParameters.GetSize() && pConnection->m_nSpacecraftID == m_nSpacecraftID && pConnection->m_nDataMode == m_nDataMode && pConnection->m_nDataLink == m_nDataLink && pConnection->m_nDataType == m_nDataType && pConnection->m_nTriggerMode == m_nTriggerMode && pConnection->m_nSampleLimit == m_nSampleLimit && pConnection->m_tRetrieveStartTime == m_tRetrieveStartTime && pConnection->m_tRetrieveStopTime == m_tRetrieveStopTime && pConnection->m_nRetrieveSpeed == m_nRetrieveSpeed && (!bStatistics || (pConnection->m_tConnection[0] == m_tConnection[0] && pConnection->m_tConnection[1] == m_tConnection[1] && pConnection->m_nMessageCount == m_nMessageCount))) ? (INT)pConnection->m_szPackets.GetSize() : -1; nPacket[0] < nPackets[0]; nPacket[0]++)
	{
		for (nPacket[1] = 0, nPackets[1] = (INT)m_szPackets.GetSize(); nPacket[1] < nPackets[1]; nPacket[1]++)
		{
			if (pConnection->m_szPackets.GetAt(nPacket[0]) == m_szPackets.GetAt(nPacket[1])) break;
			continue;
		}
		if (nPacket[1] == nPackets[1]) break;
	}
	for (nParameter[0] = 0, nParameters[0] = (nPacket[0] == nPackets[0]) ? (INT)pConnection->m_szParameters.GetSize() : -1; nParameter[0] < nParameters[0]; nParameter[0]++)
	{
		for (nParameter[1] = 0, nParameters[1] = (INT)m_szParameters.GetSize(); nParameter[1] < nParameters[1]; nParameter[1]++)
		{
			if (pConnection->m_szParameters.GetAt(nParameter[0]) == m_szParameters.GetAt(nParameter[1])) break;
			continue;
		}
		if (nParameter[1] == nParameters[1]) break;
	}
	return((nPacket[0] == nPackets[0] && nParameter[0] == nParameters[0]) ? TRUE : FALSE);
}

BOOL CTPEPConnection::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nPacketData;
	CByteArray  nParameterData;

	for (nPacket = 0, nPackets = (INT)m_szPackets.GetSize(), sData.cbPackets = 0; nPacket < nPackets; nPacket++, sData.cbPackets += cbData)
	{
		nPacketData.SetSize(sData.cbPackets + (cbData = (m_szPackets.GetAt(nPacket).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nPacketData.GetData() + sData.cbPackets, (LPCTSTR)m_szPackets.GetAt(nPacket), cbData);
	}
	for (nParameter = 0, nParameters = (INT)m_szParameters.GetSize(), sData.cbParameters = 0; nParameter < nParameters; nParameter++, sData.cbParameters += cbData)
	{
		nParameterData.SetSize(sData.cbParameters + (cbData = (m_szParameters.GetAt(nParameter).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nParameterData.GetData() + sData.cbParameters, (LPCTSTR)m_szParameters.GetAt(nParameter), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbPackets + sData.cbParameters)), sData.nType = m_nType, sData.nSpacecraftID = m_nSpacecraftID, sData.nDataMode = m_nDataMode, sData.nDataLink = m_nDataLink, sData.nDataType = m_nDataType, sData.nTriggerMode = m_nTriggerMode, sData.tRetrieveStartTime = m_tRetrieveStartTime.GetTime(), sData.tRetrieveStopTime = m_tRetrieveStopTime.GetTime(), sData.nRetrieveSpeed = m_nRetrieveSpeed, sData.nSampleLimit = m_nSampleLimit; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), nPacketData.GetData(), sData.cbPackets);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPackets), nParameterData.GetData(), sData.cbParameters);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPConnection::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbPacket;
	INT  cbPackets;
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nPacketData;
	CByteArray  nParameterData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbPackets + sData.cbParameters; )
	{
		for (nPacketData.SetSize(sData.cbPackets), CopyMemory(nPacketData.GetData(), nInfo.GetData() + (cbData = sizeof(DATA)), sData.cbPackets), m_nType = sData.nType, m_nSpacecraftID = sData.nSpacecraftID, m_nDataMode = sData.nDataMode, m_nDataLink = sData.nDataLink, m_nDataType = sData.nDataType, m_nTriggerMode = sData.nTriggerMode, m_tRetrieveStartTime = sData.tRetrieveStartTime, m_tRetrieveStopTime = sData.tRetrieveStopTime, m_nRetrieveSpeed = sData.nRetrieveSpeed, m_nSampleLimit = sData.nSampleLimit, m_szPackets.RemoveAll(), cbPacket = cbPackets = 0; cbPackets < sData.cbPackets; cbPackets += (cbPacket = (m_szPackets.GetAt(m_szPackets.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szPackets.Add((LPCTSTR)(nPacketData.GetData() + cbPackets));
			continue;
		}
		for (nParameterData.SetSize(sData.cbParameters), CopyMemory(nParameterData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbPackets), sData.cbParameters), m_szParameters.RemoveAll(), cbParameter = cbParameters = 0; cbParameters < sData.cbParameters; cbParameters += (cbParameter = (m_szParameters.GetAt(m_szParameters.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szParameters.Add((LPCTSTR)(nParameterData.GetData() + cbParameters));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPConnections

CTPEPConnections::CTPEPConnections() : CPtrArray()
{
	return;
}

CTPEPConnections::~CTPEPConnections()
{
	RemoveAll();
}

INT CTPEPConnections::Add(CTPEPConnection *pConnection)
{
	return((INT)CPtrArray::Add(pConnection));
}

CTPEPConnection *CTPEPConnections::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPConnection *)CPtrArray::GetAt(nIndex) : (CTPEPConnection *)NULL);
}

CTPEPConnection *CTPEPConnections::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPConnection *)CPtrArray::GetAt(nIndex) : (CTPEPConnection *)NULL);
}

VOID CTPEPConnections::RemoveAll()
{
	INT  nConnection;
	INT  nConnections;
	CTPEPConnection  *pConnection;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = GetAt(nConnection))) delete pConnection;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTPEPConnections::Copy(CONST CTPEPConnections *pConnections, BOOL bStatistics)
{
	INT  nConnection;
	INT  nConnections;
	CTPEPConnection  *pConnection;

	for (nConnection = 0, nConnections = (INT)pConnections->GetSize(), RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = new CTPEPConnection) != (CTPEPConnection *)NULL)
		{
			pConnection->Copy(pConnections->GetAt(nConnection), bStatistics);
			InsertAt(GetSize(), pConnection, 1);
			continue;
		}
		break;
	}
	return((nConnection == nConnections) ? TRUE : FALSE);
}

BOOL CTPEPConnections::Compare(CONST CTPEPConnections *pConnections, BOOL bStatistics) CONST
{
	INT  nConnection;
	INT  nConnections;

	for (nConnection = 0, nConnections = (pConnections->GetSize() == GetSize()) ? (INT)GetSize() : -1; nConnection < nConnections; nConnection++)
	{
		if (!pConnections->GetAt(nConnection)->Compare(GetAt(nConnection), bStatistics)) break;
		continue;
	}
	return((nConnection == nConnections) ? TRUE : FALSE);
}

BOOL CTPEPConnections::Map(CByteArray &nInfo) CONST
{
	INT  nConnection;
	INT  nConnections;
	CByteArray  nConnectionData;
	CTPEPConnection  *pConnection;

	for (nConnection = 0, nConnections = (INT)GetSize(), nInfo.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = GetAt(nConnection)) && pConnection->Map(nConnectionData) && nInfo.Append(nConnectionData) >= 0) continue;
		break;
	}
	return((nConnection == nConnections) ? TRUE : FALSE);
}

BOOL CTPEPConnections::Unmap(CONST CByteArray &nInfo)
{
	INT  cbConnection;
	INT  cbConnections;
	CByteArray  nConnectionData;
	CTPEPConnection  *pConnection;

	for (cbConnections = 0, RemoveAll(); cbConnections < nInfo.GetSize(); cbConnections += cbConnection)
	{
		for (CopyMemory(&cbConnection, nInfo.GetData() + cbConnections, sizeof(cbConnection)), nConnectionData.SetSize(max(min(cbConnection, nInfo.GetSize() - cbConnections), 0)); nConnectionData.GetSize() >= 0; )
		{
			CopyMemory(nConnectionData.GetData(), nInfo.GetData() + cbConnections, nConnectionData.GetSize());
			break;
		}
		if ((pConnection = new CTPEPConnection))
		{
			if (pConnection->Unmap(nConnectionData) && Add(pConnection) >= 0) continue;
			delete pConnection;
		}
		break;
	}
	return((cbConnections == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPConnection

CPFLPConnection::CPFLPConnection() : CObject()
{
	Reset();
}

BOOL CPFLPConnection::SetType(WORD wType)
{
	if (wType == PFLP_TYPE_TM || wType == PFLP_TYPE_TC)
	{
		m_wType = wType;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPConnection::GetType() CONST
{
	return m_wType;
}

BOOL CPFLPConnection::SetLevel(WORD wLevel)
{
	if (wLevel == PFLP_LEVEL_SOURCEPACKETS || wLevel == PFLP_LEVEL_TRANSFERFRAMES)
	{
		m_wLevel = wLevel;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPConnection::GetLevel() CONST
{
	return m_wLevel;
}

BOOL CPFLPConnection::SetEndian(WORD wEndian)
{
	if (wEndian == PFLP_ENDIAN_BIG || wEndian == PFLP_ENDIAN_LITTLE)
	{
		m_wEndian = wEndian;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPConnection::GetEndian() CONST
{
	return m_wEndian;
}

BOOL CPFLPConnection::SetFilterCount(WORD wCount)
{
	if (wCount == PFLP_FILTER_COUNT)
	{
		m_wFilterCount = wCount;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPConnection::GetFilterCount() CONST
{
	return m_wFilterCount;
}

BOOL CPFLPConnection::SetFilterManipulationCode(BYTE nCode)
{
	if (nCode == PFLP_FILTER_NONE || nCode == PFLP_FILTER_APID || nCode == PFLP_FILTER_VCID || nCode == PFLP_FILTER_APIDANDVCID)
	{
		m_nFilterManipulationCode = nCode;
		return TRUE;
	}
	return FALSE;
}

BYTE CPFLPConnection::GetFilterManipulationCode() CONST
{
	return m_nFilterManipulationCode;
}

BOOL CPFLPConnection::SetFilterGroupIdentifier(BYTE nVCID)
{
	if (nVCID >= 0)
	{
		m_nFilterGroupIdentifier = nVCID;
		return TRUE;
	}
	return FALSE;
}

BYTE CPFLPConnection::GetFilterGroupIdentifier() CONST
{
	return m_nFilterGroupIdentifier;
}

BOOL CPFLPConnection::SetFilterDataIdentifier(WORD wAPID)
{
	if (wAPID >= 0)
	{
		m_wFilterDataIdentifier = wAPID;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPConnection::GetFilterDataIdentifier() CONST
{
	return m_wFilterDataIdentifier;
}

VOID CPFLPConnection::SetTimeEpoch(CONST SYSTEMTIME *pEpoch)
{
	m_tEpoch.wYear = pEpoch->wYear;
	m_tEpoch.wMonth = pEpoch->wMonth;
	m_tEpoch.wDay = pEpoch->wDay;
	m_tEpoch.wDayOfWeek = pEpoch->wDayOfWeek;
	m_tEpoch.wHour = pEpoch->wHour;
	m_tEpoch.wMinute = pEpoch->wMinute;
	m_tEpoch.wSecond = pEpoch->wSecond;
	m_tEpoch.wMilliseconds = pEpoch->wMilliseconds;
}

BOOL CPFLPConnection::GetTimeEpoch(SYSTEMTIME *pEpoch) CONST
{
	pEpoch->wYear = m_tEpoch.wYear;
	pEpoch->wMonth = m_tEpoch.wMonth;
	pEpoch->wDay = m_tEpoch.wDay;
	pEpoch->wDayOfWeek = m_tEpoch.wDayOfWeek;
	pEpoch->wHour = m_tEpoch.wHour;
	pEpoch->wMinute = m_tEpoch.wMinute;
	pEpoch->wSecond = m_tEpoch.wSecond;
	pEpoch->wMilliseconds = m_tEpoch.wMilliseconds;
	return((pEpoch->wYear > 0) ? TRUE : FALSE);
}

VOID CPFLPConnection::SetTimeCorrelation(LONG tError, LONG tDelta)
{
	m_tCorrelationError = tError;
	m_tCorrelationDelta = tDelta;
}

BOOL CPFLPConnection::GetTimeCorrelation(LONG &tError, LONG &tDelta) CONST
{
	tError = m_tCorrelationError;
	tDelta = m_tCorrelationDelta;
	return((tError != 0 || tDelta != 0) ? TRUE : FALSE);
}

VOID CPFLPConnection::SetClockAdjustment(CONST CTimeSpan &tAdjustment)
{
	m_tAdjustment = tAdjustment;
}

CTimeSpan CPFLPConnection::GetClockAdjustment() CONST
{
	return m_tAdjustment;
}

VOID CPFLPConnection::SetStatistics(CONST CTimeTag &tConnectTime, CONST CTimeTag &tLastUseTime, DWORDLONG cbBytes)
{
	m_tConnection[0] = tConnectTime;
	m_tConnection[1] = tLastUseTime;
	m_cbConnection = cbBytes;
}

VOID CPFLPConnection::GetStatistics(CTimeTag &tConnectTime, CTimeTag &tLastUseTime, DWORDLONG &cbBytes) CONST
{
	tConnectTime = m_tConnection[0];
	tLastUseTime = m_tConnection[1];
	cbBytes = m_cbConnection;
}

BOOL CPFLPConnection::IsInitialized() CONST
{
	return(((m_wType == PFLP_TYPE_TM || m_wType == PFLP_TYPE_TC) && (m_wLevel == PFLP_LEVEL_SOURCEPACKETS || m_wLevel == PFLP_LEVEL_TRANSFERFRAMES) && (m_wEndian == PFLP_ENDIAN_BIG || m_wEndian == PFLP_ENDIAN_LITTLE) && m_wFilterCount == PFLP_FILTER_COUNT && (m_nFilterManipulationCode == PFLP_FILTER_NONE || m_nFilterManipulationCode == PFLP_FILTER_APID || m_nFilterManipulationCode == PFLP_FILTER_VCID || m_nFilterManipulationCode == PFLP_FILTER_APIDANDVCID)) ? TRUE : FALSE);
}

VOID CPFLPConnection::Reset()
{
	m_wType = 0;
	m_wLevel = 0;
	m_wEndian = 0;
	m_cbConnection = 0;
	m_wFilterCount = 0;
	m_wFilterDataIdentifier = -1;
	m_nFilterGroupIdentifier = -1;
	m_nFilterManipulationCode = 0;
	m_tConnection[0] = 0;
	m_tConnection[1] = 0;
	m_tCorrelationError = 0;
	m_tCorrelationDelta = 0;
	m_tAdjustment = 0;
	m_tEpoch.wYear = 0;
	m_tEpoch.wMonth = 0;
	m_tEpoch.wDay = 0;
	m_tEpoch.wDayOfWeek = 0;
	m_tEpoch.wHour = 0;
	m_tEpoch.wMinute = 0;
	m_tEpoch.wSecond = 0;
	m_tEpoch.wMilliseconds = 0;
}

VOID CPFLPConnection::Copy(CONST CPFLPConnection *pConnection, BOOL bStatistics)
{
	m_wType = pConnection->m_wType;
	m_wLevel = pConnection->m_wLevel;
	m_wEndian = pConnection->m_wEndian;
	m_cbConnection = pConnection->m_cbConnection;
	m_wFilterCount = pConnection->m_wFilterCount;
	m_wFilterDataIdentifier = pConnection->m_wFilterDataIdentifier;
	m_nFilterGroupIdentifier = pConnection->m_nFilterGroupIdentifier;
	m_nFilterManipulationCode = pConnection->m_nFilterManipulationCode;
	m_tConnection[0] = pConnection->m_tConnection[0];
	m_tConnection[1] = pConnection->m_tConnection[1];
	m_tCorrelationError = pConnection->m_tCorrelationError;
	m_tCorrelationDelta = pConnection->m_tCorrelationDelta;
	m_tAdjustment = pConnection->m_tAdjustment;
	m_tEpoch.wYear = pConnection->m_tEpoch.wYear;
	m_tEpoch.wMonth = pConnection->m_tEpoch.wMonth;
	m_tEpoch.wDay = pConnection->m_tEpoch.wDay;
	m_tEpoch.wDayOfWeek = pConnection->m_tEpoch.wDayOfWeek;
	m_tEpoch.wHour = pConnection->m_tEpoch.wHour;
	m_tEpoch.wMinute = pConnection->m_tEpoch.wMinute;
	m_tEpoch.wSecond = pConnection->m_tEpoch.wSecond;
	m_tEpoch.wMilliseconds = pConnection->m_tEpoch.wMilliseconds;
	m_tConnection[0] = (bStatistics) ? pConnection->m_tConnection[0] : m_tConnection[0];
	m_tConnection[1] = (bStatistics) ? pConnection->m_tConnection[1] : m_tConnection[1];
	m_cbConnection = (bStatistics) ? pConnection->m_cbConnection : m_cbConnection;
}

BOOL CPFLPConnection::Compare(CONST CPFLPConnection *pConnection, BOOL bStatistics) CONST
{
	return((pConnection->m_wType == m_wType  &&  pConnection->m_wLevel == m_wLevel  &&  pConnection->m_wEndian == m_wEndian  &&  pConnection->m_wFilterCount == m_wFilterCount  &&  pConnection->m_wFilterDataIdentifier == m_wFilterDataIdentifier  &&  pConnection->m_nFilterGroupIdentifier == m_nFilterGroupIdentifier  &&  pConnection->m_nFilterManipulationCode == m_nFilterManipulationCode  &&  pConnection->m_tCorrelationError == m_tCorrelationError  &&  pConnection->m_tCorrelationDelta == m_tCorrelationDelta  &&  pConnection->m_tAdjustment == m_tAdjustment  &&  pConnection->m_tEpoch.wYear == m_tEpoch.wYear  &&  pConnection->m_tEpoch.wMonth == m_tEpoch.wMonth  &&  pConnection->m_tEpoch.wDay == m_tEpoch.wDay  &&  pConnection->m_tEpoch.wHour == m_tEpoch.wHour  &&  pConnection->m_tEpoch.wMinute == m_tEpoch.wMinute  &&  pConnection->m_tEpoch.wSecond == m_tEpoch.wSecond  &&  pConnection->m_tEpoch.wMilliseconds == m_tEpoch.wMilliseconds && (!bStatistics || (pConnection->m_tConnection[0] == m_tConnection[0] && pConnection->m_tConnection[1] == m_tConnection[1] && pConnection->m_cbConnection == m_cbConnection))) ? TRUE : FALSE);
}

BOOL CPFLPConnection::Map(CByteArray &nInfo) CONST
{
	DATA  sData;

	for (nInfo.SetSize((sData.cbSize = sizeof(DATA))), sData.wType = m_wType, sData.wLevel = m_wLevel, sData.wEndian = m_wEndian, sData.wFilterCount = m_wFilterCount, sData.wFilterDataIdentifier = m_wFilterDataIdentifier, sData.nFilterGroupIdentifier = m_nFilterGroupIdentifier, sData.nFilterManipulationCode = m_nFilterManipulationCode, sData.tCorrelationError = m_tCorrelationError, sData.tCorrelationDelta = m_tCorrelationDelta, sData.tAdjustment = m_tAdjustment.GetTotalSeconds(), sData.tEpoch.wYear = m_tEpoch.wYear, sData.tEpoch.wMonth = m_tEpoch.wMonth, sData.tEpoch.wDay = m_tEpoch.wDay, sData.tEpoch.wDayOfWeek = m_tEpoch.wDayOfWeek, sData.tEpoch.wHour = m_tEpoch.wHour, sData.tEpoch.wMinute = m_tEpoch.wMinute, sData.tEpoch.wSecond = m_tEpoch.wSecond, sData.tEpoch.wMilliseconds = m_tEpoch.wMilliseconds; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPConnection::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA); )
	{
		m_wType = sData.wType;
		m_wLevel = sData.wLevel;
		m_wEndian = sData.wEndian;
		m_wFilterCount = sData.wFilterCount;
		m_wFilterDataIdentifier = sData.wFilterDataIdentifier;
		m_nFilterGroupIdentifier = sData.nFilterGroupIdentifier;
		m_nFilterManipulationCode = sData.nFilterManipulationCode;
		m_tCorrelationError = sData.tCorrelationError;
		m_tCorrelationDelta = sData.tCorrelationDelta;
		m_tAdjustment = sData.tAdjustment;
		m_tEpoch.wYear = sData.tEpoch.wYear;
		m_tEpoch.wMonth = sData.tEpoch.wMonth;
		m_tEpoch.wDay = sData.tEpoch.wDay;
		m_tEpoch.wDayOfWeek = sData.tEpoch.wDayOfWeek;
		m_tEpoch.wHour = sData.tEpoch.wHour;
		m_tEpoch.wMinute = sData.tEpoch.wMinute;
		m_tEpoch.wSecond = sData.tEpoch.wSecond;
		m_tEpoch.wMilliseconds = sData.tEpoch.wMilliseconds;
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPConnections

CPFLPConnections::CPFLPConnections() : CPtrArray()
{
	return;
}

CPFLPConnections::~CPFLPConnections()
{
	RemoveAll();
}

INT CPFLPConnections::Add(CPFLPConnection *pConnection)
{
	return((INT)CPtrArray::Add(pConnection));
}

CPFLPConnection *CPFLPConnections::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPConnection *)CPtrArray::GetAt(nIndex) : (CPFLPConnection *)NULL);
}

CPFLPConnection *CPFLPConnections::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPConnection *)CPtrArray::GetAt(nIndex) : (CPFLPConnection *)NULL);
}

VOID CPFLPConnections::RemoveAll()
{
	INT  nConnection;
	INT  nConnections;
	CPFLPConnection  *pConnection;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = GetAt(nConnection))) delete pConnection;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CPFLPConnections::Copy(CONST CPFLPConnections *pConnections, BOOL bStatistics)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPConnection  *pConnection;

	for (nConnection = 0, nConnections = (INT)pConnections->GetSize(), RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = new CPFLPConnection) != (CPFLPConnection *)NULL)
		{
			pConnection->Copy(pConnections->GetAt(nConnection), bStatistics);
			InsertAt(GetSize(), pConnection, 1);
			continue;
		}
		break;
	}
	return((nConnection == nConnections) ? TRUE : FALSE);
}

BOOL CPFLPConnections::Compare(CONST CPFLPConnections *pConnections, BOOL bStatistics) CONST
{
	INT  nConnection;
	INT  nConnections;

	for (nConnection = 0, nConnections = (pConnections->GetSize() == GetSize()) ? (INT)GetSize() : -1; nConnection < nConnections; nConnection++)
	{
		if (!pConnections->GetAt(nConnection)->Compare(GetAt(nConnection), bStatistics)) break;
		continue;
	}
	return((nConnection == nConnections) ? TRUE : FALSE);
}

BOOL CPFLPConnections::Map(CByteArray &nInfo) CONST
{
	INT  nConnection;
	INT  nConnections;
	CByteArray  nConnectionData;
	CPFLPConnection  *pConnection;

	for (nConnection = 0, nConnections = (INT)GetSize(), nInfo.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = GetAt(nConnection)) && pConnection->Map(nConnectionData) && nInfo.Append(nConnectionData) >= 0) continue;
		break;
	}
	return((nConnection == nConnections) ? TRUE : FALSE);
}

BOOL CPFLPConnections::Unmap(CONST CByteArray &nInfo)
{
	INT  cbConnection;
	INT  cbConnections;
	CByteArray  nConnectionData;
	CPFLPConnection  *pConnection;

	for (cbConnections = 0, RemoveAll(); cbConnections < nInfo.GetSize(); cbConnections += cbConnection)
	{
		for (CopyMemory(&cbConnection, nInfo.GetData() + cbConnections, sizeof(cbConnection)), nConnectionData.SetSize(max(min(cbConnection, nInfo.GetSize() - cbConnections), 0)); nConnectionData.GetSize() >= 0; )
		{
			CopyMemory(nConnectionData.GetData(), nInfo.GetData() + cbConnections, nConnectionData.GetSize());
			break;
		}
		if ((pConnection = new CPFLPConnection))
		{
			if (pConnection->Unmap(nConnectionData) && Add(pConnection) >= 0) continue;
			delete pConnection;
		}
		break;
	}
	return((cbConnections == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTMProcessInfo

CTMProcessInfo::CTMProcessInfo() : CObject()
{
	m_fTMBandwidth = -1.0;
	m_tTMBandwidth = m_tTMBandwidthData = 0;
	m_pCriticalSection = new CCriticalSection;
}

CTMProcessInfo::~CTMProcessInfo()
{
	delete m_pCriticalSection;
}

BOOL CTMProcessInfo::SetTMBandwidth(double fTMBandwidth, CONST CTimeTag &tTMBandwidth)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_fTMBandwidth = fTMBandwidth, m_tTMBandwidth = tTMBandwidth; fTMBandwidth < 0.0 && tTMBandwidth == 0; )
	{
		m_nTMBandwidthData.RemoveAll();
		m_tTMBandwidthData = 0;
		break;
	}
	return TRUE;
}

BOOL CTMProcessInfo::GetTMBandwidth(double &fTMBandwidth, CTimeTag &tTMBandwidth) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	fTMBandwidth = m_fTMBandwidth;
	tTMBandwidth = m_tTMBandwidth;
	return((fTMBandwidth >= 0.0  &&  tTMBandwidth > 0) ? TRUE : FALSE);
}
BOOL CTMProcessInfo::GetTMBandwidth(double &fTotalTMBandwidth, double &fMaxDiagnosticTMBandwidth) CONST
{
	return FALSE;
}

BOOL CTMProcessInfo::SetTMBandwidthData(CONST CUIntArray &nTMBandwidthData, CONST CTimeTag &tTMBandwidthData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nTMBandwidthData.Copy(nTMBandwidthData);
	m_tTMBandwidthData = tTMBandwidthData;
	return TRUE;
}

BOOL CTMProcessInfo::GetTMBandwidthData(CUIntArray &nTMBandwidthData, CTimeTag &tTMBandwidthData) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	nTMBandwidthData.Copy(m_nTMBandwidthData);
	tTMBandwidthData = m_tTMBandwidthData;
	return TRUE;
}

BOOL CTMProcessInfo::SetData(CONST CByteArray &nData)
{
	return FALSE;
}

INT CTMProcessInfo::GetData(CByteArray &nData) CONST
{
	return 0;
}

VOID CTMProcessInfo::Reset()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_fTMBandwidth = -1.0;
	m_tTMBandwidth = 0;
	m_tTMBandwidthData = 0;
	m_nTMBandwidthData.RemoveAll();
}

BOOL CTMProcessInfo::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTMProcessInfo::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTMEnvironment

CTMEnvironment::CTMEnvironment() : CObject()
{
	m_nType = DATABASE_TYPE_NONE;
	m_bHistoricalData = FALSE;
	m_pTMUnits = (CTMUnits *)NULL;
	m_pTMPacket = (CTMPacket *)NULL;
	m_pTMUnitCache = (CTMUnitCache *)NULL;
	m_pMemoryDumps = (CMemoryDumps *)NULL;
	m_pTMProcessInfo = (CTMProcessInfo *)NULL;
	m_pTMParameters[0] = (CTMParameters *)NULL;
	m_pTMParameters[1] = (CTMParameters *)NULL;
	m_pOolParameters = (COolParameters *)NULL;
	m_pOversamplingParameters = (COversamplingParameters *)NULL;
	m_pCriticalSection = new CCriticalSection;
}

CTMEnvironment::~CTMEnvironment()
{
	Destroy();
	delete m_pCriticalSection;
}

BOOL CTMEnvironment::Create(CONST CDatabaseEngine *pDatabase, BOOL bFull)
{
	for (Destroy(); (m_nType = pDatabase->GetType()) & DATABASE_TYPE_STANDARD_CCSDS; )
	{
		if ((m_pTMUnits = new CTMUnits))
		{
			if ((m_pTMPacket = new CTMPacket))
			{
				if ((m_pTMUnitCache = new CTMUnitCache))
				{
					if ((m_pMemoryDumps = new CMemoryDumps))
					{
						if ((m_pTMParameters[0] = new CTMParameters))
						{
							if ((m_pTMParameters[1] = new CTMParameters))
							{
								if ((m_pOolParameters = new COolParameters))
								{
									if ((m_pOversamplingParameters = new COversamplingParameters))
									{
										if ((bFull  &&  m_pTMParameters[0]->Create(pDatabase)) || !bFull)
										{
											m_bHistoricalData = FALSE;
											return TRUE;
										}
										delete m_pOversamplingParameters;
									}
									delete m_pOolParameters;
								}
								delete m_pTMParameters[1];
							}
							delete m_pTMParameters[0];
						}
						delete m_pMemoryDumps;
					}
					delete m_pTMUnitCache;
				}
				delete m_pTMPacket;
			}
			delete m_pTMUnits;
		}
		break;
	}
	m_nType = DATABASE_TYPE_NONE;
	m_pTMUnits = (CTMUnits *)NULL;
	m_pTMPacket = (CTMPacket *)NULL;
	m_pTMUnitCache = (CTMUnitCache *)NULL;
	m_pMemoryDumps = (CMemoryDumps *)NULL;
	m_pTMParameters[0] = (CTMParameters *)NULL;
	m_pTMParameters[1] = (CTMParameters *)NULL;
	m_pOolParameters = (COolParameters *)NULL;
	m_pOversamplingParameters = (COversamplingParameters *)NULL;
	return FALSE;
}

VOID CTMEnvironment::Destroy()
{
	for (m_nType = DATABASE_TYPE_NONE; m_pTMUnits; )
	{
		delete m_pTMUnits;
		m_pTMUnits = (CTMUnits *)NULL;
		break;
	}
	if (m_pTMPacket)
	{
		delete m_pTMPacket;
		m_pTMPacket = (CTMPacket *)NULL;
	}
	if (m_pTMUnitCache)
	{
		delete m_pTMUnitCache;
		m_pTMUnitCache = (CTMUnitCache *)NULL;
	}
	if (m_pMemoryDumps)
	{
		delete m_pMemoryDumps;
		m_pMemoryDumps = (CMemoryDumps *)NULL;
	}
	if (m_pTMProcessInfo)
	{
		delete m_pTMProcessInfo;
		m_pTMProcessInfo = (CTMProcessInfo *)NULL;
	}
	if (m_pTMParameters[0])
	{
		delete m_pTMParameters[0];
		m_pTMParameters[0] = (CTMParameters *)NULL;
	}
	if (m_pTMParameters[1])
	{
		delete m_pTMParameters[1];
		m_pTMParameters[1] = (CTMParameters *)NULL;
	}
	if (m_pOolParameters)
	{
		delete m_pOolParameters;
		m_pOolParameters = (COolParameters *)NULL;
	}
	if (m_pOversamplingParameters)
	{
		delete m_pOversamplingParameters;
		m_pOversamplingParameters = (COversamplingParameters *)NULL;
	}
}

BOOL CTMEnvironment::Initialize(CTMProcessInfo *pInfo)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pTMProcessInfo = pInfo;
	return TRUE;
}
BOOL CTMEnvironment::Initialize(CTMUnit &cTMUnit, BOOL bBadData)
{
	INT  nTMUnit;
	INT  nTMUnits;
	CString  szTag;
	CTimeTag  tTag;
	CTMUnit  cUnit;
	CTMUnit  *pTMUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		if ((pTMUnit = GetTMUnit())->IsValid())
		{
			if (!pTMUnit->HasBadData() || bBadData)
			{
				cUnit.Copy(pTMUnit);
				cTMUnit.Copy(&cUnit);
				return TRUE;
			}
		}
		for (nTMUnit = 0, nTMUnits = (INT)GetTMUnitCache()->GetSize(), szTag.Empty(), tTag = 0; nTMUnit < nTMUnits; nTMUnit++)
		{
			if ((pTMUnit = GetTMUnitCache()->GetAt(nTMUnit)))
			{
				if (!pTMUnit->HasBadData() || bBadData)
				{
					if (tTag < pTMUnit->GetTimeTag())
					{
						szTag = pTMUnit->GetTag();
						tTag = pTMUnit->GetTimeTag();
						cUnit.Copy(pTMUnit);
						cTMUnit.Copy(&cUnit);
					}
				}
			}
		}
		return !szTag.IsEmpty();
	}
	cTMUnit.Reset();
	return TRUE;
}
BOOL CTMEnvironment::Initialize(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData)
{
	CTMUnit  *pTMUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		if ((pTMUnit = GetTMUnitCache()->GetAt(GetTMUnitCache()->Find(pszTag))))
		{
			if (!pTMUnit->HasBadData() || bBadData)
			{
				cTMUnit.Copy(pTMUnit);
				return TRUE;
			}
		}
		return FALSE;
	}
	cTMUnit.Reset();
	return TRUE;
}
BOOL CTMEnvironment::Initialize(CTMParameters &pTMParameters, BOOL bBadData)
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		for (nParameter = 0, nParameters = (INT)pTMParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter[1] = ((pTMParameter[0] = pTMParameters.GetAt(nParameter))) ? GetTMParameters()->GetAt(GetTMParameters()->Find(pTMParameter[0]->GetTag())) : (CTMParameter *)NULL))
			{
				if (!pTMParameter[1]->IsInitialized())
				{
					pTMParameter[0]->Reset();
					continue;
				}
				pTMParameter[0]->Initialize(pTMParameter[1], bBadData);
			}
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	pTMParameters.Reset();
	return TRUE;
}
BOOL CTMEnvironment::Initialize(COolParameters &pOolParameters, BOOL bBadData)
{
	INT  nSample;
	INT  nSamples;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	ULONGLONG  nValue;
	CTMParameter  *pTMParameter;
	COolParameter  *pOolParameter;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		for (nParameter = 0, nParameters = (GetTMParameters() != (CTMParameters *)NULL) ? (INT)GetTMParameters()->GetSize() : -1, pOolParameters.RemoveAll(); nParameter < nParameters; nParameter++)
		{
			for (nSample = 0, nSamples = GetTMParameters()->GetAt(nParameter)->GetValueCount(); nSample < nSamples; nSample++)
			{
				if ((pTMParameter = GetTMParameters()->GetAt(nParameter))->GetRawValue(nSample, nValue, nStatus))
				{
					if ((bBadData || (nStatus & TMPARAMETER_STATUS_GOOD)) && (nStatus & (TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT)))
					{
						if ((pOolParameter = new COolParameter))
						{
							pOolParameter->CTMParameter::Copy(pTMParameter);
							if (pOolParameters.Add(pOolParameter) >= 0) continue;
							delete pOolParameter;
						}
						break;
					}
				}
			}
			if (nSample < nSamples) break;
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL CTMEnvironment::Initialize(CMemoryDump &pDump, BOOL bBadData)
{
	CMemoryDump  *pMemoryDump;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		if ((pMemoryDump = GetMemoryDumps()->GetAt(GetMemoryDumps()->Find(pDump.GetName()))))
		{
			if (pMemoryDump->GetDumpStatus() == MEMORYDUMP_STATUS_COMPLETE || pMemoryDump->GetDumpStatus() == MEMORYDUMP_STATUS_INCOMPLETE)
			{
				if ((LOBYTE(pMemoryDump->GetDumpQuality()) & MEMORYDUMP_DATAQUALITY_GOOD) == MEMORYDUMP_DATAQUALITY_GOOD || bBadData)
				{
					pDump.SetDumpInfo(pMemoryDump, -1);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
BOOL CTMEnvironment::Initialize(CONST CStringArray &szParameters, CONST CUIntArray &nSamples)
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		for (nParameter = 0, nParameters = (szParameters.GetSize() == nSamples.GetSize()) ? (INT)szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter = GetTMParameters()->GetAt(GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
			{
				pTMParameter->SetPastValueSamples(max(pTMParameter->GetPastValueSamples(), nSamples.GetAt(nParameter)));
				continue;
			}
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL CTMEnvironment::Initialize(CONST COversamplingParameters &pOversamplingParameters)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((GetType() != DATABASE_TYPE_NONE) ? m_pOversamplingParameters->Copy(&pOversamplingParameters) : FALSE);
}

BOOL CTMEnvironment::Update(CONST CTMParameters &pTMParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		for (nParameter = 0, nParameters = (INT)pTMParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter[0] = pTMParameters.GetAt(nParameter)) != (CTMParameter *)NULL)
			{
				if ((pTMParameter[1] = GetTMParameters()->GetAt(GetTMParameters()->Find(pTMParameter[0]->GetTag()))))
				{
					pTMParameter[1]->Initialize(pTMParameter[0]);
					continue;
				}
			}
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTMEnvironment::ExamineData(CONST CTMUnit *pTMUnit)
{
	m_bHistoricalData = (pTMUnit == GetTMUnit());
	return(pTMUnit != (CONST CTMUnit *) NULL);
}

BOOL CTMEnvironment::IsHistoricalData() CONST
{
	return m_bHistoricalData;
}

VOID CTMEnvironment::Reset()
{
	CTMUnit  *pTMUnit;
	CTMUnits  *pTMUnits;
	CTMUnitCache  *pTMUnitCache;
	CMemoryDumps  *pMemoryDumps;
	CTMParameters  *pTMParameters[2];
	CTMProcessInfo  *pTMProcessInfo;
	COolParameters  *pOolParameters;
	COversamplingParameters  *pOversamplingParameters;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMUnit = GetTMUnit())) pTMUnit->Reset();
	if ((pTMUnits = GetTMUnits())) pTMUnits->RemoveAll();
	if ((pTMUnitCache = GetTMUnitCache())) pTMUnitCache->RemoveAll();
	if ((pMemoryDumps = GetMemoryDumps())) pMemoryDumps->RemoveAll();
	if ((pTMProcessInfo = GetTMProcessInfo())) pTMProcessInfo->Reset();
	if ((pTMParameters[0] = GetTMParameters())) pTMParameters[0]->Reset();
	if ((pTMParameters[1] = GetSyntheticParameters())) pTMParameters[1]->Reset();
	if ((pOolParameters = GetOolParameters())) pOolParameters->Reset();
	if ((pOversamplingParameters = GetOversamplingParameters())) pOversamplingParameters->RemoveAll();
}

UINT CTMEnvironment::GetType() CONST
{
	return m_nType;
}

CTMUnit *CTMEnvironment::GetTMUnit() CONST
{
	return(((GetType() & DATABASE_TYPE_STANDARD_CCSDS) == DATABASE_TYPE_STANDARD_CCSDS) ? (CTMUnit *)m_pTMPacket : (CTMUnit *)NULL);
}

CTMUnits *CTMEnvironment::GetTMUnits() CONST
{
	return m_pTMUnits;
}

CTMUnitCache *CTMEnvironment::GetTMUnitCache() CONST
{
	return m_pTMUnitCache;
}

CMemoryDumps *CTMEnvironment::GetMemoryDumps() CONST
{
	return m_pMemoryDumps;
}

CTMParameters *CTMEnvironment::GetTMParameters() CONST
{
	return m_pTMParameters[0];
}

CTMParameters *CTMEnvironment::GetSyntheticParameters() CONST
{
	return m_pTMParameters[1];
}

CTMProcessInfo *CTMEnvironment::GetTMProcessInfo() CONST
{
	return m_pTMProcessInfo;
}

COolParameters *CTMEnvironment::GetOolParameters() CONST
{
	return m_pOolParameters;
}

COversamplingParameters *CTMEnvironment::GetOversamplingParameters() CONST
{
	return m_pOversamplingParameters;
}

BOOL CTMEnvironment::MapTMUnit(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nData[2];
	TMUNITDATA  sData;

	for (nInfo.SetSize((sData.cbSize = sizeof(TMUNITDATA) + (sData.cbUnit = (GetTMUnit()->Map(nData[0])) ? (INT)nData[0].GetSize() : 0) + (sData.cbSavedParameters = (GetSyntheticParameters()->Map(nData[1])) ? (INT)nData[1].GetSize() : 0))); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TMUNITDATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TMUNITDATA)), nData[0].GetData(), sData.cbUnit);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbUnit), nData[1].GetData(), sData.cbSavedParameters);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMEnvironment::UnmapTMUnit(CONST CByteArray &nInfo)
{
	INT  cbData;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nData[2];
	CTMParameter  *pTMParameter;
	CTMParameter  *pSavedParameter;
	CTMParameters  pSavedParameters;
	TMUNITDATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TMUNITDATA)) ? sizeof(TMUNITDATA) : 0); nInfo.GetSize() >= sizeof(TMUNITDATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(TMUNITDATA) + sData.cbUnit + sData.cbSavedParameters && sData.cbUnit >= 0 && sData.cbSavedParameters >= 0; )
	{
		for (nData[0].SetSize(sData.cbUnit), nData[1].SetSize(sData.cbSavedParameters); nData[0].GetSize() == sData.cbUnit && nData[1].GetSize() == sData.cbSavedParameters; )
		{
			CopyMemory(nData[0].GetData(), nInfo.GetData() + (cbData = sizeof(TMUNITDATA)), sData.cbUnit);
			CopyMemory(nData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbUnit), sData.cbSavedParameters);
			for (nParameter = 0, nParameters = (pSavedParameters.Unmap(nData[1], -1, TRUE)) ? (INT)pSavedParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pTMParameter = ((pSavedParameter = pSavedParameters.GetAt(nParameter))) ? GetTMParameters()->GetAt(GetTMParameters()->Find(pSavedParameter->GetTag())) : (CTMParameter *)NULL))
				{
					pTMParameter->Update(pSavedParameter);
					continue;
				}
			}
			return GetTMUnit()->Unmap(nData[0]);
		}
		break;
	}
	return FALSE;
}

BOOL CTMEnvironment::Map(CByteArray &nInfo, CONST CTimeTag &tRetention) CONST
{
	INT  cbData;
	CByteArray  nData[3];
	TMENVIRONMENTDATA  sData;

	for (nInfo.SetSize((sData.cbSize = sizeof(TMENVIRONMENTDATA) + (sData.cbCache = (GetTMUnitCache()->Map(nData[0], tRetention)) ? (INT)nData[0].GetSize() : 0) + (sData.cbParameters = (GetTMParameters()->Map(nData[1], tRetention)) ? (INT)nData[1].GetSize() : 0) + (sData.cbProcessInfo = GetTMProcessInfo()->GetData(nData[2])))); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TMENVIRONMENTDATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TMENVIRONMENTDATA)), nData[0].GetData(), sData.cbCache);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbCache), nData[1].GetData(), sData.cbParameters);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbParameters), nData[2].GetData(), sData.cbProcessInfo);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMEnvironment::Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention)
{
	INT  cbData;
	CByteArray  nData[3];
	TMENVIRONMENTDATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TMENVIRONMENTDATA)) ? sizeof(TMENVIRONMENTDATA) : 0); nInfo.GetSize() >= sizeof(TMENVIRONMENTDATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(TMENVIRONMENTDATA) + sData.cbCache + sData.cbParameters + sData.cbProcessInfo && sData.cbCache >= 0 && sData.cbParameters >= 0 && sData.cbProcessInfo >= 0; )
	{
		for (nData[0].SetSize(sData.cbCache), nData[1].SetSize(sData.cbParameters), nData[2].SetSize(sData.cbProcessInfo); nData[0].GetSize() == sData.cbCache && nData[1].GetSize() == sData.cbParameters && nData[2].GetSize() == sData.cbProcessInfo; )
		{
			CopyMemory(nData[0].GetData(), nInfo.GetData() + (cbData = sizeof(TMENVIRONMENTDATA)), sData.cbCache);
			CopyMemory(nData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbCache), sData.cbParameters);
			CopyMemory(nData[2].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbParameters), sData.cbProcessInfo);
			if (GetTMUnitCache()->Unmap(nData[0], tRetention) && GetTMParameters()->Unmap(nData[1], tRetention))
			{
				GetTMProcessInfo()->SetData(nData[2]);
				Initialize(*GetOolParameters(), TRUE);
				return TRUE;
			}
			break;
		}
		break;
	}
	return FALSE;
}

BOOL CTMEnvironment::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTMEnvironment::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInfo

CTCProcessInfo::CTCProcessInfo() : CObject()
{
	m_pCriticalSection = new CCriticalSection;
}

CTCProcessInfo::~CTCProcessInfo()
{
	delete m_pCriticalSection;
}

BOOL CTCProcessInfo::SetData(CONST CByteArray &nData)
{
	return FALSE;
}

INT CTCProcessInfo::GetData(CByteArray &nData) CONST
{
	return 0;
}

VOID CTCProcessInfo::Reset()
{
	return;
}

BOOL CTCProcessInfo::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTCProcessInfo::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTCEnvironment

CTCEnvironment::CTCEnvironment() : CObject()
{
	m_nType = 0;
	m_nTCProcedureID = 0;
	m_pTCUnit = (CTCUnit *)NULL;
	m_pTCParameters = (CTCParameters *)NULL;
	m_pTCProcessInfo = (CTCProcessInfo *)NULL;
	m_hTCProcedureCodes = (HINSTANCE *)NULL;
	m_hTCProcedureEvents = (HANDLE *)NULL;
	m_hTCFunctionEvent[0] = (HANDLE)NULL;
	m_hTCFunctionEvent[1] = (HANDLE)NULL;
	m_hMessageEvent[0] = (HANDLE)NULL;
	m_hMessageEvent[1] = (HANDLE)NULL;
	m_pCriticalSection = new CCriticalSection;
}

CTCEnvironment::~CTCEnvironment()
{
	Destroy();
	delete m_pCriticalSection;
}

BOOL CTCEnvironment::Create(CONST CDatabaseEngine *pDatabase, BOOL bFull)
{
	for (Destroy(); (m_nType = pDatabase->GetType()) & DATABASE_TYPE_STANDARD_CCSDS; )
	{
		if ((m_pTCUnit = new CTCUnit) != (CTCUnit *)NULL)
		{
			if ((m_pTCParameters = new CTCParameters) != (CTCParameters *)NULL)
			{
				if ((m_hTCProcedureEvents = (LPHANDLE)GlobalAlloc(GPTR, sizeof(HANDLE))))
				{
					if ((m_hTCProcedureEvents[0] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
					{
						if ((m_hTCFunctionEvent[0] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
						{
							if ((m_hTCFunctionEvent[1] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, TRUE, TRUE, (LPCTSTR)NULL)))
							{
								if ((m_hMessageEvent[0] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
								{
									if ((m_hMessageEvent[1] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, TRUE, TRUE, (LPCTSTR)NULL)))
									{
										if ((bFull  &&  m_pTCParameters->Create(pDatabase)) || !bFull) return TRUE;
										CloseHandle(m_hMessageEvent[1]);
									}
									CloseHandle(m_hMessageEvent[0]);
								}
								CloseHandle(m_hTCFunctionEvent[1]);
							}
							CloseHandle(m_hTCFunctionEvent[0]);
						}
						CloseHandle(m_hTCProcedureEvents[0]);
					}
					GlobalFree(m_hTCProcedureEvents);
				}
				delete m_pTCParameters;
			}
			delete m_pTCUnit;
		}
		break;
	}
	m_nType = DATABASE_TYPE_NONE;
	m_pTCUnit = (CTCUnit *)NULL;
	m_pTCParameters = (CTCParameters *)NULL;
	m_hTCProcedureCodes = (HINSTANCE *)NULL;
	m_hTCProcedureEvents = (HANDLE *)NULL;
	m_hTCFunctionEvent[0] = (HANDLE)NULL;
	m_hTCFunctionEvent[1] = (HANDLE)NULL;
	m_hMessageEvent[0] = (HANDLE)NULL;
	m_hMessageEvent[1] = (HANDLE)NULL;
	return FALSE;
}

VOID CTCEnvironment::Destroy()
{
	for (Reset(); m_hTCProcedureEvents != (HANDLE *)NULL; )
	{
		CloseHandle(m_hTCProcedureEvents[0]);
		GlobalFree(m_hTCProcedureEvents);
		m_hTCProcedureEvents = (HANDLE *)NULL;
		break;
	}
	if (m_hTCProcedureCodes)
	{
		GlobalFree(m_hTCProcedureCodes);
		m_hTCProcedureCodes = (HINSTANCE *)NULL;
	}
	if (m_hTCFunctionEvent[0])
	{
		CloseHandle(m_hTCFunctionEvent[0]);
		m_hTCFunctionEvent[0] = (HANDLE)NULL;
	}
	if (m_hTCFunctionEvent[1])
	{
		CloseHandle(m_hTCFunctionEvent[1]);
		m_hTCFunctionEvent[1] = (HANDLE)NULL;
	}
	if (m_hMessageEvent[0])
	{
		CloseHandle(m_hMessageEvent[0]);
		m_hMessageEvent[0] = (HANDLE)NULL;
	}
	if (m_hMessageEvent[1])
	{
		CloseHandle(m_hMessageEvent[1]);
		m_hMessageEvent[1] = (HANDLE)NULL;
	}
	for (m_nType = DATABASE_TYPE_NONE; m_pTCUnit; )
	{
		delete m_pTCUnit;
		m_pTCUnit = (CTCUnit *)NULL;
		break;
	}
	if (m_pTCParameters)
	{
		delete m_pTCParameters;
		m_pTCParameters = (CTCParameters *)NULL;
	}
	if (m_pTCProcessInfo)
	{
		delete m_pTCProcessInfo;
		m_pTCProcessInfo = (CTCProcessInfo *)NULL;
	}
}

BOOL CTCEnvironment::Initialize(CTCProcessInfo *pInfo)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pTCProcessInfo = pInfo;
	return TRUE;
}
BOOL CTCEnvironment::Initialize(CTCParameters &pTCParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		for (nParameter = 0, nParameters = (INT)pTCParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pTCParameter[0] = pTCParameters.GetAt(nParameter)) != (CTCParameter *)NULL)
			{
				if ((pTCParameter[1] = GetTCParameters()->GetAt(GetTCParameters()->Find(pTCParameter[0]->GetTag()))))
				{
					pTCParameter[0]->Initialize(pTCParameter[1]);
					continue;
				}
			}
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	pTCParameters.Reset();
	return TRUE;
}

BOOL CTCEnvironment::Update(CONST CTCParameters &pTCParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetType() != DATABASE_TYPE_NONE)
	{
		for (nParameter = 0, nParameters = (INT)pTCParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pTCParameter[0] = pTCParameters.GetAt(nParameter)) != (CTCParameter *)NULL)
			{
				if ((pTCParameter[1] = GetTCParameters()->GetAt(GetTCParameters()->Find(pTCParameter[0]->GetTag()))))
				{
					pTCParameter[1]->Initialize(pTCParameter[0]);
					continue;
				}
			}
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	return FALSE;
}

INT CTCEnvironment::EnumTCProcedures(CStringArray &szNames, CUIntArray &nProcedureIDs, CPtrArray &hInstances) CONST
{
	INT  nProcedure;
	INT  nProcedures;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcedure = 0, nProcedures = (INT)m_szTCProcedures.GetSize(), szNames.Copy(m_szTCProcedures), nProcedureIDs.Copy(m_nTCProcedureIDs), hInstances.RemoveAll(); nProcedure < nProcedures; nProcedure++)
	{
		hInstances.Add(m_hTCProcedureCodes[nProcedure]);
		continue;
	}
	return((INT)szNames.GetSize());
}

INT CTCEnvironment::LoadTCProcedure(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, BOOL bDebugging, HINSTANCE &hInstance, CPtrArray &hEvents)
{
	INT  nID;
	CString  szCode[2];
	CString  szFileName[2];
	CFileFindEx  cFileFind[3];
	CDatabaseTCProcedure  *pProcedure;
	CSecurityDescriptor  cSecurityDescriptor;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (szFileName[0] = pDatabase->GetFileName(), szFileName[1] = pDatabase->GetUpdateFileName(); (pProcedure = pDatabase->GetTCProcedures()->GetAt(pDatabase->GetTCProcedures()->Find(pszName))); )
	{
		if ((cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile())
		{
			szCode[0].Format(STRING(IDS_TELECOMMANDPROCEDURECODE_NORMAL_FILENAME), pszName);
			szCode[1].Format(STRING(IDS_TELECOMMANDPROCEDURECODE_UPDATE_FILENAME), pszName);
			szCode[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[0];
			szCode[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[1];
			if (!bDebugging  &&  cFileFind[1].FindFile(szCode[1]) && !cFileFind[1].FindNextFile())
			{
				CFileEx::SetAttributes(szCode[0], CFileEx::GetAttributes(szCode[0]) & ~FILE_ATTRIBUTE_READONLY);
				CFileEx::SetAttributes(szCode[1], CFileEx::GetAttributes(szCode[1]) & ~FILE_ATTRIBUTE_READONLY);
				if (CFileEx::Copy(szCode[1], szCode[0]) && cFileFind[2].FindFile(szCode[0]) && !cFileFind[2].FindNextFile())
				{
					if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ))
					{
						CSecurity::SecureFile(cFileFind[2].GetFilePath(), cSecurityDescriptor);
						CFileEx::Remove(szCode[1]);
					}
					cFileFind[2].Close();
				}
				CFileEx::SetAttributes(szCode[0], CFileEx::GetAttributes(szCode[0]) | FILE_ATTRIBUTE_READONLY);
				CFileEx::SetAttributes(szCode[1], CFileEx::GetAttributes(szCode[1]) | FILE_ATTRIBUTE_READONLY);
				cFileFind[1].Close();
			}
			if ((bDebugging  &&  cFileFind[1].FindFile(szCode[1]) && !cFileFind[1].FindNextFile()) || (cFileFind[1].FindFile(szCode[0]) && !cFileFind[1].FindNextFile()))
			{
				if ((nID = LoadTCProcedure(pDatabase, cFileFind[1].GetFilePath(), pszName, hInstance, hEvents)) >= 0)
				{
					cFileFind[1].Close();
					cFileFind[0].Close();
					return nID;
				}
				cFileFind[1].Close();
			}
			cFileFind[0].Close();
		}
		break;
	}
	return -1;
}
INT CTCEnvironment::LoadTCProcedure(CONST CDatabaseEngine *pDatabase, LPCTSTR pszFileName, LPCTSTR pszName, HINSTANCE &hInstance, CPtrArray &hEvents)
{
	INT  nIndex;
	INT  nEvent;
	INT  nEvents;
	INT  nProcedure;
	INT  nProcedures;
	CFileFindEx  cFileFind;
	HANDLE  *hTCProcedureEvents;
	HINSTANCE  *hTCProcedureCodes;
	CDatabaseTCProcedure  *pProcedure;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcedure = (cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile()) ? pDatabase->GetTCProcedures()->GetAt(pDatabase->GetTCProcedures()->Find(pszName)) : (CDatabaseTCProcedure *)NULL))
	{
		if ((hInstance = ((hInstance = AfxLoadLibrary(cFileFind.GetFileName())) == (HINSTANCE)NULL) ? AfxLoadLibrary(cFileFind.GetFilePath()) : hInstance))
		{
			for (nProcedure = 0, nProcedures = (INT)m_nTCProcedureIDs.GetSize(), nIndex = 1; nProcedure < nProcedures; nProcedure++)
			{
				nIndex += m_nTCProcedureEventCount.GetAt(nProcedure);
				continue;
			}
			if ((hTCProcedureCodes = (nProcedures > 0) ? (HINSTANCE *)GlobalReAlloc(m_hTCProcedureCodes, (nProcedures + 1)*sizeof(HINSTANCE), GMEM_MOVEABLE | GMEM_ZEROINIT) : (HINSTANCE *)GlobalAlloc(GPTR, sizeof(HINSTANCE))))
			{
				if ((hTCProcedureEvents = (HANDLE *)GlobalReAlloc(m_hTCProcedureEvents, (nIndex + pProcedure->GetSize() + 3)*sizeof(HANDLE), GMEM_MOVEABLE | GMEM_ZEROINIT)))
				{
					for (nEvent = nIndex, nEvents = nIndex + (INT)pProcedure->GetSize() + 3, hEvents.RemoveAll(); nEvent < nEvents; nEvent++)
					{
						if ((hTCProcedureEvents[nEvent] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
						{
							hEvents.Add(hTCProcedureEvents[nEvent]);
							continue;
						}
						break;
					}
					if (nEvent == nEvents)
					{
						for (m_hTCProcedureCodes = hTCProcedureCodes, m_hTCProcedureEvents = hTCProcedureEvents, m_nTCProcedureID++; m_nTCProcedureID < 0; )
						{
							m_nTCProcedureID = 0;
							break;
						}
						m_szTCProcedures.Add(pszName);
						m_nTCProcedureIDs.Add(m_nTCProcedureID);
						m_nTCProcedureEventCount.Add(nEvents - nIndex);
						m_hTCProcedureCodes[nProcedures] = hInstance;
						cFileFind.Close();
						return m_nTCProcedureID;
					}
					for (; nEvent > nIndex; nEvent--)
					{
						CloseHandle(hTCProcedureEvents[nEvent - 1]);
						continue;
					}
					m_hTCProcedureEvents = hTCProcedureEvents;
				}
				m_hTCProcedureCodes = hTCProcedureCodes;
			}
			AfxFreeLibrary(hInstance);
		}
		cFileFind.Close();
	}
	return -1;
}
BOOL CTCEnvironment::LoadTCProcedure(CString &szName, va_list &pArgumentList, CPtrArray &pEvents)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_szDebugTCProcedures.GetSize() > 0)
	{
		szName = m_szDebugTCProcedures.GetAt(0);
		pArgumentList = (va_list)m_pDebugTCProcedureArguments.GetAt(0);
		pEvents.SetAtGrow(0, m_pDebugTCProcedureEvents[0].GetAt(0));
		pEvents.SetAtGrow(1, m_pDebugTCProcedureEvents[1].GetAt(0));
		pEvents.SetAtGrow(2, m_pDebugTCProcedureEvents[2].GetAt(0));
		m_szDebugTCProcedures.RemoveAt(0);
		m_pDebugTCProcedureArguments.RemoveAt(0);
		m_pDebugTCProcedureEvents[0].RemoveAt(0);
		m_pDebugTCProcedureEvents[1].RemoveAt(0);
		m_pDebugTCProcedureEvents[2].RemoveAt(0);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCEnvironment::CallTCProcedure(LPCTSTR pszName, va_list pArgumentList)
{
	INT  nIndex;
	INT  nCount;
	HANDLE  hEvents[2];

	if (Lock())
	{
		if ((hEvents[0] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
		{
			if ((hEvents[1] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
			{
				for (m_szDebugTCProcedures.Add(pszName), m_pDebugTCProcedureArguments.Add(pArgumentList), m_pDebugTCProcedureEvents[0].Add((HANDLE)NULL), m_pDebugTCProcedureEvents[1].Add(hEvents[0]), m_pDebugTCProcedureEvents[2].Add(hEvents[1]), Unlock(); SetEvent(m_hTCProcedureEvents[0]) && WaitForMultipleObjects(sizeof(hEvents) / sizeof(HANDLE), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0; )
				{
					CloseHandle(hEvents[1]);
					CloseHandle(hEvents[0]);
					return TRUE;
				}
				for (Lock(), nIndex = 0, nCount = (INT)m_szDebugTCProcedures.GetSize(); nIndex < nCount; nIndex++)
				{
					if (m_szDebugTCProcedures.GetAt(nIndex) == pszName  &&  m_pDebugTCProcedureArguments.GetAt(nIndex) == pArgumentList)
					{
						m_szDebugTCProcedures.RemoveAt(nIndex);
						m_pDebugTCProcedureArguments.RemoveAt(nIndex);
						m_pDebugTCProcedureEvents[0].RemoveAt(nIndex);
						m_pDebugTCProcedureEvents[1].RemoveAt(nIndex);
						m_pDebugTCProcedureEvents[2].RemoveAt(nIndex);
						break;
					}
				}
				if (nIndex == nCount)
				{
					CloseHandle(hEvents[1]);
					CloseHandle(hEvents[0]);
					Unlock();
					return TRUE;
				}
				CloseHandle(hEvents[1]);
			}
			CloseHandle(hEvents[0]);
		}
		Unlock();
	}
	return FALSE;
}

BOOL CTCEnvironment::StartTCProcedure(LPCTSTR pszName, va_list pArgumentList)
{
	INT  nIndex;
	INT  nCount;
	HANDLE  hEvents[2];

	if (Lock())
	{
		if ((hEvents[0] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
		{
			if ((hEvents[1] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL)))
			{
				for (m_szDebugTCProcedures.Add(pszName), m_pDebugTCProcedureArguments.Add(pArgumentList), m_pDebugTCProcedureEvents[0].Add(hEvents[0]), m_pDebugTCProcedureEvents[1].Add((HANDLE)NULL), m_pDebugTCProcedureEvents[2].Add(hEvents[1]), Unlock(); SetEvent(m_hTCProcedureEvents[0]) && WaitForMultipleObjects(sizeof(hEvents) / sizeof(HANDLE), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0; )
				{
					CloseHandle(hEvents[1]);
					CloseHandle(hEvents[0]);
					return TRUE;
				}
				for (Lock(), nIndex = 0, nCount = (INT)m_szDebugTCProcedures.GetSize(); nIndex < nCount; nIndex++)
				{
					if (m_szDebugTCProcedures.GetAt(nIndex) == pszName  &&  m_pDebugTCProcedureArguments.GetAt(nIndex) == pArgumentList)
					{
						m_szDebugTCProcedures.RemoveAt(nIndex);
						m_pDebugTCProcedureArguments.RemoveAt(nIndex);
						m_pDebugTCProcedureEvents[0].RemoveAt(nIndex);
						m_pDebugTCProcedureEvents[1].RemoveAt(nIndex);
						m_pDebugTCProcedureEvents[2].RemoveAt(nIndex);
						break;
					}
				}
				if (nIndex == nCount)
				{
					CloseHandle(hEvents[1]);
					CloseHandle(hEvents[0]);
					Unlock();
					return TRUE;
				}
				CloseHandle(hEvents[1]);
			}
			CloseHandle(hEvents[0]);
		}
		Unlock();
	}
	return FALSE;
}

HANDLE CTCEnvironment::SignalTCProcedure() CONST
{
	return m_hTCProcedureEvents[0];
}

BOOL CTCEnvironment::FreeTCProcedure(INT nID)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nEvent;
	INT  nEvents;
	INT  nProcedure;
	INT  nProcedures;
	CString  szProcedure;
	HANDLE  *hTCProcedureEvents;
	HINSTANCE  hTCProcedureCode;
	HINSTANCE  *hTCProcedureCodes;
	BOOL(__cdecl *pAbort)(INT nID);

	for (nProcedure = nProcedures = 0; Lock(); )
	{
		for (nProcedures = (INT)m_szTCProcedures.GetSize(); nProcedure < nProcedures; nProcedure++)
		{
			if (m_nTCProcedureIDs.GetAt(nProcedure) == (UINT)nID) break;
			continue;
		}
		hTCProcedureCode = (nProcedure < nProcedures) ? m_hTCProcedureCodes[nProcedure] : (HINSTANCE)NULL;
		Unlock();
		break;
	}
	if (nProcedure < nProcedures)
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		for (; (pAbort = (BOOL(__cdecl *)(INT nID)) GetProcAddress(hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)); )
		{
			(*pAbort)(nID);
			break;
		}
		if (AfxFreeLibrary(hTCProcedureCode))
		{
			for (Lock(), nProcedure = 0, nProcedures = (INT)m_nTCProcedureIDs.GetSize(), nCount = 1; nProcedure < nProcedures; nProcedure++)
			{
				nCount += m_nTCProcedureEventCount.GetAt(nProcedure);
				continue;
			}
			for (nProcedure = 0, nProcedures = (INT)m_nTCProcedureIDs.GetSize(), nIndex = 1; nProcedure < nProcedures; nProcedure++)
			{
				if (m_nTCProcedureIDs.GetAt(nProcedure) == nID) break;
				nIndex += m_nTCProcedureEventCount.GetAt(nProcedure);
			}
			if (nProcedure < nProcedures)
			{
				for (nEvent = nIndex, nEvents = nIndex + m_nTCProcedureEventCount.GetAt(nProcedure); nEvent < nEvents; nEvent++)
				{
					CloseHandle(m_hTCProcedureEvents[nEvent]);
					continue;
				}
				for (nEvent = nIndex, nEvents = nCount - m_nTCProcedureEventCount.GetAt(nProcedure); nEvent < nEvents; nEvent++)
				{
					m_hTCProcedureEvents[nEvent] = m_hTCProcedureEvents[nEvent + m_nTCProcedureEventCount.GetAt(nProcedure)];
					continue;
				}
				for (nItem = nProcedure, nItems = (INT)m_szTCProcedures.GetSize(); nItem < nItems - 1; nItem++)
				{
					m_hTCProcedureCodes[nItem] = m_hTCProcedureCodes[nItem + 1];
					continue;
				}
				for (m_szTCProcedures.RemoveAt(nProcedure), m_nTCProcedureIDs.RemoveAt(nProcedure), m_nTCProcedureEventCount.RemoveAt(nProcedure); (hTCProcedureCodes = (HINSTANCE *)GlobalReAlloc(m_hTCProcedureCodes, m_szTCProcedures.GetSize()*sizeof(HINSTANCE), GMEM_MOVEABLE | GMEM_ZEROINIT)); )
				{
					m_hTCProcedureCodes = hTCProcedureCodes;
					break;
				}
				for (; (hTCProcedureEvents = (HANDLE *)GlobalReAlloc(m_hTCProcedureEvents, nEvents*sizeof(HANDLE), GMEM_MOVEABLE | GMEM_ZEROINIT)); )
				{
					m_hTCProcedureEvents = hTCProcedureEvents;
					break;
				}
				for (nItem = 0, nItems = (INT)m_szTCFunctions[0].GetSize(); nItem < nItems; nItem++)
				{
					if (m_nTCFunctionProcedureIDs[0].GetAt(nItem) == nID)
					{
						m_szTCFunctions[0].RemoveAt(nItem);
						m_szTCFunctions[1].RemoveAt(nItem);
						m_szTCFunctions[2].RemoveAt(nItem);
						m_szTCFunctions[3].RemoveAt(nItem);
						m_tTCFunctions[0].RemoveAt(nItem);
						m_tTCFunctions[1].RemoveAt(nItem);
						m_tTCFunctions[2].RemoveAt(nItem);
						m_nTCFunctionProcedureIDs[0].RemoveAt(nItem);
						m_nTCFunctionProcedureIDs[1].RemoveAt(nItem);
						m_dwTCFunctionReleaseOffsets.RemoveAt(nItem);
						m_dwTCFunctionExecutionOffsets.RemoveAt(nItem);
						m_bTCFunctionExecutionFlags.RemoveAt(nItem);
						m_nTCFunctionEntryIDs[0].RemoveAt(nItem);
						m_nTCFunctionEntryIDs[1].RemoveAt(nItem);
						m_bTCFunctionTypes.RemoveAt(nItem);
						m_nTCFunctionBlockIDs.RemoveAt(nItem);
						m_bTCFunctionFlags[0].RemoveAt(nItem);
						m_bTCFunctionFlags[1].RemoveAt(nItem);
						m_nTCFunctionExeModes.RemoveAt(nItem);
						m_nTCFunctionAckFlags.RemoveAt(nItem);
						m_hTCFunctionEvents[0].RemoveAt(nItem);
						m_hTCFunctionEvents[1].RemoveAt(nItem);
						nItems--;
						nItem--;
					}
				}
				Unlock();
				return TRUE;
			}
			Unlock();
		}
	}
	return FALSE;
}

BOOL CTCEnvironment::AddTCFunction(INT nProcedureID, INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, LPCTSTR pszFunction, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, UINT nExecutionMode, ULONGLONG nAckFlags, HANDLE hSuccess, HANDLE hFailure)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szTCFunctions[0].Add(pszThread);
	m_szTCFunctions[1].Add(pszStep);
	m_szTCFunctions[2].Add(pszSequence);
	m_szTCFunctions[3].Add(pszFunction);
	m_tTCFunctions[0].Add(tScheduleTime);
	m_tTCFunctions[1].Add(tReleaseTime);
	m_tTCFunctions[2].Add(tExecutionTime);
	m_nTCFunctionProcedureIDs[0].Add(nProcedureID);
	m_nTCFunctionProcedureIDs[1].Add(nProcessID);
	m_dwTCFunctionReleaseOffsets.Add(dwReleaseOffset);
	m_dwTCFunctionExecutionOffsets.Add(dwExecutionOffset);
	m_bTCFunctionExecutionFlags.Add(bEarlierExecution);
	m_nTCFunctionEntryIDs[0].Add(nEntry);
	m_nTCFunctionEntryIDs[1].Add(nEntries);
	m_bTCFunctionTypes.Add(bProcedure);
	m_nTCFunctionBlockIDs.Add(nBlockID);
	m_bTCFunctionFlags[0].Add(bGrouped);
	m_bTCFunctionFlags[1].Add(bCritical);
	m_nTCFunctionExeModes.Add(nExecutionMode);
	m_nTCFunctionAckFlags.Add(nAckFlags);
	m_hTCFunctionEvents[0].Add(hSuccess);
	m_hTCFunctionEvents[1].Add(hFailure);
	ResetEvent(m_hTCFunctionEvent[1]);
	SetEvent(m_hTCFunctionEvent[0]);
	return TRUE;
}

BOOL CTCEnvironment::RemoveTCFunction(INT &nProcedureID, INT &nProcessID, CString &szThread, CString &szStep, CString &szSequence, CString &szFunction, BOOL &bProcedure, INT &nEntry, INT &nEntries, CTimeTag &tScheduleTime, CTimeTag &tReleaseTime, DWORD &dwReleaseOffset, CTimeTag &tExecutionTime, DWORD &dwExecutionOffset, BOOL &bEarlierExecution, INT &nBlockID, BOOL &bGrouped, BOOL &bCritical, UINT &nExecutionMode, ULONGLONG &nAckFlags, HANDLE &hSuccess, HANDLE &hFailure)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_szTCFunctions[0].GetSize() > 0)
	{
		szThread = m_szTCFunctions[0].GetAt(0);
		szStep = m_szTCFunctions[1].GetAt(0);
		szSequence = m_szTCFunctions[2].GetAt(0);
		szFunction = m_szTCFunctions[3].GetAt(0);
		tScheduleTime = m_tTCFunctions[0].GetAt(0);
		tReleaseTime = m_tTCFunctions[1].GetAt(0);
		tExecutionTime = m_tTCFunctions[2].GetAt(0);
		nProcedureID = m_nTCFunctionProcedureIDs[0].GetAt(0);
		nProcessID = m_nTCFunctionProcedureIDs[1].GetAt(0);
		dwReleaseOffset = m_dwTCFunctionReleaseOffsets.GetAt(0);
		dwExecutionOffset = m_dwTCFunctionExecutionOffsets.GetAt(0);
		bEarlierExecution = m_bTCFunctionExecutionFlags.GetAt(0);
		nEntry = m_nTCFunctionEntryIDs[0].GetAt(0);
		nEntries = m_nTCFunctionEntryIDs[1].GetAt(0);
		bProcedure = m_bTCFunctionTypes.GetAt(0);
		nBlockID = m_nTCFunctionBlockIDs.GetAt(0);
		bGrouped = m_bTCFunctionFlags[0].GetAt(0);
		bCritical = m_bTCFunctionFlags[1].GetAt(0);
		nExecutionMode = m_nTCFunctionExeModes.GetAt(0);
		nAckFlags = m_nTCFunctionAckFlags.GetAt(0);
		hSuccess = m_hTCFunctionEvents[0].GetAt(0);
		hFailure = m_hTCFunctionEvents[1].GetAt(0);
		m_szTCFunctions[0].RemoveAt(0);
		m_szTCFunctions[1].RemoveAt(0);
		m_szTCFunctions[2].RemoveAt(0);
		m_szTCFunctions[3].RemoveAt(0);
		m_tTCFunctions[0].RemoveAt(0);
		m_tTCFunctions[1].RemoveAt(0);
		m_tTCFunctions[2].RemoveAt(0);
		m_nTCFunctionProcedureIDs[0].RemoveAt(0);
		m_nTCFunctionProcedureIDs[1].RemoveAt(0);
		m_dwTCFunctionReleaseOffsets.RemoveAt(0);
		m_dwTCFunctionExecutionOffsets.RemoveAt(0);
		m_bTCFunctionExecutionFlags.RemoveAt(0);
		m_nTCFunctionEntryIDs[0].RemoveAt(0);
		m_nTCFunctionEntryIDs[1].RemoveAt(0);
		m_bTCFunctionTypes.RemoveAt(0);
		m_nTCFunctionBlockIDs.RemoveAt(0);
		m_bTCFunctionFlags[0].RemoveAt(0);
		m_bTCFunctionFlags[1].RemoveAt(0);
		m_nTCFunctionExeModes.RemoveAt(0);
		m_nTCFunctionAckFlags.RemoveAt(0);
		m_hTCFunctionEvents[0].RemoveAt(0);
		m_hTCFunctionEvents[1].RemoveAt(0);
		return TRUE;
	}
	SetEvent(m_hTCFunctionEvent[1]);
	return FALSE;
}

HANDLE CTCEnvironment::SignalTCFunctionQueue(BOOL bEmpty) CONST
{
	return((!bEmpty) ? m_hTCFunctionEvent[0] : m_hTCFunctionEvent[1]);
}

BOOL CTCEnvironment::AddMessage(LPCTSTR pszMessage)
{
	return AddMessage(-1, STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_SUCCESS), pszMessage);
}
BOOL CTCEnvironment::AddMessage(LPCTSTR pszType, LPCTSTR pszMessage)
{
	return AddMessage(-1, pszType, pszMessage);
}
BOOL CTCEnvironment::AddMessage(INT nID, LPCTSTR pszMessage)
{
	return AddMessage(nID, STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_SUCCESS), pszMessage);
}
BOOL CTCEnvironment::AddMessage(INT nID, LPCTSTR pszType, LPCTSTR pszMessage)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nMessageProcedureIDs.Add(nID);
	m_szMessages[0].Add(pszType);
	m_szMessages[1].Add(pszMessage);
	ResetEvent(m_hMessageEvent[1]);
	SetEvent(m_hMessageEvent[0]);
	return TRUE;
}

BOOL CTCEnvironment::RemoveMessage(CString &szMessage)
{
	INT  nID;
	CString  szType;

	return RemoveMessage(nID, szType, szMessage);
}
BOOL CTCEnvironment::RemoveMessage(CString &szType, CString &szMessage)
{
	INT  nID;

	return RemoveMessage(nID, szType, szMessage);
}
BOOL CTCEnvironment::RemoveMessage(INT &nID, CString &szMessage)
{
	CString  szType;

	return RemoveMessage(nID, szType, szMessage);
}
BOOL CTCEnvironment::RemoveMessage(INT &nID, CString &szType, CString &szMessage)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_nMessageProcedureIDs.GetSize() > 0)
	{
		nID = m_nMessageProcedureIDs.GetAt(0);
		szType = m_szMessages[0].GetAt(0);
		szMessage = m_szMessages[1].GetAt(0);
		m_nMessageProcedureIDs.RemoveAt(0);
		m_szMessages[0].RemoveAt(0);
		m_szMessages[1].RemoveAt(0);
		return TRUE;
	}
	SetEvent(m_hMessageEvent[1]);
	return FALSE;
}

HANDLE CTCEnvironment::SignalMessageQueue(BOOL bEmpty) CONST
{
	return((!bEmpty) ? m_hMessageEvent[0] : m_hMessageEvent[1]);
}

VOID CTCEnvironment::Reset()
{
	INT  nProcedure;
	INT  nProcedures;
	CTCUnit  *pTCUnit;
	CUIntArray  nProcedureIDs;
	CTCParameters  *pTCParameters;
	CTCProcessInfo  *pTCProcessInfo;

	if (Lock())
	{
		for (nProcedure = 0, nProcedures = (INT)m_szDebugTCProcedures.GetSize(); nProcedure < nProcedures; nProcedure++)
		{
			SetEvent((HANDLE)m_pDebugTCProcedureEvents[2].GetAt(nProcedure));
			continue;
		}
		for (nProcedure = 0, nProcedures = (INT)m_szTCProcedures.GetSize(); nProcedure < nProcedures; nProcedure++)
		{
			nProcedureIDs.Add(m_nTCProcedureIDs.GetAt(nProcedure));
			continue;
		}
		Unlock();
	}
	for (nProcedure = 0, nProcedures = (INT)nProcedureIDs.GetSize(); nProcedure < nProcedures; nProcedure++)
	{
		FreeTCProcedure(nProcedureIDs.GetAt(nProcedure));
		continue;
	}
	if (Lock())
	{
		if ((pTCUnit = GetTCUnit())) pTCUnit->Reset();
		if ((pTCParameters = GetTCParameters())) pTCParameters->Reset();
		if ((pTCProcessInfo = GetTCProcessInfo())) pTCProcessInfo->Reset();
		if (m_hTCProcedureEvents != (LPHANDLE)NULL) ResetEvent(m_hTCProcedureEvents[0]);
		if (m_hTCFunctionEvent[0] != (HANDLE)NULL) ResetEvent(m_hTCFunctionEvent[0]);
		if (m_hTCFunctionEvent[1] != (HANDLE)NULL) SetEvent(m_hTCFunctionEvent[1]);
		if (m_hMessageEvent[0] != (HANDLE)NULL) ResetEvent(m_hMessageEvent[0]);
		if (m_hMessageEvent[1] != (HANDLE)NULL) SetEvent(m_hMessageEvent[1]);
		m_szDebugTCProcedures.RemoveAll();
		m_pDebugTCProcedureArguments.RemoveAll();
		m_pDebugTCProcedureEvents[0].RemoveAll();
		m_pDebugTCProcedureEvents[1].RemoveAll();
		m_pDebugTCProcedureEvents[2].RemoveAll();
		m_szTCFunctions[0].RemoveAll();
		m_szTCFunctions[1].RemoveAll();
		m_szTCFunctions[2].RemoveAll();
		m_szTCFunctions[3].RemoveAll();
		m_tTCFunctions[0].RemoveAll();
		m_tTCFunctions[1].RemoveAll();
		m_tTCFunctions[2].RemoveAll();
		m_nTCFunctionProcedureIDs[0].RemoveAll();
		m_nTCFunctionProcedureIDs[1].RemoveAll();
		m_dwTCFunctionReleaseOffsets.RemoveAll();
		m_dwTCFunctionExecutionOffsets.RemoveAll();
		m_bTCFunctionExecutionFlags.RemoveAll();
		m_nTCFunctionEntryIDs[0].RemoveAll();
		m_nTCFunctionEntryIDs[1].RemoveAll();
		m_bTCFunctionTypes.RemoveAll();
		m_nTCFunctionBlockIDs.RemoveAll();
		m_bTCFunctionFlags[0].RemoveAll();
		m_bTCFunctionFlags[1].RemoveAll();
		m_nTCFunctionExeModes.RemoveAll();
		m_nTCFunctionAckFlags.RemoveAll();
		m_hTCFunctionEvents[0].RemoveAll();
		m_hTCFunctionEvents[1].RemoveAll();
		m_nMessageProcedureIDs.RemoveAll();
		m_szMessages[0].RemoveAll();
		m_szMessages[1].RemoveAll();
		Unlock();
	}
}

UINT CTCEnvironment::GetType() CONST
{
	return m_nType;
}

CTCUnit *CTCEnvironment::GetTCUnit() CONST
{
	return(((GetType() & DATABASE_TYPE_STANDARD_CCSDS) == DATABASE_TYPE_STANDARD_CCSDS) ? m_pTCUnit : (CTCUnit *)NULL);
}

CTCParameters *CTCEnvironment::GetTCParameters() CONST
{
	return m_pTCParameters;
}

CTCProcessInfo *CTCEnvironment::GetTCProcessInfo() CONST
{
	return m_pTCProcessInfo;
}

BOOL CTCEnvironment::MapTCUnit(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nData;
	TCUNITDATA  sData;

	for (nInfo.SetSize((sData.cbSize = sizeof(TCUNITDATA) + (sData.cbUnit = (GetTCUnit()->Map(nData)) ? (INT)nData.GetSize() : 0))); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCUNITDATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TCUNITDATA)), nData.GetData(), sData.cbUnit);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCEnvironment::UnmapTCUnit(CONST CByteArray &nInfo)
{
	INT  cbData;
	CByteArray  nData;
	TCUNITDATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCUNITDATA)) ? sizeof(TCUNITDATA) : 0); nInfo.GetSize() >= sizeof(TCUNITDATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(TCUNITDATA) + sData.cbUnit && sData.cbUnit >= 0; )
	{
		for (nData.SetSize(sData.cbUnit); nData.GetSize() == sData.cbUnit; )
		{
			CopyMemory(nData.GetData(), nInfo.GetData() + (cbData = sizeof(TCUNITDATA)), sData.cbUnit);
			return GetTCUnit()->Unmap(nData);
		}
		break;
	}
	return FALSE;
}

BOOL CTCEnvironment::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nData[2];
	TCENVIRONMENTDATA  sData;

	for (nInfo.SetSize((sData.cbSize = sizeof(TCENVIRONMENTDATA) + (sData.cbParameters = (GetTCParameters()->Map(nData[0])) ? (INT)nData[0].GetSize() : 0) + (sData.cbProcessInfo = GetTCProcessInfo()->GetData(nData[1])))); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCENVIRONMENTDATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TCENVIRONMENTDATA)), nData[0].GetData(), sData.cbParameters);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbParameters), nData[1].GetData(), sData.cbProcessInfo);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCEnvironment::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	CByteArray  nData[2];
	TCENVIRONMENTDATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCENVIRONMENTDATA)) ? sizeof(TCENVIRONMENTDATA) : 0); nInfo.GetSize() >= sizeof(TCENVIRONMENTDATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(TCENVIRONMENTDATA) + sData.cbParameters + sData.cbProcessInfo && sData.cbParameters >= 0 && sData.cbProcessInfo >= 0; )
	{
		for (nData[0].SetSize(sData.cbParameters), nData[1].SetSize(sData.cbProcessInfo); nData[0].GetSize() == sData.cbParameters && nData[1].GetSize() == sData.cbProcessInfo; )
		{
			CopyMemory(nData[0].GetData(), nInfo.GetData() + (cbData = sizeof(TCENVIRONMENTDATA)), sData.cbParameters);
			CopyMemory(nData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbParameters), sData.cbProcessInfo);
			if (GetTCParameters()->Unmap(nData[0]))
			{
				GetTCProcessInfo()->SetData(nData[1]);
				return TRUE;
			}
			break;
		}
		break;
	}
	return FALSE;
}

BOOL CTCEnvironment::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTCEnvironment::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsServiceEngine

CMemoryDumpsServiceEngine::CMemoryDumpsServiceEngine() : CObject()
{
	m_hEngine = (HINSTANCE)NULL;
	m_pEngine = (CMemoryDumpsServiceEngine *)NULL;
}

CMemoryDumpsServiceEngine::~CMemoryDumpsServiceEngine()
{
	Close();
}

BOOL CMemoryDumpsServiceEngine::Open(LPCTSTR pszName)
{
	CString  szEngine;
	CMemoryDumpsServiceEngine *(__cdecl *pEngine)(VOID);

	if (IsOpen())
	{
		if (GetName() == pszName) return TRUE;
		Close();
	}
	if ((m_hEngine = AfxLoadLibrary(pszName)))
	{
#ifndef UNICODE
		szEngine = STRING(IDS_EXPORTINTERFACE_MEMORYDUMPSSERVICEENGINE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_MEMORYDUMPSSERVICEENGINE), -1, (LPSTR)szEngine.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_MEMORYDUMPSSERVICEENGINE))), lstrlen(STRING(IDS_EXPORTINTERFACE_MEMORYDUMPSSERVICEENGINE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szEngine.ReleaseBuffer();
#endif
		if ((pEngine = (CMemoryDumpsServiceEngine *(__cdecl *)(VOID)) GetProcAddress(m_hEngine, (LPCSTR)(LPCTSTR)szEngine)))
		{
			pEngine()->m_pEngine = m_pEngine = pEngine();
			m_pEngine->m_szEngine = m_szEngine = pszName;
			return TRUE;
		}
		Close();
	}
	return FALSE;
}

BOOL CMemoryDumpsServiceEngine::IsOpen() CONST
{
	return(m_pEngine != (CMemoryDumpsServiceEngine *)NULL);
}

VOID CMemoryDumpsServiceEngine::Close()
{
	for (m_szEngine.Empty(); m_pEngine != (CMemoryDumpsServiceEngine *)NULL; )
	{
		m_pEngine->m_szEngine.Empty();
		break;
	}
	if (m_hEngine != (HINSTANCE)NULL)
	{
		AfxFreeLibrary(m_hEngine);
		m_hEngine = (HINSTANCE)NULL;
	}
	m_pEngine = (CMemoryDumpsServiceEngine *)NULL;
}

CString CMemoryDumpsServiceEngine::GetName() CONST
{
	return m_szEngine;
}

CMemoryDumpsServiceEngine *CMemoryDumpsServiceEngine::GetMemoryDumpsServiceEngine() CONST
{
	return m_pEngine;
}

UINT CMemoryDumpsServiceEngine::EnumMemoryDumpSources() CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumMemoryDumpSources() : 0);
}
INT CMemoryDumpsServiceEngine::EnumMemoryDumpSources(CStringArray &szSources) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumMemoryDumpSources(szSources) : 0);
}

UINT CMemoryDumpsServiceEngine::TranslateMemoryDumpSource(LPCTSTR pszSource) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->TranslateMemoryDumpSource(pszSource) : 0);
}
CString CMemoryDumpsServiceEngine::TranslateMemoryDumpSource(UINT nSource) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->TranslateMemoryDumpSource(nSource) : EMPTYSTRING);
}

UINT CMemoryDumpsServiceEngine::DetermineMemoryDumpSource(LPCTSTR pszTag) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->DetermineMemoryDumpSource(pszTag) : 0);
}

BOOL CMemoryDumpsServiceEngine::IsMemoryDumpByAddressRange(UINT nSource) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->IsMemoryDumpByAddressRange(nSource) : FALSE);
}

BOOL CMemoryDumpsServiceEngine::IsMemoryDumpByRegisters(UINT nSource) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->IsMemoryDumpByRegisters(nSource) : FALSE);
}

UINT CMemoryDumpsServiceEngine::EnumMemoryDumpFormatTypes() CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumMemoryDumpFormatTypes() : 0);
}
INT CMemoryDumpsServiceEngine::EnumMemoryDumpFormatTypes(CStringArray &szTypes) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumMemoryDumpFormatTypes(szTypes) : 0);
}

UINT CMemoryDumpsServiceEngine::TranslateMemoryDumpFormatType(LPCTSTR pszType) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->TranslateMemoryDumpFormatType(pszType) : 0);
}
CString CMemoryDumpsServiceEngine::TranslateMemoryDumpFormatType(UINT nType) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->TranslateMemoryDumpFormatType(nType) : EMPTYSTRING);
}

UINT CMemoryDumpsServiceEngine::EnumMemoryDumpFileFormats(UINT nSource) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumMemoryDumpFileFormats(nSource) : 0);
}

INT CMemoryDumpsServiceEngine::ProcessTMUnit(CONST CTMEnvironment *pTMEnvironment, CONST CMemoryDumps &pMemoryDumps, BOOL bUnicode) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetMemoryDumpsServiceEngine()->ProcessTMUnit(pTMEnvironment, pMemoryDumps, bUnicode) : FALSE);
}

INT CMemoryDumpsServiceEngine::ProcessTMDump(CMemoryDump *pMemoryDump, BOOL bUnicode) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->ProcessTMDump(pMemoryDump, bUnicode) : FALSE);
}

CString CMemoryDumpsServiceEngine::GetMemoryDumpFileName(CONST CMemoryDump *pMemoryDump, LPCTSTR pszPrefix, CONST CTimeTag &tTimeTag, LPCTSTR pszExtension) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetMemoryDumpFileName(pMemoryDump, pszPrefix, tTimeTag, pszExtension) : EMPTYSTRING);
}

CString CMemoryDumpsServiceEngine::GetMemoryDumpFTPFileName(CONST CMemoryDump *pMemoryDump, UINT nFormat) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetMemoryDumpFTPFileName(pMemoryDump, nFormat) : EMPTYSTRING);
}

CString CMemoryDumpsServiceEngine::GetMemoryDumpSearchFileName(LPCTSTR pszPrefix, LPCTSTR pszExtension) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetMemoryDumpSearchFileName(pszPrefix, pszExtension) : EMPTYSTRING);
}

CTimeSpan CMemoryDumpsServiceEngine::GetMemoryDumpInterval(UINT nSource, UINT nSubSystem) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetMemoryDumpInterval(nSource, nSubSystem) : 0);
}

UINT CMemoryDumpsServiceEngine::GetMemoryDumpIntervalTolerance(UINT nSource, UINT nSubSystem) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetMemoryDumpIntervalTolerance(nSource, nSubSystem) : 0);
}

CString CMemoryDumpsServiceEngine::FormatMemoryDumpData(CONST CMemoryDump *pMemoryDump, UINT nFormat) CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->FormatMemoryDumpData(pMemoryDump, nFormat) : EMPTYSTRING);
}

BOOL CMemoryDumpsServiceEngine::IsServiceSupported() CONST
{
	return((m_pEngine != (CMemoryDumpsServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->IsServiceSupported() : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceEngine

CTPEPServiceEngine::CTPEPServiceEngine() : CObject()
{
	m_hEngine = (HINSTANCE)NULL;
	m_pEngine = (CTPEPServiceEngine *)NULL;
}

CTPEPServiceEngine::~CTPEPServiceEngine()
{
	Close();
}

BOOL CTPEPServiceEngine::Open(LPCTSTR pszName)
{
	CString  szEngine;
	CTPEPServiceEngine *(__cdecl *pEngine)(VOID);

	if (IsOpen())
	{
		if (GetName() == pszName) return TRUE;
		Close();
	}
	if ((m_hEngine = AfxLoadLibrary(pszName)))
	{
#ifndef UNICODE
		szEngine = STRING(IDS_EXPORTINTERFACE_TPEPSERVICEENGINE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_TPEPSERVICEENGINE), -1, (LPSTR)szEngine.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_TPEPSERVICEENGINE))), lstrlen(STRING(IDS_EXPORTINTERFACE_TPEPSERVICEENGINE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szEngine.ReleaseBuffer();
#endif
		if ((pEngine = (CTPEPServiceEngine *(__cdecl *)(VOID)) GetProcAddress(m_hEngine, (LPCSTR)(LPCTSTR)szEngine)))
		{
			pEngine()->m_pEngine = m_pEngine = pEngine();
			m_pEngine->m_szEngine = m_szEngine = pszName;
			return TRUE;
		}
		Close();
	}
	return FALSE;
}

BOOL CTPEPServiceEngine::IsOpen() CONST
{
	return(m_pEngine != (CTPEPServiceEngine *)NULL);
}

VOID CTPEPServiceEngine::Close()
{
	for (m_szEngine.Empty(); m_pEngine != (CTPEPServiceEngine *)NULL; )
	{
		m_pEngine->m_szEngine.Empty();
		break;
	}
	if (m_hEngine != (HINSTANCE)NULL)
	{
		AfxFreeLibrary(m_hEngine);
		m_hEngine = (HINSTANCE)NULL;
	}
	m_pEngine = (CTPEPServiceEngine *)NULL;
}

CString CTPEPServiceEngine::GetName() CONST
{
	return m_szEngine;
}

CTPEPServiceEngine *CTPEPServiceEngine::GetTPEPServiceEngine() CONST
{
	return m_pEngine;
}

UINT CTPEPServiceEngine::GetTPEPSupport() CONST
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetTPEPSupport() : 0);
}

UINT CTPEPServiceEngine::GetTPEPSpacecraftID() CONST
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetTPEPSpacecraftID() : 0);
}

CString CTPEPServiceEngine::GetTPEPTimeKeyFormat() CONST
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetTPEPTimeKeyFormat() : EMPTYSTRING);
}

CString CTPEPServiceEngine::GetTPEPRetrieveTimeKeyFormat() CONST
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GetTPEPRetrieveTimeKeyFormat() : EMPTYSTRING);
}

INT CTPEPServiceEngine::EnumTPEPTMUnits(CONST CDatabaseEngine *pDatabase, CONST CStringArray &szParameters, CStringArray &szTMUnits) CONST
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumTPEPTMUnits(pDatabase, szParameters, szTMUnits) : 0);
}

INT CTPEPServiceEngine::EnumTPEPTMUnitParameters(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CTPEPConnection *pConnection, BOOL bAll, CStringArray &szParameters) CONST
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->EnumTPEPTMUnitParameters(pDatabase, pTMUnit, pConnection, bAll, szParameters) : 0);
}

BOOL CTPEPServiceEngine::GenerateTPEPRandomData(CONST CDatabaseEngine *pDatabase, CTPEPConnection *pConnection, CTMEnvironment *pTMEnvironment)
{
	return((m_pEngine != (CTPEPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->GenerateTPEPRandomData(pDatabase, pConnection, pTMEnvironment) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceEngine

CPFLPServiceEngine::CPFLPServiceEngine() : CObject()
{
	m_hEngine = (HINSTANCE)NULL;
	m_pEngine = (CPFLPServiceEngine *)NULL;
}

CPFLPServiceEngine::~CPFLPServiceEngine()
{
	Close();
}

BOOL CPFLPServiceEngine::Open(LPCTSTR pszName)
{
	CString  szEngine;
	CPFLPServiceEngine *(__cdecl *pEngine)(VOID);

	if (IsOpen())
	{
		if (GetName() == pszName) return TRUE;
		Close();
	}
	if ((m_hEngine = AfxLoadLibrary(pszName)))
	{
#ifndef UNICODE
		szEngine = STRING(IDS_EXPORTINTERFACE_PFLPSERVICEENGINE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_PFLPSERVICEENGINE), -1, (LPSTR)szEngine.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_PFLPSERVICEENGINE))), lstrlen(STRING(IDS_EXPORTINTERFACE_PFLPSERVICEENGINE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szEngine.ReleaseBuffer();
#endif
		if ((pEngine = (CPFLPServiceEngine *(__cdecl *)(VOID)) GetProcAddress(m_hEngine, (LPCSTR)(LPCTSTR)szEngine)))
		{
			pEngine()->m_pEngine = m_pEngine = pEngine();
			m_pEngine->m_szEngine = m_szEngine = pszName;
			return TRUE;
		}
		Close();
	}
	return FALSE;
}

BOOL CPFLPServiceEngine::IsOpen() CONST
{
	return(m_pEngine != (CPFLPServiceEngine *)NULL);
}

VOID CPFLPServiceEngine::Close()
{
	for (m_szEngine.Empty(); m_pEngine != (CPFLPServiceEngine *)NULL; )
	{
		m_pEngine->m_szEngine.Empty();
		break;
	}
	if (m_hEngine != (HINSTANCE)NULL)
	{
		AfxFreeLibrary(m_hEngine);
		m_hEngine = (HINSTANCE)NULL;
	}
	m_pEngine = (CPFLPServiceEngine *)NULL;
}

CString CPFLPServiceEngine::GetName() CONST
{
	return m_szEngine;
}

CPFLPServiceEngine *CPFLPServiceEngine::GetPFLPServiceEngine() CONST
{
	return m_pEngine;
}

BOOL CPFLPServiceEngine::IsServiceSupported() CONST
{
	return((m_pEngine != (CPFLPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->IsServiceSupported() : FALSE);
}

BOOL CPFLPServiceEngine::FilterPFLPTMUnits(CONST CTMEnvironment *pTMEnvironment, BYTE nManipulationCode, BYTE nGroupIdentifier, WORD wDataIdentifier) CONST
{
	return((m_pEngine != (CPFLPServiceEngine *)NULL  &&  m_pEngine != this) ? m_pEngine->FilterPFLPTMUnits(pTMEnvironment, nManipulationCode, nGroupIdentifier, wDataIdentifier) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTMProcessEngine

CTMProcessEngine::CTMProcessEngine() : CObject()
{
	m_hTMEngine = (HINSTANCE)NULL;
	m_pTMEngine = (CTMProcessEngine *)NULL;
}

CTMProcessEngine::~CTMProcessEngine()
{
	Close();
}

BOOL CTMProcessEngine::Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, CTMEnvironment *pTMEnvironment)
{
	CString  szTMEngine;
	CString  szTMParameters;
	CTMProcessEngine *(__cdecl *pTMEngine)(VOID);
	BOOL(__cdecl *pTMParameters)(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment);

	if (IsOpen())
	{
		if (GetName() == pszName) return TRUE;
		Close();
	}
	if ((m_hTMEngine = AfxLoadLibrary(pszName)))
	{
#ifndef UNICODE
		szTMEngine = STRING(IDS_EXPORTINTERFACE_TMPROCESSENGINE);
		szTMParameters = STRING(IDS_EXPORTINTERFACE_INITIALIZEPARAMETERS);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_TMPROCESSENGINE), -1, (LPSTR)szTMEngine.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_TMPROCESSENGINE))), lstrlen(STRING(IDS_EXPORTINTERFACE_TMPROCESSENGINE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZEPARAMETERS), -1, (LPSTR)szTMParameters.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szTMParameters.ReleaseBuffer();
		szTMEngine.ReleaseBuffer();
#endif
		if ((pTMEngine = (CTMProcessEngine *(__cdecl *)(VOID)) GetProcAddress(m_hTMEngine, (LPCSTR)(LPCTSTR)szTMEngine)))
		{
			if ((pTMParameters = (BOOL(__cdecl *)(CONST CDatabaseEngine *, CTMEnvironment *)) GetProcAddress(pDatabase->GetLibrary(), (LPCSTR)(LPCTSTR)szTMParameters)))
			{
				for (pTMEngine()->FreeTMProcessInfo(pTMEnvironment); pTMEngine()->AllocateTMProcessInfo(pTMEnvironment); )
				{
					if (!pTMEnvironment->GetTMParameters() || !pTMEnvironment->GetTMParameters()->GetSize() || (*pTMParameters)(pDatabase, pTMEnvironment))
					{
						pTMEngine()->m_pTMEngine = m_pTMEngine = pTMEngine();
						m_pTMEngine->m_szTMEngine = m_szTMEngine = pszName;
						return TRUE;
					}
					break;
				}
				pTMEnvironment->Initialize();
			}
		}
		Close();
	}
	return FALSE;
}

BOOL CTMProcessEngine::IsOpen() CONST
{
	return(m_pTMEngine != (CTMProcessEngine *)NULL);
}

VOID CTMProcessEngine::Close()
{
	for (m_szTMEngine.Empty(); m_pTMEngine != (CTMProcessEngine *)NULL; )
	{
		m_pTMEngine->m_szTMEngine.Empty();
		break;
	}
	if (m_hTMEngine != (HINSTANCE)NULL)
	{
		AfxFreeLibrary(m_hTMEngine);
		m_hTMEngine = (HINSTANCE)NULL;
	}
	m_pTMEngine = (CTMProcessEngine *)NULL;
}

CString CTMProcessEngine::GetName() CONST
{
	return m_szTMEngine;
}

CTMProcessEngine *CTMProcessEngine::GetTMProcessEngine() CONST
{
	return m_pTMEngine;
}

BOOL CTMProcessEngine::SetSpacecraftID(UINT nID)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->SetSpacecraftID(nID) : FALSE);
}

UINT CTMProcessEngine::GetSpacecraftID() CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetSpacecraftID() : 0);
}

UINT CTMProcessEngine::DetectTMServiceLevel() CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->DetectTMServiceLevel() : 0);
}

BOOL CTMProcessEngine::SetCommandLinkControlWord(DWORD dwCLCW)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->SetCommandLinkControlWord(dwCLCW) : FALSE);
}

DWORD CTMProcessEngine::GetCommandLinkControlWord() CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetCommandLinkControlWord() : 0);
}

INT CTMProcessEngine::EnumSubSystems(CStringArray &szSubSystems, BOOL bAll) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->EnumSubSystems(szSubSystems, bAll) : 0);
}

UINT CTMProcessEngine::TranslateSubSystemToID(LPCTSTR pszSubSystem) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->TranslateSubSystemToID(pszSubSystem) : (UINT)-1);
}

CString CTMProcessEngine::TranslateIDToSubSystem(UINT nSubSystemID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->TranslateIDToSubSystem(nSubSystemID) : EMPTYSTRING);
}

INT CTMProcessEngine::ProcessTMTransferUnit(CONST CDatabaseEngine *pDatabase, CONST CTMTransferUnit *pTMTransferUnit, CTMEnvironment *pTMEnvironment)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->ProcessTMTransferUnit(pDatabase, pTMTransferUnit, pTMEnvironment) : -1);
}

INT CTMProcessEngine::ProcessTMUnit(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CTMEnvironment *pTMEnvironment)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->ProcessTMUnit(pDatabase, pTMUnit, pTMEnvironment) : -1);
}

BOOL CTMProcessEngine::IsTMDump(CONST CTMEnvironment *pTMEnvironment) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->IsTMDump(pTMEnvironment) : FALSE);
}

UINT CTMProcessEngine::GetTMUnitID(CONST CTMUnit *pTMUnit) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTMUnitID(pTMUnit) : 0);
}

BOOL CTMProcessEngine::SetTimeCorrelation(CTMEnvironment *pTMEnvironment)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->SetTimeCorrelation(pTMEnvironment) : FALSE);
}
BOOL CTMProcessEngine::SetTimeCorrelation(CTMEnvironment *pTMEnvironment, CONST CTimeTag &tOBRT, UINT nOBRT, UINT nOBTID)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->SetTimeCorrelation(pTMEnvironment, tOBRT, nOBRT, nOBTID) : FALSE);
}

BOOL CTMProcessEngine::GetTimeCorrelation(CONST CTMEnvironment *pTMEnvironment, CTimeTag &tOBRT, UINT &nOBRT, UINT nOBTID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTimeCorrelation(pTMEnvironment, tOBRT, nOBRT, nOBTID) : FALSE);
}

BOOL CTMProcessEngine::SetTimeCorrelationError(CONST CTMEnvironment *pTMEnvironment, LONG tError, LONG tDelta, UINT nOBTID)
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->SetTimeCorrelationError(pTMEnvironment, tError, tDelta, nOBTID) : FALSE);
}

BOOL CTMProcessEngine::GetTimeCorrelationError(CONST CTMEnvironment *pTMEnvironment, LONG &tError, LONG &tDelta, UINT nOBTID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTimeCorrelationError(pTMEnvironment, tError, tDelta, nOBTID) : FALSE);
}

UINT CTMProcessEngine::GetTimeCorrelationDelay(UINT nOBTID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTimeCorrelationDelay(nOBTID) : 0);
}

UINT CTMProcessEngine::GetTimeCorrelationRange(UINT nOBTID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTimeCorrelationRange(nOBTID) : 0);
}

CTimeTag CTMProcessEngine::Correlate(CONST CTMEnvironment *pTMEnvironment, UINT tField, INT nLength, BOOL bCorrelate, UINT nOBTID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->Correlate(pTMEnvironment, tField, nLength, bCorrelate, nOBTID) : 0);
}

BOOL CTMProcessEngine::CanCorrelate(CONST CTMEnvironment *pTMEnvironment, UINT nOBTID) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->CanCorrelate(pTMEnvironment, nOBTID) : FALSE);
}

CTimeSpan CTMProcessEngine::GetTMStreamInterruptionInterval() CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTMStreamInterruptionInterval() : 0);
}

CTimeSpan CTMProcessEngine::GetTMStreamDelayInterval() CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->GetTMStreamDelayInterval() : 0);
}

BOOL CTMProcessEngine::CheckTMStreamInterruption(TIMETAG tInterval) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->CheckTMStreamInterruption(tInterval) : FALSE);
}

BOOL CTMProcessEngine::CheckTMStreamDelay(TIMETAG tDelay, TIMETAG tInterval) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->CheckTMStreamDelay(tDelay, tInterval) : FALSE);
}

BOOL CTMProcessEngine::CheckTMStreamCorrelation(CONST CTMEnvironment *pTMEnvironment) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->CheckTMStreamCorrelation(pTMEnvironment) : FALSE);
}

BOOL CTMProcessEngine::CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTMParameter *pTMParameter, INT nCalTableRef, INT nOolTableRef, ULONGLONG nValue, UINT &nOolLimit, UINT &nOolStatus) CONST
{
	return CheckTMParameterOolStatus(pDatabase, pTMEnvironment, pTMParameter, nCalTableRef, nOolTableRef, nValue, 0, -1, FALSE, nOolLimit, nOolStatus);
}
BOOL CTMProcessEngine::CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTMParameter *pTMParameter, INT nCalTableRef, INT nOolTableRef, ULONGLONG nValue, ULONGLONG nOldValue, INT nOldCalTableRef, BOOL bOldValue, UINT &nOolLimit, UINT &nOolStatus) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->CheckTMParameterOolStatus(pDatabase, pTMEnvironment, pTMParameter, nCalTableRef, nOolTableRef, nValue, nOldValue, nOldCalTableRef, bOldValue, nOolLimit, nOolStatus) : FALSE);
}

BOOL CTMProcessEngine::ConvertTMParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTMParameter *pTMParameter, INT nCalTableRef, LPCTSTR pszValue, ULONGLONG &nValue) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->ConvertTMParameterValue(pDatabase, pTMParameter, nCalTableRef, pszValue, nValue) : FALSE);
}

BOOL CTMProcessEngine::AllocateTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->AllocateTMProcessInfo(pTMEnvironment) : FALSE);
}

BOOL CTMProcessEngine::FreeTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST
{
	return((m_pTMEngine != (CTMProcessEngine *)NULL  &&  m_pTMEngine != this) ? m_pTMEngine->FreeTMProcessInfo(pTMEnvironment) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessEngine

CTCProcessEngine::CTCProcessEngine() : CObject()
{
	m_hTCEngine = (HINSTANCE)NULL;
	m_pTCEngine = (CTCProcessEngine *)NULL;
}

CTCProcessEngine::~CTCProcessEngine()
{
	Close();
}

BOOL CTCProcessEngine::Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, CTCEnvironment *pTCEnvironment)
{
	CString  szTCEngine;
	CTCProcessEngine *(__cdecl *pTCEngine)(VOID);

	if (IsOpen())
	{
		if (GetName() == pszName) return TRUE;
		Close();
	}
	if ((m_hTCEngine = AfxLoadLibrary(pszName)))
	{
#ifndef UNICODE
		szTCEngine = STRING(IDS_EXPORTINTERFACE_TCPROCESSENGINE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_TCPROCESSENGINE), -1, (LPSTR)szTCEngine.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_TCPROCESSENGINE))), lstrlen(STRING(IDS_EXPORTINTERFACE_TCPROCESSENGINE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szTCEngine.ReleaseBuffer();
#endif
		if ((pTCEngine = (CTCProcessEngine *(__cdecl *)(VOID)) GetProcAddress(m_hTCEngine, (LPCSTR)(LPCTSTR)szTCEngine)))
		{
			for (pTCEngine()->FreeTCProcessInfo(pTCEnvironment); pTCEngine()->AllocateTCProcessInfo(pTCEnvironment); )
			{
				pTCEngine()->m_pTCEngine = m_pTCEngine = pTCEngine();
				m_pTCEngine->m_szTCEngine = m_szTCEngine = pszName;
				return TRUE;
			}
			pTCEnvironment->Initialize();
		}
		Close();
	}
	return FALSE;
}

BOOL CTCProcessEngine::IsOpen() CONST
{
	return(m_pTCEngine != (CTCProcessEngine *)NULL);
}

VOID CTCProcessEngine::Close()
{
	for (m_szTCEngine.Empty(); m_pTCEngine != (CTCProcessEngine *)NULL; )
	{
		m_pTCEngine->m_szTCEngine.Empty();
		break;
	}
	if (m_hTCEngine != (HINSTANCE)NULL)
	{
		AfxFreeLibrary(m_hTCEngine);
		m_hTCEngine = (HINSTANCE)NULL;
	}
	m_pTCEngine = (CTCProcessEngine *)NULL;
}

CString CTCProcessEngine::GetName() CONST
{
	return m_szTCEngine;
}

CTCProcessEngine *CTCProcessEngine::GetTCProcessEngine() CONST
{
	return m_pTCEngine;
}

BOOL CTCProcessEngine::SetSpacecraftID(UINT nID)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->SetSpacecraftID(nID) : FALSE);
}

UINT CTCProcessEngine::GetSpacecraftID() CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->GetSpacecraftID() : 0);
}

BOOL CTCProcessEngine::SetVirtualChannel(UINT nChannel)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->SetVirtualChannel(nChannel) : FALSE);
}

UINT CTCProcessEngine::GetVirtualChannel() CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->GetVirtualChannel() : 0);
}

UINT CTCProcessEngine::DetectTCServiceLevel() CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->DetectTCServiceLevel() : 0);
}

BOOL CTCProcessEngine::CorrelateTCTransferFrameSequenceNumber()
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CorrelateTCTransferFrameSequenceNumber() : FALSE);
}

BOOL CTCProcessEngine::CanCorrelateTCTransferFrameSequenceNumber() CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CanCorrelateTCTransferFrameSequenceNumber() : FALSE);
}

BOOL CTCProcessEngine::EnableTCTransferFrameExpeditedMode(BOOL bEnable)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnableTCTransferFrameExpeditedMode(bEnable) : FALSE);
}

BOOL CTCProcessEngine::IsTCTransferFrameExpeditedModeEnabled() CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->IsTCTransferFrameExpeditedModeEnabled() : FALSE);
}

INT CTCProcessEngine::EnumSubSystems(CStringArray &szSubSystems, BOOL bAll) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnumSubSystems(szSubSystems, bAll) : 0);
}

UINT CTCProcessEngine::TranslateSubSystemToID(LPCTSTR pszSubSystem) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->TranslateSubSystemToID(pszSubSystem) : (UINT)-1);
}

CString CTCProcessEngine::TranslateIDToSubSystem(UINT nSubSystemID) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->TranslateIDToSubSystem(nSubSystemID) : EMPTYSTRING);
}

BOOL CTCProcessEngine::GenerateTCTransferFrames(CONST CDatabaseEngine *pDatabase, CONST CTCPacket *pTCPacket, BYTE *pTCProcessData, CTCTransferFrames &pTCTransferFrames)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->GenerateTCTransferFrames(pDatabase, pTCPacket, pTCProcessData, pTCTransferFrames) : FALSE);
}

BOOL CTCProcessEngine::GenerateTCPackets(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszMemoryPatch, BOOL bTimeTagged, BOOL b2ndStep, BOOL bBlocked, BOOL bExample, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->GenerateTCPackets(pDatabase, pDatabaseTCFunction, pDatabaseTCPacket, pTMEnvironment, pTCEnvironment, pszMemoryPatch, bTimeTagged, b2ndStep, bBlocked, bExample, pDatabaseTCFunctions, pDatabaseTCPackets) : FALSE);
}

BOOL CTCProcessEngine::InitializeTCPacket(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CTCPacket *pTCPacket, CONST CTimeTag &tExecutionTime, BOOL bBlocked, BOOL bExample)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->InitializeTCPacket(pDatabase, pTMEnvironment, pTCEnvironment, pDatabaseTCFunction, pDatabaseTCPacket, pTCPacket, tExecutionTime, bBlocked, bExample) : FALSE);
}

BOOL CTCProcessEngine::CollectTCPacket(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CDatabaseTCFunction *pDatabaseTCFunction, CTCPacket *pTCPacket, INT nBlockID)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CollectTCPacket(pDatabase, pTMEnvironment, pDatabaseTCFunction, pTCPacket, nBlockID) : FALSE);
}

BOOL CTCProcessEngine::DecodeTCPacket(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pDatabaseBlockedTCFunctions, CDatabaseTCPacket *pDatabaseTCPacket) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->DecodeTCPacket(pDatabase, pTCEnvironment, pTCPacket, pDatabaseTCFunction, pDatabaseBlockedTCFunctions, pDatabaseTCPacket) : FALSE);
}

BOOL CTCProcessEngine::CheckTCFunctionPreexecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, INT nGroupID, CStringArray &szParameters) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCFunctionPreexecutionParameterGroup(pDatabase, pTMEnvironment, nGroupID, szParameters) : FALSE);
}
BOOL CTCProcessEngine::CheckTCFunctionPreexecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMParameters &pTMParameters, LPCTSTR pszGroup, CStringArray &szParameters) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCFunctionPreexecutionParameterGroup(pDatabase, pTMParameters, pszGroup, szParameters) : FALSE);
}

BOOL CTCProcessEngine::CheckTCFunctionExecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nGroupID, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCFunctionExecutionParameterGroup(pDatabase, pTMEnvironment, pDatabaseTCFunction, nGroupID, nStageID, tStageStart, tUncertainty, szParameters) : FALSE);
}
BOOL CTCProcessEngine::CheckTCFunctionExecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMParameters &pTMParameters, CONST CDatabaseTCFunction *pDatabaseTCFunction, LPCTSTR pszGroup, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCFunctionExecutionParameterGroup(pDatabase, pTMParameters, pDatabaseTCFunction, pszGroup, nStageID, tStageStart, tUncertainty, szParameters) : FALSE);
}

BOOL CTCProcessEngine::CheckTCFunctionExecutionTime(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTimeTag &tExecutionTime) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCFunctionExecutionTime(pDatabaseTCFunction, pDatabaseTCPacket, tExecutionTime) : FALSE);
}

BOOL CTCProcessEngine::SetTCFunctionExecutionTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->SetTCFunctionExecutionTimeOffsets(tMin, tMax) : FALSE);
}

BOOL CTCProcessEngine::GetTCFunctionExecutionTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->GetTCFunctionExecutionTimeOffsets(tMin, tMax) : FALSE);
}

BOOL CTCProcessEngine::SetTCFunctionParameterTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->SetTCFunctionParameterTimeOffsets(tMin, tMax) : FALSE);
}

BOOL CTCProcessEngine::GetTCFunctionParameterTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->GetTCFunctionParameterTimeOffsets(tMin, tMax) : FALSE);
}

UINT CTCProcessEngine::CheckTCParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter, CTCParameter *pTCParameter, ULONGLONG nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCParameterOolStatus(pDatabase, pDatabaseTCParameter, pTCParameter, nValue) : 0);
}

BOOL CTCProcessEngine::ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterValue(pDatabase, pszTag, nAttributes, pszValue, nValue) : FALSE);
}
BOOL CTCProcessEngine::ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterValue(pDatabase, pDatabaseTCParameter, nValue) : FALSE);
}

BOOL CTCProcessEngine::ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, LPCTSTR pszTime, ULONGLONG &nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterTimeValue(pDatabase, pTCEnvironment, pszTag, nWidth, pszTime, nValue) : FALSE);
}
BOOL CTCProcessEngine::ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nPTC, INT nPFC, LPCTSTR pszTime, UINT nOBTID, ULONGLONG &nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterTimeValue(pDatabase, pTCEnvironment, pszTag, nPTC, nPFC, pszTime, nOBTID, nValue) : FALSE);
}
BOOL CTCProcessEngine::ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, CONST CTimeTag &tTime, ULONGLONG &nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterTimeValue(pDatabase, pTCEnvironment, pszTag, nWidth, tTime, nValue) : FALSE);
}
BOOL CTCProcessEngine::ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nPTC, INT nPFC, CONST CTimeTag &tTime, UINT nOBTID, ULONGLONG &nValue) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterTimeValue(pDatabase, pTCEnvironment, pszTag, nPTC, nPFC, tTime, nOBTID, nValue) : FALSE);
}
BOOL CTCProcessEngine::ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, ULONGLONG nValue, CTimeTag &tTime) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterTimeValue(pDatabase, pTCEnvironment, pszTag, nWidth, nValue, tTime) : FALSE);
}
BOOL CTCProcessEngine::ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nPTC, INT nPFC, ULONGLONG nValue, UINT nOBTID, CTimeTag &tTime) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTCParameterTimeValue(pDatabase, pTCEnvironment, pszTag, nPTC, nPFC, nValue, nOBTID, tTime) : FALSE);
}

INT CTCProcessEngine::EnumTCDiagnosticsOversamplingDumpRates(CStringArray &szRates) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnumTCDiagnosticsOversamplingDumpRates(szRates) : 0);
}

BOOL CTCProcessEngine::EncodeTCDiagnosticsOversamplingDump(CONST CDatabaseEngine *pDatabase, CONST CTimeTag &tExecutionTime, CONST COversamplingParameters &pOversamplingParameters, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EncodeTCDiagnosticsOversamplingDump(pDatabase, tExecutionTime, pOversamplingParameters, pDatabaseTCFunction) : FALSE);
}

BOOL CTCProcessEngine::DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCFunction *pDatabaseTCFunction, COversamplingParameters &pOversamplingParameters) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->DecodeTCDiagnosticsOversamplingDump(pDatabase, pDatabaseTCFunction, pOversamplingParameters) : FALSE);
}
BOOL CTCProcessEngine::DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, COversamplingParameters &pOversamplingParameters, BOOL bAutomatic) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->DecodeTCDiagnosticsOversamplingDump(pDatabase, pTMEnvironment, pOversamplingParameters, bAutomatic) : FALSE);
}

double CTCProcessEngine::CalculateTCDiagnosticsOversamplingBandwidth(CONST CDatabaseEngine *pDatabase, COversamplingParameters &pOversamplingParameters) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CalculateTCDiagnosticsOversamplingBandwidth(pDatabase, pOversamplingParameters) : 0.0);
}

INT CTCProcessEngine::EnumTCOnBoardBufferTypes(CStringArray &szTypes) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnumTCOnBoardBufferTypes(szTypes) : 0);
}

INT CTCProcessEngine::EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnumTCOnBoardBufferQueues(pszType, szNames) : 0);
}
INT CTCProcessEngine::EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames, CUIntArray &nAPIDs, CUIntArray &nSubScheduleIDs, CUIntArray &nLimits, CStringArray &szUnits, CUIntArray &tTimeouts) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnumTCOnBoardBufferQueues(pszType, szNames, nAPIDs, nSubScheduleIDs, nLimits, szUnits, tTimeouts) : 0);
}

INT CTCProcessEngine::UpdateTCOnBoardBufferQueues(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CStringArray &szTypes, CStringArray &szNames, CUIntArray &nSubScheduleIDs, CUIntArray &nCounts, CTimeTagArray &tUpdateTimes, CUIntArray &nStatus)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->UpdateTCOnBoardBufferQueues(pDatabase, pTMEnvironment, szTypes, szNames, nSubScheduleIDs, nCounts, tUpdateTimes, nStatus) : 0);
}

BOOL CTCProcessEngine::CheckTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, BOOL &bStatus, BOOL &bDumpAllEntries, BOOL &bDumpByAPID, BOOL &bDumpByPSC, BOOL &bDumpByEntryRange, BOOL &bDumpByTimeRange, BOOL &bResetAllEntries, BOOL &bResetByAPID, BOOL &bResetByPSC, BOOL &bResetByEntryRange, BOOL &bResetByTimeRange) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCOnBoardBufferQueue(pszType, pszName, bStatus, bDumpAllEntries, bDumpByAPID, bDumpByPSC, bDumpByEntryRange, bDumpByTimeRange, bResetAllEntries, bResetByAPID, bResetByPSC, bResetByEntryRange, bResetByTimeRange) : FALSE);
}

BOOL CTCProcessEngine::EncodeTCOnBoardBufferQueueStatus(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, BOOL bEnable, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EncodeTCOnBoardBufferQueueStatus(pDatabase, pTCEnvironment, pszType, pszName, tExecutionTime, bEnable, pDatabaseTCFunction) : FALSE);
}
BOOL CTCProcessEngine::EncodeTCOnBoardBufferQueueDump(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EncodeTCOnBoardBufferQueueDump(pDatabase, pTCEnvironment, pszType, pszName, tExecutionTime, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime, pDatabaseTCFunction) : FALSE);
}
BOOL CTCProcessEngine::EncodeTCOnBoardBufferQueueReset(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EncodeTCOnBoardBufferQueueReset(pDatabase, pTCEnvironment, pszType, pszName, tExecutionTime, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime, pTCPacket, pDatabaseTCFunction) : FALSE);
}

BOOL CTCProcessEngine::DecodeTCOnBoardBufferQueueDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CString &szType, CString &szName, UINT &nSubScheduleID, CTCPacket *pTCPacket) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->DecodeTCOnBoardBufferQueueDump(pDatabase, pTMEnvironment, szType, szName, nSubScheduleID, pTCPacket) : FALSE);
}
BOOL CTCProcessEngine::DecodeTCOnBoardBufferQueueDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pBlockedItems, CDatabaseTCPacket *pDatabaseTCPacket, CTimeTag &tExecutionTime) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->DecodeTCOnBoardBufferQueueDump(pDatabase, pTMEnvironment, pTCEnvironment, pTCPacket, pDatabaseTCFunction, pBlockedItems, pDatabaseTCPacket, tExecutionTime) : FALSE);
}

BOOL CTCProcessEngine::FindTCOnBoardBufferQueue(CONST CTCPacket *pTCPacket, CString &szType, CString &szName, UINT &nSubScheduleID) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->FindTCOnBoardBufferQueue(pTCPacket, szType, szName, nSubScheduleID) : FALSE);
}

BOOL CTCProcessEngine::ExpandTCOnBoardBufferQueueEntry(CONST CTCEnvironment *pTCEnvironment, CONST CTCPacket *pTCPacket, UINT &nBlockOffset, UINT &nBlockBytes, CUIntArray &nBlockSizes, CTimeTagArray &tBlockTimes) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ExpandTCOnBoardBufferQueueEntry(pTCEnvironment, pTCPacket, nBlockOffset, nBlockBytes, nBlockSizes, tBlockTimes) : FALSE);
}

UINT CTCProcessEngine::CalculateTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CalculateTCOnBoardBufferQueueEntry(pTCPacket) : 0);
}

BOOL CTCProcessEngine::CheckTCOnBoardMemoryImageDumpCapabilities(CONST CDatabaseEngine *pDatabase, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL &bStop) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCOnBoardMemoryImageDumpCapabilities(pDatabase, pProcessor, pImage, bStop) : FALSE);
}

BOOL CTCProcessEngine::EncodeTCOnBoardMemoryImageDump(CONST CDatabaseEngine *pDatabase, CTCEnvironment *pTCEnvironment, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeTag &tExecutionTime, BOOL bStop, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EncodeTCOnBoardMemoryImageDump(pDatabase, pTCEnvironment, pProcessor, pImage, tExecutionTime, bStop, pDatabaseTCFunction) : FALSE);
}

BOOL CTCProcessEngine::IsTCOnBoardMemoryImageDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->IsTCOnBoardMemoryImageDump(pDatabase, pTMEnvironment) : FALSE);
}

BOOL CTCProcessEngine::CheckTCOnBoardMemoryImagePatchCapabilities(CONST CDatabaseEngine *pDatabase, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CheckTCOnBoardMemoryImagePatchCapabilities(pDatabase, pProcessor, pImage) : FALSE);
}

BOOL CTCProcessEngine::EncodeTCOnBoardMemoryImagePatch(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeTag &tExecutionTime, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EncodeTCOnBoardMemoryImagePatch(pDatabase, pTMEnvironment, pTCEnvironment, pProcessor, pImage, tExecutionTime, pDatabaseTCFunctions, pDatabaseTCPackets) : FALSE);
}

BOOL CTCProcessEngine::CalculateTCOnBoardMemoryImageCRC(CONST CDatabaseEngine *pDatabase, CONST CDatabaseOBProcessor *pProcessor, CDatabaseOBProcessorMemoryImage *pImage, LPCTSTR pszImageVersion) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CalculateTCOnBoardMemoryImageCRC(pDatabase, pProcessor, pImage, pszImageVersion) : FALSE);
}

BOOL CTCProcessEngine::IsTCOnBoardMemoryImagePatch(CONST CDatabaseEngine *pDatabase, CONST CTCPacket *pTCPacket, CString &szProcessor) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->IsTCOnBoardMemoryImagePatch(pDatabase, pTCPacket, szProcessor) : FALSE);
}

BOOL CTCProcessEngine::Get1stStepTCData(CONST CTMEnvironment *pTMEnvironment, CByteArray &nData) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->Get1stStepTCData(pTMEnvironment, nData) : FALSE);
}

BOOL CTCProcessEngine::SetTimeCorrelation(CTCEnvironment *pTCEnvironment)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->SetTimeCorrelation(pTCEnvironment) : FALSE);
}
BOOL CTCProcessEngine::SetTimeCorrelation(CTCEnvironment *pTCEnvironment, CONST CTimeTag &tOBRT, UINT nOBRT, UINT nOBTID)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->SetTimeCorrelation(pTCEnvironment, tOBRT, nOBRT, nOBTID) : FALSE);
}

BOOL CTCProcessEngine::GetTimeCorrelation(CONST CTCEnvironment *pTCEnvironment, CTimeTag &tOBRT, UINT &nOBRT, UINT nOBTID) CONST
{
	return(((m_pTCEngine != (CTCProcessEngine *)NULL) && m_pTCEngine != this) ? m_pTCEngine->GetTimeCorrelation(pTCEnvironment, tOBRT, nOBRT, nOBTID) : FALSE);
}

CTimeTag CTCProcessEngine::CorrelateTime(CONST CTCEnvironment *pTCEnvironment, CONST CTimeTag &tTime, UINT nOBTID) CONST
{
	return(((m_pTCEngine != (CTCProcessEngine *)NULL) && m_pTCEngine != this) ? m_pTCEngine->CorrelateTime(pTCEnvironment, tTime, nOBTID) : 0);
}

BOOL CTCProcessEngine::CanCorrelateTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID) CONST
{
	return(((m_pTCEngine != (CTCProcessEngine *)NULL) && m_pTCEngine != this) ? m_pTCEngine->CanCorrelateTime(pTCEnvironment, nOBTID) : FALSE);
}

UINT CTCProcessEngine::ConvertTimeToOBRT(CONST CTCEnvironment *pTCEnvironment, CONST CTimeTag &tTime, UINT nOBTID) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertTimeToOBRT(pTCEnvironment, tTime, nOBTID) : 0);
}

BOOL CTCProcessEngine::CanConvertTimeToOBRT(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CanConvertTimeToOBRT(pTCEnvironment, nOBTID) : FALSE);
}

CTimeTag CTCProcessEngine::ConvertOBRTToTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBRT, UINT nOBTID) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->ConvertOBRTToTime(pTCEnvironment, nOBRT, nOBTID) : 0);
}

BOOL CTCProcessEngine::CanConvertOBRTToTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->CanConvertOBRTToTime(pTCEnvironment, nOBTID) : FALSE);
}

BOOL CTCProcessEngine::EnableDebugging(BOOL bEnable)
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->EnableDebugging(bEnable) : FALSE);
}

BOOL CTCProcessEngine::IsDebuggingEnabled() CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->IsDebuggingEnabled() : FALSE);
}

BOOL CTCProcessEngine::AllocateTCProcessInfo(CTCEnvironment *pTCEnvironment) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->AllocateTCProcessInfo(pTCEnvironment) : FALSE);
}

BOOL CTCProcessEngine::FreeTCProcessInfo(CTCEnvironment *pTCEnvironment) CONST
{
	return((m_pTCEngine != (CTCProcessEngine *)NULL  &&  m_pTCEngine != this) ? m_pTCEngine->FreeTCProcessInfo(pTCEnvironment) : FALSE);
}
