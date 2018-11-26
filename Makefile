CC = g++

IDIR=include
ODIR=obj
SRCDIR=src
EXEDIR=executable

$(EXEDIR)/run: $(ODIR)/promise.o $(ODIR)/client.o 
	$(CC) -std=c++11 -o $(EXEDIR)/run -g $(ODIR)/promise.o $(ODIR)/client.o 

$(ODIR)/promise.o: $(SRCDIR)/promise.cpp $(IDIR)/promise.h
	$(CC) -std=c++11 -w -o $(ODIR)/promise.o -c $(SRCDIR)/promise.cpp

$(ODIR)/client.o: $(SRCDIR)/client.cpp $(IDIR)/promise.h
	$(CC) -std=c++11 -w -o $(ODIR)/client.o -c $(SRCDIR)/client.cpp
	
clean:
	rm -f $(ODIR)/*.o
	rm $(EXEDIR)/run

run:
	./$(EXEDIR)/run

	
