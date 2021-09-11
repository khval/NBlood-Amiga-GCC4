/*
 Copyright (C) 2009 Jonathon Fowler <jf@jonof.id.au>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 
 See the GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 
 */

#include "asssys.h"

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
#elif defined(__AROS__) || defined(__AMIGA__)
# include <proto/dos.h>
#else
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
#endif

void ASS_Sleep(int msec)
{
#ifdef _WIN32
	Sleep(msec);
#elif defined(__AROS__) || defined(__AMIGA__)
	//usleep(msec * 1000);
	ULONG ticks = msec / 20;
	if (ticks < 1) ticks = 1;
	Delay(ticks);
#else
	struct timeval tv;

	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
#endif
}
