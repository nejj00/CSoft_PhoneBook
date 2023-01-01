#pragma once
#include "pch.h"

/////////////////////////////////////////////////////////////////////////////
// CSelfCleaningTypedPtrArray

/// <summary>
/// Клас описващ типизиран масив от pointer-и, който сам се изчиства
/// </summary>
/// <typeparam name="TYPE"> Тип на данните, които ще се съдържат в масива </typeparam>
template<class TYPE>
class CSelfCleaningTypedPtrArray : public CTypedPtrArray<CPtrArray, TYPE>
{
public:
// Constructor / Destructor
// -------------------------
    CSelfCleaningTypedPtrArray();
    ~CSelfCleaningTypedPtrArray();

// Methods
// -----------------------
public:
    /// <summary>
    /// Метод за изчистване на масива при изтриване на запис
    /// </summary>
    /// <param name="nIndex"></param>
    void DeleteAt(int nIndex);
  
};

template<class TYPE>
CSelfCleaningTypedPtrArray<TYPE>::CSelfCleaningTypedPtrArray()
{}

template<class TYPE>
CSelfCleaningTypedPtrArray<TYPE>::~CSelfCleaningTypedPtrArray()
{
    for (int i = 0; i < CTypedPtrArray<CPtrArray, TYPE>::GetCount(); i++)
    {
        delete GetAt(i);
    }
    RemoveAll();
}

template<class TYPE>
void CSelfCleaningTypedPtrArray<TYPE>::DeleteAt(int nIndex)
{
    TYPE pType = GetAt(nIndex);
    RemoveAt(nIndex);

    delete pType;
}