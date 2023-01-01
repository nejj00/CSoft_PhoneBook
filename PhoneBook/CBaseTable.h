#pragma once
/////////////////////////////////////////////////////////////////////////////
// CBaseTable

#include "pch.h"
#include "CDBConnection.h"
#include "CDBMethods.h"
#include "ActionEnums.h"

using namespace std;

#define ERROR_OPPENIG_RECORD "Error opening record."
#define ERROR_NOT_UPDATED "ERROR: The record is not up to date. Please try again."
#define ERROR_UPDATING "Error UPDATING record."
#define ERROR_INSERTING "Error INSERTING record."
#define ERROR_DELETING "Error DELETING record."
#define ERROR_GETTING_DATA "Error getting data."

#define ACCESSOR_1 1

/// <summary>
/// Клас описващ таблица от база данни PhoneBook
/// </summary>
template <class ACCESSOR, class STRUCT, class ARRAY>
class CBaseTable : protected CCommand<CAccessor<ACCESSOR>>
{
// Constructors and Destructors
// -----------------------------
public:
	CBaseTable(CString strTableName);
	CBaseTable(CString strTableName, CSession& oSession);
	virtual ~CBaseTable();
	
// Methods
// ------------------------------
protected:
	/// <summary>
	/// Изкарване на съобщение за грешка
	/// </summary>
	/// <param name="hResult"> Променлива от тип HRESULT </param>
	/// <param name="szMessage"> Съобщение за изкарване </param>
	void ErrorMessage(HRESULT& hResult, CString szMessage);

	/// <summary>
	/// Затваряне на сесията и rowset-а
	/// </summary>
	/// <param name="oSession"> </param>
	void CloseSessionRowset(CSession& oSession);

	/// <summary>
	/// Изпълнение на заявка за Select методите
	/// </summary>
	/// <param name="hResult"> Променлива от тип HRESULT </param>
	/// <param name="oSession"> Променлива за сесията </param>
	/// <param name="strQuery"> Заявка за изпълнение </param>
	/// <param name="oDBMethods"> Обект от тип CDBMethods </param>
	/// <returns></returns>
	BOOL ExecuteSelectQuery(HRESULT& hResult, CSession& oSession, CString strQuery);

	/// <summary>
	/// Изпълнение на заявките за Update, Insert и Delete методи
	/// </summary>
	/// <param name="hResult"> Променлива от тип HRESULT </param>
	/// <param name="oSession"></param>
	/// <param name="strQuery"> Заявка за изпълнение </param>
	/// <param name="oDBPropSet"> Променлива за сесията </param>
	/// <param name="oDBMethods"> Обект от тип CDBMethods</param>
	/// <returns></returns>
	BOOL ExecuteUpdDelInsQuery(HRESULT& hResult, CSession& oSession, CString strQuery, CDBPropSet& oDBPropSet);


public:

	/// <summary>
	/// Извличане на всички записи от базата данни и слагане в масив 
	/// </summary>
	/// <param name="oCitiesArray"> Масив, който да държи записите от базата данна </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectAll(ARRAY& oArray);

	/// <summary>
	/// Извличане на запис с определено ID
	/// </summary>
	/// <param name="lID"> ID на запис от базата данни </param>
	/// <param name="recCities"> Променлива която да съдържа избрания запис </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectWhereID(const long lID, STRUCT& recStruct);

	/// <summary>
	/// Модификация на запис с определено ID от базата данни  
	/// </summary>
	/// <param name="lID"> ID на запис от базата данни </param>
	/// <param name="recCities"> Записа, който ще бъде променен </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL UpdateWhereID(const long lID, STRUCT& recStruct);

	/// <summary>
	/// Вмъкване на запис в базата данни
	/// </summary>
	/// <param name="recCities"> Записа който ще бъде вмъкнат </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Insert(STRUCT& recStruct);

	/// <summary>
	/// Изтриване на запис с определено ID от базата данни
	/// </summary>
	/// <param name="lID"> ID записа за изтриване </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL DeleteWhereID(const long lID);
	/// <summary>
	/// Избира редове от таблицата които имат подадената стойност за подадена колона
	/// </summary>
	/// <param name="strColumn"></param>
	/// <param name="oStructArray"></param>
	/// <param name="lID"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectRowsWithForeignKey(CString strColumn, ARRAY& oStructArray, long lID);

// Ovverrides
// -------------------------
protected:
	/// <summary>
	/// Достъпване на аксесорната променлива на табличните класове
	/// </summary>
	/// <returns> Референция към елемент от тип STRUCT </returns>
	virtual STRUCT& GetStruct() = 0;
	/// <summary>
	/// Връщане на UpdateCounter на запис от базата данни
	/// </summary>
	/// <param name="recStruct"></param>
	/// <returns></returns>
	virtual int& GetUpdateCounter(STRUCT& recStruct) = 0;

// Members
// -------------------------
public:
	/// <summary>
	/// Име на таблицата коята ще се използва класа
	/// </summary>
	CString m_strTableName;
	/// <summary>
	/// Указател към сесия
	/// </summary>
	CSession* m_oSession;
	/// <summary>
	/// Enum определящ какъв вид е сесията, вътрешна или външна
	/// </summary>
	TableSession m_eTableSession;
};

// Constructor
// --------------------------

template <class ACCESSOR, class STRUCT, class ARRAY>
CBaseTable<ACCESSOR, STRUCT, ARRAY>::CBaseTable(CString strTableName)
{
	m_oSession = new CSession();
	m_strTableName = strTableName;
	m_eTableSession = InnerSession;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
CBaseTable<ACCESSOR, STRUCT, ARRAY>::CBaseTable(CString strTableName, CSession& oSession)
{
	m_strTableName = strTableName;
	m_oSession = &oSession;
	m_eTableSession = OuterSession;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
CBaseTable<ACCESSOR, STRUCT, ARRAY>::~CBaseTable()
{
	if (m_eTableSession != OuterSession)
		delete m_oSession;
}

// Methods
// ---------------------------

template <class ACCESSOR, class STRUCT, class ARRAY>
void CBaseTable<ACCESSOR, STRUCT, ARRAY>::ErrorMessage(HRESULT& hResult, CString strMessage)
{
	_com_error error(hResult);
	CString strError;
	strError.Format(_T("\nError 0x%08x: %s"), hResult, error.ErrorMessage());
	strMessage += strError;

	AfxMessageBox(strMessage);
}

template <class ACCESSOR, class STRUCT, class ARRAY>
void CBaseTable<ACCESSOR, STRUCT, ARRAY>::CloseSessionRowset(CSession& oSession)
{
	if (m_eTableSession == InnerSession)
	{
		oSession.Close();
	}
	Close();
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::ExecuteSelectQuery(HRESULT& hResult, CSession& oSession, CString strQuery)
{
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		CDBMethods::QueryErrorCheck(hResult);
		return FALSE;
	}
	return TRUE;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::ExecuteUpdDelInsQuery(HRESULT& hResult, CSession& oSession, CString strQuery, CDBPropSet& oDBPropSet)
{
	hResult = Open(oSession, strQuery, &oDBPropSet);
	
	if (FAILED(hResult))
	{
		CDBMethods::QueryErrorCheck(hResult);
		return FALSE;
	}

	return TRUE;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::SelectAll(ARRAY& oStructArray)
{
	CSession oSession;
	HRESULT hResult;
	CDBMethods oDBMethods;

	CDBConnection& oDBConnection = CDBConnection::getInstance();

	if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), oSession))
	{
		return FALSE;
	}

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM %s"), m_strTableName);

	if (!ExecuteSelectQuery(hResult, oSession, strQuery))
	{
		return FALSE;
	}

	hResult = MoveNext();
	while (hResult == S_OK)
	{
		STRUCT* pStruct = new STRUCT;
		*pStruct = GetStruct();

		oStructArray.Add(pStruct);
		hResult = MoveNext();
	}

	if (hResult != DB_S_ENDOFROWSET)
	{
		return FALSE;
	}

	CloseSessionRowset(oSession);

	return TRUE;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::SelectWhereID(const long lID, STRUCT& recStruct)
{
	CSession oSession;
	HRESULT hResult;
	CDBMethods oDBMethods;

	CDBConnection& oDBConnection = CDBConnection::getInstance();

	if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), oSession))
	{
		return FALSE;
	}

	CString strQuery = oDBMethods.MakeSelectIDQuery(lID, m_strTableName, _T(""));

	if (!ExecuteSelectQuery(hResult, oSession, strQuery))
	{
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_OPPENIG_RECORD));
		CloseSessionRowset(oSession);
		return FALSE;
	}

	recStruct = GetStruct();

	CloseSessionRowset(oSession);

	return TRUE;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::UpdateWhereID(const long lID, STRUCT& recStruct)
{
	HRESULT hResult;
	CDBMethods oDBMethods;

	CDBConnection& oDBConnection = CDBConnection::getInstance();

	if (m_eTableSession == InnerSession)
	{
		if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), *m_oSession))
		{
			return FALSE;
		}
	}

	CString strQuery = oDBMethods.MakeSelectIDQuery(lID, m_strTableName, _T(" WITH (UPDLOCK) "));

	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	oDBMethods.UpDelInPropSetProperties(oUpdateDBPropSet);

	if (!ExecuteUpdDelInsQuery(hResult, *m_oSession, strQuery, oUpdateDBPropSet))
	{
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_OPPENIG_RECORD));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	if (GetUpdateCounter(GetStruct()) != GetUpdateCounter(recStruct))
	{
		AfxMessageBox(_T(ERROR_NOT_UPDATED));

		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	GetUpdateCounter(recStruct)++;

	GetStruct() = recStruct;

	hResult = SetData(ACCESSOR_1);
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_UPDATING));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	CloseSessionRowset(*m_oSession);

	return TRUE;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::Insert(STRUCT& recStruct)
{
	HRESULT hResult;
	CDBMethods oDBMethods;

	CDBConnection& oDBConnection = CDBConnection::getInstance();

	if (m_eTableSession == InnerSession)
	{
		if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), *m_oSession))
		{
			return FALSE;
		}
	}

	CString strQuery;
	strQuery.Format(_T("SELECT TOP(0) * FROM %s"), m_strTableName);

	CDBPropSet oInsertDBPropSet(DBPROPSET_ROWSET);
	oDBMethods.UpDelInPropSetProperties(oInsertDBPropSet);

	if (!ExecuteUpdDelInsQuery(hResult, *m_oSession, strQuery, oInsertDBPropSet))
	{
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_OPPENIG_RECORD));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	GetStruct() = recStruct;

	hResult = __super::Insert(ACCESSOR_1);
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_INSERTING));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	hResult = MoveLast();
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_OPPENIG_RECORD));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	hResult = GetDataHere(&recStruct);
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_GETTING_DATA));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	CloseSessionRowset(*m_oSession); 

	return TRUE;
}


template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::DeleteWhereID(const long lID)
{
	HRESULT hResult;
	CDBMethods oDBMethods;

	CDBConnection& oDBConnection = CDBConnection::getInstance();

	if (m_eTableSession == InnerSession)
	{
		if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), *m_oSession))
		{
			return FALSE;
		}
	}

	CString strQuery = oDBMethods.MakeSelectIDQuery(lID, m_strTableName, _T(""));

	CDBPropSet oDeleteDBPropSet(DBPROPSET_ROWSET);
	oDBMethods.UpDelInPropSetProperties(oDeleteDBPropSet);

	if (!ExecuteUpdDelInsQuery(hResult, *m_oSession, strQuery, oDeleteDBPropSet))
	{
		return FALSE;
	}

	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_OPPENIG_RECORD));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	hResult = Delete();
	if (FAILED(hResult))
	{
		ErrorMessage(hResult, _T(ERROR_DELETING));
		CloseSessionRowset(*m_oSession);
		return FALSE;
	}

	CloseSessionRowset(*m_oSession);

	return TRUE;
}

template <class ACCESSOR, class STRUCT, class ARRAY>
BOOL CBaseTable<ACCESSOR, STRUCT, ARRAY>::SelectRowsWithForeignKey(CString strColumn, ARRAY& oStructArray, long lID)
{
	HRESULT hResult;
	CDBMethods oDBMethods;

	CDBConnection& oDBConnection = CDBConnection::getInstance();

	if (m_eTableSession == InnerSession)
	{
		if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), *m_oSession))
		{
			return FALSE;
		}
	}

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM %s WHERE %s = %d"), m_strTableName, strColumn, lID);

	if (!ExecuteSelectQuery(hResult, *m_oSession, strQuery))
	{
		return FALSE;
	}

	hResult = MoveNext();
	while (hResult == S_OK)
	{
		STRUCT* pStruct = new STRUCT;
		*pStruct = GetStruct();

		oStructArray.Add(pStruct);
		hResult = MoveNext();
	}

	if (hResult != DB_S_ENDOFROWSET)
	{
		return FALSE;
	}

	CloseSessionRowset(*m_oSession);

	return TRUE;
}