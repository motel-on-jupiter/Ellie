/**
 * Copyright (C) 2014 The Motel on Jupiter
 */
#ifndef CRTDBG_WRAP_H_
#define CRTDBG_WRAP_H_

#ifdef _MSC_VER
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif /* _DEBUG */
#endif /* _MSC_VER */

#endif /* CRTDBG_WRAP_H_ */
