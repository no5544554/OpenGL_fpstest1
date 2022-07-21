#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FPS 60


float px = 0.0f;
float pz = 0.0f;
float py = 1.0f;
float pa = 0.0f;

BOOL keys[256];

BOOL leftArrow, rightArrow;

#define DEG_TO_RAD 0.01745329
#define NORMALIZED 0.707107


void Display(void)
{
    int i;
    double normalized = 0.2;

    glClearColor(0.2f, 0.5f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 480, 0);


    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.3f, 0.7f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 240);
    glVertex2f(640, 240);
    glVertex2f(640, 0);
    glVertex2f(0, 0);
    glEnd();

    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, 1.5, 50.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(pa, 0.0f, 1.0f, 0.0f);

    //gluLookAt(0.0, 1.0, 5.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(-px, -py, -pz);

    //glPushMatrix();
    glTranslatef(-10, -0.5, -10);
    for (i = 0; i < 40; i++)
    {
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        if (i < 20)
        {
            glTranslatef(0.0f, 0.0f, i);
        }
        else
        {
            glTranslatef(i - 20, 0.0f, 0);
            glRotatef(-90, 0.0f, 1.0f, 0.0f);
        }
        glBegin(GL_LINES);
        glVertex3f(-20, 0.0f, 0.0f);
        glVertex3f(20, 0.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }

    //glPopMatrix();
    GLfloat mat_diffuse[] = { 0.8, 0.4, 0.3, 1.0 };
    GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

    glColor3f(0.5f, 0.25f, 0.2f);
    glPushMatrix();
    glTranslatef(5, 4, 5);
    glScalef(0.5f, 4.0f, 0.5f);
    glRotatef(90, 1, 0, 0);
    glutSolidCylinder(1.0, 1.0, 16, 1);
    glPopMatrix();

    GLfloat mat_diffuse2[] = { 0.5, 0.4, 0.5, 1.0 };
    GLfloat mat_ambient2[] = { 0.3, 0.3, 0.3, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glClear(GL_DEPTH_BUFFER_BIT);
    glColor3f(0.5f, 0.4f, 0.5f);

    glLoadIdentity();
    glPushMatrix();
    glTranslatef(1.5f, -1.5f, -4.0f);
    glScalef(0.5f, 0.5f, 3.0f);
    glutSolidCylinder(1.0, 1.0, 16, 1);
    glPopMatrix();



/*
    glPushMatrix();
    glTranslatef(px - 1.0f, 0.0f, pz);
    glScalef(1.0f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
*/
    glFlush();

    if ((keys['d'] || keys['a']) && (keys['w'] || keys['s']))
    {
        normalized = 0.2 * NORMALIZED;
    }
    else
    {
        normalized = 0.2;
    }

    if (keys['d'])
    {
        px += normalized * cos(pa * DEG_TO_RAD);
        pz += normalized * sin(pa * DEG_TO_RAD);
    }
    else if (keys['a'])
    {
        px -= normalized * cos(pa * DEG_TO_RAD);
        pz -= normalized * sin(pa * DEG_TO_RAD);
    }

    if (keys['w'])
    {
        px += normalized * sin(pa * DEG_TO_RAD);
        pz -= normalized * cos(pa * DEG_TO_RAD);
    }
    else if (keys['s'])
    {
        px -= normalized * sin(pa * DEG_TO_RAD);
        pz += normalized * cos(pa * DEG_TO_RAD);
    }

    if (keys['e'])
    {
        py += 0.2f;
    }
    else if (keys['q'])
    {
        py -= 0.2f;
    }

    if (rightArrow)
    {
        pa += 2.0f;
        if (pa > 360) pa -= 360;
    }
    else if (leftArrow)
    {
        pa -= 2.0f;
        if (pa < 0) pa += 360;
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void RunMainLoop(int val)
{

}

void KeyboardDown(unsigned char key, int x, int y)
{
    keys[key] = TRUE;
}

void KeyboardUp(unsigned char key, int x, int y)
{
    keys[key] = FALSE;
}

void SpecialDown(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) leftArrow = TRUE;
    if (key == GLUT_KEY_RIGHT) rightArrow = TRUE;
}

void SpecialUp(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) leftArrow = FALSE;
    if (key == GLUT_KEY_RIGHT) rightArrow = FALSE;
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("OpenGL");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, 0.5, 50.0);

    glShadeModel(GL_SMOOTH);

    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 10.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(Display);
    glutTimerFunc(1000 / FPS, RunMainLoop, 0);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);
    glutMainLoop();
    return 0;
}