#pragma once
#include "Structures.h"
#include "ActionEnums.h"

// CPhoneTypesDialog dialog

/// <summary>
/// Клас описващ диалог на таблица PHONE_TYPES
/// </summary>
class CPhoneTypesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPhoneTypesDialog)

// Constructor & Destructor
// --------------------------
public:
	CPhoneTypesDialog(PHONE_TYPES& recPhoneType, ContextAction eContextAction, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneTypesDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PHONE_TYPES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// Methods
// ----------------------
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	/// <summary>
	/// Проверява дали подадените низове са празни
	/// </summary>
	/// <param name="strPhoneType"></param>
	/// <returns> TRUE ако дори и един низ е празен, FALSE ако всички са пълни </returns>
	BOOL CheckIfEmpty(CString strPhoneType);

// Members
// ------------------------
private:
	/// <summary>
	/// За съхранение на подадения обект от тип PHONE_TYPES
	/// </summary>
	PHONE_TYPES& m_recPhoneType;
	/// <summary>
	/// За съхранение на изброим тип ContextAction
	/// </summary>
	ContextAction m_eContextAction;
public:
	/// <summary>
	/// Променлива за EditControl IDC_EDB_CITIES_NAME
	/// </summary>
	CEdit m_edbPhoneType;
	
};
