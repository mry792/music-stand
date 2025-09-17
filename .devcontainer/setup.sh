#! /usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail
# set -o xtrace


# conan config install https://github.com/mry792/conan-config.git


# pushd ~
# BROKKR_VER=0.2.5
# wget \
#     https://github.com/mry792/brokkr/archive/refs/tags/v${BROKKR_VER}.tar.gz \
#     --output-document - | \
#     tar -xzf -
# conan create brokkr-${BROKKR_VER} --version ${BROKKR_VER} --user egoss --channel stable && \
# conan cache clean -vdebug --source --build --download --temp "brokkr/${BROKKR_VER}@egoss/stable"
# popd


sh -c "$(curl -fsLS get.chezmoi.io)" -- init --apply mry792
