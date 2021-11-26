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
    glfwSetKeyCallback(window, keyCallback);

    // BEGIN OPENGL CODE
    glewInit();

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    // Print out version of OpenGL (Also shows GPU Driver Version)
    cout << glGetString(GL_VERSION) << endl;;

    float positions[] = {
        // X Y Z coordinates    R G B A
         0.5f, -0.5f, 0.0f,    // bottom right
         0.0f,  0.5f, 0.0f,   // top
        -0.5f, -0.5f, 0.0f   // bottom left
    };

    unsigned int triangleVBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Let the GPU know to use the attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    float colors[] = {
        // RGBA
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };

    unsigned int colorVBO;
    glGenBuffers(1, &colorVBO);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colors, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1); // Let the GPU know to use the attribute array
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Shader shaderProgram("resources/shaders/vertexShader.vert", "resources/shaders/fragmentShader.frag");
    shaderProgram.use();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Continuously run until window is closed
    while (!glfwWindowShouldClose(window)) {
        // color
        glClearColor(0.22f, 0.35f, 0.45f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Devour the whole triangle with red!!
        if (colors[0] < 1.0f) {
            glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

            // better way to do this?
            colors[0] = colors[0] + 0.01f;
            colors[4] = colors[4] + 0.01f;
            colors[8] = colors[8] + 0.01f;
            colors[5] = colors[5] - 0.01f;
            colors[10] = colors[10] - 0.01f;
            glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), colors, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwSwapInterval(2);
        glfwPollEvents();
    }
    
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