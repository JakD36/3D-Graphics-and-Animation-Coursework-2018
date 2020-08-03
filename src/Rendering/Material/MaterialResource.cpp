//
// Created by Jack Davidson on 14/06/2020.
//

#include "MaterialResource.h"
#include "../../Utils/DebugUtils.h"
#include <iostream>

using namespace std;

MaterialResource::MaterialResource(string materialName) : Resource(materialName)
{
    FILE* pfile = NULL;                 // using stdio and fscanf which means formatted scan file
    int result;                         // for taking output of fscanf function
    char line[256];                     // Line limited to 256 characters, more than enough space

    pfile = fopen(materialName.c_str(),"r");    // open the file with read access

    assertm(pfile != nullptr,("Could not find file " + materialName));

    if(pfile == nullptr){ // if the file doesnt open when using fopen
        cout<<"Could not find file >> "<<materialName<<endl; // print error and name of file that failed to open
    }
    else{
        do{ // if file does open loop through each line of the file while EOF has not been reached
            result = fscanf(pfile,"%s",line); // %s refers to keep scanning until first whitespace
            // we can then compare the first section of text to the different headers for each line
            if(strcmp(line,"Ka") == 0){     // The materials reflectivity constant for ambient light
                fscanf(pfile,"%f %f %f\n",&m_ka.r,&m_ka.g,&m_ka.b);
                // line will be in format of %f %f %f\n ie three floats seperated by spaces
            }
            else if(strcmp(line,"Kd") == 0){ // The materials reflectivity constant for diffused light
                fscanf(pfile,"%f %f %f\n",&m_kd.r,&m_kd.g,&m_kd.b);
            }
            else if(strcmp(line,"Ks") == 0){ // The materials reflectivity constant for specular light
                fscanf(pfile,"%f %f %f\n",&m_ks.r,&m_ks.g,&m_ks.b);
            }
            else if(strcmp(line,"Ni") == 0){ // The materials shininess indices for the specular lighting
                fscanf(pfile,"%f\n",&m_shininess);
            }
        } while (result != EOF); // end loop when End Of File has been reached
    }
    fclose(pfile);
}