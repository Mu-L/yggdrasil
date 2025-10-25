#!/bin/bash

version=darwin$(clang --version | awk '/version/ {print $4}' | cut -d. -f1)
echo "$version"
