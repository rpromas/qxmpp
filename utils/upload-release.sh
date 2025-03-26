#!/usr/bin/env bash
# SPDX-FileCopyrightText: 2025 Melvin Keskin <melvo@olomono.de>
# SPDX-FileCopyrightText: 2025 Linus Jahn <lnj@kaidan.im>
#
# SPDX-License-Identifier: LGPL-2.1-or-later

set -e

version="$1"
project_name=qxmpp
release_tag_name="v${version}"
project_repo_url=https://invent.kde.org/libraries/qxmpp.git
work_dir=tmp-release-$version
checkout_dir="${project_name}-${version}"
compressed_archive=$project_name-$version.tar.xz
release_files_upload_url="ftp://upload.kde.org/incoming/"
sysadmin_ticket_url="https://go.kde.org/systickets"
target=unstable

if [ -z "$1" ]; then
    echo "Requires [version] as parameter."
    exit
fi

mkdir -p $work_dir
cd $work_dir

# Download, compress and sign the release files.
git clone --depth=1 -b "${release_tag_name}" "${project_repo_url}" "${checkout_dir}"
rm -rf "${checkout_dir}/.git"
tar -I "xz -9" -cf "${compressed_archive}" "${checkout_dir}"
gpg -o "${compressed_archive}.sig" -abs "${compressed_archive}"

# Upload the release files.
release_files="${compressed_archive} ${compressed_archive}.sig"
release_files_string=$(echo ${release_files} | tr "[:blank:]" ",")
curl -T "{${release_files_string}}" "${release_files_upload_url}"

printf "%s\n" \
    "Steps required to publish release files:" \
    "Create admin ticket: ${sysadmin_ticket_url}" \
    "Title: Publish $compressed_archive" \
    "Description:" \
    "Target: ${target}/${project_name}" \

printf '\nSHA-1:\n```\n'
sha1sum ${release_files}
printf '```\n\nSHA-256:\n```\n'
sha256sum ${release_files}
printf '```\n'

cd -
mv $work_dir/$compressed_archive $work_dir/$compressed_archive.sig ./

# clean up
rm -rf ${work_dir}

