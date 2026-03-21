#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <cmath>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


class Mesh
{
    public:
    std::vector <float> data ;
    unsigned int vertexcount;
    unsigned int VBO;
    unsigned int VAO;

    void genBufferObjects();
};

class MeshGenerator
{
    public:
    Mesh gencuboidmesh(float a , float b , float c);
    Mesh genplanemesh(float a , float b);
};

struct RigidBody
{
    // Physics Parameters
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
};

class Entity
{
    public:
    const unsigned int id;

    // Rendering Parameters
    glm::vec3 col;
    glm::mat4 model_matrix = glm::mat4 (1.0f);
    Mesh* mesh;
    RigidBody* body;



    Entity() = delete ;
    Entity(unsigned int i) : id(i) {} ;

    void translateEntity(glm::vec3 disp);
    void rotateEntity(float angle, glm::vec3 axis);
    void scaleEntity(glm::vec3 axis);

    void updatePosition(float timeincrement);
    void updateModelMatrix();

};

class Scene
{
    public:
    std::vector <Entity*> entities;

    void newEntity(unsigned int id ,Mesh* mesh_data,glm::vec3 position_param);

};





