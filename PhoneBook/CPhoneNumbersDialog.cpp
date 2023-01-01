// CPhoneNumbersDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "CPhoneNumbersDialog.h"
#include "afxdialogex.h"


// CPhoneNumbersDialog dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialogEx)

#define ERROR_EMPTY_CONTROL_BOX "Fields can't be empty.\nPlease fill them in or cancel operation."
#define ERROR_NUMBER "Number must include numeral charactes only."

// Constructors & Destructors
// ----------------------------
CPhoneNumbersDialog::CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, CPhoneTypesArray& oPhoneTypesArray, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_NUMBERS, pParent), m_recPhoneNumber(recPhoneNumber)
{
	m_oPhoneTypesArray = &oPhoneTypesArray;
}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}

// Methods
// ----------------------------
void CPhoneNumbersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBERS_NUMBERS, m_edbPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_NUMBERS_TYPE, m_cmbType);
}

BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialogEx)
END_MESSAGE_MAP()

// CPhoneNumbersDialog message handlers

BOOL CPhoneNumbersDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_edbPhoneNumber.SetLimitText(PHONE_NUMBERS_SIZE);

	m_edbPhoneNumber.SetWindowText(m_recPhoneNumber.szPhoneNumber);

	for (int i = 0; i < (*m_oPhoneTypesArray).GetCount(); i++)
	{
		int nItem = m_cmbType.AddString((*m_oPhoneTypesArray).GetAt(i)->szPhoneType);
		m_cmbType.SetItemData(nItem, (*m_oPhoneTypesArray).GetAt(i)->lID);

		if (m_recPhoneNumber.lPhoneTypeID == (*m_oPhoneTypesArray).GetAt(i)->lID)
			m_cmbType.SetCurSel(nItem);
	}
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPhoneNumbersDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CString strNumber, strType;

	m_edbPhoneNumber.GetWindowText(strNumber);
	m_cmbType.GetWindowText(strType);

	if (CheckIfEmpty(strNumber))
		return;

	if (!IsControlNumeral(strNumber))
		return;

	_tcscpy_s(m_recPhoneNumber.szPhoneNumber, strNumber);

	for (int i = 0; i < (*m_oPhoneTypesArray).GetCount(); i++)
	{
		CString strPhoneT = (*m_oPhoneTypesArray).GetAt(i)->szPhoneType;
		if ((*m_oPhoneTypesArray).GetAt(i)->szPhoneType == strType)
			m_recPhoneNumber.lPhoneTypeID = (*m_oPhoneTypesArray).GetAt(i)->lID;
	}

	CDialogEx::OnOK();
}

BOOL CPhoneNumbersDialog::CheckIfEmpty(CString strNumber)
{
	strNumber.Remove(' ');
	if (strNumber.IsEmpty())
	{
		AfxMessageBox(_T(ERROR_EMPTY_CONTROL_BOX));
		return TRUE;
	}
	return FALSE;
}

BOOL CPhoneNumbersDialog::IsControlNumeral(CString& strNumber)
{
	if (strNumber.SpanIncluding(_T("0123456789")) != strNumber)
	{
		AfxMessageBox(_T(ERROR_NUMBER));
		return FALSE;
	}
	return TRUE;
}