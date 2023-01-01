
// CPhoneTypesDoc.h : interface of the CPhoneTypesDoc class
//


#pragma once
#include "CPhoneTypesAccessor.h"
#include "ActionEnums.h"


/// <summary>
/// Клас за работа с данните на таблицата PHONE TYPES
/// </summary>
class CPhoneTypesDoc : public CDocument
{
	// Constructor / Destructor
	// ----------------
protected: // create from serialization only
	CPhoneTypesDoc() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesDoc)

public:
	virtual ~CPhoneTypesDoc();


// Methods
// ----------------
public:
	/// <summary>
	/// Обновяване на запис от базата данни 
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCity"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Update(long lID, PHONE_TYPES& recPhoneType);
	/// <summary>
	/// Добавяне на запис към базата данни
	/// </summary>
	/// <param name="recCity"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Insert(PHONE_TYPES& recPhoneType);
	/// <summary>
	/// Изтриване на запис от базата данни
	/// </summary>
	/// <param name="lID"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Delete(long lID);
	/// <summary>
	/// Връщане масива m_oCitiesArray
	/// </summary>
	/// <returns> m_oCitiesArray </returns>
	CPhoneTypesArray& GetPhoneTypesArray();
	/// <summary>
	/// Връща ID на елемент от масива m_oCitiesArray
	/// </summary>
	/// <param name="nIndex"></param>
	/// <returns> променлива от тип long </returns>
	long GetCityID(int nIndex);
	/// <summary>
	/// Връща индекс на града с подаденото ID
	/// </summary>
	/// <param name="lID"> ID на град </param>
	/// <returns></returns>
	int GetIndexCityWithID(long lID);


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
	/// Масив, който ще съдържа записите от базата данни
	/// </summary>
	CPhoneTypesArray m_oPhoneTypesArray;
};

