# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs
INCS = -I. -I/usr/include
LIBS = -L/usr/lib

# flags
CFLAGS = -g -O3 -Wall -Wextra -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L ${INCS}
#CFLAGS = -Os -Wall -Wextra -Werror -std=c99 -pedantic -D_POSIX_C_SOURCE=200809L ${INCS}
LDFLAGS = -static ${LIBS}

# compiler
CC=clang
