CPP=g++
CPPFLAGS=
SRCDIR=./src/cpp
BINDIR=./bin

.SUFFIXES: .cpp .o .h

MODULE = Tile Map \
	Position MapRepository \
	main Game Session

VIEW = $(SRCDIR)/Viewer.cpp

VIEWOBJ = $(BINDIR)/Viewer.o

OBJ = $(addprefix $(BINDIR)/, $(addsuffix .o, $(MODULE)))

all: ${BINDIR}/game.out

$(MODULE): % : $(SRCDIR)/%.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

Viewer: $(VIEW)
	$(CPP) -c -o $(VIEWOBJ) $<

run: $(BINDIR)/game.out
	(cd $(BINDIR);./game.out)

$(BINDIR)/game.out: $(MODULE) Viewer
	$(CPP) -o  $@ $(OBJ) $(VIEWOBJ)

.PHONY:clean

clean:
	rm -f $(BINDIR)/*
