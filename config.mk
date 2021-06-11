# xwrtnm

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# installation path prefix
PREFIX = /usr/local

# includes and libs
INCS = -I${X11INC}
LIBS = -L${X11LIB} -lX11

# flags
CPPFLAGS = -D_POSIX_C_SOURCE=200809L
CFLAGS   = -std=c99 -pedantic -Wall -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc
