#!/bin/sh

echo Bringing Zubax Babel CAN interface up
sudo slcand -o -c -s6 /dev/serial/by-id/usb-Zubax_Robotics_Zubax_Babel_* can0
sudo ifconfig can0 up
echo Done
