//
//  Light.h
//  GP2BaseCode
//
//  Created by james glasgow on 02/11/2015.
//
//

#ifndef LIGHT_h
#define LIGHT_h

#include "Common.h"

struct LightData
{
  vec3 direction;
  vec4 ambientColour;
  vec4 diffuseColour;
  vec4 specularColour;
};


#endif /* Light_h */
