# @(#)Makefile	4.2 7/13/89 14:50:41
# prsbox - print S Boxes
#
# Landon Curt Noll makes no representations concerning either the
# merchantability of this software or the suitability of this software for
# any particular purpose.  It is provided "as is" without express or 
# implied warranty of any kind.
#
# This file has been put in the public domain.  Please leave it that way.
#
# By: Landon Curt Noll   (chongo@toad.com  -or  uunet!hoptoad!chongo)

SHELL=/bin/sh
CC=cc
LINT=lint
OPT=-O
LDFLAGS=
LINTFLAGS=
CFLAGS=

all: prsbox sbox.c endian.h

prsbox: prsbox.o
	${CC} ${OPT} ${CFLAGS} ${LDFLAGS} prsbox.o -o prsbox

prsbox.o: prsbox.c prsbox.h
	${CC} ${OPT} ${CFLAGS} prsbox.c -c

endian.h: prsbox
	-rm -f endian.h
	prsbox -h > endian.h

sbox.c: prsbox
	-rm -f sbox.c
	prsbox > sbox.c

sbox.o: sbox.c prsbox.h
	${CC} ${CFLAGS} sbox.c -c

lint: prsbox.c prsbox.h endian.h
	${LINT} ${LINTFLAGS} sbox.c
	${LINT} ${LINTFLAGS} prsbox.c

clean:
	-rm -f prsbox.o sbox.o core

clobber: clean
	-rm -f prsbox sbox.c endian.h
