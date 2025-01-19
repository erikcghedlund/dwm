#!/bin/sh

DATE=$(date '+%F')
TIME=$(date '+%X:%N')
MONITORS=$(xrandr | grep 'connected' | grep '2560x1440' | wc -l)

play /usr/share/sounds/freedesktop/stereo/camera-shutter.oga
for i in $(seq $MONITORS); do
    mkdir --parent "/home/erik/Documents/Pictures/Screenshots/$DATE"
    mss --monitor $i --output "/home/erik/Documents/Pictures/Screenshots/$DATE/$TIME-monitor-$i.png"
done
notify-send "Screenshot taken"
