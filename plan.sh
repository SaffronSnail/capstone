pkg_name=capstone
pkg_description="A Modular Server"
pkg_origin=saffronsnail
pkg_version=0.1
pkg_maintainer="saffronsnail@hushmail.com"
pkg_license=('lgpl-3.0')
pkg_source=n/a
pkg_deps=()
pkg_build_deps=(core/gcc core/git core/make)
pkg_bin_dirs=(bin)
pkg_include_dirs=()
pkg_lib_dirs=()
pkg_svc_run="bin/butler.guile"

do_download() {
  SOURCE_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
  git clone $SOURCE_DIR $pkg_name
}

do_verify() {
  return 0
}

do_unpack() {
  mv $pkg_name $HAB_CACHE_SRC_PATH/$pkg_dirname
}

do_build() {
  sed -i -e "s|PACKAGE_PREFIX=|PACKAGE_PREFIX=${pkg_prefix}|" makefile
  sed -i -e "s|SERVICE_PREFIX=|SERVICE_PREFIX=${pkg_svc_path}|" makefile
  make
}

