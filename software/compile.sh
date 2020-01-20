#/bin/bash
set -ex

arduino-cli version
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install RadioLib "Adafruit INA260 Library"

echo "#define RADIOLIB_STATIC_ONLY" >> /root/Arduino/libraries/RadioLib/src/TypeDef.h

git clone https://github.com/FOSSASystems/FOSSA-Comms.git /root/Arduino/libraries/FOSSA-Comms
git clone https://github.com/FOSSASystems/tiny-AES-c.git /root/Arduino/libraries/tiny-AES-c
git clone https://github.com/jarzebski/Arduino-INA226.git /root/Arduino/libraries/Arduino-INA226
git clone https://github.com/rocketscream/Low-Power.git /root/Arduino/libraries/Low-Power

arduino-cli compile -v --fqbn arduino:avr:uno FossaSat1B

# docker run -t -i -v $PWD:/src -w /src peterus/fossasat /bin/bash compile.sh
