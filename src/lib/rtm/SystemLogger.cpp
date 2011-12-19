// -*- C++ -*-
/*!
 * @file SystemLogger.cpp
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
 * $Id: SystemLogger.cpp 845 2008-09-25 11:10:40Z n-ando $
 *
 */

#include <rtm/SystemLogger.h>
#include <rtm/Manager.h>

#if defined(_MSC_VER)
#define snprintf _snprintf
#endif

namespace RTC
{
  const char* Logger::m_levelString[] =
    {
      " SILENT: ",
      " FATAL: ",
      " ERROR: ",
      " WARNING: ",
      " INFO: ",
      " DEBUG: ",
      " TRACE: ",
      " VERBOSE: ",
      " PARANOID: "
    };

  Logger::Logger(const char* name)
    : ::coil::LogStream(&(Manager::instance().getLogStreamBuf()),
                        RTL_SILENT, RTL_PARANOID, RTL_SILENT),
      m_name(name), m_dateFormat("%b %d %H:%M:%S.%Q"),
      m_msEnable(0), m_usEnable(0)
  {
    setLevel(Manager::instance().getLogLevel().c_str());
    m_msEnable = coil::replaceString(m_dateFormat, "%Q", "#m#");
    m_usEnable = coil::replaceString(m_dateFormat, "%q", "#u#");
  }

  Logger::Logger(LogStreamBuf* streambuf)
    : ::coil::LogStream(streambuf,
                        RTL_SILENT, RTL_PARANOID,  RTL_SILENT),
      m_name("unknown"), m_dateFormat("%b %d %H:%M:%S.%Q"),
      m_msEnable(0), m_usEnable(0)
  {
    m_msEnable = coil::replaceString(m_dateFormat, "%Q", "#m#");
    m_usEnable = coil::replaceString(m_dateFormat, "%q", "#u#");
  }

  Logger::~Logger(void)
  {
  }

  /*!
   * @if jp
   * @brief ����٥��ʸ��������ꤹ��
   * @else
   * @brief Set log level by string
   * @endif
   */
  bool Logger::setLevel(const char* level)
  {
    return coil::LogStream::setLevel(strToLevel(level));
  }

  /*!
   * @if jp
   * @brief �إå����ղä��������ե����ޥåȤ���ꤹ�롣
   * @else
   * @brief Set date/time format for adding the header
   * @endif
   */
  void Logger::setDateFormat(const char* format)
  {
    m_dateFormat = std::string(format);
    m_msEnable = coil::replaceString(m_dateFormat, "%Q", "#m#");
    m_usEnable = coil::replaceString(m_dateFormat, "%q", "#u#");
  }

  /*!
   * @if jp
   * @brief �إå��������θ���ղä���ʸ��������ꤹ�롣
   * @else
   * @brief Set suffix of date/time string of header.
   * @endif
   */
  void Logger::setName(const char* name)
  {
    m_name = name;
  }

  /*!
   * @if jp
   * @brief ��å������Υץ�ե��å����ɲôؿ�
   * @else
   * @brief Message prefix appender function
   * @endif
   */
  void Logger::header(int level)
  {
    *this << getDate() + m_levelString[level] + m_name + ": ";
  }

  /*!
   * @if jp
   * @brief �ե����ޥåȤ��줿��������ʸ�����������롣
   * @else
   * @brief Get the current formatted date/time string
   * @endif
   */
  std::string Logger::getDate(void)
  {
    const int maxsize = 256;
    char buf[maxsize];
    coil::TimeValue tm(coil::gettimeofday());

    time_t timer;
    struct tm* date;

    timer = tm.sec();
    date = gmtime(&timer);
      
    strftime(buf, sizeof(buf), m_dateFormat.c_str(), date);
    std::string fmt(buf);

    if (m_msEnable > 0)
      {
        char msec[4];
#ifdef WIN32
        _snprintf(msec, 4, "%03d", (int)(tm.usec() / 1000));
#else
        snprintf(msec, 4, "%03d", (int)(tm.usec() / 1000));
#endif
        coil::replaceString(fmt, "#m#", msec);
      }
    if (m_usEnable > 0)
      {
        char usec[4];
#ifdef WIN32
        _snprintf(usec, 4, "%03d",
                 (int)(tm.usec() - ((tm.usec() / 1000) * 1000)));
#else
        snprintf(usec, 4, "%03d",
                 (int)(tm.usec() - ((tm.usec() / 1000) * 1000)));
#endif
        coil::replaceString(fmt, "#u#", usec);
      }

    return fmt;
  }

  /*!
   * @if jp
   * @brief ����٥�����
   * @else
   * @brief Set the log level
   * @endif
   */
  int Logger::strToLevel(const char* level)
  {
    std::string lv(level);
    if      (lv == "SILENT")
      return RTL_SILENT;
    else if (lv == "FATAL")
      return RTL_FATAL;
    else if (lv == "ERROR")
      return RTL_ERROR;
    else if (lv == "WARN")
      return RTL_WARN;
    else if (lv == "INFO")
      return RTL_INFO;
    else if (lv == "DEBUG")
      return RTL_DEBUG;
    else if (lv == "TRACE")
      return RTL_TRACE;
    else if (lv == "VERBOSE")
      return RTL_VERBOSE;
    else if (lv == "PARANOID")
      return RTL_PARANOID;
    else
      return RTL_SILENT;
  }

}; // namespace RTC
