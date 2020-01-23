#/bin/bash
set -ex

#arduino-cli compile -v --fqbn arduino:avr:uno FossaSat1B --build-properties compiler.cpp.extra_flags="-DRADIOLIB_STATIC_ONLY -DFOSSASAT_STATIC_ONLY" --warnings=all
arduino-cli compile -v --fqbn arduino:avr:uno FossaSat1B --warnings=all

# docker run -t -i -v $PWD:/src -v $PWD/Arduino:/root/Arduino -w /src fossasystems/fossasat /bin/bash scripts/compile.sh
