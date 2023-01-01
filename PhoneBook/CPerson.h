#pragma once
#include "Structures.h"
#include "CPhoneNumbersTable.h"

/// <summary>
/// Транспортен клас съдържащ информация за един човек
/// </summary>
class CPerson
{
// Constructor & Destructor
// ------------------------
public:
	~CPerson();

// Methods
// ------------------------
public:
	/// <summary>
	/// Връща референция към член на класа m_recPerson
	/// </summary>
	/// <returns>  </returns>
	PERSONS& GetPerson();
	/// <summary>
	/// Връща референциия към масив, член на класа, m_oPhoneNumbersArray
	/// </summary>
	/// <returns></returns>
	CPhoneNumbersArray& GetPhoneNumbers();

// Members
// ------------------------
private:
	/// <summary>
	/// За съхранение на обект от структура PERSONS
	/// </summary>
	PERSONS m_recPerson;
	/// <summary>
	/// Масив за съхранение на номерата на човека в m_recPerson
	/// </summary>
	CPhoneNumbersArray m_oPhoneNumbersArray;
};