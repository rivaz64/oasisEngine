#include "oaOGL_GraphicsAPI.h"
#include "oaOGL_VertexShader.h"
#include "oaOGL_PixelShader.h"
#include <iostream>

namespace oaEngineSDK{

bool 
OGL_GraphicsAPI::initialize()
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

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }    

  //glViewport(0, 0, 800, 600);

  vertexShader = newSPtr<OGL_VertexShader>();

  pixelShader = newSPtr<OGL_PixelShader>();

  shaderProgram = glCreateProgram();

  if(!GraphicAPI::initialize()){
    return false;
  }

  glLinkProgram(shaderProgram);

  return true;
}

bool 
OGL_GraphicsAPI::isRunning()
{
  return !glfwWindowShouldClose(window);
}

void 
OGL_GraphicsAPI::events()
{
  glfwSwapBuffers(window);
  glfwPollEvents();
}

OGL_GraphicsAPI::~OGL_GraphicsAPI()
{
  glfwTerminate();
}

}
