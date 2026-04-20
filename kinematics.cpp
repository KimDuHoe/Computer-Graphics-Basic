#include <GL/glut.h>
#include <GL/glut.h>

static float Base_Angle;
static float Lower_Arm_Angle;
static float Upper_Arm_angle;
GLUquadricObj* p;

void base(void)
{
	glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(0, -0.8, 0);
		glRotatef(-90, 1, 0, 0);
		glRotatef(Base_Angle, 0, 0, 1);
		gluCylinder(p, 0.4, 0.4, 0.3, 8, 5);
		glTranslatef(0, 0, -0.1);
		glColor3f(0.3, 0.4, 0.5);
	glPopMatrix();
}

void lower_arm(void)
{
	glPushMatrix();
		glColor3f(0, 1, 0);
		glRotatef(Base_Angle, 0, 1, 0);
		glTranslatef(0, -0.7, 0);
		glRotatef(Lower_Arm_Angle, 0, 0, 1);
		glTranslatef(0, 0.5, 0);
		glScalef(0.2, 1, 0.2);
		glutWireCube(1);
	glPopMatrix();
}

void upper_arm(void)
{
	glPushMatrix();
		glColor3f(0,0,1);
		glRotatef(Base_Angle, 0, 1, 0);
		glTranslatef(0, -0.7, 0);
		glRotatef(Lower_Arm_Angle, 0, 0, 1);
		glTranslatef(0, 1.0, 0);
		glRotatef(Upper_Arm_angle, 0, 0, 1);
		glTranslatef(0, 0.4, 0);
		glScalef(0.2, 0.8, 0.2);
		glutWireCube(1);
	glPopMatrix();
}

void Rendering(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);
	base();
	lower_arm();
	upper_arm();
	glutSwapBuffers();
}

void pressKeyboardKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': 
	case 'Q': Lower_Arm_Angle += 2;
		glutPostRedisplay();
		break;
	case 'a': 
	case 'A': Lower_Arm_Angle -= 2;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W': Upper_Arm_angle += 2;
		glutPostRedisplay();
		break;
	case 's':
	case 'S': Upper_Arm_angle -= 2;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void Init(void)
{
	p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_LINE);
	Base_Angle = 0;
	Lower_Arm_Angle = 0;
	Upper_Arm_angle = 0;
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Reshape(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0 * (float)w / (float)h, 2.0 * (float)w / (float)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Robot Arm");
	glutDisplayFunc(Rendering);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(pressKeyboardKey);
	Init();
	glutMainLoop();
}