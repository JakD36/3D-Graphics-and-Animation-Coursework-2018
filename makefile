# Makefile
# Specify what I need in the end. One single executable

target = app
APP_NAME=GL
FLAGS = -w -std=c++11
BUILDDIR = Build
CC = g++
#CC = clang

objects = main.o Controller.o KeyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o Scene1.o SceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o ShaderLoader.o Texture.o Camera.o Renderer.o Render.o imgui.o imgui_demo.o imgui_draw.o imgui_impl_opengl3.o imgui_impl_glfw.o imgui_widgets.o ProfilerService.o

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
	$(CC) -framework OpenGL $(BUILDDIR)/*.o $(FLAGS) -LFrameworks -lglfw3 -lGLEW -o $(BUILDDIR)/main  -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo

#Frameworks/libGLEW.a Frameworks/libglfw3.a
# main.o does not exist, so specify how it is produced.

main.o: src/main.cpp 
	$(CC) -c src/main.cpp $(FLAGS) -o $(BUILDDIR)/main.o

Render.o: src/Views/Render.cpp
	$(CC) -c src/Views/Render.cpp $(FLAGS) -o $(BUILDDIR)/Render.o

Controller.o: src/Controllers/Controller.cpp 
	$(CC) -c src/Controllers/Controller.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Controller.o

KeyboardAndMouse.o: src/Controllers/keyboardAndMouse.cpp 
	$(CC) -c src/Controllers/keyboardAndMouse.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/keyboardAndMouse.o

GameObject.o: src/GameObject/GameObject.cpp
	$(CC) -c src/GameObject/GameObject.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/GameObject.o

Mesh.o: src/Mesh/Mesh.cpp 
	$(CC) -c src/Mesh/Mesh.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Mesh.o

modelObject.o: src/ModelObjects/modelObject.cpp 
	$(CC) -c src/ModelObjects/modelObject.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/modelObject.o

modelObjectInst.o: src/ModelObjects/modelObjectInst.cpp 
	$(CC) -c src/ModelObjects/modelObjectInst.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/modelObjectInst.o

modelObjectSingle.o: src/ModelObjects/modelObjectSingle.cpp
	$(CC) -c src/ModelObjects/modelObjectSingle.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/modelObjectSingle.o

SceneGraph.o: src/Scenes/sceneGraph.cpp
	$(CC) -c src/Scenes/SceneGraph.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/SceneGraph.o

Scene1.o: src/Scenes/scene1.cpp 
	$(CC) -c src/Scenes/Scene1.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Scene1.o

FragShader.o: src/Shaders/FragShader.cpp 
	$(CC) -c src/Shaders/FragShader.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/FragShader.o

ShaderPipeline.o: src/Shaders/ShaderPipeline.cpp 
	$(CC) -c src/Shaders/ShaderPipeline.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/ShaderPipeline.o

VertexShader.o: src/Shaders/VertexShader.cpp
	$(CC) -c src/Shaders/VertexShader.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/VertexShader.o

ShaderLoader.o: src/Shaders/shaderLoader.cpp 
	$(CC) -c src/Shaders/ShaderLoader.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/ShaderLoader.o

Texture.o: src/Texture/Texture.cpp 
	$(CC) -c src/Texture/Texture.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Texture.o

Camera.o: src/Views/camera.cpp 
	$(CC) -c src/Views/Camera.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Camera.o

Renderer.o: src/Views/Renderer.cpp 
	$(CC) -c src/Views/Renderer.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Renderer.o

Material.o: src/Material/Material.cpp 
	$(CC) -c src/Material/Material.cpp $(FLAGS) -I Include/ -o $(BUILDDIR)/Material.o

imgui_demo.o: Include/DearImgui/imgui_demo.cpp
	$(CC) -c Include/DearImgui/imgui_demo.cpp -I Include/ -o $(BUILDDIR)/imgui_demo.o

imgui.o: Include/DearImgui/imgui.cpp
	$(CC) -c Include/DearImgui/imgui.cpp -I Include/ -o $(BUILDDIR)/imgui.o

imgui_draw.o: Include/DearImgui/imgui_draw.cpp
	$(CC) -c Include/DearImgui/imgui_draw.cpp -I Include/ -o $(BUILDDIR)/imgui_draw.o

imgui_impl_opengl3.o: Include/DearImgui/imgui_impl_opengl3.cpp
	$(CC) -c Include/DearImgui/imgui_impl_opengl3.cpp -I Include/ -o $(BUILDDIR)/imgui_impl_opengl3.o

imgui_impl_glfw.o: Include/DearImgui/imgui_impl_glfw.cpp
	$(CC) -c Include/DearImgui/imgui_impl_glfw.cpp -I Include/ -o $(BUILDDIR)/imgui_impl_glfw.o

imgui_widgets.o: Include/DearImgui/imgui_widgets.cpp
	$(CC) -c Include/DearImgui/imgui_widgets.cpp -I Include/ -o $(BUILDDIR)/imgui_widgets.o

ProfilerService.o: src/Utils/ProfilerService.cpp
	$(CC) -c src/Utils/ProfilerService.cpp -I Include/ -o $(BUILDDIR)/ProfilerService.o


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