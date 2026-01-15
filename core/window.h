# ifndef WINDOW_H
# define WINDOW_H

# include <GLFW/glfw3.h>

extern int width;
extern int height;

GLFWwindow *setup_window(const char*);
void destroy_window(GLFWwindow*);

# endif
