#include "Shader.h"

//load it form mem
GLuint loadShaderFromMemory(const char*pMem, SHADER_TYPE shaderType)
{
	GLuint program = glCreateShader(shaderType);
	glShaderSource(program, 1, &pMem, NULL);
	glCompileShader(program);
	return program;

}

GLuint loadShaderFromFile(const std::string& filename, SHADER_TYPE shaderType)
{
	string fileContents;
	ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (!file){
		cout  << "File could not be loaded" << endl;
		return 0;
	}
	//cal file size
	if (file.good()){
		file.seekg(0, std::ios::end);
		unsigned long len = file.tellg();
		file.seekg(std::ios::beg);
		if (len == 0){
			std::cout << "file has bo contents" << std::endl;
			return 0;
		}
		fileContents.resize(len);
		file.read(&fileContents[0], len);
		file.close();
		GLuint program = loadShaderFromMemory(fileContents.c_str(), shaderType);
		return program;

	
	}
	return 0;

}
bool checkForCompilerErrors(GLuint shaderProgram){
	GLint isCompiled = 0;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
	GLint maxLenght = 0;
	glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLenght);

	//maxlenght includes the NULL
	string infoLog;
	infoLog.resize(maxLenght);
	glGetShaderInfoLog(shaderProgram, maxLenght, &maxLenght, &infoLog[0]);
	
	cout << "Shander not compiled" << infoLog << endl;

	//we dont need the shader
	glDeleteShader(shaderProgram);
	return true;
}
	return false;
}
bool checkForLinkErrors(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE){
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		string infoLog;
		infoLog.resize(maxLength);

		glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		cout << "Shader not linked" << infoLog << endl;
		glDeleteProgram(program);
			return true;
	}
	return false;
}