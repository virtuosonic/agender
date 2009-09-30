OBJS= obj/AgenderApp.o obj/AgenderMain.o obj/AgenderTray.o
CPPFLAGS=`wx-config --cflags`
LDFLAGS=`wx-config --libs`

all:
	mkdir obj
	cc $(CPPFLAGS) -c AgenderApp.cpp -o obj/AgenderApp.o
	cc $(CPPFLAGS) -c AgenderMain.cpp -o obj/AgenderMain.o
	cc $(CPPFLAGS) -c AgenderTray.cpp -o obj/AgenderTray.o
	cc -o Agender $(OBJS) $(LDFLAGS)
clean:
	rm -f Agender
	rm -f -r obj
install:
	mv Agender /usr/bin
uninstall:
	rm /usr/bin/Agender
dist:
	tar -cfj
