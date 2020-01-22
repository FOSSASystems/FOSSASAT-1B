# 0 - Operational Scenarios

## Changelog

|Date|Description|Author|
|--|--|--|
|08/01/2020|Created initial document.|RB|
|20/01/2020|Added initial Scenarios.|Julian Fernandez|

## On The Ground

See document 3. for testing to be carried out on the satellite before integration procedure.

|Name|Description|
|--|--|
|Integration Test|Satellite must be programmed, tested and charged beforehand, if neccesary due to time; check battery voltage via EGSE and serial output, antenna must not deploy in duration of test (3 minutes)|
|Integration Procedure|Satellite timer for deployer is reset via killswitches and then inserted into deployer. EEPROM counter still 0 as no deployment has occured|

## During Launch
|Name|Description|
|--|--|
|Storage Period|Satellite will stay in storage for several weeks without power with killswitches active|
|Launch|Satellite must withstand launch forces, no effect on Software|
## Jettison and Deployment
|Name|Description|
|--|--|
|Initial Jettison|Satellite is activated, Reset counter at 0 hence deployment procedure started|
|Deployment|If battery above x voltage When 3 minutes passed, burn wire for y seconds, else, wait for battery to reach y voltage.
|Wait time|During wait time, satellite is active but not transmitting (like in low power mode), it can recieve.
|Deployment Try 2|If time elapsed is more than 5 hours (timer integrated or cycle counter?), deploy in any case.
|Actual Deployment|When deployment command is carried out, start transmitting.


## Anomalies 
|Name|Description|
|--|--|
|In orbit resets|If satellite resets (can be issued by command or caused by watchdog), counter is increased. For the first 2 resets, deployment procedure occurs in the same manner as explained above|
|Deployment Command|Deployment Command bypasses voltage check|

## Orbital

