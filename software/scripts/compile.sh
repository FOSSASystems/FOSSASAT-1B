#/bin/bash
set -ex

#arduino-cli compile -v --fqbn arduino:avr:pro:cpu=8MHzatmega328 FossaSat1B --build-properties compiler.cpp.extra_flags="-DRADIOLIB_STATIC_ONLY -DFOSSASAT_STATIC_ONLY" --warnings=all
arduino-cli compile -v --fqbn MiniCore:avr:328:bootloader=uart0,variant=modelPB,BOD=1v8,LTO=Os_flto,clock=8MHz_internal FossaSat1B --warnings=all --build-path=$PWD/avr-build/
/home/newuser/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-nm \
    --line-numbers --reverse-sort --size-sort --print-size --radix=d FossaSat1B/FossaSat1B.MiniCore.avr.328.elf > FossaSat1B/FossaSat1B.MiniCore.avr.328.nm.txt
/home/newuser/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-objdump \
    -h -S FossaSat1B/FossaSat1B.MiniCore.avr.328.elf > FossaSat1B/FossaSat1B.MiniCore.avr.328.lst.txt

arduino-cli compile -v --fqbn arduino:avr:pro:cpu=8MHzatmega328 FossaSat1B --warnings=all --build-path=$PWD/avr-build/
/home/newuser/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-nm \
    --line-numbers --reverse-sort --size-sort --print-size --radix=d FossaSat1B/FossaSat1B.arduino.avr.pro.elf > FossaSat1B/FossaSat1B.arduino.avr.pro.nm.txt
/home/newuser/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-objdump \
    -h -S FossaSat1B/FossaSat1B.arduino.avr.pro.elf > FossaSat1B/FossaSat1B.arduino.avr.pro.lst.txt

# docker run -t --user 1000:1000 -v $PWD:/home/newuser/src -v $PWD/../Arduino:/home/newuser/Arduino -w /home/newuser/src fossasystems/fossasat /bin/bash scripts/compile.sh
