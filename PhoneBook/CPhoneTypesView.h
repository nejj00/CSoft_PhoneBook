
// CPhoneTypesView.h : interface of the CPhoneTypesView class
//

#pragma once
#include "CPhoneTypesDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

/// <summary>
/// Клас отговарящ за визуакизацията на данните от таблица PHONE_TYPES
/// </summary>
class CPhoneTypesView : public CListView
{
// Constants
// ----------------
public:
	CPhoneTypesDoc* GetDocument() const;


// Constructor / Destructor
// ----------------
protected: // create from serialization only
	CPhoneTypesView() noexcept;
	DECLARE_DYNCREATE(CPhoneTypesView)

public:
	virtual ~CPhoneTypesView();


// Methods
// ----------------
private:
	/// <summary>
	/// Инициализиране на ListCtrl - задаване на колони и добавяне на редове
	/// </summary>
	void InitListCrtl();
	/// <summary>
	/// Обновяване на view-то и масива след обновяване на запис от базата данни
	/// </summary>
	/// <param name="pHint"></param>
	/// <param name="oListCtrl"></param>
	void UpdateViewUpdate(CObject* pHint, CListCtrl& oListCtrl);
	/// <summary>
	/// Получаване на индекса на ред от ListCtrl спрямо ID-то на града
	/// </summary>
	/// <param name="oListCtrl"></param>
	/// <param name="lID"></param>
	/// <returns> Индекс на реда </returns>
	int GetItemIndexByID(CListCtrl& oListCtrl, long lID);
	/// <summary>
	/// Добавяне на ред във view-то и на елемент в масива
	/// </summary>
	/// <param name="pHint"></param>
	/// <param name="oListCtrl"></param>
	void UpdateViewInsert(CObject* pHint, CListCtrl& oListCtrl);
	/// <summary>
	/// Добавяне на ред в ListCtrl и здаване на Item data-та
	/// </summary>
	/// <param name="oListCtrl"></param>
	/// <param name="recCity"></param>
	void ItemInsertion(CListCtrl& oListCtrl, PHONE_TYPES* recCity);
	/// <summary>
	/// Изтриване на ред от view-то и елемент от масива
	/// </summary>
	/// <param name="pHint"></param>
	/// <param name="oListCtrl"></param>
	void UpdateViewDelete(CObject* pHint, CListCtrl& oListCtrl);
	/// <summary>
	/// Поставяне на данните в recCity при маркирането им с мишката
	/// </summary>
	/// <param name="oListCtrl"></param>
	/// <param name="pos"></param>
	/// <param name="recCity"></param>
	void SelectItemData(CListCtrl& oListCtrl, POSITION& pos, PHONE_TYPES& recCity);

// Overrides
// ----------------
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

protected:
	virtual void OnInitialUpdate() override; // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) override;




	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnContextUpdate();
	afx_msg void OnContextInsert();
	afx_msg void OnContextDelete();


	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CPhoneTypesView.cpp
inline CPhoneTypesDoc* CPhoneTypesView::GetDocument() const
{
	return reinterpret_cast<CPhoneTypesDoc*>(m_pDocument);
}
#endif

