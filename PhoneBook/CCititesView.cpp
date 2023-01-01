
// CCititesView.cpp : implementation of the CCititesView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CCitiesDoc.h"
#include "CCititesView.h"
#include "CCitiesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define COLUMN_WIDTH 300
#define COLUMN_0 0
#define COLUMN_1 1

/////////////////////////////////////////////////////////////////////////////
// CCitiesView

IMPLEMENT_DYNCREATE(CCititesView, CListView)

BEGIN_MESSAGE_MAP(CCititesView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CITIES_UPDATE, &CCititesView::OnContextUpdate)
	ON_COMMAND(ID_CITIES_INSERT, &CCititesView::OnContextInsert)
	ON_COMMAND(ID_CITIES_DELETE, &CCititesView::OnContextDelete)

END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CCititesView::CCititesView() noexcept
{
	// TODO: add construction code here
}

CCititesView::~CCititesView()
{
}

// Methods
// ----------------
void CCititesView::InitListCrtl()
{
	CListCtrl& oListCtrl = GetListCtrl();

	oListCtrl.ModifyStyle(LVS_REPORT, LVS_REPORT);
	oListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	oListCtrl.InsertColumn(COLUMN_0, _T("City"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	oListCtrl.InsertColumn(COLUMN_1, _T("Region"), LVCFMT_LEFT, COLUMN_WIDTH, -1);

	int nCount = GetDocument()->GetCitiesArray().GetCount();

	for (int i = 0; i < GetDocument()->GetCitiesArray().GetCount(); i++)
	{
		ItemInsertion(oListCtrl, GetDocument()->GetCitiesArray().GetAt(i));
	}
}

int CCititesView::GetItemIndexByID(CListCtrl& oListCtrl, long lID)
{
	for (int i = 0; i < oListCtrl.GetItemCount(); i++)
	{
		if (lID == oListCtrl.GetItemData(i))
		{
			return i;
		}
	}
}

void CCititesView::UpdateViewUpdate(CObject* pHint, CListCtrl& oListCtrl)
{
	CITIES* pCity = (CITIES*)pHint;

	int nIndex = GetItemIndexByID(oListCtrl, pCity->lID);

	oListCtrl.SetItemText(nIndex, COLUMN_0, pCity->szCityName);
	oListCtrl.SetItemText(nIndex, COLUMN_1, pCity->szArea);
}


void CCititesView::UpdateViewInsert(CObject* pHint, CListCtrl& oListCtrl)
{
	CITIES* pCity = (CITIES*)pHint;

	ItemInsertion(oListCtrl, pCity);
}

void CCititesView::ItemInsertion(CListCtrl& oListCtrl, CITIES* recCity)
{
	int nItem = oListCtrl.InsertItem(COLUMN_0, recCity->szCityName);
	oListCtrl.SetItemText(nItem, COLUMN_1, recCity->szArea);
	oListCtrl.SetItemData(nItem, recCity->lID);
}


void CCititesView::UpdateViewDelete(CObject* pHint, CListCtrl& oListCtrl)
{
	long lID = (long)pHint;

	oListCtrl.DeleteItem(GetItemIndexByID(oListCtrl, lID));
}

void CCititesView::SelectItemData(CListCtrl& oListCtrl, POSITION& pos, CITIES& recCity)
{
	int nItem = oListCtrl.GetNextSelectedItem(pos);

	long lID = oListCtrl.GetItemData(nItem);

	int nIndex = GetDocument()->GetIndexCityWithID(lID);
	recCity = *GetDocument()->GetCitiesArray().GetAt(nIndex);
}

// Overrides
// ----------------
BOOL CCititesView::PreCreateWindow(CREATESTRUCT& cs)
{
	//cs.style |= LVS_REPORT;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCititesView::OnInitialUpdate()
{
	CListCtrl& oListCtrl = GetListCtrl();

	InitListCrtl();
	
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}



void CCititesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
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

void CCititesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCititesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
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

void CCititesView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CITIES recCity;
	CListCtrl& oListCtrl = GetListCtrl();

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
		return;
	
	SelectItemData(oListCtrl, pos, recCity);

	CCitiesDialog oCitiesDialog(recCity, ContextActionSelect);

	oCitiesDialog.DoModal();
}

void CCititesView::OnContextUpdate()
{
	CITIES recCity;
	CListCtrl& oListCtrl = GetListCtrl();
	CString strWord;

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	SelectItemData(oListCtrl, pos, recCity);

	CCitiesDialog oCitiesDialog(recCity, ContextActionUpdate);

	if (oCitiesDialog.DoModal() != IDOK)
		return;
	
	GetDocument()->Update(recCity.lID, recCity);
}


void CCititesView::OnContextInsert()
{
	CITIES recCity;
	CListCtrl& oListCtrl = GetListCtrl();

	CCitiesDialog oCitiesDialog(recCity, ContextActionInsert);

	if (oCitiesDialog.DoModal() != IDOK)
		return;

	GetDocument()->Insert(recCity);
}

void CCititesView::OnContextDelete()
{
	CListCtrl& oListCtrl = GetListCtrl();
	int nItem;

	POSITION pos = oListCtrl.GetFirstSelectedItemPosition();
	nItem = oListCtrl.GetNextSelectedItem(pos);
		
	long lID = oListCtrl.GetItemData(nItem);

	GetDocument()->Delete(lID);
}

// CCititesView diagnostics

#ifdef _DEBUG
void CCititesView::AssertValid() const
{
	CListView::AssertValid();
}

void CCititesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCititesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG
// CCititesView message handlers
