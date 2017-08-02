#include <atlstr.h.>

#pragma once

class CLicense
{
public:
	CLicense();
	~CLicense();
	CString GetSerial();
	CString EncryptSerial();

private:

};

extern CLicense * g_pLicense;
