#/bin/bash
set -ex

echo "#define RADIOLIB_STATIC_ONLY" >> $HOME/Arduino/libraries/RadioLib/src/TypeDef.h

arduino-cli compile -v --fqbn arduino:avr:uno FossaSat1B

# docker run -t -i -v $PWD:/src -w /src peterus/fossasat /bin/bash compile.sh
