#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define INIT_WIN_X 400
#define INIT_WIN_Y 400

float xRot = 0.0f;
float yRot = 0.0f;

void Draw() {
	glViewport(0, 0, 400, 400);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	
	glPushMatrix();
	glLoadIdentity();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glutSolidTeapot(0.5);
	glPopMatrix();
	glFlush();
}

void MyMouseClick(int Button, int State, int X, int Y)
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		xRot = X;
		yRot = Y;
	}
	glutPostRedisplay();
}

void MyMouseMove(int X, int Y) {
	xRot = X;
	yRot = Y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(INIT_WIN_X, INIT_WIN_Y);
	glutInitWindowPosition(0,0);
	glutCreateWindow("TeaPot 돌리기");

	glutDisplayFunc(Draw);
	
	glutMotionFunc(MyMouseMove);
	glutMainLoop();

	return 0;
}