#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define INIT_WIN_X 800
#define INIT_WIN_Y 800

GLfloat inner_radius = 0.2f;
GLfloat outer_radius = 0.5f;
GLfloat Delta = 0.0;
GLfloat scale_factor = 0.0001f;
GLint sides = 12;
GLint rings = 24;

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 1.0);
	glutWireTorus(inner_radius, outer_radius, sides, rings);
	glFlush();
}

void MyTimer(int Value) {
	if (Delta < 1.0f) {
		Delta = Delta + 0.01;
		glScalef(1.001, 1.0, 1.0);
	}
	else {
		Delta = 0.0;
		glScalef(0.9, 1.0, 1.0);
	}
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

void MyReshape(int NewWidth, int NewHeight)
{
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)INIT_WIN_X;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)INIT_WIN_Y;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor, -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
	glRotated(70, .3, .3, .3);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL TEST");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(Draw);
	glutTimerFunc(10, MyTimer, 1);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	return 0;
}