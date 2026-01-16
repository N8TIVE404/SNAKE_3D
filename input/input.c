# include <glad/glad.h>
# include <stdbool.h>
# include <cglm/cglm.h>

# include "input.h"
# include "camera.h"

void process_kbinput(GLFWwindow *window){
    Camera *cam = glfwGetWindowUserPointer(window);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    float velocity = cam->speed * cam->deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glm_vec3_muladds(cam->front, velocity, cam->location);
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        glm_vec3_mulsubs(cam->front, velocity, cam->location);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        vec3 temp;
        glm_cross(cam->front, cam->up, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, velocity, cam->location);
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        vec3 temp;
        glm_cross(cam->up, cam->front, temp);
        glm_normalize(temp);
        glm_vec3_muladds(temp, velocity, cam->location);
    }
}
