/*
 * Project: PRIMUM ENGINE
 * Author:  KEN KIKAYA
 *
 * The functions defined here handle all the window creation and termination logic. They also
 * set up the window and provide a ready to use pointer to a window instance. Further explanations
 * can be found below.
 *
 */

# include <stdlib.h>
# include <glad/glad.h>

# include "window.h"
# include "logger.h"
# include "input.h"

GLFWwindow *setup_window(const char *name){
    glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11); // More stable performance on X11
    glfwInit();

    // Set the OpenGL profile and version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if(!window){
        FATAL_LOG("Failed to create window!\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Tie the window created to the current OpenGL context
    glfwMakeContextCurrent(window);

    // Load Glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        FATAL_LOG("Failed to load GLAD!\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);    // For better handling of 3-D drawings on screen
    glDisable(GL_CULL_FACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glfwSwapInterval(0);    // Unleash full capabilities

    return window;
}

void terminate_window(GLFWwindow *window){
    glfwDestroyWindow(window);
    glfwTerminate();
}
