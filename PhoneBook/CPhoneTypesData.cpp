#include "pch.h"
#include "CPhoneTypesData.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesData

// Methods
// ----------------
BOOL CPhoneTypesData::SelectAll(CPhoneTypesArray& oPhoneTypesArray)
{
	return m_oPhoneTypesTable.SelectAll(oPhoneTypesArray);
}

BOOL CPhoneTypesData::SelectWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	return m_oPhoneTypesTable.SelectWhereID(lID, recPhoneType);
}

BOOL CPhoneTypesData::UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType)
{
	return m_oPhoneTypesTable.UpdateWhereID(lID, recPhoneType);
}

BOOL CPhoneTypesData::Insert(PHONE_TYPES& recPhoneType)
{
	return m_oPhoneTypesTable.Insert(recPhoneType);
}

BOOL CPhoneTypesData::Delete(const long lID)
{
	return m_oPhoneTypesTable.DeleteWhereID(lID);
}