#pragma once
#include "Structures.h"
#include "CPersonsView.h"
#include "CPerson.h"

//////////////////////////////////////////////////////////////
// CPersonsDialog dialog

/// <summary>
/// Клас описващ диалог на таблица PERSONS
/// </summary>
class CPersonsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsDialog)
// Constructor & Destructor
// --------------------------
public:
	CPersonsDialog(CPerson& oPerson, ContextAction eContextAction, CCitiesArray& oCitiesArray, CPhoneTypesArray& oPhoneTypesArray,
		CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PERSONS };
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
	/// Проверява дали подаденият CString съдържа само цифри
	/// </summary>
	/// <param name="strUSN"></param>
	/// <returns> TRUE ако съдаржанието е само от цифри FALSE при наличието на букви </returns>
	BOOL IsControlNumeral(CString& strUSN);
	/// <summary>
	/// Премахва празните пространства от низовете
	/// </summary>
	/// <param name="strFirstName"> Низ който държи съдържанието на m_edbFirstName </param>
	/// <param name="strMiddleName"> Низ който държи съдържанието на m_edbFirstName </param>
	/// <param name="strLastName"> Низ който държи съдържанието на m_edbLastName </param>
	/// <param name="strUSN">  Низ който държи съдържанието на m_edbUSN </param>
	void RemoveWhiteSpaces(CString strFirstName, CString strMiddleName, CString strLastName, CString strUSN);
	/// <summary>
	/// Проверява дали подадените низове са празни
	/// </summary>
	/// <param name="strFirstName"> Низ който държи съдържанието на m_edbFirstName </param>
	/// <param name="strMiddleName"> Низ който държи съдържанието на m_edbFirstName </param>
	/// <param name="strLastName"> Низ който държи съдържанието на m_edbLastName </param>
	/// <param name="strUSN">  Низ който държи съдържанието на m_edbUSN </param>
	/// <param name="strCity">  Низ който държи съдържанието на m_cmbCity </param>
	/// <returns> TRUE ако дори и един низ е празен, FALSE ако всички са пълни </returns>
	BOOL CheckIfEmpty(CString& strFirstName, CString& strMiddleName, CString& strLastName, CString& strUSN, CString& strCity);
	/// <summary>
	/// Запълване на диалога и ListCtrl-а 
	/// </summary>
	/// <param name="pPerson"> Обект от структура PERSONS </param>
	void FillDialog(PERSONS* pPerson);
	/// <summary>
	/// Получаване на позицията и на елемент от ListCtrl-а
	/// </summary>
	/// <param name="pos"> Променлива съхраняваща позицията на елемента </param>
	/// <param name="nItem"> Индекс на елемента в ListCtrl-a </param>
	/// <param name="nIndex"> Индекс на елемента в масив </param>
	void GetSelectedItem(POSITION& pos, int& nItem, int& nIndex);

	afx_msg void OnRButtonClick(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDialogContextUpdate();
	afx_msg void OnDialogContextInsert();
	afx_msg void OnDialogContextDelete();

// Members
// ------------------------
private:
	/// <summary>
	/// За съхранение на подадения обект от клас CPerson
	/// </summary>
	CPerson& m_oPerson;
	/// <summary>
	/// За съхранение на изброим тип ContextAction
	/// </summary>
	ContextAction m_eContextAction;
	/// <summary>
	/// Указател към подаден масив от градове
	/// </summary>
	CCitiesArray* m_oCitiesArray;
	/// <summary>
	/// Указател към подаден масив от телефонни типове
	/// </summary>
	CPhoneTypesArray* m_oPhoneTypesArray;

public:
	/// <summary>
	/// Променлива за EditControl IDC_EDB_PERSONS_FIRST_NAME
	/// </summary>
	CEdit m_edbFirstName;
	/// <summary>
	/// Променлива за EditControl IDC_EDB_PERSONS_MIDDLE_NAME
	/// </summary>
	CEdit m_edbMiddleName;
	/// <summary>
	/// Променлива за EditControl IDC_EDB_PERSONS_LAST_NAME
	/// </summary>
	CEdit m_edbLastName;
	/// <summary>
	/// Променлива за EditControl IDC_EDB_PERSONS_USN
	/// </summary>
	CEdit m_edbUSN;
	/// <summary>
	/// Променлива за ListrCtrl IDC_LSC_PERSONS_PHONE_NUMBERS
	/// </summary>
	CListCtrl m_lcsPhoneNumbers;
	/// <summary>
	/// Променлива за ComboBox IDC_CMB_PERSONS_CITY
	/// </summary>
	CComboBox m_cmbCity;
	

};
