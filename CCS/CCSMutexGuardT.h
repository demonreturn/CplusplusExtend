
#ifndef _CCS_MUTEX_GUARD_T_H_
#define _CCS_MUTEX_GUARD_T_H_

#include "CCSBase.h"

template< class locktype>
class CCSMutexGuardT
{
public:
	CCSMutexGuardT( locktype* pMutex = NULL );
	~CCSMutexGuardT();

private:
	int Lock();

	int UnLock();

private:
	CCSMutexGuardT();
	CCSMutexGuardT( const CCSMutexGuardT&);
	CCSMutexGuardT& operator = ( const CCSMutexGuardT&);

	LOCKTYPE					m_pMutex;
};

template< class locktype>
int CCSMutexGuardT<locktype>::UnLock()
{
	int iRet = -1;
	if ( NULL != m_pMutex )
	{
		iRet = m_pMutex->UnLock();
	}

	return iRet;
}

template< class locktype>
int CCSMutexGuardT<locktype>::Lock()
{
	int iRet = -1;

	if ( NULL != m_pMutex )
	{
		iRet = m_pMutex->Lock();
	}

	return iRet;
}

template< class locktype>
CCSMutexGuardT<locktype>::~CCSMutexGuardT()
{
	this->UnLock();

}

template< class locktype>
CCSMutexGuardT<locktype>::CCSMutexGuardT( locktype* pMutex /*= NULL */ )
	: m_pMutex( pMutex )
{
	this->Lock();
}

#endif	// _CCS_MUTEX_GUARD_T_H_