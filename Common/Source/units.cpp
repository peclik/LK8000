/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2 or later
   See CREDITS.TXT file for authors and copyrights

   $Id: units.cpp,v 8.5 2010/12/13 17:37:35 root Exp root $
*/

//default       EU   UK   US   AUS
//altitude      m    ft   ft   m
//verticalspeed m/s  kts  kts  kts
//wind speed    km/  kts  mp   kts
//IAS           km/  kts  mp   kts
//distance      km   nm   ml   nm


#include "externs.h"
#include "Library/Utm.h"
#include "utils/printf.h"

CoordinateFormats_t Units::CoordinateFormat;

struct UnitDescriptor_t {
  const TCHAR * const Name;
  double  ToUserFact;
  double  ToUserOffset;
};

static UnitDescriptor_t UnitDescriptors[unLastUnit] ={
  {NULL,       1,          0},
  {TEXT("km"), 0.001,      0},
  {TEXT("nm"), 0.00053996, 0},
  {TEXT("mi"), 0.0006214,  0},
  {TEXT("kh"), 0.0036,     0}, // 091219
  {TEXT("kt"), 0.001944,   0},
  {TEXT("mh"), 0.002237,   0},
  {TEXT("ms"), 1.0,        0},
  {TEXT("fm"), 3.281*60.0, 0},
  {TEXT("m"),  1.0,        0},
  {TEXT("ft"), 3.281,      0},
  {TEXT("K"),  1,          0},
  {NULL,       1.0,        -273.15}, // name is contruct by GetUnitName()
  {NULL,       1.8,        -459.67}, // name is contruct by GetUnitName()
  {TEXT("fs"), 3.281,      0} // 100128
};

static Units_t UserDistanceUnit = unKiloMeter;
static Units_t UserAltitudeUnit = unMeter;
static Units_t UserHorizontalSpeedUnit = unKiloMeterPerHour;
static Units_t UserVerticalSpeedUnit = unMeterPerSecond;
static Units_t UserWindSpeedUnit = unKiloMeterPerHour;
static Units_t UserTaskSpeedUnit = unKiloMeterPerHour;

void Units::LongitudeToDMS(double Longitude,
                           int *dd,
                           int *mm,
                           int *ss,
                           bool *east) {

  int sign = Longitude<0 ? 0 : 1;
  Longitude = fabs(Longitude);

  *dd = (int)Longitude;
  Longitude = (Longitude - (*dd)) * 60.0;
  *mm = (int)(Longitude);
  Longitude = (Longitude - (*mm)) * 60.0;
  *ss = (int)(Longitude + 0.5);
  if (*ss >= 60)
    {
      (*mm)++;
      (*ss) -= 60;
    }
  if ((*mm) >= 60)
    {
      (*dd)++;
      (*mm)-= 60;
    }
  *east = (sign==1);
}


void Units::LatitudeToDMS(double Latitude,
                          int *dd,
                          int *mm,
                          int *ss,
                          bool *north) {

  int sign = Latitude<0 ? 0 : 1;
  Latitude = fabs(Latitude);

  *dd = (int)Latitude;
  Latitude = (Latitude - (*dd)) * 60.0;
  *mm = (int)(Latitude);
  Latitude = (Latitude - (*mm)) * 60.0;
  *ss = (int)(Latitude + 0.5);
  if (*ss >= 60) {
    (*mm)++;
    (*ss) -= 60;
  }
  if ((*mm) >= 60) {
    (*dd)++;
    (*mm) -= 60;
  }
  *north = (sign==1);
}

bool Units::CoordinateToString(double Longitude, double Latitude, TCHAR *Buffer, size_t size) {
	if(CoordinateFormat == cfUTM) {
		int utmzone=0;
		char utmchar=0;
		double easting=0, northing=0;
		LatLonToUtmWGS84 ( utmzone, utmchar, easting, northing, Latitude, Longitude );
		_sntprintf(Buffer, size, _T("UTM %d%c  %.0f  %.0f"), utmzone, utmchar, easting, northing);
	} else {
		TCHAR sLongitude[16];
		TCHAR sLatitude[16];

		Units::LongitudeToString(Longitude, sLongitude);
		Units::LatitudeToString(Latitude, sLatitude);

		_sntprintf(Buffer,size,_T("%s  %s"), sLatitude, sLongitude);
	}
	return true;
}


bool Units::LongitudeToString(double Longitude, TCHAR *Buffer, size_t size){

  TCHAR EW[] = TEXT("WE");
  int dd, mm, ss;

  int sign = Longitude<0 ? 0 : 1;
  Longitude = fabs(Longitude);

  switch(CoordinateFormat){
    case cfDDMMSS:
      dd = (int)Longitude;
      Longitude = (Longitude - dd) * 60.0;
      mm = (int)(Longitude);
      Longitude = (Longitude - mm) * 60.0;
      ss = (int)(Longitude + 0.5);
      if (ss >= 60)
        {
          mm++;
          ss -= 60;
        }
      if (mm >= 60)
        {
          dd++;
          mm -= 60;
        }
      _sntprintf(Buffer, size, TEXT("%c%03d%s%02d'%02d\""), EW[sign], dd, MsgToken<2179>(), mm, ss);
    break;
    case cfDDMMSSss:
      dd = (int)Longitude;
      Longitude = (Longitude - dd) * 60.0;
      mm = (int)(Longitude);
      Longitude = (Longitude - mm) * 60.0;
      _sntprintf(Buffer, size, TEXT("%c%03d%s%02d'%05.2f\""), EW[sign], dd, MsgToken<2179>(), mm, Longitude);
    break;
    case cfDDMMmmm:
      dd = (int)Longitude;
      Longitude = (Longitude - dd) * 60.0;
      _sntprintf(Buffer, size, TEXT("%c%03d%s%06.3f'"), EW[sign], dd, MsgToken<2179>(), Longitude);
    break;
    case cfDDdddd:
      _sntprintf(Buffer, size, TEXT("%c%08.4f%s"), EW[sign], Longitude, MsgToken<2179>());
    break;
    case cfUTM:
	_tcscpy(Buffer,_T(""));
	break;
    default:
	LKASSERT(0);
    break;
  }

  return true;

}


bool Units::LatitudeToString(double Latitude, TCHAR *Buffer, size_t size){
  TCHAR EW[] = TEXT("SN");
  int dd, mm, ss;

  int sign = Latitude<0 ? 0 : 1;
  Latitude = fabs(Latitude);

  switch(CoordinateFormat){
    case cfDDMMSS:
      dd = (int)Latitude;
      Latitude = (Latitude - dd) * 60.0;
      mm = (int)(Latitude);
      Latitude = (Latitude - mm) * 60.0;
      ss = (int)(Latitude + 0.5);
      if (ss >= 60) {
        mm++;
        ss -= 60;
      }
      if (mm >= 60) {
        dd++;
        mm -= 60;
      }
      _sntprintf(Buffer, size, TEXT("%c%02d%s%02d'%02d\""), EW[sign], dd, MsgToken<2179>(), mm, ss);
    break;
    case cfDDMMSSss:
      dd = (int)Latitude;
      Latitude = (Latitude - dd) * 60.0;
      mm = (int)(Latitude);
      Latitude = (Latitude - mm) * 60.0;
      _sntprintf(Buffer, size, TEXT("%c%02d%s%02d'%05.2f\""), EW[sign], dd, MsgToken<2179>(), mm, Latitude);
    break;
    case cfDDMMmmm:
      dd = (int)Latitude;
      Latitude = (Latitude - dd) * 60.0;
      _sntprintf(Buffer, size, TEXT("%c%02d%s%06.3f'"), EW[sign], dd, MsgToken<2179>(), Latitude);
    break;
    case cfDDdddd:
      _sntprintf(Buffer, size, TEXT("%c%07.4f%s"), EW[sign], Latitude, MsgToken<2179>());
    break;
    case cfUTM:
	_tcscpy(Buffer,_T(""));
	break;
    default:
	LKASSERT(0);
    break;
  }

  return true;

}

const TCHAR *Units::GetUnitName(Units_t Unit) {
    //  return LKGetText(UnitDescriptors[Unit].Name);
    // JMW adjusted this because units are pretty standard internationally
    // so don't need different names in different languages.

    const TCHAR *szName = nullptr;
    switch (Unit) {
        case unUndef:
        case unKiloMeter:
        case unNauticalMiles:
        case unStatuteMiles:
        case unKiloMeterPerHour:
        case unKnots:
        case unStatuteMilesPerHour:
        case unMeterPerSecond:
        case unFeetPerMinutes:
        case unMeter:
        case unFeet:
        case unFligthLevel:
        case unKelvin:
            szName = UnitDescriptors[Unit].Name;
            break;
        case unGradCelcius:
            szName = MsgToken<2180>();
            break;
        case unGradFahrenheit:
            szName = MsgToken<2181>();
            break;
        case unLastUnit:
            break;
    }
    assert(szName);
    return (szName ? szName : _T(""));
}

Units_t Units::GetUserDistanceUnit() {
  return UserDistanceUnit;
}

Units_t Units::SetUserDistanceUnit(Units_t NewUnit){
  Units_t last = UserDistanceUnit;
  if (UserDistanceUnit != NewUnit){
    UserDistanceUnit = NewUnit;
  }
  return last;
}

Units_t Units::GetUserAltitudeUnit() {
  return UserAltitudeUnit;
}

Units_t Units::GetUserInvAltitudeUnit() { // 100126
  return UserAltitudeUnit==unFeet?unMeter:unFeet;
}

Units_t Units::SetUserAltitudeUnit(Units_t NewUnit){
  Units_t last = UserAltitudeUnit;
  if (UserAltitudeUnit != NewUnit){
    UserAltitudeUnit = NewUnit;
  }
  return last;
}

Units_t Units::GetUserHorizontalSpeedUnit() {
  return UserHorizontalSpeedUnit;
}

Units_t Units::SetUserHorizontalSpeedUnit(Units_t NewUnit){
  Units_t last = UserHorizontalSpeedUnit;
  if (UserHorizontalSpeedUnit != NewUnit){
    UserHorizontalSpeedUnit = NewUnit;
  }
  return last;
}

Units_t Units::GetUserTaskSpeedUnit() {
  return UserTaskSpeedUnit;
}

Units_t Units::SetUserTaskSpeedUnit(Units_t NewUnit){
  Units_t last = UserTaskSpeedUnit;
  if (UserTaskSpeedUnit != NewUnit){
    UserTaskSpeedUnit = NewUnit;
  }
  return last;
}

Units_t Units::GetUserVerticalSpeedUnit() {
  return UserVerticalSpeedUnit;
}

Units_t Units::SetUserVerticalSpeedUnit(Units_t NewUnit){
  Units_t last = UserVerticalSpeedUnit;
  if (UserVerticalSpeedUnit != NewUnit){
    UserVerticalSpeedUnit = NewUnit;
  }
  return last;
}

Units_t Units::GetUserWindSpeedUnit() {
  return UserWindSpeedUnit;
}

Units_t Units::SetUserWindSpeedUnit(Units_t NewUnit){
  Units_t last = UserWindSpeedUnit;
  if (UserWindSpeedUnit != NewUnit){
    UserWindSpeedUnit = NewUnit;
  }
  return last;
}

Units_t Units::GetUserUnitByGroup(UnitGroup_t UnitGroup){
  switch(UnitGroup){
    case ugNone:
    return unUndef;
    case ugDistance:
    return GetUserDistanceUnit();
    case ugAltitude:
    return GetUserAltitudeUnit();
    case ugHorizontalSpeed:
    return GetUserHorizontalSpeedUnit();
    case ugVerticalSpeed:
    return GetUserVerticalSpeedUnit();
    case ugWindSpeed:
    return GetUserWindSpeedUnit();
    case ugTaskSpeed:
    return GetUserTaskSpeedUnit();
    case ugInvAltitude:
    return GetUserInvAltitudeUnit();
    default:
      return unUndef;
  }
}


void Units::NotifyUnitChanged() {
  // todo

  switch (SpeedUnit_Config) {
    case 0 :
      SetUserHorizontalSpeedUnit(unStatuteMilesPerHour);
      SetUserWindSpeedUnit(unStatuteMilesPerHour);
      break;
    case 1 :
      SetUserHorizontalSpeedUnit(unKnots);
      SetUserWindSpeedUnit(unKnots);
      break;
    case 2 :
    default:
      SetUserHorizontalSpeedUnit(unKiloMeterPerHour);
      SetUserWindSpeedUnit(unKiloMeterPerHour);
      break;
  }

  switch(DistanceUnit_Config) {
    case 0 :
      SetUserDistanceUnit(unStatuteMiles);
      break;
    case 1 :
      SetUserDistanceUnit(unNauticalMiles);
      break;
    default:
    case 2 :
      SetUserDistanceUnit(unKiloMeter);
      break;
  }

  switch(AltitudeUnit_Config) {
    case 0 :
      SetUserAltitudeUnit(unFeet);
      break;
    default:
    case 1 :
      SetUserAltitudeUnit(unMeter);
      break;
  }

  switch(LiftUnit_Config) {
    case 0 :
      SetUserVerticalSpeedUnit(unKnots);
      break;
    default:
    case 1 :
      SetUserVerticalSpeedUnit(unMeterPerSecond);
      break;
    case 2 :
      SetUserVerticalSpeedUnit(unFeetPerMinutes);
      break;
  }

  switch(TaskSpeedUnit_Config) {
    case 0 :
      SetUserTaskSpeedUnit(unStatuteMilesPerHour);
      break;
    case 1 :
      SetUserTaskSpeedUnit(unKnots);
      break;
    case 2 :
    default:
      SetUserTaskSpeedUnit(unKiloMeterPerHour);
      break;
  }
}

bool Units::FormatUserAltitude(double Altitude, TCHAR *Buffer, size_t size){

  int prec;
  TCHAR sTmp[512];
  UnitDescriptor_t *pU = &UnitDescriptors[UserAltitudeUnit];

  Altitude = Altitude * pU->ToUserFact; // + pU->ToUserOffset;

//  prec = 4-log10(Altitude);
//  prec = max(prec, 0);
  prec = 0;

  _stprintf(sTmp, TEXT("%.*f%s"), prec, Altitude, GetUnitName(UserAltitudeUnit));

  if (_tcslen(sTmp) < size-1){
    _tcscpy(Buffer, sTmp);
    return true;
  } else {
    LK_tcsncpy(Buffer, sTmp, size-1);
    return false;
  }

}

#if 100126
// I don't think it is a good idea to change, even if for a short time, a global variable at all effect here,
// just to be able to call the function above with a parameter missing!
bool Units::FormatAlternateUserAltitude(double Altitude, TCHAR *Buffer, size_t size){
  Units_t useUnit;
  TCHAR sTmp[512];

  if (UserAltitudeUnit == unMeter)
	useUnit=unFeet;
  else
	useUnit=unMeter;

  UnitDescriptor_t *pU = &UnitDescriptors[useUnit];
  Altitude = Altitude * pU->ToUserFact;
  _stprintf(sTmp, TEXT("%.*f%s"), 0, Altitude, GetUnitName(useUnit));

  if (_tcslen(sTmp) < size-1){
	_tcscpy(Buffer, sTmp);
	return true;
  } else {
	LK_tcsncpy(Buffer, sTmp, size-1);
	return false;
  }
}

#else
bool Units::FormatAlternateUserAltitude(double Altitude, TCHAR *Buffer, size_t size){
  Units_t saveUnit = UserAltitudeUnit;
  bool res;

  if (saveUnit == unMeter)
    UserAltitudeUnit = unFeet;
  if (saveUnit == unFeet)
    UserAltitudeUnit = unMeter;

  res = FormatUserAltitude(Altitude, Buffer, size);

  UserAltitudeUnit = saveUnit;

  return res;

}
#endif

bool Units::FormatUserArrival(double Altitude, TCHAR *Buffer, size_t size){

  int prec;
  TCHAR sTmp[512];
  UnitDescriptor_t *pU = &UnitDescriptors[UserAltitudeUnit];

  Altitude = Altitude * pU->ToUserFact; // + pU->ToUserOffset;

//  prec = 4-log10(Altitude);
//  prec = max(prec, 0);
  prec = 0;

  _stprintf(sTmp, TEXT("%+.*f%s"), prec, Altitude, GetUnitName(UserAltitudeUnit));

  if (_tcslen(sTmp) < size-1){
    _tcscpy(Buffer, sTmp);
    return true;
  } else {
    LK_tcsncpy(Buffer, sTmp, size-1);
    return false;
  }

}

bool Units::FormatUserDistance(double Distance, TCHAR *Buffer, size_t size){

  int prec;
  TCHAR sTmp[512];

  Units_t Unit = UserDistanceUnit;
  UnitDescriptor_t *pU = &UnitDescriptors[UserDistanceUnit];
  double value = Distance * pU->ToUserFact; // + pU->ToUserOffset;

  if (value >= 100)
    prec = 0;
  else if (value > 10)
    prec = 1;
  else if (value > 1)
    prec = 2;
  else {
    prec = 3;
    if (UserDistanceUnit == unKiloMeter){
      prec = 0;
      Unit = unMeter;
      pU = &UnitDescriptors[unMeter];
      value = Distance * pU->ToUserFact;
    }
    if (UserDistanceUnit == unNauticalMiles
            || UserDistanceUnit == unStatuteMiles) {

      Unit = unFeet;
      pU = &UnitDescriptors[unFeet];
      value = Distance * pU->ToUserFact;
      if (value<1000) {
        prec = 0;
      } else {
        prec = 1;
        Unit = UserDistanceUnit;
        pU = &UnitDescriptors[UserDistanceUnit];
        value = Distance* pU->ToUserFact;
      }
    }
  }

  _stprintf(sTmp, TEXT("%.*f%s"), prec, value, GetUnitName(Unit));

  if (_tcslen(sTmp) < size-1){
    _tcscpy(Buffer, sTmp);
    return true;
  } else {
    LK_tcsncpy(Buffer, sTmp, size-1);
    return false;
  }

}

bool Units::FormatUserMapScale(Units_t *Unit, double Distance, TCHAR *Buffer, size_t size){

  int prec;
  double value;
  TCHAR sTmp[512];
  Units_t UnitIdx = UserDistanceUnit;
  UnitDescriptor_t *pU = &UnitDescriptors[UnitIdx];

  value = Distance * pU->ToUserFact; // + pU->ToUserOffset;

  if (value >= 9.999) {
    prec = 0;
  } else if (value >= 0.999) {
    prec = 1;
  } else {
    prec = 2;
    if (UserDistanceUnit == unKiloMeter){
      prec = 0;
      UnitIdx = unMeter;
    } else if ((UserDistanceUnit == unNauticalMiles || UserDistanceUnit == unStatuteMiles) && (value < 0.160)) {
      prec = 0;
      UnitIdx = unFeet;
    }
  }

  if (Unit != NULL) {
    *Unit = UnitIdx;
  }

  pU = &UnitDescriptors[UnitIdx];
  value = Distance * pU->ToUserFact;

  _stprintf(sTmp, TEXT("%.*f%s"), prec, value, GetUnitName(UnitIdx));

  if (_tcslen(sTmp) < size-1){
    _tcscpy(Buffer, sTmp);
    return true;
  } else {
    LK_tcsncpy(Buffer, sTmp, size-1);
    return false;
  }

}



double Units::ToUser(Units_t unit, double value) {
  const UnitDescriptor_t *pU = &UnitDescriptors[unit];
  return value * pU->ToUserFact + pU->ToUserOffset;
}


double Units::ToSys(Units_t unit, double value) {
  const UnitDescriptor_t *pU = &UnitDescriptors[unit];
  return (value - pU->ToUserOffset) / pU->ToUserFact;
}

void Units::TimeToText(TCHAR* text, size_t cb, int d) {
  int hours, mins;
  bool negative = (d<0);
  int dd = abs(d) % (3600*24);
  hours = (dd/3600);
  mins = (dd/60-hours*60);
  hours = hours % 24;

  lk::snprintf(text, cb, TEXT("%s%02d:%02d"), (negative ? _T("-") : _T("")), hours, mins);
}

void Units::TimeToTextSimple(TCHAR* text, size_t cb, int d) {
  int hours, mins;
  bool negative = (d<0);
  int dd = abs(d) % (3600*24);
  hours = (dd/3600);
  mins = (dd/60-hours*60);
  hours = hours % 24;

  lk::snprintf(text, cb, TEXT("%s%02d%02d"), (negative ? _T("-") : _T("")), hours, mins);
}

// Not for displaying a clock time, good for a countdown
// will display either
// Returns true if hours, false if minutes
bool Units::TimeToTextDown(TCHAR* text, size_t cb, int d) {
  int hours, mins, seconds;
  bool negative = (d < 0);
  int dd = abs(d) % (3600 * 24);

  hours = (dd / 3600);
  mins = (dd / 60 - hours * 60);
  hours = hours % 24;
  seconds = (dd - mins * 60 - hours * 3600);

  if (hours == 0) {
    lk::snprintf(text, cb, _T("%s%02d:%02d"), (negative ? _T("-") : _T("")), mins, seconds);
    return false;
  } else {
    lk::snprintf(text, cb, _T("%s%02d:%02d"), (negative ? _T("-") : _T("")), hours, mins);
    return true;
  }
}

// LK8000
void Units::TimeToTextS(TCHAR* text, size_t cb, int d) {
  bool negative = (d<0);
  int dd = abs(d) % (3600*24);
  int hours = (dd/3600);
  int mins = (dd/60-hours*60);
  int seconds = (dd-mins*60-hours*3600);
  hours = hours % 24;

  lk::snprintf(text, cb, _T("%s%d:%02d:%02d"), (negative ? _T("-") : _T("")), hours, mins, seconds);
}
