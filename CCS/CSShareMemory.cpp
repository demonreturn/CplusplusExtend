#include "CSShareMemory.h"

#include "CCSOSMemory.h"
#include "CCSOSShareMemory.h"


CCSShareMemory::CCSShareMemory()
	: m_strName( "" )
	, m_dwSize( 0 )
	, m_pHead( NULL )
	, m_pCurrent( NULL )
	, m_hFileMap( CCS_INVALID_HANDLE )
{

}

CCSShareMemory::~CCSShareMemory()
{
	if ( CCS_INVALID_HANDLE != m_hFileMap )
	{
		this->Close();
	}
}

int CCSShareMemory::Open(
	const char* pname,
	DWORD dwSize,
	DWORD dwOpenMode,
	const char* pFileDir /*= NULL */ )
{
	if ( NULL == pname
		|| 0 == dwSize )
	{
		return CCS_ERROR_INVALID_PARAM;
	}

	if ( m_hFileMap != CCS_INVALID_HANDLE )
	{
		return CCS_ERROR_ALREADY_INIT;
	}

	// ���ȳ��Դ����еĹ����ڴ����
	if ( CCS_BIT_DISABLED( dwOpenMode, OM_CREATE)
		&& CCS_BIT_ENABLED( dwOpenMode, OM_MAP_FILE)
		&& NULL != pFileDir )
	{
		// ���û��ָ��OM_CREATE�����ǳ����ļ����������Ҫ�жϳ����ļ��Ƿ����(���Linux)
		CCSString strRegularFile = GenerateFileName( pname, pFileDir );

		m_hFileMap = CCS_OS::OpenShareMemory(
			pname, strRegularFile.c_str() );
	}
	else
	{
		m_hFileMap = CCS_OS::OpenShareMemory(
			pname,
			NULL );
	}

	if ( CCS_INVALID_HANDLE == m_hFileMap )
	{
		// ������й����ڴ���󲻴��ڣ���ô�͸���Ҫ�󴴽�һ�����߷���ʧ��
		if ( CCS_BIT_DISABLED( dwOpenMode, OM_CREATE))
		{
			// ����Ҫ����
			return CCS_ERROR_FAILURE;
		}

		HANDLE hFile = CCS_INVALID_HANDLE;

		if ( CCS_BIT_ENABLED( dwOpenMode, OM_MAP_FILE ))
		{
			// ���Ҫ��ӳ�䵽�ļ��򴴽��ļ�
			CCSString strFileName = GenerateFileName( pname, pFileDir);
			if ( false == CreateMapFile( strFileName.c_str(), dwOpenMode))
			{
				return CCS_ERROR_FAILURE;
			}

			m_fMapping.SetFileSize( dwSize );
			hFile = m_fMapping.GetFileHandle();
		}

		m_hFileMap = CCS_OS::CreateShareMemory(
			hFile, 
			dwSize,
			pname );

		if ( CCS_INVALID_HANDLE == m_hFileMap )
		{
			return CCS_ERROR_FAILURE;
		}
	}

	m_pHead = (char*)CCS_OS::MapViewShareMemory(
		m_hFileMap,
		dwSize );

	if ( NULL == m_pHead )
	{
		bool bMapToFile = true;

		if ( CCS_INVALID_HANDLE == m_fMapping.GetFileHandle())
		{
			bMapToFile = false;
		}

		CCS_OS::CloseShareMemory( m_hFileMap, bMapToFile, NULL, 0 );

		m_hFileMap = CCS_INVALID_HANDLE;

		return CCS_ERROR_FAILURE;
	}

	m_strName = pname;
	m_dwSize = dwSize;

	m_pCurrent = m_pHead;

	return CCS_OK;

}

char* CCSShareMemory::GetHeadPointer() const
{
	return m_pHead;
}

int CCSShareMemory::Close()
{
	int iRet = CCS_OK;

	m_strName.clear();

	if ( NULL != m_pHead )
	{
		iRet = CCS_OS::CloseShareMemory(
			CCS_INVALID_HANDLE,
			FALSE,
			m_pHead,
			m_dwSize );

		if ( CCS_OK != iRet )
		{
			return CCS_ERROR_FAILURE;
		}

		m_pHead = NULL;
	}

	m_dwSize = 0;
	m_pCurrent = NULL;

	if ( CCS_INVALID_HANDLE != m_hFileMap )
	{
		bool bMapToFile = true;

		if ( CCS_INVALID_HANDLE != m_fMapping.GetFileHandle() )
		{
			bMapToFile = false;
		}

		iRet = CCS_OS::CloseShareMemory(
			m_hFileMap, bMapToFile, NULL, 0 );

		if ( CCS_OK != iRet )
		{
			return CCS_ERROR_FAILURE;
		}

		m_hFileMap = INVALID_HANDLE_VALUE;
	}

	if ( CCS_INVALID_HANDLE != m_fMapping.GetFileHandle() )
	{
		iRet = m_fMapping.Close();

		if ( CCS_OK != iRet )
		{
			return CCS_ERROR_FAILURE;
		}
	}

	return iRet;
}

int CCSShareMemory::Read( 
	char* pBuffer,
	DWORD dwLength,
	DWORD& dwAcutualRead )
{
	if ( NULL == pBuffer )
	{
		return CCS_ERROR_FAILURE;
	}

	// ���㵱ǰָ����ܹ��ĳ��ȿռ�
	dwAcutualRead = m_pHead + m_dwSize - m_pCurrent;

	// ʹ��ʣ�೤�Ⱥ�ϣ����ȡ�ĳ���֮����С��
	dwAcutualRead = ( dwAcutualRead > dwLength ) ? dwLength : dwAcutualRead;

	CCS_OS::OSMemcpy( pBuffer, dwAcutualRead, m_pCurrent, dwAcutualRead );

	m_pCurrent += dwAcutualRead;

	return CCS_OK;
}

int CCSShareMemory::Write(
	const char* pBuffer,
	DWORD dwLength )
{
	if ( NULL == pBuffer )
	{
		return CCS_ERROR_FAILURE;
	}

	DWORD dwRemain = m_pHead + m_dwSize - m_pCurrent;

	if ( dwRemain < dwLength )
	{
		return CCS_ERROR_FAILURE;
	}

	CCS_OS::OSMemcpy( m_pCurrent, dwLength, pBuffer, dwLength );

	return CCS_OK;
}

int CCSShareMemory::Seek( long lOffset, DWORD nMoveMethod )
{
	if ( NULL == m_pHead )
	{
		return CCS_ERROR_FAILURE;
	}

	LONGLONG llBase = 0;

	switch ( nMoveMethod )
	{
	case CCS_SEEK_BEGIN:
		llBase = 0;
		break;

	case CCS_SEEK_CUR:
		llBase = m_pCurrent - m_pHead;
		break;

	case CCS_SEEK_END:
		llBase = m_dwSize;
		break;
	default:
		return CCS_ERROR_FAILURE;
		break;
	}

	m_pCurrent = m_pHead + llBase;

	return CCS_OK;
}

char* CCSShareMemory::GetCurrentPointer() const
{
	return m_pCurrent;
}

void CCSShareMemory::UnLink()
{
	if ( !m_strName.empty() )
	{
		CCS_OS::UnLinkShareMemory( m_strName.c_str() );
	}
}

bool CCSShareMemory::Flush()
{
	if ( NULL == m_pHead )
	{
		return false;
	}

	return CCS_OS::FlushShareMemory( m_pHead, m_dwSize ) ? true : false;
}

CCSString CCSShareMemory::GenerateFileName(
	const char* pname,
	const char* pdirtory )
{
	CCSString strFileName;

	if ( NULL != pdirtory )
	{
		strFileName = pdirtory;
	}

	DWORD dwLen = strFileName.length();

	// �Ƴ��ұߵĿո��Ŀ¼�ָ��
	while ( dwLen > 0 )
	{
		char cValue = strFileName[dwLen-1];
		if ( cValue == ' '
			|| cValue == '\\'
			|| cValue == '/' )
		{
			--dwLen;
			continue;
		}
		else
		{
			break;
		}
	}

	strFileName = strFileName.substr( 0, dwLen );

	// ����Ŀ¼�ָ�����ļ������һ��������·����
	strFileName.push_back( CCS_OS_SEPARATE );
	strFileName.append( pname );

	return strFileName;
}

bool CCSShareMemory::CreateMapFile( 
	const char* pname,
	DWORD nMode )
{
	DWORD nFlag = O_RDWR | O_CREAT;

	if ( CCS_BIT_ENABLED( nMode, OM_TRUNCATE ))
	{
		nFlag |= O_TRUNC;
	}

	if ( CCS_INVALID_HANDLE != m_fMapping.GetFileHandle())
	{
		// ����Ѿ������ļ����ȹرյ�
		m_fMapping.Close();
	}

	return ( CCS_INVALID_HANDLE != m_fMapping.Open( pname, nFlag ) ) ? true : false;
}




