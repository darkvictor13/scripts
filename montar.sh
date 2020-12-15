#!/bin/bash

DISPONIVEIS=$(lsblk -lp | grep "part $" | awk '{print $1, "(" $4 ")" }')

PARTITION=$(echo "$DISPONIVEIS" | rofi -dmenu -p "Qual partição deseja montar? " | awk '{print $1}')

IS_PENDRIVE=$(printf "Sim\nNão" | rofi -dmenu -p "A partição $PARTITION é um pendrive?")

# echo "$IS_PENDRIVE"

[ "$IS_PENDRIVE" = "Sim" ] && mount "$PARTITION" /home/victor/.Pendrives

exit 0
