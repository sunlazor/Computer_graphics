#include <stdio.h>     
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define STARTWIDTH 640 //������ ���������� ������
#define STARTHEIGHT 400 //������ ���������� ������
#define DCOUNT 40 //���������� ������

const float PI = 3.14159265358979f;
unsigned int wWidth; //���������� �������� ������ ������
unsigned int wHeight; //���������� �������� ������ ������

// ��������� � ������ ������
struct drop{
	int x;
	int y;
};
typedef struct drop DROP;
DROP drops[DCOUNT];

// ������� ������
GLfloat palette[] = 
{
	0.5,  0.3,  0.0,	// ����������
	0.5,  0.78, 1.0,	// ��������
	0.74, 0.74, 0.74, 	// ������-�����
	0.67, 0.80, 0.94, 	// ������-�����������
	0.51, 0.3,  0.09,  	// ���������� ����
	0.54, 0.27, 0.21 	// ���������
};

// ������ ������ ������
GLfloat colors[81];

// ������ ������������� ��������� ��� ���������
GLfloat vertexCoeff[] = 
{
	// �����
	0,    0,		// 0-1, ��� - ����
	1,    0,		// 2-3, ��� - �����
	0,    0.1,		// 4-5, ���� - ����
	1,    0.1,		// 6-7, ���� - �����
	// ����
	0,    0.1,		// 8-9, ��� - ����
	1,    0.1,		// 10-11, ��� - �����
	0,    1,		// 12-13, ���� - ����
	1,    1,		// 14-15, ���� - �����
	// ���
	0.6,  0.075,	// 16-17, ��� - ����
	0.78, 0.075,	// 18-19, ��� - �����
	0.6,  0.3,		// 20-21, ���� - ����
	0.78, 0.3,		// 22-23, ���� - �����
	// ����	
	0.66, 0.15,		// 24-25, ��� - ����
	0.72, 0.15,		// 26-27, ��� - �����
	0.66, 0.225,	// 28-29, ���� - ����
	0.72, 0.225,	// 30-31, ���� - �����
	// ����	
	0.66, 0.15,		// 32-33, ��� - ����
	0.72, 0.15,		// 34-35, ��� - �����
	0.72, 0.225,	// 36-37, ���� - �����
	0.66, 0.225,	// 38-39, ���� - ����
	// ������ http://www.oknacom.ru/faq/products/impost/
	0.69, 0.225,	// 40-41, ������������ - ����
	0.69, 0.15,		// 42-43, ������������ - ���
	0.66, 0.1875,	// 44-45, ��������������� - �����
	0.72, 0.1875,	// 46-47, ��������������� - ������
	// �����
	0.57, 0.3,		// 48-49, ����
	0.81, 0.3,		// 50-51, �����
	0.69, 0.5		// 52-53, �������
};

// ������ ������
GLfloat vertex[sizeof(vertexCoeff)/sizeof(vertexCoeff[0])];

// ������ �������� ������
GLushort indices[] = 
{
	// �����
	0,  1,  2,  3, 
	// ����
	4,  5,  6,  7,
	// ���
	8,  9,  10, 11,
	// ����
	12, 13, 14, 15,
	// ����
	16, 17, 18, 19,
	// ������
	20, 21, 22, 23,
	// ����� ����
	24, 25, 26
};

// ���������� ������������ ��������
float Min(float a, float b)
{
	return (a > b ? b : a);
}

// ������� ���������
void Display()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex);
	glColorPointer(3, GL_FLOAT, 0, colors);
	// ����� � ����
	glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_SHORT, indices);
	// ����� ��������
    glBegin(GL_QUADS);
        glColor3f(0.24, 0.66, 0.24); //��������
        for(int i = 0, j = 0; i <= wWidth; i += 5, ++j)
        {
            glVertex2f(i, wHeight * 0.1);
            glVertex2f(i, wHeight * 0.75 + wHeight * 0.07 * sin(0.18 * j));
            glVertex2f(i + 5.0, wHeight * 0.75 + wHeight * 0.07 * sin(0.18 * (j + 1)));
            glVertex2f(i + 5.0, wHeight * 0.1);
        }
    glEnd();
	// C�����
	glBegin(GL_POLYGON); 
		glColor3f(1.0, 1.0, 0.0); //������
		for(float R = Min(wWidth * 0.03125, wHeight * 0.05), i = 0; i <= 2 * PI; i += 0.05)
		{
			glVertex2f(R * cos(i) + wWidth * 0.905, R * sin(i) + wHeight * 0.90);
		}
	glEnd();
	// ��� � ����
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, &indices[8]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, &indices[12]);
	// ����
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, &indices[16]);
	// ������
	glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, &indices[20]);
	// �����
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, &indices[24]);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void Rainy(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Display();
	glLineWidth(3);
	//�����
	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0);
		for(int i = 0; i < DCOUNT; ++i)
		{
			if(drops[i].x < 0)
				drops[i].x = wWidth;
			if(drops[i].y < 0)
				drops[i].y = wHeight;
			glVertex2f(drops[i].x, drops[i].y);
			glVertex2f(drops[i].x + 10, drops[i].y + 10);
			drops[i].x -= 15;
			drops[i].y -= 15;
		}
	glEnd();
	if(value != 1) glutTimerFunc(80, Rainy, 0);
	glFlush();
}

// ������� ��� "�����������" ����������� ��� ��������� �������� ����
void Reshape(int Width, int Height)
{
	if(wWidth != Width) 
	{
		wWidth = Width;
		for(int i = 0; i < DCOUNT; ++i)
		{
			drops[i].x = rand() % wWidth;
		}
		for(int i = 0; i < sizeof(vertexCoeff)/sizeof(vertexCoeff[0]); i += 2)
		{
			vertex[i] = wWidth * vertexCoeff[i]; 
		}
	}
	if(wHeight != Height) 
	{
		wHeight = Height;
		for(int i = 0; i < DCOUNT; ++i)
		{
			drops[i].y = rand() % wHeight;
		}
		for(int i = 1; i < sizeof(vertexCoeff)/sizeof(vertexCoeff[0]); i += 2)
		{
			vertex[i] = wHeight * vertexCoeff[i]; 
		}
	}
	if (Height == 0)
	{
		Height = 1;
	}
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)Width, 0.0, (GLdouble)Height);
	Display();
	Rainy(1);
	glFlush();
}

// ������������� ������� ������ ������
void MakeResArrayColors()
{
	int maskForColors[] = { 4, 4, 4, 4, 8, 3 };
	int countVertex = 0;
	const unsigned short countColorChannel = 3;
	for(int i = 0; i < sizeof(maskForColors)/sizeof(maskForColors[0]); ++i)
	{
		for(int j = 0; j < maskForColors[i]; ++j)
		{
			for(int k = 0; k < countColorChannel; ++k)
			{
				colors[countVertex] = palette[i * countColorChannel + k];
				++countVertex;
			}
		}
	}
}

// ������������� ������� ������
void MakeScalableArrVrtxs()
{
	for(int i = 0; i < sizeof(vertexCoeff)/sizeof(vertexCoeff[0]); i += 2)
	{
		vertex[i] = wWidth * vertexCoeff[i]; 
		vertex[i + 1] = wHeight * vertexCoeff[i + 1]; 
	}
}

// ������� �������������
void init() 
{
	// ���������� ��������
	MakeScalableArrVrtxs();
	MakeResArrayColors();

	glClearColor(1.0, 1.0, 1.0, 1.0);
}

// ������� �������
int main(int argc, char **argv)
{
	wWidth = STARTWIDTH;
	wHeight = STARTHEIGHT;
	srand(time(NULL));
	for(int i = 0; i < DCOUNT; ++i)
	{
		drops[i].x = rand() % STARTWIDTH;
		drops[i].y = rand() % STARTHEIGHT;
	}
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(STARTWIDTH, STARTHEIGHT);
	glutCreateWindow("Main window");
	init();
    glutDisplayFunc(Display);
 	glutReshapeFunc(Reshape);
	glutTimerFunc(0, Rainy, 0);
	glutMainLoop();
	return 0;
}