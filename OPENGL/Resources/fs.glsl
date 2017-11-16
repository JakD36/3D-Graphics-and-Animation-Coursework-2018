#version 410 core
out vec4 color;
in VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} fs_in;

uniform sampler2D tex;

uniform mat4 model_matrix;

struct lightStruc{
    int type;
    vec4 lightPosition;
    vec4 direction;
    float lightSpotCutOff;
    float lightSpotOuterCutOff;
    vec4 id;
    vec4 is;
};

#define LIGHTS 20
uniform lightStruc lights[LIGHTS];


uniform vec4  viewPosition;
uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

uniform vec4  ia;        // Ambient colour
uniform vec3 ka;        // Ambient constant
uniform vec3 kd;        // Diffuse constant
uniform vec3 ks;        // specular constant
uniform float shininess;// shininess constant


void main(void)
{
    // Initialise
    vec3 totalDiffuse = vec3(0,0,0);
    vec3 totalSpecular = vec3(0,0,0);
    
    // Ambient
    vec3 ambient = ka.r * ia.rgb;
    
    // Find the Diffuse and specular components for each light
    for(int n = 0; n < LIGHTS; n++){
        
        // Initialise the diffuse and specular vec3 for this light
        vec3 diffuse;
        vec3 specular;
        
        // Diffuse
        vec4 lightDir = normalize(lights[n].lightPosition - fs_in.fragPos);
        float diff = max(dot(normalize(fs_in.normals),lightDir),0.0);
        // Specular
        vec4 viewDir = normalize(viewPosition - fs_in.fragPos);
        vec4 reflectDir = reflect(-lightDir,normalize(fs_in.normals));
        float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess);
        
        if(lights[n].type == 0){ // if point light
            diffuse = diff * lights[n].id.rgb * kd.rgb;
            specular = ks.rgb * lights[n].is.rgb * spec;
        }
        
        else if(lights[n].type == 1){ // if spotlight
            //Spotlight
            float theta = dot(lightDir, normalize(-lights[n].direction));
            float epsilon = (lights[n].lightSpotCutOff - lights[n].lightSpotOuterCutOff);
            float intensity = clamp((theta - lights[n].lightSpotOuterCutOff) / epsilon, 0.0, 1.0);
            
            if(theta > lights[n].lightSpotOuterCutOff){ // calculate light ...
                diffuse = diff * lights[n].id.rgb * kd.rgb;
                specular = ks.rgb * lights[n].is.rgb * spec;
                diffuse *= intensity;
                specular *= intensity;
            }
            
        }
        // Attenuation
        float distance = length(lights[n].lightPosition - fs_in.fragPos);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));
        
        //ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        
        //totalAmbient  += ambient;
        totalDiffuse  += diffuse;
        totalSpecular += specular;
    }
    // Light
    color = vec4((ambient+totalDiffuse+totalSpecular)*texture(tex,fs_in.tc).rgb,1.0);
}
