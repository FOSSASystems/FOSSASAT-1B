#/bin/bash
set -ex

#arduino-cli compile -v --fqbn arduino:avr:pro:cpu=8MHzatmega328 FossaSat1B --build-properties compiler.cpp.extra_flags="-DRADIOLIB_STATIC_ONLY -DFOSSASAT_STATIC_ONLY" --warnings=all
arduino-cli compile -v --fqbn arduino:avr:pro:cpu=8MHzatmega328 FossaSat1B --warnings=all --build-path=$PWD/avr-build/
/root/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-nm \
    --line-numbers --reverse-sort --size-sort --print-size --radix=d FossaSat1B/FossaSat1B.arduino.avr.pro.elf > FossaSat1B/FossaSat1B.arduino.avr.pro.nm.txt
/root/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/avr-objdump \
    -h -S FossaSat1B/FossaSat1B.arduino.avr.pro.elf > FossaSat1B/FossaSat1B.arduino.avr.pro.lst.txt

# docker run -t -i -v $PWD:/src -v $PWD/Arduino:/root/Arduino -w /src fossasystems/fossasat /bin/bash scripts/compile.sh
