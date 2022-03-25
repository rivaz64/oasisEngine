/**
* @file oaSerializer.h
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 2/25/2022
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
  encodeNumber(SIZE_T n);

  SIZE_T
  decodeNumber();

  void
  encodeString(const String& string);

  String
  decodeString();

  void
  encodeImage(SPtr<Image> image);

  SPtr<Image>
  decodeImage();

  void
  encodeMaterial(SPtr<Material> material);

  SPtr<Material>
  decodeMaterial();

  void
  encodeModel(SPtr<Model> model);

  SPtr<Model>
  decodeModel();

  void
  encodeActor(SPtr<Actor> actor);

  SPtr<Actor>
  decodeActor();

  FStream file;
};

}
