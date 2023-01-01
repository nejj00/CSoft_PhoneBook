#pragma once
#include "pch.h"
#include <atldbcli.h>


/////////////////////////////////////////////////////////////////////////////
// CDBConnection

/// <summary>
/// Клас за свързване към базата данни
/// </summary>
class CDBConnection
{
private:
	
	// Constructor / Destructor
	// ----------------
	CDBConnection()
	{}

	~CDBConnection() {}

	CDBConnection(const CDBConnection&) = delete;
	CDBConnection operator=(const CDBConnection&) = delete;
	CDBConnection(CDBConnection&&) = delete;
	CDBConnection& operator=(CDBConnection&&) = delete;

	
// Methods
// ----------------
public:
	/// <summary>
	/// Връща референция към обект от тип CDBConnection
	/// </summary>
	/// <returns></returns>
	static CDBConnection& getInstance();

	/// <summary>
	/// Свързва се към базата данни
	/// </summary>
	/// <param name="hResult"></param>
	/// <param name="oDBPropSet"></param>
	/// <returns> TRUE при успешно свързване, иначе FALSE </returns>
	BOOL ConnectToDB(HRESULT& hResult, CDBPropSet& oDBPropSet);

	/// <summary>
	/// Връща m_DataSource
	/// </summary>
	/// <returns> m_DataSource </returns>
	CDataSource& GetDataSource();

	/// <summary>
	/// Затваря m_DataSource
	/// </summary>
	void CloseDataSource();

// Members
// ----------------
private:
	/// <summary>
	/// Обект от тип CDataSource за достъп към базата
	/// </summary>
	CDataSource m_oDataSource;
};

