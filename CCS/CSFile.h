
#ifndef _CCS_FILE_H_
#define _CCS_FILE_H_

#include "CCSBase.h"
#include "CCSIOBase.h"
#include "CCSFileImpl.h"
#include "CCSFileTypes.h"

class CCSFile 
	: public ICCSIOBase
{
public:
	CCSFile( DWORD dwType = FILE_TYPES_REGULAR_FILE );

	/*
	* pFileName	:[IN] 需要打开或创建的文件全路径名称
	* nFlags	:[IN] 三个读写标志 O_RDONLY, O_WRONLY or O_RDWR | 打开标志 O_CREAT O_TRUNC   O_APPEND
	* nMode		:[IN] 文件操作权限, 默认SC_DEFAULT_FILE_MODE
	*/
	CCSFile( const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode = CCS_DEFAULT_FILE_MODE,
		DWORD dwType = FILE_TYPES_REGULAR_FILE );

	virtual ~CCSFile();

	virtual HANDLE Open();

	virtual HANDLE Open( 
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode );

	virtual int Close();

	virtual int Read(
		char* pBuffer,
		DWORD dwReadLen,
		DWORD& dwActualRead );

	virtual int Write(
		const char* pBuffer,
		DWORD dwWriteLen,
		DWORD& dwActualWrite );

	virtual int Seek(
		CCS_OFFSET lDistance,
		DWORD dwMoveMethod );

	virtual int Flush();

	virtual HANDLE GetFileHandle();

	virtual int SetFileSize( LONGLONG llFileSize );

	virtual LONGLONG GetFileSize();

	virtual LONGLONG GetCreateTime();

	virtual LONGLONG GetModifyTime();

private:
	CCSFile( const CCSFile&);
	CCSFile& operator=( const CCSFile& );

	DWORD						m_fileType;
	ICCSFileImpl*				m_pFileImpl;
};

#endif	// _CCS_FILE_H_
