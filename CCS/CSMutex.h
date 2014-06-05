
#ifndef _CCS_MUTEX_H_
#define _CCS_MUTEX_H_

#include "CCSBase.h"

#include "CCSTimeStamp.h"
#include "CCSLock.h"

class CCSMutex
{
public:
	CCSMutex(
		int type = MUTEX_PROCESS,
		const char* pname = 0,
		int *parg = 0,
		int mode = CCS_DEFAULT_FILE_MODE );

	~CCSMutex();

	int Lock();

	int Lock( CCCSTimeStamp& timeout );

	int Lock( CCCSTimeStamp* timeout );

	int TryLock();

	int UnLock();

	const CSMutex& GetMutex() const;

	//void Dump() const

private:
	void operator = ( const CCSMutex& );
	CCSMutex( const CCSMutex& );

	/*
	 * 移除并释放内核对象
	 */
	int Remove();

private:
	CSMutex						m_mutex;

	const char*					m_pLockName;
};


#endif	// _CCS_MUTEX_H_

