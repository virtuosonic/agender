


IDIR=-I./
CFLAGS=`wx-config --cflags`
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
LDFLAGS=`wx-config --libs`

all: agender-mac


%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(IDIR) $(CFLAGS)

agender-mac: $(OBJ)
	g++ -o $@ $^  $(LDFLAGS)

clean:
	rm $(OBJ) agender-mac
