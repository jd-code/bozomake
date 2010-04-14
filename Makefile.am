## 
## $Id$
## Bozomake Copyright (C) 2002 Cristelle Barillon, Jean-Daniel PAUGET
## A small set graphical utilities for SDL
## 
## bozomake@disjunkt.com  -  http://bozomake.disjunkt.com/
## 
## This file is part of Bozomake.
## 
## Bozomake is free software; you can redistribute it and/or modify
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
## bozomake@disjunkt.com  -  http://bozomake.disjunkt.com/

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


install-deb: install-strip
	echo ${prefix}
	test -d ${prefix}/../DEBIAN || mkdir ${prefix}/../DEBIAN
	cp DEBIAN/control ${prefix}/../DEBIAN
	find ${mandir} -type f -regex '.*\.[0-9]' -exec gzip -f -9 '{}' \;
	mkdir -p ${prefix}/share/doc/${PACKAGE}
	gzip -f -9 -c ChangeLog > ${prefix}/share/doc/${PACKAGE}/changelog.gz
	gzip -f -9 -c DEBIAN/changelog.Debian > ${prefix}/share/doc/${PACKAGE}/changelog.Debian.gz
	cp DEBIAN/copyright ${prefix}/share/doc/${PACKAGE}
	(export DEBNAME=`echo ${prefix} | rev | cut -d/ -f2 | rev` ; cd ${prefix}/../.. ; ls -ld $$DEBNAME ; fakeroot dpkg-deb --build $$DEBNAME ; lintian $$DEBNAME.deb)

man-html: 
	test -d html || mkdir html
	for NOM in man/*.? ; do groff -man -Thtml $$NOM > html/`echo $$NOM | rev | cut -d/ -f1 | rev`.html ; done
	(cd html && echo '<div><ul>' > index.html ; ls *.?.html | while read NOM ; do echo '<li><a href="./'$$NOM'">'`echo $$NOM | rev | cut -d. -f2- | rev`'</a></li>' >> index.html ; done ; echo '</ul></div>' >> index.html)

##  additional file(s) to be removed when making dist...
## DISTCLEANFILES = ./src/Caroube.exe ./src/stderr.txt ./src/stdout.txt


