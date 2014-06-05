#include "CSMutex.h"

#include <assert.h>

CCSMutex::CCSMutex( 
	int type /*= MUTEX_PROCESS*/,
	const char* pname /*= 0*/,
	int *parg /*= 0*/,
	int mode /*= CCS_DEFAULT_FILE_MODE */ )
	: m_pLockName( NULL )
{
	int iRet = -1;

	iRet = CCS_OS::InitMutex(
		&this->m_mutex,
		type,
		pname,
		parg );

	assert( 0 == iRet );
}

CCSMutex::~CCSMutex()
{
	this->Remove();
}

int CCSMutex::Remove()
{
	return CCS_OS::DestoryMutex( &this->m_mutex );
}

int CCSMutex::Lock()
{
	return CCS_OS::LockMutex( &this->m_mutex );
}

int CCSMutex::Lock( CCCSTimeStamp& timeout )
{
	return CCS_OS::LockMutex( &this->m_mutex, timeout );
}

int CCSMutex::Lock( CCCSTimeStamp* timeout )
{
	return CCS_OS::LockMutex( &this->m_mutex, timeout );
}

int CCSMutex::TryLock()
{
	return CCS_OS::TryLockMutex( &this->m_mutex );
}

int CCSMutex::UnLock()
{
	return CCS_OS::UnLockMutex( &this->m_mutex );
}
