#include <stdio.h>     
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define WWIDTH 640 //ширина начального экрана
#define WHEIGHT 400 //высота начального экрана
#define DCOUNT 40 //количество капель

const float PI = 3.14159265358979f;
unsigned int wWidth; //переменная нынешней ширины экрана
unsigned int wHeight; //переменная нынешней высоты экрана

//структура капель
struct drop{
	int x;
	int y;
};
typedef struct drop DROP;
DROP drops[DCOUNT];

//Нахождение минимального значения
float Min(float a, float b)
{
	return (a > b ? b : a);
}

// функция рисования
void Display()
{
	//небо и земля
	glBegin(GL_QUADS);
		glColor3f(0.5, 0.3, 0.0); //коричневый
		glVertex2f(0.0, 0.0);
		glVertex2f(wWidth, 0.0);
		glVertex2f(wWidth, wHeight * 0.1);
		glVertex2f(0.0, wHeight * 0.1);
		glColor3f(0.5, 0.78, 1.0); //небесный
		glVertex2f(0.0, wHeight * 0.1);
		glVertex2f(wWidth, wHeight * 0.1);
		glVertex2f(wWidth, wHeight);
		glVertex2f(0.0, wHeight);
	glEnd();
	//линия деревьев
    glBegin(GL_QUADS);
        glColor3f(0.24, 0.66, 0.24); //травяной
        for(int i = 0, j = 0; i <= wWidth; i += 5, ++j)
        {
            glVertex2f(i, wHeight * 0.1);
            glVertex2f(i, wHeight * 0.75 + wHeight * 0.07 * sin(0.18 * j));
            glVertex2f(i + 5.0, wHeight * 0.75 + wHeight * 0.07 * sin(0.18 * (j + 1)));
            glVertex2f(i + 5.0, wHeight * 0.1);
        }
    glEnd();
	//Cолнце
	glBegin(GL_POLYGON); 
		glColor3f(1.0, 1.0, 0.0); //желтый
		for(float R = Min(wWidth * 0.03125, wHeight * 0.05), i = 0; i <= 2 * PI; i += 0.05)
		{
			glVertex2f(R * cos(i) + wWidth * 0.905, R * sin(i) + wHeight * 0.90);
		}
	glEnd();
	//дом, стена
	glBegin(GL_QUADS);
		glColor3f(0.74, 0.74, 0.74); //светло-серый
		glVertex2f(wWidth * 0.6, wHeight * 0.075);
		glVertex2f(wWidth * 0.78, wHeight * 0.075);
		glVertex2f(wWidth * 0.78, wHeight * 0.3);
		glVertex2f(wWidth * 0.6, wHeight * 0.3);
	glEnd();
	//дом, крыша
	glBegin(GL_TRIANGLES);
		glColor3f(0.54, 0.27, 0.21); //кирпичный
		glVertex2f(wWidth * 0.57, wHeight * 0.3);
		glVertex2f(wWidth * 0.81, wHeight * 0.3);
		glVertex2f(wWidth * 0.69, wHeight * 0.5);
	glEnd();
	//дом, окно (стекло)
	glBegin(GL_POLYGON);
		glColor3f(0.67, 0.80, 0.94); //бледно-васильковый
		glVertex2f(wWidth * 0.66, wHeight * 0.225);
		glVertex2f(wWidth * 0.72, wHeight * 0.225);
		glVertex2f(wWidth * 0.72, wHeight * 0.15);
		glVertex2f(wWidth * 0.66, wHeight * 0.15);
	glEnd();
	glLineWidth(2);
	//дом, окно (рама)
	glBegin(GL_LINE_LOOP);
		glColor3f(0.51, 0.3, 0.09); //медвежьего ушка
		glVertex2f(wWidth * 0.66, wHeight * 0.225);
		glVertex2f(wWidth * 0.72, wHeight * 0.225);
		glVertex2f(wWidth * 0.72, wHeight * 0.15);
		glVertex2f(wWidth * 0.66, wHeight * 0.15);
	glEnd();
	//дом, окно (перегородки)
	glBegin(GL_LINES);
		glColor3f(0.51, 0.3, 0.09); //медвежьего ушка
		glVertex2f(wWidth * 0.69, wHeight * 0.225);
		glVertex2f(wWidth * 0.69, wHeight * 0.15);
		glVertex2f(wWidth * 0.72, wHeight * 0.1875);
		glVertex2f(wWidth * 0.66, wHeight * 0.1875);
	glEnd();
}

// функция для "перестройки" изображения при изменении размеров окна
void Reshape(int Width, int Height)
{
	wWidth = Width;
	wHeight = Height;
	for(int i = 0; i < DCOUNT; ++i)
	{
		drops[i].x = rand() % Width;
		drops[i].y = rand() % Height;
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
} 

void Rainy(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);
	Display();
	glLineWidth(3);
	//дождь
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
	glFlush();
	glutTimerFunc(50, Rainy, 0);
}

// функция инициализации
void init() 
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

// главная функция
int main(int argc, char **argv)
{
	wWidth = WWIDTH;
	wHeight = WHEIGHT;
	srand(time(NULL));
	for(int i = 0; i < DCOUNT; ++i)
	{
		drops[i].x = rand() % WWIDTH;
		drops[i].y = rand() % WHEIGHT;
	}
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(WWIDTH, WHEIGHT);
	glutCreateWindow("Main window");
	init();
    glutDisplayFunc(Display);
 	glutReshapeFunc(Reshape);
	glutTimerFunc(100, Rainy, 0);
	glutMainLoop();
	return 0;
}