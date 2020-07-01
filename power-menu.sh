#!/bin/bash

# small power menu using rofi, i3, systemd and pm-utils
# (last 3 dependencies are adjustable below)
# tostiheld, 2016

# icons [⏻][↻][][鈴][]

poweroff_command="systemctl poweroff"
reboot_command="systemctl reboot"
logout_command="i3-msg exit"
hibernate_command="systemctl hibernate"
lock_command="i3lock-fancy"

# you can customise the rofi command all you want ...
rofi_command="rofi -width 20 -hide-scrollbar -bg #586e75 -opacity 100 -padding 5"

options=$'poweroff\nreboot\nlogout\nsuspend\nlock' 

# ... because the essential options (-dmenu and -p) are added here
eval \$"$(echo "$options" | $rofi_command -dmenu -p "")_command"

exit
