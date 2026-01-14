# ifndef INPUT_H
# define INPUT_H

# include <GLFW/glfw3.h>

extern int width;
extern int height;

void process_input(GLFWwindow*);
void framebuffer_resize(GLFWwindow*, int, int);

# endif
