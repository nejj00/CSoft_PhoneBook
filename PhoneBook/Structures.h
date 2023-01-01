#pragma once
#include "framework.h"
#include <afxtempl.h>
#include "CSelfCleaningTypedPtrArray.h"

#define CITIES_SIZE 128
#define PHONE_TYPES_SIZE 16
#define PERSONS_SIZE 32
#define PHONE_NUMBERS_SIZE 32

/// <summary>
/// Структура CITIES
/// </summary>
struct CITIES
{
	/// <summary> Уникален идентификатор за ред </summary>
	long lID;
	/// <summary> Версия </summary>
	int nUpdateCounter;
	/// <summary> Име на града </summary>
	TCHAR szCityName[CITIES_SIZE];
	/// <summary> Име на областта </summary>
	TCHAR szArea[CITIES_SIZE];

	CITIES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
/// Структура PHONE_TYPES
/// </summary>
struct PHONE_TYPES
{
	//// <summary> Уникален идентификатор за ред </summary>
	long lID;
	/// <summary> Версия </summary>
	int nUpdateCounter;
	/// <summary> Име на типа </summary>
	TCHAR szPhoneType[PHONE_TYPES_SIZE];

	PHONE_TYPES()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

};


/// <summary>
/// Структура PERSONS
/// </summary>
struct PERSONS
{
	/// <summary> Уникален идентификатор за ред </summary>
	long lID;
	/// <summary> Версия </summary>
	int nUpdateCounter;
	/// <summary> Име </summary>
	TCHAR szFirstName[PERSONS_SIZE];
	/// <summary> Бащино име </summary>
	TCHAR szMiddleName[PERSONS_SIZE];
	/// <summary> Фамилно име </summary>
	TCHAR szLastName[PERSONS_SIZE];
	/// <summary> ЕГН </summary>
	TCHAR szUSN[PERSONS_SIZE];
	/// <summary> Идентификатор за град </summary>
	long lCityID;

	PERSONS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};


/// <summary>
/// Структура PHONE_NUMBERS
/// </summary>
struct PHONE_NUMBERS
{
	/// <summary> Уникален идентификатор за ред </summary>
	long lID;
	/// <summary> Версия </summary>
	int nUpdateCounter;
	/// <summary> Идентификатор за човек </summary>
	long lPersonID;
	/// <summary> Идентификатор за тип на телефона </summary>
	long lPhoneTypeID;
	/// <summary> Телефонен номер </summary>
	TCHAR szPhoneNumber[PHONE_NUMBERS_SIZE];

	PHONE_NUMBERS()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CSelfCleaningTypedPtrArray<CITIES*> CCitiesArray;
typedef CSelfCleaningTypedPtrArray<PHONE_TYPES*> CPhoneTypesArray;
typedef CSelfCleaningTypedPtrArray<PERSONS*> CPersonsArray;
typedef CSelfCleaningTypedPtrArray<PHONE_NUMBERS*> CPhoneNumbersArray;