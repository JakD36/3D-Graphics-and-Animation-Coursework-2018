#version 410 core

/// TODO: Fix shader issues with using UBO that conflicts with the for loop and lights[n].type, Seems to be a driver issue

out vec4 color;

in VS_OUT
{
    vec2 tc;
    vec3 normals;
    vec3 fragPos;
} fs_in;

uniform sampler2D tex;

struct lightStruct{
    int on;
    int type;

    vec4 lightPosition;
    vec4 direction;

    float lightSpotCutOff;
    float lightSpotOuterCutOff;

    vec4 id;
    vec4 is;
};

#define LIGHTS 4
layout (std140) uniform lightBlock
{
    lightStruct lights[LIGHTS];
};


uniform vec3  viewPosition;
// Attenuation variables
uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

uniform vec4 ia;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float shininess;

struct Lighting
{
    vec3 diffuse;
    vec3 specular;
};

vec3 Diffuse(vec3 lightDir, vec3 surfaceNormal, vec3 light, vec3 reflectionConstant);
vec3 Specular(vec3 lightDir, vec3 surfaceNormal, vec3 fragWorldPos, float shininess, vec3 eyePosition, vec3 light, vec3 reflectionConstant);
Lighting CalculateSpotLight(lightStruct light, vec3 fragWorldPos,vec3 fragToLightDir, vec3 normal);
Lighting CalculateLighting(lightStruct light, vec3 fragWorldPos, vec3 normal);

void main(void)
{
    vec3 ambient = ka.r * ia.rgb;

    Lighting light1 = CalculateLighting(lights[0], fs_in.fragPos.xyz, fs_in.normals.xyz);
    Lighting light2 = CalculateLighting(lights[1], fs_in.fragPos.xyz, fs_in.normals.xyz);
    Lighting light3 = CalculateLighting(lights[2], fs_in.fragPos.xyz, fs_in.normals.xyz);
    Lighting light4 = CalculateLighting(lights[3], fs_in.fragPos.xyz, fs_in.normals.xyz);

    vec3 totalDiffuse = light1.diffuse + light2.diffuse + light3.diffuse + light4.diffuse;
    vec3 totalSpecular = light1.specular + light2.specular + light3.specular + light4.specular;
    vec3 totalLight = ambient + totalDiffuse + totalSpecular;

    color = vec4(totalLight * texture(tex, fs_in.tc).rgb,1.0);
}

vec3 Diffuse(vec3 lightDir, vec3 surfaceNormal, vec3 light, vec3 reflectionConstant)
{
    float diff = max(dot(surfaceNormal,lightDir),0.0);
    return diff * light * reflectionConstant;
}

vec3 Specular(vec3 lightDir, vec3 surfaceNormal, vec3 fragWorldPos, float shininess, vec3 eyePosition, vec3 light, vec3 reflectionConstant)
{
    vec3 viewDir = normalize(eyePosition - fragWorldPos);
    vec3 reflectDir = reflect(-lightDir,surfaceNormal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess);

    return reflectionConstant * light * spec;
}

Lighting CalculateSpotLight(lightStruct light, vec3 fragWorldPos,vec3 fragToLightDir, vec3 normal)
{
    Lighting data;
    data.diffuse = vec3(0,0,0);
    data.specular = vec3(0,0,0);

    float theta = dot(-fragToLightDir, light.direction.xyz);
    float epsilon = (light.lightSpotCutOff - light.lightSpotOuterCutOff);
    float intensity = clamp((theta - light.lightSpotOuterCutOff) / epsilon, 0.0, 1.0);

    if(theta > light.lightSpotOuterCutOff){
        data.diffuse = Diffuse(fragToLightDir,normal,light.id.rgb, kd.rgb);
        data.specular = Specular(fragToLightDir, normal, fragWorldPos, shininess, viewPosition, light.is.rgb, ks.rgb);

        data.diffuse *= intensity;
        data.specular *= intensity;
    }

    return data;
}

Lighting CalculateLighting(lightStruct light, vec3 fragWorldPos, vec3 normal)
{
    Lighting data;
    data.diffuse = vec3(0,0,0);
    data.specular = vec3(0,0,0);

    if(light.on == 1)
    {
        vec3 fragToLight = light.lightPosition.xyz - fragWorldPos;
        vec3 fragToLightDir = normalize(fragToLight);

        float distance = length(fragToLight);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));

        if(light.type == 0) // Point
        {
            data.diffuse = Diffuse(fragToLightDir,normal,light.id.rgb, kd.rgb);
            data.specular = Specular(fragToLightDir, normal, fs_in.fragPos.xyz, shininess, viewPosition, light.is.rgb, ks.rgb);
        }
        else if(light.type == 1) // Spotlight
        {
            data = CalculateSpotLight(light, fragWorldPos, fragToLightDir, normal);
        }

        data.diffuse  *= attenuation;
        data.specular *= attenuation;
    }

    return data;
}
