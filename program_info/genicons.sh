#/bin/bash

# ICO

inkscape -w 16 -h 16 -o QFRCScouter_16.png QFRCScouter.svg
inkscape -w 24 -h 24 -o QFRCScouter_24.png QFRCScouter.svg
inkscape -w 32 -h 32 -o QFRCScouter_32.png QFRCScouter.svg
inkscape -w 48 -h 48 -o QFRCScouter_48.png QFRCScouter.svg
inkscape -w 64 -h 64 -o QFRCScouter_64.png QFRCScouter.svg
inkscape -w 128 -h 128 -o QFRCScouter_128.png QFRCScouter.svg

convert QFRCScouter_128.png QFRCScouter_64.png QFRCScouter_48.png QFRCScouter_32.png QFRCScouter_24.png QFRCScouter_16.png QFRCScouter.ico

rm -f QFRCScouter_*.png

inkscape -w 1024 -h 1024 -o QFRCScouter_1024.png QFRCScouter.svg

png2icns QFRCScouter.icns QFRCScouter_1024.png

rm -f QFRCScouter_*.png
