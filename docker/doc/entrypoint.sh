#!/usr/bin/env bash

cd /build/documentation || {
  echo "Missing /build/documentation directory, exiting"
  exit 1
}

uv sync --no-cache
source .venv/bin/activate

make clean || exit 1
make html || exit 1