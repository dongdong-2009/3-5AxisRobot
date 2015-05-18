#! /bin/sh

export set QWS_DISPLAY="LinuxFB:mmWidth=192:mmHeight=144:0"
export set QWS_SIZE="800x600"

cd /opt/Qt/apps
./Multi-axisManipulatorSystem -qws -style cleanlooks -stylesheet stylesheet/global.qss
