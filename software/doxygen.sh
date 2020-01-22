#/bin/bash
set -ex

doxygen Doxyfile

# docker run -t -i -v $PWD:/src -w /src peterus/fossasat /bin/bash doxygen.sh
