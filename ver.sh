#!/bin/sh

devour vlc "$1" && mv "$1" "[ok]_$1"

exit 0
