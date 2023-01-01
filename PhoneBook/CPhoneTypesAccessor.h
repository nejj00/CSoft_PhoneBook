#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define ACCESSOR_0 0
#define ACCESSOR_1 1

#define DB_COLUMN_1 1
#define DB_COLUMN_2 2
#define DB_COLUMN_3 3


/// <summary>
/// Клас за достъп към таблицата PERSONS
/// </summary>
class CPhoneTypesAccessor
{
protected:
	/// <summary>
	/// Променлива съхраняваща запис от базата данни
	/// </summary>
	PHONE_TYPES m_recPhoneType;

	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_0, true)
		COLUMN_ENTRY(DB_COLUMN_1, m_recPhoneType.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_1, true)
		COLUMN_ENTRY(DB_COLUMN_2, m_recPhoneType.nUpdateCounter)
		COLUMN_ENTRY(DB_COLUMN_3, m_recPhoneType.szPhoneType)

		END_ACCESSOR()

	END_ACCESSOR_MAP()

};
