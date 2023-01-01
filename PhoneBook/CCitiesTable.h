#pragma once
#include "CBaseTable.h"
#include "CCitiesAccessor.h"


/////////////////////////////////////////////////////////////////////////////
// CCitiesTable

/// <summary>
/// Клас описващ таблица CITIES от база данни PhoneBook
/// </summary>
class CCitiesTable : public CBaseTable<CCitiesAccessor, CITIES, CCitiesArray>
{
public:
	CCitiesTable();

public:
	CITIES& GetStruct()override;
	int& GetUpdateCounter(CITIES& recCity)override;
};