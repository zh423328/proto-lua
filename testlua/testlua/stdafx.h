// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>
using namespace std;

#ifndef CC_SAFE_DELETE
#define CC_SAFE_DELETE(p) if (p){delete p; p = NULL;}
#endif

// TODO: reference additional headers your program requires here
