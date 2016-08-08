#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<GLAUX.h>
//vertex 배열을 이용해 Cube를 크기값만 주면 그려주는 함수 및 노말 벡터 적용

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
//------cube vertex ----
GLfloat ver_c[8][3] =
{
	{ -1.0,-1.0,1.0 },
	{ -1.0,1.0,1.0 },
	{ 1.0,1.0,1.0 },
	{ 1.0,-1.0,1.0 },

	{ -1.0,-1.0,-1.0 },
	{ -1.0,1.0,-1.0 },
	{ 1.0,1.0,-1.0 },
	{ 1.0,-1.0,-1.0 },
};
//------pyramid vertex ----
GLfloat ver_p[4][3] =
{
	{ 0.0,1.0,0.0 },
	{ -1.0,-1.0,1.0 },
	{ 1.0,-1.0,1.0 },
	{ 0.0,-1.0,-1.0 },
};
//------pyramid2 vertex ----
GLfloat ver_roof[6][3] =
{
	{ -1.0,1.0,0.0 },
	{ -1.0,0.0,0.0 },
	{ -1.0,0.0,1.0 },

	{ 1.0,1.0,0.0 },
	{ 1.0,0.0,0.0 },
	{ 1.0,0.0,1.0 },
};
GLfloat ver_roof2[8][3] =
{
	{ -1.0,-1.0,1.0 },
	{ (GLfloat)-0.6,1.0,1.0 },
	{ (GLfloat)0.6,1.0,1.0 },
	{ 1.0,-1.0,1.0 },

	{ -1.0,-1.0,-1.0 },
	{ (GLfloat)-0.6,1.0,-1.0 },
	{ (GLfloat)0.6,1.0,-1.0 },
	{ 1.0,-1.0,-1.0 },
};

GLfloat ver_hotel[20][3] =
{
	{ -1,1,1 },{ -0.5,1,0.5 },{ 0,1,(GLfloat)0.3 },{ 0.5, 1, 0.5 },{ 1,1,1 },
	{ 1,1,0 },{ 0.5,1,0. - 0.75 },{ 0,1, -1 },{ -0.5,1,-0.75 },{ -1,1,0 },

	{ -1,-1,1 },{ -0.5,-1,0.5 },{ 0,-1,(GLfloat)0.3 },{ 0.5,-1,0.5 },{ 1,-1,1, },
	{ 1,-1,0 },{ 0.5,-1,-0.75 },{ 0,-1,-1 },{ -0.5,-1,-0.75 },{ -1,-1,0 },
};
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
	glLoadIdentity();
}
void quad(int a, int b, int c, int d, GLfloat size, int e)
{
	float p[3][3] = { { ver_roof2[a][0] * size, ver_roof2[a][1] * size, ver_roof2[a][2] * size },
	{ ver_roof2[b][0] * size, ver_roof2[b][1] * size, ver_roof2[b][2] * size },
	{ ver_roof2[c][0] * size, ver_roof2[c][1] * size, ver_roof2[c][2] * size } };

	float vec1[3] = { p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2] };
	float vec2[3] = { p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2] };
	float out[3] = { vec1[1] * vec2[2] - vec1[2] * vec2[1], vec1[2] * vec2[0] - vec1[0] * vec2[2], vec1[0] * vec2[1] - vec1[1] * vec2[0] };
	float vecSize = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);

	out[0] = out[0] / vecSize;
	out[1] = out[1] / vecSize;
	out[2] = out[2] / vecSize;
	glBindTexture(GL_TEXTURE_2D, textures[e]);	// 1번 텍스처 쓰겠다.
	glBegin(GL_QUADS);
	glNormal3f(out[0], out[1], out[2]);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_c[a][0] * size, ver_c[a][1] * size, ver_c[a][2] * size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(ver_c[b][0] * size, ver_c[b][1] * size, ver_c[b][2] * size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(ver_c[c][0] * size, ver_c[c][1] * size, ver_c[c][2] * size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(ver_c[d][0] * size, ver_c[d][1] * size, ver_c[d][2] * size);
	glEnd();
}
void quad2(int a, int b, int c, int d, GLfloat size, int e)
{
	float p[3][3] = { { ver_c[a][0] * size, ver_c[a][1] * size, ver_c[a][2] * size },
	{ ver_c[b][0] * size, ver_c[b][1] * size, ver_c[b][2] * size },
	{ ver_c[c][0] * size, ver_c[c][1] * size, ver_c[c][2] * size } };

	float vec1[3] = { p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2] };
	float vec2[3] = { p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2] };
	float out[3] = { vec1[1] * vec2[2] - vec1[2] * vec2[1], vec1[2] * vec2[0] - vec1[0] * vec2[2], vec1[0] * vec2[1] - vec1[1] * vec2[0] };
	float vecSize = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);

	out[0] = out[0] / vecSize;
	out[1] = out[1] / vecSize;
	out[2] = out[2] / vecSize;
	glBindTexture(GL_TEXTURE_2D, textures[e]);	// 1번 텍스처 쓰겠다.

	glBegin(GL_QUADS);
	glNormal3f(out[0], out[1], out[2]);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_roof2[a][0] * size, ver_roof2[a][1] * size, ver_roof2[a][2] * size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_roof2[b][0] * size, ver_roof2[b][1] * size, ver_roof2[b][2] * size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_roof2[c][0] * size, ver_roof2[c][1] * size, ver_roof2[c][2] * size);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_roof2[d][0] * size, ver_roof2[d][1] * size, ver_roof2[d][2] * size);
	glEnd();
}
void polygon(int a, int b, int c, int d, GLfloat size, int flag)
{
	float p[3][3] = { { ver_c[a][0] * size, ver_c[a][1] * size, ver_c[a][2] * size },
	{ ver_c[b][0] * size, ver_c[b][1] * size, ver_c[b][2] * size },
	{ ver_c[c][0] * size, ver_c[c][1] * size, ver_c[c][2] * size } };

	float vec1[3] = { p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2] };
	float vec2[3] = { p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2] };
	float out[3] = { vec1[1] * vec2[2] - vec1[2] * vec2[1], vec1[2] * vec2[0] - vec1[0] * vec2[2], vec1[0] * vec2[1] - vec1[1] * vec2[0] };
	float vecSize = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);

	out[0] = out[0] / vecSize;
	out[1] = out[1] / vecSize;
	out[2] = out[2] / vecSize;
	if (flag == 1)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f(out[0], out[1], out[2]);
		glVertex3f(ver_roof[a][0] * size, ver_roof[a][1] * size, ver_roof[a][2] * size);
		glVertex3f(ver_roof[b][0] * size, ver_roof[b][1] * size, ver_roof[b][2] * size);
		glVertex3f(ver_roof[c][0] * size, ver_roof[c][1] * size, ver_roof[c][2] * size);
	}
	else
	{
		glBegin(GL_QUADS);
		glNormal3f(out[0], out[1], out[2]);
		glVertex3f(ver_roof[a][0] * size, ver_roof[a][1] * size, ver_roof[a][2] * size);
		glVertex3f(ver_roof[b][0] * size, ver_roof[b][1] * size, ver_roof[b][2] * size);
		glVertex3f(ver_roof[c][0] * size, ver_roof[c][1] * size, ver_roof[c][2] * size);
		glVertex3f(ver_roof[d][0] * size, ver_roof[d][1] * size, ver_roof[d][2] * size);
	}
	glEnd();
}
void polygon_hotel(int a, int b, int c, int d, GLfloat size, int flag, int e)
{
	float p[3][3] = { { ver_c[a][0] * size, ver_c[a][1] * size, ver_c[a][2] * size },
	{ ver_c[b][0] * size, ver_c[b][1] * size, ver_c[b][2] * size },
	{ ver_c[c][0] * size, ver_c[c][1] * size, ver_c[c][2] * size } };

	float vec1[3] = { p[1][0] - p[0][0], p[1][1] - p[0][1], p[1][2] - p[0][2] };
	float vec2[3] = { p[2][0] - p[0][0], p[2][1] - p[0][1], p[2][2] - p[0][2] };
	float out[3] = { vec1[1] * vec2[2] - vec1[2] * vec2[1], vec1[2] * vec2[0] - vec1[0] * vec2[2], vec1[0] * vec2[1] - vec1[1] * vec2[0] };
	float vecSize = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);

	out[0] = out[0] / vecSize;
	out[1] = out[1] / vecSize;
	out[2] = out[2] / vecSize;
	glBindTexture(GL_TEXTURE_2D, textures[e]);	// 1번 텍스처 쓰겠다.
	if (flag == 1)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f(out[0], out[1], out[2]);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_hotel[a][0] * size, ver_hotel[a][1] * size, ver_hotel[a][2] * size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(ver_hotel[b][0] * size, ver_hotel[b][1] * size, ver_hotel[b][2] * size);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(ver_hotel[c][0] * size, ver_hotel[c][1] * size, ver_hotel[c][2] * size);
	}
	else
	{
		glBegin(GL_QUADS);
		glNormal3f(out[0], out[1], out[2]);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(ver_hotel[a][0] * size, ver_hotel[a][1] * size, ver_hotel[a][2] * size);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(ver_hotel[b][0] * size, ver_hotel[b][1] * size, ver_hotel[b][2] * size);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(ver_hotel[c][0] * size, ver_hotel[c][1] * size, ver_hotel[c][2] * size);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(ver_hotel[d][0] * size, ver_hotel[d][1] * size, ver_hotel[d][2] * size);
	}
	glEnd();
}

void drawCube(double x, double y, GLfloat size, int texe, int texf)
{
	glPushMatrix();
	glScalef((GLfloat)x, (GLfloat)y, 1.0f);
	quad(0, 3, 2, 1, size, texf);      // 앞면
	quad(4, 0, 1, 5, size, texe);      // 왼면
	quad(7, 4, 5, 6, size, texe);      // 뒷면
	quad(7, 6, 2, 3, size, texe);      // 오른면
	quad(1, 2, 6, 5, size, texe);      // 윗면
	quad(0, 4, 7, 3, size, texe);      // 밑면
	glPopMatrix();
}
void drawCube_building2(double x, double y, GLfloat size, int texe, int texf)
{
	glPushMatrix();
	glScalef((GLfloat)x, (GLfloat)y, 1.0f);
	quad(0, 3, 2, 1, size, texe);      // 앞면
	quad(4, 0, 1, 5, size, texe);      // 왼면
	quad(7, 4, 5, 6, size, texe);      // 뒷면
	quad(7, 6, 2, 3, size, texf);      // 오른면
	quad(1, 2, 6, 5, size, texe);      // 윗면
	quad(0, 4, 7, 3, size, texe);      // 밑면
	glPopMatrix();
}
void drawCube_train(double x, double y, GLfloat size, int texe, int texf)
{
	glPushMatrix();
	glScalef((GLfloat)x, (GLfloat)y, 1.0f);
	quad(0, 3, 2, 1, size, texf);      // 앞면
	quad(4, 0, 1, 5, size, texe);      // 왼면
	quad(7, 4, 5, 6, size, texf);      // 뒷면
	quad(7, 6, 2, 3, size, texe);      // 오른면
	quad(1, 2, 6, 5, size, texe);      // 윗면
	quad(0, 4, 7, 3, size, texe);      // 밑면
	glPopMatrix();
}
void drawSchoolroof(double x, double y, GLfloat size, int texe)
{
	glPushMatrix();
	glScalef((GLfloat)x, (GLfloat)y, 1.0f);
	quad2(0, 3, 2, 1, size, texe);      // 앞면
	quad2(4, 0, 1, 5, size, texe);      // 왼면
	quad2(7, 4, 5, 6, size, texe);      // 뒷면
	quad2(7, 6, 2, 3, size, texe);      // 오른면
	quad2(1, 2, 6, 5, size, texe);      // 윗면
	quad2(0, 4, 7, 3, size, texe);      // 밑면
	glPopMatrix();
}
void drawPoly(double x, double y, GLfloat size)
{
	glPushMatrix();
	glScalef((GLfloat)x, (GLfloat)y, 1.0f);
	polygon(1, 2, 0, 0, size, 1);	// 왼면
	polygon(4, 5, 3, 0, size, 1);	// 오른면
	polygon(2, 5, 3, 0, size, 2);	// 오른면
	polygon(4, 1, 0, 3, size, 2);
	polygon(1, 4, 5, 2, size, 2);
	glPopMatrix();
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
	
	glutSolidCube(10);

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
	switch (key)
	{
	case '0':
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		break;

	case '1':
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		break;

	case '2':
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		break;
	case '3':
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		break;
	}
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