#include "pch.h"
#include "CCitiesData.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

// Methods
// ----------------
BOOL CCitiesData::SelectAll(CCitiesArray& oCitiesArray)
{
	return m_oCitiesTable.SelectAll(oCitiesArray);
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	return m_oCitiesTable.SelectWhereID(lID, recCities);
}

BOOL CCitiesData::UpdateWhereID(const long lID, CITIES& recCities)
{
	return m_oCitiesTable.UpdateWhereID(lID, recCities);
}

BOOL CCitiesData::Insert(CITIES& recCities)
{
	return m_oCitiesTable.Insert(recCities);
}

BOOL CCitiesData::Delete(const long lID)
{
	return m_oCitiesTable.DeleteWhereID(lID);
}