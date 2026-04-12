#!/bin/bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
APP_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
WEST_WORKSPACE_DIR="${WEST_WORKSPACE_DIR:-$(cd "$APP_DIR/.." && pwd)}"

cd "$APP_DIR"

if ! west topdir >/dev/null 2>&1; then
    mkdir -p "$WEST_WORKSPACE_DIR"
    cd "$WEST_WORKSPACE_DIR"
    west init -l "$APP_DIR"
fi

cd "$WEST_WORKSPACE_DIR"

west update
west zephyr-export
pip install -r "$WEST_WORKSPACE_DIR/zephyr/scripts/requirements.txt"
echo "alias ll='ls -lah'" >> "$HOME/.bashrc"
west completion bash > "$HOME/west-completion.bash"
echo 'source $HOME/west-completion.bash' >> "$HOME/.bashrc"
history -c