#!/bin/bash

ndk-build.cmd -C ./libxhook/jni
ndk-build.cmd -C ./libbiz/jni
ndk-build.cmd -C ./libtest/jni
