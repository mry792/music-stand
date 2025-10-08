
###
# image - Qt installer (aqt)
###

# FROM python:3.13-bookworm AS qt-installer
FROM mcr.microsoft.com/devcontainers/base:ubuntu

# RUN \
#     PIPX_HOME=/usr/local/pipx \
#     PIPX_BIN_DIR=/usr/local/bin \
#     PIPX_MAN_DIR=/usr/local/share/man \
#     pipx install aqtinstall

# RUN \
#     aqt install-qt linux desktop 6.9.3 linux_gcc_64 \
#         --modules qtpdf --outputdir /opt/qt
#     # aqt install-tool linux


##############################################################################

###
# image - product
###


# FROM mcr.microsoft.com/devcontainers/base:ubuntu

RUN apt update && \
    apt install --yes --no-install-recommends \
        # common apt packages
        cmake \
        cmake-curses-gui \
        curl \
        gdb \
        grep \
        less \
        lsb-release \
        pipx \
        pkg-config \
        sudo \
        tree \
        vim \
        #
        # qt dependencies
        libdbus-1-3 \
        libfontconfig1 \
        libfreetype6 \
        libgl1-mesa-dev \
        libpthread-stubs0-dev \
        libxcb-cursor0 \
        libxcb-icccm4 \
        libxcb-keysyms1 \
        libxcb-shape0 \
        libxcb-xkb1 \
        libxkbcommon-x11-0 \
        libxkbcommon0 \
      && \
    rm --recursive --force /var/lib/apt/lists/*

# TODO: Maybe remove
# vvvvvv
RUN \
    PIPX_HOME=/usr/local/pipx \
    PIPX_BIN_DIR=/usr/local/bin \
    PIPX_MAN_DIR=/usr/local/share/man \
    pipx install aqtinstall

RUN \
    aqt install-qt linux desktop 6.9.3 linux_gcc_64 \
        --modules qtpdf --outputdir /opt/qt
    # aqt install-tool linux
# ^^^^^^


# #######
# # Setup user
# ###

# ARG USERNAME=egoss
# ARG USER_UID=1000
# ARG USER_GID=${USER_UID}

# RUN groupadd --gid ${USER_GID} $USERNAME && \
#     useradd --uid ${USER_UID} --gid ${USER_GID} -m ${USERNAME} && \
#     echo "${USERNAME} ALL=(root) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} && \
#     chmod 0440 /etc/sudoers.d/${USERNAME}

USER root


#######
# Setup Conan.
###

ARG CONAN_VER=2.19
# ARG CONAN_EXE=/home/${USERNAME}/.local/bin/conan

RUN \
    PIPX_HOME=/usr/local/pipx \
    PIPX_BIN_DIR=/usr/local/bin \
    PIPX_MAN_DIR=/usr/local/share/man \
    pipx install conan==${CONAN_VER}
# RUN pip install conan==${CONAN_VER}
# && \
    # pipx ensurepath
# RUN ${CONAN_EXE} config install https://github.com/mry792/conan-config.git


#######
# Setup dev dependencies.
###

USER vscode

ARG BROKKR_VER=0.2.5
RUN \
    conan config install https://github.com/mry792/conan-config.git && \
    echo "core.cache:storage_path = /workspaces/music-stand/.conan-cache" \
        >> $(conan config home)/global.conf
    # cd && \
    # wget \
    #     https://github.com/mry792/brokkr/archive/refs/tags/v${BROKKR_VER}.tar.gz \
    #     --output-document - | \
    #     tar -xzf - && \
    # conan create brokkr-${BROKKR_VER} --version ${BROKKR_VER} --user egoss --channel stable && \
    # conan cache clean -vdebug --source --build --download --temp "brokkr/${BROKKR_VER}@egoss/stable"


#######
# Setup shell.
###

# ARG GITHUB_USERNAME=mry792
# RUN sh -c "$(curl -fsLS get.chezmoi.io)" -- init --apply ${GITHUB_USERNAME}


# ENTRYPOINT [ "/bin/bash" ]
