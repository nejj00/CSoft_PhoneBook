#pragma once
#include "Structures.h"
#include "CCititesView.h"

/////////////////////////////////////////////////////////////////////////////
// CCitiesDialog dialog

class CCitiesDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesDialog)
// Constructor / Destructor
// ----------------
public:
	CCitiesDialog(CITIES& recCity, ContextAction eContextAction, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesDialog();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CITIES };
#endif


// Methods
// ----------------
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// Overrides
// ----------------
public:
	virtual BOOL OnInitDialog()override;
	virtual void OnOK()override;

	/// <summary>
	/// Проверява дали подадените низове са празни
	/// </summary>
	/// <param name="strName"></param>
	/// <param name="strRegion"></param>
	/// <returns> TRUE ако дори и един низ е празен, FALSE ако всички са пълни </returns>
	BOOL CheckIfEmpty(CString strName, CString strRegion);

// Members
// ----------------
private:
	/// <summary>
	/// За съхранение на обект от структура CITIES
	/// </summary>
	CITIES& m_recCity;
	/// <summary>
	/// За съхранение на изброим тип ContextAction
	/// </summary>
	ContextAction m_eContextAction;

public:
	/// <summary>
	/// Променлива за EditControl IDC_EDB_CITIES_NAME
	/// </summary>
	CEdit m_edbName;
	/// <summary>
	/// Променлива за EditControl IDC_EDB_CITIES_REGION
	/// </summary>
	CEdit m_edbRegion;

};
