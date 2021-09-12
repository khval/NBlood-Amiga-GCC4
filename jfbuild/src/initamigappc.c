
#define __USE_INLINE__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/graphics.h>
#include <proto/gadtools.h>
#include <proto/diskfont.h>
#include <exec/emulation.h>
#include <proto/asl.h>

#include <intuition/imageclass.h>
#include <intuition/gadgetclass.h>

#include "initamigappc.h"

struct Library			*LayersBase = NULL;
struct LayersIFace		*ILayers = NULL;

struct Library			*IntuitionBase = NULL;
struct IntuitionIFace		*IIntuition = NULL;

struct Library			*GraphicsBase = NULL;
struct GraphicsIFace		*IGraphics = NULL;

struct Library			*GadToolsBase = NULL;
struct GadToolsIFace	*IGadTools = NULL;

struct Library			*DiskfontBase = NULL;
struct DiskfontIFace		*IDiskfont = NULL;

struct Library 			 *AslBase = NULL;
struct AslIFace 			 *IAsl = NULL;

struct Library 			 *AHIBase = NULL;
struct AHIIFace 			 *IAHI = NULL;

struct Library 			 *IconBase = NULL;
struct IconIFace 		 *IIcon = NULL;

struct Library 			 *LowLevelBase = NULL;
struct IconIFace 		 *ILowLevel = NULL;



APTR video_mutex = NULL;

struct TextFont *default_font = NULL;

BOOL open_lib( const char *name, int ver , const char *iname, int iver, struct Library **base, struct Interface **interface)
{
	*interface = NULL;
	*base = OpenLibrary( name , ver);

	if (*base)
	{
		 *interface = GetInterface( *base,  iname , iver, TAG_END );
		if (!*interface) Printf("Unable to getInterface %s for %s %ld!\n",iname,name,ver);
	}
	else
	{
	   	Printf("Unable to open the %s %ld!\n",name,ver);
	}
	return (*interface) ? TRUE : FALSE;
}

void close_lib_all( struct Library **Base, struct Interface **I )
{
	if (*Base) CloseLibrary(*Base); *Base = 0;
	if (*I) DropInterface((struct Interface*) *I); *I = 0;
}

bool open_libs()
{
	struct TextAttr _font;

	if ( ! open_lib( "layers.library", 51L , "main", 1, &LayersBase, (struct Interface **) &ILayers ) ) return FALSE;
	if ( ! open_lib( "intuition.library", 51L , "main", 1, &IntuitionBase, (struct Interface **) &IIntuition  ) ) return FALSE;
	if ( ! open_lib( "graphics.library", 54L , "main", 1, &GraphicsBase, (struct Interface **) &IGraphics  ) ) return FALSE;
	if ( ! open_lib( "diskfont.library", 53L , "main", 1, &DiskfontBase, (struct Interface **) &IDiskfont  ) ) return FALSE;
	if ( ! open_lib( "gadtools.library", 53L , "main", 1, &GadToolsBase, (struct Interface **) &IGadTools  ) ) return FALSE;
	if ( ! open_lib( "asl.library", 53L , "main", 1, &AslBase, (struct Interface **) &IAsl  ) ) return FALSE;
	if ( ! open_lib( "icon.library", 53L , "main", 1, &AslBase, (struct Interface **) &IAsl  ) ) return FALSE;


	video_mutex = (APTR) AllocSysObjectTags(ASOT_MUTEX, TAG_DONE);
	if ( ! video_mutex) return FALSE;

	_font.ta_Name = "topaz.font";
	_font.ta_YSize = 8;
	_font.ta_Style = 0;
	_font.ta_Flags = 0;

	default_font = OpenDiskFont( &_font );
	if ( !default_font ) return FALSE;

	return TRUE;
}

void close_libs()
{
	if (default_font)
	{
		CloseFont( default_font );
		default_font = NULL;
	}

	if (video_mutex) 
	{
		FreeSysObject(ASOT_MUTEX, video_mutex); 
		video_mutex = NULL;
	}

	close_lib(AHI);
	close_lib(Asl);
	close_lib(GadTools);
	close_lib(Diskfont);
	close_lib(Layers);
	close_lib(Intuition);
	close_lib(Graphics);
}

struct Gadeget *add_window_button(struct Window *window, struct Image *img, ULONG id)
{
	struct Gadeget *retGad = NULL;

	if (img)
	{
		retGad = (struct Gadeget *) NewObject(NULL , "buttongclass", 
			GA_ID, id, 
			GA_RelVerify, TRUE, 
			GA_Image, img, 
			GA_TopBorder, TRUE, 
			GA_RelRight, 0, 
			GA_Titlebar, TRUE, 
			TAG_END);

		if (retGad)
		{
			AddGadget( window, (struct Gadget *) retGad, ~0 );
		}
	}

	return retGad;
}

void open_icon(struct Window *window,struct DrawInfo *dri, ULONG imageID, ULONG gadgetID, struct kIcon *icon )
{
	icon -> image = (struct Image *) NewObject(NULL, "sysiclass", SYSIA_DrawInfo, dri, SYSIA_Which, imageID, TAG_END );
	if (icon -> image)
	{
		icon -> gadget = add_window_button( window, icon -> image, gadgetID);
	}
}

void dispose_icon(struct Window *win, struct kIcon *icon)
{
	if (icon -> gadget)
	{
		RemoveGadget( win, (struct Gadget *) icon -> gadget );
		icon -> gadget = NULL;
	}

	if (icon -> image)
	{
		DisposeObject( (Object *) icon -> image );
		icon -> image = NULL;
	}
}


