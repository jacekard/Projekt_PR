#pragma once

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN
static const bool FULL_SCREEN = true;
static const bool VSYNC_ENABLED = true;
static const float SCREEN_DEPTH = 1000.0f;
static const float SCREEN_NEAR = 0.1f;

#include <cstdint>
#include <windows.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include "UtilsConfig.hpp"
#if defined(CONSOLE_VIEW_BUILD)
#include "Console.hpp"
#endif

#include "InputClass.hpp"
#if defined(DIRECTX_VIEW_BUILD)
//#include "SystemClass.hpp"
#endif