/**
 * @file oaColor.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 9/07/2021
 */

#pragma once

#include "oaPrerequisitesUtilities.h"

namespace oaEngineSDK{

class Color
{
 public:
  /**
   * @brief default constuctor for the color
  */
  Color() = default;

  /**
   * @brief parametrized constructor
   * @param _r red
   * @param _g green
   * @param _b blue
   * @param _a alpha
  */
  Color(float _r, float _g, float _b, float _a = 1.0f) :
    r(_r), g(_g), b(_b), a(_a) {}

  static const Color BLACK;
  static const Color WHITE;
  static const Color RED;
  static const Color GREEN;
  static const Color BLUE;
  static const Color YELLOW;
  static const Color MAGENTA;
  static const Color CYAN;
  static const Color ORANGE;
  static const Color RASPBERRY;
  static const Color VIOLET;
  static const Color OCEAN;
  static const Color TURQUOISE;
  static const Color SPRINGGREEN;

  /**
   * @brief red
  */
  float r;

  /**
   * @brief green
  */
  float g;

  /**
   * @brief blue
  */
  float b;

  /**
   * @brief alpha
  */
  float a;
};

}


