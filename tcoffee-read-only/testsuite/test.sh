#!/bin/bash
# set path to java using JAVA_HOME if available, otherwise assume it's on the PATH
JAVA_PATH=${JAVA_HOME:+$JAVA_HOME/jre/bin/}java
$JAVA_PATH -jar ./black-coffee.jar "$@"