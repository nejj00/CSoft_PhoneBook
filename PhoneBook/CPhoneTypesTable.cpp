#include "pch.h"
#include "CPhoneTypesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesTable

// Constructors & Destructors
// ---------------------------
CPhoneTypesTable::CPhoneTypesTable() : CBaseTable(_T("PHONE_TYPES"))
{
}

// Methods
// -------------------------
PHONE_TYPES& CPhoneTypesTable::GetStruct()
{
	return m_recPhoneType;
}

int& CPhoneTypesTable::GetUpdateCounter(PHONE_TYPES& recPhoneType)
{
	return recPhoneType.nUpdateCounter;
}