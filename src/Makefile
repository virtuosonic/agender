#!/usr/bin/make
#Desc:	Makefile para compilar Agender en Mac OS
#Fecha:	21-Jun-2017
#Autor Gabriel Espinoza


IDIR=-I./
CFLAGS=`wx-config --cflags`
LDFLAGS=`wx-config --libs`
SRC=AboutDialog.cpp \
AgenderApp.cpp \
AgenderCal.cpp \
AgenderDnd.cpp \
AgenderIPC.cpp \
AgenderMain.cpp \
AgenderTray.cpp \
Notifier.cpp \
Updater.cpp \
wxAutoStart.cpp
OBJ=$(SRC:.cpp=.o)
DEPS=$(SRC:.cpp=.h)

all: agender-mac

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(IDIR) $(CFLAGS)

agender-mac: $(OBJ)
	g++ -o $@ $^  $(LDFLAGS)

clean:
	rm $(OBJ) agender-mac
	rm -rf Agender.app

pack: Agender.app

Agender.app:
	mkdir Agender.app
	mkdir Agender.app/Contents
	mkdir Agender.app/Contents/MacOS
	mkdir Agender.app/Contents/Resources
	cp ../share/Info.plist Agender.app/Contents
	cp agender-mac Agender.app/Contents/MacOS
	cp ../share/{*.png,*.jpg,*.icns} Agender.app/Contents/Resources
	cp *.ico *.xpm Agender.app/Contents/Resources
	cp ../po/*.mo Agender.app/Contents/Resources
