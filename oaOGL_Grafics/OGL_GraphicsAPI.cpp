#include "OGL_GraphicsAPI.h"
#include <iostream>
#include<glad\glad.h>
#include <GLFW/glfw3.h>
void oaEngineSDK::OGL_GraphicsAPI::initialize()
{
  std::cout<<"openGL graphic API"<<std::endl;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

  //glViewport(0, 0, 800, 600);

  while(!glfwWindowShouldClose(window))
  {
    glfwSwapBuffers(window);
    glfwPollEvents();    
  }

  glfwTerminate();
}
