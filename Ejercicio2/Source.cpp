#include<iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

GLfloat angle = 0.0f;
int slices = 15;
int stacks = 15;
bool wired = false;

void idle()
{
	glutPostRedisplay();
}

void materialPhong()
{
	const GLfloat mat_ambient[] = { 0.19225f, 0.19225f, 0.19225f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.50754f, 0.50754f, 0.50754f, 1.0f };
	const GLfloat mat_specular[] = { 0.508273f, 0.508273f, 0.508273f, 1.0f };
	const GLfloat high_shininess[] = { 51.2f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void puntual()
{
	const GLfloat mat_specular[] = { 0.7f, 0.6f, 0.6f, 1.0f };
	const GLfloat mat_shininess[] = { 32.0f };
	const GLfloat light_position[] = { 2.0, 5.0, 5.0, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void spotlight()
{
	GLfloat light1_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_position[] = { 2.0, 5.0, 5.0, 0.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glEnable(GL_LIGHT1);
}

void direccional()
{
	const GLfloat mat_specular[] = { 0.7f, 0.6f, 0.6f, 1.0f };
	const GLfloat mat_shininess[] = { 32.0f };
	const GLfloat light_position[] = { 2.0, 5.0, 5.0, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void cono()
{
	materialPhong();
	glPushMatrix();
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0, 1.0, 0.0);
	if (!wired)
	{
		glutSolidCone(1, 1, slices, stacks);
	}
	else
	{
		glutWireCone(1, 1, slices, stacks);
	}
	glPopMatrix();

	angle += 0.2f;
}

void esfera()
{
	materialPhong();
	glPushMatrix();
	glTranslated(0.0, 2.0, 0.0);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0, 1.0, 0.0);
	if (!wired)
	{

		glutSolidSphere(1, slices, stacks);
	}
	else
	{
		glutWireSphere(1, slices, stacks);
	}
	glPopMatrix();

	angle += 0.2f;
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	case 'q':
	case 'Q':
		exit(0);
		break;

	case '+':
		slices++;
		stacks++;
		break;

	case '-':
		if (slices > 3 && stacks >3)
		{
			slices--;
			stacks--;
		}

	case 'w':
	case 'W':
		wired = !wired;
		break;
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//-------------------------------------
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);
	//-------------------------------------
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//----------------------------------------
	//--Posicionar la camara
	//----------------------------------------
	gluLookAt(
		3, 3, 3, /*posicion camara*/
		0, 0, 0, /*Direccion*/
		0, 0, 1  /*Up*/
	);
	//---------------------------------------
	cono();
	esfera();
	glutIdleFunc(idle);
	glutKeyboardFunc(keyInput);
	//puntual();
	//spotlight();
	direccional();
	glutSwapBuffers();
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);

	glutCreateWindow("Pregunta 4");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}