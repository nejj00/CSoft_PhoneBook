#include "pch.h"
#include <atldbcli.h>
#include "CDBMethods.h"

/////////////////////////////////////////////////////////////////////////////
// CDBMethods

// Methods
// ----------------
BOOL CDBMethods::UpDelInPropSetProperties(CDBPropSet& UpDelInPropSet)
{
	UpDelInPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	UpDelInPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	UpDelInPropSet.AddProperty(DBPROP_IRowsetChange, true);
	UpDelInPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_DELETE | DBPROPVAL_UP_INSERT);

	return TRUE;
}

void CDBMethods::QueryErrorCheck(HRESULT& hResult)
{
	CString strMessage = _T("Error executing query. Error: %d. Query: %s");
	_com_error error(hResult);
	CString strError;
	strError.Format(_T("\nError 0x%08x: %s"), hResult, error.ErrorMessage());
	strMessage += strError;
	AfxMessageBox(strMessage);
}

BOOL CDBMethods::OpenSession(HRESULT& hResult, CDataSource& oDataSource, CSession& oSession)
{
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);

		return FALSE;
	}

	return TRUE;
}

CString CDBMethods::MakeSelectIDQuery(long lID, CString strTableName, CString strLock)
{
	CString strSelectQuery;
	strSelectQuery.Format(_T("SELECT * FROM %s %s WHERE ID = %d"), strTableName, strLock, lID);

	return strSelectQuery;
}

