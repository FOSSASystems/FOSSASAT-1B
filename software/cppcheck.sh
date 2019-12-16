#/bin/bash
set -ex

cppcheck --version

cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --inline-suppr --error-exitcode=1 \
    -IFossaSat1B FossaSat1B FossaSat1B/FossaSat1B.ino
    # --suppress=unusedFunction
    #--platform=avr8

# docker run -t -i -v $PWD:/src -w /src peterus/fossasat /bin/bash cppcheck.sh