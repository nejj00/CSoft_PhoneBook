#pragma once
#include "CPersonsTable.h"
#include "CPerson.h"
#include "CPersonsTable.h"
#include "CPhoneNumbersTable.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

/// <summary>
/// Клас съхраняващ данните на таблицата PERSONS
/// </summary>
class CPersonsData
{
private:
	

// Methods
// --------------
public:
	/// <summary>
	/// Извикване на SelectAll от CCitiesTable
	/// </summary>
	/// <param name="oCitiesArray"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectAll(CPersonsArray& oPersonsArray);
	/// <summary>
	/// Извикване на SelectWherID от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCities"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL SelectWhereID(const long lID, CPerson& oPersons);
	/// <summary>
	/// Извикване на UpdateWhereID от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCities"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL UpdateWhereID(const long lID, CPerson& oPersons);
	/// <summary>
	/// Извикване на Insert от CCitiesTable
	/// </summary>
	/// <param name="recCities"> </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Insert(CPerson& oPersons);
	/// <summary>
	/// Извикване на Delete от CCitiesTable
	/// </summary>
	/// <param name="lID"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Delete(CPerson& oPerson);
	/// <summary>
	/// Вмъкване на телефонен номер при UpdateWhereID метода
	/// </summary>
	/// <param name="oPerson"> Обект от клас CPerson </param>
	/// <param name="oPhoneNumbersTable"> Обект от табличен клас CPhoneNumbersTable </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL InsertPhoneNumber(CPerson& oPerson, CPhoneNumbersTable& oPhoneNumbersTable);
	/// <summary>
	/// Актуализиране или изтриване на номер при UpdateWhereID метода
	/// </summary>
	/// <param name="oPerson"> Обект от клас CPerson </param>
	/// <param name="oPhoneNumbersTable"> Обект от табличен клас CPhoneNumbersTable </param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL UpdateDeletePhoneNumber(CPerson& oPerson, CPhoneNumbersTable& oPhoneNumbersTable);
	/// <summary>
	/// Прекратяване на транзакция и затваряне на сесия
	/// </summary>
	void SessionAbortClose();


// Members
// ---------------
public:
	/// <summary>
	/// Сесия използвана при транзакциите в методите за вмъкване, актуализация и изтриване
	/// </summary>
	CSession m_oSession;
};
