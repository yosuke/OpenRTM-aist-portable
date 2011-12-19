// -*- C++ -*-
/*!
 * @file SystemLogger.h
 * @brief RT component logger class
 * @date $Date: 2007-07-20 16:10:32 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SystemLogger.h 2017 2010-12-30 16:38:36Z n-ando $
 *
 */

#ifndef RTC_SYSTEMLOGGER_H
#define RTC_SYSTEMLOGGER_H

#include <rtm/config_rtc.h>

// COIL
#include <coil/Time.h>
#include <coil/Logger.h>
#include <coil/Mutex.h>
#include <coil/Guard.h>
#include <coil/stringutil.h>


namespace RTC
{
  typedef ::coil::LogStreamBuffer LogStreamBuf;
  typedef ::coil::LogStream LogStream;

  /*!
   * @if jp
   * @class Logger
   * @brief Logger ���饹
   *
   * - �����Ϥ򥷥ꥢ�饤��������ʬ�ۤ���Хåե����饹
   * - ����ե����ޥåȤ���ե����ޥåȥ��饹
   * �ǹ��������������饹
   * 
   * - �Хåե����饹
   *  - �ޥ������åɽ񤭹��ߤ��Ф��ƥ��ꥢ�饤�����ƥХåե���󥰤���
   *  - ʣ���ν�����˥�����ϤǤ���
   *  - ���������Ȥ��Ƥϡ��ե����롢ɸ����ϡ���⡼�ȤΥ���������
   *  - �Хåե����Ф���addStream�ǽ�������ɲäǤ���
   * - �ե����ޥåȥ��饹
   *  - ����٥����ꤷ�ƽ��ϤǤ���
   *  - �񼰤ϡ�[����] [����٥�] [���ե��å���] [��å�����]
   *  - [����] [����٥�] [���ե��å���]�ϼ�ư�ղ�
   *  - [���ե��å���] �����Ǥ���ؿ����Ѱ�
   *  - ����٥�ϰʲ��ΤȤ���
   *   - RTL_SILENT
   *   - RTL_FATAL
   *   - RTL_ERROR
   *   - RTL_WARN
   *   - RTL_INFO
   *   - RTL_DEBUG
   *   - RTL_TRACE
   *   - RTL_VERBOSE
   *   - RTL_PARANOID
   *  - ���Υե����ޥåȥ��֥������Ȥ��Ф����å��������å���ǽ
   *
   * @else
   * @class Logger
   * @brief Logger class
   *
   * This class is composed of the buffer class and the format class. 
   * - The buffer class
   *  - The buffer class serializes to the MultiThreading writing and 
   *    does buffering.
   *  - The buffer class can output the log at two or more output destination.
   *    As the example of the output destination, filing, the standard, 
   *    the log server etc. 
   *  - The output destination can be added to the buffer with addStream. 
   * - The format class
   *  - The format class can output it by specifying the log level. 
   *  - The format is [Time] [Loglevel] [Ssuffix] [Message].
   *  - [Time] [Loglevel] [Suffix] are added by the automatic operation. 
   *  - [Suffix] can be specified. 
   *  - Loglevel
   *   - RTL_SILENT
   *   - RTL_FATAL
   *   - RTL_ERROR
   *   - RTL_WARN
   *   - RTL_INFO
   *   - RTL_DEBUG
   *   - RTL_TRACE
   *   - RTL_VERBOSE
   *   - RTL_PARANOID
   *  - The format class can be locked/unlocked to this format object. 
   *
   * @endif
   */
  class Logger
    : public coil::LogStream
  {
  public:
    enum
      {              // No: Write out messages include the following.
        RTL_SILENT,  // 0: ()
        RTL_FATAL,   // 1: (FATAL)
        RTL_ERROR,   // 2: (FATAL, ERROR)
        RTL_WARN,    // 3: (FATAL, ERROR, WARN)
        RTL_INFO,    // 4: (FATAL, ERROR, WARN, INFO)
        RTL_DEBUG,   // 5: (FATAL, ERROR, WARN, INFO, DEBUG)
        RTL_TRACE,   // 6: (FATAL, ERROR, WARN, INFO, DEBUG, TRACE)
        RTL_VERBOSE, // 7: (FATAL, ERROR, WARN, INFO, DEBUG, TRACE, VERBOSE)
        RTL_PARANOID // 8: (FATAL, ERROR, WARN, INFO, DEBUG, TRACE, VERBOSE, PARA)
      };
 
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param name �إå��������θ���ղä���ʸ����
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name suffix of date/time string of header.
     *
     * @endif
     */
    Logger(const char* name = "");
    /*!
     * @if jp
     * @brief ���󥹥ȥ饯��
     *
     * ���󥹥ȥ饯��
     *
     * @param streambuf LogStream ���֥������� 
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param streambuf LogStream object
     *
     * @endif
     */
    Logger(LogStreamBuf* streambuf);
    /*!
     * @if jp
     *
     * @brief ���ۥǥ��ȥ饯��
     * 
     * @else
     * 
     * @brief Virtual destructor
     * 
     * @endif
     */
    virtual ~Logger(void);

    /*!
     * @if jp
     *
     * @brief ����٥��ʸ��������ꤹ��
     *
     * @param level ����٥�
     *
     * @else
     *
     * @brief Set log level by string
     *
     * @param level log level
     *
     * @endif
     */
    bool setLevel(const char* level);

    /*!
     * @if jp
     *
     * @brief �إå����ղä��������ե����ޥåȤ���ꤹ�롣
     *
     * �ե����ޥåȻ���ʸ����ϰʲ��ΤȤ��ꡣ
     * <pre>
     * @%a abbreviated weekday name 
     * @%A full weekday name 
     * @%b abbreviated month name 
     * @%B full month name 
     * @%c the standard date and time string 
     * @%d day of the month, as a number (1-31) 
     * @%H hour, 24 hour format (0-23) 
     * @%I hour, 12 hour format (1-12) 
     * @%j day of the year, as a number (1-366) 
     * @%m month as a number (1-12).
     *    Note: some versions of Microsoft Visual C++ may use values that range
     *    from 0-11. 
     * @%M minute as a number (0-59) 
     * @%p locale's equivalent of AM or PM 
     * @%Q millisecond as a number (0-999) from ver 1.1
     * @%q microsecond as a number (0-999) from ver 1.1
     * @%S second as a number (0-59) 
     * @%U week of the year, sunday as the first day 
     * @%w weekday as a decimal (0-6, sunday=0) 
     * @%W week of the year, monday as the first day 
     * @%x standard date string 
     * @%X standard time string 
     * @%y year in decimal, without the century (0-99) 
     * @%Y year in decimal, with the century 
     * @%Z time zone name 
     * %% a percent sign 
     * </pre>
     *
     * @param fmt �����ե����ޥå�
     *
     * @else
     *
     * @brief Set date/time format for adding the header
     *
     * The format specification string is as follows:
     * <pre>
     * @%a abbreviated weekday name 
     * @%A full weekday name 
     * @%b abbreviated month name 
     * @%B full month name 
     * @%c the standard date and time string 
     * @%d day of the month, as a number (1-31) 
     * @%H hour, 24 hour format (0-23) 
     * @%I hour, 12 hour format (1-12) 
     * @%j day of the year, as a number (1-366) 
     * @%m month as a number (1-12).
     *    Note: some versions of Microsoft Visual C++ may use values that range
     *    from 0-11. 
     * @%M minute as a number (0-59) 
     * @%p locale's equivalent of AM or PM 
     * @%Q millisecond as a number (0-999) from ver 1.1
     * @%q microsecond as a number (0-999) from ver 1.1
     * @%S second as a number (0-59) 
     * @%U week of the year, sunday as the first day 
     * @%w weekday as a decimal (0-6, sunday=0) 
     * @%W week of the year, monday as the first day 
     * @%x standard date string 
     * @%X standard time string 
     * @%y year in decimal, without the century (0-99) 
     * @%Y year in decimal, with the century 
     * @%Z time zone name 
     * %% a percent sign 
     * </pre>
     *
     * @param fmt Datetime format
     *
     * @endif
     */
    void setDateFormat(const char* format);
    
    /*!
     * @if jp
     *
     * @brief �إå��������θ���ղä���ʸ��������ꤹ�롣
     *
     * �إå��������θ���ղä�����Ƭ��ʸ��������ꤹ�롣
     *
     * @param suffix ��Ƭ��ʸ����
     *
     * @else
     *
     * @brief Set suffix of date/time string of header.
     *
     * Set the suffix string added after the datatime of the header.
     *
     * @param suffix Suffix string
     *
     * @endif
     */
    void setName(const char* name);

  protected:
    /*!
     * @if jp
     *
     * @brief ��å������Υץ�ե��å����ɲôؿ�
     *
     * ���֥��饹�ˤ����Ƥ��δؿ��򥪡��С��饤�ɤ���
     * ����å�������Ŭ���ʥץ�ե��å�������ɲä��롣
     *
     * @else
     *
     * @brief Message prefix appender function
     *
     * Subclasses of this class should override this operation, and
     * this function should be defined to append some prefix to the
     * log messages.
     *
     * @endif
     */
    virtual void header(int level);

    /*!
     * @if jp
     * @brief �ե����ޥåȤ��줿��������ʸ�����������롣
     * ���ꤵ�줿�񼰤ǵ��Ҥ�������������������롣
     *
     * @return �񼰻��긽������
     *
     * @else
     * @brief Get the current formatted date/time string
     * Get the current datetime described by specified format.
     *
     * @return Format specification current datetime
     *
     * @endif
     */
    std::string getDate(void);

    /*!
     * @if jp
     * @brief ����٥�����
     * Ϳ����줿ʸ������б���������٥�����ꤹ�롣
     *
     * @param lv ����٥�ʸ����
     * @return ���ꤷ������٥�
     *
     * @else
     * @brief Set the log level
     * Set the log level corresponding to the given string.
     *
     * @param lv Log level string
     * @return The set log level
     *
     * @endif
     */
    int strToLevel(const char* level);

  private:
    std::string m_name;
    std::string m_dateFormat;
    static const char* m_levelString[];
    int m_msEnable;
    int m_usEnable;
  };    


#ifndef NO_LOGGING
/*!
 * @if jp
 *
 * @brief ���ѥ����ϥޥ���
 *
 * ����٥뤪��ӽ��ϥե����ޥå�ʸ���������Ȥ��ƤȤ롣
 *
 * @else
 *
 * @brief General-purpose log output macro
 *
 * Lock log level and output format string as arguments.
 *
 * @endif
 */
#define RTC_LOG(LV, fmt)			            \
  if (rtclog.isValid(LV))                                   \
    {                                                       \
      std::string str = ::coil::sprintf fmt;                \
      rtclog.lock();                                        \
      rtclog.level(LV) << str << std::endl; \
      rtclog.unlock();                                      \
    }

#define RTC_LOG_STR(LV, str)			            \
  if (rtclog.isValid(LV))                                   \
    {                                                       \
      rtclog.lock();                                        \
      rtclog.level(LV) << str << std::endl;  \
      rtclog.unlock();                                      \
    }

   /*!
   * @if jp
   *
   * @brief ���顼�����ϥޥ���
   *
   * ���顼��٥�Υ����ϥޥ���<BR>����٥뤬
   * ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Error log output macro
   *
   * This is a log output macro of the error level.
   * If log levels are ERROR, WARN, INFO, NORMAL, DEBUG, TRACE,
   * VERBOSE or PARANOID, message will be output to log.
   *
   * @endif
   */
#define RTC_FATAL(fmt) RTC_LOG(::RTC::Logger::RTL_FATAL, fmt)
#define RTC_FATAL_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_FATAL, str)
 
  /*!
   * @if jp
   *
   * @brief ���顼�����ϥޥ���
   *
   * ���顼��٥�Υ����ϥޥ���<BR>����٥뤬
   * ERROR, WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Error log output macro
   *
   * This is a log output macro of the error level.
   * If log levels are ERROR, WARN, INFO, NORMAL, DEBUG, TRACE,
   * VERBOSE or PARANOID, message will be output to log.
   *
   * @endif
   */
#define RTC_ERROR(fmt) RTC_LOG(::RTC::Logger::RTL_ERROR, fmt)
#define RTC_ERROR_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_ERROR, str)
  
  /*!
   * @if jp
   *
   * @brief ��˥󥰥����ϥޥ���
   *
   * ��˥󥰥�٥�Υ����ϥޥ���<BR>����٥뤬
   * ( WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Warning log output macro
   *
   * If log levels are
   * ( WARN, INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_WARN(fmt) RTC_LOG(::RTC::Logger::RTL_WARN, fmt)
#define RTC_WARN_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_WARN, str)
  
  /*!
   * @if jp
   *
   * @brief ����ե������ϥޥ���
   *
   * ����ե���٥�Υ����ϥޥ���<BR>����٥뤬
   * ( INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Information level log output macro
   *
   *  If log levels are
   * ( INFO, NORMAL, DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_INFO(fmt) RTC_LOG(::RTC::Logger::RTL_INFO, fmt)
#define RTC_INFO_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_INFO, str)

  /*!
   * @if jp
   *
   * @brief �ǥХå������ϥޥ���
   *
   * �ǥХå���٥�Υ����ϥޥ���<BR>����٥뤬
   * ( DEBUG, TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Debug level log output macro.
   *
   * If log levels are
   * ( DEBUG, TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_DEBUG(fmt) RTC_LOG(::RTC::Logger::RTL_DEBUG, fmt)
#define RTC_DEBUG_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_DEBUG, str)
  
  /*!
   * @if jp
   *
   * @brief �ȥ졼�������ϥޥ���
   *
   * �ȥ졼����٥�Υ����ϥޥ���<BR>����٥뤬
   * ( TRACE, VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Trace level log output macro.
   *
   * If log levels are
   * ( TRACE, VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_TRACE(fmt) RTC_LOG(::RTC::Logger::RTL_TRACE, fmt)
#define RTC_TRACE_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_TRACE, str)


  /*!
   * @if jp
   *
   * @brief �٥�ܡ��������ϥޥ���
   *
   * �٥�ܡ�����٥�Υ����ϥޥ���<BR>����٥뤬
   * ( VERBOSE, PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Verbose level log output macro.
   *
   * If log levels are
   * ( VERBOSE, PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_VERBOSE(fmt) RTC_LOG(::RTC::Logger::RTL_VERBOSE, fmt)
#define RTC_VERBOSE_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_VERBOSE, str)
  
  /*!
   * @if jp
   *
   * @brief �ѥ�Υ��ɥ����ϥޥ���
   *
   * �ѥ�Υ��ɥ�٥�Υ����ϥޥ���<BR>����٥뤬
   * ( PARANOID )
   * �ξ��˥����Ϥ���롣
   *
   * @else
   *
   * @brief Paranoid level log output macro.
   *
   * If log levels are
   * ( PARANOID ),
   * message will be output to log.
   *
   * @endif
   */
#define RTC_PARANOID(fmt) RTC_LOG(::RTC::Logger::RTL_PARANOID, fmt)
#define RTC_PARANOID_STR(str) RTC_LOG_STR(::RTC::Logger::RTL_PARANOID, str)
  
#else
#define RTC_ERROR(fmt)
#define RTC_ERROR_STR(str)
#define RTC_WARN(fmt)
#define RTC_WARN_STR(str)
#define RTC_NORMAL(fmt)
#define RTC_NORMAL_STR(str)
#define RTC_INFO(fmt)
#define RTC_INFO_STR(str)
#define RTC_DEBUG(fmt)
#define RTC_DEBUG_STR(str)
#define RTC_TRACE(fmt)
#define RTC_TRACE_STR(str)
#define RTC_VERBOSE(fmt)
#define RTC_VERBOSE_STR(str)
#define RTC_PARANOID(fmt)
#define RTC_PARANOID_STR(str)
#endif
  
}; // namespace RTC

#endif  // RTC_SYSTEMLOGGER_H
