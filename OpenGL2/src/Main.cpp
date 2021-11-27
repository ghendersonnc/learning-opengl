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
#include "VBO/VBO.h"

// Some defs
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

using std::cout;
using std::cerr;
using std::endl;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    // BEGIN OPENGL CODE
    glewInit();

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    // Print out version of OpenGL (Also shows GPU Driver Version)
    cout << glGetString(GL_VERSION) << endl;;

    float positions[] = {
        // X Y Z coordinates
        // FRONT face
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        // BACK face
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,


        // RIGHT face
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,

        // LEFT face
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    VBO triangleVBO(GL_ARRAY_BUFFER, positions, 36 * sizeof(float), GL_STATIC_DRAW);
    
    // Link triangleVBO
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); // Let the GPU know to use the attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

    triangleVBO.unbind();
    glBindVertexArray(0);

    float colors[] = {
        // RGBA
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };


    VBO colorVBO(GL_ARRAY_BUFFER, colors, 48 * sizeof(float), GL_STATIC_DRAW);

    // Link colorVBO
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(1); // Let the GPU know to use the attribute array
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)0);

    colorVBO.unbind();
    glBindVertexArray(0);

    Shader shaderProgram("resources/shaders/vertexShader.vert", "resources/shaders/fragmentShader.frag");
    shaderProgram.use();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    
    // Continuously run until window is closed
    float rotDeg = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        // color
        glClearColor(0.22f, 0.35f, 0.45f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(VAO);
    
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        model = glm::rotate(model, glm::radians(rotDeg), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.f);
        shaderProgram.setMat4Uniform("model", model);
        shaderProgram.setMat4Uniform("view", view);
        shaderProgram.setMat4Uniform("projection", projection);
        rotDeg = rotDeg + 1.0f;
        colorVBO.bind();
        colors[0] = sin(glfwGetTime());
        colors[5] = sin(glfwGetTime() + 1);
        colors[10] = sin(glfwGetTime() + 2);

        colors[12] = sin(glfwGetTime() + 3);
        colors[17] = sin(glfwGetTime() + 4);
        colors[22] = sin(glfwGetTime() + 5);

        colors[24] = sin(glfwGetTime() + 6);
        colors[29] = sin(glfwGetTime() + 7);
        colors[34] = sin(glfwGetTime() + 8);

        colors[36] = sin(glfwGetTime() + 9);
        colors[41] = sin(glfwGetTime() + 10);
        colors[46] = sin(glfwGetTime() + 11);
     
        colorVBO.update(48 * sizeof(float), colors);
        colorVBO.unbind();


        glDrawArrays(GL_TRIANGLES, 0, 12);

        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    triangleVBO.destroy();
    colorVBO.destroy();
    shaderProgram.destroy();

    glfwTerminate();
    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) exit(0);
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {

        /*
        This block took a bit of trial and error to figure out as the docs do not talk
        much about GL_POLYGON_MODE being used with glGet*.

        After searching it seems I had to have passed in a buffer of 2 integers.
        This is why I am using dynamic memory allocation
        */

        int* polyMode = (int*)malloc(2 * sizeof(int));
        glGetIntegerv(GL_POLYGON_MODE, polyMode);

        if (polyMode) {
            if (*polyMode == GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            free(polyMode);
        }
        else {
            free(polyMode);
        }
    }
}