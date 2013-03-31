# Maintainer: Barbu Paul - Gheorghe <paullik[dot]paul[at]gmail.com>

pkgname=conway-git
pkgver=20130331
pkgrel=1
pkgdesc="C++ implementation of Conway's Game Of Life using SDL and Boost
libraries"
arch=('i686' 'x86_64')
url="https://github.com/paullik/ConwaysGameOfLife"
license=('GPL3')
depends=('sdl' 'boost-libs')
makedepends=('git' 'boost')

_gitroot="git://github.com/paullik/ConwaysGameOfLife.git"
_gitname="conwaysgameoflife"

build() {
  cd "$srcdir"
  msg "Connecting to GIT server...."

  if [[ -d "$_gitname" ]]; then
    cd "$_gitname" && git pull origin
    msg "The local files are updated."
  else
    git clone "$_gitroot" "$_gitname"
  fi

  msg "GIT checkout done or server timeout"
  msg "Starting build..."

  rm -rf "$srcdir/$_gitname-build"
  git clone "$srcdir/$_gitname" "$srcdir/$_gitname-build"
  cd "$srcdir/$_gitname-build/src"

  make

  mkdir -p "$pkgdir/usr/bin"
  mkdir -p "$pkgdir/usr/share"
}

package() {
  cd "$srcdir/$_gitname-build/src"
  make DESTDIR="$pkgdir" install
}

# vim:set ts=2 sw=2 et:
