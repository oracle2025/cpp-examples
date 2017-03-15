#!/bin/sh
fswatch -o *.cpp *.h *.fl | xargs -n1 ./make.sh
