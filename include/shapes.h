#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cmath>
#include <glm/glm/glm.hpp>


class Mesh
{
    public:
    std::vector <float> data ;
    unsigned int VBO;
    unsigned int VAO;

    void genBufferObjects();
};

class MeshGenerator
{
    public:
    Mesh gencuboidmesh();
    //Mesh loadmesh();
};

class Entity
{
    public:
    const unsigned int id;

    glm::mat4 transform;
    Mesh* mesh;
    

    Entity() = delete ;
    Entity(unsigned int i) : id(i) {} ;

};



