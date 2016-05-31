class CTCProcedureThread_%s : public CTCProcedureThread
{
public:
	CTCProcedureThread_%s(LPCTSTR pszName,CONST CDatabaseEngine *pDatabase,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment,HANDLE hTMEvent,HANDLE hTCEvent,HANDLE hUpdate,HANDLE hExit);

public:
	virtual int Run();
private:
	INT ExecuteCode();

private:
	virtual BOOL InitParameters();
	virtual INT EnumParameters(CStringArray &szParameters) CONST;
private:
	virtual BOOL WaitThreadActivationExpression();
	virtual BOOL CheckStepTriggerExpression(LPCTSTR pszName) CONST;
	virtual BOOL CheckStepBodyExpression(LPCTSTR pszName) CONST;
	virtual BOOL CheckStepConfirmationExpression(LPCTSTR pszName) CONST;
private:
	virtual BOOL InitTCFunction(LPCTSTR pszName,INT nEntry,BOOL bExpanded,CDatabaseTCFunction *pTCFunction,CDatabaseTCPacket *pTCPacket,CString &szMemoryPatch,BOOL &bAuthorization);
	virtual BOOL EnumTCFunctionExecutionVerificationTimeWindows(LPCTSTR pszName,INT nEntry,CUIntArray &nStageIDs,CUIntArray &nStageTimeWindowOffsets,CUIntArray &nStageTimeWindowSizes,CUIntArray &nStageTimeWindowUncertainties) CONST;
	virtual BOOL CheckTCFunctionPreexecutionExpression(LPCTSTR pszName,INT nEntry,CStringArray &szParameters) CONST;
	virtual BOOL CheckTCFunctionExecutionExpression(LPCTSTR pszName,INT nEntry,CONST CDatabaseTCFunction *pTCFunction,UINT nStageID,CONST CTimeTag &tStageStart,CONST CTimeSpan &tUncertainty,CStringArray &szParameters) CONST;
};


CTCProcedureThread_%s::CTCProcedureThread_%s(LPCTSTR pszName,CONST CDatabaseEngine *pDatabase,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment,HANDLE hTMEvent,HANDLE hTCEvent,HANDLE hUpdate,HANDLE hExit) : CTCProcedureThread(pszName,pDatabase,pTCProcessEngine,pTCEnvironment,hTMEvent,hTCEvent,hUpdate,hExit)
{
  return;
}

int CTCProcedureThread_%s::Run()
{
  return ExitInstance(ExecuteCode());
}

%s
{
  %sreturn FALSE;
}

%s
{
  %sreturn TRUE;
}

INT CTCProcedureThread_%s::EnumParameters(CStringArray &szParameters) CONST
{
  szParameters.RemoveAll();%s
  return((INT) szParameters.GetSize());
}

BOOL CTCProcedureThread_%s::WaitThreadActivationExpression()
{
  DWORD  dwCode;

  do
  { if (%s)
    { if (IsThreadEnabled())
      { dwCode = WAIT_OBJECT_0+1;
        break;
      }
    }
  }
  while ((dwCode = Wait(__GetTMEvent(),FALSE)) == WAIT_OBJECT_0+1);
  return((dwCode == WAIT_OBJECT_0+1) ? TRUE:FALSE);
}

BOOL CTCProcedureThread_%s::CheckStepTriggerExpression(LPCTSTR pszName) CONST
{
  %sreturn TRUE;
}

BOOL CTCProcedureThread_%s::CheckStepBodyExpression(LPCTSTR pszName) CONST
{
  %sreturn TRUE;
}

BOOL CTCProcedureThread_%s::CheckStepConfirmationExpression(LPCTSTR pszName) CONST
{
  %sreturn TRUE;
}

BOOL CTCProcedureThread_%s::InitTCFunction(LPCTSTR pszName,INT nEntry,BOOL bExpanded,CDatabaseTCFunction *pTCFunction,CDatabaseTCPacket *pTCPacket,CString &szMemoryPatch,BOOL &bAuthorization)
{
  for (szMemoryPatch.Empty(),bAuthorization = FALSE; __InitTCFunctionConstParameters(pTCFunction) &&  __InitTCPacketConstParameters(pTCPacket); )
  { if (!bExpanded)
    { %s}
    else
    { %s}
    break;
  }
  return FALSE;
}

BOOL CTCProcedureThread_%s::EnumTCFunctionExecutionVerificationTimeWindows(LPCTSTR pszName,INT nEntry,CUIntArray &nStageIDs,CUIntArray &nStageTimeWindowOffsets,CUIntArray &nStageTimeWindowSizes,CUIntArray &nStageTimeWindowUncertainties) CONST
{
  nStageIDs.RemoveAll();
  nStageTimeWindowOffsets.RemoveAll();
  nStageTimeWindowSizes.RemoveAll();
  nStageTimeWindowUncertainties.RemoveAll();
  %sreturn FALSE;
}

BOOL CTCProcedureThread_%s::CheckTCFunctionPreexecutionExpression(LPCTSTR pszName,INT nEntry,CStringArray &szParameters) CONST
{
  %sreturn FALSE;
}

BOOL CTCProcedureThread_%s::CheckTCFunctionExecutionExpression(LPCTSTR pszName,INT nEntry,CONST CDatabaseTCFunction *pTCFunction,UINT nStageID,CONST CTimeTag &tStageStart,CONST CTimeSpan &tUncertainty,CStringArray &szParameters) CONST
{
  %sreturn FALSE;
}
