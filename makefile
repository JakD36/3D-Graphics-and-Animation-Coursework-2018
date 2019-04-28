# Makefile
# Specify what I need in the end. One single executable

target = app
APP_NAME=GL
FLAGS = -w -std=c++11
BUILDDIR = Build

objects = main.o Controller.o KeyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o Scene1.o SceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o ShaderLoader.o Texture.o Camera.o Renderer.o

all: clean_app $(target) package_app clean

debug : FLAGS += -g
debug : BUILDDIR = Debug
debug : $(target)
	cp -r Resources/* Debug/

clean_debug:
	rm -r Debug/*

# Read this as divisionExecutable depends on ..
$(target) : $(objects)
# Need to specify how executable is produced, using below statement
	g++ -framework OpenGL $(BUILDDIR)/*.o $(FLAGS) -LFrameworks -lglfw3 -lGLEW -o $(BUILDDIR)/main  -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo

#Frameworks/libGLEW.a Frameworks/libglfw3.a
# main.o does not exist, so specify how it is produced.

main.o: src/main.cpp 
	g++ -c src/main.cpp $(FLAGS) -o $(BUILDDIR)/main.o

Controller.o: src/Controllers/Controller.cpp 
	g++ -c src/Controllers/Controller.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Controller.o

KeyboardAndMouse.o: src/Controllers/keyboardAndMouse.cpp 
	g++ -c src/Controllers/keyboardAndMouse.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/keyboardAndMouse.o

GameObject.o: src/GameObject/GameObject.cpp
	g++ -c src/GameObject/GameObject.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/GameObject.o

Mesh.o: src/Mesh/Mesh.cpp 
	g++ -c src/Mesh/Mesh.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Mesh.o

modelObject.o: src/ModelObjects/modelObject.cpp 
	g++ -c src/ModelObjects/modelObject.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/modelObject.o

modelObjectInst.o: src/ModelObjects/modelObjectInst.cpp 
	g++ -c src/ModelObjects/modelObjectInst.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/modelObjectInst.o

modelObjectSingle.o: src/ModelObjects/modelObjectSingle.cpp
	g++ -c src/ModelObjects/modelObjectSingle.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/modelObjectSingle.o

SceneGraph.o: src/Scenes/sceneGraph.cpp
	g++ -c src/Scenes/SceneGraph.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/SceneGraph.o

Scene1.o: src/Scenes/scene1.cpp 
	g++ -c src/Scenes/Scene1.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Scene1.o

FragShader.o: src/Shaders/FragShader.cpp 
	g++ -c src/Shaders/FragShader.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/FragShader.o

ShaderPipeline.o: src/Shaders/ShaderPipeline.cpp 
	g++ -c src/Shaders/ShaderPipeline.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/ShaderPipeline.o

VertexShader.o: src/Shaders/VertexShader.cpp
	g++ -c src/Shaders/VertexShader.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/VertexShader.o

ShaderLoader.o: src/Shaders/shaderLoader.cpp 
	g++ -c src/Shaders/ShaderLoader.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/ShaderLoader.o

Texture.o: src/Texture/Texture.cpp 
	g++ -c src/Texture/Texture.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Texture.o

Camera.o: src/Views/camera.cpp 
	g++ -c src/Views/Camera.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Camera.o

Renderer.o: src/Views/Renderer.cpp 
	g++ -c src/Views/Renderer.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Renderer.o

Material.o: src/Material/Material.cpp 
	g++ -c src/Material/Material.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Material.o

clean_app:
	rm -rf "./$(BUILDDIR)/$(APP_NAME).app/"
	
package_app:
	mkdir -p "./$(BUILDDIR)/$(APP_NAME).app"/Contents/{MacOS,Resources}
	
	./IconBuilder icon
	mv icon.icns "./$(BUILDDIR)/$(APP_NAME).app/Contents/Resources/"
	
	# Copy any Resources folders
	cp -r "Resources/" "./$(BUILDDIR)/$(APP_NAME).app/Contents/Resources/"
	
	cp Info.plist "./$(BUILDDIR)/$(APP_NAME).app/Contents/"
	sed -e "s/APP_NAME/$(APP_NAME)/g" -i "" "./$(BUILDDIR)/$(APP_NAME).app/Contents/Info.plist"
	cp $(BUILDDIR)/main "./$(BUILDDIR)/$(APP_NAME).app/Contents/MacOS/$(APP_NAME)"

clean:
	rm $(BUILDDIR)/*.o
	rm $(BUILDDIR)/main