#!/usr/bin/env bash

cd /build/documentation || {
  echo "Could not find /build/documentation, exiting"
  exit 1
}

CURRENT_DIR=$(pwd)
MERMAID_DIR="source"

OLF_IFS=${IFS}
ICON_PACKS=(@iconify-json/{codicon,devicon,logos,material-symbols,mdi,solar})
IFS=" "
MMDC="/home/mermaidcli/node_modules/.bin/mmdc -p /puppeteer-config.json --iconPacks ${ICON_PACKS[*]}"
IFS=${OLF_IFS}

echo "Icon pack list"
for i in ${ICON_PACKS[*]}; do
  echo "    - $i"
done

for FILE in $(find ${MERMAID_DIR} -type f -name '*.mmd'); do
  echo "Processing ${FILE}"

  {
    cat ${FILE} | grep -e '%% transparent' && ARG='-b transparent'
  } || ARG=""

  SVG_FILE="${FILE%%.mmd}.svg"
  ${MMDC} ${ARG} -i "${FILE}" -o "${SVG_FILE}" &
done

wait