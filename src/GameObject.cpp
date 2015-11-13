//
//  GameObject.cpp
//  GP2BaseCode
//
//  Created by james glasgow on 13/11/2015.
//
//

#include <GameObject.h>
GameObject::GameObject(){
  m_VBO=0;
  m_EBO=0;
  m_VAO=0;
  m_shaderProgram=0;
  m_NoOfVertices=0;
  m_NoOfIndices=0;
  
  m_ModelMatrix=mat4(1.0f);
  m_Position =vec3(0.0f,0.0f,0.0f);
  m_Rotation=vec3(0.0f,0.0f,0.0f);
  m_Scale=vec3(1.0f,1.0f,1.0f);;
  
  m_ambientMaterial=vec4(0.2f,0.2f,0.2f,1.0f);
  m_diffuseMaterial=vec4(0.6f,0.6f,0.6f,1.0f);
  m_specularMaterial=vec4(1.0f,1.0f,1.f,1.0f);
  
  m_specularPower = 0.0f;
};

GameObject::~GameObject(){
  
  glDeleteProgram(m_shaderProgram);
  glDeleteBuffers(1, &m_EBO);
  glDeleteBuffers(1, &m_VBO);
  glDeleteVertexArrays(1, &m_VAO);

};

void GameObject::update(){
  mat4 translationMatrix = translate(mat4(1.0f), m_Position);
  mat4 scaleMatric=scale(mat4(1.0f), m_Scale);
  mat4 rotationMatrix=
  rotate(mat4(1.0f), m_Rotation.x,vec3(1.0f,0.0f,0.0f))*
  rotate(mat4(1.0f), m_Rotation.y,vec3(0.0f,1.0f,0.0f))*
  rotate(mat4(1.0f), m_Rotation.z,vec3(0.0f,0.0f,1.0f));
  m_ModelMatrix=scaleMatric*rotationMatrix*translationMatrix;
};

void GameObject::createBuffer(Vertex *pVerts,int numVerts, int *pIndices,int numIndices){

};

void GameObject::loadShader(const string& vsFileName,const string& fsFileName){

};