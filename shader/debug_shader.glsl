#version 330 core

in vec3 Normal;
in vec3 Fragpos; 
out vec4 Frag_Color;

uniform vec3 lightpos;
uniform vec3 objcol;


void main ()
{
    
    Frag_Color = vec4(Fragpos,1.0f);
}