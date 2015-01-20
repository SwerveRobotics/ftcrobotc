#pragma config(Sensor, S1,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-eopd-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * HTCS-driver.h provides an API for the HiTechnic EOPD Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Now uses HTSMUX driver which has been split from common.h\n
 *        HTSMUX initialisation and scanning functions have been removed\n
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.2
 */

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-eopd.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor HTEOPD = msensor_S1_1;

task main() {
  int _raw = 0;
  int _processed = 0;

  // Standard range is set to short range
  bool shortrange = true;

  nNxtButtonTask  = -2;

  eraseDisplay();
  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "EOPD");
  nxtDisplayCenteredTextLine(3, "SMUX Test");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and sensor to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  nxtDisplayCenteredTextLine(5, "Press enter to");
  nxtDisplayCenteredTextLine(6, "switch between");
  nxtDisplayCenteredTextLine(7, "ranges");
  wait1Msec(2000);
  eraseDisplay();

  // Set the sensor to short range
  HTEOPDsetShortRange(HTEOPD);

  while(true) {
    if (time1[T1] > 1000) {
      if (shortrange == false) {
        // set the sensor to short range and display this
        HTEOPDsetShortRange(HTEOPD);
        nxtDisplayClearTextLine(1);
        nxtDisplayTextLine(1, "Short range");
        shortrange = true;
      } else {
        // set the sensor to long range and display this
        HTEOPDsetLongRange(HTEOPD);
        nxtDisplayClearTextLine(1);
        nxtDisplayTextLine(1, "Long range");
        shortrange = false;
      }
	    PlaySound(soundBeepBeep);
	    while(bSoundActive)
      time1[T1] = 0;
    }

    while(nNxtButtonPressed != kEnterButton) {
      // Read the raw sensor value
      _raw = HTEOPDreadRaw(HTEOPD);

      // read the processed value which is linear with
      // the distance detected.  Use the processed value
      // when you want to determine distance to an object
      _processed = HTEOPDreadProcessed(HTEOPD);
      nxtDisplayClearTextLine(3);
      nxtDisplayClearTextLine(4);
      nxtDisplayTextLine(4, "Proc:  %4d", _processed);
      nxtDisplayTextLine(3, "Raw :  %4d", _raw);
      wait1Msec(50);
    }
  }
}

/*
 * $Id: hitechnic-eopd-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */
