/**
* @file oaDX11Shader.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 10/14/2021
*/

#pragma once

#include <oaShader.h>
#include <d3d11.h>

namespace oaEngineSDK{

class DX11Shader :
  public Shader
{
 public:

  virtual 
  ~DX11Shader()=default;

public:
  
  /**
   * @brief reads the shader from the file to a blob
   * @param file 
   * @param blob 
   * @return 
  */
  bool
  readFromFile(String file,ID3DBlob** blob);

  //ID3DBlob* m_blob = nullptr;

  String m_version;
};

}


