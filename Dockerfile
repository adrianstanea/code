# syntax=docker/dockerfile:1
FROM debian:sid-slim

ARG DEBIAN_FRONTEND=noninteractive

# Install Clang tool-chain with clangd, LLDB debugger CMake and development tools

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    clang-19 \
    clangd-19 \
    lldb-19 \
    libc++-19-dev \
    clang-tools-19 \
    cmake \
    ninja-build \
    make \
    pkg-config \
    valgrind \
    lcov \
    git \
    openssh-client \
    ssh-askpass \
    bash \
    bash-completion \
    less \
    nano  \
    sudo \
    locales && \
    \
    # 🌐 Configure locale to prevent warnings
    echo "C.UTF-8 UTF-8" > /etc/locale.gen && \
    locale-gen C.UTF-8 && \
    echo "LANG=C.UTF-8" > /etc/default/locale && \
    \
    # Register version-agnostic binaries via update-alternatives for learning
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 100 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-19 100 && \
    update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-19 100 && \
    update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-19 100 && \
    update-alternatives --install /usr/bin/clang-scan-deps clang-scan-deps /usr/bin/clang-scan-deps-19 100 && \
    \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# 👤 VS Code user with password-less sudo and Bash as default shell
RUN useradd -m -u 1000 vscode && \
    echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers && \
    chsh -s /bin/bash vscode && \
    \
    # 🌐 Set up locale environment for vscode user
    echo "# Fix locale warnings" > /home/vscode/.bashrc && \
    echo "export LANG=C.UTF-8" >> /home/vscode/.bashrc && \
    echo "export LC_ALL=C.UTF-8" >> /home/vscode/.bashrc && \
    echo "" >> /home/vscode/.bashrc && \
    chown vscode:vscode /home/vscode/.bashrc

USER vscode
WORKDIR /workspace

USER vscode
WORKDIR /workspace

# 🎯  Environment variables for C++23 learning with Clang-19
ENV CC=clang
ENV CXX=clang++
ENV CLANGD_PATH=/usr/bin/clangd-19

# 🌐  Locale environment variables to prevent warnings
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# 📁  Create module cache directory for C++23 std module
RUN mkdir -p /workspace/build
ENV CXX=clang++