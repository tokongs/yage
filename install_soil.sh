#!/bin/sh
wget http://www.lonesock.net/files/soil.zip
unzip soil.zip
cd 'Simple OpenGL Image Library'/projects/makefile
make && sudo make install