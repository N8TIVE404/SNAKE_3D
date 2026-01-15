/*
 * Project: PRIMUM ENGINE
 * Author:  KEN KIKAYA
 *
 * This file defines a function for loading a texture and provides the user with a valid texture ID
 * to be used upon activation.
 * The function will provide a valid texture even if loading the texture fails. The function provides
 * a fallback texture to be used but reports the failure to load.
 *
 */

# include <glad/glad.h>

# include "textures.h"
# include "logger.h"

# define STB_IMAGE_IMPLEMENTATION
# include <stb_image.h>

unsigned int load_texture(const char *directory, const char *path){
    char filename[200];
    snprintf(filename, sizeof(filename), "%s/%s", directory, path);

    // Replace backslashes with forward slashes for Linux/macOS
    for(int i = 0; filename[i] != '\0'; i++) {
        if(filename[i] == '\\') filename[i] = '/';
    }

    int numChannels, imgWidth, imgHeight;

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    unsigned char *data = stbi_load(filename, &imgWidth, &imgHeight, &numChannels, 0);
    if(!data){
        ERROR_LOG("Failed to load texture from path %s. Reason: %s!\n", path, stbi_failure_reason());
        unsigned char fallback[3] = {255, 0, 255};
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, fallback);
        return textureID;
    }

    GLenum target = numChannels == 4 ? GL_RGBA : GL_RGB;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, target, imgWidth, imgHeight, 0, target, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

    INFO_LOG("Textures loaded successfully from %s.", filename);
    stbi_image_free(data);

    return textureID;
}

unsigned int load_cubemap(const char *fullPath){
    char path[100];
    snprintf(path, sizeof(path), "%s", fullPath);
    for(int i = 0; i < sizeof(path); i++){
        if(path[i] == '\\') path[i] = '/';
    }

    const char *skyboxFaces[6] = {
        "px.png", "nx.png", "py.png", "ny.png", "pz.png", "nz.png"
    };

    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int imgWidth, imgHeight, channels;

    for(int i = 0; i < 6; i++){
        char imgPath[100] = {0};
        snprintf(imgPath, sizeof(imgPath), "%s/%s", path, skyboxFaces[i]);
        unsigned char *data = stbi_load(imgPath, &imgWidth, &imgHeight, &channels, 0);
        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;

        if(!data){
            ERROR_LOG("Failed to load textures from %s. Reason: %s", path, stbi_failure_reason());
            INFO_LOG("Using fallback texture");
            unsigned char fallback[3] = {255, 0, 255};
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 1, 1, 0, GL_RGB, 0, format, GL_UNSIGNED_BYTE, fallback);
            stbi_image_free(data);
        } else{
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
