
#ifndef _CCS_REGULAR_FILEIMPL_H_
#define _CCS_REGULAR_FILEIMPL_H_

#include "CCSBase.h"
#include "CCSFileImpl.h"

class CCSRegularFileImpl
	: public ICCSFileImpl
{
public:
	CCSRegularFileImpl();

	CCSRegularFileImpl(
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode = CCS_DEFAULT_FILE_MODE );

	virtual ~CCSRegularFileImpl();

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

	virtual int SetFileName( const char* pFileName );

	virtual void SetFlags( DWORD dwFlags )
	{
		m_dwFlags = dwFlags;
	}

	virtual void SetAccessMode( DWORD dwMode )
	{
		m_dwMode = dwMode;
	}

private:
	CCSRegularFileImpl( const CCSRegularFileImpl& );

	CCSRegularFileImpl& operator = ( const CCSRegularFileImpl& );

	char						m_fileName[MAX_FILENAMELEN];	/*ÎÄ¼þÃû*/
	HANDLE						m_fileHandle;
	DWORD						m_dwFlags;
	DWORD						m_dwMode;
	FileAttribute				m_fileAttribute;
};

#endif	// _CCS_REGULAR_FILEIMPL_H_
