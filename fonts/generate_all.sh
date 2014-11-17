#!/bin/bash


# Requires saxon9ee and phantomjs
# saxon9ee can be aliased from Oxygen in ~/.bash_profile
# alias saxon9ee="java -jar /Applications/oxygen/lib/saxon9ee.jar"

shopt -s expand_aliases
[[ -f ~/.bash_profile ]] && source ~/.bash_profile

if [ ! -e tmp ]; then
    mkdir tmp
fi

if ! command -v saxon9ee >/dev/null 2>&1 ; then
	echo >&2 "Saxon9ee is required.  Aborting.";
	exit 1;
fi

if ! command -v phantomjs >/dev/null 2>&1 ; then
	echo >&2 "Phantomjs is required.  Aborting.";
	exit 1;
fi

echo "Generating C++ files ..."
# saxon9ee supported.xsl generate-h.xsl
# saxon9ee supported.xsl generate-cpp.xsl

echo "Generating Bravura files ..."
saxon9ee Bravura.svg extract-glyphs.xsl > tmp/Bravura-bounding-boxes.svg
phantomjs generate-bbox.js tmp/Bravura-bounding-boxes.svg ../data/Bravura.xml

echo "Generating Leipzig files ..."
saxon9ee Leipzig.svg extract-glyphs.xsl > tmp/Leipzig-bounding-boxes.svg
phantomjs generate-bbox.js tmp/Leipzig-bounding-boxes.svg ../data/Leipzig.xml

echo "Done!"
