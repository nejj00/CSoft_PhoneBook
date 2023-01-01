
// CPersonsView.cpp : implementation of the CPersonsView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CPersonsDoc.h"
#include "CPersonsView.h" 
#include "CPersonsDialog.h"
#include "CPerson.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define COLUMN_WIDTH 300
#define COLUMN_0 0
#define COLUMN_1 1
#define COLUMN_2 2
#define COLUMN_3 3
#define COLUMN_4 4

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

IMPLEMENT_DYNCREATE(CPersonsView, CListView)

BEGIN_MESSAGE_MAP(CPersonsView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CITIES_UPDATE, &CPersonsView::OnContextUpdate)
	ON_COMMAND(ID_CITIES_INSERT, &CPersonsView::OnContextInsert)
	ON_COMMAND(ID_CITIES_DELETE, &CPersonsView::OnContextDelete)

END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsView::CPersonsView() noexcept
{
	// TODO: add construction code here
}

CPersonsView::~CPersonsView()
{
}

// Methods
// ----------------

void CPersonsView::InitListCrtl()
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.ModifyStyle(LVS_REPORT, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	oListCtrl.InsertColumn(COLUMN_0, _T("First Name"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	oListCtrl.InsertColumn(COLUMN_1, _T("Middle Name"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	oListCtrl.InsertColumn(COLUMN_2, _T("Last Name"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	oListCtrl.InsertColumn(COLUMN_3, _T("USN"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	oListCtrl.InsertColumn(COLUMN_4, _T("City"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	 
	for (int i = 0; i < GetDocument()->GetPersonsArray().GetCount(); i++)
	{
		ItemInsertion(oListCtrl, GetDocument()->GetPersonsArray().GetAt(i));
	}
}

int CPersonsView::GetItemIndexByID(CListCtrl& oListCtrl, long lID)
{
	for (int i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (lID == oListCtrl.GetItemData(i))
		{
			return i;
		}
	}
}

void CPersonsView::UpdateViewUpdate(CObject* pHint, CListCtrl& oListCtrl)
{
	PERSONS* pPerson = (PERSONS*)pHint;

	int nItem= GetItemIndexByID(oListCtrl, pPerson->lID);

	oListCtrl.SetItemText(nItem, COLUMN_0, pPerson->szFirstName);
	oListCtrl.SetItemText(nItem, COLUMN_1, pPerson->szMiddleName);
	oListCtrl.SetItemText(nItem, COLUMN_2, pPerson->szLastName);
	oListCtrl.SetItemText(nItem, COLUMN_3, pPerson->szUSN);

	for (int i = 0; i < GetDocument()->GetCitiesArray().GetCount(); i++)
	{
		if (GetDocument()->GetCitiesArray().GetAt(i)->lID == pPerson->lCityID)
			oListCtrl.SetItemText(nItem, COLUMN_4, GetDocument()->GetCitiesArray().GetAt(i)->szCityName);
	}
}

void CPersonsView::UpdateViewInsert(CObject* pHint, CListCtrl& oListCtrl)
{
	PERSONS* pPerson = (PERSONS*)pHint;

	ItemInsertion(oListCtrl, pPerson);
}

void CPersonsView::ItemInsertion(CListCtrl& oListCtrl, PERSONS* recPerson)
{
	int nItem = oListCtrl.InsertItem(COLUMN_0, recPerson->szFirstName);
	oListCtrl.SetItemText(nItem, COLUMN_1, recPerson->szMiddleName);
	oListCtrl.SetItemText(nItem, COLUMN_2, recPerson->szLastName);
	oListCtrl.SetItemText(nItem, COLUMN_3, recPerson->szUSN);

	for (int i = 0; i < GetDocument()->GetCitiesArray().GetCount(); i++)
	{
		if (GetDocument()->GetCitiesArray().GetAt(i)->lID == recPerson->lCityID)
			oListCtrl.SetItemText(nItem, COLUMN_4, GetDocument()->GetCitiesArray().GetAt(i)->szCityName);
	}
	oListCtrl.SetItemData(nItem, recPerson->lID);
}

void CPersonsView::UpdateViewDelete(CObject* pHint, CListCtrl& oListCtrl)
{
	long lID = (long)pHint;
	oListCtrl.DeleteItem(GetItemIndexByID(oListCtrl, lID));
}

void CPersonsView::SelectItemData(CListCtrl& oListCtrl, POSITION& pos, PERSONS& recPerson)
{
	int nItem = oListCtrl.GetNextSelectedItem(pos);

	long lID = oListCtrl.GetItemData(nItem);

	int nIndex = GetDocument()->GetIndexPersonWithID(lID);
	recPerson = *GetDocument()->GetPersonsArray().GetAt(nIndex);
}

// Overrides
// ----------------
BOOL CPersonsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CPersonsView::OnInitialUpdate()
{
	CListCtrl& oListCtrl = GetListCtrl();

	InitListCrtl();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

void CPersonsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oListCtrl = GetListCtrl();

	if (lHint == ViewActionUpdate)
	{
		UpdateViewUpdate(pHint, oListCtrl);
	}

	if (lHint == ViewActionInsert)
	{
		UpdateViewInsert(pHint, oListCtrl);
	}

	if (lHint == ViewActionDelete)
	{
		UpdateViewDelete(pHint, oListCtrl);
	}
}

void CPersonsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPersonsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CListCtrl& oListCtrl = GetListCtrl();

	CMenu oMenu;
	oMenu.LoadMenu(IDR_POPUP_CITIES);
	CMenu* pMenu = oMenu.GetSubMenu(0);

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		pMenu->EnableMenuItem(ID_CITIES_UPDATE, MF_GRAYED);
		pMenu->EnableMenuItem(ID_CITIES_DELETE, MF_GRAYED);

		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else
	{
		pMenu->EnableMenuItem(ID_CITIES_INSERT, MF_GRAYED);

		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

}

void CPersonsView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListCtrl& oListCtrl = GetListCtrl();
	CPerson oPerson;

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	SelectItemData(oListCtrl, pos, oPerson.GetPerson());

	GetDocument()->FillPersonFromView(oPerson);

	CPersonsDialog oPersonsDialog(oPerson, ContextActionSelect, GetDocument()->GetCitiesArray(), GetDocument()->GetPhoneTypesArray());

	if (oPersonsDialog.DoModal() != IDOK)
		return;
}

void CPersonsView::OnContextUpdate()
{
	CListCtrl& oListCtrl = GetListCtrl();
	CString strWord;

	CPerson oPerson;
	 
	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	SelectItemData(oListCtrl, pos, oPerson.GetPerson());

	GetDocument()->FillPersonFromView(oPerson);

	CPersonsDialog oPersonsDialog(oPerson, ContextActionUpdate, GetDocument()->GetCitiesArray(), GetDocument()->GetPhoneTypesArray()); // use CPerson

	if (oPersonsDialog.DoModal() != IDOK)
		return;

	GetDocument()->Update(oPerson.GetPerson().lID, oPerson);
}

void CPersonsView::OnContextInsert()
{
	CListCtrl& oListCtrl = GetListCtrl();

	CPerson oPerson;

	CPersonsDialog oPersonsDialog(oPerson, ContextActionInsert, GetDocument()->GetCitiesArray(), GetDocument()->GetPhoneTypesArray());

	if (oPersonsDialog.DoModal() != IDOK)
		return;

	GetDocument()->Insert(oPerson);
}

void CPersonsView::OnContextDelete()
{
	CListCtrl& oListCtrl = GetListCtrl();
	int nItem;

	CPerson oPerson;

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	SelectItemData(oListCtrl, pos, oPerson.GetPerson());

	GetDocument()->FillPersonFromView(oPerson);

	GetDocument()->Delete(oPerson);
}

// CPersonsView diagnostics

#ifdef _DEBUG
void CPersonsView::AssertValid() const
{
	CListView::AssertValid();
}

void CPersonsView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPersonsDoc* CPersonsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}
#endif //_DEBUG


// CPersonsView message handlers
