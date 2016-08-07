#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<GLAUX.h>

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);				 // black clear color, opaque window
	glColor4f(1.0, 1.0, 1.0, 1);					     // white
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0, 1.0, 500.0);		 // 각도~ 45도로 잡겠다 내가 보는 방향. 
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	glPushMatrix();
	glTranslatef(-3.0, 0.0, 0.0);

	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 1, 1);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 1.0);		// 정면
	glVertex3f(1.0, -1.0, 1.0);

	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, -1.0);		// 오른쪽
	glVertex3f(1.0, -1.0, 1.0);

	glVertex3f(0.0, 1.0, 0.0);		// 왼쪽
	glVertex3f(0.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glVertex3f(0.0, -1.0, -1.0);	// 밑면
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 0.0, 0.0);
	glBegin(GL_QUADS); // 큐브
	glColor4f(1, 1, 1, 1);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);		// 정면
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, -1.0, 1.0);

	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);		// 오른쪽면
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);		// 왼쪽면
	glVertex3f(-1.0, -1.0, 1.0);

	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);		// 윗면
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);

	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);		// 뒷면
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, -1.0);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);		// 밑면
	glVertex3f(-1.0, -1.0, 1.0);

	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
void mouseclick(int button, int state, int x, int y)
{
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

	glutMainLoop();
}