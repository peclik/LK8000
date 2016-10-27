/*
 * LK8000 Tactical Flight Computer -  WWW.LK8000.IT
 * Released under GNU/GPL License v.2
 * See CREDITS.TXT file for authors and copyrights
 *
 * File:   resource_data.h
 * Author: Bruno de Lacheisserie
 *
 * Created on 18 septembre 2014, 13:34
 */
#ifndef resource_data_h
#define	resource_data_h

#include "Util/ConstBuffer.hpp"
#include <string.h>

// for avoid uneeded copy when data is string, all resource are null termined!

#define BIN_DATA(_NAME) \
    extern const unsigned char _NAME##_begin[]; \
    extern const unsigned char _NAME##_end[]; \
    extern const unsigned int _NAME##_size;

// XMLDIALOG
#ifndef WIN32_RESOURCE

BIN_DATA(IDR_XML_MULTISELECTLIST_L)
BIN_DATA(IDR_XML_MULTISELECTLIST_P)
BIN_DATA(IDR_XML_AIRSPACE_L)
BIN_DATA(IDR_XML_AIRSPACE_P)
BIN_DATA(IDR_XML_AIRSPACECOLOURS_L)
BIN_DATA(IDR_XML_AIRSPACECOLOURS_P)
#ifdef HAVE_HATCHED_BRUSH
BIN_DATA(IDR_XML_AIRSPACEPATTERNS_L)
BIN_DATA(IDR_XML_AIRSPACEPATTERNS_P)
#endif
BIN_DATA(IDR_XML_ANALYSIS_L)
BIN_DATA(IDR_XML_ANALYSIS_P)
BIN_DATA(IDR_XML_BASICSETTINGS_L)
BIN_DATA(IDR_XML_BASICSETTINGS_P)
BIN_DATA(IDR_XML_CHECKLIST_L)
BIN_DATA(IDR_XML_CHECKLIST_P)
BIN_DATA(IDR_XML_LOGGERREPLAY)
BIN_DATA(IDR_XML_STARTUP_L)
BIN_DATA(IDR_XML_STARTUP_P)
BIN_DATA(IDR_XML_DUALPROFILE_L)
BIN_DATA(IDR_XML_DUALPROFILE_P)
BIN_DATA(IDR_XML_ORACLE_L)
BIN_DATA(IDR_XML_ORACLE_P)
BIN_DATA(IDR_XML_TASKOVERVIEW_L)
BIN_DATA(IDR_XML_TASKOVERVIEW_P)
BIN_DATA(IDR_XML_FLYSIM_P)
BIN_DATA(IDR_XML_FLYSIM_L)
BIN_DATA(IDR_XML_STATUS)
BIN_DATA(IDR_XML_TASKCALCULATOR)
BIN_DATA(IDR_XML_TASKWAYPOINT_P)
BIN_DATA(IDR_XML_WAYPOINTDETAILS_P)
BIN_DATA(IDR_XML_WAYPOINTSELECT_P)
BIN_DATA(IDR_XML_WAYPOINTQUICK_L)
BIN_DATA(IDR_XML_WAYPOINTQUICK_P)
BIN_DATA(IDR_XML_WINDSETTINGS)
BIN_DATA(IDR_XML_STARTTASK)
BIN_DATA(IDR_XML_TIMEGATES)
BIN_DATA(IDR_XML_TOPOLOGY)
BIN_DATA(IDR_XML_CUSTOMKEYS)
BIN_DATA(IDR_XML_BOTTOMBAR)
BIN_DATA(IDR_XML_INFOPAGES)
BIN_DATA(IDR_XML_WAYPOINTTERRAIN)
BIN_DATA(IDR_XML_LKAIRSPACEWARNING_P)
BIN_DATA(IDR_XML_LKAIRSPACEWARNING_L)
BIN_DATA(IDR_XML_HELP_P)
BIN_DATA(IDR_XML_TEXTENTRY_KEYBOARD_P)
BIN_DATA(IDR_XML_TEXTENTRY_KEYBOARD_L)
BIN_DATA(IDR_XML_TEAMCODE)
BIN_DATA(IDR_XML_STARTPOINT_P)
BIN_DATA(IDR_XML_WAYPOINTEDIT_P)
BIN_DATA(IDR_XML_TARGET_P)
BIN_DATA(IDR_XML_TASKRULES)
BIN_DATA(IDR_XML_AIRSPACEDETAILS)
BIN_DATA(IDR_XML_LKTRAFFICDETAILS)
BIN_DATA(IDR_XML_THERMALDETAILS)
BIN_DATA(IDR_XML_CHECKLIST_L)
BIN_DATA(IDR_XML_WAYPOINTDETAILS_L)
BIN_DATA(IDR_XML_ANALYSIS_L)
BIN_DATA(IDR_XML_HELP_L)
BIN_DATA(IDR_XML_STARTPOINT_L)
BIN_DATA(IDR_XML_WAYPOINTSELECT_L)
BIN_DATA(IDR_XML_TASKWAYPOINT_L)
BIN_DATA(IDR_XML_STARTUP_L)
BIN_DATA(IDR_XML_DUALPROFILE_L)
BIN_DATA(IDR_XML_WAYPOINTEDIT_L)
BIN_DATA(IDR_XML_AIRSPACESELECT_P)
BIN_DATA(IDR_XML_AIRSPACESELECT_L)
BIN_DATA(IDR_XML_TARGET_L)
BIN_DATA(IDR_XML_COMBOPICKER_L)
BIN_DATA(IDR_XML_COMBOPICKER_P)
BIN_DATA(IDR_XML_PROFILES)
BIN_DATA(IDR_XML_AIRSPACEWARNINGPARAMS)

BIN_DATA(IDR_XML_CONFIGURATION_P)
BIN_DATA(IDR_XML_CONFIGURATION_L)
BIN_DATA(IDR_XML_CONFIGAIRCRAFT_P)
BIN_DATA(IDR_XML_CONFIGAIRCRAFT_L)
BIN_DATA(IDR_XML_CONFIGPILOT_P)
BIN_DATA(IDR_XML_CONFIGPILOT_L)
BIN_DATA(IDR_XML_CONFIGDEVICE_P)
BIN_DATA(IDR_XML_CONFIGDEVICE_L)

BIN_DATA(IDR_XML_NUMENTRY_KEYBOARD_L)
BIN_DATA(IDR_XML_NUMENTRY_KEYBOARD_P)

BIN_DATA(IDR_XML_WAYPOINTEDITUTM_P)
BIN_DATA(IDR_XML_WAYPOINTEDITUTM_L)

BIN_DATA(IDR_XML_CUSTOMMENU)
BIN_DATA(IDR_XML_OVERLAYS)
BIN_DATA(IDR_XML_MULTIMAPS)

BIN_DATA(IDR_XML_DEVCPROBE)

BIN_DATA(IDR_XML_BLUETOOTH_P)
BIN_DATA(IDR_XML_BLUETOOTH_L)

BIN_DATA(IDR_XML_IGCFILE_P)
BIN_DATA(IDR_XML_IGCFILE_L)

BIN_DATA(IDR_XML_BLUEFLYCONFIG_L)
BIN_DATA(IDR_XML_BLUEFLYCONFIG_P)

BIN_DATA(IDR_XML_TERMINAL_L)
BIN_DATA(IDR_XML_TERMINAL_P)

BIN_DATA(IDR_XML_PROGRESS_P)
BIN_DATA(IDR_XML_PROGRESS_L)

BIN_DATA(IDR_RASTER_EGM96S)

BIN_DATA(IDR_XML_RADIOSETTINGS)

#endif

#ifndef WIN32
// on win32 platform, Bitmap can't be in unix style resource.
BIN_DATA(IDB_EMPTY)
BIN_DATA(IDB_TOWN)
BIN_DATA(IDB_LKSMALLTOWN)
BIN_DATA(IDB_LKVERYSMALLTOWN)

#ifndef DISABLEAUDIO

    BIN_DATA(IDR_WAV_MM0)
    BIN_DATA(IDR_WAV_MM1)
    BIN_DATA(IDR_WAV_MM2)
    BIN_DATA(IDR_WAV_MM3)
    BIN_DATA(IDR_WAV_MM4)
    BIN_DATA(IDR_WAV_MM5)
    BIN_DATA(IDR_WAV_MM6)

    BIN_DATA(IDR_WAV_DRIP)
    BIN_DATA(IDR_WAV_CLICK)
    BIN_DATA(IDR_WAV_HIGHCLICK)

    BIN_DATA(IDR_WAV_TONE1)
    BIN_DATA(IDR_WAV_TONE2)
    BIN_DATA(IDR_WAV_TONE3)
    BIN_DATA(IDR_WAV_TONE4)
    BIN_DATA(IDR_WAV_TONE7)

    BIN_DATA(IDR_WAV_BTONE2)
    BIN_DATA(IDR_WAV_BTONE4)
    BIN_DATA(IDR_WAV_BTONE5)
    BIN_DATA(IDR_WAV_BTONE6)
    BIN_DATA(IDR_WAV_BTONE7)

	BIN_DATA(IDR_WAV_OVERTONE0)
    BIN_DATA(IDR_WAV_OVERTONE1)
    BIN_DATA(IDR_WAV_OVERTONE2)
    BIN_DATA(IDR_WAV_OVERTONE3)
    BIN_DATA(IDR_WAV_OVERTONE4)
    BIN_DATA(IDR_WAV_OVERTONE5)
    BIN_DATA(IDR_WAV_OVERTONE6)
    BIN_DATA(IDR_WAV_OVERTONE7)
#endif

#endif

#include <tchar.h>
#include "resource.h"
#define RESOURCE_ID(_NAME)  #_NAME
#define NAMED_RESOURCE(_NAME) { _TEXT(RESOURCE_ID(_NAME)) , ConstBuffer<void>(_NAME##_begin, _NAME##_size) }
#ifndef WIN32_RESOURCE
static const struct {
    const TCHAR * szName;
    ConstBuffer<void> data;
} named_resources[] = {

    NAMED_RESOURCE(IDR_XML_AIRSPACE_P),
    NAMED_RESOURCE(IDR_XML_AIRSPACECOLOURS_P),
    NAMED_RESOURCE(IDR_XML_MULTISELECTLIST_P),
    NAMED_RESOURCE(IDR_XML_MULTISELECTLIST_L),

#ifdef HAVE_HATCHED_BRUSH
    NAMED_RESOURCE(IDR_XML_AIRSPACEPATTERNS_P),
    NAMED_RESOURCE(IDR_XML_AIRSPACEPATTERNS_L),
#endif // HAVE_HATCHED_BRUSH

    NAMED_RESOURCE(IDR_XML_ANALYSIS_P),
    NAMED_RESOURCE(IDR_XML_BASICSETTINGS_P),
    NAMED_RESOURCE(IDR_XML_BASICSETTINGS_L),
    NAMED_RESOURCE(IDR_XML_CHECKLIST_P),
    NAMED_RESOURCE(IDR_XML_LOGGERREPLAY),
    NAMED_RESOURCE(IDR_XML_STARTUP_P),
    NAMED_RESOURCE(IDR_XML_DUALPROFILE_P),
    NAMED_RESOURCE(IDR_XML_ORACLE_P),
    NAMED_RESOURCE(IDR_XML_ORACLE_L),
    NAMED_RESOURCE(IDR_XML_FLYSIM_P),
    NAMED_RESOURCE(IDR_XML_FLYSIM_L),
    NAMED_RESOURCE(IDR_XML_STATUS),
    NAMED_RESOURCE(IDR_XML_TASKCALCULATOR),
    NAMED_RESOURCE(IDR_XML_TASKOVERVIEW_P),
    NAMED_RESOURCE(IDR_XML_TASKWAYPOINT_P),
    NAMED_RESOURCE(IDR_XML_WAYPOINTDETAILS_P),
    NAMED_RESOURCE(IDR_XML_WAYPOINTSELECT_P),
    NAMED_RESOURCE(IDR_XML_WAYPOINTQUICK_L),
    NAMED_RESOURCE(IDR_XML_WAYPOINTQUICK_P),
    NAMED_RESOURCE(IDR_XML_WINDSETTINGS),
    NAMED_RESOURCE(IDR_XML_STARTTASK),
    NAMED_RESOURCE(IDR_XML_TIMEGATES),
    NAMED_RESOURCE(IDR_XML_TOPOLOGY),
    NAMED_RESOURCE(IDR_XML_CUSTOMKEYS),
    NAMED_RESOURCE(IDR_XML_BOTTOMBAR),
    NAMED_RESOURCE(IDR_XML_INFOPAGES),
    NAMED_RESOURCE(IDR_XML_WAYPOINTTERRAIN),
    NAMED_RESOURCE(IDR_XML_LKAIRSPACEWARNING_P),
    NAMED_RESOURCE(IDR_XML_LKAIRSPACEWARNING_L),
    NAMED_RESOURCE(IDR_XML_HELP_P),
    NAMED_RESOURCE(IDR_XML_TEXTENTRY_KEYBOARD_P),
    NAMED_RESOURCE(IDR_XML_TEXTENTRY_KEYBOARD_L),
    NAMED_RESOURCE(IDR_XML_TEAMCODE),
    NAMED_RESOURCE(IDR_XML_STARTPOINT_P),
    NAMED_RESOURCE(IDR_XML_WAYPOINTEDIT_P),
    NAMED_RESOURCE(IDR_XML_TARGET_P),
    NAMED_RESOURCE(IDR_XML_TASKRULES),
    NAMED_RESOURCE(IDR_XML_AIRSPACEDETAILS),
    NAMED_RESOURCE(IDR_XML_LKTRAFFICDETAILS),
    NAMED_RESOURCE(IDR_XML_THERMALDETAILS),
    NAMED_RESOURCE(IDR_XML_CHECKLIST_L),
    NAMED_RESOURCE(IDR_XML_WAYPOINTDETAILS_L),
    NAMED_RESOURCE(IDR_XML_ANALYSIS_L),
    NAMED_RESOURCE(IDR_XML_HELP_L),
    NAMED_RESOURCE(IDR_XML_AIRSPACE_L),
    NAMED_RESOURCE(IDR_XML_AIRSPACECOLOURS_L),
    NAMED_RESOURCE(IDR_XML_STARTPOINT_L),
    NAMED_RESOURCE(IDR_XML_WAYPOINTSELECT_L),
    NAMED_RESOURCE(IDR_XML_TASKOVERVIEW_L),
    NAMED_RESOURCE(IDR_XML_TASKWAYPOINT_L),
    NAMED_RESOURCE(IDR_XML_STARTUP_L),
    NAMED_RESOURCE(IDR_XML_DUALPROFILE_L),
    NAMED_RESOURCE(IDR_XML_WAYPOINTEDIT_L),
    NAMED_RESOURCE(IDR_XML_AIRSPACESELECT_P),
    NAMED_RESOURCE(IDR_XML_AIRSPACESELECT_L),
    NAMED_RESOURCE(IDR_XML_TARGET_L),
    NAMED_RESOURCE(IDR_XML_COMBOPICKER_L),
    NAMED_RESOURCE(IDR_XML_COMBOPICKER_P),
    NAMED_RESOURCE(IDR_XML_PROFILES),
    NAMED_RESOURCE(IDR_XML_AIRSPACEWARNINGPARAMS),

    NAMED_RESOURCE(IDR_XML_CONFIGURATION_P),
    NAMED_RESOURCE(IDR_XML_CONFIGURATION_L),
    NAMED_RESOURCE(IDR_XML_CONFIGAIRCRAFT_P),
    NAMED_RESOURCE(IDR_XML_CONFIGAIRCRAFT_L),
    NAMED_RESOURCE(IDR_XML_CONFIGPILOT_P),
    NAMED_RESOURCE(IDR_XML_CONFIGPILOT_L),
    NAMED_RESOURCE(IDR_XML_CONFIGDEVICE_P),
    NAMED_RESOURCE(IDR_XML_CONFIGDEVICE_L),

    NAMED_RESOURCE(IDR_XML_NUMENTRY_KEYBOARD_L),
    NAMED_RESOURCE(IDR_XML_NUMENTRY_KEYBOARD_P),
    NAMED_RESOURCE(IDR_XML_WAYPOINTEDITUTM_P),
    NAMED_RESOURCE(IDR_XML_WAYPOINTEDITUTM_L),
    NAMED_RESOURCE(IDR_XML_CUSTOMMENU),
    NAMED_RESOURCE(IDR_XML_OVERLAYS),
    NAMED_RESOURCE(IDR_XML_MULTIMAPS),
    NAMED_RESOURCE(IDR_XML_DEVCPROBE),
    NAMED_RESOURCE(IDR_XML_BLUETOOTH_P),
    NAMED_RESOURCE(IDR_XML_BLUETOOTH_L),
    NAMED_RESOURCE(IDR_XML_IGCFILE_P),
    NAMED_RESOURCE(IDR_XML_IGCFILE_L),
    NAMED_RESOURCE(IDR_XML_BLUEFLYCONFIG_L),
    NAMED_RESOURCE(IDR_XML_BLUEFLYCONFIG_P),
    NAMED_RESOURCE(IDR_XML_TERMINAL_P),
    NAMED_RESOURCE(IDR_XML_TERMINAL_L),
    NAMED_RESOURCE(IDR_XML_PROGRESS_P),
    NAMED_RESOURCE(IDR_XML_PROGRESS_L),
    NAMED_RESOURCE(IDR_XML_RADIOSETTINGS),


#ifndef WIN32
    // on win32 platform, Bitmap can't be in unix style resource.
    NAMED_RESOURCE(IDB_EMPTY),
    NAMED_RESOURCE(IDB_TOWN),
    NAMED_RESOURCE(IDB_LKSMALLTOWN),
    NAMED_RESOURCE(IDB_LKVERYSMALLTOWN),

#ifndef DISABLEAUDIO

    NAMED_RESOURCE(IDR_WAV_MM0),
    NAMED_RESOURCE(IDR_WAV_MM1),
    NAMED_RESOURCE(IDR_WAV_MM2),
    NAMED_RESOURCE(IDR_WAV_MM3),
    NAMED_RESOURCE(IDR_WAV_MM4),
    NAMED_RESOURCE(IDR_WAV_MM5),
    NAMED_RESOURCE(IDR_WAV_MM6),

    NAMED_RESOURCE(IDR_WAV_DRIP),
    NAMED_RESOURCE(IDR_WAV_CLICK),
    NAMED_RESOURCE(IDR_WAV_HIGHCLICK),

    NAMED_RESOURCE(IDR_WAV_TONE1),
    NAMED_RESOURCE(IDR_WAV_TONE2),
    NAMED_RESOURCE(IDR_WAV_TONE3),
    NAMED_RESOURCE(IDR_WAV_TONE4),
    NAMED_RESOURCE(IDR_WAV_TONE7),

    NAMED_RESOURCE(IDR_WAV_BTONE2),
    NAMED_RESOURCE(IDR_WAV_BTONE4),
    NAMED_RESOURCE(IDR_WAV_BTONE5),
    NAMED_RESOURCE(IDR_WAV_BTONE6),
    NAMED_RESOURCE(IDR_WAV_BTONE7),

	NAMED_RESOURCE(IDR_WAV_OVERTONE0),
    NAMED_RESOURCE(IDR_WAV_OVERTONE1),
    NAMED_RESOURCE(IDR_WAV_OVERTONE2),
    NAMED_RESOURCE(IDR_WAV_OVERTONE3),
    NAMED_RESOURCE(IDR_WAV_OVERTONE4),
    NAMED_RESOURCE(IDR_WAV_OVERTONE5),
    NAMED_RESOURCE(IDR_WAV_OVERTONE6),
    NAMED_RESOURCE(IDR_WAV_OVERTONE7),

#endif // !DISABLEAUDIO

#endif // !WIN32

};


#include <limits>
#include <stdio.h>

#ifdef WIN32
  #include <windows.h>
#endif // WIN32

#ifdef __linux__
  #include "tchar.h"
  #include "types.h"

  #define MAKEINTRESOURCE(i) (const char*)((unsigned long)((uint16_t)(i)))

#endif //__linux__

inline ConstBuffer<void> GetNamedResource(const TCHAR* szName) {

    const TCHAR* szID = szName;
    TCHAR szTmp[10] = {};
    if((ptrdiff_t)szName < (ptrdiff_t)std::numeric_limits<unsigned short>::max()) {
        // we have resource ID
        _stprintf(szTmp, _T("%u"), (unsigned short)(ptrdiff_t)szName);
        szID = szTmp;
    }
    if(szID) {
        for (auto Resource : named_resources) {
            if (_tcscmp(Resource.szName, szID) == 0) {
                return Resource.data;
            }
        }
    }
    assert(false); // ressource not found;
    return ConstBuffer<void>::Null();
}

inline const TCHAR* GetNamedResourceString(const TCHAR* szName) {
    const ConstBuffer<void>& Resource = GetNamedResource(szName);
    const TCHAR* szText = static_cast<const TCHAR*>(Resource.data);
    assert(_tcslen(szText) == (Resource.size/sizeof(TCHAR)));
    return szText;
}

#endif // !WIN32_RESOURCE

#endif	/* resource_data_h */
