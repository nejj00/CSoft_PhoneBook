#pragma once
#pragma once
#include "CPhoneTypesTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary>
/// Клас съхраняващ данните на таблицата PHONE TYPES
/// </summary>
class CPhoneTypesData
{
// Methods
// -----------
public:
	/// <summary>
	/// Извикване на SelectAll от CCitiesTable
	/// </summary>
	/// <param name="oCitiesArray"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectAll(CPhoneTypesArray& oPhoneTypesArray);
	/// <summary>
	/// Извикване на SelectWherID от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCities"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectWhereID(const long lID, PHONE_TYPES& recPhoneType);
	/// <summary>
	/// Извикване на UpdateWhereID от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCities"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL UpdateWhereID(const long lID, PHONE_TYPES& recPhoneType);
	/// <summary>
	/// Извикване на Insert от CCitiesTable
	/// </summary>
	/// <param name="recCities"> TRUE при успешно изпълнение и FALSE при неуспешно </param>
	/// <returns></returns>
	BOOL Insert(PHONE_TYPES& recPhoneType);
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
	/// Масив съдържащ записите от базата данни за хора
	/// </summary>
	CPhoneTypesTable m_oPhoneTypesTable = CPhoneTypesTable();


};
