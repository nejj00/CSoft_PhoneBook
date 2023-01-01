#pragma once
#include "CBaseTable.h"
#include "CPhoneNumbersAccessor.h"


/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

/// <summary>
/// Клас описващ таблица PHONE_NUMBERS от база данни PhoneBook
/// </summary>
class CPhoneNumbersTable : public CBaseTable<CPhoneNumbersAccessor, PHONE_NUMBERS, CPhoneNumbersArray>
{
/// Construcotrs & Destructors
/// ----------------------------
public:
	CPhoneNumbersTable();
	CPhoneNumbersTable(CSession& oSession);

// Methods
// ------------------------------
public:
	PHONE_NUMBERS& GetStruct()override;
	int& GetUpdateCounter(PHONE_NUMBERS& recCity)override;
};