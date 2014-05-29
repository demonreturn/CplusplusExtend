

#ifndef _CCS_FILEIMPL_H_
#define _CCS_FILEIMPL_H_

#include "CCSBase.h"

class ICCSFileImpl
{
public: 
	virtual ~ICCSFileImpl(){}

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

	virtual int Seek(
		CCS_OFFSET lDistance,
		DWORD dwMoveMethod ) = 0;

	virtual int Flush() = 0;

	virtual HANDLE GetFileHandle() = 0;

	virtual int SetFileSize( LONGLONG llFileSize ) = 0;

	virtual LONGLONG GetFileSize() = 0;

	virtual LONGLONG GetCreateTime() = 0;

	virtual LONGLONG GetModifyTime() = 0;
};

#endif	//_CCS_FILEIMPL_H_