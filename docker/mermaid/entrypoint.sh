#!/usr/bin/env bash

cd /build/documentation || {
  echo "Could not find /build/documentation, exiting"
  exit 1
}

CURRENT_DIR=$(pwd)
MERMAID_DIR="source"

OLF_IFS=${IFS}
ICON_PACKS=(@iconify-json/{material-symbols,mdi,solar})
IFS=" "
MMDC="/home/mermaidcli/node_modules/.bin/mmdc -p /puppeteer-config.json --iconPacks ${ICON_PACKS[*]}"
IFS=${OLF_IFS}

for FILE in $(find ${MERMAID_DIR} -type f -name '*.mmd'); do
  echo "Processing ${FILE}"

  SVG_FILE="${FILE%%.mmd}.svg"
  ${MMDC} -i "${FILE}" -o "${SVG_FILE}" &
done

wait