
#ifndef _CCS_SHARE_VARIANT_H_
#define _CCS_SHARE_VARIANT_H_

#include "CCSBase.h"
#include "CCSLock.h"
#include "CSShareMemory.h"
#include "CSShareVariantT.h"

template< typename TVar>
class CCSShareVariantT
{
public:
	explicit CCSShareVariantT( const char* szName,
		const TVar& defaultValue )
	{

	}
	~CCSShareVariantT();

private:
	bool						m_bFirstOpen;

	mutable CCSMutex*			m_mutex;
	mutable ccssh
};

#endif // _CCS_SHARE_VARIANT_H_
