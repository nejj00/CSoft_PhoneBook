#pragma once
#include "CBaseTable.h"
#include "CPersonsAccessor.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>
/// Клас описващ таблица PERSONS от база данни PhoneBook
/// </summary>
class CPersonsTable : public CBaseTable<CPersonsAccessor, PERSONS, CPersonsArray>
{
public:
	CPersonsTable(CSession& oSession);

public:
	PERSONS& GetStruct()override;
	int& GetUpdateCounter(PERSONS& recPerson)override;
};