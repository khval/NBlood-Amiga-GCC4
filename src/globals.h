//-------------------------------------------------------------------------
/*
Copyright (C) 2010-2019 EDuke32 developers and contributors
Copyright (C) 2019 Nuke.YKT

This file is part of NBlood.

NBlood is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------
#pragma once
#include "compat.h"
#include "build.h"
#include "resource.h"

typedef struct {
    int32 usejoystick;
    int32 usemouse;
    int32 fullscreen;
    int32 xdim;
    int32 ydim;
    int32 bpp;
    int32 forcesetup;
    int32 noautoload;
} ud_setup_t;

extern ud_setup_t gSetup;
extern ClockTicks gFrameClock;
extern ClockTicks gFrameTicks;
extern int gFrame;
//extern ClockTicks gGameClock;
extern int gFrameRate;
extern int32 gGamma;
extern bool bVanilla;

extern Resource gSysRes;
const char *GetVersionString(void);
