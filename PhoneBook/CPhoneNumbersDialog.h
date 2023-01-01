#pragma once
#include "Structures.h"


// CPhoneNumbersDialog dialog

/// <summary>
/// Клас описващ диалога на телефонните номера
/// </summary>
class CPhoneNumbersDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

// Constructor / Destructor
// ----------------------------
public:
	CPhoneNumbersDialog(PHONE_NUMBERS& recPhoneNumber, CPhoneTypesArray& oPhoneTypesArray, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PHONE_NUMBERS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
// Methods
// -----------------------------
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	/// <summary>
	/// Проверява дали подадения низ е празен
	/// </summary>
	/// <param name="strNumber"></param>
	/// <returns> TRUE ако низът е празен, FALSE ако е пълен </returns>
	BOOL CheckIfEmpty(CString strNumber);
	/// <summary>
	/// Проверява дали подаденият CString съдържа само цифри
	/// </summary>
	/// <param name="strNumber"></param>
	/// <returns> TRUE ако съдаржанието е само от цифри FALSE при наличието на букви </returns>
	BOOL IsControlNumeral(CString& strNumber);
// Members
// -----------------------------
private:
	/// <summary>
	/// За съхранение на подадения обект от тип PHONE_NUMBERS
	/// </summary>
	PHONE_NUMBERS& m_recPhoneNumber;
	/// <summary>
	/// Указател към подаден масив от телефонни типове
	/// </summary>
	CPhoneTypesArray* m_oPhoneTypesArray;

public:
	/// <summary>
	/// Променлива за EditControl IDC_EDB_PHONE_NUMBERS_NUMBER
	/// </summary>
	CEdit m_edbPhoneNumber;
	/// <summary>
	/// Променлива за ComboBox IDC_CMB_PHONE_NUMBERS_TYPE
	/// </summary>
	CComboBox m_cmbType;
};
