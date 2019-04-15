#version 410 core
// The more complex fragment shader to cover the majority of the objects in the scene
out vec4 color; // We will output the colour of each fragment as per usual

in VS_OUT // grab the outputs from the vertex shader and assign to fs_in
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} fs_in;

// Grab what we need from the uniforms
uniform sampler2D tex; // the texture
uniform mat4 model_matrix;


// Set up the same lightStruc in GLSL that is used in the rest of the program, this way we can grab the lightStruc from the uniform and access everything we need
struct lightStruc{
    int on;
    int type;
    vec4 lightPosition;
    vec4 direction;
    float lightSpotCutOff;
    float lightSpotOuterCutOff;
    vec4 id;
    vec4 is;
};

#define LIGHTS 20 // We can get away with this number being higher than the one from the rest of the program, but if this is less than the number of lights then, lights will not be rendered
uniform lightStruc lights[LIGHTS];

// grab the light relevant info from uniforms
uniform vec4  viewPosition;     // camera position
uniform float lightConstant;    // used for calculating attenuation
uniform float lightLinear;      // used for calculating attenuation
uniform float lightQuadratic;   // used for calculating attenuation

uniform vec4  ia;               // Ambient colour
uniform vec3 ka;                // Ambient constant
uniform vec3 kd;                // Diffuse constant
uniform vec3 ks;                // specular constant
uniform float shininess;        // shininess constant


void main(void)
{
    // Initialise, if we dont initialise this every pixel keeps changing colour almost randomly, so if we assign the total diffuse and specular to 0 first for each fragment we get the colour we expect
    vec3 totalDiffuse = vec3(0,0,0);
    vec3 totalSpecular = vec3(0,0,0);
    
    // Ambient, Our ambient light is a constant for the scene, to my understanding. You can have each light add to the ambient, if so throw it into the loop like the rest
    // Ambient takes into account light bouncing around the room from any and ever source, so it lights every surface
    vec3 ambient = ka.r * ia.rgb;
    
    // Find the Diffuse and specular components for each light
    for(int n = 0; n < LIGHTS; n++){ // loop through each light
        
        // Initialise the diffuse and specular vec3 for this light
        vec3 diffuse;
        vec3 specular;
        if(lights[n].on == 1){ // There is a bool to determine if the light is on or off, so check if its 1 (on) or 0 (off)
            // If the light is off carr on past and set diffuse and specular to 0
            
            // Diffuse
            vec4 lightDir = normalize(lights[n].lightPosition - fs_in.fragPos); // the direction to the lightsource
            
            float diff = max(dot(normalize(fs_in.normals),lightDir),0.0); // calculate the angle between the normal for that fragment and direction to the light,
            //use max(angle,0) to make sure we only use positive angles. As a negative angle means the light source is behind the surface and therefore cant hit the surface
            
            
            // Specular
            vec4 viewDir = normalize(viewPosition - fs_in.fragPos); // find the direction from the position of the fragment in the world space to the camera
            vec4 reflectDir = reflect(-lightDir,normalize(fs_in.normals)); // find the direction that the light ideally reflects along
            
            float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess); // find the angle between these two vectors using dot product
            // again use max(angle,0) to make sure we only use the positive angles, as a negative angle means the light source is behind the fragment and therefore the light from it wont hit that surface
            
            if(lights[n].type == 0){ // if point light, remember we have two types of light, point and spotlight in this project
                // if its a point light its pretty simple just calculate the diffuse and specular components using their equations
                // with the id,is of that specific light source and the kd,ks of the material of the model
                diffuse = diff * lights[n].id.rgb * kd.rgb;
                specular = ks.rgb * lights[n].is.rgb * spec;
            }
            
            else if(lights[n].type == 1){ // if spotlight
                //Spotlight
                // we need to calculate the angle between the direction of the light to the fragment and the direction of the light
                float theta = dot(lightDir, normalize(-lights[n].direction));
                
                // we can then calculate the intensity of the light if the angle is greater than the angle of cut off for the spotlight
                float epsilon = (lights[n].lightSpotCutOff - lights[n].lightSpotOuterCutOff);
                float intensity = clamp((theta - lights[n].lightSpotOuterCutOff) / epsilon, 0.0, 1.0);
                
                if(theta > lights[n].lightSpotOuterCutOff){ // calculate light ...
                    diffuse = diff * lights[n].id.rgb * kd.rgb;     // same as before
                    specular = ks.rgb * lights[n].is.rgb * spec;
                    diffuse *= intensity; // now we can multiply our diffuse and specular by the intensity to have the light gradually fade the greater the angle
                    specular *= intensity;
                }
            }
        }else{ // if light is switched off, assign 0 to both diffuse and specular
            diffuse = vec3(0,0,0);
            specular = vec3(0,0,0);
        }
        
        // Attenuation
        float distance = length(lights[n].lightPosition - fs_in.fragPos);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));
        
        //ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        
        // Now all the light types for this particularly light has been calculated we can sum it with the total for this fragment
        //totalAmbient  += ambient;
        totalDiffuse  += diffuse;
        totalSpecular += specular;
    }
    
    //Once diffuse and specular has been found for all light sources we can use the equation for colour with a texture and light
    // Light
    color = vec4((ambient+totalDiffuse+totalSpecular)*texture(tex,fs_in.tc).rgb,1.0);
}
