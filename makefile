# Makefile
# Specify what I need in the end. One single executable

objects = main.o controller.o keyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o scene1.o sceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o shaderLoader.o Texture.o camera.o renderer.o

# Read this as divisionExecutable depends on ..
executable : $(objects)
# Need to specify how executable is produced, using below statement
	g++ -lglfw.3.3 -lGLEW.2.1.0 -framework OpenGL $(objects) -std=c++11 -w -o executable

# main.o does not exist, so specify how it is produced.

main.o: OPENGL/main.cpp OPENGL/Scenes/sceneGraph.hpp OPENGL/Scenes/scene1.hpp OPENGL/Controllers/controller.hpp OPENGL/Controllers/keyboardAndMouse.hpp OPENGL/Views/renderer.hpp
	g++ -c OPENGL/main.cpp -w -std=c++11

# Controllers
controller.o: OPENGL/Controllers/controller.cpp OPENGL/Controllers/controller.hpp
	g++ -c OPENGL/Controllers/controller.cpp -w -std=c++11 

keyboardAndMouse.o: OPENGL/Controllers/keyboardAndMouse.cpp OPENGL/Controllers/keyboardAndMouse.hpp
	g++ -c OPENGL/Controllers/keyboardAndMouse.cpp -w -std=c++11 

GameObject.o: OPENGL/GameObject/GameObject.cpp OPENGL/GameObject/GameObject.hpp
	g++ -c OPENGL/GameObject/GameObject.cpp -w -std=c++11 

Mesh.o: OPENGL/Mesh/Mesh.cpp OPENGL/Mesh/Mesh.hpp
	g++ -c OPENGL/Mesh/Mesh.cpp -w -std=c++11 

modelObject.o: OPENGL/ModelObjects/modelObject.cpp OPENGL/ModelObjects/modelObject.h
	g++ -c OPENGL/ModelObjects/modelObject.cpp -w -std=c++11 

modelObjectInst.o: OPENGL/ModelObjects/modelObjectInst.cpp OPENGL/ModelObjects/modelObjectInst.h
	g++ -c OPENGL/ModelObjects/modelObjectInst.cpp -w -std=c++11 

modelObjectSingle.o: OPENGL/ModelObjects/modelObjectSingle.cpp OPENGL/ModelObjects/modelObjectSingle.h
	g++ -c OPENGL/ModelObjects/modelObjectSingle.cpp -w -std=c++11 

sceneGraph.o: OPENGL/Scenes/sceneGraph.cpp OPENGL/Scenes/sceneGraph.hpp
	g++ -c OPENGL/Scenes/sceneGraph.cpp -w -std=c++11 

scene1.o: OPENGL/Scenes/scene1.cpp OPENGL/Scenes/scene1.hpp
	g++ -c OPENGL/Scenes/scene1.cpp -w -std=c++11 

FragShader.o: OPENGL/Shaders/Objects/FragShader.cpp OPENGL/Shaders/Objects/FragShader.hpp
	g++ -c OPENGL/Shaders/Objects/FragShader.cpp -w -std=c++11 

ShaderPipeline.o: OPENGL/Shaders/Objects/ShaderPipeline.cpp OPENGL/Shaders/Objects/ShaderPipeline.hpp
	g++ -c OPENGL/Shaders/Objects/ShaderPipeline.cpp -w -std=c++11 

VertexShader.o: OPENGL/Shaders/Objects/VertexShader.cpp OPENGL/Shaders/Objects/VertexShader.hpp
	g++ -c OPENGL/Shaders/Objects/VertexShader.cpp -w -std=c++11 

shaderLoader.o: OPENGL/Shaders/shaderLoader.cpp OPENGL/Shaders/shaderLoader.hpp
	g++ -c OPENGL/Shaders/shaderLoader.cpp -w -std=c++11 

Texture.o: OPENGL/Texture/Texture.cpp OPENGL/Texture/Texture.hpp
	g++ -c OPENGL/Texture/Texture.cpp -w -std=c++11 

camera.o: OPENGL/Views/camera.cpp OPENGL/Views/camera.hpp
	g++ -c OPENGL/Views/camera.cpp -w -std=c++11 

renderer.o: OPENGL/Views/renderer.cpp OPENGL/Views/renderer.hpp
	g++ -c OPENGL/Views/renderer.cpp -w -std=c++11 

Material.o: OPENGL/Material/Material.cpp OPENGL/Material/Material.hpp
	g++ -c OPENGL/Material/Material.cpp -w -std=c++11