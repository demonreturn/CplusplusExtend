

#ifndef _CCS_TIME_SPAN_H_
#define _CCS_TIME_SPAN_H_

#include "CCSBase.h"
#include "CCSTimeStamp.h"

class CCSTimeSpan
{
public:
	typedef CCCSTimeStamp::TTimeDiff TTimeDiff;

	// 跨度为0
	CCSTimeSpan();

	// 创建指定微秒的时间跨度
	CCSTimeSpan( TTimeDiff microseconds );

	// 用于timeval结构体时创建的Timespan
	CCSTimeSpan( long seconds, long microseconds );

	CCSTimeSpan( int days, int hours, int minutes,
		int seconds, int microseconds );

	CCSTimeSpan( const CCSTimeSpan& timespan );

	CCSTimeSpan& operator = ( const CCSTimeSpan& timespan );

	CCSTimeSpan& operator = ( TTimeDiff microseconds );

	CCSTimeSpan& Assign( int days, int hours, int minutes, int seconds, int microseconds );

	CCSTimeSpan& Assign( long seconds, long microseconds );

	bool operator == ( const CCSTimeSpan& ts ) const;
	bool operator != ( const CCSTimeSpan& ts ) const;
	bool operator >  ( const CCSTimeSpan& ts ) const;
	bool operator >= ( const CCSTimeSpan& ts ) const;
	bool operator <  ( const CCSTimeSpan& ts ) const;
	bool operator <= ( const CCSTimeSpan& ts ) const;

	bool operator == ( TTimeDiff microseconds ) const;
	bool operator != ( TTimeDiff microseconds ) const;
	bool operator >  ( TTimeDiff microseconds ) const;
	bool operator >= ( TTimeDiff microseconds ) const;
	bool operator <  ( TTimeDiff microseconds ) const;
	bool operator <= ( TTimeDiff microseconds ) const;

	CCSTimeSpan operator + ( const CCSTimeSpan& ts ) const;
	CCSTimeSpan operator - ( const CCSTimeSpan& ts ) const;

	CCSTimeSpan& operator += ( const CCSTimeSpan& ts );
	CCSTimeSpan& operator -= ( const CCSTimeSpan& ts );

	CCSTimeSpan operator + ( TTimeDiff microseconds ) const;
	CCSTimeSpan operator - ( TTimeDiff microseconds ) const;

	CCSTimeSpan& operator += ( TTimeDiff microseconds );
	CCSTimeSpan& operator -= ( TTimeDiff microseconds );

	/************************************
		描述: 返回天数
	
		返回值:int  天数
	
		参数列表:
	************************************/
	int Days() const;

	/************************************
		描述: 返回其中的小时数
	
		返回值:int 小时数，0～24小时
	
		参数列表:
	************************************/
	int Hours() const;

	/************************************
		描述: 返回总的小时数，天数会转化为小时
	
		返回值:int 小时数
	
		参数列表:
	************************************/
	int TotalHours() const;

	/************************************
		描述: 返回其中的分中数
	
		返回值:int 分钟数，0～59
	
		参数列表:
	************************************/
	int Minutes() const;

	/************************************
		描述: 返回时间跨度所表示的总分钟数
	
		返回值:int 总分钟数，天与小时都会被转化
	
		参数列表:
	************************************/
	int TotalMinutes() const;

	/************************************
		描述: 返回其中的秒数
	
		返回值:int 秒数，0～59
	
		参数列表:
	************************************/
	int Seconds() const;

	/************************************
		描述: 返回时间跨度所表示的总的秒数
	
		返回值:int 总的秒数
	
		参数列表:
	************************************/
	int TotalSeconds() const;

	/************************************
		描述: 返回其中的毫秒数
	
		返回值:int 毫秒数，0～999
	
		参数列表:
	************************************/
	int MilliSeconds() const;

	/************************************
		描述: 返回时间跨度所表示的总的毫秒数
	
		返回值:CVxTimespan::TTimeDiff
	
		参数列表:
	************************************/
	TTimeDiff TotalMilliSeconds() const;

	/************************************
		描述: 返回其中的微秒数
	
		返回值:int
	
		参数列表:
	************************************/
	int MicroSeconds() const;

	/************************************
		描述: 返回时间跨度所表示的总的微秒数
	
		返回值:CVxTimespan::TTimeDiff
	
		参数列表:
	************************************/
	TTimeDiff TotalMicroSeconds() const;

	/************************************
		描述: 以微秒的形式返回秒的小数部分
	
		返回值:int 0～999999
	
		参数列表:
	************************************/
	int Useconds() const;

	// 毫秒转微秒的倍数
	static const TTimeDiff MILLISECONDS									= 1000;

	// 秒转微秒的倍数
	static const TTimeDiff SECONDS										= 1000*MILLISECONDS;

	// 分转微秒的倍数
	static const TTimeDiff MINUTES										= 60*SECONDS;

	// 小时转微秒的倍数
	static const TTimeDiff HOURS										= 60*MINUTES;

	// 天转微秒的倍数
	static const TTimeDiff DAYS											= 24*HOURS;

private:
	/**
	 * 时间跨度表示，64位整数
	 */
	TTimeDiff					m_span;
};

#endif	// _CCS_TIME_SPAN_H_

