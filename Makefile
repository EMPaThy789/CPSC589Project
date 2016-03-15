EXEFILE = Subdivision
LIBS = -lglfw -lGL -lGLU
OBJS = main.o DCEL.o Face.o HalfEdge.o Vertex.o


$(EXEFILE): main.o
	g++ $(LIBS) -o $(EXEFILE) $(OBJS)
	
clean:
	rm $(EXEFILE) (OBJS)

# OBJS
# add more for each new file
# also add to OBJS at top seperated by space
# add to header when new headers are needed
main.o: main.cpp
	g++ -c main.cpp
DCEL.o: DCEL.cpp
	g++ -c DCEL.cpp
Face.o: Face.cpp
	g++ -c Face.cpp
HalfEdge.o: HalfEdge.cpp
	g++ -c HalfEdge.cpp
Vertex.o: Vertex.cpp
	g++ -c Vertex.cpp