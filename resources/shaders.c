/*
 * Project: PRIMUM ENGINE
 * Author:  KEN KIKAYA
 *
 * This file defines a function to load a shader, fragment and vertex from a file and make a valid
 * shader program that is ready to be used after activation.
 *
 */

# include <glad/glad.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

# include "shaders.h"
# include "logger.h"

ShaderText load_shader(const char *filePath){
    ShaderText text  = {.data = NULL, .size = 0};
    
    // Open the file and get the size of the file
    FILE *file = fopen(filePath, "rb");
    if(!file){
        ERROR_LOG("fopen() failed with %s!", strerror(errno));
        return text;
    }

    if(fseek(file, 0, SEEK_END)){
        ERROR_LOG("fseek() failed with %s", strerror(errno));
        fclose(file);
        return text;
    }

    long size = ftell(file);
    if(size <= 0){
        ERROR_LOG("ftell() failed with %s", strerror(errno));
        fclose(file);
        return text;
    }

    if(fseek(file, 0, SEEK_SET)){
        ERROR_LOG("fseek() failed with %s", strerror(errno));
        fclose(file);
        return text;
    }

    // Allocate memory and read the contents of the file
    unsigned char *ptr = malloc((size_t)size + 1);
    if(!ptr){
        ERROR_LOG("malloc() failed with %s", strerror(errno));
        fclose(file);
        return text;
    }

    size_t read = fread(ptr, sizeof(char), size, file);
    if(!read || read != (size_t)size){
        ERROR_LOG("fread() failed with %s", strerror(errno));
        free(ptr);
        fclose(file);
        return text;
    }
    ptr[size] = '\0';

    text.data = ptr;
    text.size = size;
    fclose(file);

    return text;
}

GLuint shader_program(const char *vertexPath, const char *fragmentPath){
    ShaderText vertexSource, fragmentSource;
    vertexSource = load_shader(vertexPath);
    if(!vertexSource.data){
        ERROR_LOG("load_shader() failed for vertex shader");
        return -1;
    }

    fragmentSource = load_shader(fragmentPath);
    if(!fragmentSource.data){
        ERROR_LOG("load_shader() failed for fragment shader");
        free(vertexSource.data);
        return -1;
    }

    int success = 0;
    char infoLog[512] = {0};

    GLuint v, f;
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v, 1, (const GLchar *const *)&vertexSource.data, NULL);
    glShaderSource(f, 1, (const GLchar *const *)&fragmentSource.data, NULL);

    glCompileShader(v);
    glGetShaderiv(v, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(v, 512, NULL, infoLog);
        FATAL_LOG("Vertex shader compilation failed: (%s)\n", infoLog);
        exit(EXIT_FAILURE);
    }

    glCompileShader(f);
    success = 0; memset(infoLog, 0, sizeof(infoLog));
    glGetShaderiv(f, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(f, 512, NULL, infoLog);
        FATAL_LOG("Fragment shader compilation failed: (%s)\n", infoLog);
        exit(EXIT_FAILURE);
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, v);
    glAttachShader(shaderProgram, f);
    glLinkProgram(shaderProgram);

    success = 0; memset(infoLog, 0, sizeof(infoLog));
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        FATAL_LOG("Program linking failed: (%s)\n", infoLog);
        exit(EXIT_FAILURE);
    }

    glDeleteShader(v);
    glDeleteShader(f);

    free(vertexSource.data);
    free(fragmentSource.data);

    return shaderProgram;
}
