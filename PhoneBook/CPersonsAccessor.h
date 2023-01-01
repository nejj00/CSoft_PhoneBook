#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define ACCESSOR_0 0
#define ACCESSOR_1 1

#define DB_COLUMN_1 1
#define DB_COLUMN_2 2
#define DB_COLUMN_3 3
#define DB_COLUMN_4 4
#define DB_COLUMN_5 5
#define DB_COLUMN_6 6
#define DB_COLUMN_7 7

/// <summary>
/// Клас за достъп към таблицата PERSONS
/// </summary>
class CPersonsAccessor
{
protected:
	/// <summary>
	/// Променлива съхраняваща запис от базата данни
	/// </summary>
	PERSONS m_recPerson;

	BEGIN_ACCESSOR_MAP(CPersonsAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_0, true)
		COLUMN_ENTRY(DB_COLUMN_1, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_1, true)
		COLUMN_ENTRY(DB_COLUMN_2, m_recPerson.nUpdateCounter)
		COLUMN_ENTRY(DB_COLUMN_3, m_recPerson.szFirstName)
		COLUMN_ENTRY(DB_COLUMN_4, m_recPerson.szMiddleName)
		COLUMN_ENTRY(DB_COLUMN_5, m_recPerson.szLastName)
		COLUMN_ENTRY(DB_COLUMN_6, m_recPerson.szUSN)
		COLUMN_ENTRY(DB_COLUMN_7, m_recPerson.lCityID)

		END_ACCESSOR()

	END_ACCESSOR_MAP()
	
};