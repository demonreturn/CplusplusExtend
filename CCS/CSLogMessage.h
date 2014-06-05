

#ifndef _CCS_LOG_MESSAGE_H_
#define _CCS_LOG_MESSAGE_H_


#include "CCSBase.h"

#include "CCSTimeStamp.h"

/**
 * CScLogMessage����ʾһ��log��Ϣ��
 * ������־����Ŀ��ǣ�
 * ��־����Ҫ�ȼ����Ӹߵ��� { FATAL>CRITICAL>ERROR>WARNING>NOTICE>INFORMATION>DEBUG>TRACE }
 * ÿ���ȼ�����־�ڳ����ڲ���Ӧ��ʹ��������£�
 * LOG_FATAL:
 *		������ȼ�����¼����ϵͳ�ڲ�����Ҫ����Ϣ������Ǵ�������������󣬳��򽫲��ܼ������У�
 *		��Ҫ�رա�������Ǵ����ǽ��Ǵ��������˳�����Ϣ��ʹ������������־��¼֮��
 * LOG_CRITICAL:
 *		�ؼ���־����¼�����ڲ���Ϊ�ؼ�����Ϣ����������ϵͳ�����ж���������Ƚϴ��Ӱ�죬������Ϣ
 *		�����й�����Ҳ��Ƚ��٣�Ŀǰ���ڵ���Ȩ�����¼ʱ���˳�ʱʹ�á�
 * LOG_ERROR:
 *		������Ϣ�����й����м�⵽�Ĵ����Լ������ڲ������˴��������ڲ�ʹ�õ�Ҳ��Ƚ��٣�
 *		���������ݷ��ֲ�һ��ʱʹ�á��϶���Ƿ�Ӧ�����ڲ��Ĵ���
 * LOG_WARNING:
 *		�澯��Ϣ����Ӧ�Ų����ϵĴ������ⲿ�������ʧ�ܣ����ڳ����ڲ���˵��������һ��������ڲ�
 *		δ��������ʧ�ܵ�ֻ�ǵ�ǰ��ĳ��������������ĳ��λ��ʧ�ܣ��������͵�ֵʱ������̬�����ڵȡ�
 * LOG_NOTICE:
 *		֪ͨ��Ϣ�������ر���Ҫ��֪ͨ��Ϣ�����������Ϣ�Գ��������ִ�в����ش�Ӱ�죬Ӧ��ʹ��
 *		LOG_CRITICAL������ȷʵ�������ͨ��Ϣ��Ϊ��ҪһЩ��������һЩ״�������Ҷ������ģ����˵��
 *		һ�ֱ����Ľ��ա���ɨ�赽�µķ���ʵ������ʵ�����ߡ�
 * LOG_INFORMATION:
 *		��ͨ��ʾ��Ϣ����¼һЩ�ⲿ����Ĳ�����������Щ�����Գ����ڲ�������ĳЩӰ�죬��λ�ŵ����ӣ�
 *		ɾ���ȡ�
 * LOG_DEBUG:
 *		������Ϣ���ڽ��г������ʱʹ�ý϶࣬��ͨ����²���������ء�����������־��Ҫ�ڽ��г���
 *		����׷��ʱʹ�ã���¼�������ʱ�Ĳ����Լ����÷���ʱ�ķ���ֵ�����ⷽ�������ԵĽǶȶ����ӵġ�
 * LOG_TRACE:
 *		׷����Ϣ��ѭ����������������ڵ�����Ϣ������Ҫ����־��Ϣ��Ϊʲô�趨�������
 *		����Ŀ�����������������ӡһЩ���磺���� ���͵���ϸ��Ϣ�������Բ�������Ϣ�������������Ϣ
 *		�ϲ���Debug�����£��ᷢ����һ���������Ϣ����������ԡ�
 *		�ںܶ�ʱ�򣬵����Ѿ���ɣ��ܶ��Debug��־���Ը�ΪTrace�������־��
 */

class CCSLogMessage
{
public:
	enum ELogLevel
	{
		// ����Ҫ��Ϣ�� ������ȼ���־�����̽����п����޷��������У���Ҫ�رա�
		LOG_FATAL = 1,

		// �ؼ���Ϣ��.����Ǵ�����Ϣ��������ڲ��Ѿ����ִ���
		LOG_CRITICAL,

		// ���� ����ʧ�ܣ�����Ϊ���������Խ������ܵ�Ӱ��
		LOG_ERROR,

		// �澯�� �����ﲻ��Ԥ�ڵĽ��
		LOG_WARNING,

		// ֪ͨ�� ��info�������ȼ�����־
		LOG_NOTICE,

		// ��Ϣ
		LOG_INFORMATION,

		// ������Ϣ.
		LOG_DEBUG,

		// ��ͨtrace
		LOG_TRACE,


		LOG_LEVEL_SIZE
	};

	static const char* LOG_LEVEL_NAME[LOG_LEVEL_SIZE];

	CCSLogMessage( 
		const CCSString& src,
		const CCSString& text,
		ELogLevel level,
		const char* pfile,
		const char* fun,
		int line );

	CCSLogMessage( const CCSLogMessage& msg );


	~CCSLogMessage(){}

	const CCSString& GetSource() const
	{
		return m_source;
	}

	const CCSString& GetText() const
	{
		return m_text;
	}
	
	int GetLevel() const
	{
		return m_level;
	}

	const char* GetLevelName() const;

	const CCCSTimeStamp& GetTime() const
	{
		return m_time;
	}

	const char* GetSourceFile() const
	{
		return m_file;
	}

	const char* GetFunction() const
	{
		return m_function;
	}

	int GetSourceLine() const
	{
		return m_line;
	}

	CCS_THREAD_ID GetThreadID() const
	{
		return m_threadID;
	}

	long GetPID() const
	{
		return m_pid;
	}

	static const char* GetLevelName( int level );

	CCSLogMessage& operator = ( const CCSLogMessage& msg );

	bool operator == ( const CCSLogMessage& msg );

private:
	CCSString					m_source;

	CCSString					m_text;

	ELogLevel					m_level;

	CCCSTimeStamp				m_time;

	long						m_pid;

	CCS_THREAD_ID				m_threadID;

	int							m_line;

	const char*					m_file;

	const char*					m_function;
};

#endif	// _CCS_LOG_MESSAGE_H_