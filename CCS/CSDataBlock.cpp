#include "CSDataBlock.h"
#include "CCSOSMemory.h"

#include <assert.h>

CCSDataBlock::CCSDataBlock( 
	DWORD dwSize, 
	char* pBase /*= NULL */ )
	: m_pBase( NULL )
	, m_size( dwSize )
	, m_readPos( 0 )
	, m_writePos( 0 )
	, m_refCount( 1 )
	, m_dwFlag( 0 )
{
	if ( NULL != pBase )
	{
		// 用户申请了空间
		m_pBase = pBase;
		CCS_SET_BITS( m_dwFlag, NO_DEL_DATA );
	}
	else
	{
		// DB 负责删除数据
		m_pBase = new char[dwSize];

		CCS_ZERO( m_pBase, dwSize );
	}
}

CCSDataBlock::~CCSDataBlock()
{

}

CCSDataBlock* CCSDataBlock::Duplicate()
{
	m_refCount++;

	return this;
}

CCSDataBlock* CCSDataBlock::Clone()
{
	CCSDataBlock* pnew = new CCSDataBlock( this->m_size );

	if ( NULL != pnew )
	{
		CCS_OS::OSMemcpy(
			pnew->m_pBase,
			pnew->m_size,
			this->m_pBase,
			this->m_size );

		pnew->m_readPos = this->m_readPos;
		pnew->m_writePos = this->m_writePos;
	}

	return pnew;
}

int CCSDataBlock::Read( 
	char* pDst,
	DWORD dwBeginPos,
	DWORD dwLength )
{
	if ( 0 == dwLength )
	{
		return CCS_OK;
	}

	if ( NULL == pDst
		|| ( dwLength + dwBeginPos) > m_size )
	{
		return CCS_ERROR_FAILURE;
	}

	CCS_OS::OSMemcpy(
		pDst,
		dwLength,
		m_pBase + dwBeginPos,
		dwLength );

	m_readPos = dwBeginPos + dwLength;

	return CCS_OK;
}

int CCSDataBlock::Write( 
	const char* pBuffer,
	DWORD dwBeginPos,
	DWORD dwLength )
{
	if ( 0 == dwLength )
	{
		return CCS_OK;
	}

	if ( NULL == pBuffer 
		|| ( dwLength + dwBeginPos) > m_size )
	{
		return CCS_ERROR_FAILURE;
	}

	CCS_OS::OSMemcpy(
		m_pBase + dwBeginPos,
		dwLength,
		pBuffer,
		dwLength );

	m_writePos = dwBeginPos + dwLength;

	return CCS_OK;
}

DWORD CCSDataBlock::GetSpace()
{
	if ( m_size <= m_writePos )
	{
		return (DWORD)0;
	}
	else
	{
		return (DWORD)(m_size - m_writePos);
	}
}

DWORD CCSDataBlock::GetLength( DWORD nMBRelativeFlag /*= 0 */ )
{
	// 默认是从头到尾的整个空间长度
	DWORD nBegin = 0;
	DWORD nEnd = m_size;

	assert( nMBRelativeFlag < (CUR_WRITE_DB << 1) );

	// 如果DB是MB当前读指针所在位置,则长度计算从DB的读指针开始
	if ( CCS_BIT_ENABLED( nMBRelativeFlag, CUR_READ_DB ))
	{
		nBegin = m_readPos;
	}

	// 如果DB是MB当前写指针所在位置,则长度计算到写指针结束
	if ( CCS_BIT_ENABLED( nMBRelativeFlag, CUR_WRITE_DB))
	{
		nEnd = m_writePos;
	}

	if ( nBegin >= nEnd )
	{
		return 0;
	}
	else
	{
		return (nEnd - nBegin);
	}
}

DWORD CCSDataBlock::GetSize()
{
	return m_size;
}

char* CCSDataBlock::GetBasePtr()
{
	return m_pBase;
}

DWORD CCSDataBlock::GetCurReadPos()
{
	return m_readPos;
}

DWORD CCSDataBlock::GetCurWritePos()
{
	return m_writePos;
}

int CCSDataBlock::SetCurReadPos( DWORD dwPos )
{
	if ( dwPos > m_size )
	{
		return CCS_ERROR_FAILURE;
	}

	m_readPos = dwPos;

	return CCS_OK;
}

int CCSDataBlock::SetCurWritePos( DWORD dwPos )
{
	if ( dwPos > m_size )
	{
		return CCS_ERROR_FAILURE;
	}

	m_writePos = dwPos;

	return CCS_OK;
}

void CCSDataBlock::Reset()
{
	m_readPos = 0;
	m_writePos = 0;

	CCS_ZERO( m_pBase, m_size );
}

int CCSDataBlock::Release()
{
	int iRet = CCS_OK;

	m_refCount--;

	if ( 0 == m_refCount )
	{
		if ( NULL != m_pBase 
			&& CCS_BIT_ENABLED( m_dwFlag, DEL_DATA))
		{
			CCS_ARRAY_DELETE( m_pBase );
		}

		delete this;
	}

	return iRet;
}
