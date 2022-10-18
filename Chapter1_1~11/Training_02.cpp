/*
���콺 ����Ŭ��
	- �簢�� ���� : �簢�� ���� ���� ����
	- �簢�� �ܺ� : ���� ���� ����
���콺 ����Ŭ��
	- �簢�� ���� : �簢�� ũ�� Ȯ��
	- �簢�� �ܺ� : �簢�� ũ�� ���
*/

#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int,int,int);

double length = 0.5;
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(500, 500); // �������� ��ġ ����
	glutInitWindowSize(WIDTH, HEIGHT); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����

		//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

double rect_R=0.0f, rect_G=0.0f, rect_B = 1.0f;
GLvoid drawScene() {
	//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� ��blue�� �� ����

	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	glColor3f(rect_R, rect_G, rect_B);
	glRectf(-length, -length, length, length);
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	}
}

std::random_device rd;
std::uniform_real_distribution<double> urd(0.0f, 1.0f);
GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double w = (double)WIDTH / 2;
	double h = (double)HEIGHT / 2;
	double glut_x = (x - w) / w;
	double glut_y = ((y - h) / h) * -1;
	std::cout << x << " " << y << std::endl;
	std::cout << glut_x << " " << glut_y << std::endl;

	if (state == GLUT_DOWN) return;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (-length <= glut_x && glut_x <= length && -length <= glut_y && glut_y <= length) {
			//�ȿ�����
			rect_R = urd(rd);
			rect_G = urd(rd);
			rect_B = urd(rd);
		}
		else {
			//�ۿ�����
			glClearColor(urd(rd), urd(rd), urd(rd), 1.0f);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (-length <= glut_x && glut_x <= length && -length <= glut_y && glut_y <= length) {
			//�ȿ�����
			length += 0.1;
			if (length >= 0.9) {
				length = 0.9;
				printf("���� - ������ �ʰ��Ͽ����ϴ� �簢�� �ܺθ� �����ּ���\n");
			}
		}
		else {
			//�ۿ�����
			length -= 0.1;
			if (length <= 0.1) {
				length = 0.1;
				printf("���� - ������ �ʰ��Ͽ����ϴ� �簢�� ���θ� �����ּ���\n");
			}
		}
		break;
	}
}