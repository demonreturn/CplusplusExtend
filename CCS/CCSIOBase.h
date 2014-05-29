

#ifndef _CCS_IOBASE_H_
#define _CCS_IOBASE_H_

#include "CCSBase.h"

class ICCSIOBase
{
public:
	virtual ~ICCSIOBase(){}

	virtual HANDLE Open() = 0;

	virtual HANDLE Open( 
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode ) = 0;

	virtual int Close() = 0;

	virtual int Read(
		char* pBuffer,
		DWORD dwReadLen,
		DWORD& dwActualRead ) = 0;

	virtual int Write(
		const char* pBuffer,
		DWORD dwWriteLen,
		DWORD& dwActualWrite ) = 0;
};

#endif	// _CCS_IOBASE_H_