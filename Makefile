# dharma - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dharma.c util.c events.c
OBJ = ${SRC:.c=.o}
MAKEFILE_DIR := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

all: options dharma

options:
	@echo dharma build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dharma: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dharma ${OBJ} dharma-${VERSION}.tar.gz

dist: clean
	mkdir -p dharma-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dharma.1 drw.h util.h ${SRC} dharma.png transient.c dharma-${VERSION}
	tar -cf dharma-${VERSION}.tar dharma-${VERSION}
	gzip dharma-${VERSION}.tar
	rm -rf dharma-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	ln -sf ${MAKEFILE_DIR}/dharma ${DESTDIR}${PREFIX}/bin/dharma
	cp -f dharmactl ${DESTDIR}${PREFIX}/bin
	cp -f dharma.desktop /usr/share/xsessions/dharma.desktop
	chmod 755 ${DESTDIR}${PREFIX}/bin/dharma
	chmod +x ${DESTDIR}${PREFIX}/bin/dharmactl
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dharma.1 > ${DESTDIR}${MANPREFIX}/man1/dharma.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dharma.1

init:
	mkdir -p ~/.config/dharma
	ln -sf ${MAKEFILE_DIR}/config.h ~/.config/dharma/config.h
	ln -sf ${MAKEFILE_DIR}/autostart ~/.config/dharma/autostart
	ln -sf ${MAKEFILE_DIR}/autostart_always ~/.config/dharma/autostart_always

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dharma\
		${DESTDIR}${MANPREFIX}/man1/dharma.1

.PHONY: all options clean dist install uninstall
