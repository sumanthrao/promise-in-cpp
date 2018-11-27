CC = g++

IDIR=include
ODIR=obj
SRCDIR=src
EXEDIR=executable

$(EXEDIR)/run: $(ODIR)/client.o $(ODIR)/proxy.o $(ODIR)/scheduler.o $(ODIR)/task.o
	$(CC) -std=c++11 -pthread -g -o $(EXEDIR)/run -g $(ODIR)/client.o $(ODIR)/proxy.o $(ODIR)/scheduler.o $(ODIR)/task.o

$(ODIR)/client.o: $(SRCDIR)/client.cpp $(IDIR)/proxy.h
	$(CC) -std=c++11 -pthread -g -w -o $(ODIR)/client.o -c $(SRCDIR)/client.cpp

$(ODIR)/proxy.o: $(SRCDIR)/proxy.cpp $(IDIR)/proxy.h
	$(CC) -std=c++11 -pthread -g -w -o $(ODIR)/proxy.o -c $(SRCDIR)/proxy.cpp

$(ODIR)/scheduler.o: $(SRCDIR)/scheduler.cpp $(IDIR)/scheduler.h $(IDIR)/thread_pool.h
	$(CC) -std=c++11 -pthread -w -g -o $(ODIR)/scheduler.o -c $(SRCDIR)/scheduler.cpp

$(ODIR)/task.o: $(SRCDIR)/task.cpp $(IDIR)/task.h
	$(CC) -std=c++11 -pthread -w -g -o  $(ODIR)/task.o -c $(SRCDIR)/task.cpp

clean:
	rm -f $(ODIR)/*.o
	rm $(EXEDIR)/run

run:
	./$(EXEDIR)/run

	
