#include "LicenseSystem.h"
#include <winioctl.h>
#include "stdafx.h"

using namespace std;

CLicense::CLicense()
{
}

CLicense::~CLicense()
{
}
// License system by Obede || Thanks Anderson for Helps
CString CLicense::GetSerial()
{   
	LPCTSTR nDisco = _T("C:\\");
	BOOL bSuccess;
	DWORD dSerialNum;
	string str;
	unsigned int nReturn;
				 
	bSuccess = GetVolumeInformation(nDisco, NULL, NULL, &dSerialNum, NULL, NULL, NULL, NULL);

	if(!bSuccess)
	{
		return "";
	}
	nReturn = dSerialNum;
	str = to_string(nReturn);

	return CString(str.c_str());
}

CString CLicense::EncryptSerial()
{ 
	LPCTSTR nDisco = _T("C:\\");
	
	string str;
	DWORD dSerialNum;
	DWORD dSerialEncr;
	BOOL bSuccess;

	bSuccess = GetVolumeInformation(nDisco, NULL, NULL, &dSerialNum, NULL, NULL, NULL, NULL);

	dSerialEncr = (dSerialNum * 37) / 2;

	str = to_string(dSerialEncr);

	return CString(str.c_str());
}