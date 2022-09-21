/*
�ʱ� ���� ���
R: ������
G: �ʷϻ�
B: �Ķ���
A: ������
W: ���
K: ������
T: Ÿ�̸Ӹ� �����Ͽ� Ư�� �ð����� ���������� ��� �ٲ�� �Ѵ�.
S: Ÿ�̸� ����
Q: ���α׷� ����
*/

#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define TimerTime 100
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid TimerFunc(int);
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(500, 500); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����

		//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyBoard);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� ��blue�� �� ����
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}


GLvoid drawScene() {
	//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	

	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}

std::random_device rd;
std::uniform_real_distribution<double> ufd(0.0f, 1.0f);
GLboolean flag_timer_off = false;
GLvoid KeyBoard(unsigned char key, int x, int y) {

	switch (key) {
	case 'Q':	
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'R':	//Red
	case 'r':
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 'G':	//Green
	case 'g':
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 'B':	//Blue
	case 'b':
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 'A':	//Random
	case 'a':
		glClearColor(ufd(rd), ufd(rd), ufd(rd), 1.0f);
		break;
	case 'W':	//White
	case 'w':
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case 'K':
	case 'k':
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 'T':
	case 't':
		glutTimerFunc(TimerTime, TimerFunc, 1);
		break;
	case 'S':
	case 's':
		flag_timer_off = true;
		break;
	}

	glutPostRedisplay();
}
GLvoid TimerFunc(int num) {
	glClearColor(ufd(rd), ufd(rd), ufd(rd), 1.0f);
	if (flag_timer_off) {
		flag_timer_off = false;
		return;
	}
	glutTimerFunc(TimerTime, TimerFunc, 1);

	glutPostRedisplay();
}