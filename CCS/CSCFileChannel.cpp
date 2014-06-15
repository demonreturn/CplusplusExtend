#include "CSCFileChannel.h"
#include "CSTraceDefine.h"

#include "CSTraceFormator.h"

CCSCFileChannel::CCSCFileChannel()
{
}

void CCSCFileChannel::Log( const CCSLogMessage& msg )
{
	if ( !IsOpend() )
	{
		return;
	}

	char pformatBuffer[CCS_TRACE_AVAILABLE_DATA_LEN] = { 0 };
	CCSTraceFormator traceFormater( pformatBuffer, CCS_TRACE_AVAILABLE_DATA_LEN );
	traceFormater
		<< "["
		<< ""

}

const char* CCSCFileChannel::ChannelName() const
{

}
