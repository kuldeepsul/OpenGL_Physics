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

Mesh MeshGenerator::gencuboidmesh(float a ,float b , float c)
{

    float hx = a * 0.5f;
    float hy = b * 0.5f;
    float hz = c * 0.5f;

    std::vector<float> vertexData = {
        // FRONT (+Z)
        -hx, -hy,  hz,  0, 0, 1,
        hx, -hy,  hz,  0, 0, 1,
        hx,  hy,  hz,  0, 0, 1,

        hx,  hy,  hz,  0, 0, 1,
        -hx,  hy,  hz,  0, 0, 1,
        -hx, -hy,  hz,  0, 0, 1,

        // BACK (-Z)  ← flipped compared to yours
        hx, -hy, -hz,  0, 0,-1,
        -hx, -hy, -hz,  0, 0,-1,
        -hx,  hy, -hz,  0, 0,-1,

        -hx,  hy, -hz,  0, 0,-1,
        hx,  hy, -hz,  0, 0,-1,
        hx, -hy, -hz,  0, 0,-1,

        // LEFT (-X)
        -hx, -hy, -hz, -1, 0, 0,
        -hx, -hy,  hz, -1, 0, 0,
        -hx,  hy,  hz, -1, 0, 0,

        -hx,  hy,  hz, -1, 0, 0,
        -hx,  hy, -hz, -1, 0, 0,
        -hx, -hy, -hz, -1, 0, 0,

        // RIGHT (+X)
        hx, -hy,  hz,  1, 0, 0,
        hx, -hy, -hz,  1, 0, 0,
        hx,  hy, -hz,  1, 0, 0,

        hx,  hy, -hz,  1, 0, 0,
        hx,  hy,  hz,  1, 0, 0,
        hx, -hy,  hz,  1, 0, 0,

        // TOP (+Y)
        -hx,  hy,  hz,  0, 1, 0,
        hx,  hy,  hz,  0, 1, 0,
        hx,  hy, -hz,  0, 1, 0,

        hx,  hy, -hz,  0, 1, 0,
        -hx,  hy, -hz,  0, 1, 0,
        -hx,  hy,  hz,  0, 1, 0,

        // BOTTOM (-Y)
        -hx, -hy, -hz,  0,-1, 0,
        hx, -hy, -hz,  0,-1, 0,
        hx, -hy,  hz,  0,-1, 0,

        hx, -hy,  hz,  0,-1, 0,
        -hx, -hy,  hz,  0,-1, 0,
        -hx, -hy, -hz,  0,-1, 0
    };

    Mesh obj;
    obj.data =  vertexData;
    obj.vertexcount = 36;
    obj.genBufferObjects();

    return obj;

};

Mesh MeshGenerator::genplanemesh(float a , float b)
{
    float hx  = a * 0.5f;
    float hz  = b * 0.5f;

    std::vector<float> vertexData = {
        
        -hx, 0.0f, -hz,  0.0f,  1.0f,  0.0f,
        hx , 0.0f, -hz,  0.0f,  1.0f,  0.0f,
        hx , 0.0f,  hz,  0.0f,  1.0f,  0.0f,

        -hx, 0.0f, -hz,  0.0f,  1.0f,  0.0f,
         hx , 0.0f,  hz,  0.0f,  1.0f,  0.0f,
        -hx, 0.0f,  hz,  0.0f,  1.0f,  0.0f
    };

    Mesh obj;
    obj.data = vertexData;
    obj.vertexcount = 6 ;
    obj.genBufferObjects();

    return obj;
};

void Scene::newEntity(unsigned int id ,Mesh* mesh_data,glm::vec3 position_param)
{
    Entity* ent = new Entity(id);
    ent->mesh = mesh_data;

    ent->body = new RigidBody();
    // Default position at origin.
    ent->body->position = position_param;
    // Default colour white.
    ent->col = {1.0f, 1.0f, 1.0f};
    ent->translateEntity(ent->body->position);

    this->entities.push_back(ent);
};

void Entity::translateEntity(glm::vec3 disp)
{
    this->model_matrix =  glm::translate(this->model_matrix , disp);
};

void Entity::rotateEntity(float angle, glm::vec3 axis)
{
    this->model_matrix =  glm::rotate(this->model_matrix,angle,axis);
};

void Entity::scaleEntity(glm::vec3 axis)
{
    this->model_matrix =  glm::scale(this->model_matrix,axis);
};


void Entity::updatePosition(float timeincrement)
{
    this->body->position += timeincrement * this->body->velocity;
};
void Entity::updateModelMatrix()
{
    this->model_matrix = glm::translate(glm::mat4 (1.0f) ,this->body->position);
};
