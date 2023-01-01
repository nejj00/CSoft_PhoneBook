#pragma once
#include "pch.h"
#include <atldbcli.h>


/////////////////////////////////////////////////////////////////////////////
// CDBMethods

/// <summary>
/// Kлас за методи използвани в табличните класове
/// </summary>
class CDBMethods
{
public:
	/// <summary>
	/// Задаване на PropSet в Update, Insert и Delete методите
	/// </summary>
	/// <param name="UpDelInPropSet"></param>
	/// <returns></returns>
	BOOL UpDelInPropSetProperties(CDBPropSet& UpDelInPropSet);

	/// <summary>
	/// Проверка за грешка при изпълнение на заявка
	/// </summary>
	/// <param name="hResult"></param>
	/// <param name="oSession"></param>
	static void QueryErrorCheck(HRESULT& hResult);

	/// <summary>
	/// Отваряне на сесия
	/// </summary>
	/// <param name="hResult"></param>
	/// <param name="oDataSource"></param>
	/// <param name="oSession"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL OpenSession(HRESULT& hResult, CDataSource& oDataSource, CSession& oSession);

	/// <summary>
	/// Създаване на SELECT WHERE ID заявка 
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="strLock"></param>
	/// <returns></returns>
	CString MakeSelectIDQuery(long lID, CString strTableName, CString strLock);
};

