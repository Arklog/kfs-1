#!/usr/bin/env bash

cd /build/documentation || {
  echo "Could not find /build/documentation, exiting"
  exit 1
}

CURRENT_DIR=$(pwd)
MERMAID_DIR="mermaid"

for DIR_TO_PROCESS in $(find ${MERMAID_DIR} -type d); do
  if [[ "${DIR_TO_PROCESS}" == "${MERMAID_DIR}" ]]; then
    continue
  fi

  echo "Processing ${DIR_TO_PROCESS}"


  cd ${DIR_TO_PROCESS} || {
    echo "Could not cd into ${DIR_TO_PROCESS}, exiting"
     exit 1
  }

  FILES=$(find . -maxdepth 1 -type f -name '*.md')

  mermaid -s ${FILES}

  SVG_DIR="${CURRENT_DIR}/source/${DIR_TO_PROCESS/mermaid\///}"
  echo ${SVG_DIR}

  find . -maxdepth 1 -type f -name '*.svg' -exec mv {} "${SVG_DIR}" \;

  cd "${CURRENT_DIR}" || {
    echo "Could not restore current directory, exiting"
    exit 1
  }

done