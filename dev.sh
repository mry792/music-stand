#! /usr/bin/env bash

set -o errexit
set -o nounset

cmd=${1}
shift

CONTAINER_LABEL="egoss.name=music-stand"
REPO_ROOT=$(dirname $(realpath ${BASH_SOURCE[0]}))

COMMON_ARGS="--workspace-folder ${REPO_ROOT} --id-label ${CONTAINER_LABEL}"

case ${cmd} in
    up)
        devcontainer up ${COMMON_ARGS} --config .devcontainer/devcontainer.json
        ;;

    down)
        CONTAINER_NAME=$(docker ps --filter "label=${CONTAINER_LABEL}" --format "{{.Names}}")
        docker rm --force ${CONTAINER_NAME}
        ;;

    *)
        devcontainer exec ${COMMON_ARGS} ${cmd} "$@"
        ;;
esac
