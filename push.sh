#!/bin/bash

cd "$(dirname "$0")" || exit 1

git add .
git commit -m "$(date '+%Y-%m-%d %H:%M:%S')"
git push