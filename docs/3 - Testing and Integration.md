
# 3 - Testing and Integration

## Changelog
|Date|Description|Author|
|--|--|--|
|08/01/2020|Created initial document.|RB|
|27/01/2020|Updated to include successful test result.|RB|


## Testing
Use your discretion when intrepreting the successful result of a test, if unsure, contact FOSSA Systems at our discord channel.

### Main Program
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successful Result|
|--|--|--|--|--|--|
|MAINPROGT1|Startup configuration.||||Once the program has started, are all the pins, components and internal code configured correctly? Do they match the indended use?|
|MAINPROGT2|Test pin configuration.||||Do all pins attach to their intended component pin correctly?| 
|MAINPROGT3|Test radio error mode handling.|||| Are all the radio exceptions created handled?|
|MAINPROGT4|Confirm the MCU has enough resources to run the software.||||When the software is executed on the target hardware, does it run the entire program without having memory issues?.|
|MAINPROGT5|Check that the satellite transmits.|||| Can the satellite transmissions be received by a radio?
|MAINPROGT6|Check that the satellite can recieve trasmissions.|||| Can the satellite receive transmissions?|
|MAINPROGT7|Check that the radio re-configures successfully.||||When the radio is changed, does the satellite still transmit and receive correctly?|
|MAINPROGT8|Check that the MCU can be delayed by up to 10 minutes.||||When the satellite is delayed, does it react the way you intended?|
|MAINPROGT9|Check that the MCU can run the software system for at least a week.||||When you run the software on the related hardware, does it run how it should for a long time?| 
|MAINPROGT10|Check that the hardware watchdog is signalled correctly.||||Does the hardware watchdog cause any issues with restarting during its operation? For example causing restarts in long functions?|
|MAINPROGT11|Check that the hardware watchdog does not switch the satellite off during transmission.||||When the satellite transmits in any mode, does it correctly send transmissions without the watchdog interefering, even with long transmissions|
|MAINPROGT12|Check the software does not enter any restart loops.||||Does the code of the satellite enter any sections of code that cause it to restart over and over again? (check restart command useage)|

## Deployment
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successful Result|
|--|--|--|--|--|--|
|DEPLOYT1|Test the deployment sequence in scenarios; debugging, integration and jettison.||||Does the deployment sequence run correctly in these 3 scenarios? the debugging deployment sequence, integration and jettison sequences are different.|
|DEPLOYT2|Check that the deployment sequence writes to the EEPROM.|||| When the deployment sequence runs in jettison mode, does it correctly save its state to the EEPROM?|
|DEPLOYT3|Check that the deployment sequence does not run if the EEPROM state has been set.||||If the deployment sequence has ran, does it run again?|
|DEPLOYT4|Check that the deployment sequence enable time is suitable.||||When the satellite powers the deployment mechanism, does it work correctly?| 
|DEPLOYT5|Confirm that a system information transmission is sent before the deployment sequence begins.||||Before the deployment sequence begins, does it send a transmission to notify receivers that it is about to occur?| 
|DEPLOYT6|Check that the deployment sequence transmits a success transmission afterwards.||||After the deployment sequence, does it tell receivers that it has occured?|
|DEPLOYT7|Check that the deployment system returns the correct value for its current state.||||When the satellite restarts, does it load the correct value from the EEPROM?|

## Power Control
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successfull Result|
|--|--|--|--|--|--|
|POWCONT1|Check the battery charging state changes when the temperature is >0 and <0 degrees Celsius.||||Simulate the sub-0 scenario by override the temperature sensor, does the battery charging react accordingly?| 
|POWCONT12|Check the battery charging circuit (MPPT) is switched on and off correctly.||||When using the MPPT circuit, does it switch on and off without affecting other areas of code? (check call graph)|

## Automatic Interval Control
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successful Result|
|--|--|--|--|--|--|
|AUTOINT1|Check that the intervals returned for a given battery charged level matches the specified table of delays.||||Simulate the battery charging level at the specified thresholds (using bounds testing too) and check the interval changes according to the specified delays (see Julian for spec)|
|AUTOINT2|Check that the maximum and minimum intervals do not cause errors. (resetting loops)||||When the satellite is delayed, does it restart when it should? does it get into a restart loop anywhere? check this| 
|AUTOINT3|Check if the low power mode is enabled, if so force delay.||||If the low power mode is enabled, then make sure that the maximum interval for battery charging is used to maximise charging.
|AUTOINT4|Check if the interval control is disabled, if so force no delay.||||If the interval control is disabled, then test that there is no interval delay.|

## Hardware Interface
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successful Result|
|--|--|--|--|--|--|
|HARDINT1|Test the bounds and normal readings of voltages. (Volts)||||Check that the voltage readings are ok, different scenarios such as broken component, disconnected component.etc|
|HARDINT2|Check that the battery voltage is output when the MPPT is disabled.||||When the MPPT is disabled, make sure that the battery voltage is output.|
|HARDINT3|Check that the battery charging voltage is output when the MPPT is enabled. (Volts)||||When the MPPT is enabled, double check that the voltage it reads matches the battery charging voltage.|
|HARDINT4|Test that the satellite restarts when the hardware watchdog is not given a signal.||||Disconnect the watchdog, does the satellite restart?|
|HARDINT5|Check that the battery charging voltage is output correctly. (Amperes)||||Doublecheck that the battery charging voltage reads correct values i.e. values that make sense.|
|HARDINT6|Check that the battery voltage reading is output correctly. (Volts)||||double check that the battery voltage read is correct and makes sense.|
|HARDINT7|Check that the solar cell's voltage readings are correct. (Volts)||||Double check the voltage readings.|
|HARDINT8|Check that the battery temperature reading is correct. (Celsius)||||Double check the battery temperature readings are ok.|
|HARDINT9|Check that the battery voltage reading is output correctly.||||Double check that the battery voltage|
|HARDINT10 (REMOVED DUPLICATE OF HARDINT7)|Check that the watchdog heartbeat signal can be enabled and disabled. (REMOVED DUPLICATE OF HARDINT7)|(REMOVED DUPLICATE OF HARDINT7)|(REMOVED DUPLICATE OF HARDINT7)|(REMOVED DUPLICATE OF HARDINT7)|(REMOVED DUPLICATE OF HARDINT7)|
|HARDINT11|Check that the sensors are configured correctly.||||Look at all the sensor readings together, do they all make sense?|

## Safety & Security
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successful Result|
|--|--|--|--|--|--|
|SAFESECT1|Check that the satellite correctly handles LoRa radio codes.||||When the radio outputs errors, how are they handled? check the failure modes - consult team discord to report unknown failure mode reponses.|
|SAFESECT2|Check that the transmissions content are safe and secure.||||Transmissions do not affect other satellites negatively, make sure encrypted transmissions are encrypted by receiving them.|
|SAFESECT3|Check that the EEPROM values for errors and handle them.||||If the eeprom values return errors, how are they handled?|

## Communication
|Reference ID|Description|Tested (Y/N)|Tested Date (dd-mm-yyyy|Status|Successful Result|
|--|--|--|--|--|--|
|COMMST1|Test the enable and disabling of transmissions.||||When the transmissions are enabled and disabled, does the satellite stop transmitting and start transmitting again correctly?|
|COMMST2|Test the repeater command.||||Send the satellite a repeater command and receive it with a radio.|
|COMMST3|Test the ping-pong command.||||Send a PING command to the satellite and receive a PONG command from a seperate radio.|
|COMMST4|Test the callsign change command.||||Send the satellite a callsign change command and then receive a transmissions of the new callsign|
|COMMST5|Test the command security features.||||Make sure protected security features cannot be invoked without permission|
|COMMST6|Test that the satellite transmits a notification when it powers on.|||||Check that when you start the satellite, it sends you information to validate that it has turned on|
|COMMST7|Test that the satellite transmits a notification after it deploys.||||Run a deployment sequence in jettison mode and then see if you can receive a transmission.|
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
