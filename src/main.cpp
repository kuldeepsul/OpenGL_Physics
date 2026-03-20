#include "default.h"
#include "shapes.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

int main()
{
    const char title [] = {"Trial"};   
    GLFWwindow* window;

    try
    {
        window = InitializeProject(1920,1080,title);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    glViewport(0,0,1920,1080);
    
    MeshGenerator MeshGen;
    Mesh m1 = MeshGen.gencuboidmesh();

    Entity cube(1);
    cube.mesh = &m1;
    
    std::string path_vert = "shader/Vertex_shader.glsl";
    std::string path_frag = "shader/Lighting_shader.glsl";

    unsigned int program = getShaderProgram(path_vert,path_frag);

    // perspective 
    glm::mat4 Presp = glm::perspective(glm::radians(90.0f), (1920.0f/1080.0f),0.1f,100.0f);
    unsigned int persloc = glGetUniformLocation(program,"Perspective_mat");
    glUniformMatrix4fv(persloc,1,GL_FALSE,glm::value_ptr(Presp));
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    FPSCamera cam;
    cam.campos = {0.0f, 0.0f, 0.0f};
    cam.camfront = {1.0f,1.0f,1.0f};
    cam.updateViewMatrix();

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        
        if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window,GLFW_TRUE);
        }

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        
        cam.processkeyboardinput( window);
        cam.processMouseInput(window);

        unsigned int viewloc = glGetUniformLocation(program,"View_mat");
        glUniformMatrix4fv(viewloc,1,GL_FALSE,glm::value_ptr(cam.viewmatrix));

        unsigned int lightposloc = glGetUniformLocation(program,"lightpos");
        glUniform3fv(lightposloc,1,glm::value_ptr(cam.campos));

        for (int i {0} ; i < 10 ; i ++)
        {
            glm::mat4 move = glm::mat4(1.0f);
            glm::mat4 rotate = glm::mat4(1.0f);
            glm::mat4 scale = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);

            glm::vec3 objcol = {0.7f,0.3f,0.2f};

            unsigned int objcolloc = glGetUniformLocation(program,"objcol");
            glUniform3fv(objcolloc,1,glm::value_ptr(glm::normalize(objcol)));

            move = glm::translate(move,cubePositions[i]);
            rotate = glm::rotate(move, glm::radians(20.0f), cubePositions[i]);
            scale = glm::scale(rotate,{3.0f,3.0f,3.0f});

            model = move * scale;

            unsigned int modelloc = glGetUniformLocation(program,"Model_mat");
            glUniformMatrix4fv(modelloc,1,GL_FALSE,glm::value_ptr(model));

            glBindVertexArray(cube.mesh->VAO);
            glDrawArrays(GL_TRIANGLES,0,36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    
}