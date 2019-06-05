#!/usr/bin/env bash

dest=codes
unzip "$1" -d "${dest}"
pushd ${dest}
mapfile -t names <<<$(
    for f in *; do
        echo ${f/_assignsubmission_file_AT-*/}
    done | sort |uniq
)
for name in "${names[@]}"; do
    echo "moving: $name*"
    mapfile -t files <<<$(ls "${name}"*)
    mkdir -p $(echo "$name" | sed -e "s/.*_\([0-9]*\)/\1/g")
    for f in "${files[@]}"; do
        mv "$f" "$(echo "$f" | sed -e "s/.*_\([0-9]*\)_assignsubmission_file_AT-[0-9]*-\(.*\)/\1\/\2/g")"
    done
done
popd
