#/bin/bash
set -ex

arduino-cli core update-index --additional-urls https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json
arduino-cli lib install RadioLib
git clone https://github.com/FOSSASystems/FOSSA-Comms.git $HOME/Arduino/libraries/FOSSA-Comms
git clone https://github.com/FOSSASystems/tiny-AES-c.git $HOME/Arduino/libraries/tiny-AES-c
git clone https://github.com/jarzebski/Arduino-INA226.git $HOME/Arduino/libraries/Arduino-INA226
#git clone https://github.com/rocketscream/Low-Power.git $HOME/Arduino/libraries/Low-Power
git clone https://github.com/canique/Low-Power-Canique.git $HOME/Arduino/libraries/Low-Power


# docker run -t --user 1000:1000 -v $PWD:/home/newuser/src -v $PWD/../Arduino:/home/newuser/Arduino -w /home/newuser/src fossasystems/fossasat /bin/bash scripts/prepare.sh
