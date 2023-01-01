#include "pch.h"
#include "CPerson.h"

// Constructors & Destructors
// ---------------------------
CPerson::~CPerson()
{
	for (int i = 0; i < m_oPhoneNumbersArray.GetCount(); i++)
	{
		m_oPhoneNumbersArray.DeleteAt(i);
	}
}

// Methods
// -----------------------
PERSONS& CPerson::GetPerson()
{
	return m_recPerson;
}

CPhoneNumbersArray& CPerson::GetPhoneNumbers()
{
	return m_oPhoneNumbersArray;
}