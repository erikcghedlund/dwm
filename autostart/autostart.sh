#!/usr/bin/sh

numlockx
setxkbmap workman -variant workman-intl -option caps:swapescape
xsetroot -cursor_name left_ptr
pipewire &
picom &
synapse --startup &

sudo /home/erik/.kill-sshd.sh
sudo /home/erik/.local/bin/fastreboot-reset.sh

nitrogen --restore

sleep 0.3
spotify_player --daemon
parcellite &
ckb-next --background &
caffeine &
/home/erik/side-projects/autorandr-tray/autorandr-tray.py &
NET_WM_BYPASS_COMPOSITOR=1 mangohud steam-native -silent &
discord --ignore-gpu-blocklist --disable-features=UseOzonePlatform --enable-features=VaapiVideoDecoder  --enable-gpu-rasterization --enable-zero-copy --start-minimized &
mattermost-desktop &
kitty /home/erik/.dwm/dwmblocks_hacks.sh
