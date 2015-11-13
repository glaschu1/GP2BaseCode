//
//  GameObject.cpp
//  GP2BaseCode
//
//  Created by james glasgow on 13/11/2015.
//
//

#include <GameObject.h>
#include "Shader.cpp"
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
  
  //Generate Vertex Array
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  
  glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(Vertex),
               pVerts, GL_STATIC_DRAW);
  
  //create buffer
  glGenBuffers(1, &m_EBO);
  //Make the EBO active
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  //Copy Index data to the EBO
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               numIndices*sizeof(int),
               pIndices, GL_STATIC_DRAW);
  
  
  //Tell the shader that 0 is the position element
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
  
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3)));
  
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4)));
  
  //send the normals to the buffer
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)(sizeof(vec3) + sizeof(vec4) + sizeof(vec2)));
  


};

void GameObject::loadShader(const string& vsFileName,const string& fsFileName){
  
  GLuint vertexShaderProgram = 0;
  
  vertexShaderProgram = loadShaderFromFile(vsFileName, VERTEX_SHADER);
  checkForCompilerErrors(vertexShaderProgram);
  
  GLuint fragmentShaderProgram = 0;
  fragmentShaderProgram = loadShaderFromFile(fsFileName, FRAGMENT_SHADER);
  checkForCompilerErrors(fragmentShaderProgram);
  
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShaderProgram);
  glAttachShader(m_shaderProgram, fragmentShaderProgram);
  
  //Link attributes
  glBindAttribLocation(m_shaderProgram, 0, "vertexPosition");
  glBindAttribLocation(m_shaderProgram, 1, "vertexColour");
  glBindAttribLocation(m_shaderProgram, 2, "vertexTexCoords");
  glBindAttribLocation(m_shaderProgram, 3, "vertexNormal");
  
  glLinkProgram(m_shaderProgram);
  checkForLinkErrors(m_shaderProgram);
  //now we can delete the VS & FS Programs
  glDeleteShader(vertexShaderProgram);
  glDeleteShader(fragmentShaderProgram);
  

};