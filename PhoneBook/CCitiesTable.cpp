#include "pch.h"
#include "CCitiesTable.h"

// Constructors & Destructors
// ---------------------------
CCitiesTable::CCitiesTable() : CBaseTable(_T("CITIES"))
{

}

// Methods
// -------------------------
CITIES& CCitiesTable::GetStruct()
{
	return m_recCity;
}

int& CCitiesTable::GetUpdateCounter(CITIES& recCity)
{
	return recCity.nUpdateCounter;
}