#include "pch.h"
#include "CPhoneNumbersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersTable

// Constructors & Destructors
// ---------------------------
CPhoneNumbersTable::CPhoneNumbersTable() : CBaseTable(_T("PHONE_NUMBERS"))
{
}

CPhoneNumbersTable::CPhoneNumbersTable(CSession& oSession) : CBaseTable(_T("PHONE_NUMBERS"), oSession)
{
}

// Methods
// --------------------------
PHONE_NUMBERS& CPhoneNumbersTable::GetStruct()
{
	return m_recPhoneNumber;
}

int& CPhoneNumbersTable::GetUpdateCounter(PHONE_NUMBERS& recPhoneNumber)
{
	return recPhoneNumber.nUpdateCounter;
}