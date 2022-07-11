#include "oaOGL_Texture.h"
#include <freeimage\FreeImage.h>
#include<glad\glad.h>
#include <GLFW/glfw3.h>

namespace oaEngineSDK{

OGL_Texture::~OGL_Texture()
{
  glDeleteTextures(1,&id);
}
bool OGL_Texture::loadFromFile(const String& file)
{
  FIBITMAP* dib(0);
  uint32 width(0), height(0);
  FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
  BYTE* bits(0);

  fif = FreeImage_GetFileType(file.c_str(), 0);

  if (fif == FIF_UNKNOWN)
    fif = FreeImage_GetFIFFromFilename(file.c_str());

  if (fif == FIF_UNKNOWN)
    return false;

  if (FreeImage_FIFSupportsReading(fif)) {
    dib = FreeImage_Load(fif, file.c_str());

    dib = FreeImage_ConvertTo32Bits(dib);

  }

  if (!dib)
    return false;

  bits = FreeImage_GetBits(dib);
  width = FreeImage_GetWidth(dib);
  height = FreeImage_GetHeight(dib);

  if ((bits == 0) || (width == 0) || (height == 0))
    return false;

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
  FreeImage_Unload(dib);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  

  return true;
}


}
