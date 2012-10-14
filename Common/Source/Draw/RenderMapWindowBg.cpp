/*
   LK8000 Tactical Flight Computer -  WWW.LK8000.IT
   Released under GNU/GPL License v.2
   See CREDITS.TXT file for authors and copyrights

   $Id$
*/

#include "externs.h"
#include <Message.h>
#include "Terrain.h"
#include "RasterTerrain.h"
#include "LKGeneralAviation.h"
#include "Multimap.h"

#if NEWSMARTZOOM
// We do smart zoom only with real map painted, and in quickdraw mode
// Temporarily, work only in Inversemode to test speed difference on PNAs (Inverse works..inverted!)
#define ONSMARTZOOM	((MAPMODE8000 &&  QUICKDRAW) &&  Appearance.InverseInfoBox )
#define OFFSMARTZOOM	((MAPMODE8000 && !QUICKDRAW) || !Appearance.InverseInfoBox )
#endif

extern bool FastZoom;


void MapWindow::RenderMapWindowBg(HDC hdc, const RECT rc,
				  const POINT &Orig,
				  const POINT &Orig_Aircraft)
{
  HFONT hfOld;

  // Calculations are taking time and slow down painting of map, beware
  #define MULTICALC_MINROBIN	5	// minimum split
  #define MULTICALC_MAXROBIN	20	// max split
  static short multicalc_slot=0;// -1 (which becomes immediately 0) will force full loading on startup, but this is not good
				// because currently we are not waiting for ProgramStarted=3
				// and the first scan is made while still initializing other things

  // TODO assign numslots with a function, based also on available CPU time
  short numslots=1;
  #if NEWSMARTZOOM
  static double quickdrawscale=0.0;
  static double delta_drawscale=1.0;
  #endif

  #if 0 
  extern void TestChangeRect();
  TestChangeRect();
  #endif

  #if DYNASCREEN
  if ((MapWindow::AlphaBlendSupported() && BarOpacity<100) || mode.AnyPan()) {
	MapWindow::ChangeDrawRect(MapRect);
  } else {
	RECT newRect={0,0,ScreenSizeX,ScreenSizeY-BottomSize};
	MapWindow::ChangeDrawRect(newRect);
  }
  #else
  MapWindow::ChangeDrawRect(MapRect);
  #endif

  // If we have a BigZoom request, we serve it immediately without calculating anything
  // TODO: stretch the old map bitmap to the new zoom, while fastzooming
  if (QUICKDRAW) {
	goto fastzoom;
  }

  if (NumberOfWayPoints>200) {
	numslots=NumberOfWayPoints/400;
	// keep numslots optimal
	if (numslots<MULTICALC_MINROBIN) numslots=MULTICALC_MINROBIN; // seconds for full scan, as this is executed at 1Hz
	if (numslots>MULTICALC_MAXROBIN) numslots=MULTICALC_MAXROBIN;

	// When waypointnumber has changed, we wont be using an exceeded multicalc_slot, which would crash the sw
	// In this case, we shall probably continue for the first round to calculate without going from the beginning
	// but this is not a problem, we are round-robin all the time here.
	if (++multicalc_slot>numslots) multicalc_slot=1;
  } else {
	multicalc_slot=0; // forcing full scan
  }

  // Here we calculate arrival altitude, GD etc for map waypoints. Splitting with multicalc will result in delayed
  // updating of visible landables, for example. The nearest pages do this separately, with their own sorting.
  // Basically we assume -like for nearest- that values will not change that much in the multicalc split time.
  // Target and tasks are recalculated in real time in any case. Nearest too. 
  LKCalculateWaypointReachable(multicalc_slot, numslots);
  CalculateScreenPositionsAirspace();
  CalculateScreenPositionsThermalSources();
  CalculateScreenPositionsGroundline();

  if (PGZoomTrigger) {
    if(!mode.Is(Mode::MODE_PANORAMA)) {
      mode.Special(Mode::MODE_SPECIAL_PANORAMA, true);
		LastZoomTrigger=DrawInfo.Time;
      
		Message::Lock();
	        Message::AddMessage(1000, 3, gettext(TEXT("_@M872_"))); // LANDSCAPE ZOOM FOR 20s
		Message::Unlock();
		#ifndef DISABLEAUDIO
		if (EnableSoundModes) LKSound(TEXT("LK_TONEUP.WAV"));
		#endif
    }
    else {
		// previously called, see if time has passed
		if ( DrawInfo.Time > (LastZoomTrigger + 20.0)) {
			// time has passed, lets go back
			LastZoomTrigger=0; // just for safety
        mode.Special(Mode::MODE_SPECIAL_PANORAMA, false);
			PGZoomTrigger=false;
			Message::Lock(); 
	        	Message::AddMessage(1500, 3, gettext(TEXT("_@M873_"))); // BACK TO NORMAL ZOOM
			Message::Unlock();
			#ifndef DISABLEAUDIO
			if (EnableSoundModes) LKSound(TEXT("LK_TONEDOWN.WAV"));
			#endif
		}
	}
  }

  // 
  // "Checkpoint Charlie"
  // This is were we process stuff for anything else but main map.
  // We let the calculations run also for MapSpace modes.
  // But for multimaps, we can also draw some more stuff..
  // We are also sent back here from next code, when we detect that
  // the MapSpace mode has changed from MAP to something else while we
  // were rendering.
  //
#if NEWMULTIMAPS
QuickRedraw:
#endif
  //
  if (DONTDRAWTHEMAP) 
  {
	#if NEWMULTIMAPS
	DrawMapSpace(hdc, rc);
	// Is this a "shared map" environment? 
	if (IsMultiMapShared()) { 
		// Shared map, of course not MSN_MAP, since dontdrawthemap was checked
		//
		if (IsMultimapOverlays()) {

			DrawLook8000(hdc,rc);
			if (LKVarioBar) LKDrawVario(hdc,rc);

			if ((mode.Is(Mode::MODE_CIRCLING)) )
				if (ThermalBar) DrawThermalBand(hdcDrawWindow, rc);

			DrawFinalGlide(hdcDrawWindow,rc);
		}

	} else {
		// Not in map painting environment 
		// ex. nearest pages, but also MAPRADAR..
	}
	#else
	// Drawing Look8000 here was probably a mistake!
QuickRedraw:
	DrawLook8000(hdc,rc);
	#endif

	// 
	DrawBottomBar(hdc,rc);
#ifdef CPUSTATS
	DrawCpuStats(hdc,rc);
#endif
#ifdef DRAWDEBUG
	DrawDebug(hdc,rc);
#endif
	// no need to do SelectObject as at the bottom of function
	return;
  }

  // When no terrain is painted, set a background0
  // Remember that in this case we have plenty of cpu time to spend for best result
  #if NEWMULTIMAPS
  if (!IsMultimapTerrain() || !DerivedDrawInfo.TerrainValid || !RasterTerrain::isTerrainLoaded() ) {
  #else
  if (!EnableTerrain || !DerivedDrawInfo.TerrainValid || !RasterTerrain::isTerrainLoaded() ) {
  #endif

    // display border and fill background..
	SelectObject(hdc, hInvBackgroundBrush[BgMapColor]);
	SelectObject(hdc, GetStockObject(WHITE_PEN));

	Rectangle(hdc,rc.left,rc.top,rc.right,rc.bottom);
	// We force LK painting black values on screen depending on the background color in use
	// TODO make it an array once settled
	// blackscreen would force everything to be painted white, instead
	LKTextBlack=BgMapColorTextBlack[BgMapColor];
	if (BgMapColor>6 ) BlackScreen=true; else BlackScreen=false; 
  } else {
	LKTextBlack=false;
	BlackScreen=false;
  }

fastzoom:  

  #if NEWSMARTZOOM
  // Copy the old background map with no overlays
  if (ONSMARTZOOM) {

	if (quickdrawscale>0) {
		delta_drawscale=zoom.DrawScale() / quickdrawscale;
	}

// StartupStore(_T("... QuickDrawScale=%.2f new zoom=%.2f  delta=%.2f\n"),quickdrawscale,zoom.DrawScale(),delta_drawscale);

	int dx=MapRect.right-MapRect.left;
	int dy=MapRect.bottom-MapRect.top;

	// notice: zoom in is always ok.. but zoom out starting from high zoom levels will make the picture
	// very small and unusable. We can consider to zoom out in fast zoom normally, in such cases?
	//
	// Notice 2: the delta is not yet working correctly 
	//
	if (delta_drawscale>1.0) {
		// zoom in
		StretchBlt(hdcDrawWindow, 
			0,0,
			dx,dy, 
			hdcQuickDrawWindow,
			(int)((dx/2) - (dx / delta_drawscale)/2),
			(int)((dy/2) - (dy / delta_drawscale)/2),
			(int)(dx / delta_drawscale),
			(int)(dy / delta_drawscale), 
			SRCCOPY);
	} else {
		// zoom out
		StretchBlt(hdcDrawWindow,
			(int)((dx/2) - (dx * delta_drawscale)/2),
			(int)((dy/2) - (dy * delta_drawscale)/2),
			(int)(dx * delta_drawscale),
			(int)(dy * delta_drawscale), 
			hdcQuickDrawWindow,
			0,0,
			dx,dy,  
			SRCCOPY);
	}
  }
  #endif

  SelectObject(hdc, GetStockObject(BLACK_BRUSH));
  SelectObject(hdc, GetStockObject(BLACK_PEN));
  hfOld = (HFONT)SelectObject(hdc, MapWindowFont);
  

  // Logic of DONTDRAWTHEMAP is the following:
  // We are rendering the screen page here. If we are here, we passed Checkpoint Charlie.
  // So we were, at charlie, in MSM_MAP: preparing the main map stuff.
  // If we detect that MapSpace has CHANGED while we were doing our job here,
  // it means that the user has clicked meanwhile. He desires another page, so let's
  // reset our intentions and go back to beginning, or nearby..
  // We have a new job to do, for another MapSpace, no more MAP.
  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  #if NEWSMARTZOOM
  if ( OFFSMARTZOOM ) {
  #endif

  #if NEWMULTIMAPS
  if ((IsMultimapTerrain() && (DerivedDrawInfo.TerrainValid) 
  #else
  if ((EnableTerrain && (DerivedDrawInfo.TerrainValid) 
  #endif
       && RasterTerrain::isTerrainLoaded())
	) {
	// sunelevation is never used, it is still a todo in Terrain
	double sunelevation = 40.0;
	double sunazimuth=GetAzimuth();

    LockTerrainDataGraphics();
 	if (DONTDRAWTHEMAP) { // 100318
		UnlockTerrainDataGraphics();
		SelectObject(hdcDrawWindow, hfOld);
		goto QuickRedraw;
	}
    DrawTerrain(hdc, DrawRect, sunazimuth, sunelevation);
 	if (DONTDRAWTHEMAP) {
		UnlockTerrainDataGraphics();
		SelectObject(hdcDrawWindow, hfOld);
		goto QuickRedraw;
	}
    if (!QUICKDRAW) {
    	// SHADED terrain unreachable, aka glide amoeba. This is not the outlined perimeter!
        #ifdef GTL2
    	if (((FinalGlideTerrain == 2) || (FinalGlideTerrain == 4)) && 
            DerivedDrawInfo.TerrainValid) {
        #else
    	if ((FinalGlideTerrain==2) && DerivedDrawInfo.TerrainValid) {
        #endif
    	  DrawTerrainAbove(hdc, DrawRect);
    	}
    }
    UnlockTerrainDataGraphics();
  }

  #if NEWSMARTZOOM
  }
  #endif

  #if TESTBENCH
  if (MapSpaceMode!=MSM_MAP) {
	DoStatusMessage(_T("RENDERMAPWINDOWBG NOT IN MSM_MAP!"));
  }
  #endif

  //
  // REMINDER: WE ARE IN MAIN MAP HERE: MSM_MAP ONLY.
  //

  // If we detect the quick draw request, we accelerate drawing of main map.
  // We paing the minimum: overlays and bottom bar, and quickly we return.
  //
  if (QUICKDRAW)  {
	if ( !mode.AnyPan()) {
		#if 0 
		//
		// ALl of this is not needed, we are in main map -- REMOVE!
		// 
		#if NEWMULTIMAPS
		if (MapSpaceMode!= MSM_MAP) DrawMapSpace(hdc, rc);
		if (IsMultiMapShared() && IsMultimapOverlays()) DrawLook8000(hdc,rc);
		#else
		DrawLook8000(hdc,rc);
		#endif
		#endif
		DrawLook8000(hdc,rc);
		DrawBottomBar(hdc,rc);
	}
  	SelectObject(hdcDrawWindow, hfOld);
	return;
  }

  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  #if NEWMULTIMAPS
  if (IsMultimapTopology()) {
  #else
  if (EnableTopology) {
  #endif
    DrawTopology(hdc, DrawRect);
  }
  #if 0
  StartupStore(_T("... Experimental1=%.0f\n"),Experimental1);
  StartupStore(_T("... Experimental2=%.0f\n"),Experimental2);
  Experimental1=0.0;
  Experimental2=0.0;
  #endif

  // Topology labels are printed first, using OLD wps positions from previous run!
  // Reset for topology labels decluttering engine occurs also in another place here!
  ResetLabelDeclutter();
  
  if (ValidTaskPoint(ActiveWayPoint) && ValidTaskPoint(1)) {
	DrawTaskAAT(hdc, DrawRect);
  }

  
  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  #if NEWMULTIMAPS
  if (IsMultimapAirspace())
  #else 
  if (OnAirSpace > 0)  // Default is true, always true at startup no regsave 
  #endif
  {
    if ( (GetAirSpaceFillType() == asp_fill_ablend_full) || (GetAirSpaceFillType() == asp_fill_ablend_borders) )
      DrawTptAirSpace(hdc, rc);
    else
      DrawAirSpace(hdc, rc);	 // full screen, to hide clipping effect on low border
  }

  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }
  
  if(TrailActive) {
	// NEED REWRITING
	LKDrawTrail(hdc, Orig_Aircraft, DrawRect);
  }

  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  DrawThermalEstimate(hdc, DrawRect);
  if (OvertargetMode==OVT_THER) DrawThermalEstimateMultitarget(hdc, DrawRect);
 
  // draw red cross on glide through terrain marker
  if (FinalGlideTerrain && DerivedDrawInfo.TerrainValid) {
    DrawGlideThroughTerrain(hdc, DrawRect);
  }
  
  if (DONTDRAWTHEMAP) { 
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  #if NEWMULTIMAPS
  if (IsMultimapAirspace() && AirspaceWarningMapLabels)
  #else
  if ((OnAirSpace > 0) && AirspaceWarningMapLabels)
  #endif
  {
	DrawAirspaceLabels(hdc, DrawRect, Orig_Aircraft);
	if (DONTDRAWTHEMAP) { // 100319
		SelectObject(hdcDrawWindow, hfOld);
		goto QuickRedraw;
	}
  }

  DrawWaypointsNew(hdc,DrawRect);

  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  if (ValidTaskPoint(ActiveWayPoint) && ValidTaskPoint(1)) { // 100503
	DrawTask(hdc, DrawRect, Orig_Aircraft);
  }
  DrawTeammate(hdc, rc);

  if (extGPSCONNECT) {
    DrawBestCruiseTrack(hdc, Orig_Aircraft);
    DrawBearing(hdc, DrawRect);
  }

  // draw wind vector at aircraft
  if (!mode.AnyPan()) {
    DrawWindAtAircraft2(hdc, Orig_Aircraft, DrawRect);
  } else if (mode.Is(Mode::MODE_TARGET_PAN)) {
    DrawWindAtAircraft2(hdc, Orig, rc);
  }

  #if NEWSMARTZOOM
  // Save the current rendered map before painting overlays
  if ( OFFSMARTZOOM ) {
	quickdrawscale=zoom.DrawScale();
	BitBlt(hdcQuickDrawWindow, 0, 0, MapRect.right-MapRect.left, MapRect.bottom-MapRect.top,
		hdcDrawWindow, 0, 0, SRCCOPY);
  }
  #endif

  // VisualGlide drawn BEFORE lk8000 overlays
  if (!mode.AnyPan() && VisualGlide > 0) {
    DrawGlideCircle(hdc, Orig, rc); 
  }

  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }

  // Draw traffic and other specifix LK gauges
  	LKDrawFLARMTraffic(hdc, DrawRect, Orig_Aircraft);

  if (!mode.AnyPan()) {
    // REMINDER TODO let it be configurable for not circling also, as before
    if ((mode.Is(Mode::MODE_CIRCLING)) )
      if (ThermalBar) DrawThermalBand(hdcDrawWindow, rc); // 091122
  
    if (IsMultimapOverlays()) DrawLook8000(hdc,rc); 
    DrawBottomBar(hdc,rc);
  }

  if (DONTDRAWTHEMAP) {
	SelectObject(hdcDrawWindow, hfOld);
	goto QuickRedraw;
  }
    
  if (LKVarioBar && !mode.AnyPan()) 
	LKDrawVario(hdc,rc);
  
  // Draw glider or paraglider
  if (extGPSCONNECT) {
    DrawAircraft(hdc, Orig_Aircraft);
  }

  if (!mode.AnyPan()) {
	if (TrackBar) DrawHeading(hdc, Orig, DrawRect); 
  }

  #if USETOPOMARKS
  // marks on top...
  DrawMarks(hdc, rc);
  #endif

  if (ISGAAIRCRAFT) DrawHSI(hdc,Orig,DrawRect); 

  DrawMapScale(hdcDrawWindow,rc, zoom.BigZoom()); // unused BigZoom
  DrawCompass(hdcDrawWindow, rc);

  if (NOTANYPAN) DrawFinalGlide(hdcDrawWindow,rc);


#ifdef CPUSTATS
  DrawCpuStats(hdc,rc);
#endif
#ifdef DRAWDEBUG
  DrawDebug(hdc,rc);
#endif

  SelectObject(hdcDrawWindow, hfOld);

}


