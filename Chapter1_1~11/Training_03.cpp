/*
���� define���� ���� ����
��Ŭ�� - �̵�
��Ŭ�� - ������
�߰�Ŭ�� - �ʱ�ȭ
A/a - �Ѱ� �߰�
D/d - �������� ����� �� �� ����
*/


#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define LENGTH 0.35
#define MaxRectNum 5

std::random_device rd;
std::uniform_real_distribution<double> urd(0.0f, 1.0f);
std::uniform_real_distribution<double> sizeurd(0.15f, LENGTH);
class myRect {
public:
	double left = -sizeurd(rd);
	double bottom = -sizeurd(rd);
	double height = sizeurd(rd)-bottom;
	double width = sizeurd(rd) - left;

	double r = urd(rd);
	double g = urd(rd);
	double b = urd(rd);

	GLboolean grab = false;

	static int count;

	void initRect() {
		left = -sizeurd(rd);
		bottom = -sizeurd(rd);
		height = sizeurd(rd) - bottom;
		width = sizeurd(rd) - left;

		r = urd(rd);
		g = urd(rd);
		b = urd(rd);

		GLboolean grab = false;
	}
};
int myRect::count = 1;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
myRect rect[MaxRectNum];
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
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}


GLvoid drawScene() {
	//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� ��blue�� �� ����

	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	for (int i = 0; i < rect[0].count; ++i) {
		glColor3f(rect[i].r, rect[i].g, rect[i].b);
		glRectf(rect[i].left, rect[i].bottom, rect[i].left + rect[i].width, rect[i].bottom + rect[i].height);
	}


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
	case 'A':
	case 'a':
		if (rect[0].count == MaxRectNum) {
			printf("�̹� �ִ�ġ���� �����߽��ϴ�. ������ �������ּ���!\n");
			break;
		}
		rect[rect[0].count].initRect();
		++rect[0].count;
		std::cout << "���� ����: " << rect[0].count << std::endl;
		break;
	case 'D':
	case 'd':
		if (rect[0].count == 0) {
			printf("�簢���� �Ѱ��� ���� ������ �����Ͽ����ϴ�.\n");
			break;
		}
		--rect[0].count;
		std::cout << "���� ����: " << rect[0].count << std::endl;
		break;

	}

	glutPostRedisplay();
}

int grabnum = -1;
GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double w = (double)WIDTH / 2;
	double h = (double)HEIGHT / 2;
	double glut_x = (x - w) / w;
	double glut_y = ((y - h) / h) * -1;

	if (state == GLUT_UP) {
		for (int i = 0; i < rect[0].count; ++i) {
			rect[i].grab = false;	
		}
		grabnum = -1;
		return;
	}
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			for (int i = 0; i < rect[0].count; ++i) {
				if (rect[i].left <= glut_x && glut_x <= (rect[i].left+rect[i].width) && rect[i].bottom <= glut_y && glut_y <= (rect[i].bottom+rect[i].height)) {
					grabnum = i;
				}
			}
			if (grabnum != -1) {
				rect[grabnum].grab = true;
			}
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			int check_select = -1;
			for (int i = 0; i < rect[0].count; ++i) {
				if (rect[i].left <= glut_x && glut_x <= (rect[i].left + rect[i].width) && rect[i].bottom <= glut_y && glut_y <= (rect[i].bottom + rect[i].height)) {
					check_select = i;
				}
			}
			if (check_select != -1) {
				rect[check_select].r = urd(rd);
				rect[check_select].g = urd(rd);
				rect[check_select].b = urd(rd);
			}
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			int check_select = -1;
			for (int i = 0; i < rect[0].count; ++i) {
				if (rect[i].left <= glut_x && glut_x <= (rect[i].left + rect[i].width) && rect[i].bottom <= glut_y && glut_y <= (rect[i].bottom + rect[i].height)) {
					check_select = i;
				}
			}
			if (check_select != -1) {
				rect[check_select].initRect();
			}
		}
		break;
	}
	
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	double w = (double) WIDTH/ 2;
	double h = (double)HEIGHT / 2;
	double glut_x = (x - w) / w;
	double glut_y = ((y - h) / h) * -1;
	if (grabnum != -1 && rect[grabnum].grab) {
		rect[grabnum].left = glut_x - rect[grabnum].width / 2;
		rect[grabnum].bottom = glut_y - rect[grabnum].height / 2;
		if (rect[grabnum].left <= -1) rect[grabnum].left = -1.0f;
		if (rect[grabnum].bottom <= -1)rect[grabnum].bottom = -1.0f;
		if (rect[grabnum].left + rect[grabnum].width >= 1.0f) rect[grabnum].left = 1.0f - rect[grabnum].width;
		if (rect[grabnum].bottom + rect[grabnum].height >= 1.0f) rect[grabnum].bottom = 1.0f - rect[grabnum].height;
	}
	glutPostRedisplay();
}