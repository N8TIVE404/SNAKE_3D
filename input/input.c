/*
 * PROJECT: PRIMUM ENGINE
 * AUTHOR:  KEN KIKAYA
 *
 * This file contains functions that handle all the input from the keyboard and the mouse.
 *
 */

# include <glad/glad.h>
# include <cglm/cglm.h>
# include <stdbool.h>

# include "camera.h"
# include "input.h"

int width = 3840;
int height = 2160;

void process_input(GLFWwindow *window){
    Camera *cam = glfwGetWindowUserPointer(window);

    // Close window on ESC
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    // Get the speed of camera movement that is platform independent
    float velocity = cam -> speed * cam -> deltaTime;

    // Movement forward, towards the user
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        glm_vec3_muladds(cam -> front, velocity, cam -> position);
    }

    // Movement backwards, into the screen
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        glm_vec3_mulsubs(cam -> front, velocity, cam -> position);
    }

    // Movement to the left along -x axis
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        vec3 temp;
        glm_cross(cam -> front, cam -> up, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, velocity, cam -> position);
    }

    // Movement along the right towards +x axis
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        vec3 temp;
        glm_cross(cam -> up, cam -> front, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, velocity, cam -> position);
    }
}

void framebuffer_resize(GLFWwindow *window, int w, int h){
    if(!window) return;
    if(w == 0 || h == 0) return;
    // Update the width variable and height variable
    width = w;
    height = h;

    // Update the size of the viewport
    glViewport(0, 0, width, height);
}
