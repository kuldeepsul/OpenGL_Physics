#include "shapes.h"
#define PI 3.14159265358979323846


void Mesh::genBufferObjects()
{
    // generate
    glGenVertexArrays(1,&this->VAO);
    glGenBuffers(1,&this->VBO);
    
    // bind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    
    // specify attributes
    glBufferData(GL_ARRAY_BUFFER,this->data.size() * sizeof(float), this->data.data(),GL_STATIC_DRAW);
    

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(0*sizeof(float)));
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
};

Mesh MeshGenerator::gencuboidmesh()
{

    std::vector <float> vertexData = {
        // Position (x, y, z)            // Normals (nx, ny, nz)
        // Front face (z = 0.25)
        -0.25f, -0.25f,  0.25f,  0.0f,  0.0f,  1.0f,
        0.25f, -0.25f,  0.25f,  0.0f,  0.0f,  1.0f,
        0.25f,  0.25f,  0.25f,  0.0f,  0.0f,  1.0f,
        0.25f,  0.25f,  0.25f,  0.0f,  0.0f,  1.0f,
        -0.25f,  0.25f,  0.25f,  0.0f,  0.0f,  1.0f,
        -0.25f, -0.25f,  0.25f,  0.0f,  0.0f,  1.0f,

        // Back face (z = -0.25)
        -0.25f, -0.25f, -0.25f,  0.0f,  0.0f, -1.0f,
        -0.25f,  0.25f, -0.25f,  0.0f,  0.0f, -1.0f,
        0.25f,  0.25f, -0.25f,  0.0f,  0.0f, -1.0f,
        0.25f,  0.25f, -0.25f,  0.0f,  0.0f, -1.0f,
        0.25f, -0.25f, -0.25f,  0.0f,  0.0f, -1.0f,
        -0.25f, -0.25f, -0.25f,  0.0f,  0.0f, -1.0f,

        // Left face (x = -0.25)
        -0.25f,  0.25f,  0.25f, -1.0f,  0.0f,  0.0f,
        -0.25f,  0.25f, -0.25f, -1.0f,  0.0f,  0.0f,
        -0.25f, -0.25f, -0.25f, -1.0f,  0.0f,  0.0f,
        -0.25f, -0.25f, -0.25f, -1.0f,  0.0f,  0.0f,
        -0.25f, -0.25f,  0.25f, -1.0f,  0.0f,  0.0f,
        -0.25f,  0.25f,  0.25f, -1.0f,  0.0f,  0.0f,

        // Right face (x = 0.25)
        0.25f,  0.25f,  0.25f,  1.0f,  0.0f,  0.0f,
        0.25f, -0.25f,  0.25f,  1.0f,  0.0f,  0.0f,
        0.25f, -0.25f, -0.25f,  1.0f,  0.0f,  0.0f,
        0.25f, -0.25f, -0.25f,  1.0f,  0.0f,  0.0f,
        0.25f,  0.25f, -0.25f,  1.0f,  0.0f,  0.0f,
        0.25f,  0.25f,  0.25f,  1.0f,  0.0f,  0.0f,

        // Top face (y = 0.25)
        -0.25f,  0.25f, -0.25f,  0.0f,  1.0f,  0.0f,
        -0.25f,  0.25f,  0.25f,  0.0f,  1.0f,  0.0f,
        0.25f,  0.25f,  0.25f,  0.0f,  1.0f,  0.0f,
        0.25f,  0.25f,  0.25f,  0.0f,  1.0f,  0.0f,
        0.25f,  0.25f, -0.25f,  0.0f,  1.0f,  0.0f,
        -0.25f,  0.25f, -0.25f,  0.0f,  1.0f,  0.0f,

        // Bottom face (y = -0.25)
        -0.25f, -0.25f, -0.25f,  0.0f, -1.0f,  0.0f,
        0.25f, -0.25f, -0.25f,  0.0f, -1.0f,  0.0f,
        0.25f, -0.25f,  0.25f,  0.0f, -1.0f,  0.0f,
        0.25f, -0.25f,  0.25f,  0.0f, -1.0f,  0.0f,
        -0.25f, -0.25f,  0.25f,  0.0f, -1.0f,  0.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, -1.0f,  0.0f
    }; 

    Mesh obj;
    obj.data =  vertexData;
    obj.genBufferObjects();

    return obj;

};

