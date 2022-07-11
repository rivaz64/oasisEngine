#include "oaOGL_GraphicsAPI.h"
#include "oaOGL_VertexShader.h"
#include "oaOGL_PixelShader.h"
#include "oaOGL_Buffer.h"
#include "oaOGL_Texture.h"
#include "oaResoureManager.h"
#include "oaColor.h"
#include "oaShaderProgram.h"
#include "oaOGL_ShaderProgram.h"


namespace oaEngineSDK{
void OGL_GraphicsAPI::onShutDown()
{
  glfwTerminate();
}
bool
OGL_GraphicsAPI::initialize()
{
  print("openGL graphic API");

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_windowName.c_str(), NULL, NULL);
  if (window == NULL)
  {
    print("Failed to create GLFW window");
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

  /*
  vertexShader = newSPtr<OGL_VertexShader>();

  pixelShader = newSPtr<OGL_PixelShader>();

  shaderProgram = glCreateProgram();

  glLinkProgram(shaderProgram);*/

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

void 
OGL_GraphicsAPI::setBackgroundColor(const Color& color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}

SPtr<ShaderProgram> 
OGL_GraphicsAPI::createShaderProgram()
{
  return newSPtr<OGL_ShaderProgram>();
/*
  int success;
  char infoLog[512];
  glAttachShader(shaderProgram, cast<OGL_Shader>(vertexShader)->id);
  glAttachShader(shaderProgram, cast<OGL_Shader>(pixelShader)->id);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glUseProgram(shaderProgram); */
}
/*
void 
OGL_GraphicsAPI::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
*/
void
OGL_GraphicsAPI::draw(uint32 indexes)
{
  glDrawElements(GL_TRIANGLES, indexes, GL_UNSIGNED_INT, 0);
}

void 
OGL_GraphicsAPI::show()
{
  //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window);
}

SPtr<Buffer> 
OGL_GraphicsAPI::createBuffer()
{
  return newSPtr<OGL_Buffer>();
}

SPtr<Texture> 
OGL_GraphicsAPI::createTexture()
{
  return newSPtr<OGL_Texture>();
}
/*
void 
OGL_GraphicsAPI::setVertexBuffer(const SPtr<Buffer>& buffer)
{
  glBindVertexArray(cast<OGL_Buffer>(buffer)->m_id);
}*/

void 
OGL_GraphicsAPI::setIndexBuffer(const SPtr<Buffer>& buffer)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cast<OGL_Buffer>(buffer)->m_id);
}
/*
void 
OGL_GraphicsAPI::setTexture(const SPtr<Texture>& texture)
{
  glBindTexture(GL_TEXTURE_2D, cast<OGL_Texture>(texture)->id);
}*/
/*
void 
OGL_GraphicsAPI::setBuffer(const SPtr<Buffer>& buffer, uint32 location)
{
  //unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
  //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, reinterpret_cast<float*>(data));
  glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float*>(cast<OGL_Buffer>(buffer)->m_id));//
}

void* 
OGL_GraphicsAPI::getWindow()
{
  return window;
}

OGL_GraphicsAPI::~OGL_GraphicsAPI()
{
  glDeleteProgram(shaderProgram);
}
*/
}
