#pragma once
#include "CBaseTable.h"
#include "CPhoneTypesAccessor.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>
/// Клас описващ таблица PHONE_NUMBERS от база данни PhoneBook
/// </summary>
class CPhoneTypesTable : public CBaseTable<CPhoneTypesAccessor, PHONE_TYPES, CPhoneTypesArray>
{
/// Construcotrs & Destructors
/// ----------------------------
public:
	CPhoneTypesTable();

// Methods
// ------------------------------
public:
	PHONE_TYPES& GetStruct()override;
	int& GetUpdateCounter(PHONE_TYPES& recCity)override;
};