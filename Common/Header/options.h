/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id: options.h,v 8.2 2010/12/15 12:25:23 root Exp root $
*/
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Debug.h"				// DEBUG OPTIONS FOR EVERYONE
#define   MONOCHROME_SCREEN     1             // optimize for monochrom screen

#define   LOGGDEVICEINSTREAM    0             // log device in stream
#define   LOGGDEVCOMMANDLINE    NULL          // device in-stream logger command line
                                              // ie TEXT("-logA=\\Speicherkarte\\logA.log ""-logB=\\SD Card\\logB.log""")

// define this to be true for windows PC port
#if !defined(WINDOWSPC)
#define   WINDOWSPC             0
#endif

#define   FONTQUALITY           NONANTIALIASED_QUALITY

#if (WINDOWSPC>0)
#if _DEBUG
// leak checking
#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
#endif

#define DISABLEAUDIOVARIO

// disable internally generated sounds
//#define DISABLEAUDIO

// no vegavoice support
#undef VEGAVOICE

#ifndef BIGDISPLAY
#define BIGDISPLAY
#endif

#ifdef PNA
#define NOLINETO
#endif

// General OPTIMIZATION for LK8000. Needed for all sub optimization definitions
#define LK8000_OPTIMIZE 	1


// -------------------------------------------------------------
// Activate cache on all calculations defined below:
#ifdef LK8000_OPTIMIZE

 // NEWIBLSCALE  to be used only for NUMBERS between 0 and MAXIBLSCALE !!!!
 #define NEWIBLSCALE	1

 // CACHE CALCULATIONS: IT IS IMPERATIVE THAT THIS OPTION CAN BE DISABLED ANYTIME!
 #define LK_CACHECALC 1
 // Notice:  These are only used if above is active!
 // MacCreadyAltitude and its statistics
 #define LK_CACHECALC_MCA 60
 // #define LK_CACHECALC_MCA_STAT 1

 #define NOFLARMGAUGE	1
 // Old vario gauge for landscape geometry 6
 #define NOVARIOGAUGE	1
 #define NOCDIGAUGE	1
 // no instrument thread
 #define NOINSTHREAD	1

#endif
// -------------------------------------------------------------

#ifdef NEWIBLSCALE
 #define IBLSCALE(x) (   (InfoBoxLayout::IntScaleFlag) ? ((x)*InfoBoxLayout::scale) : ((int)((x)*InfoBoxLayout::dscale)))
 #define NIBLSCALE(x) (LKIBLSCALE[x])
 #define MAXIBLSCALE	100
#else
 #define IBLSCALE(x) (   (InfoBoxLayout::IntScaleFlag) ? ((x)*InfoBoxLayout::scale) : ((int)((x)*InfoBoxLayout::dscale)))
 #define NIBLSCALE(x) (   (InfoBoxLayout::IntScaleFlag) ? ((x)*InfoBoxLayout::scale) : ((int)((x)*InfoBoxLayout::dscale)))
#endif

#define NOWINDREGISTRY	1	// Configurable: load and save wind from registry

// New topology OPTIMIZE options
#ifdef LK8000_OPTIMIZE
 #define TOPOFAST	1
 #define TOPOFASTLABEL	1
 #define TOPOFASTCACHE	1
#endif


// TEMPORARY FIXES THAT REQUIRE EXTENSIVE TESTING - KEEP #ifdef until expiring date
// When expire date is reached, unnecessary old stuff can be removed, even if commented
//

// ------------ NEW AIRSPACE ENGINE -------------------------------------------------
// Using new airspaces requires to change lk8000.rc and activate LKAIRSPACE xmls. 
// They are 2 files in total.
// No need to change any XML filename. Just comment/uncomment.
//
#define LKAIRSPACE		1	// New airspace handling code 

#define ALPHADEBUG		1	// DEBUG STARTUPSTORE MESSAGES FOR ALPHA AND BETA VERSIONS
					// IN FINAL VERSIONS WILL BE DISABLED

#if (WINDOWSPC>0)
#define WINE
#endif

// ------------ NEW OLC ENGINE -------------------------------------------------
// This is permanently enabled as of 2.2 .
// We keep the old olc engine because Mat has made full support for both versions.
// After 2.2 we should remove old stuff.
// Using old OLC requires to change lk8000.rc and activate OLDOLC xmls. 
// They are 3 files in total.
// No need to change any XML filename. Just comment/uncomment.
//
#define NEW_OLC                 1     // Applied 110313 - does not expire
// -----------------------------------------------------------------------------

#define DUALBARO		1	// Handle dual baro feed

#define USEGOINIT		1	// expire 1.7.2011, it is disabled and should be removed


// #define USERLEVEL	1	// old UserLevel configuration expert/basic mode, obsoleted

/*
 * Incomplete work, or stuff that never got into production versions but still interesting

#define NEWTRIGGERGPS	  // Parser approach for triggering a quantum data completed
			  // The idea was correct, since I could verify later that also the real
			  // LX8000 has the same approach, although simplified!!

#define FIXGDI		  // todo, work for further optimization of GDIs. 
			  // To check GDI memory leaks, use the freeware GDIView.exe 

#define LKCLIP		  // replace old Sutherland Hodgman clipping algo
#define NEWUTM		  // New full UTM support INCOMPLETED
#define NOIBOX		  // Ibox mode no more available, an important TODO
#define DSX		  // only an experimental test feature for sms reception

// Very old stuff probably we can clean and remove
#define   EXPERIMENTAL          0             // unused stuff, such like SMS send
#define   AIRSPACEUSEBINFILE    0             // use and maintain binary airspace file

 */

/*
 * All debug options should be put inside Debug.h
 */

#endif
