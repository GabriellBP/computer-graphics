#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

#define AZUL     0.0, 0.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO  1.0, 1.0, 0.0
#define VERDE    0.0, 1.0, 0.0
#define CYAN     1.0, 0.0, 1.0
#define LARANJA  0.8, 0.6, 0.1
#define ROSEO    0.7, 0.1, 0.6
#define CINZA    0.6, 0.6, 0.6

static GLfloat vertices[60] = {
  0.0,  30.0, 50.0, /* 0 */
  30.0, 30.0, 50.0, /* 1 */
  30.0, 30.0, 50.0, /* 2 */
  30.0,  0.0, 50.0, /* 3 */
  0.0,   0.0, 50.0, /* 4 */
  0.0,  30.0,  0.0, /* 5 */
  30.0, 30.0,  0.0, /* 6 */
  30.0,  0.0,  0.0, /* 7 */
  0.0,   0.0,  0.0, /* 8 */
  30.0, 30.0, 50.0, /* 9 */
  15.0, 45.0, 0.0,  /* 10 */
  15.0, 45.0, 50.0, /* 11 */
  -50.0, 0, -50.0,/* 12 */ 
  -50.0, 0, 50.0, /* 13 */
  50.0, 0, 50.0,  /* 14 */
  50.0, 0, -50.0  /* 15 */
};

static GLubyte frenteIndices[] = { 0,4,3,2,1 };
static GLubyte trasIndices[] = { 5,6,7,8 };
static GLubyte esquerdaIndices[] = { 0,5,8,4 };
static GLubyte direitaIndices[] = { 2,3,7,6,9 };
static GLubyte topoIndices[] = { 0,1,9,6,5 };
static GLubyte fundoIndices[] = { 3,4,8,7 };
static GLubyte tetoEsqIndices[] = { 0, 11, 10, 5 };
static GLubyte tetoDirIndices[] = { 11, 9, 6, 10 };
static GLubyte trianguloFrenteIndices[] = { 9,11,0};
static GLubyte trianguloTrasIndices[] = { 5,10,6 };
static GLubyte chaoIndices[] = { 12, 13, 14, 15 };


static int eixoy, eixox;
int largura, altura;
float theta = 0, gama = 0.5, epson = 0;


int main(int argc, char** argv) {
	int i;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho(-50, 50, -50, 50, -100, 100);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	largura = w;
	altura = h;
}

void display(void) {
	glPushMatrix();
	gluLookAt(sin(theta), sin(gama), cos(epson), //de onde
			0, 0, 0, //pra onde
			0, 1, 0); //como
	glRotatef((GLfloat)eixoy, 0.0, 1.0, 0.0);
	glTranslated(-15.0, -30.0, -25.0);
	glRotatef((GLfloat)eixox, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glColor3f(AZUL); /* frente */
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, frenteIndices);

	glColor3f(VERMELHO); /* esquerda */
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, esquerdaIndices);

	glColor3f(AZUL); /* tras */
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trasIndices);

	glColor3f(VERMELHO); /* direita */
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, direitaIndices);

	glColor3f(CYAN); /* topo */
	glDrawElements(GL_POLYGON, 5, GL_UNSIGNED_BYTE, topoIndices);

	glColor3f(LARANJA); /* fundo */
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fundoIndices);

	glColor3f(CINZA); /* Teto esquerdo */
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, tetoEsqIndices);

	glColor3f(CINZA); /* Teto direito */
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, tetoDirIndices);

	glColor3f(AMARELO); /* Triangulo do Teto frente */
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trianguloFrenteIndices);

	glColor3f(AMARELO); /* Triangulo do Teto tras */
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, trianguloTrasIndices);
	
	//glColor3f(VERDE); /* chao */
	//glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, chaoIndices);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'a':
		printf("%d, %d\n", x, y);
		break;
	case 'y':
		eixoy = (eixoy + 5) % 360;
		glutPostRedisplay();
		break;
	case 'Y':
		eixoy = (eixoy - 5) % 360;
		glutPostRedisplay();
		break;
	case 'x':
		eixox = (eixox + 5) % 360;
		glutPostRedisplay();
		break;
	case 'X':
		eixox = (eixox - 5) % 360;
		glutPostRedisplay();
		break;
	case 'p':
		glLoadIdentity();
		gluPerspective(65.0, (GLfloat)largura / (GLfloat)altura, 20.0, 120.0);
		gluLookAt(0, 0, -90, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'o':
		glLoadIdentity();
		glOrtho(-50, 50, -50, 50, -100, 100);
		glutPostRedisplay();
		break;
	case 'r':		
		theta += 0.0174533;
		epson += 0.0174533;
		glutPostRedisplay();
		break;
	case 'R':
		theta -= 0.0174533;
		epson -= 0.0174533;
		glutPostRedisplay();
		break;
	case 't':
		gama += 0.0174533;
		epson += 0.0174533;
		glutPostRedisplay();
		break;
	case 'T':
		gama -= 0.0174533;
		epson -= 0.0174533;
		glutPostRedisplay();
		break;
	}
}