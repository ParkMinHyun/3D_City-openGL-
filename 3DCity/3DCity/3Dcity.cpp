#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<GLAUX.h>


GLfloat X_axis = 0;
GLfloat Y_axis = 0;
GLfloat Z_axis = 0;
GLfloat transitionX = 0;
GLfloat transitionY = 0;
GLfloat mouseStartX;
GLfloat mouseStartY;
int zoomming = 0;
int dragging = 0;
int transing = 0;

GLfloat zoom = 10;

GLfloat ambient0[] = { 0.1f, 0.15f, 0.15f, 1.0f };
GLfloat diffuse0[] = { 0.0f, 0.3f, 0.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPos0[] = { -100.0f, 0.0f, 150.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };


GLfloat ambient1[] = { 0.4, 0.28, 0.25, 1.0 };
GLfloat diffuse1[] = { 0.10, 0.00, 0.50, 1.0 };
GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos1[] = { 3.0, 30.0, -30 };

GLfloat ambient2[] = { 0.27, 0.10, 0.20, 1.0 };
GLfloat diffuse2[] = { 0.73, 0.75, 0.52, 1.0 };
GLfloat specular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPos2[] = { 28.0,0.3, 1.0 };
GLfloat shine[] = { 25.0 };

GLfloat specular_m[] = { 1.00, 1.00, 1.00, 1.0 };


void Initlight()										// All Setup For OpenGL Goes Here
{
	glClearColor(1, 1, 1, 1);
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE);
}

void init()
{
	Initlight();

	glClearColor(0.0, 0.0, 0.0, 0.0); // black clear color, opaque window
	glColor4f(1.0, 1.0, 1.0, 1); // white
	glMatrixMode(GL_PROJECTION);

	gluPerspective(45.0f, 1.0, 1.0, 500.0);		 // 각도~ 45도로 잡겠다 내가 보는 방향. 
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, 1.0, 0.1, 1000);
	gluLookAt(-200, 300, 700, transitionX, transitionY, 0, 0, 1, 0);

	glRotatef(X_axis, 1.0, 0.0, 0.0);  // 마우스 드래그 회전 X축 기준
	glRotatef(Y_axis, 0.0, 1.0, 0.0);  // 마우스 드래그 회전 Y축 기준
	
	glutSolidCube(2);

	glutSwapBuffers();
}

void mouseclick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		dragging = 1; mouseStartX = (GLfloat)x; mouseStartY = (GLfloat)y;
	}
	else
		dragging = 0;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)  // http://www.coders-hub.com/2013/06/opengl-code-to-zoom-in-and-zoom-out.html#.VzGjGoSLSUm
	{
		zoomming = 1; 
		mouseStartX = (GLfloat)x; 
		mouseStartY = (GLfloat)y;
	}
	else
		zoomming = 0;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		transing = 1;  mouseStartX = (GLfloat)x; mouseStartY = (GLfloat)y;
	}
	else
		transing = 0;

}
void mousemove(int x, int y) //https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Arcball -출처
{
	if (dragging)
	{
		Y_axis += (x - mouseStartX) / 2;
		X_axis -= (y - mouseStartY) / 2;
	}
	else if (zoomming)
	{
		if (zoom > 179) zoom = 179;
		else if (zoom < 1) zoom = 1;
		zoom -= (y - mouseStartY) / 20;
	}
	else if (transing)
	{
		transitionX -= (x - mouseStartX) / 40;
		transitionY -= -(y - mouseStartY) / 40;
	}
	mouseStartX = (GLfloat)x;
	mouseStartY = (GLfloat)y;

	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(1400, 1400);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("122179_박민현");

	init();
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseclick);
	glutMotionFunc(mousemove);

	glutMainLoop();
}