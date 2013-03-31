Conway's Game of Life
=====================

C++ implementation using SDL and Boost libraries

How to install it
=================

```
cd src
make
sudo make install
```

Or if you're on Arch Linux, download the `PKGBUILD` and:
```
makepkg -si
```

Please check the `/usr/share/conway/` directory for example configuration files.

How to run it
=============

```
conway --help
conway
conway glider.txt
conway /usr/share/conway/gosper_glider_gun.txt -r 50 -c 50
```

How to uninstall it
===================

If you used the first method described above:
```
cd src
sudo make uninstall
```

If you used the second method described above:
```
# pacman -Rs conway-git
```

License
=======

(C) Copyright 2013 Barbu Paul - Gheorghe

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
