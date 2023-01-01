#include "pch.h"
#include <atldbcli.h>
#include "CDBConnection.h"

/////////////////////////////////////////////////////////////////////////
// CDBConnection

// Methods
// ----------------
CDataSource& CDBConnection::GetDataSource()
{
	return m_oDataSource;
}

CDBConnection& CDBConnection::getInstance()
{
	static CDBConnection* oConnection = new CDBConnection();
	return *oConnection;
}

BOOL CDBConnection::ConnectToDB(HRESULT& hResult, CDBPropSet& oDBPropSet)
{
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-0DIN1MS"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));

	hResult = m_oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);

		return FALSE;
	}

	return TRUE;
}

void CDBConnection::CloseDataSource()
{
	m_oDataSource.Close();
}
