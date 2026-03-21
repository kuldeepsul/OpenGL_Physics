#version 330

layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 norm;

uniform mat4 Perspective_mat;
uniform mat4 View_mat;
uniform mat4 Model_mat;

out vec3 Normal;
out vec3 Fragpos;

void main ()
{
    gl_Position =  Perspective_mat*View_mat*Model_mat*vec4(apos,1.0f);
    vec4 pos = Model_mat*vec4(apos,1.0f);

    Fragpos = (pos.xyz);
    mat3 normaltransform = inverse(transpose(mat3(Model_mat)));
    Normal = normaltransform * norm;
}
