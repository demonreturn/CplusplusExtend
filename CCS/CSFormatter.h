
#include "CCSBase.h"
class CCSLogMessage;

class CCSFormatter
{
public:
	virtual ~CCSFormatter(){}

	virtual void Format( const CCSLogMessage& msg, CCSString& str ) = 0;
};

typedef std::shared_ptr<CCSFormatter>		TFormatterPtr;

