#version 330 core

in vec3 Normal;
in vec3 Fragpos; 
out vec4 Frag_Color;

uniform vec3 lightpos;
uniform vec3 objcol;


void main ()
{
    

    float amb = 0.2f ;
    vec3 norm =  normalize(Normal);
    vec3 lightdir = normalize(lightpos - Fragpos);

    float diff = max(dot(norm,lightdir),0.0f);

    vec3 lightcol = vec3 (1.0f,1.0f,1.0f);
    vec3 diffuse = diff * lightcol;
    vec3 ambient  = amb * lightcol;

    vec3 factor  = (ambient + diff) ;

    vec3 col = objcol * factor ; 
    Frag_Color = vec4(col,1.0f);
}