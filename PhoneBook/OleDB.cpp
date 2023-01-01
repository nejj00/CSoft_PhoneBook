#include "pch.h"
/*
#include <iostream>
#include "CCitiesTable.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCitiesClass


// Methods
// ----------------
BOOL CCitiesTable::SelectAll(CCitiesArray& oCitiesArray)
{
	CDataSource oDataSource;  // връзка с БД
	CSession oSession; // Сесия

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-0DIN1MS")); 
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));


	// Свързване към базата данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	// Отваряне на сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	// Заявка
	CString strQuery = _T("SELECT * FROM CITIES");

	// Изпълнение
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: %d. Query: %s"), hResult);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	while (MoveNext() == S_OK)
	{
		CITIES* recCity = new CITIES;
		recCity->lID = m_recCity.lID;
		recCity->nUpdateCounter = m_recCity.lID;
		wcscpy_s(recCity->szCityName, m_recCity.szCityName);
		wcscpy_s(recCity->szArea, m_recCity.szArea);

		oCitiesArray.Add(recCity);
	}

	Close();
	oSession.Close();
	oDataSource.Close();

	return true;
}

BOOL CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	CDataSource oDataSource;  // връзка с БД
	CSession oSession; // Сесия

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-0DIN1MS"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));


	// Свързване към базата данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	

	// Отваряне на сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

	// Изпълняваме команда
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: %d. Query: %s"), hResult);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error opening record. Error: %d. Query: %s"), hResult);

		Close();
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}

	recCities.lID = m_recCity.lID;
	recCities.nUpdateCounter = m_recCity.nUpdateCounter;
	wcscpy_s(recCities.szCityName, m_recCity.szCityName);
	wcscpy_s(recCities.szArea, m_recCity.szArea);

	Close();
	oSession.Close();
	oDataSource.Close();

	return true;
}

BOOL CCitiesTable::UpdateWhereID(const long lID, CITIES& recCities)
{
	CDataSource oDataSource;  // връзка с БД
	CSession oSession; // Сесия

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("DESKTOP-0DIN1MS"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_PROMPT, static_cast<short>(4));


	// Свързване към базата данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}



	// Отваряне на сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID = %d"), lID);

	// 
	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oUpdateDBPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oUpdateDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oUpdateDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE);

	/*
	hResult = Open(oSession, strQuery, oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: %d."), hResult);

		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}





	return true;
}

BOOL CCitiesTable::Insert(const CITIES& recCities)
{

	return true;
}

BOOL CCitiesTable::DeleteWhereID(const long lID)
{

	return true;
}
*/