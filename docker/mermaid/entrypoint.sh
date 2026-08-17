#!/usr/bin/env bash

cd /build/documentation || {
  echo "Could not find /build/documentation, exiting"
  exit 1
}

CURRENT_DIR=$(pwd)
MERMAID_DIR="mermaid"

OLF_IFS=${IFS}
ICON_PACKS=(@iconify-json/{material-symbols,mdi,solar})
IFS=" "
MMDC="/home/mermaidcli/node_modules/.bin/mmdc -p /puppeteer-config.json --iconPacks ${ICON_PACKS[*]}"
IFS=${OLF_IFS}
for DIR_TO_PROCESS in $(find ${MERMAID_DIR} -type d); do
  if [[ "${DIR_TO_PROCESS}" == "${MERMAID_DIR}" ]]; then
    continue
  fi

  echo "Processing ${DIR_TO_PROCESS}"


  cd "${DIR_TO_PROCESS}" || {
    echo "Could not cd into ${DIR_TO_PROCESS}, exiting"
     exit 1
  }

  FILES=$(find . -maxdepth 1 -type f -name '*.mmd')

  for FILE in ${FILES}; do
    SVG_FILE="${FILE%%.mmd}.svg"
    ${MMDC} -i "${FILE}" -o "${SVG_FILE}"
  done

  cd "${CURRENT_DIR}" || {
    echo "Could not restore current directory, exiting"
    exit 1
  }
done

for SVG_FILE in $(find ${MERMAID_DIR} -type f -name '*.svg'); do
  OUT_FILE="source/${SVG_FILE##"${MERMAID_DIR}"}"
  mv "${SVG_FILE}" "${OUT_FILE}"
done