#!/bin/sh

rm -rf *.o
if [ -d ./out ]; then
	mv v4l2_capture ./out/
else
	mkdir -m 775 out
	mv v4l2_capture ./out/
fi
