//
//  modelObject.cpp
//  OPENGLClassTest
//
//  Created by Jack Davidson on 09/11/2017.
//  Copyright © 2017 Jack Davidson. All rights reserved.
//

#include "modelObject.h"

modelObject::modelObject(){
    // Does nothing
}

modelObject::~modelObject(){
    // Does nothing
}

void modelObject::initModel(string objPath,string vsPath,string fsPath){
    
    ShaderLoader* shaderInst = ShaderLoader::GetInstance(); // Get the instance of the singleton to load the shader
    
    program = glCreateProgram();                    // Create the program, for this model, to attach the shaders to
    
    // Load, compile and attach the provided to the program
    // Vertex shader
    string vs_text = shaderInst->ReadShader(vsPath);
    const char * vs_source = vs_text.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    shaderInst->CheckErrorShader(vs);
    glAttachShader(program, vs);
    
    // Fragment shader
    string fs_text = shaderInst->ReadShader(fsPath);
    const char * fs_source = fs_text.c_str();
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    shaderInst->CheckErrorShader(fs);
    glAttachShader(program, fs);
    
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    
    
    glGenBuffers(3,buffer); // Generate the buffer to store the vertices, uvs and normals
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    
//     TODO: Could move object loading to a singleton, save it being part of the model class
    load(objPath); // Get the vertices, uvs and normals from the .obj files
    
    // For debug we can uncomment to see how many vertices, UVs and Normals are in each object
//    cout<<"Vertices\t"<<out_vertices.size()<<"\tUVS\t"<<out_uvs.size()<<"\tNormals"<<out_normals.size()<<endl;
    
    
    glBufferData(GL_ARRAY_BUFFER,                       // store the vertices in the first part of the buffer
                 out_vertices.size()*sizeof(glm::vec3), // vertices size * size of vec3 tells us how much space in the buffer to allocate
                 &out_vertices[0],                      // Where to start in the vertices vector
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    // Do the same for uvs
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 out_uvs.size()*sizeof(glm::vec2),      // Uvs are only two coordinates, so use size of vec2 for space allocation
                 &out_uvs[0],
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    
    // Same again for normals
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER,
                 out_normals.size()*sizeof(glm::vec3),
                 &out_normals[0],
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(2, 3 , GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);
    
    glLinkProgram(program);
    glUseProgram(program);

}

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

// The following comes from the labs in F21GA 3D Graphics and Animation

void modelObject::initTexture(string texPath){
    glGenTextures(1, texture);
    gli::texture tex = gli::load(texPath);
    if(tex.empty()){
        cout<<"Unable to load file "+texPath <<endl;
    }
    gli::gl texGL(gli::gl::PROFILE_GL33);
    gli::gl::format const texFormat = texGL.translate(tex.format(), tex.swizzles());
    //load and create a texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glm::tvec3<GLsizei> const texExtent(tex.extent());
    GLsizei const texFaceTotal = static_cast<GLsizei>(tex.layers()*tex.faces());
    glTexStorage2D(GL_TEXTURE_2D,static_cast<GLint>(tex.levels()),texFormat.Internal,texExtent.x,texExtent.y);
    for(std::size_t Layer = 0;Layer<tex.layers();++Layer){
        for(std::size_t Face = 0;Face<tex.faces();++Face){
            for(std::size_t Level = 0; Level<tex.levels();++Level){
                glTexSubImage2D(GL_TEXTURE_2D,static_cast<GLint>(Level),0,0,texExtent.x,texExtent.y,texFormat.External,texFormat.Type,tex.data(Layer,Face,Level));
            }
        }
    }
    
    // This only works for 2D Textures...
    // Set the texture wrapping parameters (next lecture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering parameters (next lecture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Generate mipmaps (next lecture)
    glGenerateMipmap(GL_TEXTURE_2D);
}

// End of code taken from lectures!

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/*
 Reads the file provided, to extract the material properties for the object
 
*/
bool modelObject::loadMat(string name){
    FILE* pfile = NULL;                 // using stdio and fscanf which means formatted scan file
    int result;                         // for taking output of fscanf function
    char line[256];                     // Line limited to 256 characters, more than enough space
    
    pfile = fopen(name.c_str(),"r");    // open the file with read access
    
    if(pfile == NULL){ // if the file doesnt open when using fopen
        cout<<"Could not find file >> "<<name<<endl; // print error and name of file that failed to open
        return false; // exit function as it has failed
    }
    else{
        do{ // if file does open loop through each line of the file while EOF has not been reached
            result = fscanf(pfile,"%s",line); // %s refers to keep scanning until first whitespace
            // we can then compare the first section of text to the different headers for each line
            if(strcmp(line,"Ka") == 0){     // The materials reflectivity constant for ambient light
                fscanf(pfile,"%f %f %f\n",&ka.r,&ka.g,&ka.b);
                // line will be in format of %f %f %f\n ie three floats seperated by spaces
            }
            else if(strcmp(line,"Kd") == 0){ // The materials reflectivity constant for diffused light
                fscanf(pfile,"%f %f %f\n",&kd.r,&kd.g,&kd.b);
            }
            else if(strcmp(line,"Ks") == 0){ // The materials reflectivity constant for specular light
                fscanf(pfile,"%f %f %f\n",&ks.r,&ks.g,&ks.b);
            }
            else if(strcmp(line,"Ni") == 0){ // The materials shininess indices for the specular lighting
                fscanf(pfile,"%f\n",&shininess);
            }
        } while (result != EOF); // end loop when End Of File has been reached
        return true; // Return to true to show the file did open successfully
    }
}

/*
 Set up the object to be rendered
*/
void modelObject::setupRender(glm::mat4& proj_matrix, lightStruct lights[],glm::vec3& camera){
    // For each model Object
    glUseProgram(program);
    glBindVertexArray(vao);
    
    // Pass projection matrix through to the shaders through the uniforms
    glUniformMatrix4fv(glGetUniformLocation(program,"proj_matrix"), 1, GL_FALSE, &proj_matrix[0][0]);
    // Bind textures and samplers - using 0 as I know there is only one texture - need to extend.
    
    // Assign the values to each of the appropriate uniforms so that they can be accessed by the shaders
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Pass a number of values through to the shaders through the uniforms
    glUniform1i(glGetUniformLocation(program,"tex"), 0);                    // The texture
    glUniform4f(glGetUniformLocation(program,"viewPosition"),camera.x,camera.y,camera.z,1.0f); // The camera position
    glUniform4f(glGetUniformLocation(program, "ia"), ia.r, ia.g, ia.b, 1.0f); // The ambient light intensity, as there is only one for the scene
    glUniform3f(glGetUniformLocation(program, "ka"), ka.r,ka.g,ka.b); // The material materials ambient reflectivity constant
    glUniform3f(glGetUniformLocation(program, "kd"), kd.r,kd.g,kd.b); // The material materials diffused reflectivity constant
    glUniform3f(glGetUniformLocation(program, "ks"), ks.r,ks.g,ks.b); // The material materials specular reflectivity constant
    glUniform1f(glGetUniformLocation(program, "shininess"), shininess); // The materials shininess indices
    glUniform1f(glGetUniformLocation(program,"lightConstant"),0.25f);       // Constant used for attenuation, taken from lecture notes
    glUniform1f(glGetUniformLocation(program,"lightLinear"),0.7f);          // Constant used for attenuation, taken from lecture notes
    glUniform1f(glGetUniformLocation(program,"lightQuadratic"),1.0f);       // Constant used for attenuation, taken from lecture notes

    
    // Loop through each of the lights and provide the necessary information to the shader through the uniforms
    for(int n = 0;n<LIGHTSN;n++){
        /*
         Need to pass each piece of information in seperately, so that the shaders can read it
         The name of each element is constructed as follows
         lights[#].KEY
         where the # is the number of that light
         and the KEY is the information wanted for that light, such as on, type, lightPosition
        */
        glUniform1i(glGetUniformLocation(program,("lights["+to_string(n)+"].on").c_str()),lights[n].lightOn);
        glUniform1i(glGetUniformLocation(program,("lights["+to_string(n)+"].type").c_str()),lights[n].type);
        glUniform4f(glGetUniformLocation(program,
                                         ("lights["+to_string(n)+"].lightPosition").c_str()),
                    lights[n].position.x,lights[n].position.y,lights[n].position.z,1.0f);
        
        glUniform4f(glGetUniformLocation(program,
                                         ("lights["+to_string(n)+"].direction").c_str()),
                    lights[n].direction.x,lights[n].direction.y,lights[n].direction.z,0.0f);
        glUniform4f(glGetUniformLocation(program,("lights["+to_string(n)+"].id").c_str()),lights[n].id.r,lights[n].id.g,lights[n].id.b,1.0f);
        glUniform1f(glGetUniformLocation(program, ("lights["+to_string(n)+"].lightSpotCutOff").c_str()), glm::cos(glm::radians(15.0f)));
        glUniform1f(glGetUniformLocation(program, ("lights["+to_string(n)+"].lightSpotOuterCutOff").c_str()), glm::cos(glm::radians(20.0f)));
        
        glUniform4f(glGetUniformLocation(program,("lights["+to_string(n)+"].is").c_str()),lights[n].is.r,lights[n].is.g,lights[n].is.b,1.0f);
    }
    
    /*
     This is the same for all model Objects, so this is contained within the modelObject abstract class,
     To render the object, call this method followed by the render method that is implemented in subclasses.
    */
}


bool modelObject::load(string name){
    // Variables
    FILE* pfile = NULL; // using stdio and fscanf which means formatted scan file
    int result;         // for taking output of fscanf function
    char line[256];     // char array of size 256 for storing each line of the file (limited to lines of 256 in length which could be an issue)
    
    vector<glm::vec3> tmpV; //Temp vertex indices
    vector<glm::vec2> tmpVt; // temp vertex texture indices
    vector<glm::vec3> tmpVn; // temp vertex normal indices
    
    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    
    int matches;
    
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    
    
    pfile = fopen(name.c_str(),"r"); // open the file with read access
    
    if(pfile == NULL){ // if the file doesnt open when using fopen
        cout<<"Could not find file >> "<<name<<endl; // print error and name of file that failed to open
        return false; // exit function as it has failed
    }
    else{
        do{ // if file does open loop through each line of the file while EOF has not been reached
            result = fscanf(pfile,"%s",line); // %s refers to keep scanning until first whitespace
            // we can then compare the first section of text to the different headers for each line
            
            // "v" means the following text is vertexs
            if(strcmp(line,"v") == 0){ // vertex indices (x,y,z) glm::vec3
                glm::vec3 vertex; // create temporary storage for vertices
                
                fscanf(pfile,"%f %f %f\n",&vertex.x,&vertex.y,&vertex.z); // take the vertices and assign to vertex variable
                // line will be in format of %f %f %f\n ie three floats seperated by spaces
                tmpV.push_back(vertex); // copy the vertex from this line to the back of the vertex vector
                
            }
            // "vt" means the following text is uvs
            else if(strcmp(line,"vt") == 0){ // vertex texture indices (u,v) glm::vec2
                glm::vec2 uv; // Create temporary storage for vertices
                
                fscanf(pfile,"%f %f\n",&uv.x,&uv.y); // assign the uvs to the uv variable as with vertex line
                tmpVt.push_back(uv); // copy temporary uv to the back of the uv vector
            }
            // "vn" means the following text is normals
            else if(strcmp(line,"vn") == 0){ // vertex normal indices (x,y,z) glm::vec3, might not be unit vectors
                glm::vec3 normal; // create temporary storage for normals
                
                fscanf(pfile,"%f %f %f\n",&normal.x,&normal.y,&normal.z); // assign the normals to the normal variable as with vertex line
                tmpVn.push_back(normal); // copy the temporary normal to the normal vector
            }
            else if(strcmp(line,"f") == 0){ // Polygonal face element
                
                // so there are multiple formats for these lines so we use sscanf to go through each line after the first whitespace
                // the formats are
                
                // %d/%d/%d %d/%d/%d %d/%d/%d\n ie we have vertex.x/uv.x/normal.x vertex.y/uv.y/normal.y vertex.z/uv.z/normal.z\n
                
                // %d//%d %d//%d %d//%d\n ie we have vertex.x//normal.x vertex.y//normal.y vertex.z//normal.z\n
                
                // %d/%d %d/%d %d/%d\n ie we have vertex.x/uv.x vertex.y/uv.y vertex.z/uv.z\n
                
                // %d %d %d\n ie we have vertex.x vertex.y vertex.z\n
                
                result = fscanf(pfile,"%[^\n]", line); // store everything until the end of the line in the char array line
                if((matches = sscanf(line,"%d/%d/%d %d/%d/%d %d/%d/%d\n", // Format of expected line, ie 3 sets of vertex,uv and normal
                                     &vertexIndex[0],&uvIndex[0],&normalIndex[0], // Assign .x values for each
                                     &vertexIndex[1],&uvIndex[1],&normalIndex[1], // assign .y values for each
                                     &vertexIndex[2],&uvIndex[2],&normalIndex[2]) // assign .z values for each
                    ) == 9){ // sscanf returns how many of the variables in the line follow the pattern we have given if there 9 matches we have the right format
                    
                    // add each vertex index into the vertexIndices vector
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    
                    // add each uv index into the uvIndices vector
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    
                    // add each normal index into the normalIndices vector
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                    
                }
                else if((matches = sscanf(line,"%d//%d %d//%d %d//%d\n", // format of expected line ie 3 sets of vertex and normals
                                          &vertexIndex[0],&normalIndex[0], // assign .x values for each
                                          &vertexIndex[1],&normalIndex[1], // assign .y values for each
                                          &vertexIndex[2],&normalIndex[2]) // assign .z values for each
                         ) == 6){ // sscanf returns how many of the variables in the line follow the pattern we have given if there 6 matches we have the right format
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    normalIndices.push_back(normalIndex[0]);
                    
                    vertexIndices.push_back(vertexIndex[1]);
                    normalIndices.push_back(normalIndex[1]);
                    
                    vertexIndices.push_back(vertexIndex[2]);
                    normalIndices.push_back(normalIndex[2]);
                    
                }
                else if(sscanf(line,"%d/%d %d/%d %d/%d\n", // format of expected line ie 3 sets of vertex and uvs
                               &vertexIndex[0],&uvIndex[0], // assign .x values for each
                               &vertexIndex[1],&uvIndex[1], // assign .y values for each
                               &vertexIndex[2],&uvIndex[2]) // assign .z values for each
                        == 6){ // sscanf returns how many of the variables in the line follow the pattern we have given if there 6 matches we have the right format
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                    
                }
                
                else if(sscanf(line,"%d %d %d\n", // format of expected line ie 3 vertices
                               &vertexIndex[0],
                               &vertexIndex[1],
                               &vertexIndex[2])
                        == 3){
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                }
                else{ // If the lines dont match any of the given formats then the error will be printed along with the line and the number of matches
                    cout<<"Does not match parser result >>"<<endl;
                    cout<<line<<endl;
                    cout<<"This gave "<< matches<<" matches"<<endl;
                }
            }
            
            
            
        } while (result != EOF);
        
        
        // Now to go through vertex, uv and normal and push each to the vectors that will be outputted from the object
        for(unsigned int i=0; i<vertexIndices.size();i+=3){ // loops through the vertexIndices in batches of 3, so we can reverse them so that everything is displayed correctly
            
            // the index of the vertex position is vertexIndices[i]
            // so the position is temp_vertices[vertexIndex-1], -1 because C++ starts at 0 whereas obj starts at 1
            
            unsigned int vertexIndex = vertexIndices[i]; // Creates an index and assigns 2 above the current place in loop so we start at the end
            glm::vec3 vertex = tmpV[vertexIndex-1]; // stores the tmpV and subtracts 1 from index as C++ starts at 0 not 1
            out_vertices.push_back(vertex); // this adds the position to the back of the vertex
            
            vertexIndex = vertexIndices[i+1]; // so we get the index for the middle vertex by moving up 1 indices
            vertex = tmpV[vertexIndex-1];
            out_vertices.push_back(vertex); // this makes the position of our new vertex
            
            vertexIndex = vertexIndices[i+2]; // finally indexes the first value in the 3 and adds it to the back of the 3 completing reverse of batch
            vertex = tmpV[vertexIndex-1];
            out_vertices.push_back(vertex); // this makes the position of our new vertex
        }
        
        // Repeats the above done for vertices for both normals and uvs if we have them
        if(!tmpVn.empty()){ // If we have normals push them
            for(unsigned int i=0; i<normalIndices.size();i+=3){
                // the index of the vertex position is vertexIndices[i]
                // so the position is temp_vertices[vertexIndex-1] -1 because C++ starts at 0 whereas obj starts at
                
                unsigned int normalIndex = normalIndices[i];
                glm::vec3 normal = tmpVn[normalIndex-1];
                out_normals.push_back(normal);
                
                normalIndex = normalIndices[i+1];
                normal = tmpVn[normalIndex-1];
                out_normals.push_back(normal);
                
                normalIndex = normalIndices[i+2];
                normal = tmpVn[normalIndex-1];
                out_normals.push_back(normal);
            }
        }
        if(!tmpVt.empty()){
            for(unsigned int i=0; i<uvIndices.size();i+=3){
                // the index of the vertex position is vertexIndices[i]
                // so the position is temp_vertices[vertexIndex-1] -1 because C++ starts at 0 whereas obj starts at 1
                
                unsigned int uvIndex = uvIndices[i];
                glm::vec2 uv = tmpVt[uvIndex-1];
                out_uvs.push_back(uv);
                
                uvIndex = uvIndices[i+1];
                uv = tmpVt[uvIndex-1];
                out_uvs.push_back(uv);
                
                uvIndex = uvIndices[i+2];
                uv = tmpVt[uvIndex-1];
                out_uvs.push_back(uv);
            }
        }
        /*// Now to go through vertex, uv and normal and push each to the vectors that will be outputted from the object
         for(unsigned int i=0; i<vertexIndices.size();i++){ // loops through the vertexIndices in batches of 3, so we can reverse them so that everything is displayed correctly
         
         // the index of the vertex position is vertexIndices[i]
         // so the position is temp_vertices[vertexIndex-1], -1 because C++ starts at 0 whereas obj starts at 1
         
         unsigned int vertexIndex = vertexIndices[i]; // Creates an index and assigns 2 above the current place in loop so we start at the end
         glm::vec3 vertex = tmpV[vertexIndex-1]; // stores the tmpV and subtracts 1 from index as C++ starts at 0 not 1
         out_vertices.push_back(vertex); // this adds the position to the back of the vertex
         
         }
         
         // Repeats the above done for vertices for both normals and uvs if we have them
         if(!tmpVn.empty()){ // If we have normals push them
         for(unsigned int i=0; i<normalIndices.size();i++){
         // the index of the vertex position is vertexIndices[i]
         // so the position is temp_vertices[vertexIndex-1] -1 because C++ starts at 0 whereas obj starts at
         
         unsigned int normalIndex = normalIndices[i];
         glm::vec3 normal = tmpVn[normalIndex-1];
         out_normals.push_back(normal);
         }
         }
         if(!tmpVt.empty()){
         for(unsigned int i=0; i<uvIndices.size();i++){
         // the index of the vertex position is vertexIndices[i]
         // so the position is temp_vertices[vertexIndex-1] -1 because C++ starts at 0 whereas obj starts at
         
         unsigned int uvIndex = uvIndices[i];
         glm::vec2 uv = tmpVt[uvIndex-1];
         out_uvs.push_back(uv);
         }
         }*/
        fclose(pfile); // closes file and returns true to indicate that the import was successful
        return true;
    }
}
