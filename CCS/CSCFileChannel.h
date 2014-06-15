
#ifndef _CCS_FILE_CHANNEL_H_
#define _CCS_FILE_CHANNEL_H_

#include "CCSBase.h"
#include "CSChannel.h"

class CCSCFileChannel : public CCSChannel
{
public:
	CCSCFileChannel();

	virtual void Log( const CCSLogMessage& msg );

	virtual const char* ChannelName() const;
};


#endif	// _CCS_FILE_CHANNEL_H_
