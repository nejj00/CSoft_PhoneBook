
// CPersonsDoc.h : interface of the CPersonsDoc class
//


#pragma once
#include "CPersonsAccessor.h"
#include "ActionEnums.h"
#include "CPerson.h"


/// <summary>
/// Клас за работа с данните на таблицата PERSONS
/// </summary>
class CPersonsDoc : public CDocument
{
// Constructor / Destructor
// ----------------
protected: // create from serialization only
	CPersonsDoc() noexcept;
	DECLARE_DYNCREATE(CPersonsDoc)

public:
	virtual ~CPersonsDoc();


// Methods
// ----------------
public:
	/// <summary>
	/// Обновяване на запис от базата данни 
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCity"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Update(long lID, CPerson& oPerson);
	/// <summary>
	/// Добавяне на запис към базата данни
	/// </summary>
	/// <param name="recCity"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Insert(CPerson& oPerson);
	/// <summary>
	/// Изтриване на запис от базата данни
	/// </summary>
	/// <param name="lID"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Delete(CPerson& oPerson);
	/// <summary>
	/// Връщане масива m_oCitiesArray
	/// </summary>
	/// <returns> m_oCitiesArray </returns>
	CPersonsArray& GetPersonsArray();
	/// <summary>
	/// Връща ID на елемент от масива m_oCitiesArray
	/// </summary>
	/// <param name="nIndex"></param>
	/// <returns> променлива от тип long </returns>
	long GetCityID(int nIndex);
	/// <summary>
	/// Връща индекс на човека с подаденото ID
	/// </summary>
	/// <param name="lID"> ID на град </param>
	/// <returns> Индекс на човека </returns>
	int GetIndexPersonWithID(long lID);
	/// <summary>
	/// Запълва масива с телефонни номера на обект от CPerson
	/// </summary>
	/// <param name="oPerson"></param>
	void FillPersonFromView(CPerson& oPerson);
	/// <summary>
	/// Връща масив с градовете от базата данни
	/// </summary>
	/// <returns> Масив от тип CCitiesArray </returns>
	CCitiesArray& GetCitiesArray();
	/// <summary>
	/// Връща масив с телефонните типове от базата данни
	/// </summary>
	/// <returns> Масив от тип CPhoneTypesArray </returns>
	CPhoneTypesArray& GetPhoneTypesArray();

// Overrides
// ----------------
public:
	virtual BOOL OnNewDocument() override;
	virtual void Serialize(CArchive& ar) override;

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

// Members
// ----------------
private:
	/// <summary>
	/// Масив, който ще съдържа записите от таблица PERSONS от базата данни
	/// </summary>
	CPersonsArray m_oPersonsArray;
	/// <summary>
	/// Масив, който ще съдържа записите от таблица CITES от базата данни
	/// </summary>
	CCitiesArray m_oCitiesArray;
	/// <summary>
	/// Масив, който ще съдържа записите от таблица PHONE_TYPES от базата данни
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};
