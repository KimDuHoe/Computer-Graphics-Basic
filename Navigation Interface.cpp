#include <GL/glut.h>
#include <GL/glut.h>
#include <math.h>

float x = 0.0, y = -5.0; 
float deltaMove = 0.0; 

float lx = 0.0, ly = 1.0; 
float angle = 0.0; 
float deltaAngle = 0.0; 

int isDragging = 0; 
int xDragStart = 0; 
int yDragStart = 0;

void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0, ratio, 0.1, 100.0); 
    glMatrixMode(GL_MODELVIEW); 
    glViewport(0, 0, w, h); 
}

void drawBox()
{
    glColor3f(1.0, 1.0, 1.0); 
    glPushMatrix();
    glutWireTeapot(2.0);
    glPopMatrix();
}

void update(void)
{
    if (deltaMove) { 
        x += deltaMove * lx * 0.1;
        y += deltaMove * ly * 0.1;
    }
    glutPostRedisplay(); 
}

void renderScene(void)
{
    int i, j;
    glClearColor(0.1, 0.1, 0.1, 0.1); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(x, y, 1.0, x + lx, y + ly, 1.0, 0.0, 0.0, 1.0);

    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(-100.0, -100.0, 0.0);
    glVertex3f(-100.0, 100.0, 0.0);
    glVertex3f(100.0, 100.0, 0.0);
    glVertex3f(100.0, -100.0, 0.0);
    glEnd();

    for (i = -4; i < 4; i++)
        for (j = -4; j < 4; j++) {
            glPushMatrix();
            glTranslatef(i * 7.5, j * 7.5, 0);
            drawBox();
            glPopMatrix();
        }
    glutSwapBuffers();
}

void pressKeyboardKey(unsigned char key, int x, int y)
{
    switch(key) {
    case 'w': 
    case 'W': deltaMove = 1.0; break;
    case 's':
    case 'S': deltaMove = -1.0; break;
    }
    
}

void releaseKeyboardKey(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 'W': deltaMove = 0.0; 
        break;
    case 's':
    case 'S': deltaMove = 0.0; break;
    }

    float i = 0;
    i = sin(deltaMove) * 0.08;
    glPushMatrix();
    
    glutSwapBuffers();
}

void mouseMove(int x, int y)
{
    if (isDragging) { 
        deltaAngle = (x - xDragStart) * 0.005;
       
        lx = -sin(angle + deltaAngle);
        ly = cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) { 
            isDragging = 1; 
            xDragStart = x; 
        }
        else { 
            angle += deltaAngle; 
            isDragging = 0; 
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 600);
    glutCreateWindow("Navigation Interface");

    glutReshapeFunc(changeSize); 
    glutDisplayFunc(renderScene); 
    glutIdleFunc(update); 
    glutIgnoreKeyRepeat(1); 
    glutMouseFunc(mouseButton); 
    glutMotionFunc(mouseMove); 
    glutKeyboardFunc(pressKeyboardKey); 
    glutKeyboardUpFunc(releaseKeyboardKey);
    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}