#include "CSFile.h"

#include "CSFileImplFactory.h"
#include "CSRegularFileImpl.h"
#include <assert.h>

CCSFile::CCSFile( DWORD dwType /*= FILE_TYPES_REGULAR_FILE */ )
	: m_fileType( dwType )
	, m_pFileImpl( NULL )
{
	CCSFileImplFactory fileFactory;

	int iRet = fileFactory.CreateFileImpl( m_fileType, m_pFileImpl );

	assert( iRet == CCS_OK );
}

CCSFile::CCSFile( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode /*= CCS_DEFAULT_FILE_MODE*/,
	DWORD dwType /*= FILE_TYPES_REGULAR_FILE */ )
	: m_fileType( dwType )
	, m_pFileImpl( NULL )
{
	CCSFileImplFactory fileFactory;

	int iRet = fileFactory.CreateFileImpl( m_fileType, m_pFileImpl );
	assert( iRet == CCS_OK );

	if ( CCS_OK == iRet )
	{
		iRet = m_pFileImpl->SetFileName( pFileName );
		assert( iRet == CCS_OK );

		m_pFileImpl->SetFlags( dwFlags );
		m_pFileImpl->SetAccessMode( dwMode );
	}
}

CCSFile::~CCSFile()
{
	CCS_DELETE( m_pFileImpl );
}

HANDLE CCSFile::Open()
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_INVALID_HANDLE;
	}

	return m_pFileImpl->Open();
}

HANDLE CCSFile::Open( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode )
{
	if ( NULL == m_pFileImpl ||
		NULL == pFileName )
	{
		return CCS_INVALID_HANDLE;
	}

	return m_pFileImpl->Open(pFileName,
		dwFlags,
		dwMode );
}

int CCSFile::Close()
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_ERROR_FAILURE;
	}

	return m_pFileImpl->Close();
}

int CCSFile::Read( 
	char* pBuffer,
	DWORD dwReadLen,
	DWORD& dwActualRead )
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_ERROR_FAILURE;
	}

	return m_pFileImpl->Read( pBuffer, dwReadLen, dwActualRead );
}

int CCSFile::Write( 
	const char* pBuffer,
	DWORD dwWriteLen,
	DWORD& dwActualWrite )
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_ERROR_FAILURE;
	}

	return m_pFileImpl->Write(pBuffer, dwWriteLen, dwActualWrite );
}

int CCSFile::Seek( CCS_OFFSET lDistance, DWORD dwMoveMethod )
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_ERROR_FAILURE;
	}

	return m_pFileImpl->Seek( lDistance, dwMoveMethod );
}

int CCSFile::Flush()
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_ERROR_FAILURE;
	}

	return m_pFileImpl->Flush();
}

HANDLE CCSFile::GetFileHandle()
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_INVALID_HANDLE;
	}

	return m_pFileImpl->GetFileHandle();
}

int CCSFile::SetFileSize( LONGLONG llFileSize )
{
	if ( NULL == m_pFileImpl )
	{
		return CCS_ERROR_FAILURE;
	}

	return m_pFileImpl->SetFileSize( llFileSize );
}

LONGLONG CCSFile::GetFileSize()
{
	if ( NULL == m_pFileImpl )
	{
		return -1;
	}

	return m_pFileImpl->GetFileSize();
}

LONGLONG CCSFile::GetCreateTime()
{
	if ( NULL == m_pFileImpl )
	{
		return -1;
	}

	return m_pFileImpl->GetCreateTime();
}

LONGLONG CCSFile::GetModifyTime()
{
	if ( NULL == m_pFileImpl )
	{
		return -1;
	}

	return m_pFileImpl->GetModifyTime();
}
