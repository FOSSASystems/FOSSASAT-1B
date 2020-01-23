#/bin/bash
set -ex

cppcheck --version

cppcheck --language=c++ -f \
    -DRADIOLIB_VERSION=0x03010000 -DRADIOLIB_STATIC_ONLY \
    --enable=all --suppress=missingIncludeSystem --inconclusive --inline-suppr --error-exitcode=1 \
    -IFossaSat1B FossaSat1B FossaSat1B/FossaSat1B.ino
    #--platform=avr8

# docker run -t -i -v $PWD:/src -v $PWD/Arduino:/root/Arduino -w /src fossasystems/fossasat /bin/bash scripts/cppcheck.sh
