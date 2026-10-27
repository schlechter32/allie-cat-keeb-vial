#!/usr/bin/env bash
# Flash the Lily58 halves (RP2040, UF2) one after the other, without root. TRRS can stay connected.
#
# Usage: util/flash_lily58.sh [--build] [config]
#   config defaults to trackpoint_tps43 (files build_lily58/lily58_rev1_vial_<config>_<side>.uf2)
#   --build rebuilds both halves first.

set -euo pipefail

cd "$(dirname "$0")/.."

BUILD=no
if [[ "${1:-}" == "--build" ]]; then
    BUILD=yes
    shift
fi
CONFIG="${1:-trackpoint_tps43}"
LEFT_DEVICE="${CONFIG%%_*}"
RIGHT_DEVICE="${CONFIG#*_}"
FW_DIR="build_lily58"
LABEL="RPI-RP2"

if [[ "$BUILD" == yes ]]; then
    export QMK_HOME="$PWD" QMK_FIRMWARE="$PWD" PYTHONPATH="$PWD/lib/python"
    export PATH="$PWD/bin:$HOME/opt/arm-gnu-toolchain-13.3.rel1-x86_64-arm-none-eabi/bin:$HOME/.venvs/qmk/bin:$PATH"
    for side in left right; do
        python3 build.py --build-single --keyboard lily58/rev1 --keymap vial --user-name holykeebs \
            --left-device "$LEFT_DEVICE" --right-device "$RIGHT_DEVICE" --side "$side"
    done
fi

for side in left right; do
    fw="$FW_DIR/lily58_rev1_vial_${CONFIG}_${side}.uf2"
    if [[ ! -f "$fw" ]]; then
        echo "Missing $fw - run with --build first." >&2
        exit 1
    fi
done

# Prints the mount point of the RP2040 bootloader drive, mounting it if needed.
mount_bootloader() {
    local dev mnt
    dev="$(readlink -f "/dev/disk/by-label/$LABEL" 2>/dev/null || true)"
    [[ -b "$dev" ]] || return 1
    mnt="$(findmnt -nro TARGET -S "$dev" || true)"
    if [[ -z "$mnt" ]]; then
        udisksctl mount -b "$dev" >/dev/null
        mnt="$(findmnt -nro TARGET -S "$dev")"
    fi
    echo "$mnt"
}

flash_side() {
    local side="$1" fw="$FW_DIR/lily58_rev1_vial_${CONFIG}_$1.uf2" mnt="" i
    echo "Waiting for the $LABEL drive..."
    for i in $(seq 1 20); do
        if mnt="$(mount_bootloader)"; then
            break
        fi
        sleep 0.5
    done
    if [[ -z "$mnt" ]]; then
        echo "No $LABEL drive found. Is the $side half really in bootloader mode?" >&2
        return 1
    fi
    echo "Copying $(basename "$fw") to $mnt"
    cp "$fw" "$mnt/"
    sync
    # The RP2040 reboots into the new firmware once the UF2 is written; wait for the drive to go away.
    for i in $(seq 1 20); do
        [[ -e "/dev/disk/by-label/$LABEL" ]] || break
        sleep 0.5
    done
    echo "$side half flashed."
}

echo "Flashing $CONFIG. Keep TRRS connected; only ever plug or unplug it with USB disconnected."
echo "Keymap-only changes just need the left half (answer n for the right)."
echo "Left half: LOWER+RAISE then the Boot key (Esc position). Right half: move USB to it, double-tap reset."
echo

for side in left right; do
    while true; do
        read -r -p "${side^^} half: USB in the $side half and in bootloader ($LABEL drive)? [y]es / [n]o, skip / [q]uit: " answer
        case "$answer" in
            y|Y) if flash_side "$side"; then break; fi ;;
            n|N) echo "Skipping $side half."; break ;;
            q|Q) exit 0 ;;
        esac
    done
    echo
done

echo "Done. If USB is in the right half, move it back to the LEFT half."
