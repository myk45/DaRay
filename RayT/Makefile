# write comment!
OBJS = Main.o Camera.o Window.o Ray.o Object.o Scene.o Sphere.o Plane.o
INC = -I "./"
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -lGL -lGLU -lglut
LIBS = -lGL -lGLU -lglut

RayT: $(OBJS)
	g++ -lGL -lGLU -lglut $(OBJS) -o RayT.out
	rm -f $(OBJS)

Main.o:
	g++ -c Main.cpp $(INC)
	
Camera.o:
	g++ -c Camera.cpp $(INC)	
	
Window.o:
	g++ -c Window.cpp $(INC)	

Ray.o:
	g++ -c Ray.cpp $(INC)
	
Object.o:
	g++ -c Object.cpp $(INC)	
	
Sphere.o:
	g++ -c Sphere.cpp $(INC)	
	
Scene.o:
	g++ -c Scene.cpp $(INC)	
	
Plane.o:
	g++ -c Plane.cpp $(INC)		
	
	
clean:
	rm -f $(OBJS) RayT



