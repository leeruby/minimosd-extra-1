
/******* STARTUP PANEL *******/

void startPanels(){
    osd.setPanel(5, 5);
    osd.printf_P(PSTR(OSD_VERSION));

  do_converts(); // load the unit conversion preferences
}

//------------------ Panel: Startup ArduCam OSD LOGO -------------------------------



/******* PANELS - POSITION *******/

void writePanels(){ 

#ifdef IS_PLANE
    if ((takeofftime == 1) && (osd_alt_to_home > 10 || osd_groundspeed > 1 || osd_throttle > 1 || osd_home_distance > 100)){
        landed = millis();
    }
#endif

    //if(millis() < (lastMAVBeat + 2200))
    //  waitingMAVBeats = 1;
    //if(is_on(panWarn_XY)) panWarn(panWarn_XY.x, panWarn_XY.y); // this must be here so warnings are always checked

  //Base panel selection
  //No mavlink data available panel
  if(millis() > (lastMAVBeat + 2200)){
    if (currentBasePanel != 2){
      osd.clear();
      currentBasePanel = 2;
    }   
    panWaitMAVBeats(5,10); //Waiting for MAVBeats...
  }

  //Flight summary panel
  //Only show flight summary 10 seconds after landing and if throttle < 15
#ifdef IS_COPTER
  else if (!motor_armed && (((millis() / 10000) % 2) == 0) && (tdistance > 50)){ 
    if (currentBasePanel != 1){
      osd.clear();
      currentBasePanel = 1;
    }
#else
#ifdef IS_PLANE
    //Only show flight summary 7 seconds after landing
  else if ((millis() - 7000) > landed){
#else
    if(0) {
#endif
#endif
    panFdata(); 
  }
  //Normal osd panel
  else{
    if(is_on(panWarn_XY)) panWarn(panWarn_XY.x, panWarn_XY.y); // this must be here so warnings are always checked

    //Check for panel toggle
    if(ch_toggle > 3) panOff(); // This must be first so you can always toggle

    //If there is a panel switch or a change in base panel then clear osd
    if ((osd_clear == 1) || (currentBasePanel != 0)){
      osd.clear();
      osd_clear = 0;
      currentBasePanel = 0;
    }
    if(panel < npanels){ // конфигурируемые юзером экраны
    	// must be first to other can overwrite free space
      if(is_on(panHorizon_XY)) panHorizon(panHorizon_XY.x, panHorizon_XY.y); //14x5
    
//      if(is_on(panCenter_XY)) panCenter(panCenter_XY.x, panCenter_XY.y);   //4x2 - нет в конфигураторе
      if(is_on(panPitch_XY)) panPitch(panPitch_XY.x, panPitch_XY.y); //5x1
      if(is_on(panRoll_XY)) panRoll(panRoll_XY.x, panRoll_XY.y); //5x1
      if(is_on(panBatt_A_XY)) panBatt_A(panBatt_A_XY.x, panBatt_A_XY.y); //7x1
      //if(is_on(panBatt_B_XY)) panBatt_B(panBatt_B_XY.x, panBatt_B_XY.y); //7x1
      if(is_on(panGPSats_XY)) panGPSats(panGPSats_XY.x, panGPSats_XY.y); //5x1
  //  if(is_on(panGPL_XY)) panGPL(panGPL_XY.x, panGPL_XY.y); //2x1
      if(is_on(panGPS_XY)) panGPS(panGPS_XY.x, panGPS_XY.y); //12x3
      if(is_on(panBatteryPercent_XY)) panBatteryPercent(panBatteryPercent_XY.x, panBatteryPercent_XY.y); //
      if(is_on(panCOG_XY)) panCOG(panCOG_XY.x, panCOG_XY.y); //

      if(is_on(panRose_XY)) panRose(panRose_XY.x, panRose_XY.y);        //13x3
      if(is_on(panHeading_XY)) panHeading(panHeading_XY.x, panHeading_XY.y); //13x3
  //  if(is_on(panMavBeat_XY)) panMavBeat(panMavBeat_XY.x, panMavBeat_XY.y); //13x3

      if(osd_got_home == 1){
        if(is_on(panHomeDis_XY)) panHomeDis(panHomeDis_XY.x, panHomeDis_XY.y); //13x3
        if(is_on(panHomeDir_XY)) panHomeDir(panHomeDir_XY.x, panHomeDir_XY.y); //13x3
      }

      if(is_on(panTime_XY)) panTime(panTime_XY.x, panTime_XY.y);
      
      //Only show wp panel if there is one
      if(wp_number > 0){
        if(is_on(panWPDis_XY)) panWPDis(panWPDis_XY.x, panWPDis_XY.y); //??x??
      }

      if(is_on(panAlt_XY)) panAlt(panAlt_XY.x, panAlt_XY.y); //
      if(is_on(panHomeAlt_XY)) panHomeAlt(panHomeAlt_XY.x, panHomeAlt_XY.y); //
      if(is_on(panVel_XY)) panVel(panVel_XY.x, panVel_XY.y); //
      if(is_on(panAirSpeed_XY)) panAirSpeed(panAirSpeed_XY.x, panAirSpeed_XY.y); //
      if(is_on(panThr_XY)) panThr(panThr_XY.x, panThr_XY.y); //
      if(is_on(panFMod_XY)) panFlightMode(panFMod_XY.x, panFMod_XY.y);  //
      
      if(is_on(panCur_A_XY)) panCur_A(panCur_A_XY.x, panCur_A_XY.y);

      //For now we don't have windspeed in copter - really?
      if(is_on(panWindSpeed_XY)) panWindSpeed(panWindSpeed_XY.x, panWindSpeed_XY.y);
  
      if(is_on(panClimb_XY)) panClimb(panClimb_XY.x, panClimb_XY.y);
#ifdef IS_PLANE
      if(is_on(panTune_XY)) panTune(panTune_XY.x, panTune_XY.y);
#endif
      if(is_on(panRSSI_XY)) panRSSI(panRSSI_XY.x, panRSSI_XY.y); //??x??
      if(is_on(panEff_XY)) panEff(panEff_XY.x, panEff_XY.y);

      if(is_on(panTemp_XY)) panTemp(panTemp_XY.x, panTemp_XY.y);
  //  if(is_on(panCh_XY)) panCh(panCh_XY.x, panCh_XY.y);
      if(is_on(panDistance_XY)) panDistance(panDistance_XY.x, panDistance_XY.y);

    }
  }
//  if(is_on(panCALLSIGN_XY)) panCALLSIGN(panCALLSIGN_XY.x, panCALLSIGN_XY.y); //call sign even in off panel
    // show warnings even if screen is disabled 
    if(is_on(panWarn_XY)) panWarn(panWarn_XY.x, panWarn_XY.y);


  timers();

    // OSD debug for development (Shown on top-middle panels) 
#ifdef membug
    osd.setPanel(13,4);
    osd.printf_P(PSTR("%i"),freeMem()); 
#endif
}

/******* PANELS - DEFINITION *******/
/* **************************************************************** */

/* **************************************************************** */
// Panel  : COG Course Over Ground
// Needs  : X, Y locations
// Output : 
// Size   : 
// Staus  : done

void panCOG(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    
    osd_COG_arrow_rotate_int = round(((osd_cog / 100) - osd_heading)/360.0 * 16.0 +1); //Convert to int 1-16 
    if(osd_COG_arrow_rotate_int <= 0 ) osd_COG_arrow_rotate_int += 16;
    if(osd_COG_arrow_rotate_int >16)   osd_COG_arrow_rotate_int -= 16;
    
    if (((osd_cog / 100) - osd_heading) > 180){
       off_course = (osd_cog / 100 - osd_heading) - 360;
    }else if (((osd_cog / 100) - osd_heading) < -180){
       off_course = (osd_cog / 100 - osd_heading) + 360;
    }else{
       off_course = (osd_cog / 100 - osd_heading);
    }
    
    showArrow((uint8_t)osd_COG_arrow_rotate_int,2);
}

// Panel  : ODO
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panDistance(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    if ((tdistance * converth) > 9999.0) {
      osd.printf(PSTR("\x8f%5.2f%c"), ((tdistance * converth) / distconv), distchar);
    }else{
      osd.printf_P(PSTR("\x8f%5.0f%c"), (tdistance * converth), high);
    }
}

/* **************************************************************** */
// Panel  : panFdata
// Needs  : X, Y locations
// Output : 
// Size   : 
// Staus  : done
void panFdata()
{
  osd.setPanel(11, 4);
  osd.printf_P(PSTR("\x08%3i\x3a%02i|\x0B%5i%c|\x8F%5i%c|\x14%5i%c|\x12%5i%c|\x03%10.6f|\x04%10.6f"), ((int)total_flight_time_seconds/60)%60,(int)total_flight_time_seconds%60,
				      (int)((max_home_distance) * converth), high, 
				                 (int)((tdistance) * converth), high,
				                	(int)(max_osd_groundspeed * converts),spe,
				                		    (int)(max_osd_home_alt * converth), high, 
				                			      (double)osd_lat, 
				                			    		(double)osd_lon);
}

/* **************************************************************** */
// Panel  : pantemp
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panTemp(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    //do_converts();
    osd.printf_P(PSTR("%5.1f%c"), (float(temperature / 10 * tempconv + tempconvAdd) / 100), temps);    
}

/* **************************************************************** */
// Panel  : efficiency
// Needs  : X, Y locations
// Output : 
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done
void panEff(byte first_col, byte first_line)
{
  osd.setPanel(first_col, first_line);

#ifdef IS_COPTER
  //Check takeoff just to prevent inicial false readings
  if (motor_armed)
  {
    if(osd_battery_remaining_A != last_battery_reading)
    {
      remaining_estimated_flight_time_seconds = ((float)osd_battery_remaining_A * total_flight_time_milis / (max_battery_reading - osd_battery_remaining_A)) / 1000;
      last_battery_reading = osd_battery_remaining_A;
    }
    osd.printf_P(PSTR("\x17%2i\x3A%02i"), ((int)remaining_estimated_flight_time_seconds/60)%60,(int)remaining_estimated_flight_time_seconds%60);
  }
#endif

#ifdef IS_PLANE
    if (osd_throttle >= 1){
      if (ma == 0) {
              ma = 1;
            }
        if (osd_groundspeed != 0) eff = (float(osd_curr_A * 10.0) / (osd_groundspeed * converts))* 0.1 + eff * 0.9;
          if (eff > 0 && eff <= 9999) {
            osd.printf_P(PSTR("%c%4.0f%c"), 0x16, eff, 0x01);
          }else{
          osd.printf_P(PSTR("\x16\x20\x20\x20\x20\x20"));
          }

    }else{

        if ((osd_throttle < 1)){
            if (ma == 1) {
              palt = osd_alt_to_home;
              ddistance = tdistance;
              ma = 0;
            }
        }
        if (osd_climb < -0.05){
            glide = ((osd_alt_to_home / (palt - osd_alt_to_home)) * (tdistance - ddistance)) * converth;
            if (glide > 9999) glide = 9999;
            if (glide > -0){
                osd.printf_P(PSTR("\x18%4.0f%c"), glide, high);
            }
        }else if (osd_climb >= -0.05 && osd_pitch < 0) {
              osd.printf_P(PSTR("\x18\x20\x20\x90\x91\x20"));
        }else{
              osd.printf_P(PSTR("\x18\x20\x20\x20\x20\x20"));
        }
    }
#endif
}

/* **************************************************************** */
// Panel  : panRSSI
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panRSSI(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    if((rssiraw_on % 2 == 0))
    {
       if(osd_rssi < rssipersent) osd_rssi = rssipersent;
       if(osd_rssi > rssical) osd_rssi = rssical;
       if(rssiraw_on == 0) rssi = (int16_t)((float)((int16_t)osd_rssi - rssipersent)/(float)(rssical-rssipersent)*100.0f);
       if(rssiraw_on == 8) rssi = (int16_t)((float)(chan8_raw / 10 - rssipersent)/(float)(rssical-rssipersent)*100.0f);
    }
    if(rssiraw_on == 1) rssi = (int16_t)osd_rssi;
    if(rssiraw_on == 9) rssi = chan8_raw;

    if(rssi > 100.0) rssi = 100;

    osd.printf_P(PSTR("\x09%3i\x25"), rssi);
}

/* **************************************************************** */
// Panel  : panCALLSIGN
// Needs  : X, Y locations
// Output : Call sign identification
// Size   : 1 x 6Hea  (rows x chars)
// Staus  : done

void panCALLSIGN(byte first_col, byte first_line){

    osd.setPanel(first_col, first_line);
    if(((millis() / 1000) % 60) < 2){
      osd.print( char_call);
    }else{
      osd.print(strclear);
    }

}


/* **************************************************************** */
// Panel  : pan wind speed
// Needs  : X, Y locations
// Output : Wind direction symbol (arrow) and velocity
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panWindSpeed(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    if (osd_winddirection < 0){
        osd_wind_arrow_rotate_int = round(((osd_winddirection + 360) - osd_heading)/360.0 * 16.0) + 9; //Convert to int 1-16
    }else{
        osd_wind_arrow_rotate_int = round((osd_winddirection - osd_heading)/360.0 * 16.0) + 9; //Convert to int 1-16
    }
    if(osd_wind_arrow_rotate_int > 16 ) osd_wind_arrow_rotate_int -= 16; //normalize
    if(osd_wind_arrow_rotate_int < 1 ) osd_wind_arrow_rotate_int += 16; //normalize
    nor_osd_windspeed = osd_windspeed * 0.010 + nor_osd_windspeed * 0.990;    
    
    showArrow((uint8_t)osd_wind_arrow_rotate_int,1); //print data to OSD
}

/* **************************************************************** */
// Panel toggle : panOff
// Output : OSD off
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panOff(){
  bool rotatePanel = 0;

      if(ch_toggle == 5) ch_raw = chan5_raw;
      else if(ch_toggle == 6) ch_raw = chan6_raw;
      else if(ch_toggle == 7) ch_raw = chan7_raw;
      else if(ch_toggle == 8) ch_raw = chan8_raw;


  //If there is a warning force switch to panel 0
  if(canswitch == 0){
    if(panel != panel_auto_switch){ 
      osd_clear = 1;
    }
    panel = panel_auto_switch; 
    readPanelSettings();
  }
  else{
    //Flight mode switching


/*	автоматическое управление OSD  (если режим не RTL или CIRCLE) смена режима туда-сюда переключает экран

    if (ch_toggle == 4){
      if ((osd_mode != 6) && (osd_mode != 7)){
        if (osd_off_switch != osd_mode){ 
          osd_off_switch = osd_mode;
            osd_switch_time = millis();
            if (osd_off_switch == osd_switch_last){
              rotatePanel = 1;
            }
        }
        if ((millis() - osd_switch_time) > 2000){
          osd_switch_last = osd_mode;
        }
      }
    }
    else */ {

      //Switch mode by value
      if (switch_mode == 0){
        //First panel
        if (ch_raw < 1200 && panel != 0) {
          osd_clear = 1;
          panel = 0;
        }
        //Second panel
        else if (ch_raw >= 1200 && ch_raw <= 1800 && panel != 1) { //second panel
          osd_clear = 1;
          panel = 1;
        }
        //Panel off
        else if (ch_raw > 1800 && panel != npanels) {
            osd_clear = 1;
            panel = npanels; //off panel
        }
	readPanelSettings();
      }
      //Rotation switch
      else{
        if (ch_raw > 1200)
          if (osd_switch_time + 1000 < millis()){
            rotatePanel = 1;
            osd_switch_time = millis();
        }
      }    
    }
    if(rotatePanel == 1){
        osd_clear = 1;
        panel++;
        if (panel > npanels)
            panel = 0;
    
	readPanelSettings();

    }
  }
}

/* **************************************************************** */
// Panel  : panCur_A
// Needs  : X, Y locations
// Output : Current symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panCur_A(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("%5.2f\x0e"), (float(osd_curr_A) * 0.01));
}

/* **************************************************************** */
// Panel  : panAlt
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panAlt(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    if(EEPROM.read(SIGN_MSL_ON_ADDR) != 0) 
	osd.write(0x11);
    osd.printf_P(PSTR("%5.0f%c"), (double)(osd_alt_gps * converth), high);
}

/* **************************************************************** */
// Panel  : panClimb
// Needs  : X, Y locations
// Output : Alt symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panClimb(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("\x15%4.0f%c"), int(vs) * 1.0, climbchar);
}

/* **************************************************************** */
// Panel  : panHomeAlt
// Needs  : X, Y locations
// Output : Alt symbol and home altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done

void panHomeAlt(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    if(EEPROM.read(SIGN_HA_ON_ADDR) != 0) 
	osd.write( 0x12);
    osd.printf_P(PSTR("%5.0f%c"), (double)(osd_alt_rel * converth), high);
}

/* **************************************************************** */
// Panel  : panVel
// Needs  : X, Y locations
// Output : Velocity value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panVel(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    if(EEPROM.read(SIGN_GS_ON_ADDR) != 0) osd.write(0x14);
    osd.printf_P(PSTR("%3.0f%c"),(double)(osd_groundspeed * converts),spe);
}

/* **************************************************************** */
// Panel  : panAirSpeed
// Needs  : X, Y locations
// Output : Airspeed value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panAirSpeed(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    if(EEPROM.read(SIGN_AS_ON_ADDR) != 0) osd.write(0x13);
    osd.printf_P(PSTR("%3.0f%c"), (double)(osd_airspeed * converts), spe); 
}

/* **************************************************************** */

uint8_t warning;

void check_warn()
{
 uint8_t wmask = 0;
 uint8_t bit, prev_warn;

 if (!one_sec_timer_switch) return;

 if ((osd_fix_type) < 2) 
    wmask |= 1;
 if (osd_airspeed * converts < stall && takeofftime == 1) 
    wmask |= 2;
 if ((osd_airspeed * converts) > (float)overspeed) 
    wmask |= 4;

 if (osd_vbat_A < float(battv)/10.0 || (osd_battery_remaining_A < batt_warn_level && batt_warn_level != 0))
    wmask |= 8;

 if (rssi < rssi_warn_level && rssi != -99 && !rssiraw_on)
    wmask |= 16;

 if(wmask == 0) 
    warning = 0;
 else {
    prev_warn = warning;
    if(warning == 0) warning = 1;
    else             warning = prev_warn+1;

    bit = 1 << (warning-1);

    while(1) {
        if(warning == 6) {
	    warning = 1;
	    bit = 1;
        }
        if(wmask&bit) break;
        warning++;
        bit <<= 1;
    }
    /* stay blank for one cycle for single warning */
    if(warning == prev_warn) warning = 0;
 }

    if (wmask && panel_auto_switch < 3) canswitch = 0;
    else if (ch_raw < 1200) canswitch = 1;
}

// Panel  : panWarn
// Needs  : X, Y locations
// Output : Airspeed value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done


void panWarn(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

#define WARNINGS 5

#ifdef IS_PLANE
    check_warn();

    switch(warning) {
         case 1:
                 osd.printf_P(PSTR("\x20\x4E\x6F\x20\x47\x50\x53\x20\x66\x69\x78\x21"));
                 break;
         case 2:
                 osd.printf_P(PSTR("\x20\x20\x20\x53\x74\x61\x6c\x6c\x21\x20\x20\x20"));
                 break;
         case 3:
                 osd.printf_P(PSTR("\x20\x4f\x76\x65\x72\x53\x70\x65\x65\x64\x21\x20"));
                 break;
         case 4:
                 osd.printf_P(PSTR("\x42\x61\x74\x74\x65\x72\x79\x20\x4c\x6f\x77\x21"));
                 break;
         case 5:
                 osd.printf_P(PSTR("\x20\x20\x4c\x6f\x77\x20\x52\x73\x73\x69\x20\x20"));
    }
#endif


#ifdef IS_COPTER
  if (one_sec_timer_switch == 1){
    boolean warning[]={0,0,0,0,0,0,0}; // Make and clear the array

                // check all warnings at once
                if ((osd_fix_type) < 2) {
                  warning[1] = 1; 
                  warning[0] = 1;
                  }
                if (abs(vs) > stall * 10 && stall >0) {
                  warning[2] = 1; 
                  warning[0] = 1;
                  }
                if ((osd_airspeed * converts) > (float)overspeed && overspeed > 0) {
                  warning[3] = 1; 
                  warning[0] = 1;
                  }
                if (osd_vbat_A < float(battv)/10.0 || (osd_battery_remaining_A < batt_warn_level && batt_warn_level != 0)) {
                  warning[4] = 1; 
                  warning[0] = 1;
                  }
                if (rssi < rssi_warn_level && rssi != -99 && !rssiraw_on) {
                  warning[5] = 1; 
                  warning[0] = 1;
                  }
//                if (eph > 150){  
//                  warning[6] = 1;
//                  warning[0] = 1;
//                  }

	    // TODO надо еще контролировать osd_roll и osd_pitch на превышение кренов.


            // Prepare for printf in rotation
            if (rotation == 0) if (warning[0] == 0 || warning[0] + warning[1] + warning[2] + warning[3] + warning[4] + warning[5] == 2) {
                warning_string = PSTR("\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"); //Blank line
              }else{
                  rotation = 1; 
              } 
            if (rotation == 1) if (warning[1] == 1) {
                warning_string = PSTR("\x20\x4E\x6F\x20\x47\x50\x53\x20\x66\x69\x78\x21"); //No GPS fix!
              }else{
                  rotation = 2; 
              }
            if (rotation == 2) if (warning[2] == 1) {
                warning_string = PSTR("\x48\x69\x67\x68\x20\x56\x53\x70\x65\x65\x64\x21"); //Hi VSpeed!
              }else{
                  rotation = 3; 
              }
            if (rotation == 3) if (warning[3] == 1) {
                warning_string = PSTR("\x20\x4f\x76\x65\x72\x53\x70\x65\x65\x64\x21\x20"); //Over Speed!
              }else{
                  rotation = 4; 
              }
            if (rotation == 4) if (warning[4] == 1) {
                warning_string = PSTR("Battery low!"); //Battery Low!
              }else{
                  rotation = 5; 
              }
            if (rotation == 5) if (warning[5] == 1) {
                warning_string = PSTR("\x20\x20\x4c\x6f\x77\x20\x52\x73\x73\x69\x20\x20"); //Low Rssi
//                  rotation = 6;
              }
            
//            if (rotation == 6) if (warning[6] == 1) {
//                warning_string = PSTR("\x20\x20\x4c\x6f\x77\x20\x48\x44\x4f\x50\x20\x20");            
//              }
            rotation++;
          
          // Auto switch decesion
          if (warning[0] == 1 && panel_auto_switch < 3){
              canswitch = 0;  
          }else if (ch_raw < 1200) {
              canswitch = 1; // выключатель в выключенном состоянии
          }
  if (rotation > WARNINGS) rotation = 0;
  osd.printf_P(warning_string);
#endif

 
  }
}  



/* **************************************************************** */
// Panel  : panThr
// Needs  : X, Y locations
// Output : Throttle value from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panThr(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("%3.0i\x25"),osd_throttle);
}

/* **************************************************************** */
// Panel  : panBatteryPercent
// Needs  : X, Y locations
// Output : Battery state from MAVlink with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panBatteryPercent(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    if (EEPROM.read(OSD_BATT_SHOW_PERCENT_ADDR) == 1){
//        osd.printf_P(PSTR("\x17%3.0i\x25"), 0x17, osd_battery_remaining_A, 0x25);
      osd.printf_P(PSTR("\x88%c\x8e%3.0i%%"), osd_battery_pic_A, osd_battery_remaining_A/255*100);

    }else{
//        osd.printf_P(PSTR("%c%4.0f%c"), 0x17, mah_used, 0x01);
        osd.printf_P(PSTR("\x88%c\x8e%4.0f\x01"), osd_battery_pic_A, mah_used);
    }


}

/* **************************************************************** */
// Panel  : panTime
// Needs  : X, Y locations
// Output : Time from start with symbols
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panTime(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("%2i\x3a%02i"),((int)total_flight_time_seconds/60)%60,(int)total_flight_time_seconds%60);
}

/* **************************************************************** */
// Panel  : panHomeDis
// Needs  : X, Y locations
// Output : Home Symbol with distance to home in meters
// Size   : 1 x 7  (rows x chars)
// Staus  : done

void panHomeDis(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    if ((osd_home_distance * converth) > 9999.0) {
      osd.printf_P(PSTR("\0b%5.2f%c"), ((osd_home_distance * converth) / distconv), distchar);
    }else{
      osd.printf_P(PSTR("\x0B%5.0f%c"), (double)((osd_home_distance) * converth), high);
    }
}


/* **************************************************************** */
// Panel  : panHorizon
// Needs  : X, Y locations
// Output : 5 x 12 Horizon line surrounded by 2 cols (left/right rules)
// Size   : 5 x 14  (rows x chars)
// Staus  : done

void panHorizon(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
  
  // сначала очистим и нарисуем стрелочки. Самая правая колонка - ILS, ее бы лучше вынести в отдельный элемент.

/*
    osd.printf_P(PSTR("\xb2\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb3\x20|"
                      "\xb2\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb3\x20|"
                      "\xC6\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xC5\x20|"
                      "\xb5\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb6\x20|"
                      "\xb5\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb6\x20"));
*/
osd.printf_P(PSTR("\xb2\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb3\x20|"
                      "\xb2\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb3\x20|"
                      "\xC6\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xC5\x20|"
                      "\xb5\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb6\x20|"
                      "\xb5\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\xb6\x20"));
                      
    showHorizon((first_col + 1), first_line);

//#ifdef IS_COPTER
    //Show ground level on  HUD
    showILS(first_col, first_line);
//#endif

    // Птичка по центру
    osd.setPanel(first_col+6, first_line+2);
    osd.printf_P(PSTR("\xb8\xb9"));
}

/* **************************************************************** */
// Panel  : panPitch
// Needs  : X, Y locations
// Output : -+ value of current Pitch from vehicle with degree symbols and pitch symbol
// Size   : 1 x 6  (rows x chars)
// Staus  : done

void panPitch(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("%4i\x05\x07"),osd_pitch);
}

/* **************************************************************** */
// Panel  : panRoll
// Needs  : X, Y locations
// Output : -+ value of current Roll from vehicle with degree symbols and roll symbol
// Size   : 1 x 6  (rows x chars)
// Staus  : done

void panRoll(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("%4i\x05\x06"),osd_roll);
}

/* **************************************************************** */
// Panel  : panBattery A (Voltage 1)
// Needs  : X, Y locations
// Output : Voltage value as in XX.X and symbol of over all battery status
// Size   : 1 x 8  (rows x chars)
// Staus  : done

void panBatt_A(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

/*************** This commented code is for the next ArduPlane Version
    if(osd_battery_remaining_A > 100){
        osd.printf(" %c%5.2f%c", 0xbc, (double)osd_vbat_A, 0x0d);
    else osd.printf("%c%5.2f%c%c", 0xbc, (double)osd_vbat_A, 0x0d, osd_battery_pic_A);
    */

//    osd.printf_P(PSTR("\xBC%5.2f\x0D"), (double)osd_vbat_A);
    osd.printf_P(PSTR("%5.2f\x0D"), (double)osd_vbat_A);
}




//------------------ Panel: Waiting for MAVLink HeartBeats -------------------------------

void panWaitMAVBeats(byte first_col, byte first_line){
  //panLogo();

  osd.setPanel(first_col, first_line);
  osd.printf_P(PSTR("No mavlink data!"));
}


/* **************************************************************** */
// Panel  : panGPSats
// Needs  : X, Y locations
// Output : 1 symbol and number of locked satellites
// Size   : 1 x 5  (rows x chars)
// Staus  : done

void panGPSats(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    byte gps_str = 0x2a;

    if (osd_fix_type == 2) gps_str = 0x1f;
    if (osd_fix_type == 3) gps_str = 0x0f;
    
    if ((eph >= 200) && blinker)
       gps_str = 0x20;
    
    osd.printf_P(PSTR("%c%2i"), gps_str, osd_satellites_visible);    
}

/* **************************************************************** */
// Panel  : panGPS
// Needs  : X, Y locations
// Output : two row numeric value of current GPS location with LAT/LON symbols as on first char
// Size   : 2 x 12  (rows x chars)
// Staus  : done

void panGPS(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("\x03%10.6f|\x04%10.6f"), (double)osd_lat, (double)osd_lon);
}

/* **************************************************************** */
// Panel  : panHeading
// Needs  : X, Y locations
// Output : Symbols with numeric compass heading value
// Size   : 1 x 5  (rows x chars)
// Staus  : not ready

void panHeading(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("%4.0f\x05"), (double)osd_heading);
}

/* **************************************************************** */
// Panel  : panRose
// Needs  : X, Y locations
// Output : a dynamic compass rose that changes along the heading information
// Size   : 2 x 13  (rows x chars)
// Staus  : done

void panRose(byte first_col, byte first_line){
 // generate the heading patern
    char buf_show[12];

    const char buf_Rule[] PROGMEM = {
      0x82,0x80,0x81,0x80,0x81,0x80,
      0x84,0x80,0x81,0x80,0x81,0x80,
      0x83,0x80,0x81,0x80,0x81,0x80,
      0x85,0x80,0x81,0x80,0x81,0x80
     };

  int start = round((osd_heading * 24)/360) - 3;
 
  if(start < 0) start += 24;
  for(uint8_t x=0; x <= 10; x++){
    buf_show[x] = buf_Rule[start];
    if(++start > 23) start = 0;
  }
  buf_show[7] = '\0';


    osd.setPanel(first_col, first_line);

//  osd.printf_P(PSTR("%s|\xc3%s\x87"), "\x20\xc0\xc0\xc0\xc0\xc0\xc7\xc0\xc0\xc0\xc0\xc0\x20", buf_show);
    osd.printf_P(PSTR(                  "\x20\xb7\xb7\xb7\xb4\xb7\xb7\xb7\x20|\xc3%s\x87"), buf_show);
    
//    osd.printf_P(PSTR("%c%s%c"), 0xc3, buf_show, 0x87);
}




/* **************************************************************** */
// Panel  : panWPDir
// Needs  : X, Y locations
// Output : 2 symbols that are combined as one arrow, shows direction to next waypoint
// Size   : 1 x 2  (rows x chars)
// Staus  : not ready

void panWPDir(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
   
    wp_target_bearing_rotate_int = round(((float)wp_target_bearing - osd_heading)/360.0 * 16.0) + 1; //Convert to int 0-16 
    if(wp_target_bearing_rotate_int < 0 ) wp_target_bearing_rotate_int += 16; //normalize  

    showArrow((uint8_t)wp_target_bearing_rotate_int,0);
}

/* **************************************************************** */
// Panel  : panWPDis
// Needs  : X, Y locations
// Output : W then distance in Km - Distance to next waypoint
// Size   : 1 x 2  (rows x chars)
// Staus  : not ready TODO - CHANGE the Waypoint symbol - Now only a W!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void panWPDis(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

//    wp_target_bearing_rotate_int = ((int)round(((float)wp_target_bearing - osd_heading)/360.0 * 16.0) + 16) % 16 + 1; //[1, 16]

    if (wp_target_bearing > 0){
      wp_target_bearing_rotate_int = round((wp_target_bearing - osd_heading)/360 *16.0) + 1; 
    }else if (wp_target_bearing < 0){
      wp_target_bearing_rotate_int = round(((360 + wp_target_bearing) - osd_heading)/360 *16.0) + 1;
    } 
    if (wp_target_bearing_rotate_int < 0) wp_target_bearing_rotate_int += 16;
    if (wp_target_bearing_rotate_int == 0) wp_target_bearing_rotate_int = 16;
    
    if (xtrack_error > 999) xtrack_error = 999;
    else if (xtrack_error < -999) xtrack_error = -999;

    osd.printf_P(PSTR("\x57\x70%2i %4.0f%c|"), wp_number,(double)((float)(wp_dist) * converth),high);
    showArrow((uint8_t)wp_target_bearing_rotate_int,0);

    if (osd_mode == 10){ // auto
        osd.printf_P(PSTR("\x20\x58\x65%4.0f%c"), (xtrack_error* converth), high);
    }else{
        osd.printf_P(PSTR("\x20\x20\x20\x20\x20\x20\x20\x20"));
    }
}

/* **************************************************************** */
// Panel  : panHomeDir
// Needs  : X, Y locations
// Output : 2 symbols that are combined as one arrow, shows direction to home
// Size   : 1 x 2  (rows x chars)
// Status : not tested

void panHomeDir(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    showArrow((uint8_t)osd_home_direction,0);
}

/* **************************************************************** */
// Panel  : panFlightMode 
// Needs  : X, Y locations
// Output : 2 symbols, one static name symbol and another that changes by flight modes
// Size   : 1 x 2  (rows x chars)
// Status : done

void panFlightMode(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    osd.write( 0x7F);

/* проклятая гарвардская архитектура...
    const char *mode_str[] PROGMEM ={
	PSTR("stab"), //Stabilize	0
	PSTR("acro"), //Acrobatic	1
	PSTR("alth"), //Alt Hold	2
	PSTR("auto"), //Auto		3
	PSTR("guid"), //Guided		4
	PSTR("loit"), //Loiter		5
	PSTR("rtl "), //Return to Launch 6
	PSTR("circ"), //Circle		7
	PSTR("posh"), //Position Hold (Old) 8
	PSTR("land"), //Land		9
	PSTR("oflo"), //OF_Loiter 	10
	PSTR("drif"), //Drift		11
	PSTR("n 12"), //              12
	PSTR("sprt"), //Sport		13
	PSTR("flip"), //Flip		14
	PSTR("tune"), //Tune		15
	PSTR("hold"), //Position Hold (Earlier called Hybrid) 16
    };

    osd.print(mode_str[osd_mode] );

*/

    PGM_P mode_str;

#ifdef IS_COPTER

    switch (osd_mode){
    case 0:
	mode_str = PSTR("stab"); //Stabilize
	break;
	 
    case  1: 
	mode_str = PSTR("acro"); //Acrobatic
	break;
	
    case  2: 
	mode_str = PSTR("alth"); //Alt Hold
	break;
	 
    case  3: 
	mode_str = PSTR("auto"); //Auto
	break;
	 
    case  4: 
	mode_str = PSTR("guid"); //Guided
	break;
	 
    case  5: 
	mode_str = PSTR("loit"); //Loiter
	break;
	 
    case  6: 
	mode_str = PSTR("rtl "); //Return to Launch
	break;
	 
    case  7: 
	mode_str = PSTR("circ"); //Circle
	break;
	 
    case  8: 
	mode_str = PSTR("posi"); //Position Hold (Old)
	break;
	 
    case  9: 
	mode_str = PSTR("land"); //Land
	break;
	 
    case  10: 
	mode_str = PSTR("oflo"); //OF_Loiter
	break;
	 
    case  11: 
	mode_str = PSTR("drif"); //Drift
	break;
	 
    case  13: 
	mode_str = PSTR("sprt"); //Sport
	break;
	 
    case  14: 
	mode_str = PSTR("flip"); //Flip
	break;
	 
    case  15: 
	mode_str = PSTR("tune"); //Tune
	break;
	 
    case  16: 
	mode_str = PSTR("hold"); //Position Hold (Earlier called Hybrid)
	break;
	
    }

#endif
#ifdef IS_PLANE
    if (osd_mode == 0) mode_str = PSTR("manu"); //Manual
    if (osd_mode == 1) mode_str = PSTR("circ"); //CIRCLE
    if (osd_mode == 2) mode_str = PSTR("stab"); //Stabilize
    if (osd_mode == 3) mode_str = PSTR("trai"); //Training
    if (osd_mode == 4) mode_str = PSTR("acro"); //ACRO
    if (osd_mode == 5) mode_str = PSTR("fbwa"); //FLY_BY_WIRE_A
    if (osd_mode == 6) mode_str = PSTR("fbwb"); //FLY_BY_WIRE_B
    if (osd_mode == 7) mode_str = PSTR("cruz"); //Cruise
    if (osd_mode == 8) mode_str = PSTR("atun"); //autotune
    if (osd_mode == 10) mode_str = PSTR("auto"); //AUTO
    if (osd_mode == 11) mode_str = PSTR("rtl "); //Return to Launch.
    if (osd_mode == 12) mode_str = PSTR("loit"); //Loiter
    if (osd_mode == 15) mode_str = PSTR("guid"); //GUIDED
    if (osd_mode == 16) mode_str = PSTR("init"); //initializing
#endif

    osd.printf_P(mode_str );
    osd.write( motor_armed ? 0x86:' ');
}


// ---------------- EXTRA FUNCTIONS ----------------------
// Show those fancy 2 char arrows
void showArrow(uint8_t rotate_arrow,uint8_t method) {  
    char arrow_set1 = 0x90;
    //We trust that we receive rotate_arrow [1, 16] so 
    //it's no needed (rotate_arrow <= 16) in the if clause

    arrow_set1 += rotate_arrow * 2 - 2;

    if(method == 1)      osd.printf_P(PSTR("\x1D%3.0f%c|%c%c%2.0f%c"),(double)(osd_windspeed * converts),spe, arrow_set1, arrow_set1 + 1, (double)(nor_osd_windspeed * converts),spe);
    else if(method == 2) osd.printf_P(PSTR("%c%c%4i\x05"), arrow_set1, arrow_set1 + 1, off_course);
    else 		 osd.printf_P(PSTR("%c%c"),        arrow_set1, arrow_set1 + 1);
}

// Calculate and shows Artificial Horizon
// Smooth horizon by Jörg Rothfuchs
							// with different factors we can adapt do different cam optics
#define AH_PITCH_FACTOR		0.010471976		// conversion factor for pitch
#define AH_ROLL_FACTOR		0.017453293		// conversion factor for roll
#define AH_COLS			12			// number of artificial horizon columns
#define AH_ROWS			5			// number of artificial horizon rows
#define CHAR_COLS		12			// number of MAX7456 char columns
#define CHAR_ROWS		18			// number of MAX7456 char rows
#define CHAR_SPECIAL		9			// number of MAX7456 special chars for the artificial horizon
#define AH_TOTAL_LINES		AH_ROWS * CHAR_ROWS	// helper define


#define LINE_SET_STRAIGHT__	(0xC7 - 1)		// code of the first MAX7456 straight char -1
#define LINE_SET_STRAIGHT_O	(0xD0 - 3)		// code of the first MAX7456 straight overflow char -3
#define LINE_SET_P___STAG_1	(0xD1 - 1)		// code of the first MAX7456 positive staggered set 1 char -1
#define LINE_SET_P___STAG_2	(0xDA - 1)		// code of the first MAX7456 positive staggered set 2 char -1
#define LINE_SET_N___STAG_1	(0xE3 - 1)		// code of the first MAX7456 negative staggered set 1 char -1
#define LINE_SET_N___STAG_2	(0xEC - 1)		// code of the first MAX7456 negative staggered set 2 char -1
#define LINE_SET_P_O_STAG_1	(0xF5 - 2)		// code of the first MAX7456 positive overflow staggered set 1 char -2
#define LINE_SET_P_O_STAG_2	(0xF9 - 1)		// code of the first MAX7456 positive overflow staggered set 2 char -1
#define LINE_SET_N_O_STAG_1	(0xF7 - 2)		// code of the first MAX7456 negative overflow staggered set 1 char -2
#define LINE_SET_N_O_STAG_2	(0xFC - 1)		// code of the first MAX7456 negative overflow staggered set 2 char -1


#define OVERFLOW_CHAR_OFFSET	6			// offset for the overflow subvals


#define ANGLE_1			9			// angle above we switch to line set 1
#define ANGLE_2			25			// angle above we switch to line set 2


// Calculate and show artificial horizon
// used formula: y = m * x + n <=> y = tan(a) * x + n
void showHorizon(byte start_col, byte start_row) {
    byte col, row;
    int pitch_line, middle, hit, subval;
    int roll;
    int line_set = LINE_SET_STRAIGHT__;
    int line_set_overflow = LINE_SET_STRAIGHT_O;
    int subval_overflow = 9;
    
    // preset the line char attributes
    roll = osd_roll;
    if ((roll >= 0 && roll < 90) || (roll >= -179 && roll < -90)) {	// positive angle line chars
	roll = roll < 0 ? roll + 179 : roll;
        if (abs(roll) > ANGLE_2) {
	    line_set = LINE_SET_P___STAG_2;
	    line_set_overflow = LINE_SET_P_O_STAG_2;
            subval_overflow = 7;
	} else if (abs(roll) > ANGLE_1) {
	    line_set = LINE_SET_P___STAG_1;
	    line_set_overflow = LINE_SET_P_O_STAG_1;
            subval_overflow = 8;
	}
    } else {								// negative angle line chars
	roll = roll > 90 ? roll - 179 : roll;
        if (abs(roll) > ANGLE_2) {
	    line_set = LINE_SET_N___STAG_2;
	    line_set_overflow = LINE_SET_N_O_STAG_2;
            subval_overflow = 7;
	} else if (abs(roll) > ANGLE_1) {
	    line_set = LINE_SET_N___STAG_1;
	    line_set_overflow = LINE_SET_N_O_STAG_1;
            subval_overflow = 8;
	}
    }
    
    pitch_line = round(tan(-AH_PITCH_FACTOR * osd_pitch) * AH_TOTAL_LINES) + AH_TOTAL_LINES/2;	// 90 total lines
    for (col=1; col<=AH_COLS; col++) {
        middle = col * CHAR_COLS - (AH_COLS/2 * CHAR_COLS) - CHAR_COLS/2;	  // -66 to +66	center X point at middle of each column
        hit = tan(AH_ROLL_FACTOR * osd_roll) * middle + pitch_line;	          // 1 to 90	calculating hit point on Y plus offset
        if (hit >= 1 && hit <= AH_TOTAL_LINES) {
	    row = (hit-1) / CHAR_ROWS;						  // 0 to 4 bottom-up
	    subval = (hit - (row * CHAR_ROWS) + 1) / (CHAR_ROWS / CHAR_SPECIAL);  // 1 to 9
	    
	    // print the line char
            osd.openSingle(start_col + col - 1, start_row + AH_ROWS - row - 1);
            osd.write(line_set + subval);
	    
	    // check if we have to print an overflow line char
	    if (subval >= subval_overflow && row < 4) {	// only if it is a char which needs overflow and if it is not the upper most row
                osd.openSingle(start_col + col - 1, start_row + AH_ROWS - row - 2);
                osd.write( line_set_overflow + subval - OVERFLOW_CHAR_OFFSET);
	    }
        }
    }
}


void showILS(byte start_col, byte start_row) {
#ifdef IS_COPTER // Calculate and shows verical speed aid


    //Show line on panel center because horizon line can be
    //high or low depending on pitch attitude
    char subval_char = 0xCF;

    //shift alt interval from [-5, 5] to [0, 10] interval, so we
    //can work with remainders.
    //We are using a 0.2 altitude units as resolution (1 decimal place)
    //so convert we convert it to times 10 to work 
    //only with integers and save some bytes

    //int alt = (osd_alt_to_home * converth + 5) * 10;
    char alt = (osd_alt_rel * converth + 5) * 4.4; //44 possible position 5 rows times 9 chars
    
    if((alt < 44) && (alt > 0)){
        //We have 9 possible chars
        //(alt * 5) -> 5 represents 1/5 which is our resolution. Every single
        //line (char) change represents 0,2 altitude units
        //% 10 -> Represents our 10 possible characters
        //9 - -> Inverts our selected char because when we gain altitude
        //the selected char has a lower position in memory
        //+ C7 -> Is the memory displacement od the first altitude charecter 
        //in memory (it starts at 0x05
        //subval_char = (99 - ((alt * 5) % 100)) / 9 + 0xC7;
        subval_char = (8 - (alt  % 9)) + 0xC7; // 9 уровней C7-CF
        //Each row represents 9 altitude units
        start_row += (alt / 9);
    }
    else if(alt >= 44){
        //Copter is too high. Ground is way too low to show on panel, 
        //so show down arrow at the bottom
        subval_char =0x2E; // 0xC8; C8 сейчас это совсем не стрелка
        start_row += 4;
    }

    //Enough calculations. Let's show the result
    osd.openSingle(start_col + AH_COLS + 2, start_row);
    osd.write( subval_char);
#endif

#ifdef IS_PLANE // Calculate and shows ILS

  //Vertical calculation
    int currentAngleDisplacement = atan(osd_alt_to_home / osd_home_distance) * 57.2957795 - 10;
    //Calc current char position.
    //int numberOfPixels = CHAR_ROWS * AH_ROWS;
    int totalNumberOfLines = 9 * AH_ROWS; //9 chars in chartset for vertical line
    int linePosition = totalNumberOfLines * currentAngleDisplacement / 10 + (totalNumberOfLines / 2); //+-5 degrees
    int charPosition = linePosition / 9;
    int selectedChar = 9 - (linePosition % 9) + 0xC7;
    if(charPosition >= 0 && charPosition <= CHAR_ROWS) {
      osd.openSingle(start_col + AH_COLS + 2, start_row + charPosition);
      osd.write(selectedChar);
    }

  //Horizontal calculation
    currentAngleDisplacement = osd_home_direction - takeoff_heading;
    //Horizontal calculation
    totalNumberOfLines = 6 * AH_COLS; //6 chars in chartset for vertical line
    linePosition = totalNumberOfLines * currentAngleDisplacement / 10 + (totalNumberOfLines / 2); //+-5 degrees
    charPosition = linePosition / 6;
    selectedChar = (linePosition % 6) + 0xBF;
    if(charPosition >= 0 && charPosition <= CHAR_COLS)  {
      osd.openSingle(start_col + charPosition, start_row + AH_ROWS + 1);
      osd.write( selectedChar);
    }
#endif
}

void do_converts()
{
    if (EEPROM.read(measure_ADDR) == 0) { // метрическая система
        converts = 3.6; 
        converth = 1.0;
        spe = 0x10;
        high = 0x0c;
        temps = 0xba;
        tempconv = 10;
        tempconvAdd = 0;
        distchar = 0x1b;
        distconv = 1000;
        climbchar = 0x1a;
    } else {
        converts = 2.23;
        converth = 3.28;
        spe = 0x19;
        high = 0x66;
        temps = 0xbb;
        tempconv = 18;
        tempconvAdd = 3200;
        distchar = 0x1c;
        distconv = 5280;
        climbchar = 0x1e;
    }
}

void timers()
{
  if (one_sec_timer_switch == 1){ 
    one_sec_timer = millis() + 1000;
    one_sec_timer_switch = 0;
    blinker = !blinker;
  }
  if (millis() > one_sec_timer) one_sec_timer_switch = 1;
}


//* **************************************************************** */
// Panel  : panTune
// Needs  : X, Y locations
// Output : Current symbol and altitude value in meters from MAVLink
// Size   : 1 x 7Hea  (rows x chars)
// Staus  : done
    
void panTune(byte first_col, byte first_line){
  osd.setPanel(first_col, first_line);

#ifdef IS_COPTER
  osd.printf_P(PSTR("\x4E\x52%2.0f\x05|\x4E\x50%2.0f\x05|\x4E\x48%4.0i\x05|\x54\x42%4.0i\x05|\x41\x45%3.0f%c|\x58\x45%3.0f\x6D|\x41\x45%3.0f%c"), (nav_roll), 
				       (nav_pitch), 
				    			 (nav_bearing),  
				    					    (wp_target_bearing), 
				    							        (alt_error * converth), high, 
				    							    		     (xtrack_error), 0x6D, 
				    							    		    			((aspd_error / 100.0) * converts), spe);
#endif
#ifdef IS_PLANE
    osd.printf_P(PSTR("\xb0%3.0f%c|\xb1%3.0f%c"), (alt_error * converth * -1), high, ((aspd_error / 100.0) * converts), spe);
#endif
}




/* **************************************************************** */
// Panel  : panCenter
// Needs  : X, Y locations
// Output : 2 row croshair symbol created by 2 x 4 chars
// Size   : 2 x 4  (rows x chars)
// Staus  : done

void panCenter(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    osd.printf_P(PSTR("\x05\x03\x04\x05|\x15\x13\x14\x15"));
}



#if 0 // unused

/* **************************************************************** */
// Panel  : panSetup
// Needs  : Nothing, uses whole screen
// Output : The settings menu
// Size   : 3 x ?? (rows x chars)
// Staus  : done

void panSetup(){

    if (millis() > text_timer){
        text_timer = millis() + 500;

        osd.clear();
        osd.setPanel(5, 7);

        if (chan1_raw_middle == 0 && chan2_raw_middle == 0){
            chan1_raw_middle = chan1_raw;
            chan2_raw_middle = chan2_raw;
        }

        if ((chan2_raw - 100) > chan2_raw_middle ) setup_menu++;  //= setup_menu + 1;
        else if ((chan2_raw + 100) < chan2_raw_middle ) setup_menu--;  //= setup_menu - 1;
        if (setup_menu < 0) setup_menu = 0;
        else if (setup_menu > 2) setup_menu = 2;


        switch (setup_menu){
        case 0:
            {
                osd.printf_P(PSTR("    Overspeed    "));
                osd.printf("%3.0i%c", overspeed, spe);
                overspeed = change_val(overspeed, overspeed_ADDR);
                break;
            }
        case 1:
            {
                osd.printf_P(PSTR("   Stall Speed   "));
                osd.printf("%3.0i%c", stall , spe);
                //overwritedisplay();
                stall = change_val(stall, stall_ADDR);
                break;
            }
        case 2:
            {
                osd.printf_P(PSTR("Battery warning "));
                osd.printf("%3.1f\x76", float(battv)/10.0);
                battv = change_val(battv, battv_ADDR);
                break;
            }
        }
    }
}

int change_val(uint8_t value, int address)
{
    uint8_t value_old = value;
    if (chan1_raw > chan1_raw_middle + 100) value--;
    if (chan1_raw  < chan1_raw_middle - 100) value++;
    if(value != value_old && setup_menu ) EEPROM.write(address, value);
    return value;
}

/* **************************************************************** */
// Panel  : panGPL
// Needs  : X, Y locations
// Output : 1 static symbol with changing FIX symbol
// Size   : 1 x 2  (rows x chars)
// Staus  : done

void panGPL(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    if(osd_fix_type == 0 || osd_fix_type == 1) 
        osd.printf_P(PSTR("\x10\x20"));
    else if(osd_fix_type == 2 || osd_fix_type == 3)
        osd.printf_P(PSTR("\x11\x20"));

    
}

/* **************************************************************** */
// Panel  : panMavBeat
// Needs  : X, Y locations
// Output : 2 symbols, one static and one that blinks on every 50th received 
//          mavlink packet.
// Size   : 1 x 2  (rows x chars)
// Staus  : done

void panMavBeat(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    if(mavbeat == 1){
        osd.printf_P(PSTR("\xEA\xEC"));
        mavbeat = 0;
    }
    else{
        osd.printf_P(PSTR("\xEA\xEB"));
    }
}


/* **************************************************************** */
// Panel  : panBattery B (Voltage 2)
// Needs  : X, Y locations
// Output : Voltage value as in XX.X and symbol of over all battery status
// Size   : 1 x 8  (rows x chars)
// Status : done

void panBatt_B(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);

    osd.printf_P(PSTR("%5.2f\x0D"), (double)osd_vbat_B);
}

/* **************************************************************** */
// Panel  : panCh
// Needs  : X, Y locations
// Output : Scaled channel values from MAVLink
// Size   
// Staus  : done

void panCh(byte first_col, byte first_line){
    osd.setPanel(first_col, first_line);
    
    osd.printf_P(PSTR("C1%5i|C2%5i|C3%5i|C4%5i|C5%5i|C6%5i"), 
		      chan1_raw, chan2_raw, chan3_raw, chan4_raw, chan5_raw, chan6_raw); 
}


#endif