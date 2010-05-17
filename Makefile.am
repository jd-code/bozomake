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

debian:
	## bozoconf --prefix="$${HOME}/${PACKAGE}-${VERSION}_"`echo "${target_cpu}" | sed 's/x86_64/amd64/' `"/usr" ; make install-deb
	bozoconf --prefix="$${HOME}/${PACKAGE}-${VERSION}_"@AC_DEBARCHSUBST@"/usr" ; make install-deb

install-deb: install-strip
	echo ${prefix}
	test -d ${prefix}/../DEBIAN || mkdir ${prefix}/../DEBIAN
	cp -a DEBIAN/control DEBIAN/config DEBIAN/templates DEBIAN/postinst DEBIAN/postrm ${prefix}/../DEBIAN
	find ${mandir} -type f -regex '.*\.[0-9]' -exec gzip -f -9 '{}' \;
	mkdir -p ${prefix}/share/doc/${PACKAGE}
	gzip -f -9 -c ChangeLog > ${prefix}/share/doc/${PACKAGE}/changelog.gz
	gzip -f -9 -c DEBIAN/changelog.Debian > ${prefix}/share/doc/${PACKAGE}/changelog.Debian.gz
	cp DEBIAN/copyright ${prefix}/share/doc/${PACKAGE}
	(export DEBNAME=`echo ${prefix} | rev | cut -d/ -f2 | rev` ; cd ${prefix}/../.. ; ls -ld $$DEBNAME ; fakeroot dpkg-deb --build $$DEBNAME ; lintian $$DEBNAME.deb)

man-html: man
	test -d html || mkdir html
	for NOM in man/*.? ; do groff -man -Thtml $$NOM	|						\
	sed 's_bozomake_<a href="bozomake.1.html">bozomake</a>_g' |					\
	sed 's_bozoconf_<a href="bozoconf.1.html">bozoconf</a>_g' |					\
	sed 's_brev_<a href="brev.1.html">brev</a>_g' |					\
	sed 's_count_<a href="count.1.html">count</a>_g' |					\
	sed 's_countsort_<a href="countsort.1.html">countsort</a>_g' |					\
	sed 's_cptobackup_<a href="cptobackup.1.html">cptobackup</a>_g' |					\
	sed 's_cvsstat_<a href="cvsstat.1.html">cvsstat</a>_g' |					\
	sed 's_maketags_<a href="maketags.1.html">maketags</a>_g' |					\
	sed 's_mvtobackup_<a href="mvtobackup.1.html">mvtobackup</a>_g' |					\
	sed 's_percent_<a href="percent.1.html">percent</a>_g' |					\
	sed 's_repozclean_<a href="repozclean.1.html">repozclean</a>_g' |					\
	sed 's_revtail_<a href="revtail.1.html">revtail</a>_g' |					\
	sed 's_scramble_<a href="scramble.1.html">scramble</a>_g' |					\
	sed 's_vimall_<a href="vimall.1.html">vimall</a>_g' |					\
	cat > html/`echo $$NOM | rev | cut -d/ -f1 | rev`.html ; done
	(cd man &&											\
	echo '<div><ul>' ;										\
	for NOM in *.? ; do										\
	    echo -n '<li><a href="./'$$NOM'.html">'`echo $$NOM | rev | cut -d. -f2- | rev`'</a>' ;	\
	    grep -A1 '^.SH NAME' $$NOM | tail -1 | sed 's/^[[:alnum:]]*[[:space:]]*//' |		\
		sed 's/\\-/\&nbsp;- /' ;								\
	    echo "</LI>" ;										\
	done ;												\
	echo '</ul></div>' ; ) > html/index.html


##	(cd html && echo '<div><ul>' > index.html ; ls *.?.html | while read NOM ; do echo '<li><a href="./'$$NOM'">'`echo $$NOM | rev | cut -d. -f2- | rev`'</a></li>' >> index.html ; done ; echo '</ul></div>' >> index.html)

##  additional file(s) to be removed when making dist...
## DISTCLEANFILES = ./src/Caroube.exe ./src/stderr.txt ./src/stdout.txt


