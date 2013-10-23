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

static GLfloat color[] = 
{
	//0.5, 0.3, 0.0, //земля, коричневый
	//0.5, 0.3, 0.0, //земля, коричневый
	//0.5, 0.3, 0.0, //земля, коричневый
	//0.5, 0.3, 0.0, //земля, коричневый
	1, 0 ,0,
	0, 1 ,0,
	//0, 0 ,1,
	1, 0 ,0,
	0, 1 ,0,
	//0, 0 ,1,
	1, 0 ,0,
	0, 1 ,0,
	//0, 0 ,1,
	1, 0 ,0,
	0, 1 ,0,
	//0, 0 ,1,
	0.5, 0.78, 1.0, //небо, небесный
	0.5, 0.78, 1.0, //небо, небесный
	0.5, 0.78, 1.0, //небо, небесный
	0.5, 0.78, 1.0, //небо, небесный
	0.5, 0.78, 1.0, //небо, небесный
	0.5, 0.78, 1.0, //небо, небесный
	//0.74, 0.74, 0.74, //стена, светло-серый
	//0.74, 0.74, 0.74, //стена, светло-серый
	//0.67, 0.80, 0.94, //стекло, бледно-васильковый
	//0.67, 0.80, 0.94, //стекло, бледно-васильковый
	//0.54, 0.27, 0.21, //крыша, кирпичный
	//0.51, 0.3, 0.09, //рама, медвежьего ушка
	//0.51, 0.3, 0.09, //рама, медвежьего ушка
	//0.51, 0.3, 0.09 //рама, медвежьего ушка
};

GLfloat vertex[] = 
{
	0.0, 0.0, //0.нижний левый угол
	wWidth, 0.0, //1.нижний правый угол
	0.0, wHeight, //2. verh lev
	wWidth, wHeight, //3. verh prav
	//0.0, wHeight * 0.1, //4. land left
	//wWidth, wHeight * 0.1, //5. land right
	0.0, wHeight * 0.5, //4. land left
	wWidth, wHeight * 0.5, //5. land right
	wWidth * 0.6, wHeight * 0.075, //6. dom lev nizh
	wWidth * 0.78, wHeight * 0.075, //7. dom prav nizh
	wWidth * 0.78, wHeight * 0.3, //8. dom prav verh
	wWidth * 0.6, wHeight * 0.3, //9. dom lev verh
	wWidth * 0.57, wHeight * 0.3, //10. krisha lev
	wWidth * 0.81, wHeight * 0.3, //11. krisha prav
	wWidth * 0.69, wHeight * 0.5, //12. krisha verh
	wWidth * 0.66, wHeight * 0.225, //13. okno lev nizh
	wWidth * 0.72, wHeight * 0.225, //14. okno prav nizh
	wWidth * 0.72, wHeight * 0.15, //15. okno prav verh
	wWidth * 0.66, wHeight * 0.15, //16. okno lev verh
	wWidth * 0.66, wHeight * 0.225, //17. rama lev nizh
	wWidth * 0.72, wHeight * 0.225, //18. rama prav nizh
	wWidth * 0.72, wHeight * 0.15, //19. rama prav verh
	wWidth * 0.66, wHeight * 0.15, //20. rama lev verh
	wWidth * 0.69, wHeight * 0.225, //21. vert nizh
	wWidth * 0.69, wHeight * 0.15, //22. vert verh
	wWidth * 0.72, wHeight * 0.1875, //23. gor lev
	wWidth * 0.66, wHeight * 0.1875 //24. gor prav
};

//GLushort indices[] = 
//{
//	//земля
//	0, 1, 5,
//	0, 5, 4,
//	//небо
//	4, 5, 3,
//	4, 3, 2,
//	//дом, стена
//	6, 7, 8,
//	6, 8, 9,
//	//дом, окно
//	13, 14, 15,
//	13, 15, 16,
//	//дом, крыша
//	10, 11, 12,
//	//дом, рама окна
//	17, 18, 19, 20,
//	21, 22, 23, 24
//};

GLushort indices[] = 
{
	//земля
	0, 1, 4, 5, 
	//небо
	4, 5, 2, 3,
	//дом, стена
	6, 7, 8, 9,
	//дом, окно
	13, 14, 15, 16,
	//дом, крыша
	10, 11, 12,
	//дом, рама окна
	17, 18, 19, 20,
	21, 22, 
	23, 24
};

//Нахождение минимального значения
float Min(float a, float b)
{
	return (a > b ? b : a);
}

// функция рисования
void Display()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex);
	glColorPointer(3, GL_FLOAT, 0, color);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, indices);
	//glColorPointer(3, GL_FLOAT, 0, &color[6]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, &indices[4]);
	glFlush();
	//линия деревьев
 //   glBegin(GL_QUADS);
 //       glColor3f(0.24, 0.66, 0.24); //травяной
 //       for(int i = 0, j = 0; i <= wWidth; i += 5, ++j)
 //       {
 //           glVertex2f(i, wHeight * 0.1);
 //           glVertex2f(i, wHeight * 0.75 + wHeight * 0.07 * sin(0.18 * j));
 //           glVertex2f(i + 5.0, wHeight * 0.75 + wHeight * 0.07 * sin(0.18 * (j + 1)));
 //           glVertex2f(i + 5.0, wHeight * 0.1);
 //       }
 //   glEnd();
	////Cолнце
	//glBegin(GL_POLYGON); 
	//	glColor3f(1.0, 1.0, 0.0); //желтый
	//	for(float R = Min(wWidth * 0.03125, wHeight * 0.05), i = 0; i <= 2 * PI; i += 0.05)
	//	{
	//		glVertex2f(R * cos(i) + wWidth * 0.905, R * sin(i) + wHeight * 0.90);
	//	}
	//glEnd();
	////glFlush();
	//glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_SHORT, &indices[12]);
	//glFlush();
	//glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, &indices[27]);
	//glFlush();
	//glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, &indices[31]);
	//glFlush();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glFlush();
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
	if(1 != value)
		glutTimerFunc(50, Rainy, 0);
}

// функция для "перестройки" изображения при изменении размеров окна
void Reshape(int Width, int Height)
{
	wWidth = Width;
	wHeight = Height;
	//Пересчет вершин
	vertex[2] = wWidth;
	vertex[5] = wHeight;
	vertex[6] = wWidth;
	vertex[7] = wHeight;
	vertex[9] = wHeight * 0.5;//
	vertex[10] = wWidth;
	vertex[11] = wHeight * 0.5;//
	vertex[12] = wWidth * 0.6;
	vertex[13] = wHeight * 0.075;
	vertex[14] = wWidth * 0.78;
	vertex[15] = wHeight * 0.075;
	vertex[16] = wWidth * 0.78;
	vertex[17] = wHeight * 0.3;
	vertex[18] = wWidth * 0.6;
	vertex[19] = wHeight * 0.3;
	vertex[20] = wWidth * 0.57;
	vertex[21] = wHeight * 0.3;
	vertex[22] = wWidth * 0.81;
	vertex[23] = wHeight * 0.3;
	vertex[24] = wWidth * 0.69;
	vertex[25] = wHeight * 0.5;
	vertex[26] = wWidth * 0.66;
	vertex[27] = wHeight * 0.225;
	vertex[28] = wWidth * 0.72;
	vertex[29] = wHeight * 0.225;
	vertex[30] = wWidth * 0.72;
	vertex[31] = wHeight * 0.15;
	vertex[32] = wWidth * 0.66;
	vertex[33] = wHeight * 0.15;
	vertex[34] = wWidth * 0.66;
	vertex[35] = wHeight * 0.225;
	vertex[36] = wWidth * 0.72;
	vertex[37] = wHeight * 0.225;
	vertex[38] = wWidth * 0.72;
	vertex[39] = wHeight * 0.15;
	vertex[40] = wWidth * 0.66;
	vertex[41] = wHeight * 0.15;
	vertex[42] = wWidth * 0.69;
	vertex[43] = wHeight * 0.225;
	vertex[44] = wWidth * 0.69;
	vertex[45] = wHeight * 0.15;
	vertex[46] = wWidth * 0.72;
	vertex[47] = wHeight * 0.1875;
	vertex[48] = wWidth * 0.66;
	vertex[49] = wHeight * 0.1875;
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
	Rainy(1);
	glFlush();
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
	glutTimerFunc(0, Rainy, 0);
	glutMainLoop();
	return 0;
}