#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<GLAUX.h>

#define PI 3.1415927
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
int train_transing = 0;

bool flag_trans = false;
bool f1_flag = false;
bool f2_flag = false;
bool f3_flag = false;
bool f4_flag = false;
bool f5_flag = false;
bool f6_flag = false;
bool f7_flag = false;
bool f8_flag = false;
bool f9_flag = false;
bool f10_flag = false;
bool f11_flag = false;
bool f12_flag = false;

GLfloat train_t = 0;
GLfloat zoom = 10;
GLfloat flag = 0;
GLfloat fog_density = 0;

bool near_linear = false;
GLuint textures[25];

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
GLfloat fogColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
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
AUX_RGBImageRec *LoadBMPFile(char *filename)
{
	FILE *hFile = NULL;

	if (!filename) return NULL;

	hFile = fopen(filename, "r");

	if (hFile) {
		fclose(hFile);
		return auxDIBImageLoad(filename);
	}

	return NULL;
}

int LoadGLTextures(GLint modify)									// Load Bitmaps And Convert To Textures
{
	int Status = FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[25];					// Create Storage Space For The Texture

	memset(TextureImage, 0, sizeof(void *) * 1);           	// Set The Pointer To NULL

	if (modify == 1)
	{
		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if ((TextureImage[0] = LoadBMPFile("road2.bmp")) &&
			(TextureImage[1] = LoadBMPFile("lightening.bmp")) &&
			(TextureImage[2] = LoadBMPFile("power.bmp")) &&
			(TextureImage[3] = LoadBMPFile("building2.bmp")) &&
			(TextureImage[3] = LoadBMPFile("building2.bmp")) &&
			(TextureImage[4] = LoadBMPFile("building_surface.bmp")) &&
			(TextureImage[5] = LoadBMPFile("building_surface2.bmp")) &&
			(TextureImage[6] = LoadBMPFile("hospital.bmp")) &&
			(TextureImage[7] = LoadBMPFile("cityhall.bmp")) &&
			(TextureImage[8] = LoadBMPFile("church.bmp")) &&
			(TextureImage[9] = LoadBMPFile("school.bmp")) &&
			(TextureImage[10] = LoadBMPFile("school_surface.bmp")) &&
			(TextureImage[11] = LoadBMPFile("police2.bmp")) &&
			(TextureImage[12] = LoadBMPFile("police1.bmp")) &&
			(TextureImage[13] = LoadBMPFile("police3.bmp")) &&
			(TextureImage[14] = LoadBMPFile("train.bmp")) &&
			(TextureImage[15] = LoadBMPFile("door2.bmp")) &&
			(TextureImage[16] = LoadBMPFile("door3.bmp")) &&
			(TextureImage[17] = LoadBMPFile("cupang.bmp")) &&
			(TextureImage[18] = LoadBMPFile("hotel_front.bmp")) &&
			(TextureImage[19] = LoadBMPFile("hotel_up.bmp")))
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures(20, &textures[0]);					// Create The Texture
			for (int i = 0; i<20; i++)
			{
				// Typical Texture Generation Using Data From The Bitmap
				glBindTexture(GL_TEXTURE_2D, textures[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
		}
		for (int i = 0; i<20; i++)
		{
			if (TextureImage[i])									// If Texture Exists
			{
				if (TextureImage[i]->data)							// If Texture Image Exists		
					free(TextureImage[i]->data);					// Free The Texture Image Memory
				free(TextureImage[i]);								// Free The Image Structure
			}
		}

		if ((TextureImage[16] = LoadBMPFile("block.bmp")))
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures(1, &textures[16]);
			glBindTexture(GL_TEXTURE_2D, textures[16]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 10, 10, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[16]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		if (TextureImage[16])									// If Texture Exists
		{
			if (TextureImage[16]->data)							// If Texture Image Exists		
				free(TextureImage[16]->data);					// Free The Texture Image Memory
			free(TextureImage[16]);								// Free The Image Structure
		}
		return Status;										// Return The Status
	}
	else
	{
		if ((TextureImage[0] = LoadBMPFile("road2.bmp")) &&
			(TextureImage[1] = LoadBMPFile("lightening.bmp")) &&
			(TextureImage[2] = LoadBMPFile("power.bmp")) &&
			(TextureImage[3] = LoadBMPFile("building2.bmp")) &&
			(TextureImage[3] = LoadBMPFile("building2.bmp")) &&
			(TextureImage[4] = LoadBMPFile("building_surface.bmp")) &&
			(TextureImage[5] = LoadBMPFile("building_surface2.bmp")) &&
			(TextureImage[6] = LoadBMPFile("hospital.bmp")) &&
			(TextureImage[7] = LoadBMPFile("cityhall.bmp")) &&
			(TextureImage[8] = LoadBMPFile("church.bmp")) &&
			(TextureImage[9] = LoadBMPFile("school.bmp")) &&
			(TextureImage[10] = LoadBMPFile("school_surface.bmp")) &&
			(TextureImage[11] = LoadBMPFile("police2.bmp")) &&
			(TextureImage[12] = LoadBMPFile("police1.bmp")) &&
			(TextureImage[13] = LoadBMPFile("police3.bmp")) &&
			(TextureImage[14] = LoadBMPFile("train.bmp")) &&
			(TextureImage[15] = LoadBMPFile("door2.bmp")) &&
			(TextureImage[16] = LoadBMPFile("door3.bmp")) &&
			(TextureImage[17] = LoadBMPFile("cupang.bmp")) &&
			(TextureImage[18] = LoadBMPFile("hotel_front.bmp")) &&
			(TextureImage[19] = LoadBMPFile("hotel_up.bmp")))
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures(20, &textures[0]);					// Create The Texture
			for (int i = 0; i<20; i++)
			{
				// Typical Texture Generation Using Data From The Bitmap
				glBindTexture(GL_TEXTURE_2D, textures[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
		}
		for (int i = 0; i<20; i++)
		{
			if (TextureImage[i])									// If Texture Exists
			{
				if (TextureImage[i]->data)							// If Texture Image Exists		
					free(TextureImage[i]->data);					// Free The Texture Image Memory
				free(TextureImage[i]);								// Free The Image Structure
			}
		}

		if ((TextureImage[16] = LoadBMPFile("block.bmp")))
		{
			Status = TRUE;									// Set The Status To TRUE

			glGenTextures(1, &textures[16]);
			glBindTexture(GL_TEXTURE_2D, textures[16]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, 10, 10, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[16]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		if (TextureImage[16])									// If Texture Exists
		{
			if (TextureImage[16]->data)							// If Texture Image Exists		
				free(TextureImage[16]->data);					// Free The Texture Image Memory
			free(TextureImage[16]);								// Free The Image Structure
		}
		return Status;										// Return The Status
	}
}

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

int init()
{
	Initlight();

	if (!LoadGLTextures(0))								// Jump To Texture Loading Routine ( NEW )
		return FALSE;									// If Texture Didn't Load Return FALSE

	glFogi(GL_FOG_MODE, GL_EXP); // GL_LINEAR, GL_EXP, GL_EXP2
	glFogfv(GL_FOG_COLOR, fogColor);
	glHint(GL_FOG_HINT, GL_NICEST);
	glEnable(GL_FOG);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMatrixMode(GL_PROJECTION);
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
void cityhall()
{
	drawCube(2.5, 2.0, 1, 5, 7);
	glPushMatrix(); glTranslatef(3.5, (GLfloat)-1.75, (GLfloat)0);  glRotatef(-90.0, 1.0, 0.0, 0.0); glScalef(1, 1, 5.5);    cylinder(0.9, 0.9, 0.9);            glPopMatrix();//(1,1,2.3);
	glPushMatrix(); glTranslatef(0, (GLfloat)-1.3, (GLfloat)2.2); glRotatef(90.0, 0.0, 1.0, 0.0);          drawCube(0.6, 0.05, (GLfloat)1.7, 4, 5.5);  glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-1, (GLfloat)-2.7, (GLfloat)6);  glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);         glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-0.4, (GLfloat)-2.7, (GLfloat)6); glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);         glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.2, (GLfloat)-2.7, (GLfloat)6); glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);         glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.8, (GLfloat)-2.7, (GLfloat)6); glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);         glPopMatrix();
}
void policeOffice()
{
	GLfloat ambient_p[] = { 0.92 , 0.99, 0.99 , 1.0 }; GLfloat diffues_p[] = { 0.92 , 0.95, 0.94, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_p);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_p); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);

	drawCube(1, 1, (GLfloat)1.2, 4, 12);

	GLfloat ambient_po[] = { 0.02 , 0.01 , 0.92 , 1.0 };
	GLfloat diffues_po[] = { 0.02 , 0.05, 0.94, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_po);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_po);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(0, (GLfloat)2.03, 0); drawCube(1, 0.8, 1.0, 11, 11); glPopMatrix();

	GLfloat ambient_p1[] = { 0.92 , 0.99, 0.99 , 1.0 }; GLfloat diffues_p1[] = { 0.92 , 0.95, 0.94, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_p1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_p1); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(0, (GLfloat)3.5, 0); drawCube(1, 0.8, (GLfloat)0.8, 4, 13);        glPopMatrix();

	GLfloat ambient_po1[] = { 0.02 , 0.01 , 0.92 , 1.0 };
	GLfloat diffues_po1[] = { 0.02 , 0.05, 0.94, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_po1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_po1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(-2, (GLfloat)0.7, 1);  glRotatef(90.0, 1.0, 0.0, 0.0);  drawCube(0.05, 0.05, (GLfloat)2, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(-2.5, (GLfloat)0.7, 1); glRotatef(90.0, 1.0, 0.0, 0.0);  drawCube(0.05, 0.05, (GLfloat)2, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef(-0.6, (GLfloat)-0.15, 1.5);  glRotatef(90.0, 0.0, 1.0, 0.0); drawCube(0.5, 0.1, (GLfloat)0.5, 4, 4);  glPopMatrix();
}
void hotel(double x, double y, GLfloat size)
{
	glShadeModel(GL_SMOOTH);
	glPushMatrix();
	glScalef((GLfloat)x, (GLfloat)y, 1.0f);
	polygon_hotel(0, 10, 19, 9, size, 2, 4); polygon_hotel(4, 14, 15, 5, size, 2, 4);
	polygon_hotel(0, 1, 9, 0, size, 1, 19);   polygon_hotel(1, 8, 9, 0, size, 1, 19); polygon_hotel(1, 7, 8, 0, size, 1, 19); polygon_hotel(1, 2, 7, 0, size, 1, 19);
	polygon_hotel(2, 6, 7, 0, size, 1, 19);   polygon_hotel(2, 3, 6, 0, size, 1, 19); polygon_hotel(3, 4, 6, 0, size, 1, 19); polygon_hotel(4, 5, 6, 0, size, 1, 19); // 윗면 삼각형으로 그리기.
	polygon_hotel(0, 10, 11, 1, size, 2, 18);   polygon_hotel(1, 11, 12, 2, size, 2, 18); polygon_hotel(2, 12, 13, 3, size, 2, 18); polygon_hotel(3, 13, 14, 4, size, 2, 18); // 앞면
	polygon_hotel(19, 9, 8, 18, size, 2, 4); polygon_hotel(18, 8, 7, 17, size, 2, 4); polygon_hotel(17, 7, 6, 16, size, 2, 4); polygon_hotel(16, 6, 5, 15, size, 2, 4); // 뒷면
	polygon_hotel(10, 19, 18, 11, size, 2, 4); polygon_hotel(11, 18, 17, 12, size, 2, 4); polygon_hotel(12, 17, 16, 13, size, 2, 4); polygon_hotel(13, 16, 15, 14, size, 2, 4); // 밑면
	glPopMatrix();
}
void car()
{
	drawCube(2.0, 1.0, 0.5, 4, 4);
	glPushMatrix(); glTranslatef(0, (GLfloat)0.95, 0.0); drawSchoolroof(1.3, 1.0, (GLfloat)0.45, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-0.4, (GLfloat)-0.8, (GLfloat)0.2);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.4, (GLfloat)-0.8, (GLfloat)0.2);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-0.4, (GLfloat)-0.8, (GLfloat)-0.4);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.4, (GLfloat)-0.8, (GLfloat)-0.4);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
}
void truck()
{
	glPushMatrix();	glRotatef(90.0, 0.0, 0.0, 1.0); drawSchoolroof(1, 0.7, (GLfloat)0.6, 4);    glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.6, (GLfloat)0, (GLfloat)0);		glRotatef(90.0, 0.0, 0.0, 1.0); drawCube(0.1, 2, (GLfloat)0.1, 4, 1); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.5, (GLfloat)0.2, (GLfloat)0);	drawCube_train(1.5, 1.3, (GLfloat)0.6, 4, 17); glPopMatrix();		// 화물
	glPushMatrix(); glTranslatef((GLfloat)2, (GLfloat)-0.8, (GLfloat)0.2);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();	//바퀴 4개
	glPushMatrix(); glTranslatef((GLfloat)1, (GLfloat)-0.8, (GLfloat)0.2);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)2, (GLfloat)-0.8, (GLfloat)-0.4);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1, (GLfloat)-0.8, (GLfloat)-0.4);	draw_Cylinder((GLfloat)0.3, (GLfloat)0.3); glPopMatrix();
}
void train()
{
	glPushMatrix();	glTranslatef((GLfloat)3.7, (GLfloat)2.5, (GLfloat)0); glRotatef(90.0, 0.0, 0.0, 1.0);	 drawSchoolroof(1, 0.7, (GLfloat)0.6, 4);  glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)1.9, (GLfloat)0, (GLfloat)0); drawCube_train(2.5, 1, (GLfloat)0.6, 4, 14);		 glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)3.5, (GLfloat)0, (GLfloat)0); glRotatef(90.0, 0.0, 0.0, 1.0);	 drawCube(0.1, 2, (GLfloat)0.1, 4, 1); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)5.1, (GLfloat)0, (GLfloat)0); drawCube_train(2.5, 1, (GLfloat)0.6, 4, 14);		 glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)6.7, (GLfloat)0, (GLfloat)0); glRotatef(90.0, 0.0, 0.0, 1.0);	 drawCube(0.1, 2, (GLfloat)0.1, 4, 1); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)8.3, (GLfloat)0, (GLfloat)0); drawCube_train(2.5, 1, (GLfloat)0.6, 4, 14);		 glPopMatrix();
}
void bridge()
{
	drawCube(30, 0.8, (GLfloat)0.5, 4, 4);
	glPushMatrix(); glTranslatef((GLfloat)-1.9, (GLfloat)-1.3, (GLfloat)0); drawCube(1, 2, (GLfloat)0.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)3.9, (GLfloat)-1.3, (GLfloat)0); drawCube(1, 2, (GLfloat)0.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)8.9, (GLfloat)-1.3, (GLfloat)0); drawCube(1, 2, (GLfloat)0.5, 4, 4); glPopMatrix();
}
void tree()
{

	GLfloat ambient_tree_1[] = { 0.02 , 0.91 , 0.02 , 1.0 }; GLfloat diffues_tree_1[] = { 0.12 , 0.95, 0.14, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_tree_1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_tree_1); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef((GLfloat)-0.6, (GLfloat)2.3, (GLfloat)0.5); glRotatef(180.0, 1.0, 0.0, 0.0); draw_Cylinder((GLfloat)0.7, (GLfloat)0.7); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.6, (GLfloat)2.3, (GLfloat)0.5);  glRotatef(180.0, 1.0, 0.0, 0.0); draw_Cylinder((GLfloat)0.7, (GLfloat)0.7); glPopMatrix();
	glPushMatrix(); glTranslatef(0, (GLfloat)1.8, (GLfloat)0.5);			 glRotatef(180.0, 1.0, 0.0, 0.0); draw_Cylinder((GLfloat)0.7, (GLfloat)0.7); glPopMatrix();
	glPushMatrix(); glTranslatef(0, (GLfloat)3, (GLfloat)0.5);				 glRotatef(180.0, 1.0, 0.0, 0.0); draw_Cylinder((GLfloat)0.7, (GLfloat)0.7); glPopMatrix();

	GLfloat ambient_tree[] = { 0.62 , 0.21 , 0.02 , 1.0 }; GLfloat diffues_tree[] = { 0.62 , 0.35, 0.14, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_tree);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_tree); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glScalef((GLfloat)0.7, (GLfloat)1.7, 1);					 glRotatef(90.0, 1.0, 0.0, 0.0);  drawCube(0.1, 0.1, 1, 4, 4); glPopMatrix();
}
void house()
{
	GLfloat ambient_ho[] = { 0.82 , 0.81 , 0.02 , 1.0 }; GLfloat diffues_ho[] = { 0.92 , 0.85, 0.14, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_ho);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_ho); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(0.0, (GLfloat)0, 0.0); glRotatef(-90.0, 0.0, 1.0, 0.0);  drawCube(1, 1.0, 1.0, 16, 15); glPopMatrix();

	GLfloat ambient_roof[] = { 0.92 , 0.11 , 0.02 , 1.0 }; GLfloat diffues_roof[] = { 0.92 , 0.05, 0.14, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_roof);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_roof); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(0.0, (GLfloat)1.2, 0.0); drawPoly(0.75, 0.5, 1.5); glPopMatrix();
	glPushMatrix(); glTranslatef(0.0, (GLfloat)1.2, 0.0); glRotatef(180.0, 0.0, 1.0, 0.0); drawPoly(0.75, 0.5, 1.5); glPopMatrix();
}
void crossload()
{
	GLfloat ambient_car2[] = { 1 , 1 , 1 , 1.0 }; GLfloat diffues_car2[] = { 1 , 1, 1, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_car2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_car2); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(-3, -8, 0.0); glScalef(1.3, 0.1, 0.5); glRotatef(-90, 1, 0, 0); drawCube(1, 1, 1, 4, 4); glPopMatrix();
}
void road()
{
	GLfloat ambient_road[] = { 0.2 , 0.2 , 0.2 , 1.0 }; GLfloat diffues_road[] = { .1 , .1, .1, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_road);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_road); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(-2.2, -10, 4.5); glScalef(40, 0.1, 6); drawCube(1, 1, 1, 0, 0); glPopMatrix();
	glPushMatrix();   glTranslatef(-5, -10, -18.0); glRotatef(90, 0, 1, 0); glScalef(16.5, 0.1, 4.2);  drawCube(1, 1, 1, 0, 0); glPopMatrix();
	glPushMatrix();   glTranslatef(15, -10, 28.0); glRotatef(90, 0, 1, 0); glScalef(17.5, 0.1, 4.2);  drawCube(1, 1, 1, 0, 0); glPopMatrix();
	glPushMatrix();   glTranslatef(-22, -10, 28.0); glRotatef(90, 0, 1, 0); glScalef(17.5, 0.1, 3.2);  drawCube(1, 1, 1, 0, 0); glPopMatrix();
}
void field()
{
	glPushMatrix(); glTranslatef(-6.0, -2.0, 2.0); glScalef(1, 1, 0.05); drawCube(40, 40, 1, 4, 1); glPopMatrix();
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
void drawCityhall_Policeoffice()
{
	GLfloat ambient_city[] = { 0.92 , 0.71 , 0.22 , 1.0 }; GLfloat diffues_city[] = { 0.92 , 0.75, 0.24, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_city);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_city); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(14.5, 1.0, 25.0);   glRotatef(-90, 0.0, 1.0, 0.0); glScalef(2, 2.5, 2); cityhall(); glPopMatrix();

	GLfloat ambient_po[] = { 0.02 , 0.01 , 0.92 , 1.0 };
	GLfloat diffues_po[] = { 0.02 , 0.05, 0.94, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_po);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_po);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(14.5, -1.0, 40.0);   glRotatef(-90, 0.0, 1.0, 0.0); glScalef(2, 2.5, 2); policeOffice(); glPopMatrix();
}
void drawHotelEntrance()
{
	GLfloat ambient_hotel[] = { 0.52 , 0.81 , 0.92 , 1.0 }; GLfloat diffues_hotel[] = { 0.52 , 0.85, 0.94, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_hotel);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_hotel); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);

	glPushMatrix(); glTranslatef(0, (GLfloat)-1.3, (GLfloat)1.6); glRotatef(90.0, 0.0, 1.0, 0.0);			 drawCube(0.6, 0.05, (GLfloat)1.7, 4, 1);  glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-1, (GLfloat)-2.7, (GLfloat)5.5);  glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);			glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-0.4, (GLfloat)-2.7, (GLfloat)5.5); glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);			glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.2, (GLfloat)-2.7, (GLfloat)5.5); glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);			glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)0.8, (GLfloat)-2.7, (GLfloat)5.5); glRotatef(90.0, 0.0, 1.0, 0.0); drawCylinder(0.1, 0.1, 0.5);			glPopMatrix();
}
void drawHotel()
{
	GLfloat ambient_hotel[] = { 0.52 , 0.81 , 0.92 , 1.0 }; GLfloat diffues_hotel[] = { 0.52 , 0.85, 0.94, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_hotel);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_hotel); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(40.0, 0, 30.0); glRotatef(-90, 0.0, 1.0, 0.0); glScalef((GLfloat)1.3, (GLfloat)1.3, (GLfloat)1.3); hotel(2, 2, 2); glPopMatrix();
	glPushMatrix(); glTranslatef(40.0, -3, 30.0); glRotatef(-90, 0.0, 1.0, 0.0); drawHotelEntrance(); glPopMatrix();
}
void drawCar()
{
	GLfloat ambient_car[] = { 0.22 , 0.21 , 0.22 , 1.0 }; GLfloat diffues_car[] = { 0.22 , 0.25, 0.24, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_car);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_car); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(-25.0, -4.0, 28.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-25.0, -4.0, 31.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-25.0, -4.0, 34.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-25.0, -4.0, 37.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-21.0, -4.0, 37.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-21.0, -4.0, 34.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-21.0, -4.0, 31.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-30.0, 0.0, 1.0, 0.0); car(); glPopMatrix();

	GLfloat ambient_car2[] = { 0.92 , 0.21 , 0.22 , 1.0 }; GLfloat diffues_car2[] = { 0.92 , 0.25, 0.24, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_car2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_car2); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef(-23.0, -4.0, 7.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8);  car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-23.0, -4.0, 9.0);  glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8);  car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-23.0, -4.0, 11.0); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8);  car(); glPopMatrix();
	glPushMatrix(); glTranslatef(-20.0, -4.0, 11.0); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8);  car(); glPopMatrix();


	glPushMatrix(); glTranslatef(0.0, -4.0, 1.0); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(-90.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(15.0, -4.0, 11.0); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(12.0, -4.0, 9.0); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(37.0, -4.0, 9.5); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); car(); glPopMatrix();
	glPushMatrix(); glTranslatef(23.0, -4.0, 40); glScalef((GLfloat)1, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); car(); glPopMatrix();
}
void drawTruck()
{
	GLfloat ambient_car[] = { 0.99 , 0.99 , 0.92 , 1.0 }; GLfloat diffues_car[] = { 0.92 , 0.95, 0.94, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, diffues_car);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambient_car); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);

	glPushMatrix(); glTranslatef(-5.0, -4.0, 5.0); truck(); glPopMatrix();
	glPushMatrix(); glTranslatef(-5.0, -4.0, 3.0); truck(); glPopMatrix();
	glPushMatrix(); glTranslatef(25.0, -4.0, 3.0); truck(); glPopMatrix();
	glPushMatrix(); glTranslatef(20.0, -4.0, 40); glRotatef(90.0, 0.0, 1.0, 0.0); truck(); glPopMatrix();
}
void drawtrain()
{
	GLfloat ambient_car2[] = { 0.92 , 0.91 , 0.92 , 1.0 }; GLfloat diffues_car2[] = { 0.92 , 0.95, 0.74, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_car2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_car2); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix();   glTranslatef(-7.0, -2.5, 0.0); glScalef(1.8, 1, 1);   train(); glPopMatrix();
}
void drawbridge()
{
	GLfloat ambient_bridge[] = { 0.22 , 0.21 , 0.22 , 1.0 }; GLfloat diffues_bridge[] = { 0.22 , 0.25, 0.24, 1.0 }; glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_bridge);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffues_bridge); glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m); glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glPushMatrix(); glTranslatef((GLfloat)2, (GLfloat)-2, (GLfloat)0);	   drawCube(80, 0.8, (GLfloat)0.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)-15.9, (GLfloat)-3.3, (GLfloat)0); drawCube(1, 2, (GLfloat)0.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)10.9, (GLfloat)-3.3, (GLfloat)0); drawCube(1, 2, (GLfloat)0.5, 4, 4); glPopMatrix();
	glPushMatrix(); glTranslatef((GLfloat)38.9, (GLfloat)-3.3, (GLfloat)0); drawCube(1, 2, (GLfloat)0.5, 4, 4); glPopMatrix();
}
void drawHouse()
{
	glPushMatrix(); glTranslatef(38.0, -4.0, 16.0); glRotatef(90.0, 0.0, 1.0, 0.0); house(); glPopMatrix();
	glPushMatrix(); glTranslatef(38.0, -4.0, 20.0); glRotatef(90.0, 0.0, 1.0, 0.0); house(); glPopMatrix();
	glPushMatrix(); glTranslatef(34.0, -4.0, 16.0); glRotatef(90.0, 0.0, 1.0, 0.0); house(); glPopMatrix();
	glPushMatrix(); glTranslatef(34.0, -4.0, 20.0); glRotatef(90.0, 0.0, 1.0, 0.0); house(); glPopMatrix();
	glPushMatrix(); glTranslatef(30.0, -4.0, 16.0); glRotatef(90.0, 0.0, 1.0, 0.0); house(); glPopMatrix();
	glPushMatrix(); glTranslatef(30.0, -4.0, 20.0); glRotatef(90.0, 0.0, 1.0, 0.0); house(); glPopMatrix();
}
void drawTree()
{
	glPushMatrix();	glTranslatef(-23.0, -3.0, -10.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-24.0, -3.0, -3.0);  glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-8.5, -3.0, 16.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-5.5, -3.0, 16.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-2.5, -3.0, 16.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(0.5, -3.0, 16.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(0.5, -3.0, 20.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(3.5, -3.0, 17.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(6.5, -3.0, 17.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(9.5, -3.0, 17.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();

	glPushMatrix();	glTranslatef(6.5, -3.0, 40.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(3.5, -3.0, 40.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(0.5, -3.0, 40.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(0.5, -3.0, 37.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-3.5, -3.0, 39.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-6.5, -3.0, 38.5); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-9.5, -3.0, 38.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();

	glPushMatrix();	glTranslatef(-11.5, -3.0, 30.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(-11.5, -3.0, 25.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();


	glPushMatrix();	glTranslatef(32.0, -3.0, 14.5); glScalef((GLfloat)0.5, (GLfloat)0.5, (GLfloat)0.5); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(39.0, -3.0, 24.0); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
	glPushMatrix();	glTranslatef(40.0, -3.0, 14.5); glScalef((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8); glRotatef(90.0, 0.0, 1.0, 0.0); tree(); glPopMatrix();
}
void drawfield()
{
	GLfloat ambient[] = { 0.01 , 0.09 , 0.09 , 1.0 };
	GLfloat diffues[] = { 0.092 , 0.095, 0.092, 1.0 };
	GLfloat specular[] = { 1.00, 1.00, 1.00, 1.0 };
	GLfloat shine[] = { 25.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffues);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
	glTranslatef(0.0, -8.5, 0.0);
	glPushMatrix(); glTranslatef(10.0, 4.5, 10.0); glRotatef(90, 1, 0, 0); field(); glPopMatrix();
}
void drawcrossload()
{
	glPushMatrix(); glTranslatef(-6.0, 3.0, 2.0);  crossload(); glPopMatrix();
	glPushMatrix(); glTranslatef(-6.0, 3.0, 4.0);  crossload(); glPopMatrix();
	glPushMatrix(); glTranslatef(-6.0, 3.0, 6.0);  crossload(); glPopMatrix();
	glPushMatrix(); glTranslatef(-6.0, 3.0, 8.0);  crossload(); glPopMatrix();
	glPushMatrix(); glTranslatef(-6.0, 3.0, 10.0); crossload(); glPopMatrix();
}
void drawroad()
{
	glPushMatrix(); glTranslatef(6.0, 13.2, 2.0); road(); glPopMatrix();
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

	if (f1_flag == true)
		drawBuilding1();
	if (f2_flag == true)
	{
		drawBuilding2();
		drawHospital();
	}
	if (f3_flag == true)
		drawCityhall_Policeoffice();
	if (f4_flag == true)
	{
		drawChurch();
		drawSchool();
	}
	if (f5_flag == true)
	{
		drawCar();
		drawTruck();
	}
	if (f6_flag == true)
	{
		drawHotel();
		drawHouse();
	}
	if (f7_flag == true)
	{
		glPushMatrix(); glTranslatef(train_t, 0, 0.0); drawtrain(); glPopMatrix();
		drawTree();
		drawcrossload();
		drawbridge();
	}

	drawfield();
	drawroad();

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

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:  // F1 function key
		if (f1_flag == false)
			f1_flag = true;
		else
			f1_flag = false;
		break;
	case GLUT_KEY_F2:  // F2 function key
		if (f2_flag == false)
			f2_flag = true;
		else
			f2_flag = false;
		break;
	case GLUT_KEY_F3:  // F3 function key
		if (f3_flag == false)
			f3_flag = true;
		else
			f3_flag = false;
		break;
	case GLUT_KEY_F4:  // F4 function key
		if (f4_flag == false)
			f4_flag = true;
		else
			f4_flag = false;
		break;
	case GLUT_KEY_F5:  // F5 function key
		if (f5_flag == false)
			f5_flag = true;
		else
			f5_flag = false;
		break;
	case GLUT_KEY_F6:  // F6 function key
		if (f6_flag == false)
			f6_flag = true;
		else
			f6_flag = false;
		break;
	case GLUT_KEY_F7:  // F7 function key
		if (f7_flag == false)
			f7_flag = true;
		else
			f7_flag = false;
		break;
	case GLUT_KEY_F8:  // F8 function key
		if (f8_flag == false)
			f8_flag = true;
		else
			f8_flag = false;
		break;
	case GLUT_KEY_F9:  // F9 function key
		if (f9_flag == false)
			f9_flag = true;
		else
			f9_flag = false;
		break;
	case GLUT_KEY_F10:  // F10 function key
		if (f10_flag == false)
			f10_flag = true;
		else
			f10_flag = false;
		break;
	case GLUT_KEY_PAGE_UP:
		if (train_t > -30)
			train_t--;
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (train_t < 35)
			train_t++;
		break;


	}
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
	case 'f':
		if (fog_density > 1)
			fog_density = 1;
		fog_density += 0.02;

		break;
	case 'g':
		if (fog_density < 0)
			fog_density = 0;
		fog_density -= 0.02;
		break; 
	case 't':					// 전체 텍스처 in or out
		if (flag == 0)
		{
			glDisable(GL_TEXTURE_2D);
			flag = 1;
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
			flag = 0;
		}
		break;
	case 'm':
			if (near_linear == false)
			{
				LoadGLTextures(0);
				printf("%d", near_linear);
				near_linear = true;
			}
			else
			{
				LoadGLTextures(1);
				printf("%d", near_linear);
				near_linear = false;
			}
			break;
	case 'b':					// 전체 텍스처 in or out
		if (flag_trans == false)
		{
			glClearColor(0, 0, 0, 0.21);
			glEnable(GL_BLEND);
			flag_trans = true;
			break;
		}
		else
		{
			glClearColor(1, 1, 1, 1);
			glDisable(GL_BLEND);
			flag_trans = false;
			break;

		}
	case 'x':
		exit(0);
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
	glutSpecialFunc(specialKeys);

	glutMainLoop();
}