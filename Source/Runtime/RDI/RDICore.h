#pragma once

#include "Core.h"

#ifdef RDI_EXPORT
#define RDI_API GHOST_DLLEXPORT
#else
#define RDI_API GHOST_DLLIMPORT
#endif

#include "RenderCore/RenderViewport.h"
#include "RenderCore/IRDI.h"