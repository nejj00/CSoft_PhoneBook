#include "pch.h"
#include "CPersonsTable.h"
#include "ActionEnums.h"
/////////////////////////////////////////////////////////////////////////////
// CPersonsTable

CPersonsTable::CPersonsTable(CSession& oSession) : CBaseTable(_T("PERSONS"), oSession)
{
}

PERSONS& CPersonsTable::GetStruct()
{
	return m_recPerson;
}

int& CPersonsTable::GetUpdateCounter(PERSONS& recPerson)
{
	return recPerson.nUpdateCounter;
}