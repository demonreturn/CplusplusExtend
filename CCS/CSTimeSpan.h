

#ifndef _CCS_TIME_SPAN_H_
#define _CCS_TIME_SPAN_H_

#include "CCSBase.h"
#include "CCSTimeStamp.h"

class CCSTimeSpan
{
public:
	typedef CCCSTimeStamp::TTimeDiff TTimeDiff;

	// ���Ϊ0
	CCSTimeSpan();

	// ����ָ��΢���ʱ����
	CCSTimeSpan( TTimeDiff microseconds );

	// ����timeval�ṹ��ʱ������Timespan
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
		����: ��������
	
		����ֵ:int  ����
	
		�����б�:
	************************************/
	int Days() const;

	/************************************
		����: �������е�Сʱ��
	
		����ֵ:int Сʱ����0��24Сʱ
	
		�����б�:
	************************************/
	int Hours() const;

	/************************************
		����: �����ܵ�Сʱ����������ת��ΪСʱ
	
		����ֵ:int Сʱ��
	
		�����б�:
	************************************/
	int TotalHours() const;

	/************************************
		����: �������еķ�����
	
		����ֵ:int ��������0��59
	
		�����б�:
	************************************/
	int Minutes() const;

	/************************************
		����: ����ʱ��������ʾ���ܷ�����
	
		����ֵ:int �ܷ�����������Сʱ���ᱻת��
	
		�����б�:
	************************************/
	int TotalMinutes() const;

	/************************************
		����: �������е�����
	
		����ֵ:int ������0��59
	
		�����б�:
	************************************/
	int Seconds() const;

	/************************************
		����: ����ʱ��������ʾ���ܵ�����
	
		����ֵ:int �ܵ�����
	
		�����б�:
	************************************/
	int TotalSeconds() const;

	/************************************
		����: �������еĺ�����
	
		����ֵ:int ��������0��999
	
		�����б�:
	************************************/
	int MilliSeconds() const;

	/************************************
		����: ����ʱ��������ʾ���ܵĺ�����
	
		����ֵ:CVxTimespan::TTimeDiff
	
		�����б�:
	************************************/
	TTimeDiff TotalMilliSeconds() const;

	/************************************
		����: �������е�΢����
	
		����ֵ:int
	
		�����б�:
	************************************/
	int MicroSeconds() const;

	/************************************
		����: ����ʱ��������ʾ���ܵ�΢����
	
		����ֵ:CVxTimespan::TTimeDiff
	
		�����б�:
	************************************/
	TTimeDiff TotalMicroSeconds() const;

	/************************************
		����: ��΢�����ʽ�������С������
	
		����ֵ:int 0��999999
	
		�����б�:
	************************************/
	int Useconds() const;

	// ����ת΢��ı���
	static const TTimeDiff MILLISECONDS									= 1000;

	// ��ת΢��ı���
	static const TTimeDiff SECONDS										= 1000*MILLISECONDS;

	// ��ת΢��ı���
	static const TTimeDiff MINUTES										= 60*SECONDS;

	// Сʱת΢��ı���
	static const TTimeDiff HOURS										= 60*MINUTES;

	// ��ת΢��ı���
	static const TTimeDiff DAYS											= 24*HOURS;

private:
	/**
	 * ʱ���ȱ�ʾ��64λ����
	 */
	TTimeDiff					m_span;
};

#endif	// _CCS_TIME_SPAN_H_

