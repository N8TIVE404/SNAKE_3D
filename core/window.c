# include <glad/glad.h>
# include <stdlib.h>

# include "window.h"
# include "logger.h"

int width = 2160;
int height = 1080;

GLFWwindow *setup_window(const char *name){
    glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

    INFO_LOG("INITIALIZING GLFW...");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    INFO_LOG("CREATING WINDOW...");
    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if(!window){
        FATAL_LOG("FAILED TO CREATE WINDOW!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    INFO_LOG("WINDOW CREATED SUCCESSFULLY");
    INFO_LOG("LOADING GLAD...");
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        FATAL_LOG("FAILED TO LOAD GLAD!");
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    INFO_LOG("GLAD LOADED SUCCESSFULLY");
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    return window;
}

void destroy_window(GLFWwindow *window){
    INFO_LOG("DESTROYING WINDOW...");
    glfwDestroyWindow(window);
    INFO_LOG("WINDOW DESTROYED SUCCESSFULLY");
    glfwTerminate();
    INFO_LOG("TERMINATED GLFW SUCCESSFULLY");
}
