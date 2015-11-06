#include "Common.h"
#include "Graphics.h"
#include "Vertices.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "FileSystem.h"
#include "FBXLoader.h"
#include "Light.h"
#include "Material.h"


vec3 rotationAngle = {0.0f, 0.0f, 0.0f};

vec3 cameraPosition = {0.0f, 0.0f, 50.0f};

float specularPower = 1.0f;
//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;
mat4 MVPMatrix;
mat4 modelMatrix;
mat4 rotationMatrix;

//timing
Uint32 old_time,current_time;
float ftime;
float totalTime;
//
LightData lightData;
MaterialData materialData;

GLuint VBO;
GLuint EBO;
GLuint VAO;
GLuint shaderProgram;
GLuint fontTexture;
GLuint diffuseMap;

MeshData currentMesh;

GLuint FBOTexture;
GLuint FBODepthBuffer;
GLuint frameBufferObject;
GLuint fullScreenVAO;
GLuint fullScreenVBO;
GLuint fullScreenShaderProgram;

const int FRAME_BUFFER_WIDTH=640;
const int FRAME_BUFFER_HEIGHT=480;

void createFramebuffer(){
  //Create Texture Object
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1,	&FBOTexture);
  glBindTexture(GL_TEXTURE_2D,	FBOTexture);
  // Texture Object setup
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,	GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,	GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,	GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,	GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D,	0,	GL_RGBA,
               FRAME_BUFFER_WIDTH,
               FRAME_BUFFER_HEIGHT,
               0,	GL_RGBA,
               GL_UNSIGNED_BYTE,	NULL);
  
  //creating depthbuffer
  glGenRenderbuffers(1,	&FBODepthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER,FBODepthBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT32,FRAME_BUFFER_WIDTH,FRAME_BUFFER_HEIGHT);
  glBindRenderbuffer(GL_RENDERBUFFER,	0);
  
  //creating framebuffer
  glGenFramebuffers(1,	&frameBufferObject);
  glBindFramebuffer(GL_FRAMEBUFFER,frameBufferObject);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,	FBOTexture,	0);
  
  //framebuffer setup
  glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,	GL_RENDERBUFFER,FBODepthBuffer);
  
  //error testing
  GLenum status;
  if	((status	=glCheckFramebufferStatus(
                                          GL_FRAMEBUFFER))	!=
       GL_FRAMEBUFFER_COMPLETE)	{
    cout <<	"Issue	with	Framebuffers"	<<endl;
  }
  
  float vertices[]	={
    -1,	-1,
    1,	-1,
    -1,	1,
    1,	1,
  };
  
  //create and bind a VAO
  glGenVertexArrays(1, &fullScreenVAO);
  glBindVertexArray(fullScreenVAO);
  
  //create and bind VBO
  glGenBuffers(1, &fullScreenVBO);
  glBindBuffer(GL_ARRAY_BUFFER, fullScreenVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(float), vertices, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,0,0);
  //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), NULL);
  
  GLuint vertexShaderProgram = 0;
  string vsPath = ASSET_PATH + SHADER_PATH + "/simplePostPorcessVS.glsl";
  vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
  checkForCompilerErrors(vertexShaderProgram);
  
  GLuint fragmentShaderProgram = 0;
  string fsPath = ASSET_PATH + SHADER_PATH + "/simplePostPorcessFS.glsl";
  fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
  checkForCompilerErrors(fragmentShaderProgram);
  
  //create shader
  fullScreenShaderProgram = glCreateProgram();
  glAttachShader(fullScreenShaderProgram, vertexShaderProgram);
  glAttachShader(fullScreenShaderProgram, fragmentShaderProgram);
  
  glBindAttribLocation(fullScreenShaderProgram, 0, "vertexPostion");
  
  glLinkProgram(fullScreenShaderProgram);
  checkForLinkErrors(fullScreenShaderProgram);
  
  //now we can delete the VS & FS Programs
  glDeleteShader(vertexShaderProgram);
  glDeleteShader(fragmentShaderProgram);
  

  

}
/*void createFullscreenQuad(){
  
  float vertices[]	={
    -1,	-1,
    1,	-1,
    -1,	1,
    1,	1,
  };

  //create and bind a VAO
  glGenVertexArrays(1, &fullScreenVAO);
  glBindVertexArray(fullScreenVAO);
  
  //create and bind VBO
  glGenBuffers(1, &fullScreenVBO);
  glBindBuffer(GL_ARRAY_BUFFER, fullScreenVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(float), vertices, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,0,0);
  //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), NULL);
  
  GLuint vertexShaderProgram = 0;
  string vsPath = ASSET_PATH + SHADER_PATH + "/simplePostPorcessVS.glsl";
  vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
  checkForCompilerErrors(vertexShaderProgram);
  
  GLuint fragmentShaderProgram = 0;
  string fsPath = ASSET_PATH + SHADER_PATH + "/simplePostPorcessFS.glsl";
  fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
  checkForCompilerErrors(fragmentShaderProgram);
  
  //create shader
  fullScreenShaderProgram = glCreateProgram();
  glAttachShader(fullScreenShaderProgram, vertexShaderProgram);
  glAttachShader(fullScreenShaderProgram, fragmentShaderProgram);
  
  glBindAttribLocation(fullScreenShaderProgram, 0, "vertexPostion");
  
  glLinkProgram(fullScreenShaderProgram);
  checkForLinkErrors(fullScreenShaderProgram);
  
  //now we can delete the VS & FS Programs
  glDeleteShader(vertexShaderProgram);
  glDeleteShader(fragmentShaderProgram);

}*/
void cleanUpFrameBuffer(){
  glDeleteProgram(fullScreenShaderProgram);
  glDeleteBuffers(1, &fullScreenVBO);
  glDeleteVertexArrays(1, &fullScreenVAO);
  glDeleteFramebuffers(1, &frameBufferObject);
  glDeleteRenderbuffers(1, &FBODepthBuffer);
  glDeleteTextures(1, &FBOTexture);

}
void renderScene(){
  glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
  
  //Set the clear colour(background)
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  //clear the colour and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glUseProgram(shaderProgram);
  
  //get the uniform loaction for the MVP
  GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
  glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
  
  //get the model matrix uniform
  GLint modelLocation = glGetUniformLocation(shaderProgram, "Model");
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(worldMatrix));
  
  GLint AMCLocation = glGetUniformLocation(shaderProgram, "ambientMaterialColour");
  glUniform4fv(AMCLocation, 1,  glm::value_ptr(materialData.ambientColour));
  
  GLint ALCLocation = glGetUniformLocation(shaderProgram, "ambientLightColour");
  glUniform4fv(ALCLocation, 1,  glm::value_ptr(lightData.ambientColour));
  
  GLint lightDirLocation = glGetUniformLocation(shaderProgram, "lightDirection");
  glUniform3fv(lightDirLocation, 1, value_ptr(lightData.direction));
  
  GLint DMCLocation = glGetUniformLocation(shaderProgram, "diffuseMaterialColour");
  glUniform4fv(DMCLocation, 1,  glm::value_ptr(materialData.diffuseColour));
  
  GLint DLCLocation = glGetUniformLocation(shaderProgram, "diffuseLightColour");
  glUniform4fv(DLCLocation, 1,  glm::value_ptr(lightData.diffuseColour));
  
  GLint SMCLocation = glGetUniformLocation(shaderProgram, "specularMaterialColour");
  glUniform4fv(SMCLocation, 1,  glm::value_ptr(materialData.specularColour));
  
  GLint SLCLocation = glGetUniformLocation(shaderProgram, "specularLightColour");
  glUniform4fv(SLCLocation, 1,  glm::value_ptr(lightData.specularColour));
  
  GLint SpecPowerLocation = glGetUniformLocation(shaderProgram, "specularPower");
  glUniform1f(SpecPowerLocation, specularPower);
  
  GLint pptime = glGetUniformLocation(shaderProgram, "time");
  glUniform1f(ppresolution, specularPower);
  
  GLint ppresolution = glGetUniformLocation(shaderProgram, "specularPower");
  glUniform1f(ppresolution, specularPower);
  
  //get the uniform for the texture coords
  GLint texture0Location = glGetUniformLocation(shaderProgram, "texture0");
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, diffuseMap);
  glUniform1i(texture0Location, 0);
  
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, currentMesh.getNumIndices(),
                 GL_UNSIGNED_INT, 0);
}
void renderPostProcessing(){
  glBindFramebuffer(GL_FRAMEBUFFER,0);
  //Set the clear colour(background)
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glUseProgram(fullScreenShaderProgram);
  
  //retrive the location of texture
  GLint textureLocation = glGetUniformLocation(fullScreenShaderProgram, "texture0");
  
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, FBOTexture);
  glUniform1i(textureLocation, 0);
  
  glBindVertexArray(fullScreenVAO);
  
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  
}
void initScene()
{
  createFramebuffer();
  //createFullscreenQuad();
  //load font
  string modelPath = ASSET_PATH + MODEL_PATH + "/Utah-Teapot.fbx";
  loadFBXFromFile(modelPath, &currentMesh);
  string fontPath =ASSET_PATH + FONT_PATH + "/OratorStd.otf";
  fontTexture=loadTextureFromFont(fontPath,18,"Hello world");
  
  glBindTexture(GL_TEXTURE_2D, fontTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  
	
  
  //load texture & bind
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	diffuseMap = loadTextureFromFile(texturePath);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Generate Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
  glBufferData(GL_ARRAY_BUFFER, currentMesh.getNumVerts()*sizeof(Vertex),
               &currentMesh.vertices[0], GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Copy Index data to the EBO
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               currentMesh.getNumIndices()*sizeof(int),
               &currentMesh.indices[0], GL_STATIC_DRAW);
	

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


	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/specularVS.glsl";//ambient
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);
	checkForCompilerErrors(vertexShaderProgram);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/specularFS.glsl";//
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);
	checkForCompilerErrors(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);

	//Link attributes
	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
	glBindAttribLocation(shaderProgram, 1, "vertexColour");
	glBindAttribLocation(shaderProgram, 2, "vertexTexCoords");
  glBindAttribLocation(shaderProgram, 3, "vertexNormal");

	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);
	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
  
  //init material
  lightData.direction = vec3(0.0f, 0.0f, 1.0f);
  lightData.ambientColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  lightData.diffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  lightData.specularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  
  //int light
  materialData.ambientColour = vec4(0.3f, 0.3f, 0.3, 1.0f);
  materialData.diffuseColour = vec4(0.3f, 0.3f, 0.3, 1.0f);
  materialData.specularColour = vec4(0.3f, 0.3f, 0.3, 1.0f);
}

void cleanUp()
{
  cleanUpFrameBuffer();
  glDeleteTextures(1,&fontTexture);
	glDeleteTextures(1, &diffuseMap);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void update()
{
  old_time=current_time;
  current_time=SDL_GetTicks();
  ftime=(current_time-old_time)/1000.0f;
  totalTime+=ftime;
  rotationMatrix =
		mat4(cos(rotationAngle.z), -sin(rotationAngle.z), 0, 0,
         sin(rotationAngle.z), cos(rotationAngle.z), 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1) *
		mat4(cos(rotationAngle.y), 0, sin(rotationAngle.y), 0,
         0, 1, 0, 0,
         -sin(rotationAngle.y), 0, cos(rotationAngle.y), 0,
         0, 0, 0, 1) *
		mat4(1, 0, 0, 0,
         0, cos(rotationAngle.x), -sin(rotationAngle.x), 0,
         0, sin(rotationAngle.x), cos(rotationAngle.x), 0,
         0, 0, 0, 1);
  
	projMatrix = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	viewMatrix = glm::lookAt(vec3(cameraPosition), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	MVPMatrix = projMatrix*viewMatrix*worldMatrix*rotationMatrix;
}

void render()
{
  renderScene();
  renderPostProcessing();
	
}

int main(int argc, char * arg[])
{

  ChangeWorkingDirectory();
	//Controls the game loop
	bool run = true;

	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}
	//
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{

		cout << "ERROR	SDL_Image	Init	" << IMG_GetError() << endl;
	}
  
  if (TTF_Init() == -1)	{
    std::cout << "ERROR	TTF_Init: " << TTF_GetError();
  }
  

	//Request opengl 4.1 context, Core Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	//Create a window
	SDL_Window * window = SDL_CreateWindow(
		"SDL",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		640,                        // width, in pixels
		480,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);

	// Create an OpenGL context associated with the window.
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	//Call our InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(640, 480);

	initScene();
	//Value to hold the event generated by SDL
	SDL_Event event;
  //time

  
  current_time=SDL_GetTicks();
 
	//Game Loop
	while (run)
	{
   
		//While we still have events in the queue
		while (SDL_PollEvent(&event)) {
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				//set our boolean which controls the loop to false
				run = false;
			}
			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
             lightData.direction.x +=-1.0f;
         
          break;
				case SDLK_RIGHT:
            lightData.direction.x +=1.0f;
            
					break;
				case SDLK_UP:
            lightData.direction.y +=1.0f;
					break;
				case SDLK_DOWN:
            lightData.direction.y +=-1.0f;
					break;
        case SDLK_n:
            lightData.direction.z +=1.0f;
          break;
        case SDLK_m:
            lightData.direction.z +=-1.0f;
          break;
        case SDLK_d:
            rotationAngle.z += 1.0f;
          break;
        case SDLK_a:
            rotationAngle.z -= 1.0f;
          break;
        case SDLK_q:
            rotationAngle.y += 1.0f;
          break;
        case SDLK_e:
            rotationAngle.y -= 1.0f;
          break;
        case SDLK_w:
            rotationAngle.x += 1.0f;
          break;
        case SDLK_s:
            rotationAngle.x -= 1.0f;
          break;
				default:
					break;
				}
			}
		}

    
    
    
		//init Scene
		update();
		//render
		render();
		//Call swap so that our GL back buffer is displayed
		SDL_GL_SwapWindow(window);

	}

	// clean up, reverse order!!!
	cleanUp();
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
	SDL_Quit();

	return 0;
}
