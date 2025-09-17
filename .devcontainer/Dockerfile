
FROM mcr.microsoft.com/devcontainers/base:ubuntu

RUN apt update && \
    apt install --yes --no-install-recommends \
        # common apt packages
        cmake \
        curl \
        gdb \
        grep \
        less \
        lsb-release \
        pipx \
        sudo \
        tree \
        vim \
        #
        # (big) dependencies
        qt6-base-dev \
      && \
    rm --recursive --force /var/lib/apt/lists/*


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
    cd && \
    wget \
        https://github.com/mry792/brokkr/archive/refs/tags/v${BROKKR_VER}.tar.gz \
        --output-document - | \
        tar -xzf - && \
    conan create brokkr-${BROKKR_VER} --version ${BROKKR_VER} --user egoss --channel stable && \
    conan cache clean -vdebug --source --build --download --temp "brokkr/${BROKKR_VER}@egoss/stable"


#######
# Setup shell.
###

# ARG GITHUB_USERNAME=mry792
# RUN sh -c "$(curl -fsLS get.chezmoi.io)" -- init --apply ${GITHUB_USERNAME}


# ENTRYPOINT [ "/bin/bash" ]
