CPP=g++ 
DEF=
BINDIR=../../bin
SRCDIR=../cpp

all:

testtile: testTile.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(SRCDIR)/Tile.cpp $(SRCDIR)/Position.cpp -I$(SRCDIR)
	$(BINDIR)/$@

testmovable: testmovable.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(SRCDIR)/Position.cpp -I$(SRCDIR)
	$(BINDIR)/$@

testmap: testmap.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(SRCDIR)/Map.cpp $(SRCDIR)/Tile.cpp $(SRCDIR)/Position.cpp -I$(SRCDIR)
	$(BINDIR)/$@

testrule: testrule.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(SRCDIR)/Map.cpp $(SRCDIR)/Session.cpp $(SRCDIR)/Tile.cpp $(SRCDIR)/Position.cpp -I$(SRCDIR)
	$(BINDIR)/$@

testsession: testsession.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(SRCDIR)/Map.cpp $(SRCDIR)/Session.cpp $(SRCDIR)/Tile.cpp $(SRCDIR)/Position.cpp -I$(SRCDIR)
	$(BINDIR)/$@

testfileutil: testfileutil.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(SRCDIR)/MapRepository.cpp -I$(SRCDIR)
	(cd $(BINDIR);./$@)

testpeek: testpeek.cpp
	$(CPP) -o $(BINDIR)/$@ $<
	(cd $(BINDIR);./$@)
