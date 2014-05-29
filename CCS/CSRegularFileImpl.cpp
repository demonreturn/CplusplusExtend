#include "CSRegularFileImpl.h"
#include "CCSOSMemory.h"
#include "CCSFile.h"

CCSRegularFileImpl::CCSRegularFileImpl()
	: m_dwFlags( 0 )
	, m_dwMode( CCS_DEFAULT_FILE_MODE )
	, m_fileHandle( CCS_INVALID_HANDLE )
{
	CCS_OS::OSMemset( m_fileName, 0, sizeof(m_fileName) );
}

CCSRegularFileImpl::CCSRegularFileImpl( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode /*= CCS_DEFAULT_FILE_MODE */ )
	: m_dwFlags( dwFlags )
	, m_dwMode( dwMode )
	, m_fileHandle( CCS_INVALID_HANDLE )
{
	CCS_OS::OSMemset( m_fileName, 0, sizeof(m_fileName) );

	CCS_OS::OSMemcpy( m_fileName,
		sizeof( m_fileName),
		pFileName,
		CCS_OS::OSStrlen( pFileName, MAX_FILENAMELEN ) );
}

CCSRegularFileImpl::~CCSRegularFileImpl()
{
	if ( CCS_INVALID_HANDLE != m_fileHandle )
	{
		Close();
	}
}

HANDLE CCSRegularFileImpl::Open()
{
	return this->Open(
		m_fileName,
		m_dwFlags,
		m_dwMode );
}

HANDLE CCSRegularFileImpl::Open( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode )
{
	if ( NULL == pFileName )
	{
		return CCS_INVALID_HANDLE;
	}

	CCS_OS::OSMemcpy( m_fileName,
		sizeof( m_fileName),
		pFileName,
		CCS_OS::OSStrlen( pFileName, MAX_FILENAMELEN ) );

	m_fileHandle = CCS_OS::OpenFile(
		pFileName,
		dwFlags,
		dwMode );

	return m_fileHandle;
}

int CCSRegularFileImpl::Close()
{
	if ( CCS_INVALID_HANDLE == m_fileHandle)
	{
		return CCS_ERROR_FAILURE;
	}

	int iRet = CCS_OS::CloseFile( m_fileHandle );
}

int CCSRegularFileImpl::Read( 
	char* pBuffer,
	DWORD dwReadLen,
	DWORD& dwActualRead )
{
	if ( CCS_INVALID_HANDLE != m_fileHandle )
	{
		return CCS_ERROR_FAILURE;
	}

	int iRet = CCS_OS::ReadFile(
		m_fileHandle,
		pBuffer,
		dwReadLen,
		&dwActualRead );

	return (0 == iRet) ? CCS_OK : CCS_ERROR_FAILURE;
}

int CCSRegularFileImpl::Write( 
	const char* pBuffer,
	DWORD dwWriteLen,
	DWORD& dwActualWrite )
{
	if ( NULL == pBuffer || CCS_INVALID_HANDLE == m_fileHandle )
	{
		return CCS_ERROR_FAILURE;
	}

	int iRet = CCS_OS::WriteFile(
		m_fileHandle,
		(const LPVOID)pBuffer,
		dwWriteLen,
		&dwActualWrite );

	return ( 0 == iRet ) ? CCS_OK : CCS_ERROR_FAILURE;
}

int CCSRegularFileImpl::Seek( 
	CCS_OFFSET lDistance,
	DWORD dwMoveMethod )
{
	if ( CCS_INVALID_HANDLE == m_fileHandle )
	{
		return CCS_ERROR_FAILURE;
	}

	int iRet = CCS_OS::SeekFile(
		m_fileHandle,
		lDistance,
		dwMoveMethod );

	return ( 0 == iRet ) ? CCS_OK : CCS_ERROR_FAILURE;
}

int CCSRegularFileImpl::Flush()
{
	if ( CCS_INVALID_HANDLE == m_fileHandle )
	{
		return CCS_ERROR_FAILURE;
	}

	int iRet = CCS_OS::FlushFile( m_fileHandle );

	return ( 0 == iRet ) ? CCS_OK : CCS_ERROR_FAILURE;
}

HANDLE CCSRegularFileImpl::GetFileHandle()
{
	return m_fileHandle;
}

int CCSRegularFileImpl::SetFileSize( LONGLONG llFileSize )
{
	if ( NULL == m_fileHandle ||
		0 >= llFileSize )
	{
		return CCS_ERROR_FAILURE;
	}

	CCS_OFFSET curOff = CCS_OS::GetFilePosition( m_fileHandle );
	LONGLONG llCurSize = GetFileSize();

	if ( llCurSize == llFileSize )
	{
		return CCS_OK;
	}

	int iRet = CCS_OS::TruncateFile(
		m_fileHandle,
		llFileSize );

	if ( 0 != iRet )
	{
		return CCS_ERROR_FAILURE;
	}

	if ( curOff < llFileSize )
	{
		CCS_OS::SeekFile( m_fileHandle,
			curOff,
			CCS_SEEK_BEGIN );
	}

	return CCS_OK;
}

LONGLONG CCSRegularFileImpl::GetFileSize()
{
	int iRet = CCS_OS::GetFileAddribute(
		m_fileName,
		m_fileAttribute );

	return ( 0 == iRet ) ? m_fileAttribute.llFlesize : -1;
}

LONGLONG CCSRegularFileImpl::GetCreateTime()
{
	int iRet = CCS_OS::GetFileAddribute(
		m_fileName,
		m_fileAttribute );

	return ( 0 == iRet ) ? m_fileAttribute.llCreateTime : -1;
}

LONGLONG CCSRegularFileImpl::GetModifyTime()
{
	int iRet = CCS_OS::GetFileAddribute(
		m_fileName,
		m_fileAttribute );

	return ( 0 == iRet ) ? m_fileAttribute.llModifyTime : -1;
}

int CCSRegularFileImpl::SetFileName( const char* pFileName )
{
	CCS_OS::OSMemcpy( m_fileName,
		sizeof( m_fileName),
		pFileName,
		CCS_OS::OSStrlen( pFileName, MAX_FILENAMELEN ) );

	return CCS_OK;
}
