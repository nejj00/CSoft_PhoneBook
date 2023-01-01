#pragma once
#include "CCitiesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesData

/// <summary>
/// Клас съхраняващ данните на таблицата CITIES
/// </summary>
class CCitiesData
{

// Methods
// -----------
public:
	/// <summary>
	/// Извикване на SelectAll от CCitiesTable
	/// </summary>
	/// <param name="oCitiesArray"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectAll(CCitiesArray& oCitiesArray);
	/// <summary>
	/// Извикване на SelectWherID от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCities"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectWhereID(const long lID, CITIES& recCities);
	/// <summary>
	/// Извикване на UpdateWhereID от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCities"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL UpdateWhereID(const long lID, CITIES& recCities);
	/// <summary>
	/// Извикване на Insert от CCitiesTable
	/// </summary>
	/// <param name="recCities"> TRUE при успешно изпълнение и FALSE при неуспешно </param>
	/// <returns></returns>
	BOOL Insert(CITIES& recCities);
	/// <summary>
	/// Извикване на Delete от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Delete(const long lID);

// Members
// -----------
private:
	/// <summary>
	/// Масив съдържащ записите от базата данни за градовете
	/// </summary>
	CCitiesTable m_oCitiesTable = CCitiesTable();

};