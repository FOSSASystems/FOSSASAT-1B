#/bin/bash
set -ex

doxygen Doxyfile

# docker run -t -i -v $PWD:/src -w /src fossasystems/fossasat /bin/bash scripts/doxygen.sh
