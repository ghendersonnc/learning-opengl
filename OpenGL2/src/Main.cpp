// yeah
#include <iostream>
#include <Windows.h>


// Dependencies
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Self made headers 
#include "Shaders/Shaders.h"

using std::cout;
using std::cerr;
using std::endl;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;


    window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    

    // BEGIN OPENGL CODE

    glewInit();

    if (glewInit() != GLEW_OK) {
        return -1;
    }



    // Print out version of OpenGL (Also shows GPU Driver Version)
    cout << glGetString(GL_VERSION) << endl;;

    float positions[] = {
        // X Y Z coordinates    R G B A
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  // bottom left
    };

    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 21 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Let the GPU know to use the attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0);

    glEnableVertexAttribArray(1); // Let the GPU know to use the attribute array
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float)));

    std::string vertexShaderSrc = readShaderFile("resources/shaders/vertexShader.vert");
    std::string fragmentShaderSrc = readShaderFile("resources/shaders/fragmentShader.frag");
    unsigned int shaderProgram = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);
    glUseProgram(shaderProgram);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind

    int something = 0;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glfwSetKeyCallback(window, keyCallback);
    // Continuously run until window is closed
    while (!glfwWindowShouldClose(window)) {
        // color
        glClearColor(0.22f, 0.35f, 0.45f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);


        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        unsigned int transLocation = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        
        //glfwSwapInterval(1);
        glfwPollEvents();
    }
    
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) exit(0);
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        int* polyMode = (int*)malloc(2 * sizeof(int));
        glGetIntegerv(GL_POLYGON_MODE, polyMode);

        if (polyMode) {
            if (*polyMode == GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            free(polyMode);
        }
    }
}