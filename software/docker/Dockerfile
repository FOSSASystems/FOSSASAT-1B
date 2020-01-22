FROM ubuntu:latest
ENV USER=root

RUN apt-get update \
    && apt-get install -y build-essential libpcre3 libpcre3-dev python wget git curl doxygen graphviz \
    && rm -rf /var/lib/apt/lists/*

RUN wget -O /tmp/cppcheck-1.90.tar.gz https://github.com/danmar/cppcheck/archive/1.90.tar.gz \
    && cd /tmp/ && tar xvzf cppcheck-1.90.tar.gz \
    && cd /tmp/cppcheck-1.90 && make install -j8 MATCHCOMPILER=yes FILESDIR=/usr/share/cppcheck HAVE_RULES=yes CXXFLAGS="-O2 -DNDEBUG -Wall -Wno-sign-compare -Wno-unused-function"

RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/bin sh

RUN arduino-cli core update-index \
    && arduino-cli core install arduino:avr \
    && arduino-cli lib install RadioLib "Adafruit INA260 Library" \
    && git clone https://github.com/FOSSASystems/FOSSA-Comms.git $HOME/Arduino/libraries/FOSSA-Comms \
    && git clone https://github.com/FOSSASystems/tiny-AES-c.git $HOME/Arduino/libraries/tiny-AES-c \
    && git clone https://github.com/jarzebski/Arduino-INA226.git $HOME/Arduino/libraries/Arduino-INA226 \
    && git clone https://github.com/rocketscream/Low-Power.git $HOME/Arduino/libraries/Low-Power
