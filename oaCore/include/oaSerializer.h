/**
* @file oaSerializer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 9/25/2021
*/

#pragma once

#include "oaPrerequisitesCore.h"

namespace oaEngineSDK{

/**
 * @brief encodes and decodes files to binary
*/
class OA_CORE_EXPORT Serializer
{
 public:

  void 
  init(const Path& path);

  void
  encodeModel(SPtr<Model> model);

  SPtr<Model>
  decodeModel();

  FStream file;
};

}
