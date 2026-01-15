# include <glad/glad.h>

# include "window.h"
# include "shaders.h"
# include "render.h"
# include "models.h"
# include "camera.h"

int
main(void){
    GLFWwindow *window = setup_window("SNAKE HAVEN");
    Camera cam = initialize_camera(60.0f);
    glfwSetWindowUserPointer(window, &cam);

    Mesh sphere = sphere_mesh(160, 80, "8k_sun.jpg");
    Position pos1 = {.scale = {0.5f, 0.5f, 0.5f}, .axis = {1.0f, 0.0f, 1.0f}, .location = {0.0f, 0.0f, 0.0f}};
    GLuint shader = shader_program("../assets/shaders/shader.vert", "../assets/shaders/shader.frag");

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.6f, 0.2f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        
        draw_mesh(&cam, &pos1, &sphere, shader);
      
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    destroy_window(window);

    return 0;
}
