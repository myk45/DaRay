# write comment!
OBJS = Main.o Camera.o Window.o Ray.o Object.o Scene.o Sphere.o Plane.o Light.o TexCoordCalc.o SphereTexCoordCalc.o Texture.o
INC = -I "./"
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LDFLAGS = -lGL -lGLU -lglut 
LIBS = -lGL -lGLU -lglut 

RayT: $(OBJS)
	g++ -pthread -lGL -lGLU -lglut $(OBJS) -o RayT.out
	rm -f $(OBJS)

Main.o:
	g++ -c -std=c++0x -pthread Main.cpp $(INC)
	
Camera.o:
	g++ -c -std=c++0x -pthread Camera.cpp $(INC)	
	
Window.o:
	g++ -c -std=c++0x -pthread Window.cpp $(INC)	

Ray.o:
	g++ -c -std=c++0x -pthread Ray.cpp $(INC)
	
Object.o:
	g++ -c -std=c++0x -pthread Object.cpp $(INC)	
	
Sphere.o:
	g++ -c -std=c++0x -pthread Sphere.cpp $(INC)	
	
Scene.o:
	g++ -c -std=c++0x -pthread Scene.cpp $(INC)	
	
Plane.o:
	g++ -c -std=c++0x -pthread Plane.cpp $(INC)		
		
Light.o:
	g++ -c -std=c++0x -pthread Light.cpp $(INC)		
			
TexCoordCalc.o:
	g++ -c -std=c++0x -pthread TexCoordCalc.cpp $(INC)	
	
SphereTexCoordCalc.o:
	g++ -c -std=c++0x -pthread SphereTexCoordCalc.cpp $(INC)	
			
Texture.o:
	g++ -c -std=c++0x -pthread Texture.cpp $(INC)	
			
					
clean:
	rm -f $(OBJS) RayT



