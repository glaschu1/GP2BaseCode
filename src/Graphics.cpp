#include "Graphics.h"
#include "Vertices.h"
#include "Common.h"

string getRendererCapsAsString()
{
	stringstream stringStream;

	stringStream << "OpenGl Version: " << glGetString(GL_VERSION)<<"\n";
	stringStream << "Vendor: " << glGetString(GL_VENDOR) << "\n";
	stringStream << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	stringStream << "Shading: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	stringStream << "Extensions Supported\n";
	GLint n = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &n);
	for(GLint i = 0; i<n; i++)
	{
		const char* extension =
			(const char*)glGetStringi(GL_EXTENSIONS, i);
		stringStream << extension << ", ";
	}

	return stringStream.str();
}

//Function to initialise OpenGL
void initOpenGL()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

	std::cout << getRendererCapsAsString() << endl;

    //Smooth shading
    glShadeModel( GL_SMOOTH );

    //clear the background to black
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    //Clear the depth buffer
    glClearDepth( 1.0f );

    //Enable depth testing
    glEnable( GL_DEPTH_TEST );

    //The depth test to go
    glDepthFunc( GL_LEQUAL );

    //Turn on best perspective correction
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

//Function to set/reset viewport
void setViewport( int width, int height )
{
    ////screen ration
    //GLfloat ratio;

    ////make sure height is always above 1
    //if ( height == 0 ) {
    //    height = 1;
    //}

    ////calculate screen ration
    //ratio = ( GLfloat )width / ( GLfloat )height;

    //Setup viewport
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    ////Change to poject matrix mode
    //glMatrixMode( GL_PROJECTION );
    //glLoadIdentity( );

    //Calculate perspective matrix, using glu library functions
   //gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    ////Swith to ModelView
    //glMatrixMode( GL_MODELVIEW );

    ////Reset using the Indentity Matrix
    //glLoadIdentity( );
}
