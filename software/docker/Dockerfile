FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y build-essential libpcre3 libpcre3-dev python wget git curl \
    && rm -rf /var/lib/apt/lists/*

RUN wget -O /tmp/cppcheck-1.90.tar.gz https://github.com/danmar/cppcheck/archive/1.90.tar.gz \
    && cd /tmp/ && tar xvzf cppcheck-1.90.tar.gz \
    && cd /tmp/cppcheck-1.90 && make install -j8 MATCHCOMPILER=yes FILESDIR=/usr/share/cppcheck HAVE_RULES=yes CXXFLAGS="-O2 -DNDEBUG -Wall -Wno-sign-compare -Wno-unused-function"

ENV USER=root
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/bin sh

