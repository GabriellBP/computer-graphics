#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

static int year = 0, day = 0;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
	GLfloat lightPosition[] = { -5, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

/*desenha as trnsformacoes*/
void display(void) {
	/*limpa o display*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glColor3ub(248, 246, 38);
		glRotatef((GLfloat) year, 1.0, 0.0, 0.0);
		glRotatef((GLfloat) day, 0.0, 0.0, 1.0);
		glutSolidSphere(1.0, 20, 16);/*desenha o sol*/
	glPopMatrix();
	glPushMatrix();
		glColor3ub(0, 0, 255);
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0); /*translada a partir do novo sistema de coordenadas resultante da Rotação*/
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
		glutSolidSphere(0.2, 10, 8); /*desenha um planeta*/
	glPopMatrix();
	glPushMatrix();
		glColor3ub(161, 51, 0);
		glRotatef(-2 * (GLfloat)year, 0.0, 2.0, 0.0);
		glTranslatef(4.0, 0.0, 0.0); /*translada a partir do novo sistema de coordenadas resultante da Rotação*/
		glPushMatrix();
			glRotatef(2 * (GLfloat)day, 0.0, 1.0, 0.0);
			glutSolidSphere(0.2, 20, 8); /*desenha um planeta*/
		glPopMatrix();

		glPushMatrix();
			glColor3ub(255, 11, 208);
			glRotatef(-2 * (GLfloat)day, 0.0, 2.0, 0.0);
			glTranslatef(0.5, 0.0, 0.0); /*translada a partir do novo sistema de coordenadas resultante da Rotação*/
			glutSolidSphere(0.07, 20, 8); /*desenha uma lua*/
		glPopMatrix();

		glPushMatrix();
			glColor3ub(102, 248, 38);
			glRotatef(2 * (GLfloat)day, 0.0, 2.0, 2.0);
			glTranslatef(1.0, 0.0, 0.0); /*translada a partir do novo sistema de coordenadas resultante da Rotação*/
			glRotatef(2 * (GLfloat)day, 0.0, 1.0, 0.0);
			glutSolidSphere(0.07, 20, 8); /*desenha uma lua*/
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();

}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		day = (day + 10) % 360; //% valor do resto
		glutPostRedisplay(); //Redesenha a cena com novas coordenadas, é exeutado no gluMainLoop;
		break;
	case 'D':
		day = (day - 10) % 360;
		glutPostRedisplay();
		break;
	case 'y':
		year = (year + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		year = (year - 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void exit(unsigned char key, int x, int y) {
	if (key == 'q')
		exit(0);
}

int main(int argc, char *argv[]) {
	/*inicializa o sistema GLUT*/
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1400, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Rotacao de Planetas");

	/*chama a funcao init e inicia as propriedades View Port*/
	init();

	glutDisplayFunc(display);

	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;

}