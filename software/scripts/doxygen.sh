#/bin/bash
set -ex

doxygen Doxyfile

# docker run -t --user 1000:1000 -v $PWD:/home/newuser/src -w /home/newuser/src fossasystems/fossasat /bin/bash scripts/doxygen.sh
