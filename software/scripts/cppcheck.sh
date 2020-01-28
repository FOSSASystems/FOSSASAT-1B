#/bin/bash
set -ex

cppcheck --version

cppcheck --language=c++ -f \
    -DRADIOLIB_VERSION=0x03010000 -DRADIOLIB_STATIC_ONLY \
    --enable=all --suppress=missingIncludeSystem --inconclusive --inline-suppr --error-exitcode=1 \
    -IFossaSat1B FossaSat1B FossaSat1B/FossaSat1B.ino
    #--platform=avr8

# docker run -t --user 1000:1000 -v $PWD:/home/newuser/src -v $PWD/../Arduino:/home/newuser/Arduino -w /home/newuser/src fossasystems/fossasat /bin/bash scripts/cppcheck.sh
