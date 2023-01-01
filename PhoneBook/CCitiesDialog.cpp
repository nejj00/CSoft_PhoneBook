// CCitiesDialog.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "CCitiesDialog.h"
#include "afxdialogex.h"

///////////////////////////////////////////////////////////////////////////
// CCitiesDialog

#define ERROR_EMPTY_CONTROL_BOX "Fields can't be empty.\nPlease fill them in or cancel operation."

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialogEx)

CCitiesDialog::CCitiesDialog(CITIES& recCity, ContextAction eContextAction, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CITIES, pParent), m_recCity(recCity), m_eContextAction(eContextAction)
{
}

CCitiesDialog::~CCitiesDialog()
{
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_edbName);
	DDX_Control(pDX, IDC_EDB_CITIES_REGION, m_edbRegion);
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialogEx)
END_MESSAGE_MAP()

// CCitiesDialog message handlers

BOOL CCitiesDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_edbName.SetLimitText(CITIES_SIZE);
	m_edbRegion.SetLimitText(CITIES_SIZE);

	m_edbName.SetWindowText(m_recCity.szCityName);
	m_edbRegion.SetWindowText(m_recCity.szArea);

	if (m_eContextAction == ContextActionSelect)
	{
		m_edbName.EnableWindow(FALSE);
		m_edbRegion.EnableWindow(FALSE);
	}

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CCitiesDialog::OnOK()
{
	CString strName, strRegion;

	m_edbName.GetWindowText(strName);
	m_edbRegion.GetWindowText(strRegion);

	if (CheckIfEmpty(strName, strRegion))
		return;

	_tcscpy_s(m_recCity.szCityName, strName);
	_tcscpy_s(m_recCity.szArea, strRegion);

	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}

BOOL CCitiesDialog::CheckIfEmpty(CString strName, CString strRegion)
{
	strName.Remove(' ');
	strRegion.Remove(' ');

	if (strName.IsEmpty() || strRegion.IsEmpty())
	{
		AfxMessageBox(_T(ERROR_EMPTY_CONTROL_BOX));
		return TRUE;
	}
	return FALSE;
}
