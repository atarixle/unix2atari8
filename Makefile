unix2atari8: unix2atari8.c str_replace.c
	cc unix2atari8.c -o unix2atari8

clean:
	rm -f unix2atari8 unix2atari8.o

install: unix2atari8
	cp unix2atari8 /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/unix2atari8

