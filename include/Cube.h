//
//  Cube.h
//  GP2BaseCode
//
//  Created by james glasgow on 13/11/2015.
//
//

#ifndef _CUBE_h
#define _CUBE_h

#include "Common.h"
#include "Vertices.h"
Vertex cubeVerts[] = {
  //Front
  { vec3(-0.5f, 0.5f, 0.5f),
    vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f), vec3(-0.3f,0.3f,0.3f) },// Top Left
  
  { vec3(-0.5f, -0.5f, 0.5f),
    vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f),vec3(-0.3f,-0.3f,0.3f) },// Bottom Left
  
  { vec3(0.5f, -0.5f, 0.5f),
    vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f),vec3(0.3f,-0.3f,0.3f) }, //Bottom Right
  
  { vec3(0.5f, 0.5f, 0.5f),
    vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f),vec3(0.3f,0.3f,0.3f) },// Top Right
  
  
  //back
  { vec3(-0.5f, 0.5f, -0.5f),
    vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f),vec3(-0.3f,0.3f,-0.3f) },// Top Left
  
  { vec3(-0.5f, -0.5f, -0.5f),
    vec4(1.0f, 1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f),vec3(-0.3f,-0.3f,-0.3f) },// Bottom Left
  
  { vec3(0.5f, -0.5f, -0.5f),
    vec4(0.0f, 1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f),vec3(0.3f,-0.3f,-0.3f) }, //Bottom Right
  
  { vec3(0.5f, 0.5f, -0.5f),
    vec4(1.0f, 0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f),vec3(0.3f,0.3f,-0.3f) },// Top Right
  
};

int cubeIndices[] = {
  //front
  0, 1, 2,
  0, 3, 2,
  
  //left
  4, 5, 1,
  4, 1, 0,
  
  //right
  3, 7, 2,
  7, 6, 2,
  
  //bottom
  1, 5, 2,
  6, 2, 5,
  
  //top
  4, 0, 7,
  0, 7, 3,
  
  //back
  4, 5, 6,
  4, 7, 6
};

#endif /* Cube_h */
