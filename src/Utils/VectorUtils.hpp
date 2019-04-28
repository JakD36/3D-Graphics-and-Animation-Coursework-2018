#ifndef VectorUtils_hpp
#define VectorUtils_hpp

#include <glm/glm.hpp>
#include <string>

namespace Utils{

    inline glm::vec3 Spherical2Cartesian(float radius,float yaw,float pitch){
        glm::vec3 pos;
        pos.x = radius* sin( glm::radians(yaw) ) * cos(glm::radians(pitch) );
        pos.y = radius* sin( glm::radians(pitch) );
        pos.z = radius* cos( glm::radians(yaw) ) * cos(glm::radians(pitch) );
        
        return pos;
    }

    /// Handy for debugging to find out what different vec3s are
    ///
    inline void PrintVec3(glm::vec3 vec3, std::string str1, std::string str2, std::string str3){
        
        std::string str = str1 + " >> " + std::to_string(vec3.x)
        + "\t" + str2 + " >> " + std::to_string(vec3.y)
         + "\t" + str3 + " >> " + std::to_string(vec3.z);
         
    }

}

#endif /* VectorUtils_hpp */