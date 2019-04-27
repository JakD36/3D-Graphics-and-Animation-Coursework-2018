# Makefile
# Specify what I need in the end. One single executable

target = app
APP_NAME=GL
FLAGS = -w -std=c++11

objects = main.o controller.o keyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o scene1.o sceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o shaderLoader.o Texture.o camera.o renderer.o

all: clean_app $(target) package_app clean

debug : FLAGS += -g
debug : $(target)
	# mkdir -p Debug
	mv main Debug/
	# mv *.o Debug/
	cp -r Resources/* Debug/

clean_debug:
	rm -r Debug

# Read this as divisionExecutable depends on ..
$(target) : $(objects)
# Need to specify how executable is produced, using below statement
	g++ -framework OpenGL $(objects) $(FLAGS) -LFrameworks -lglfw3 -lGLEW -o main  -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo

#Frameworks/libGLEW.a Frameworks/libglfw3.a
# main.o does not exist, so specify how it is produced.

main.o: src/main.cpp 
	g++ -c src/main.cpp $(FLAGS)

controller.o: src/Controllers/controller.cpp 
	g++ -c src/Controllers/controller.cpp $(FLAGS) -I Include/

keyboardAndMouse.o: src/Controllers/keyboardAndMouse.cpp 
	g++ -c src/Controllers/keyboardAndMouse.cpp $(FLAGS) -I Include/

GameObject.o: src/GameObject/GameObject.cpp
	g++ -c src/GameObject/GameObject.cpp $(FLAGS) -I Include/

Mesh.o: src/Mesh/Mesh.cpp 
	g++ -c src/Mesh/Mesh.cpp $(FLAGS) -I Include/

modelObject.o: src/ModelObjects/modelObject.cpp 
	g++ -c src/ModelObjects/modelObject.cpp $(FLAGS) -I Include/

modelObjectInst.o: src/ModelObjects/modelObjectInst.cpp 
	g++ -c src/ModelObjects/modelObjectInst.cpp $(FLAGS) -I Include/

modelObjectSingle.o: src/ModelObjects/modelObjectSingle.cpp
	g++ -c src/ModelObjects/modelObjectSingle.cpp $(FLAGS) -I Include/

sceneGraph.o: src/Scenes/sceneGraph.cpp
	g++ -c src/Scenes/sceneGraph.cpp $(FLAGS) -I Include/

scene1.o: src/Scenes/scene1.cpp 
	g++ -c src/Scenes/scene1.cpp $(FLAGS) -I Include/

FragShader.o: src/Shaders/Objects/FragShader.cpp 
	g++ -c src/Shaders/Objects/FragShader.cpp $(FLAGS) -I Include/

ShaderPipeline.o: src/Shaders/Objects/ShaderPipeline.cpp 
	g++ -c src/Shaders/Objects/ShaderPipeline.cpp $(FLAGS) -I Include/

VertexShader.o: src/Shaders/Objects/VertexShader.cpp
	g++ -c src/Shaders/Objects/VertexShader.cpp $(FLAGS) -I Include/

shaderLoader.o: src/Shaders/shaderLoader.cpp 
	g++ -c src/Shaders/shaderLoader.cpp $(FLAGS) -I Include/

Texture.o: src/Texture/Texture.cpp 
	g++ -c src/Texture/Texture.cpp $(FLAGS) -I Include/

camera.o: src/Views/camera.cpp 
	g++ -c src/Views/camera.cpp $(FLAGS) -I Include/

renderer.o: src/Views/renderer.cpp 
	g++ -c src/Views/renderer.cpp $(FLAGS) -I Include/

Material.o: src/Material/Material.cpp 
	g++ -c src/Material/Material.cpp $(FLAGS) -I Include/

clean_app:
	rm -rf "./Build/$(APP_NAME).app/"
	
package_app:
	mkdir -p "./Build/$(APP_NAME).app"/Contents/{MacOS,Resources}
	
	./IconBuilder icon
	mv icon.icns "./Build/$(APP_NAME).app/Contents/Resources/"
	
	# Copy any Resources folders
	cp -r "Resources/" "./Build/$(APP_NAME).app/Contents/Resources/"
	
	cp Info.plist "./Build/$(APP_NAME).app/Contents/"
	sed -e "s/APP_NAME/$(APP_NAME)/g" -i "" "./Build/$(APP_NAME).app/Contents/Info.plist"
	cp ./main "./Build/$(APP_NAME).app/Contents/MacOS/$(APP_NAME)"

clean:
	rm *.o
	rm main