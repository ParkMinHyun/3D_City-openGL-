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

void cylinder(GLdouble base, GLdouble top, GLdouble height)
{
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH); /* smooth shaded */
	gluCylinder(qobj, base, top, height, 15, 5);

}
void drawCylinder(double a, double b, double c)            // 빈 실린더
{
	glPushMatrix(); // 실린더 그리기. 
	glTranslatef(3.0, 2.0, 0.0);
	GLUquadricObj *obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	glTranslatef(0.0, (GLfloat)-0.7, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);  // 마우스 드래그 회전 X축 기준
	gluCylinder(obj, a, b, c, 12, 10);//실린더 크기를 적당한 크기로 변경
	glPopMatrix();
}
void draw_Cylinder(GLfloat radius, GLfloat height)         // 꽉찬 실린더
{
	GLfloat x = 0.0; GLfloat y = 0.0;
	GLfloat angle = 0.0; GLfloat angle_stepsize = (GLfloat)0.1;

	/** Draw the tube */
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		glVertex3f(x, y, 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();

	/** Draw the circle on top of cylinder */
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();
}
void building1()   // glTranslatef의 y축에 GLfloat을 해야 경고문이 없어져서 ㅠㅠ 코드가 길어지긴 했지만 넣었습니다..........
{
	drawCube(1.0, 0.4, 1.5, 4, 4);
	glPushMatrix(); glTranslatef(0.0, (GLfloat)0.8, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)1.0, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)1.5, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)1.7, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)2.2, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)2.4, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)2.9, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)3.1, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)3.6, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)3.8, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)4.3, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)4.5, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)5.0, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)5.2, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)5.7, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)5.9, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)6.4, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)6.6, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)7.1, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)7.3, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)7.8, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)8.0, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)8.5, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)8.7, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)9.2, 0.0); drawCube(1.0, 0.11, 1.9, 4, 4); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)9.4, 0.0); drawCube(1, 0.4, 1.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)9.9, 0.0); drawCube(1.0, 0.11, 1.9, 4, 2); glPopMatrix();/**/ glPushMatrix(); glTranslatef(0.0, (GLfloat)10.9, 0.0); drawCube(1, 0.5, 1.5, 4, 1); glPopMatrix();
}
void building2()
{
	drawCube_building2(1.0, 3.0, 1.5, 5, 3);
	glPushMatrix(); glTranslatef(0.0, (GLfloat)5.12, 0.0);   glScalef(1, 0.5, 1); drawCube(0.8, 1, (GLfloat)1.1, 5, 5); glPopMatrix();
}
void church()
{
	drawCube(0.7, 1.0, 1.5, 5, 5);
	glPushMatrix(); glTranslatef(0.0, (GLfloat)1.6, 0.0); drawPoly(0.75, 0.5, 1.5); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)1.6, 0.0); glRotatef(180.0, 0.0, 1.0, 0.0); drawPoly(0.75, 0.5, 1.5);					 glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.25, (GLfloat)0.7, 0.0); drawCube_building2(0.1, 2.2, 1, 4, 8);	glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.25, (GLfloat)2.9, 0.0); drawPoly(0.1, 0.5, 1);	glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.25, (GLfloat)2.9, 0.0); glRotatef(180.0, 0.0, 1.0, 0.0); drawPoly(0.1, 0.5, 1);			 glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.25, (GLfloat)3.7, 0.0); drawCube(0.1, 3, (GLfloat)0.1, 4, 1); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.25, (GLfloat)3.8, 0.0); glRotatef(90.0, 0.0, 1.0, 0.0);  drawCube(2, 0.5, (GLfloat)0.1, 4, 1); glPopMatrix();
}
void school()
{
	drawCube_building2(1, 1.0, (GLfloat)1.2, 10, 9);


	GLfloat ambient_b3[] = { 0.52 , 0.11 , 0.02 , 1.0 };
	GLfloat diffues_b3[] = { 0.52 , 0.15, 0.14, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(0.0, (GLfloat)1.85, 0.0);			drawSchoolroof(1.02, 0.5, (GLfloat)1.27, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.5, (GLfloat)-0.7, 0.0); drawCube(0.2, 0.1, (GLfloat)0.5, 10, 1);	   glPopMatrix();
}
void hospital()
{
	GLfloat ambient_hotel[] = { 0.12 , 0.81 , 0.52 , 1.0 }; GLfloat diffues_hotel[] = { 0.02 , 0.85, 0.54, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_hotel);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_hotel); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	drawCube_building2(1, 2, 1.5, 5, 6);
	glPushMatrix(); glTranslatef((GLfloat)1.8, (GLfloat)-2.5, 0);  drawCube(0.2, 0.2, 1, 4, 1); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.45, (GLfloat)3.9, 0.0); drawCube(0.05, 0.3, (GLfloat)1, 4, 1); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.35, (GLfloat)3.9, 0.0); glRotatef(90.0, 1.0, 0.0, 0.0);  drawCube(0.05, 0.3, 1, 4, 1); glPopMatrix();
}
//---------------------------------------------------------------------------------건물 그리기
void drawBuilding1()
{
	GLfloat ambient_b1[] = { 0.22 , 0.51 , 0.52 , 1.0 };
	GLfloat diffues_b1[] = { 0.02 , 0.15, 0.94, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(-16.0, -2.5, -10.0); glScalef(2.5, 2.5, 2.5); building1(); glPopMatrix();

	GLfloat ambient_b2_1[] = { 0.25 , 0.21 , 0.32 , 1.0 }; GLfloat diffues_b2_1[] = { 0.12 , 0.70, 0.9, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2_1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2_1); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef((GLfloat)35.3, -3.0, (GLfloat)-5.5);  glScalef(2.5, 2.5, 2.5); building1(); glPopMatrix();
}
void drawBuilding2()
{
	GLfloat ambient_b2[] = { 0.72 , 0.21 , 0.32 , 1.0 }; GLfloat diffues_b2[] = { 0.92 , 0.15, 0.14, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(-8.5, (GLfloat)1.2, (GLfloat)-5.7);  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef((GLfloat)1.4, (GLfloat)1.2, (GLfloat)1.3); building2(); glPopMatrix();

	GLfloat ambient_b2_1[] = { 0.25 , 0.21 , 0.32 , 1.0 }; GLfloat diffues_b2_1[] = { 0.12 , 0.70, 0.9, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2_1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2_1); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(-6.0, (GLfloat)2.9, (GLfloat)-9.6);  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef((GLfloat)1.2, (GLfloat)1.6, (GLfloat)1); building2(); glPopMatrix();

	GLfloat ambient_b2_2[] = { 0.25 , 0.91 , 0.32 , 1.0 }; GLfloat diffues_b2_2[] = { 0.12 , 0.90, 0.3, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2_2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2_2); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(8.0, (GLfloat)3.3, (GLfloat)-18.6); glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(1, (GLfloat)1.9, (GLfloat)1.3); building2(); glPopMatrix();
	glPushMatrix(); glTranslatef(8.0, 1.7, (GLfloat)-13.6);			  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(1, (GLfloat)1.5, (GLfloat)1.5); building2(); glPopMatrix();


	GLfloat ambient_b2_3[] = { 0.25 , 0.71 , 0.52 , 1.0 }; GLfloat diffues_b2_3[] = { 0.12 , 0.70, 0.7, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2_3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2_3); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef((GLfloat)17.3, 2.0, (GLfloat)-5.5);  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(1, (GLfloat)1.4, (GLfloat)1.8); building2(); glPopMatrix(); // 은행 
	glPushMatrix(); glTranslatef(17.5, (GLfloat)5, (GLfloat)-18.6);  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(1, (GLfloat)2.2, (GLfloat)1.3); building2(); glPopMatrix();
	glPushMatrix(); glTranslatef(15.0, (GLfloat)5, (GLfloat)-15.6);  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(1, (GLfloat)2.2, (GLfloat)1.3); building2(); glPopMatrix();

	GLfloat ambient_b2_4[] = { 0.85 , 0.71 , 0.22 , 1.0 }; GLfloat diffues_b2_4[] = { 0.82 , 0.70, 0.1, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2_4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2_4); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(24.0, 9.0, (GLfloat)-12.6);		  glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(3, 3, (GLfloat)3);	  building2(); glPopMatrix();	// 은행 뒤
}
void drawChurch()
{
	GLfloat ambient_ch[] = { 0.52 , 0.51 , 0.22 , 1.0 };
	GLfloat diffues_ch[] = { 0.72 , 0.45, 0.94, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_ch);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_ch);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(-23.0, -1.0, 20.0); glRotatef(-90, 0.0, 1.0, 0.0); glScalef(3, 2, 2); church(); glPopMatrix();
}
void drawSchool()
{
	GLfloat ambient_b2[] = { 0.82 , 0.11 , 0.02 , 1.0 };
	GLfloat diffues_b2[] = { 0.92 , 0.15, 0.14, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_b2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_b2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(-29.5, -1.0, 20.0); glRotatef(180, 0.0, 1.0, 0.0); glScalef(2, 3, 2); school(); glPopMatrix();
}
void drawHospital()
{
	glPushMatrix(); glTranslatef((GLfloat)12.3, (GLfloat)1.7, (GLfloat)-10.5); glRotatef(180.0, 0.0, 1.0, 0.0); glScalef(1, (GLfloat)2.2, (GLfloat)1.9); hospital(); glPopMatrix();
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