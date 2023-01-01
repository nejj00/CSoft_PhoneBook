
// CPhoneTypesView.cpp : implementation of the CPhoneTypesView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CPhoneTypesDoc.h"
#include "CPhoneTypesView.h"
#include "CPhoneTypesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define COLUMN_WIDTH 300
#define COLUMN_0 0

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesView

IMPLEMENT_DYNCREATE(CPhoneTypesView, CListView)

BEGIN_MESSAGE_MAP(CPhoneTypesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CITIES_UPDATE, &CPhoneTypesView::OnContextUpdate)
	ON_COMMAND(ID_CITIES_INSERT, &CPhoneTypesView::OnContextInsert)
	ON_COMMAND(ID_CITIES_DELETE, &CPhoneTypesView::OnContextDelete)

END_MESSAGE_MAP()

// Constructor / Destructor
// -------------------------
CPhoneTypesView::CPhoneTypesView() noexcept
{
	// TODO: add construction code here
}

CPhoneTypesView::~CPhoneTypesView()
{
}

// Methods
// ---------------------------
void CPhoneTypesView::InitListCrtl()
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.ModifyStyle(LVS_REPORT, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	oListCtrl.InsertColumn(COLUMN_0, _T("Phone Type"), LVCFMT_LEFT, COLUMN_WIDTH, -1);

	for (int i = 0; i < GetDocument()->GetPhoneTypesArray().GetCount(); i++)
	{
		ItemInsertion(oListCtrl, GetDocument()->GetPhoneTypesArray().GetAt(i));
	}
}

int CPhoneTypesView::GetItemIndexByID(CListCtrl& oListCtrl, long lID)
{
	for (int i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (lID == oListCtrl.GetItemData(i))
		{
			return i;
		}
	}
}

void CPhoneTypesView::UpdateViewUpdate(CObject* pHint, CListCtrl& oListCtrl)
{
	PHONE_TYPES* pPhoneType = (PHONE_TYPES*)pHint;

	int nIndex = GetItemIndexByID(oListCtrl, pPhoneType->lID);

	oListCtrl.SetItemText(nIndex, COLUMN_0, pPhoneType->szPhoneType);
}

void CPhoneTypesView::UpdateViewInsert(CObject* pHint, CListCtrl& oListCtrl)
{
	PHONE_TYPES* pPhoneType = (PHONE_TYPES*)pHint;

	ItemInsertion(oListCtrl, pPhoneType);
}

void CPhoneTypesView::ItemInsertion(CListCtrl& oListCtrl, PHONE_TYPES* recPhoneType)
{
	int nItem = oListCtrl.InsertItem(COLUMN_0, recPhoneType->szPhoneType);
	oListCtrl.SetItemData(nItem, recPhoneType->lID);
}

void CPhoneTypesView::UpdateViewDelete(CObject* pHint, CListCtrl& oListCtrl)
{
	long lID = (long)pHint;

	oListCtrl.DeleteItem(GetItemIndexByID(oListCtrl, lID));
}

void CPhoneTypesView::SelectItemData(CListCtrl& oListCtrl, POSITION& pos, PHONE_TYPES& recPhoneType)
{
	int nItem = oListCtrl.GetNextSelectedItem(pos);

	long lID = oListCtrl.GetItemData(nItem);

	int nIndex = GetDocument()->GetIndexCityWithID(lID);
	recPhoneType = *GetDocument()->GetPhoneTypesArray().GetAt(nIndex);
}

// Overrides
// ----------------
BOOL CPhoneTypesView::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style |= LVS_REPORT;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CPhoneTypesView::OnInitialUpdate()
{

	CListCtrl& oListCtrl = GetListCtrl();

	InitListCrtl();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

void CPhoneTypesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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



void CPhoneTypesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPhoneTypesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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

void CPhoneTypesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	PHONE_TYPES recPhoneType;
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	SelectItemData(oListCtrl, pos, recPhoneType);

	CPhoneTypesDialog oPhoneTypesDialog(recPhoneType, ContextActionSelect);

	oPhoneTypesDialog.DoModal();
}

void CPhoneTypesView::OnContextUpdate()
{
	PHONE_TYPES recPhoneType;
	CListCtrl& oListCtrl = GetListCtrl();
	CString strWord;

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	SelectItemData(oListCtrl, pos, recPhoneType);

	CPhoneTypesDialog oPhoneTypesDialog(recPhoneType, ContextActionUpdate);

	if (oPhoneTypesDialog.DoModal() != IDOK)
		return;

	GetDocument()->Update(recPhoneType.lID, recPhoneType);
}


void CPhoneTypesView::OnContextInsert()
{
	PHONE_TYPES recPhoneType;
	CListCtrl& oListCtrl = GetListCtrl();

	CPhoneTypesDialog oPhoneTypesDialog(recPhoneType, ContextActionInsert);

	if (oPhoneTypesDialog.DoModal() != IDOK)
		return;

	GetDocument()->Insert(recPhoneType);
}

void CPhoneTypesView::OnContextDelete()
{
	CListCtrl& oListCtrl = GetListCtrl();
	int nItem;

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	nItem = oListCtrl.GetNextSelectedItem(pos);

	long lID = oListCtrl.GetItemData(nItem);

	GetDocument()->Delete(lID);
} 

// CPhoneTypesView diagnostics

#ifdef _DEBUG
void CPhoneTypesView::AssertValid() const
{
	CListView::AssertValid();
}

void CPhoneTypesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPhoneTypesDoc* CPhoneTypesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhoneTypesDoc)));
	return (CPhoneTypesDoc*)m_pDocument;
}
#endif //_DEBUG


// CPhoneTypesView message handlers
