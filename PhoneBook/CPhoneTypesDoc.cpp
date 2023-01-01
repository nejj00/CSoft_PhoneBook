
// CPhoneTypesDoc.cpp : implementation of the CPhoneTypesDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CPhoneTypesDoc.h"
#include "CPhoneTypesData.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPhoneTypesDoc

IMPLEMENT_DYNCREATE(CPhoneTypesDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhoneTypesDoc, CDocument)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhoneTypesDoc

// Constructor / Destructor
// ---------------------------
CPhoneTypesDoc::CPhoneTypesDoc() noexcept
{
	// TODO: add one-time construction code here

}

CPhoneTypesDoc::~CPhoneTypesDoc()
{
}

// Methods
// --------------------------
long CPhoneTypesDoc::GetCityID(int nIndex)
{
	return m_oPhoneTypesArray.GetAt(nIndex)->lID;
}

int CPhoneTypesDoc::GetIndexCityWithID(long lID)
{
	for (int i = 0; i < m_oPhoneTypesArray.GetCount(); i++)
	{
		if (GetCityID(i) == lID)
		{
			return i;

			break;
		}
	}
}

BOOL CPhoneTypesDoc::Update(long lID, PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	if (!oPhoneTypesData.UpdateWhereID(lID, recPhoneType))
	{
		return FALSE;
	}

	*m_oPhoneTypesArray.GetAt(GetIndexCityWithID(lID)) = recPhoneType;

	UpdateAllViews(NULL, ViewActionUpdate, (CObject*)&recPhoneType);

	return TRUE;
}

BOOL CPhoneTypesDoc::Insert(PHONE_TYPES& recPhoneType)
{
	CPhoneTypesData oPhoneTypesData;

	if (!oPhoneTypesData.Insert(recPhoneType))
	{
		return FALSE;
	}

	m_oPhoneTypesArray.Add(new PHONE_TYPES(recPhoneType));

	UpdateAllViews(NULL, ViewActionInsert, (CObject*)&recPhoneType);

	return TRUE;
}

BOOL CPhoneTypesDoc::Delete(long lID)
{
	CPhoneTypesData oPhoneTypesData;

	if (!oPhoneTypesData.Delete(lID))
	{
		return FALSE;
	}

	m_oPhoneTypesArray.DeleteAt(GetIndexCityWithID(lID));
	UpdateAllViews(NULL, ViewActionDelete, (CObject*)lID);

	return TRUE;
}

CPhoneTypesArray& CPhoneTypesDoc::GetPhoneTypesArray()
{
	return m_oPhoneTypesArray;
}

// Overrides
// ----------------
BOOL CPhoneTypesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPhoneTypesData oPhoneTypesData;

	if (!oPhoneTypesData.SelectAll(m_oPhoneTypesArray))
	{
		return FALSE;
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CPhoneTypesDoc serialization

void CPhoneTypesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPhoneTypesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPhoneTypesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPhoneTypesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPhoneTypesDoc diagnostics

#ifdef _DEBUG
void CPhoneTypesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhoneTypesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CPhoneTypesDoc commands
