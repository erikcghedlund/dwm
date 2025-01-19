#!/usr/bin/sh

xdotool windowunmap $(xdotool search --pid $KITTY_PID)
cd /tmp
nohup $HOME/.dwm/dwmblocks &
sleep 1
exit
