#!/bin/sh

SUCKLESS_DEPS="xorg base-devel libX11-devel libXft-devel libXinerama-devel harfbuzz-devel gtk+3-devel gcr-devel webkit2gtk-devel"

sudo xbps-install -Sy $SUCKLESS_DEPS
