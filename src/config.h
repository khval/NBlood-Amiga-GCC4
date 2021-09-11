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

#ifndef config_public_h_
#define config_public_h_

#include "keyboard.h"
#include "function.h"
#include "control.h"
#include "_control.h"
#include "gamedefs.h"
#ifdef EDUKE32
#include "hash.h"
#endif

#define MAXRIDECULE 10
#define MAXRIDECULELENGTH 40
#define MAXPLAYERNAME 16

extern int32 MouseDeadZone, MouseBias;
extern int32 SmoothInput;
extern int32 MouseFunctions[MAXMOUSEBUTTONS][2];
extern int32 MouseAnalogueAxes[MAXMOUSEAXES];
#ifndef EDUKE32
extern int32 MouseAnalogueScale[MAXMOUSEAXES];
#endif
extern int32 JoystickFunctions[MAXJOYBUTTONSANDHATS][2];
extern int32 JoystickDigitalFunctions[MAXJOYAXES][2];
extern int32 JoystickAnalogueAxes[MAXJOYAXES];
extern int32 JoystickAnalogueScale[MAXJOYAXES];
extern int32 JoystickAnalogueDead[MAXJOYAXES];
extern int32 JoystickAnalogueSaturate[MAXJOYAXES];
extern uint8_t KeyboardKeys[NUMGAMEFUNCTIONS][2];
extern int32 scripthandle;
extern int32 setupread;
extern int32 MusicRestartsOnLoadToggle;
extern int32 configversion;
extern int32 CheckForUpdates;
extern int32 LastUpdateCheck;
extern int32 useprecache;
extern char CommbatMacro[MAXRIDECULE][MAXRIDECULELENGTH];
extern char szPlayerName[MAXPLAYERNAME];
extern int32 gTurnSpeed;
extern int32 gDetail;
extern int32 gAutoAim;
extern int32 gWeaponSwitch;
extern int32 gAutoRun;
extern int32 gViewInterpolate;
extern int32 gViewHBobbing;
extern int32 gViewVBobbing;
extern int32 gFollowMap;
extern int32 gOverlayMap;
extern int32 gRotateMap;
extern int32 gAimReticle;
extern int32 gSlopeTilting;
extern int32 gMessageState;
extern int32 gMessageCount;
extern int32 gMessageTime;
extern int32 gMessageFont;
extern int32 gbAdultContent;
extern char gzAdultPassword[9];
extern int32 gDoppler;
extern int32 gShowPlayerNames;
extern int32 gShowWeapon;
extern int32 gMouseSensitivity;
extern int32 gMouseAiming;
extern int32 gMouseAimingFlipped;
extern int32 gRunKeyMode;
extern bool gNoClip;
extern bool gInfiniteAmmo;
extern bool gFullMap;
#ifdef EDUKE32
extern hashtable_t h_gamefuncs;
#endif
extern int32 gUpscaleFactor;
extern int32 gLevelStats;
extern int32 gPowerupDuration;
extern int32 gShowMapTitle;
extern int32 gFov;
extern int32 gCenterHoriz;
extern int32 gDeliriumBlur;

///////
extern int32 gWeaponsV10x;
//////

int  CONFIG_ReadSetup(void);
void CONFIG_WriteSetup(uint32 flags);
void CONFIG_SetDefaults(void);
void CONFIG_SetupMouse(void);
void CONFIG_SetupJoystick(void);
void CONFIG_SetDefaultKeys(const char (*keyptr)[MAXGAMEFUNCLEN], bool lazy=false);
#ifndef EDUKE32
void CONFIG_SetJoystickDefaults(int style);
#endif

int32 CONFIG_GetMapBestTime(char const *mapname, uint8_t const *mapmd4);
int     CONFIG_SetMapBestTime(uint8_t const *mapmd4, int32 tm);

int32 CONFIG_FunctionNameToNum(const char *func);
char *  CONFIG_FunctionNumToName(int32 func);

int32     CONFIG_AnalogNameToNum(const char *func);
const char *CONFIG_AnalogNumToName(int32 func);

void CONFIG_MapKey(int which, kb_scancode key1, kb_scancode oldkey1, kb_scancode key2, kb_scancode oldkey2);

#endif
