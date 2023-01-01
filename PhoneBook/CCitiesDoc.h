
// CCitiesDoc.h : interface of the CCitiesDoc class
//


#pragma once
#include "CCitiesAccessor.h"
#include "ActionEnums.h"

/*
enum ViewAction {
	ViewActionUpdate,
	ViewActionInsert,
	ViewActionDelete
};
*/

/// <summary>
/// Клас за работа с данните на таблицата CITIES
/// </summary>
class CCitiesDoc : public CDocument
{
// Constructor / Destructor
// ----------------
protected: // create from serialization only
	CCitiesDoc() noexcept;
	DECLARE_DYNCREATE(CCitiesDoc)

public:
	virtual ~CCitiesDoc();


// Methods
// ----------------
public:
	/// <summary>
	/// Обновяване на запис от базата данни 
	/// </summary>
	/// <param name="lID"></param>
	/// <param name="recCity"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Update(long lID, CITIES &recCity);
	/// <summary>
	/// Добавяне на запис към базата данни
	/// </summary>
	/// <param name="recCity"></param>
	/// <returns> TRUE при успешно изпълнение и FALSE при неуспешно </returns>
	BOOL Insert(CITIES& recCity);
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
	CCitiesArray& GetCitiesArray();
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
	CCitiesArray m_oCitiesArray;
};
