#!/usr/bin/env bash

DISK_NAME=disk.vdi
DISK_SIZE=20M

function help() {
    echo "This script create a vdi disk image"

    echo "OPTIONS:"
    printf "\t%-10s | %-2s: %s\n" '--disk' '-d' "The name of the disk to be created"
    printf "\t%-10s | %-2s: %s\n" '--size' '-s' "The size of the disk to be created"
}

while [[ $# -gt 0 ]]; do
  case $1 in
    --disk|-d)
      DISK_NAME=$2;
      shift 2;
      ;;
    --size|-s)
      DISK_SIZE=$2;
      shift 2;
      ;;
    *)
      echo "unknown argument: $1";
      help ;
      exit 1;
      ;;
  esac
done

if ! whereis qemu >/dev/null; then
  echo "qemu missing"
  exit 1
fi

if ! whereis grub-install >/dev/null; then
  echo "grub-install missing"
  exit 1
fi

qemu-img create -f vdi -o static=on "$DISK_NAME" "$DISK_SIZE" || {
  echo "Failed to create disk: $DISK_NAME of size $DISK_SIZE"
  exit 1
}