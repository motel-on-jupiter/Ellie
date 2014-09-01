﻿/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <vector>
#include <boost/serialization/singleton.hpp>

class LogEmitter;

#define LOGGER (Logger::get_mutable_instance())

class Logger : public boost::serialization::singleton<Logger> {
 public:
  enum Level {
    kNoneLevel,
    kTrace,
    kDebug,
    kInfo,
    kNotice,
    kWarn,
    kError,
    kCrit,
    kNumLogLevels,
  };

  Logger();
  virtual ~Logger();

  inline void Emit(const char *format, ...);
  inline void Emitv(const char *format, va_list args);
  inline void Emit(Level level, const char *format, ...);
  inline void Emitv(Level level, const char *format, va_list args);

  inline void Trace(const char *format, ...);
  inline void Tracev(const char *format, va_list args);
  inline void Debug(const char *format, ...);
  inline void Debugv(const char *format, va_list args);
  inline void Info(const char *format, ...);
  inline void Infov(const char *format, va_list args);
  inline void Notice(const char *format, ...);
  inline void Noticev(const char *format, va_list args);
  inline void Warn(const char *format, ...);
  inline void Warnv(const char *format, va_list args);
  inline void Error(const char *format, ...);
  inline void Errorv(const char *format, va_list args);
  inline void Crit(const char *format, ...);
  inline void Critv(const char *format, va_list args);

  inline void PushEmitter(LogEmitter &emitter);
  inline void ClearEmitters();

 private:
  static const char *kLogPrefixes[kNumLogLevels];

  std::vector<LogEmitter *> emitters_;
};

#include "Logger.inl"

#endif /* LOGGER_H_ */
