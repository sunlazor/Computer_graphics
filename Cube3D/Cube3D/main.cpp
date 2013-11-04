#include <stdio.h>     
#include <GL/glut.h>


// функция рисования
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP); 
		glVertex2f(220.0, 300.0);
		glVertex2f(245.0, 325.0);
		glVertex2f(295.0, 270.0);
		glVertex2f(345.0, 340.0);
		glVertex2f(395.0, 300.0);
		glVertex2f(445.0, 420.0);
	glEnd();

	glFlush();
}

// функция для "перестройки" изображения при изменении размеров окна
void Reshape(int Width, int Height)
{
	if (Height == 0)
	{
		Height = 1;
	}
	
	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)Width, 0.0, (GLdouble)Height);

	display();
} 

// функция инициализации
void init() 
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

// главная функция
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow( "Main window" );
	init();
    glutDisplayFunc(display);
 	glutReshapeFunc(Reshape);
    printf("It's a test app.");
	glutMainLoop();

	return 0;
}

