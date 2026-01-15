# include <glad/glad.h>
# include <stdbool.h>

# include "input.h"
# include "camera.h"

void process_kbinput(GLFWwindow *window){
    Camera *cam = glfwGetWindowUserPointer(window);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    float velocity;
    cam->speed = 2.5 * cam->deltaTime;
}
