/**
 * Copyright (C) 2014 The Motel On Jupiter
 */
#ifndef COROUTINE_WRAP_H_
#define COROUTINE_WRAP_H_

#include "external/coroutine.h"

#define ccrAsContParam(var) struct ccrContextTag **ccrParam = (struct ccrContextTag **) &(var)

#define ccrBegin_(x)        if(!x) {x= *ccrParam=(struct ccrContextTag *)malloc(sizeof(*x)); x->ccrLine=0;}\
                            if (x) switch(x->ccrLine) { case 0:;

#endif /* COROUTINE_WRAP_H_ */
