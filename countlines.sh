#!/bin/bash
cd "`dirname $0`"
find src -type f -exec cat {} + | wc -l
