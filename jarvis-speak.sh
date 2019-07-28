#!/bin/bash
say() { local IFS=+;/usr/bin/firefox & "https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&tl=en-GB&q="$1; }
say $*