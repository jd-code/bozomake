## 
## $Id$
## Matcalc Copyright (C) 2002 Cristelle Barillon, Jean-Daniel PAUGET
## A small set graphical utilities for SDL
## 
## matcalc@disjunkt.com  -  http://matcalc.disjunkt.com/
## 
## This file is part of Matcalc.
## 
## Matcalc is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
## 
## Caroube is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with Caroube; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
## you can also try the web at http://www.gnu.org/
## 
## matcalc@disjunkt.com  -  http://matcalc.disjunkt.com/

## probably redundant with somewhere else
## CFLAGS = -O2 -Wall

SUBDIRS = scripts src man

vimtest: all
	echo 9 8 7 6 5 4 3 2 1 | ./src/brev
	cat ./src/revtail.c | ./src/revtail > /tmp/1
	./src/revtail ./src/revtail.c > /tmp/2
	diff /tmp/1 /tmp/2
	## ./src/Caroube
	## startx -display :1 -e ./src/Caroube -- :1 -depth 16 -ac

vimtestw32: all
	## rm -f ./src/Caroube.exe
	## mv ./src/Caroube ./src/Caroube.exe


##  additional file(s) to be removed when making dist...
## DISTCLEANFILES = ./src/Caroube.exe ./src/stderr.txt ./src/stdout.txt


