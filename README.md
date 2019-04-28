# 3D-Graphics-and-Animation-Coursework

Coursework for F21GA 3D Graphics and Animation.

My submission for the coursework, will be adding to this periodically to try new things in OpenGL and improve on the project.

## Getting Started

To build this project for MacOS is achieved through the use of make.

### Prerequisites

To be able build the project two OpenGL libraries are required, found at the sites linked below.
```
GLEW - http://glew.sourceforge.net/
glfw3 - https://www.glfw.org/
```
Build the static libraries following the instructions on their respective websites and add these to a Frameworks folder in the root of this project. 

As for the headers, this project makes use of the two header folders for the above libraries along side two header only libraries
```
gli - http://gli.g-truc.net/0.8.2/index.html
glm - https://glm.g-truc.net/0.9.9/index.html
```
The folders for each of these shoulde be added to an Include folder at the root of the project.

### Building

Once the Frameworks and header files are in place, simply open the terminal to root of the project and enter make to start the build. This will remove any previous build, then compile each of the source files before packaging the result into a .app bundle.

Expected output is as follows
```
$ make
rm -rf "./Build/GL.app/"
g++ -c src/main.cpp -w -std=c++11 -I Include/ 
g++ -c src/Controllers/controller.cpp -w -std=c++11 -I Include/ 
g++ -c src/Controllers/keyboardAndMouse.cpp -w -std=c++11 -I Include/ 
g++ -c src/GameObject/GameObject.cpp -w -std=c++11 -I Include/ 
g++ -c src/Material/Material.cpp -w -std=c++11 -I Include/ 
g++ -c src/Mesh/Mesh.cpp -w -std=c++11 -I Include/ 
g++ -c src/ModelObjects/modelObject.cpp -w -std=c++11 -I Include/  
g++ -c src/ModelObjects/modelObjectInst.cpp -w -std=c++11 -I Include/  
g++ -c src/ModelObjects/modelObjectSingle.cpp -w -std=c++11 -I Include/  
g++ -c src/Scenes/scene1.cpp -w -std=c++11 -I Include/  
g++ -c src/Scenes/sceneGraph.cpp -w -std=c++11 -I Include/  
g++ -c src/Shaders/Objects/FragShader.cpp -w -std=c++11 -I Include/  
g++ -c src/Shaders/Objects/VertexShader.cpp -w -std=c++11 -I Include/  
g++ -c src/Shaders/Objects/ShaderPipeline.cpp -w -std=c++11 -I Include/  
g++ -c src/Shaders/shaderLoader.cpp -w -std=c++11 -I Include/  
g++ -c src/Texture/Texture.cpp -w -std=c++11 -I Include/  
g++ -c src/Views/camera.cpp -w -std=c++11 -I Include/  
g++ -c src/Views/Renderer.cpp -w -std=c++11 -I Include/  
g++ -framework OpenGL main.o controller.o keyboardAndMouse.o GameObject.o Material.o Mesh.o modelObject.o modelObjectInst.o modelObjectSingle.o scene1.o sceneGraph.o FragShader.o VertexShader.o ShaderPipeline.o shaderLoader.o Texture.o camera.o Renderer.o -std=c++11 -w -LFrameworks -lglfw3 -lGLEW -o main  -framework Cocoa -framework IOKit -framework CoreFoundation -framework CoreVideo
mkdir -p "./Build/GL.app"/Contents/{MacOS,Resources}
# Copy any Resources folders
cp -r "Resources/" "./Build/GL.app/Contents/Resources/"
cp Info.plist "./Build/GL.app/Contents/"
sed -e "s/APP_NAME/GL/g" -i "" "./Build/GL.app/Contents/Info.plist"
cp ./main "./Build/GL.app/Contents/MacOS/GL"
rm *.o
```
