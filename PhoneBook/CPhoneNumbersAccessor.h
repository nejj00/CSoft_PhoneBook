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


/// <summary>
/// Клас за достъп към таблицата PERSONS
/// </summary>
class CPhoneNumbersAccessor
{
protected:
	/// <summary>
	/// Променлива съхраняваща запис от базата данни
	/// </summary>
	PHONE_NUMBERS m_recPhoneNumber;

	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_0, true)
		COLUMN_ENTRY(DB_COLUMN_1, m_recPhoneNumber.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_1, true)
		COLUMN_ENTRY(DB_COLUMN_2, m_recPhoneNumber.nUpdateCounter)
		COLUMN_ENTRY(DB_COLUMN_3, m_recPhoneNumber.lPersonID)
		COLUMN_ENTRY(DB_COLUMN_4, m_recPhoneNumber.lPhoneTypeID)
		COLUMN_ENTRY(DB_COLUMN_5, m_recPhoneNumber.szPhoneNumber)

		END_ACCESSOR()

	END_ACCESSOR_MAP()

};