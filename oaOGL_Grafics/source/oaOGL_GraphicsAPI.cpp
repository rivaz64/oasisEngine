#include "oaOGL_GraphicsAPI.h"
#include "oaOGL_VertexShader.h"
#include "oaOGL_PixelShader.h"
#include "oaOGL_Buffer.h"
#include "oaOGL_Texture.h"
#include "oaResoureManager.h"
#include <iostream>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace oaEngineSDK{
void OGL_GraphicsAPI::onShutDown()
{
  glfwTerminate();
}
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

  glViewport(0, 0, 800, 600);

  vertexShader = newSPtr<OGL_VertexShader>();

  pixelShader = newSPtr<OGL_PixelShader>();

  shaderProgram = glCreateProgram();

  if(!GraphicAPI::initialize()){
    return false;
  }
  glLinkProgram(shaderProgram);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glUseProgram(shaderProgram); 
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
  glfwPollEvents();
}

void OGL_GraphicsAPI::setBackgroundColor(const Vector4f& color)
{

  glClearColor(color.x, color.y, color.z, color.w);

}

void OGL_GraphicsAPI::clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void OGL_GraphicsAPI::show()
{

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glfwSwapBuffers(window);
}

void OGL_GraphicsAPI::initImGui()
{
  ImGui::CreateContext();

  //ImGui::SetCurrentContext(io)
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize.x = windowWidth;
  io.DisplaySize.y = windowHeight;
}

void OGL_GraphicsAPI::newImGuiFrame()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::Begin("test");
  ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

SPtr<Buffer> OGL_GraphicsAPI::createBuffer()
{
  return newSPtr<OGL_Buffer>();
}

SPtr<Texture> OGL_GraphicsAPI::createTexture()
{
  return newSPtr<OGL_Texture>();
}

void OGL_GraphicsAPI::setVertexBuffer(const SPtr<Buffer>& buffer)
{
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OGL_GraphicsAPI::~OGL_GraphicsAPI()
{
  glDeleteProgram(shaderProgram);
}

}
