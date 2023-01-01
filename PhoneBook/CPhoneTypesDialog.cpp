// CPhoneTypesDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "CPhoneTypesDialog.h"
#include "afxdialogex.h"

// CPhoneTypesDialog dialog

#define ERROR_EMPTY_CONTROL_BOX "Fields can't be empty.\nPlease fill them in or cancel operation."

IMPLEMENT_DYNAMIC(CPhoneTypesDialog, CDialogEx)

CPhoneTypesDialog::CPhoneTypesDialog(PHONE_TYPES& recPhoneType, ContextAction eContextAction, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_TYPES, pParent), m_recPhoneType(recPhoneType), m_eContextAction(eContextAction)
{
}

CPhoneTypesDialog::~CPhoneTypesDialog()
{
}

void CPhoneTypesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_TYPES_TYPE, m_edbPhoneType);
}

BEGIN_MESSAGE_MAP(CPhoneTypesDialog, CDialogEx)
END_MESSAGE_MAP()

// CPhoneTypesDialog message handlers

BOOL CPhoneTypesDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_edbPhoneType.SetLimitText(PHONE_TYPES_SIZE);
	
	m_edbPhoneType.SetWindowText(m_recPhoneType.szPhoneType);

	if (m_eContextAction == ContextActionSelect)
	{
		m_edbPhoneType.EnableWindow(FALSE);
	}

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPhoneTypesDialog::OnOK()
{
	CString strPhoneType;

	m_edbPhoneType.GetWindowText(strPhoneType);

	if (CheckIfEmpty(strPhoneType))
		return;

	_tcscpy_s(m_recPhoneType.szPhoneType, strPhoneType);

	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}

BOOL CPhoneTypesDialog::CheckIfEmpty(CString strPhoneType)
{
	strPhoneType.Remove(' ');

	if (strPhoneType.IsEmpty())
	{
		AfxMessageBox(_T(ERROR_EMPTY_CONTROL_BOX));
		return TRUE;
	}
	return FALSE;
}
