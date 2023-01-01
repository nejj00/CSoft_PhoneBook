// CPersonsDialog.cpp : implementation file
//
#include "pch.h"
#include "PhoneBook.h"
#include "CPersonsDialog.h"
#include "CPhoneNumbersDialog.h"
#include "afxdialogex.h"

#define COLUMN_0 0
#define COLUMN_1 1

#define COLUMN_WIDTH 200

#define ERROR_EMPTY_CONTROL_BOX "Fields can't be empty.\nPlease fill them in or cancel operation."
#define ERROR_USN "USN must include numerals only."

// CPersonsDialog dialog

IMPLEMENT_DYNAMIC(CPersonsDialog, CDialogEx)

// Constructors & Destructors
// ---------------------------
CPersonsDialog::CPersonsDialog(CPerson& oPerson, ContextAction eContextAction, CCitiesArray& oCitiesArray, CPhoneTypesArray& oPhoneTypesArray,
	CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PERSONS, pParent), m_oPerson(oPerson), m_eContextAction(eContextAction)
{
	m_oCitiesArray = &oCitiesArray;
	m_oPhoneTypesArray = &oPhoneTypesArray;
}

CPersonsDialog::~CPersonsDialog()
{
}

// Methods
// ------------------------
void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PERSONS_FIRST_NAME, m_edbFirstName);
	DDX_Control(pDX, IDC_EDB_PERSONS_MIDDLE_NAME, m_edbMiddleName);
	DDX_Control(pDX, IDC_EDB_PERSONS_LAST_NAME, m_edbLastName);
	DDX_Control(pDX, IDC_EDB_PERSONS_USN, m_edbUSN);
	DDX_Control(pDX, IDC_LCS_PERSONS_PHONE_NUMBERS, m_lcsPhoneNumbers);
	DDX_Control(pDX, IDC_CMB_PERSONS_CITY, m_cmbCity);
}

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LCS_PERSONS_PHONE_NUMBERS, OnRButtonClick)
	ON_COMMAND(ID_CITIES_UPDATE, &CPersonsDialog::OnDialogContextUpdate)
	ON_COMMAND(ID_CITIES_INSERT, &CPersonsDialog::OnDialogContextInsert)
	ON_COMMAND(ID_CITIES_DELETE, &CPersonsDialog::OnDialogContextDelete)

END_MESSAGE_MAP()

// CPersonsDialog message handlers

void CPersonsDialog::FillDialog(PERSONS* pPerson)
{
	m_edbFirstName.SetLimitText(PERSONS_SIZE);
	m_edbMiddleName.SetLimitText(PERSONS_SIZE);
	m_edbLastName.SetLimitText(PERSONS_SIZE);
	m_edbUSN.SetLimitText(PERSONS_SIZE);

	m_edbFirstName.SetWindowText(pPerson->szFirstName);
	m_edbMiddleName.SetWindowText(pPerson->szMiddleName);
	m_edbLastName.SetWindowText(pPerson->szLastName);
	m_edbUSN.SetWindowText(pPerson->szUSN);

	for (int i = 0; i < m_oCitiesArray->GetCount(); i++)
	{
		int nItem = m_cmbCity.AddString(m_oCitiesArray->GetAt(i)->szCityName);
		m_cmbCity.SetItemData(nItem, m_oCitiesArray->GetAt(i)->lID);

		if (pPerson->lCityID == m_oCitiesArray->GetAt(i)->lID)
			m_cmbCity.SetCurSel(nItem);
	}

	if (m_eContextAction == ContextActionSelect)
	{
		m_edbFirstName.EnableWindow(FALSE);
		m_edbMiddleName.EnableWindow(FALSE);
		m_edbLastName.EnableWindow(FALSE);
		m_edbUSN.EnableWindow(FALSE);
		m_lcsPhoneNumbers.EnableWindow(FALSE);
		m_cmbCity.EnableWindow(FALSE);
	}
}

BOOL CPersonsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	PERSONS* pPerson = &m_oPerson.GetPerson();

	FillDialog(pPerson);

	m_lcsPhoneNumbers.InsertColumn(COLUMN_0, _T("Phone Number"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	m_lcsPhoneNumbers.InsertColumn(COLUMN_1, _T("Type"), LVCFMT_LEFT, COLUMN_WIDTH, -1);
	
	for (int i = 0; i < m_oPerson.GetPhoneNumbers().GetCount(); i++)
	{
		CString strNumber = m_oPerson.GetPhoneNumbers().GetAt(i)->szPhoneNumber;
		int nIndex = m_lcsPhoneNumbers.InsertItem(i, strNumber);

		for (int j = 0; j < m_oPhoneTypesArray->GetCount(); j++)
		{
			if (m_oPhoneTypesArray->GetAt(j)->lID == m_oPerson.GetPhoneNumbers().GetAt(i)->lPhoneTypeID)
				m_lcsPhoneNumbers.SetItemText(nIndex, 1, m_oPhoneTypesArray->GetAt(j)->szPhoneType);
		}
	}

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPersonsDialog::OnOK()
{
	CString strFirstName, strMiddleName, strLastName, strUSN, strCity;

	PERSONS* pPerson = &m_oPerson.GetPerson();

	m_edbFirstName.GetWindowText(strFirstName);
	m_edbMiddleName.GetWindowText(strMiddleName);
	m_edbLastName.GetWindowText(strLastName);
	m_edbUSN.GetWindowText(strUSN);
	m_cmbCity.GetWindowText(strCity);
	long lID = m_cmbCity.GetItemData(m_cmbCity.GetCurSel());


	if (CheckIfEmpty(strFirstName, strMiddleName, strLastName, strUSN, strCity))
		return;

	if (!IsControlNumeral(strUSN))
		return;

	_tcscpy_s(pPerson->szFirstName, strFirstName);
	_tcscpy_s(pPerson->szMiddleName, strMiddleName);
	_tcscpy_s(pPerson->szLastName, strLastName);
	_tcscpy_s(pPerson->szUSN, strUSN);

	for (int i = 0; i < m_oCitiesArray->GetCount(); i++)
	{
		if (m_oCitiesArray->GetAt(i)->lID == lID)
			pPerson->lCityID = m_oCitiesArray->GetAt(i)->lID;
	}

	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}

BOOL CPersonsDialog::IsControlNumeral(CString& strUSN)
{
	if (strUSN.SpanIncluding(_T("0123456789")) != strUSN)
	{
		AfxMessageBox(_T(ERROR_USN));
		return FALSE;
	}
	return TRUE;
}

void CPersonsDialog::RemoveWhiteSpaces(CString strFirstName, CString strMiddleName, CString strLastName, CString strUSN)
{
	strFirstName.Remove(' ');
	strMiddleName.Remove(' ');
	strLastName.Remove(' ');
	strUSN.Remove(' ');
}

BOOL CPersonsDialog::CheckIfEmpty(CString& strFirstName, CString& strMiddleName, CString& strLastName, CString& strUSN, CString& strCity)
{
	RemoveWhiteSpaces(strFirstName, strMiddleName, strLastName, strUSN);

	if (strFirstName.IsEmpty() || strMiddleName.IsEmpty() || strLastName.IsEmpty() || strUSN.IsEmpty() || strCity.IsEmpty())
	{
		AfxMessageBox(_T(ERROR_EMPTY_CONTROL_BOX));

		if (strFirstName.IsEmpty())
			m_edbFirstName.SetFocus();
		else if (strMiddleName.IsEmpty())
			m_edbMiddleName.SetFocus();
		else if (strLastName.IsEmpty())
			m_edbLastName.SetFocus();
		else if (strUSN.IsEmpty())
			m_edbUSN.SetFocus();

		return TRUE;
	}

	return FALSE;
}

void CPersonsDialog::OnRButtonClick(NMHDR* pNotifyStruct, LRESULT* result)
{
	CMenu oMenu;
	oMenu.LoadMenu(IDR_POPUP_CITIES);
	CMenu* pMenu = oMenu.GetSubMenu(0);

	CPoint point;
	point.x = GetCurrentMessage()->pt.x;
	point.y = GetCurrentMessage()->pt.y;

	POSITION pos = m_lcsPhoneNumbers.GetFirstSelectedItemPosition();
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

void CPersonsDialog::GetSelectedItem(POSITION& pos, int& nItem, int& nIndex)
{
	pos = m_lcsPhoneNumbers.GetFirstSelectedItemPosition();
	nItem = m_lcsPhoneNumbers.GetNextSelectedItem(pos);
	nIndex = nItem;
}

void CPersonsDialog::OnDialogContextUpdate()
{
	PHONE_NUMBERS recPhoneNumber;
	POSITION pos;
	int nItem, nIndex;

	GetSelectedItem(pos, nItem, nIndex);

	recPhoneNumber = *m_oPerson.GetPhoneNumbers().GetAt(nIndex);

	CPhoneNumbersDialog oPhoneNumbersDialog(recPhoneNumber, *m_oPhoneTypesArray);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
		return;

	m_lcsPhoneNumbers.SetItemText(nItem, COLUMN_0, recPhoneNumber.szPhoneNumber);

	for (int j = 0; j < m_oCitiesArray->GetCount(); j++)
	{
		if (m_oCitiesArray->GetAt(j)->lID == recPhoneNumber.lPhoneTypeID)
			m_lcsPhoneNumbers.SetItemText(nIndex, 1, m_oPhoneTypesArray->GetAt(j)->szPhoneType);
	}

	*m_oPerson.GetPhoneNumbers().GetAt(nIndex) = recPhoneNumber;
}

void CPersonsDialog::OnDialogContextInsert()
{
	PHONE_NUMBERS recPhoneNumber;

	CPhoneNumbersDialog oPhoneNumbersDialog(recPhoneNumber, *m_oPhoneTypesArray);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
		return;

	int nItem = m_lcsPhoneNumbers.InsertItem(m_lcsPhoneNumbers.GetItemCount(), recPhoneNumber.szPhoneNumber);

	for (int j = 0; j < m_oPhoneTypesArray->GetCount(); j++)
	{
		if (m_oPhoneTypesArray->GetAt(j)->lID == recPhoneNumber.lPhoneTypeID)
			m_lcsPhoneNumbers.SetItemText(nItem, 1, m_oPhoneTypesArray->GetAt(j)->szPhoneType);
	}

	m_oPerson.GetPhoneNumbers().Add(new PHONE_NUMBERS(recPhoneNumber));
}

void CPersonsDialog::OnDialogContextDelete()
{
	POSITION pos;
	int nItem, nIndex;

	GetSelectedItem(pos, nItem, nIndex);

	m_oPerson.GetPhoneNumbers().DeleteAt(nIndex);
	m_lcsPhoneNumbers.DeleteItem(nItem);
}

