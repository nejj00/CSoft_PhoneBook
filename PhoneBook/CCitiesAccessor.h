#pragma once
#include <atldbcli.h>
#include "Structures.h"

#define ACCESSOR_0 0
#define ACCESSOR_1 1

#define DB_COLUMN_1 1
#define DB_COLUMN_2 2
#define DB_COLUMN_3 3
#define DB_COLUMN_4 4

/// <summary>
/// Клас за достъп към таблицата CITIES
/// </summary>
class CCitiesAccessor
{
protected:
	/// <summary>
	/// Променлива съхраняваща запис от базата данни
	/// </summary>
	CITIES m_recCity;

	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
		BEGIN_ACCESSOR(ACCESSOR_0, true)
			COLUMN_ENTRY(DB_COLUMN_1, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(ACCESSOR_1, true)
			COLUMN_ENTRY(DB_COLUMN_2, m_recCity.nUpdateCounter)
			COLUMN_ENTRY(DB_COLUMN_3, m_recCity.szCityName)
			COLUMN_ENTRY(DB_COLUMN_4, m_recCity.szArea)
		END_ACCESSOR()

	END_ACCESSOR_MAP()

};
