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
    && arduino-cli core install arduino:avr
