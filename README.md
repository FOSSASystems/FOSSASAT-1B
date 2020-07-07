# FOSSASAT-1B

[![Build Status](https://github.com/FOSSASystems/FOSSASAT-1B/workflows/CI/badge.svg)](https://github.com/FOSSASystems/FOSSASAT-1B/actions)

[Doxygen Documentation](https://fossasystems.github.io/FOSSASAT-1B)

FOSSASAT-1B is slightly modified second iteration of the FOSSASAT-1 satellite launched in December of 2019 Second generation 1P Satellite. It is set to launch with FOSSASAT-2 aboard the Alpha Firefly rocket in Q2-3 2020 into a 300km LEO orbit. The following differences are listed:

- Use of IXYS Cells instead of TrisolX
- No deployable Solar Panels
- Use of a new through-hole burnwire resistor
- Diodes added in MPPT
- DRF1268 has RST and SW connections modified
- Added Watchdog external connection for programming
- Passive attitude control re-designed


## Hardware

PCBs and Schematics are designed using EasyEDA, Java files are available for using them in said interface. 

## Software

The design of the FOSSASAT-1 code is a minimalist C-type structure. Everything is contained within code files whos name represents the functionality of the funtions within.

The core of the communications system uses a large switch that routes received messages to function calls.

The system has a large amount of configuration defines that control all aspects, this is found in the configuration.h/.cpp which again is documented thoroughly to describe it. There is a single function within the configuration "module" that controls the pin setups that can be found here: https://github.com/FOSSASystems/FOSSASAT-1B/blob/master/software/FossaSat1B/configuration.cpp#L32

