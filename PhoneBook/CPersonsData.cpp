#include "pch.h"
#include "CPersonsData.h"

/////////////////////////////////////////////////////////////////////////////
// CPersonsData

#define ERROR_TRANSACTION "Transaction Failed";

// Methods
// ----------------
BOOL CPersonsData::SelectAll(CPersonsArray& oPersonsArray)
{
	CPersonsTable oPersonsTable(m_oSession);
	return oPersonsTable.SelectAll(oPersonsArray);
}

BOOL CPersonsData::SelectWhereID(const long lID, CPerson& oPerson)
{
	CPhoneNumbersTable oPhoneNumbersTable;
	CPersonsTable oPersonsTable(m_oSession);

	if (!oPhoneNumbersTable.SelectRowsWithForeignKey(_T("PERSON_ID"), oPerson.GetPhoneNumbers(), lID))
		return FALSE;

	if (!oPersonsTable.SelectWhereID(lID, oPerson.GetPerson()))
		return FALSE;

	return TRUE;
}

void CPersonsData::SessionAbortClose()
{
	m_oSession.Abort();
	m_oSession.Close();
}

BOOL CPersonsData::UpdateWhereID(const long lID, CPerson& oPerson)
{
	HRESULT hResult;
	CDBConnection& oDBConnection = CDBConnection::getInstance();
	CDBMethods oDBMethods;

	CPhoneNumbersTable oPhoneNumbersTable(m_oSession);
	CPersonsTable oPersonsTable(m_oSession);

	if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), m_oSession))
		return FALSE;

	hResult = m_oSession.StartTransaction();

	if (FAILED(hResult))
	{
		return FALSE;
	}

	if (!InsertPhoneNumber(oPerson, oPhoneNumbersTable))
	{
		SessionAbortClose();
		return FALSE;
	}
	
	if (!UpdateDeletePhoneNumber(oPerson, oPhoneNumbersTable))
	{
		SessionAbortClose();
		return FALSE;
	}

	if (!oPersonsTable.UpdateWhereID(lID, oPerson.GetPerson()))
	{
		SessionAbortClose();
		return FALSE;
	}

	m_oSession.Commit();
	m_oSession.Close();

	return TRUE;
}

BOOL CPersonsData::InsertPhoneNumber(CPerson& oPerson, CPhoneNumbersTable& oPhoneNumbersTable)
{
	PHONE_NUMBERS* pPhoneNumber;

	for (int i = 0; i < oPerson.GetPhoneNumbers().GetCount(); i++)
	{
		pPhoneNumber = oPerson.GetPhoneNumbers().GetAt(i);

		if (pPhoneNumber->lID == 0)
		{
			pPhoneNumber->lPersonID = oPerson.GetPerson().lID;
			if (!oPhoneNumbersTable.Insert(*pPhoneNumber))
				return FALSE;
		}
	}
	return TRUE;
}

BOOL CPersonsData::UpdateDeletePhoneNumber(CPerson& oPerson, CPhoneNumbersTable& oPhoneNumbersTable)
{
	CPhoneNumbersArray oPhoneNumbersArray;
	if (!oPhoneNumbersTable.SelectRowsWithForeignKey(_T("PERSON_ID"), oPhoneNumbersArray, oPerson.GetPerson().lID))
		return FALSE;

	BOOL bIsInArray;
	PHONE_NUMBERS* pPhoneNumber;
	PHONE_NUMBERS recPhoneNumDB;

	for (int i = 0; i < oPhoneNumbersArray.GetCount(); i++)
	{
		bIsInArray = FALSE;

		recPhoneNumDB = *oPhoneNumbersArray.GetAt(i);
		for (int j = 0; j < oPerson.GetPhoneNumbers().GetCount(); j++)
		{
			pPhoneNumber = oPerson.GetPhoneNumbers().GetAt(j);

			if (pPhoneNumber->lID == 0)
				continue;

			if (recPhoneNumDB.lID == pPhoneNumber->lID)
			{
				if (!oPhoneNumbersTable.UpdateWhereID(pPhoneNumber->lID, *pPhoneNumber))
					return FALSE;

				bIsInArray = TRUE;
				break;
			}
		}

		if (bIsInArray)
			continue;

		if (!oPhoneNumbersTable.DeleteWhereID(recPhoneNumDB.lID))
			return FALSE;
	}

	return TRUE;
}

BOOL CPersonsData::Insert(CPerson& oPerson)
{
	HRESULT hResult;
	CDBConnection& oDBConnection = CDBConnection::getInstance();
	CDBMethods oDBMethods;

	CPhoneNumbersTable oPhoneNumbersTable(m_oSession);
	CPersonsTable oPersonsTable(m_oSession);

	if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), m_oSession))
		return FALSE;

	hResult = m_oSession.StartTransaction();

	if (FAILED(hResult))
	{
		return FALSE;
	}

	if (!oPersonsTable.Insert(oPerson.GetPerson()))
	{
		SessionAbortClose();
		return FALSE;
	}

	PHONE_NUMBERS recPhoneNum;
	CString strNum;

	for (int i = 0; i < oPerson.GetPhoneNumbers().GetCount(); i++)
	{
		recPhoneNum = *oPerson.GetPhoneNumbers().GetAt(i);
		recPhoneNum.lPersonID = oPerson.GetPerson().lID;

		if (!oPhoneNumbersTable.Insert(recPhoneNum))
		{
			SessionAbortClose();
			return FALSE;
		}
	}

	m_oSession.Commit();
	m_oSession.Close();

	return TRUE;
}

BOOL CPersonsData::Delete(CPerson& oPerson)
{
	HRESULT hResult;
	CDBConnection& oDBConnection = CDBConnection::getInstance();
	CDBMethods oDBMethods;

	CPhoneNumbersTable oPhoneNumbersTable(m_oSession);
	CPersonsTable oPersonsTable(m_oSession);

	if (!oDBMethods.OpenSession(hResult, oDBConnection.GetDataSource(), m_oSession))
		return FALSE;

	hResult = m_oSession.StartTransaction();

	if (FAILED(hResult))
	{
		return FALSE;
	}

	PHONE_NUMBERS recPhoneNum;

	for (int i = 0; i < oPerson.GetPhoneNumbers().GetCount(); i++)
	{
		recPhoneNum = *oPerson.GetPhoneNumbers().GetAt(i);

		if (!oPhoneNumbersTable.DeleteWhereID(recPhoneNum.lID))
		{
			SessionAbortClose();
			return FALSE;
		}
	}

	if (!oPersonsTable.DeleteWhereID(oPerson.GetPerson().lID))
	{
		SessionAbortClose();
		return FALSE;
	}

	m_oSession.Commit();
	m_oSession.Close();

	return TRUE;
}
