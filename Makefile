include config.mk

SRC    = gof.c
OBJ    = ${SRC:.c=.o}

all: options gof

options:
	@echo gof build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

gof: ${OBJ}
	@echo LD $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f gof ${OBJ} ${LIBOBJ} gof-${VERSION}.tar.gz
	@rm -f *.pbm

dist: clean
	@echo creating dist tarball
	@mkdir -p gof-${VERSION}
	@cp -R LICENSE Makefile config.mk ${SRC} gof-${VERSION}
	@tar -cf gof-${VERSION}.tar gof-${VERSION}
	@gzip gof-${VERSION}.tar
	@rm -rf gof-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f gof ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/gof

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/gof

.PHONY: all options clean dist install uninstall
