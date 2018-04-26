INSTALL=install -D
INSTALL_DEPS=dreconf
PREFIX?=/usr/local

DEST_PROGRAM=$(PREFIX)/sbin/dreconf
# DEST_MANUAL=$(PREFIX)/man/man8

install: $(INSTALL_DEPS)
	$(INSTALL) -m 0755 dreconf $(DEST_PROGRAM)
#	$(INSTALL) -m 0444 dreconf.8 $(DEST_MANUAL)
