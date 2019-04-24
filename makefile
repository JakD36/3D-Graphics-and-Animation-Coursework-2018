# Makefile
# Specify what I need in the end. One single executable

target = app
APP_NAME=GL
uOpt = -w -std=c++11 -I Include/ 

objects = main.o controller.o keyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o scene1.o sceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o shaderLoader.o Texture.o camera.o renderer.o

all: clean_app $(target) package_app clean

# Read this as divisionExecutable depends on ..
$(target) : $(objects)
# Need to specify how executable is produced, using below statement
	g++ -framework OpenGL $(objects) -std=c++11 -w -LFrameworks -lglfw3 -lGLEW -o main  -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo

#Frameworks/libGLEW.a Frameworks/libglfw3.a
# main.o does not exist, so specify how it is produced.

main.o: src/main.cpp 
	g++ -c src/main.cpp $(uOpt)

controller.o: src/Controllers/controller.cpp 
	g++ -c src/Controllers/controller.cpp $(uOpt)

keyboardAndMouse.o: src/Controllers/keyboardAndMouse.cpp 
	g++ -c src/Controllers/keyboardAndMouse.cpp $(uOpt)

GameObject.o: src/GameObject/GameObject.cpp
	g++ -c src/GameObject/GameObject.cpp $(uOpt)

Mesh.o: src/Mesh/Mesh.cpp 
	g++ -c src/Mesh/Mesh.cpp $(uOpt)

modelObject.o: src/ModelObjects/modelObject.cpp 
	g++ -c src/ModelObjects/modelObject.cpp $(uOpt) 

modelObjectInst.o: src/ModelObjects/modelObjectInst.cpp 
	g++ -c src/ModelObjects/modelObjectInst.cpp $(uOpt) 

modelObjectSingle.o: src/ModelObjects/modelObjectSingle.cpp
	g++ -c src/ModelObjects/modelObjectSingle.cpp $(uOpt) 

sceneGraph.o: src/Scenes/sceneGraph.cpp
	g++ -c src/Scenes/sceneGraph.cpp $(uOpt) 

scene1.o: src/Scenes/scene1.cpp 
	g++ -c src/Scenes/scene1.cpp $(uOpt) 

FragShader.o: src/Shaders/Objects/FragShader.cpp 
	g++ -c src/Shaders/Objects/FragShader.cpp $(uOpt) 

ShaderPipeline.o: src/Shaders/Objects/ShaderPipeline.cpp 
	g++ -c src/Shaders/Objects/ShaderPipeline.cpp $(uOpt) 

VertexShader.o: src/Shaders/Objects/VertexShader.cpp
	g++ -c src/Shaders/Objects/VertexShader.cpp $(uOpt) 

shaderLoader.o: src/Shaders/shaderLoader.cpp 
	g++ -c src/Shaders/shaderLoader.cpp $(uOpt) 

Texture.o: src/Texture/Texture.cpp 
	g++ -c src/Texture/Texture.cpp $(uOpt) 

camera.o: src/Views/camera.cpp 
	g++ -c src/Views/camera.cpp $(uOpt) 

renderer.o: src/Views/renderer.cpp 
	g++ -c src/Views/renderer.cpp $(uOpt) 

Material.o: src/Material/Material.cpp 
	g++ -c src/Material/Material.cpp $(uOpt)

clean_app:
	rm -rf "./Build/$(APP_NAME).app/"
	
package_app:
	mkdir -p "./Build/$(APP_NAME).app"/Contents/{MacOS,Resources}
	
	# Copy any Resources folders
	cp -r "Resources/" "./Build/$(APP_NAME).app/Contents/Resources/"
	
	cp Info.plist "./Build/$(APP_NAME).app/Contents/"
	sed -e "s/APP_NAME/$(APP_NAME)/g" -i "" "./Build/$(APP_NAME).app/Contents/Info.plist"
	cp ./main "./Build/$(APP_NAME).app/Contents/MacOS/$(APP_NAME)"

clean:
	rm *.o