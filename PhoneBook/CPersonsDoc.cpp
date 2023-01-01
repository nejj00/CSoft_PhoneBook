
// CPersonsDoc.cpp : implementation of the CPersonsDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhoneBook.h"
#endif

#include "CPersonsDoc.h"
#include "CPersonsData.h"
#include "CCitiesTable.h"
#include "CPhoneTypesTable.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPersonsDoc

IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersonsDoc

// Constructor / Destructor
// ----------------
CPersonsDoc::CPersonsDoc() noexcept
{
	// TODO: add one-time construction code here

}

CPersonsDoc::~CPersonsDoc()
{
}

// Methods
// ----------------
long CPersonsDoc::GetCityID(int nIndex)
{
	return m_oPersonsArray.GetAt(nIndex)->lID;
}

int CPersonsDoc::GetIndexPersonWithID(long lID)
{
	for (int i = 0; i < m_oPersonsArray.GetCount(); i++)
	{
		if (GetCityID(i) == lID)
		{
			return i;

			break;
		}
	}
}

void CPersonsDoc::FillPersonFromView(CPerson& oPerson)
{
	CPersonsData oPersonData;
	oPersonData.SelectWhereID(oPerson.GetPerson().lID, oPerson);
}

BOOL CPersonsDoc::Update(long lID, CPerson& recPerson)
{
	CPersonsData oPersonsData;

	if (!oPersonsData.UpdateWhereID(lID, recPerson))
	{
		return FALSE;
	}

	*m_oPersonsArray.GetAt(GetIndexPersonWithID(lID)) = recPerson.GetPerson();

	UpdateAllViews(NULL, ViewActionUpdate, (CObject*)&recPerson);

	return TRUE;
}

BOOL CPersonsDoc::Insert(CPerson& oPerson)
{
	CPersonsData oPersonsData;

	if (!oPersonsData.Insert(oPerson))
	{
		return FALSE;
	}

	m_oPersonsArray.Add(new PERSONS(oPerson.GetPerson()));

	UpdateAllViews(NULL, ViewActionInsert, (CObject*)&oPerson);

	return TRUE;
}

BOOL CPersonsDoc::Delete(CPerson& oPerson)
{

	CPersonsData oPersonsData;

	if (!oPersonsData.Delete(oPerson))
	{
		return FALSE;
	}

	m_oPersonsArray.DeleteAt(GetIndexPersonWithID(oPerson.GetPerson().lID));

	UpdateAllViews(NULL, ViewActionDelete, (CObject*)oPerson.GetPerson().lID);

	return TRUE;
}

CPersonsArray& CPersonsDoc::GetPersonsArray()
{
	return m_oPersonsArray;
}

CCitiesArray& CPersonsDoc::GetCitiesArray()
{
	return m_oCitiesArray;
}

CPhoneTypesArray& CPersonsDoc::GetPhoneTypesArray()
{
	return m_oPhoneTypesArray;
}

// Overrides
// ----------------
BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPersonsData oPersonsData;

	if (!oPersonsData.SelectAll(m_oPersonsArray))
	{
		return FALSE;
	}

	CCitiesTable oCitiesTable;
	CPhoneTypesTable oPhoneTypesTable;

	if (!oCitiesTable.SelectAll(m_oCitiesArray))
	{
		return FALSE;
	}

	if (!oPhoneTypesTable.SelectAll(m_oPhoneTypesArray))
	{
		return FALSE;
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CPersonsDoc serialization

void CPersonsDoc::Serialize(CArchive& ar)
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
void CPersonsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CPersonsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPersonsDoc::SetSearchContent(const CString& value)
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

// CPersonsDoc diagnostics

#ifdef _DEBUG
void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPersonsDoc commands
