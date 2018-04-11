#pragma once

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN
static const bool FULL_SCREEN = false;
static const bool VSYNC_ENABLED = true;
static const float SCREEN_DEPTH = 1000.0f;
static const float SCREEN_NEAR = 0.1f;

#include <cstdint>
#include <windows.h>
#include <assert.h>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include "UtilsConfig.hpp"
#include "Console.hpp"

#include "InputClass.hpp"
#if defined(DIRECTX_VIEW_BUILD)
#include "GraphicsClass.hpp"
#include "SystemClass.hpp"
#endif