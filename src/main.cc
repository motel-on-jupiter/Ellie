/**
 * Copyright (C) 2014 The Motel on Jupiter
 */

#include "core/EllieMain.h"
#include "util/auxiliary/csyntax_aux.h"
#include "util/logging/emitter/DebuggerConsoleLogEmitter.h"
#include "util/logging/emitter/FileLogEmitter.h"
#include "util/logging/Logger.h"
#include "util/wrapper/crtdbg_wrap.h"

#define kDebugAlloc (-1)

int main(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);

#ifdef _MSC_VER
#ifdef _DEBUG
  // Validate the detection for memory leak
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetBreakAlloc(kDebugAlloc);
#endif
#endif

  // Set up logger
  LOGGER.PushEmitter(DEBUGGER_CONSOLE_LOG_EMITTER);
  LOGGER.PushEmitter(STDERR_LOG_EMITTER);

  // Start the main function for Ellie
  return EllieMain();
}
