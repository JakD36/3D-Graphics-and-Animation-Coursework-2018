#version 410 core

out vec4 color;

in VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} fs_in;


uniform sampler2D tex;
uniform sampler2D normal;

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
uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

uniform vec4 ia;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float shininess;

void main(void)
{
    vec3 ambient = ka.r * ia.rgb;

    vec3 totalDiffuse = vec3(0,0,0);
    vec3 totalSpecular = vec3(0,0,0);

    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);

    vec3 normalsTex = texture(normal,fs_in.tc).rgb;
    vec3 normals = normalize(normalsTex * 2.0 - 1.0);


    if(lights[0].on == 1)
    {
        vec4 lightDir = normalize(vec4(lights[0].lightPosition.xyz,1) - fs_in.fragPos);
        float diff = max(dot(normalize(normals),lightDir.rgb),0.0); // calculate the angle between the normal for that fragment and direction to the light,

        float distance = length(lights[0].lightPosition - fs_in.fragPos);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));

        vec3 viewDir = normalize(viewPosition - fs_in.fragPos.xyz); // find the direction from the position of the fragment in the world space to the camera
        vec3 reflectDir = reflect(-lightDir.xyz,normalize(normals.xyz)); // find the direction that the light ideally reflects along
        float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess); // find the angle between these two vectors using dot product

        if(lights[0].type == 0){ // if point light, remember we have two types of light, point and spotlight in this project
            // if its a point light its pretty simple just calculate the diffuse and specular components using their equations
            // with the id,is of that specific light source and the kd,ks of the material of the model
            diffuse = diff * lights[0].id.rgb * kd.rgb;
            specular = ks.rgb * lights[0].is.rgb * spec;
        }
        else if(lights[0].type == 1){ // if spotlight
            //Spotlight
            // we need to calculate the angle between the direction of the light to the fragment and the direction of the light
            float theta = dot(lightDir, normalize(-vec4(lights[0].direction.xyz,1)));

            // we can then calculate the intensity of the light if the angle is greater than the angle of cut off for the spotlight
            float epsilon = (lights[0].lightSpotCutOff - lights[0].lightSpotOuterCutOff);
            float intensity = clamp((theta - lights[0].lightSpotOuterCutOff) / epsilon, 0.0, 1.0);

            if(theta > lights[0].lightSpotOuterCutOff){ // calculate light ...
                diffuse = diff * lights[0].id.rgb * kd.rgb;     // same as before
                specular = ks.rgb * lights[0].is.rgb * spec;
                diffuse *= intensity; // now we can multiply our diffuse and specular by the intensity to have the light gradually fade the greater the angle
                specular *= intensity;
            }
        }

        diffuse  *= attenuation;
        specular *= attenuation;

        totalDiffuse += diffuse;
        totalSpecular += specular;
    }

    if(lights[1].on == 1)
    {
        vec4 lightDir = normalize(vec4(lights[1].lightPosition.xyz,1) - fs_in.fragPos);
        float diff = max(dot(normalize(normals),lightDir.rgb),0.0); // calculate the angle between the normal for that fragment and direction to the light,

        float distance = length(lights[1].lightPosition - fs_in.fragPos);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));

        vec3 viewDir = normalize(viewPosition - fs_in.fragPos.xyz); // find the direction from the position of the fragment in the world space to the camera
        vec3 reflectDir = reflect(-lightDir.xyz,normalize(normals.xyz)); // find the direction that the light ideally reflects along
        float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess); // find the angle between these two vectors using dot product

        if(lights[1].type == 0){ // if point light, remember we have two types of light, point and spotlight in this project
            // if its a point light its pretty simple just calculate the diffuse and specular components using their equations
            // with the id,is of that specific light source and the kd,ks of the material of the model
            diffuse = diff * lights[1].id.rgb * kd.rgb;
            specular = ks.rgb * lights[1].is.rgb * spec;
        }
        else if(lights[1].type == 1){ // if spotlight
            //Spotlight
            // we need to calculate the angle between the direction of the light to the fragment and the direction of the light
            float theta = dot(lightDir, normalize(-vec4(lights[1].direction.xyz,1)));

            // we can then calculate the intensity of the light if the angle is greater than the angle of cut off for the spotlight
            float epsilon = (lights[1].lightSpotCutOff - lights[1].lightSpotOuterCutOff);
            float intensity = clamp((theta - lights[1].lightSpotOuterCutOff) / epsilon, 0.0, 1.0);

            if(theta > lights[1].lightSpotOuterCutOff){ // calculate light ...
                diffuse = diff * lights[1].id.rgb * kd.rgb;     // same as before
                specular = ks.rgb * lights[1].is.rgb * spec;
                diffuse *= intensity; // now we can multiply our diffuse and specular by the intensity to have the light gradually fade the greater the angle
                specular *= intensity;
            }
        }
        diffuse  *= attenuation;
        specular *= attenuation;

        totalDiffuse += diffuse;
        totalSpecular += specular;
    }

    if(lights[2].on == 1)
    {
        vec3 lightDir = normalize(lights[2].lightPosition.xyz - fs_in.fragPos.xyz);
        float diff = max(dot(normalize(normals.xyz),lightDir.rgb),0.0); // calculate the angle between the normal for that fragment and direction to the light,

        float distance = length(lights[2].lightPosition.xyz - fs_in.fragPos.xyz);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));

        vec3 viewDir = normalize(viewPosition.xyz - fs_in.fragPos.xyz); // find the direction from the position of the fragment in the world space to the camera
        vec3 reflectDir = reflect(-lightDir,normalize(normals.xyz)); // find the direction that the light ideally reflects along
        float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess); // find the angle between these two vectors using dot product

        if(lights[2].type == 0){ // if point light, remember we have two types of light, point and spotlight in this project
            // if its a point light its pretty simple just calculate the diffuse and specular components using their equations
            // with the id,is of that specific light source and the kd,ks of the material of the model
            diffuse = diff * lights[2].id.rgb * kd.rgb;
            specular = ks.rgb * lights[2].is.rgb * spec;
        }
        else if(lights[2].type == 1){ // if spotlight
            //Spotlight
            // we need to calculate the angle between the direction of the light to the fragment and the direction of the light
            float theta = dot(lightDir, normalize(-lights[2].direction.xyz));

            // we can then calculate the intensity of the light if the angle is greater than the angle of cut off for the spotlight
            float epsilon = (lights[2].lightSpotCutOff - lights[2].lightSpotOuterCutOff); // Want a negative value
            float intensity = clamp((theta - lights[2].lightSpotOuterCutOff) / epsilon, 0.0, 1.0);

            if(theta > lights[2].lightSpotOuterCutOff){ // calculate light ...
                diffuse = diff * lights[2].id.rgb * kd.rgb;     // same as before
                specular = ks.rgb * lights[2].is.rgb * spec;
                diffuse *= intensity; // now we can multiply our diffuse and specular by the intensity to have the light gradually fade the greater the angle
                specular *= intensity;
            }
        }

        diffuse  *= attenuation;
        specular *= attenuation;

        totalDiffuse += diffuse;
        totalSpecular += specular;
    }

    if(lights[3].on == 1)
    {
        vec3 lightDir = normalize(lights[3].lightPosition.xyz - fs_in.fragPos.xyz);
        float diff = max(dot(normalize(normals.xyz),lightDir),0.0); // calculate the angle between the normal for that fragment and direction to the light,

        float distance = length(lights[3].lightPosition.xyz - fs_in.fragPos.xyz);
        float attenuation = 1.0f / (lightConstant + lightLinear * distance + lightQuadratic * (distance*distance));

        vec3 viewDir = normalize(viewPosition.xyz - fs_in.fragPos.xyz); // find the direction from the position of the fragment in the world space to the camera
        vec3 reflectDir = reflect(-lightDir,normalize(normals.xyz)); // find the direction that the light ideally reflects along
        float spec = pow(max(dot(viewDir,reflectDir),0.0),shininess); // find the angle between these two vectors using dot product

        if(lights[3].type == 0){ // if point light, remember we have two types of light, point and spotlight in this project
            // if its a point light its pretty simple just calculate the diffuse and specular components using their equations
            // with the id,is of that specific light source and the kd,ks of the material of the model
            diffuse = diff * lights[3].id.rgb * kd.rgb;
            specular = ks.rgb * lights[3].is.rgb * spec;
        }
        else if(lights[3].type == 1){ // if spotlight
            //Spotlight
            // we need to calculate the angle between the direction of the light to the fragment and the direction of the light
            float theta = dot(lightDir, normalize(-lights[3].direction.xyz));

            // we can then calculate the intensity of the light if the angle is greater than the angle of cut off for the spotlight
            float epsilon = (lights[3].lightSpotCutOff - lights[3].lightSpotOuterCutOff); // Want a negative value
            float intensity = clamp((theta - lights[3].lightSpotOuterCutOff) / epsilon, 0.0, 1.0);

            if(theta > lights[3].lightSpotOuterCutOff){ // calculate light ...

                diffuse = diff * lights[3].id.rgb * kd.rgb;     // same as before
                specular = ks.rgb * lights[3].is.rgb * spec;
                diffuse *= intensity; // now we can multiply our diffuse and specular by the intensity to have the light gradually fade the greater the angle
                specular *= intensity;
            }
        }

        diffuse  *= attenuation;
        specular *= attenuation;

        totalDiffuse += diffuse;
        totalSpecular += specular;
    }

    color = vec4((ambient+totalDiffuse+totalSpecular) * texture(tex,fs_in.tc).rgb,1.0);
}