//
//  GameObject.h
//  GP2BaseCode
//
//  Created by james glasgow on 13/11/2015.
//
//

#ifndef _GAMEOBJECT_h
#define _GAMEOBJECT_h
#include "Common.h"
#include "Vertices.h"
class GameObject{
public:
  GameObject();
  ~GameObject();
  
  void update();
  void createBuffer(Vertex *pVerts,int numVerts, int *pIndices,int numIndices);
  void loadShader(const string& vsFileName,const string& fsFileName);
private:
  GLuint m_VBO;
  GLuint m_EBO;
  GLuint m_VAO;
  GLuint m_shaderProgram;
  int m_NoOfVertices;
  int m_NoOfIndices;
  
  mat4 m_ModelMatrix;
  vec3 m_Position;
  vec3 m_Rotation;
  vec3 m_Scale;
  
  vec4 m_ambientMaterial;
  vec4 m_diffuseMaterial;
  vec4 m_specularMaterial;
  float m_specularPower;
protected:
  
};
#endif /* GameObject_h */
