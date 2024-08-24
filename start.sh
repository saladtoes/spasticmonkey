#!/bin/sh 
 
Xephyr :5 -terminate -screen 1280x720 &
sleep 3
DISPLAY=:5 ./spasticmonkey & 
DISPLAY=:5 ./autostart.sh
