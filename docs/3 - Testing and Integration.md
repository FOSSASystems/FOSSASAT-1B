# 3 - Testing and Integration

## Changelog
|Date|Description|Author|
|--|--|--|
|08/01/2020|Created initial document.|RB|


## Testing

### Main Program
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|MAINPROGT1|Startup configuration.|||| 
|MAINPROGT2|Test pin configuration.|||| 
|MAINPROGT3|Test radio error mode handling.|||| 
|MAINPROGT4|Confirm the MCU has enough resources to run the software.||||
|MAINPROGT5|Check that the satellite transmits.|||| 
|MAINPROGT6|Check that the satellite can recieve trasmissions.|||| 
|MAINPROGT7|Check that the radio re-configures successfully.||||
|MAINPROGT8|Check that the MCU can be delayed by up to 10 minutes.||||
|MAINPROGT9|Check that the MCU can run the software system for at least a week.|||| 
|MAINPROGT10|Check that the hardware watchdog is signalled correctly.|||| 
|MAINPROGT11|Check that the hardware watchdog does not switch the satellite off during transmission.||||
|MAINPROGT12|Check the software does not enter any restart loops.||||

## Deployment
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|DEPLOYT1|Test the deployment science in scenarios; debugging, integration and jettison.|||| 
|DEPLOYT2|Check that the deployment sequence writes to the EEPROM.|||| 
|DEPLOYT3|Check that the deployment sequence does not run if the EEPROM state has been set.|||| 
|DEPLOYT4|Check that the deployment sequence enable time is suitable.|||| 
|DEPLOYT5|Confirm that a system information transmission is sent before the deployment sequence begins.|||| 
|DEPLOYT6|Check that the deployment sequence transmits a success transmission afterwards.|||| 
|DEPLOYT7|Check that the deployment system returbs the correct value for its current state.||||

## Power Control
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|POWCONT1|Check the battery charging state changes when the temperature is >0 and <0 degrees Celsius.|||| 
|POWCONT12|Check the battery charging circuit (MPPT) is switch on and off correctly..||||

## Automatic Interval Control
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|AUTOINT1|Check that the intervals returned for a given battery charged level matches the specified table of delays.|||| 
|AUTOINT2|Check that the maximum and minimum intervals do not cause errors. (resetting loops)|||| 
|AUTOINT3|Check if the low power mode is enabled, if so force delay.|||| 
|AUTOINT4|Check if the interval control is disabled, if so force no delay.|||| 

## Hardware Interface
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|HARDINT1|Test the bounds and normal readings of voltages. (Volts)||||
|HARDINT2|Check that the battery voltage is output when the MPPT is disabled.|||| 
|HARDINT3|Check that the battery charging voltage is output when the MPPT is enabled. (Volts)||||
|HARDINT4|Test that the satellite restarts when the hardware watchdog is not given a signal.||||
|HARDINT5|Check that the battery charging voltage is output correctly. (Amperes)||||
|HARDINT6|Check that the battery voltage reading is output correctly. (Volts)||||
|HARDINT7|Check that the solar cell's voltage readings are correct. (Volts)||||
|HARDINT8|Check that the battery temperature reading is correct. (Celsius)||||
|HARDINT9|Check that the battery voltage reading is output correctly.||||
|HARDINT10|Check that the watchdog heartbeat signal can be enabled and disabled.||||
|HARDINT11|Check that the sensors are configured correctly.||||

## Safety & Security
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|SAFESECT1|Check that the satellite correctly handles LoRa radio codes.||||
|SAFESECT2|Check that the transmissions content are safe and secure.||||
|SAFESECT3|Check that the EEPROM values for errors and handle them.||||

## Communication
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|
|--|--|--|--|--|
|COMMST1|Test the enable and disabling of transmissions.||||
|COMMST2|Test the repeater command.||||
|COMMST3|Test the ping-pong command.||||
|COMMST4|Test the callsign change command.||||
|COMMST5|Test the command security features.||||
|COMMST6|Test that the satellite transmits a notification when it powers on.||||
|COMMST7|Test that the satellite transmits a notification after it deploys.||||
|COMMST8|Test that the EEPROM is reset on command.||||
|COMMST9|Test the restart command.||||
|COMMST10|Test the frequency band changing command.||||
|COMMST11|Test the manual deployment command.||||
|COMMST12|Test the manual system information command.||||
|COMMST13|Test the satellite transmits when it shuts down.||||
|COMMST14|Check the transmission timing is correct.||||
|COMMST15|Check the callisgn is transmitted.||||
|COMMST16|Check the spreading factor changes do not break transmissions.||||
|COMMST17|Check the low power mode disable and enable command.||||
|COMMST18|Check the MPPT keep-alive command.||||
|COMMST19|Check the MPPT enable and disable command.||||

## System Verification and Validation

### Requirements Fulfilment

  

## Operation and Maintenance
