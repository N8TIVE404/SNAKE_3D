#include <errno.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "shaders.h"

char *load_shader(const char *dir, const char *fileName) {
  char fullPath[200];
  memset(fullPath, 0, sizeof(fullPath));
  snprintf(fullPath, sizeof(fullPath), "%s/%s", dir, fileName);

  INFO_LOG("Loading shader from %s", fullPath);

  FILE *file = fopen(fullPath, "rb");
  if (!file) {
    WARNING_LOG("Failed to open %s !", fullPath);
    return NULL;
  }

  if (fseek(file, 0, SEEK_END)) {
    WARNING_LOG("Error while traversing file! (%s)", strerror(errno));
    return NULL;
  }

  long size = ftell(file);
  if (size <= 0) {
    WARNING_LOG("Error getting size of file! (%s)", strerror(errno));
    return NULL;
  }

  if (fseek(file, 0, SEEK_SET)) {
    WARNING_LOG("Error while resetting file pointer! (%s)", strerror(errno));
    return NULL;
  }

  char *text = malloc((size_t)size + 1);
  if (!text) {
    FATAL_LOG("Failed to allocate memory!");
    _exit(EXIT_FAILURE);
  }

  size_t read = fread(text, sizeof(char), size, file);
  if (read != (size_t)size) {
    WARNING_LOG("Failed to read entire stream!");
    return NULL;
  }

  text[size] = '\0';
  fclose(file);
  return text;
}

unsigned int create_program(const char *dir, const char *vertexName,
                            const char *fragmentName) {
  GLuint vertex, fragment, program;

  char infoLog[1024] = {0};
  int success = 0;

  char *vertexCode = load_shader(dir, vertexName);
  if (!vertexCode) {
    FATAL_LOG("Error reading vertex shader code!");
    _exit(EXIT_FAILURE);
  }

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, (const GLchar *const *)&vertexCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, sizeof(infoLog), NULL, infoLog);
    FATAL_LOG("Failed to compile vertex shader! (%s)", infoLog);
    _exit(EXIT_FAILURE);
  }

  free(vertexCode);

  char *fragmentCode = load_shader(dir, fragmentName);
  if (!fragmentCode) {
    FATAL_LOG("Error reading fragment shader code!");
    _exit(EXIT_FAILURE);
  }

  memset(infoLog, 0, sizeof(infoLog));
  success = 0;

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, (const GLchar *const *)&fragmentCode, NULL);
  glCompileShader(fragment);

  free(fragmentCode);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
    FATAL_LOG("Failed to compile fragment shader! (%s)", infoLog);
    _exit(EXIT_FAILURE);
  }

  INFO_LOG("Compiled vertex and fragment shaders.");

  memset(infoLog, 0, sizeof(infoLog));
  success = 0;

  program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
    FATAL_LOG("Program linking failed! (%s)", infoLog);
    _exit(EXIT_FAILURE);
  }

  glDetachShader(program, vertex);
  glDetachShader(program, fragment);

  return program;
}
