dnl 
dnl $Id$
dnl Bozomake Copyright (C) 2002 Cristelle Barillon, Jean-Daniel PAUGET
dnl A whole set of building utilities
dnl 
dnl bozomake@disjunkt.com  -  http://bozomake.disjunkt.com/
dnl 
dnl 
dnl 
dnl 
dnl 
dnl This file is part of Bozomake.
dnl 
dnl Matcalc is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl 
dnl Matcalc is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with Matcalc; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
dnl you can also try the web at http://www.gnu.org/
dnl 
dnl 
dnl bozomake@disjunkt.com  -  http://bozomake.disjunkt.com/

dnl Process this file with autoconf to produce a configure script.

dnl mettre pareil dans DEBIAN/control.in
AC_INIT([bozomake], [1.12.13], [bozomake@disjunkt.com])
AC_CONFIG_SRCDIR([scripts/cvsstat.in])
dnl debian package subrevision
DEBSUBREVISION=002

dnl Detect the canonical host and target build environment
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

dnl autoheader
dnl JDJDJDJD though useless in this package,
dnl this is here for autoheader 2.56 on msys
AC_CONFIG_HEADER(src/config.h)

dnl Setup for automake
AM_INIT_AUTOMAKE([foreign])

dnl the magic of additionnal local m4 ?
AC_CONFIG_MACRO_DIR([m4])

# set the libtool so version numbers
lt_major=1
lt_revision=0
lt_age=0

AC_SUBST(lt_major)
AC_SUBST(lt_revision)
AC_SUBST(lt_age)


dnl Detect the canonical host and target build environment ---- was here

dnl Check for tools

AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL


dnl Check for compiler environment

AC_C_CONST

dnl JD's standard minimum CFLAG
dnl	CFLAGS="$CFLAGS -O2 -Wall"
dnl	CXXFLAGS="$CFLAGS -O2 -Wall"
dnl CHANGED for JD's ENterGroup default nasty warnings
CFLAGS="$CFLAGS -O2 -Wall -Wcast-qual -Wwrite-strings"
dnl CXXFLAGS="$CXXFLAGS -O2 -Wall -Woverloaded-virtual -Wcast-qual -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wredundant-decls -Winline"
CXXFLAGS="$CXXFLAGS -O2 -Wall -Woverloaded-virtual -Wcast-qual -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes -Wredundant-decls"

dnl are we compiling for windows -----------------------------------------------------------

dnl first we set the default value
case "$target" in
    *-*-mingw32*)
	defbuildforwin32=yes
	;;
    *)
	defbuildforwin32=no
	;;
esac

dnl then we act as eventually required by the configure...
AC_MSG_CHECKING([whether we build for windows])
AC_ARG_ENABLE(build-for-win32,
[  --enable-build-for-win32
                          enables building for a win32 paths repartition],
     try_build_for_win32=$enableval, try_build_for_win32="$defbuildforwin32")
AC_MSG_RESULT($try_build_for_win32)

if test "$try_build_for_win32" = yes; then
    AC_DEFINE(BUILD_FOR_WIN32, 1, we build for a win32 install paths flavour)
fi

dnl check wether gfind can be used rather than find (we need gnu find)
AC_ARG_ENABLE(not-look-for-gfind,
[  --enable-not-look-for-gfind
                          dont try to check for gnu find],
    AC_GFIND='find', AC_GFIND='')

if test '!' "${AC_GFIND}"
then
    AC_MSG_CHECKING([wether gfind is gnu find])
    if gfind --version | grep -i 'GNU.*findutil' > /dev/null
    then
	AC_GFIND='gfind'
    else
	AC_GFIND='find'
    fi
    AC_MSG_RESULT($AC_GFIND)
fi

AC_SUBST(AC_GFIND)

dnl look for an exuberant ctags
AC_ARG_ENABLE(not-look-for-ctags,
[  --enable-not-look-for-ctags
                          dont try to check for exhuberant ctags],
    AC_OURCTAGS='ctags', AC_OURCTAGS='')


if test '!' "${AC_OURCTAGS}"
then
    AC_MSG_CHECKING([for some exuberant ctags])
    AC_OURCTAGS=""
    echo "${PATH}" | tr ':' '\n' | while read DIR
    do
	if test -x "${DIR}/ctags"
	then
	    if "${DIR}/ctags" --version | grep -i 'Exuberant.*Ctags' > /dev/null
	    then
		AC_OURCTAGS="${DIR}/ctags"
		echo "${AC_OURCTAGS}" > ourctags
		break;
	    fi
	fi
    done
    if test '-f' ourctags
    then
	AC_OURCTAGS=`cat ourctags`
	AC_MSG_RESULT($AC_OURCTAGS)
	rm ourctags
    else
	AC_OURCTAGS='ctags'
	AC_MSG_RESULT(not sure so will try to use $AC_OURCTAGS)
    fi
fi

AC_SUBST(AC_OURCTAGS)


dnl look for a libtoolize
AC_MSG_CHECKING([for some libtoolize])
if libtoolize --version | grep -i 'GNU.*libtool' > /dev/null
then
    AC_LIBTOOLIZE='libtoolize'
    AC_MSG_RESULT($AC_LIBTOOLIZE)
else
    if glibtoolize --version | grep -i 'GNU.*libtool' > /dev/null
    then
	AC_LIBTOOLIZE='glibtoolize'
	AC_MSG_RESULT($AC_LIBTOOLIZE)
    else
	AC_LIBTOOLIZE='libtoolize'
	AC_MSG_RESULT(not sure so will try to use $AC_LIBTOOLIZE)
    fi
fi
AC_SUBST(AC_LIBTOOLIZE)

dnl check for dpkg-architecture
AC_DEFUN([AC_PROG_DPKGARCHITECURE], [AC_CHECK_PROG(HASDPKGARCHITECURE,dpkg-architecture,yes)])
AC_PROG_DPKGARCHITECURE

if test x"${HASDPKGARCHITECURE}" == x"yes" ; then

dnl create deb-packages arch substitution
    AC_MSG_CHECKING([arch substitution for deb packages])
    AC_DEBARCHSUBST=`dpkg-architecture -qDEB_BUILD_ARCH`
dnl was:    AC_DEBARCHSUBST=`echo "$target" | cut -d- -f1`
dnl was:    case $AC_DEBARCHSUBST in
dnl was:        x86_64)
dnl was:    	AC_DEBARCHSUBST=amd64
dnl was:    	;;
dnl was:        i686)
dnl was:    	AC_DEBARCHSUBST=i386
dnl was:    	;;
dnl was:        *)
dnl was:    	:
dnl was:    	;;
dnl was:    esac
    if test "$AC_DEBARCHSUBST"
    then
	AC_MSG_RESULT($AC_DEBARCHSUBST)
    else
	AC_DEBARCHSUBST="UNKNOWN"
	AC_MSG_RESULT($AC_DEBARCHSUBST)
    fi
else
    AC_DEBARCHSUBST="UNKNOWN"
fi

AC_SUBST(AC_DEBARCHSUBST)

# version substitution for debian packaging
AC_DEBVERSION=$VERSION-$DEBSUBREVISION
AC_SUBST(AC_DEBVERSION)


# Finally create all the generated files
AC_OUTPUT([
	Makefile
	src/Makefile
	scripts/Makefile
	DEBIAN/control
	scripts/autoall
	scripts/repozclean
	scripts/bozoconf
	scripts/cptobackup
	scripts/cvsstat
	scripts/maketags
	scripts/mvtobackup
	scripts/vimall
	scripts/settitle
	man/Makefile
	man/autoall.1
	man/bozoconf.1
	man/brev.1
	man/count.1
	man/countsort.1
	man/cptobackup.1
	man/cvsstat.1
	man/maketags.1
	man/mvtobackup.1
	man/percent.1
	man/repozclean.1
	man/scramble.1
	man/vimall.1
	man/revtail.1
	man/settitle.1
])
