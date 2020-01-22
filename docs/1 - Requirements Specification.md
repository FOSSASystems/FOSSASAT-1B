# 1 - Requirements

## Changelog

|Date|Description|Author|
|--|--|--|
|08/01/2020|Created initial document.|RB|
|08/01/2020|Added HREQ1 to HREQ25.|RB|
|08/01/2020|Added LREQ1 to LREQ5.|RB|
|08/01/2020|Merged FOSSASAT-1 requirements.|RB|
|09/01/2020|Modified requirement for transmissions modes to CW and FSK|RB|

## High Level Requirements Specification
|ID|Description|Author|Functional Requirements (Y/N)|Reference IDs|
|--|--|--|--|--|
|HREQ1|The satellite shall communicate with other generic and widely used radio systems.|RB|Y||
|HREQ2|The satellite must be able to be silenced with a radio command.|RB|Y||
|HREQ3|The satellite must transmit with a callsign.|RB|Y||
|HREQ4|The satellite must protect sensitive commands with encryption|RB|Y||
|HREQ5|The satellite must be able to operate from a battery.|RB|Y||
|HREQ6|The satellite must be able to re-charge the battery using solar panels.|RB|Y||
|HREQ7|The satellite must deploy its antenna|RB|Y||
|HREQ8|The satellite must be able to give a ground station its system information on command.|RB|Y||
|HREQ9|The radio power and operation shall not exceed or violate the regulated standards.|RB|Y||
|HREQ10|The radio communications shall not harm other radio communicating devices.|RB|Y||
|HREQ11|The satellite must be able to restart on command.|RB|Y||
|HREQ12|The satellite must be able to operate with no MCU issues such as memory leaking or halting.|RB|Y||
|HREQ13|The satellite must power on once it is jettisonned|RB|Y||
|HREQ14|The satellite must be able to orbit for at least 1 year.|RB|Y||
|HREQ15|The satellite's radio must be able to be configured remotely.|RB|Y||
|HREQ16|The satellite must be able to handle software and hardware errors.|RB|Y||
|HREQ17|The communications protocol shall be open source.|RB|N||
|HREQ18|The communications protocol must be accessible and simple.|RB|N||
|HREQ19|There must be no malicious transmisions.|RB|N||
|HREQ20|The satellite must be able to operate in a low power mode.|RB|Y||
|HREQ21|The satellite's hardware must be able to withstand all operational conditions.|RB|Y||
|HREQ22|The satellites hardware must be destroy in the atmosphere when de-oribiting.|RB|Y||
|HREQ23|The satellite's oribtal TLE must be available to the public.|RB|Y||
|HREQ24|The satellite must be registered with Satnogs to ensure ground station coverage.|RB|N||
|HREQ25|The satellite must not affect other satellites during launch.|RB|Y||
|HREQ26|The satellite must be able to communicate using the FOSSA Protocol.|RB|Y||

## Low Level Requirements
|Requirement ID|Description|Functional (Y/N)|Author|Reference IDs|
|--|--|--|--|--|
|LREQ1|The satellite must be able to trasmit using CW|Y|RB||
|LREQ2|The satellite must be able to trasmit using GFSK|Y|RB||
|LREQ3|The battery must stop charging if the temperature goes below 0 degrees Celsius.|Y|RB||
|LREQ4|The satellite must enter a low power mode when not in use.|Y|RB||
|LREQ5|Low power mode must be saved and retrieved from EEPROM|Y|RB||
|LREQ6|The callsign must be saved and retrieved from EEPROM|Y|RB||
|LREQ7|The battery temperature switching state must be saced and retrieved from EEPROM.|Y|RB||
|LREQ8|The radio's frequency band must be able to switch between X.XXX, Y.YYY,Z.ZZZ.etc|Y|RB||
|LREQ9|The radio's spreading factor must be able to switch between X,Y,Z.etc|Y|RB||
|LREQ10|The radio's sync word must be compatible with all devices.|Y|RB||
|LREQ11|The satellite must be able to communicate using Morse Code.|Y|RB||
|LREQ12|The satellite must stop transmissions when X command received..|Y|RB||
