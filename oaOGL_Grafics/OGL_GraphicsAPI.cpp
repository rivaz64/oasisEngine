#include "OGL_GraphicsAPI.h"
#include <iostream>

bool oaEngineSDK::OGL_GraphicsAPI::initialize()
{
  std::cout<<"openGL graphic API"<<std::endl;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(window);

  //glViewport(0, 0, 800, 600);
  return true;
}

bool oaEngineSDK::OGL_GraphicsAPI::isRunning()
{
  return !glfwWindowShouldClose(window);
}

void oaEngineSDK::OGL_GraphicsAPI::events()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

oaEngineSDK::OGL_GraphicsAPI::~OGL_GraphicsAPI()
{
  glfwTerminate();
}
