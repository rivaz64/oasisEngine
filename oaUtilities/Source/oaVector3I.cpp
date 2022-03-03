/**
* @file oaVector3I.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 11/10/2021
*/

#include "oaVector3I.h"

namespace oaEngineSDK{

const Vector3I Vector3I::ZERO(0,0,0);

const Vector3I Vector3I::RIGHT(1, 0, 0);
const Vector3I Vector3I::LEFT(-1, 0, 0);
const Vector3I Vector3I::UP(0, 1, 0);
const Vector3I Vector3I::DOWN(0, -1, 0);
const Vector3I Vector3I::FRONT(0, 0, 1);
const Vector3I Vector3I::BACK(0, 0, -1);

}