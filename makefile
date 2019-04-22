# Makefile
# Specify what I need in the end. One single executable

target = 3DG

uOpt = -w -std=c++11

objects = main.o controller.o keyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o scene1.o sceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o shaderLoader.o Texture.o camera.o renderer.o

# Read this as divisionExecutable depends on ..
$(target) : $(objects)
# Need to specify how executable is produced, using below statement
	g++ -lglfw.3.3 -lGLEW.2.1.0 -framework OpenGL $(objects) -std=c++11 -w -o $(target)

# main.o does not exist, so specify how it is produced.

main.o: OPENGL/main.cpp 
	g++ -c OPENGL/main.cpp $(uOpt)

controller.o: OPENGL/Controllers/controller.cpp 
	g++ -c OPENGL/Controllers/controller.cpp $(uOpt)

keyboardAndMouse.o: OPENGL/Controllers/keyboardAndMouse.cpp 
	g++ -c OPENGL/Controllers/keyboardAndMouse.cpp $(uOpt)

GameObject.o: OPENGL/GameObject/GameObject.cpp
	g++ -c OPENGL/GameObject/GameObject.cpp $(uOpt)

Mesh.o: OPENGL/Mesh/Mesh.cpp 
	g++ -c OPENGL/Mesh/Mesh.cpp $(uOpt)

modelObject.o: OPENGL/ModelObjects/modelObject.cpp 
	g++ -c OPENGL/ModelObjects/modelObject.cpp $(uOpt) 

modelObjectInst.o: OPENGL/ModelObjects/modelObjectInst.cpp 
	g++ -c OPENGL/ModelObjects/modelObjectInst.cpp $(uOpt) 

modelObjectSingle.o: OPENGL/ModelObjects/modelObjectSingle.cpp
	g++ -c OPENGL/ModelObjects/modelObjectSingle.cpp $(uOpt) 

sceneGraph.o: OPENGL/Scenes/sceneGraph.cpp
	g++ -c OPENGL/Scenes/sceneGraph.cpp $(uOpt) 

scene1.o: OPENGL/Scenes/scene1.cpp 
	g++ -c OPENGL/Scenes/scene1.cpp $(uOpt) 

FragShader.o: OPENGL/Shaders/Objects/FragShader.cpp 
	g++ -c OPENGL/Shaders/Objects/FragShader.cpp $(uOpt) 

ShaderPipeline.o: OPENGL/Shaders/Objects/ShaderPipeline.cpp 
	g++ -c OPENGL/Shaders/Objects/ShaderPipeline.cpp $(uOpt) 

VertexShader.o: OPENGL/Shaders/Objects/VertexShader.cpp
	g++ -c OPENGL/Shaders/Objects/VertexShader.cpp $(uOpt) 

shaderLoader.o: OPENGL/Shaders/shaderLoader.cpp 
	g++ -c OPENGL/Shaders/shaderLoader.cpp $(uOpt) 

Texture.o: OPENGL/Texture/Texture.cpp 
	g++ -c OPENGL/Texture/Texture.cpp $(uOpt) 

camera.o: OPENGL/Views/camera.cpp 
	g++ -c OPENGL/Views/camera.cpp $(uOpt) 

renderer.o: OPENGL/Views/renderer.cpp 
	g++ -c OPENGL/Views/renderer.cpp $(uOpt) 

Material.o: OPENGL/Material/Material.cpp 
	g++ -c OPENGL/Material/Material.cpp $(uOpt)

clean:
	rm *.o