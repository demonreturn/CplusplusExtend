
#ifndef _CCS_FILE_FACTORY_H_
#define _CCS_FILE_FACTORY_H_

#include "CCSBase.h"

class ICCSFileImpl;

class CCSFileImplFactory
{
public:
	int CreateFileImpl(
		DWORD dwType,
		ICCSFileImpl*& pFile );
};

#endif	// _CCS_FILE_FACTORY_H_
