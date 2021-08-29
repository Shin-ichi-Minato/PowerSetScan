CC	= g++

OPT 	= -O3 -Wall 
OPTN 	= -O3 -DNAIVE
OPTP 	= -O3 -DPMAP

OBJ	= PSS_Table.o PSS_Main.o
OBJN	= PSS_Table_nv.o PSS_Main.o
OBJP	= PSS_Table_pmap.o PSS_Main.o

PROGRAM = pss
PROGRAMN = pss-nv
PROGRAMP = pss-pmap

#DIR	= ../..
#INCLUDE = -I$(DIR)/include 
#LIBDIR	= $(DIR)/lib

all:	$(PROGRAM)    

$(PROGRAM): $(OBJ)
	$(CC) $(OPT) $(OBJ) -o $(PROGRAM)
#	$(CC) $(OPT) $(INCLUDE) \
#	$(OBJ) $(LIBDIR)/BDD64.a -o $(PROGRAM)
#	$(OBJ) $(LIBDIR)/BDD.a -o $(PROGRAM)

naive:	$(PROGRAMN)    

$(PROGRAMN): $(OBJN)
	$(CC) $(OPTN) $(OBJN) -o $(PROGRAMN)

pmap:	$(PROGRAMP)    

$(PROGRAMP): $(OBJP)
	$(CC) $(OPTP) $(OBJP) -o $(PROGRAMP)

PSS_Main.o: PSS_Main.cc
	$(CC) $(OPT) -c PSS_Main.cc

PSS_Table.o: PSS_Table.cc
	$(CC) $(OPT) -c PSS_Table.cc

PSS_Table_nv.o: PSS_Table.cc
	$(CC) $(OPTN) -c PSS_Table.cc -o PSS_Table_nv.o

PSS_Table_pmap.o: PSS_Table.cc
	$(CC) $(OPTP) -c PSS_Table.cc -o PSS_Table_pmap.o

clean:
	rm -f *.o

# DO NOT DELETE THIS LINE -- make depend depends on it.
