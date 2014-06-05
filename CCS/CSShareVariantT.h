
#ifndef _CCS_SHARE_VARIANT_H_
#define _CCS_SHARE_VARIANT_H_

#include "CCSBase.h"
#include "CSShareMemory.h"
#include "CSShareVariantT.h"
#include "CCSMutexGuardT.h"
#include "CSMutex.h"

template< typename TVar>
class CCSShareVariantT
{
public:
	explicit CCSShareVariantT( const char* szName,
		const TVar& defaultValue )
		: m_bFirstOpen( false )
		, m_mutex( NULL )
		, m_shareMemory( NULL )
	{
		Open( szName, defaultValue );
	}
	~CCSShareVariantT()
	{
		Close();
	}

	CCSShareVariantT& operator = ( const TVar& val )
	{
		Set( val );

		return *this;
	}

	operator TVar() const
	{
		if ( Good() )
		{
			return *(TVar*)m_shareMemory->GetHeadPointer();
		}

		return TVar(0);
	}

	bool Set( const TVar& val );

	bool Get( TVar& val ) const;

	bool IsFirstOpen() const
	{
		return m_bFirstOpen;
	}

	bool Good() const
	{
		return NULL != m_shareMemory && NULL != m_mutex;
	}

private:
	bool Open( const char* pName,
		const TVar& defaultVale );

	void Close();

private:
	CCSShareVariantT( const CCSShareVariantT& );

	void operator = ( const CCSShareVariantT& );

	bool						m_bFirstOpen;

	mutable CCSMutex*			m_mutex;
	mutable CCSShareMemory*		m_shareMemory;
};

template< typename TVar>
void CCSShareVariantT<TVar>::Close()
{
	if ( NULL != m_shareMemory )
	{
		m_shareMemory->Close();

		CCS_DELETE( m_shareMemory );
	}

	CCS_DELETE( m_mutex );
}

template< typename TVar>
bool CCSShareVariantT<TVar>::Open( const char* pName, const TVar& defaultVale )
{
	if ( NULL == pName 
		|| 0 == strcmp(pName, "" ))
	{
		return false;
	}

	if ( NULL == m_mutex )
	{
		CCSString mutexName = pName;
		mutexName += "_MUTEX_VARIANT_";

		m_mutex = new CCSMutex( MUTEX_PROCESS, mutexName.c_str() );
	}

	if ( NULL == m_shareMemory )
	{
		m_shareMemory = new CCSShareMemory();
	}

	CCSMutexGuardT<CCSMutex> guard( m_mutex );
	CCSString strSharenameTemp = pName;
	strSharenameTemp += "_SM_VARIANT_";

	int iRet = m_shareMemory->Open( 
		strSharenameTemp.c_str(),
		sizeof(TVar) );

	if ( CCS_OK != iRet )
	{
		iRet = m_shareMemory->Open(
			strSharenameTemp.c_str(),
			sizeof(TVar),
			CCSShareMemory::OM_CREATE );

		if ( CCS_OK != iRet )
		{
			Close();

			return false;
		}

		m_bFirstOpen = true;

		m_shareMemory->Write( (const char*)&defaultVale, sizeof(TVar) );
	}

	return true;
}

template< typename TVar>
bool CCSShareVariantT<TVar>::Get( TVar& val ) const
{
	if ( !Good() )
	{
		return false;
	}

	DWORD dwActualRead = 0;
	int iRet = CCS_ERROR_FAILURE;
	{
		CCSMutexGuardT<CCSMutex> guard( m_mutex );

		m_shareMemory->Seek( 0, CCS_SEEK_BEGIN );
		iRet = m_shareMemory->Read(
			(char*)&val,
			sizeof(TVar),
			dwActualRead );
	}

	if ( CCS_OK == iRet 
		&& dwActualRead == sizeof(TVar) )
	{
		return true;
	}

	return false;
}

template< typename TVar>
bool CCSShareVariantT<TVar>::Set( const TVar& val )
{
	if ( !Good() )
	{
		return false;
	}

	CCSMutexGuardT<CCSMutex> guard( m_mutex );

	m_shareMemory->Seek( 0, CCS_SEEK_BEGIN );
	int iRet = m_shareMemory->Write( (const char*)&val, sizeof(TVar) );

	return (CCS_OK == iRet);
}

#endif // _CCS_SHARE_VARIANT_H_
