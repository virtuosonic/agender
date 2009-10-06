#this file is part of the Agender project 
#it is free software and is licensed under the gpl
#
OBJS= obj/AgenderApp.o obj/AgenderMain.o obj/AgenderTray.o
CPPFLAGS=`wx-config --cflags`
LDFLAGS=`wx-config --libs`
CXX=cc
#
PREFIX=/usr

all:
	if (test ! -d obj ) ; then mkdir obj;fi
	$(CXX) $(CPPFLAGS) -c AgenderApp.cpp -o obj/AgenderApp.o
	$(CXX) $(CPPFLAGS) -c AgenderMain.cpp -o obj/AgenderMain.o
	$(CXX) $(CPPFLAGS) -c AgenderTray.cpp -o obj/AgenderTray.o
	$(CXX) -o bin/Agender $(OBJS) $(LDFLAGS)
clean:
	rm -f bin/Agender
	rm -f -r obj
install:
	if (test ! -d $(PREFIX)/bin) ; then mkdir $(PREFIX)/bin ; fi
	cp bin/Agender $(PREFIX)/bin
uninstall:
	rm $(PREFIX)/bin/Agender
