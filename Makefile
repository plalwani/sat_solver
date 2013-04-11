OBJS = sat_solver.o parser.o problem.o

myrun: $(OBJS)
	g++ -g -O0 -Wall $(OBJS) -o myrun

sat_solver.o: sat_solver.cpp parser.h
	g++ -c -g sat_solver.cpp

parser.o: parser.cpp parser.h
	g++ -c -g parser.cpp

node.o: node.cpp node.h
	g++ -c -g node.cpp

problem.o: problem.cpp problem.h
	g++ -c -g problem.cpp

clean:
	rm -f *.o core


