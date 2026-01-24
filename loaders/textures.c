#include <glad/glad.h>

#include "logger.h"
#include "stb_image.h"
#include "textures.h"

Texture load_texture(const char *directory, const char *file) {
  Texture tex;
  char fullPath[200] = {0};
  snprintf(fullPath, sizeof(fullPath), "%s/%s", directory, file);

  INFO_LOG("Loading textures from %s", fullPath);
  int w, h, channels;
  unsigned char *data = stbi_load(fullPath, &w, &h, &channels, 0);
  if (!data) {
    FATAL_LOG("Failed to load textures from %s", fullPath);
    tex.textureID = -1;
    return tex;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  GLenum format = channels == 4 ? GL_RGBA : GL_RGB;

  glGenTextures(1, &tex.textureID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex.textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE,
               data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  return tex;
}

Texture load_cubemap(const char *fullPath) {
  const char *skyboxFaces[6] = {"px.png", "nx.png", "py.png",
                                "ny.png", "pz.png", "nz.png"};

  GLuint textureID;
  glGenTextures(1, &textureID);
  glActiveTexture(GL_TEXTURE10);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  int imgWidth, imgHeight, channels;

  for (int i = 0; i < 6; i++) {
    char imgPath[100] = {0};
    snprintf(imgPath, sizeof(imgPath), "%s/%s", fullPath, skyboxFaces[i]);
    unsigned char *data =
        stbi_load(imgPath, &imgWidth, &imgHeight, &channels, 0);
    GLenum format = channels == 4 ? GL_RGBA : GL_RGB;

    if (!data) {
      WARNING_LOG("Failed to load textures from %s. Reason: %s", imgPath,
                  stbi_failure_reason());
    } else {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, imgWidth,
                   imgHeight, 0, format, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    }
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  Texture tex;
  tex.textureID = textureID;
  return tex;
}
