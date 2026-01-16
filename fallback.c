# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include "logger.h"
# include "primitives.h"
# include "shaders.h"


int
main(void){
    Sphere s = generate_sphere(160, 80);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(900, 600, "WINDOW", NULL, NULL);
    
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        FATAL_LOG("Failed to load GLAD");
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, 900, 600);

    GLint shader = shader_program("../assets/shaders/fallback.vert", "../assets/shaders/fallback.frag");

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, s.vertexCount * sizeof(VertexEntry), s.vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s.indexCount, s.indices, GL_STATIC_DRAW);

    glUseProgram(shader);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, s.indexCount, GL_UNSIGNED_INT, (void *)0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}
