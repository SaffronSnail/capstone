pkg_name=capstone
pkg_description="A Modular Server"
pkg_origin=saffronsnail
pkg_version=0.1
pkg_maintainer="saffronsnail@hushmail.com"
pkg_license=('lgpl-3.0')
pkg_source=n/a
pkg_deps=()
pkg_build_deps=(core/git)
pkg_bin_dirs=()
pkg_include_dirs=()
pkg_lib_dirs=()

do_download() {
  git clone https://github.com/saffronsnail/capstone $HAB_CACHE_SRC_PATH/$pkg_dirname
}

do_verify  () {
  return 0
}

do_unpack  () {
  return 0
}

do_clean() {
  return 0
}

