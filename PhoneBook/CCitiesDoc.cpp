
// CCitiesDoc.cpp : implementation of the CCitiesDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CCitiesDoc.h"
#include "CCitiesData.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCitiesDoc

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCitiesDoc

// Constructor / Destructor
// ----------------

CCitiesDoc::CCitiesDoc() noexcept
{
	// TODO: add one-time construction code here

}

CCitiesDoc::~CCitiesDoc()
{
}

// Methods
// ----------------

long CCitiesDoc::GetCityID(int nIndex)
{
	return m_oCitiesArray.GetAt(nIndex)->lID;
}

int CCitiesDoc::GetIndexCityWithID(long lID)
{
	for (int i = 0; i < m_oCitiesArray.GetCount(); i++)
	{
		if (GetCityID(i) == lID)
		{
			return i;

			break;
		}
	}
}

BOOL CCitiesDoc::Update(long lID, CITIES &recCity)
{
	CCitiesData oCitiesData;

	if (!oCitiesData.UpdateWhereID(lID, recCity))
	{
		return FALSE;
	}
	
	*m_oCitiesArray.GetAt(GetIndexCityWithID(lID)) = recCity;

	UpdateAllViews(NULL, ViewActionUpdate, (CObject*)&recCity);

	return TRUE;
}

BOOL CCitiesDoc::Insert(CITIES& recCity)
{
	CCitiesData oCitiesData;
	
	if (!oCitiesData.Insert(recCity))
	{
		return FALSE;
	}

	m_oCitiesArray.Add(new CITIES(recCity));

	UpdateAllViews(NULL, ViewActionInsert, (CObject*)&recCity);

	return TRUE;
}

BOOL CCitiesDoc::Delete(long lID)
{
	CCitiesData oCitiesData;

	if (!oCitiesData.Delete(lID))
	{
		return FALSE;
	}

	m_oCitiesArray.DeleteAt(GetIndexCityWithID(lID));
	UpdateAllViews(NULL, ViewActionDelete, (CObject*)lID);

	return TRUE;
}

CCitiesArray& CCitiesDoc::GetCitiesArray()
{
	return m_oCitiesArray;
}


// Overrides
// ----------------

BOOL CCitiesDoc::OnNewDocument()
{

	if (!CDocument::OnNewDocument())
		return FALSE;

	CCitiesData oCitiesData;

	if (!oCitiesData.SelectAll(m_oCitiesArray))
	{
		return FALSE;
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CCitiesDoc serialization

void CCitiesDoc::Serialize(CArchive& ar)
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
void CCitiesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCitiesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCitiesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCitiesDoc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CCitiesDoc commands
