#include "CSFileImplFactory.h"

#include "CCSFileTypes.h"
#include "CSRegularFileImpl.h"

// Ŀǰ�˴�ֻʵ����ͨ�ļ�
int CCSFileImplFactory::CreateFileImpl( DWORD dwType, ICCSFileImpl*& pFile )
{
	if ( FILE_TYPES_REGULAR_FILE == dwType )
	{
		pFile = new CCSRegularFileImpl();

		if ( NULL == pFile )
		{
			return CCS_ERROR_FAILURE;
		}

		return CCS_OK;
	}

	return CCS_ERROR_NOT_FOUND;
}
