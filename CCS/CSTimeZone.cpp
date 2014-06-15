#include "CSTimeZone.h"

#include <ctime>
#include <time.h>
#ifdef CCS_WIN32
#include <Windows.h>
#endif

int CCSTimeZone::UtcOffset()
{
#ifdef CCS_WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation( &tzInfo );

	return -tzInfo.Bias * 60;
#elif defined( CCS_LINUX)		// linux  ʵ��
	return -timezone;
#endif
}

int CCSTimeZone::Dst()
{
#ifdef CCS_WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation( &tzInfo );
	return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias*60 : 0;
#elif defined( CCS_LINUX)		// linux  ʵ��
	std::time_t now = std::time(NULL);
	struct std::tm t;
	if ( !localtime_r(&now, &t ))
	{
		return 0;
	}

	return t.tm_isdst == 1 ? 3600 : 0;
#endif
}

bool CCSTimeZone::IsDst( const CCCSTimeStamp& timestamp )
{
	std::time_t time = timestamp.GetTime();
	struct std::tm tms;
	errno_t eno = localtime_s( &tms, &time);
	if (0 != eno)
		return false;
	return tms.tm_isdst > 0;
}

int CCSTimeZone::Tzd()
{
	return UtcOffset() + Dst();
}
