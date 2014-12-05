#! /bin/sh

cd 8inch-drivers
chmod +x ./UpdateSystem.sh
./UpdateSystem.sh
cd ..
./UpdateGUI update_cmd -qws

reboot

