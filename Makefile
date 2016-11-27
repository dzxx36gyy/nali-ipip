include config.mak
all:nali.c lib17mon/ipip.c
	gcc -o bin/ipipnali nali.c lib17mon/ipip.c
	cp share/nali.sh bin/nali
install:bin share
	install bin/ipipnali $(DESTDIR)$(bindir) 
	install bin/nali $(DESTDIR)$(bindir) 
	install bin/nali-traceroute $(DESTDIR)$(bindir) 
	install bin/nali-tracepath $(DESTDIR)$(bindir) 
	install bin/nali-dig $(DESTDIR)$(bindir) 
	install bin/nali-nslookup $(DESTDIR)$(bindir) 
	install bin/nali-ping $(DESTDIR)$(bindir) 
	install share/17monipdb.dat $(DESTDIR)$(datadir) 
	install share/nali.pl $(DESTDIR)$(datadir) 
distclean: clean
	rm -f config.mak
	rm -f config.h
clean:
	rm -f bin/ipipnali
	rm -f bin/nali
