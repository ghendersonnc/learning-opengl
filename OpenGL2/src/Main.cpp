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
#include "Shaders.h"
#include "VBO.h"
#include "VAO.h"

// Some defs
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TARGET_FPS 60

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
        // Back face
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
     1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
     1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
     1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
    // Front face
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    // Left face
    -1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
    // Right face
     1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
    // Bottom face
    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
    // Top face
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f
    };

    VBO cubeVBO(GL_ARRAY_BUFFER, positions, 216 * sizeof(float), GL_STATIC_DRAW);
    VAO cubeVAO;
    cubeVAO.linkVBO(cubeVBO, 0, 3, 6, 0);
    cubeVAO.linkVBO(cubeVBO, 2, 3, 6, 3);
    cubeVAO.unbind();
    
    VAO lightVAO;
    lightVAO.linkVBO(cubeVBO, 0, 3, 6, 0);
    cubeVBO.unbind();
    lightVAO.unbind();

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
        0.0f, 0.0f, 1.0f, 1.0f,

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
        0.0f, 0.0f, 1.0f, 1.0f,

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

    VBO colorVBO(GL_ARRAY_BUFFER, colors, 156 * sizeof(float), GL_STATIC_DRAW);

    // Link colorVBO
    cubeVAO.bind();
    cubeVAO.linkVBO(colorVBO, 1, 4, 4, 0);
    colorVBO.unbind();
    cubeVAO.unbind();

    Shader cubeShader("resources/shaders/cubeShader.vert", "resources/shaders/cubeShader.frag");
    Shader lightShader("resources/shaders/lightShader.vert", "resources/shaders/lightShader.frag");
    cubeShader.use();
    lightShader.use();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    
    // Continuously run until window is closed
    double lastTime = glfwGetTime();
    glm::vec4 lightPos = glm::vec4(-1.0f, 1.0f, 0.0f, 1.5f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    bool r = true;
    while (!glfwWindowShouldClose(window)) {
        // color
        //glClearColor(0.20f, 0.91f, 0.91f, 1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*
        * 
        * Camera is moving side to side (instead of RGB cube being translated) with
        * light position being glued to the camera
        * 
        * Aware of how the world moves around the camera.
        * 
        */



        if (r) {
            cameraPosition += 0.05f * glm::normalize(glm::cross(cameraFront, cameraUp));
            lightPos += glm::vec4(0.05, 0.0f, 0.0f, 0.0f);
            if (cameraPosition.r >= 2)
                r = false;

        }
        else {
            cameraPosition -= 0.05f * glm::normalize(glm::cross(cameraFront, cameraUp));
            lightPos -= glm::vec4(0.05, 0.0f, 0.0f, 0.0f);
            if (cameraPosition.r <= -2)
                r = true;
        }

        {
            cubeShader.use();
            cubeShader.setVec3("lightColor", lightColor);
            cubeShader.setVec4("lightPos", lightPos);
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 0.0f));

            view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

            projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.f);

            cubeShader.setMat4("model", model);
            cubeShader.setMat4("view", view);
            cubeShader.setMat4("projection", projection);
            cubeVAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
            cubeVAO.unbind();
        }

        {
            lightShader.use();

            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            model = glm::translate(model, glm::vec3(lightPos));
            model = glm::scale(model, glm::vec3(0.2f));
            model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 1.0f, 0.0f));

            
            view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

            projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.f);
            lightShader.setMat4("model", model);
            lightShader.setMat4("view", view);
            lightShader.setMat4("projection", projection);
            lightVAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
       
        glfwPollEvents();

        // Rate limit to 60 FPS
        while (glfwGetTime() < lastTime + 1.0 / TARGET_FPS) {}
        lastTime += 1.0/ TARGET_FPS;

    }
    
    cubeVAO.destroy();
    cubeVBO.destroy();
    colorVBO.destroy();
    cubeShader.destroy();

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