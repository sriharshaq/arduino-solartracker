/***************************************************************************************************************
    This file is part of Solar Tracker using Arduino.

    Solar Tracker using Arduino is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Solar Tracker using Arduino is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Solar Tracker using Arduino.  If not, see <http://www.gnu.org/licenses/>.
/**************************************************************************************************************/



/***
**   File       : gsmModem.cpp
**   Author     : Sriharsha
**   Website    : www.zuna.in
**   Email      : helpzuna@gmail.com
**   Description: This is the GSM Modem (SIM300) driver file for arduino
***/

#include "config.h"
#include "gsmModem.h"

// Globals
const char ConnectCallCmd[10]    = "ATD";
const char disConnectCallCmd[10] = "ATH";

/*** Method      : NA
**   Parameters  : None
**   Return      : unsigned char (0 or 1)
**   Description : This will detect GSM Modem (Return 1: Detected, Return 0: Not Detected) 
**/
unsigned char gsmModem::detectModem(void)
{
  // Add Gsm Modem detect logic now this is dummy
  return 1;
}

/*** Method      : sendSms
**   Parameters  : unsigned char*,unsigned char* (Mobile Number Buffer,Text Message Buffer)
**   Return      : None
**   Description : This will send new sms
**/
void gsmModem::sendSms(char *No,char *Msg)
{
  Serial.print("SMS Sent");
}

/*** Method      : connectCall
**   Parameters  : unsigned char*(Mobile Number Buffer)
**   Return      : None
**   Description : This will connect new call
**/
void gsmModem::connectCall(char *No)
{
  Serial.print(ConnectCallCmd);
  Serial.print(No);
  Serial.println();
}

/*** Method      : disconnectCall
**   Parameters  : unsigned char*(Mobile Number Buffer)
**   Return      : None
**   Description : This will disconnect ongoing call
**/
void gsmModem::disconnectCall(void)
{
  Serial.print(disConnectCallCmd);
  Serial.println();
}
