FROM alpine:3.10

RUN apk add --no-cache --update \
        bash \
        wget \
        bzip2 \
        tar \
        ca-certificates \
        cppcheck

ENV USER=root
RUN wget -O /tmp/cli.tar.bz2 \
        https://downloads.arduino.cc/arduino-cli/arduino-cli-latest-linux64.tar.bz2 && \
    cd /tmp && \
    mkdir arduino && \
    bunzip2 /tmp/cli.tar.bz2 && \
    tar -xvf /tmp/cli.tar && \
    mv /tmp/arduino-cli* /usr/bin/arduino

RUN arduino core update-index
