#!/usr/bin/env bash
# Auto-update .clangd configuration with newly built modules

MODULE_NAME="$1"
WORKSPACE_ROOT="/workspace"
CLANGD_CONFIG="${WORKSPACE_ROOT}/.clangd"
echo "🔧 Auto-updating .clangd for module: ${MODULE_NAME}"
MODULE_FLAG="    - \"-fmodule-file=${MODULE_NAME}=/workspace/build/modules/${MODULE_NAME}.pcm\""
# Create .clangd if it doesn't exist
if [[ ! -f "${CLANGD_CONFIG}" ]]; then
    cat > "${CLANGD_CONFIG}" <<EOF
CompileFlags:
  Add:
    - "-fprebuilt-module-path=/workspace/build/modules"
    - "-fmodule-file=std=/workspace/build/modules/std.pcm"
${MODULE_FLAG}
EOF
    echo "✅ Created .clangd config with ${MODULE_NAME} module"
    exit 0
fi
# Check if module is already in config
if grep -q "\-fmodule-file=${MODULE_NAME}=" "${CLANGD_CONFIG}"; then
    echo "✅ Module ${MODULE_NAME} already in .clangd config"
else
    # Add new module after std module line
    sed -i "/fmodule-file=std=/a\\${MODULE_FLAG}" "${CLANGD_CONFIG}"
    echo "✅ Added ${MODULE_NAME} to .clangd config"
fi