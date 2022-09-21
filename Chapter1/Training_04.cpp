/*
���콺 ��Ŭ���� ���ؼ� ���� ����
���� �ִ밹�� / ũ�⺯�� Ƚ�� �� ũ�� / ������� Ƚ�� ��������

a - �밢�� �̵��Ѵ�/���Ѵ�
i - �簢�� ������׷� �̵��Ѵ�/���Ѵ�
c - �簢�� ũ�� ���Ѵ�/�������ʴ´�
s - ��� ������ ����
m - ���� ó�� ��ġ�� �̵�
r - �簢�� 1�� ����
d - �簢�� ��ü ����
+/- Ÿ�̸� �ӵ� ����

*/

#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define MaxRectNum 5
#define SizeChangeNum 5		//������ ����ɶ� Ƚ�� ���� n�� Ŀ���� n�� �۾����� n�� Ŀ���� ...
#define SizeChange 0.05
#define ZigzagTime 2		//������� Ƚ�� ��2�� �Ʒ� 2�� �Ʒ� 2�� �� 2��

int TimerSpeed = 50;
std::random_device rd;
std::uniform_int_distribution<int> uid(0, 1);
std::uniform_real_distribution<double> rand_color(0.0f, 1.0f);
std::uniform_real_distribution<double> rand_size(0.25f, 0.5f);
std::uniform_real_distribution<double> rand_delta(0.05f,0.1f);
class myRect {
public:
	double left, bottom;
	double width, height;
	double r, g, b;
	double dx, dy;
	double first_left, first_bottom;
	double first_width, first_height;

	static int count;

	void CreateRect(double x, double y) {
		width = rand_size(rd), height = rand_size(rd);
		left = x - width / 2, bottom = y - height / 2;
		if (left < -1.0f) left = -1.0f;
		if (bottom < -1.0f)bottom = -1.0f;
		r = rand_color(rd);
		g = rand_color(rd);
		b = rand_color(rd);
		dx = rand_delta(rd), dy = rand_delta(rd);
		first_left = left, first_bottom = bottom;
		first_width = width, first_height = height;

		++count;
	}
};
int myRect::count = 0;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid TimerMove(int);
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
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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

GLboolean flag_timer = false;		//Ÿ�̸Ӱ� ���ư����� üũ�ϴ� �Һ���
GLboolean move_diagonal = false;		//�밢�� �̵� �Ǵ� �Һ���(diagonal �� �밢���̶�� ���̶��ϴ�~)
GLboolean move_zigzag = false;		//������� �̵� �Ǵ� �Һ���
GLboolean change_size = false;		//ũ�⺯�� �Ǵ� �Һ���


int count_change_size = 10;
int count_move_zigzag = ZigzagTime*2;
GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'D':		//��ü����
	case 'd':
		if (rect[0].count == 0) {
			printf("����! - ������ 0���Դϴ�! ���� �� �������ּ���!\n");
			break;
		}
		rect[0].count = 0;
		printf("���� ��ü ���� �Ϸ�! �ٽ� �������ּ���:)\n");
		break;
	case 'R':		//1������
	case 'r':
		if (rect[0].count == 0) {
			printf("����! - ������ 0���Դϴ�! ���� �� �������ּ���!\n");
			break;
		}
		rect[0].count--;
		printf("������ ���� ���� �Ϸ�! �ٽ� �������ּ���:)\n");
		break;
	case 'A':
	case 'a':
		if (!flag_timer) {//Ÿ�̸Ӱ� ���ư��� ���� �ƴϾ��ٸ�,
			flag_timer = true;
			glutTimerFunc(TimerSpeed, TimerMove, 0);
		}
		if (move_diagonal) {
			move_diagonal = false;
			move_zigzag = false;
		}
		else {
			move_diagonal = true;
			move_zigzag = false;
			for (int i = 0; i < rect[0].count; ++i) {
				rect[i].dx = rand_delta(rd);
				if (uid(rd) == 0)rect[i].dx *= -1;
				rect[i].dy = rand_delta(rd);
				if (uid(rd) == 0)rect[i].dy *= -1;
			}
		}
		break;
	case 'I':
	case 'i':
		if (!flag_timer) {//Ÿ�̸Ӱ� ���ư��� ���� �ƴϾ��ٸ�,
			flag_timer = true;
			glutTimerFunc(TimerSpeed, TimerMove, 0);
		}
		if (move_zigzag) {
			move_diagonal = false;
			move_zigzag = false;
		}
		else {
			move_diagonal = false;
			move_zigzag = true;
			for (int i = 0; i < rect[0].count; ++i) {
				rect[i].dx = rand_delta(rd);
				if (uid(rd) == 0)rect[i].dx *= -1;
				rect[i].dy = rand_delta(rd);
				if (uid(rd) == 0)rect[i].dy *= -1;
			}
			count_move_zigzag = ZigzagTime * 2;
		}
		break;
	case 'C':
	case 'c':
		if (!flag_timer) {//Ÿ�̸Ӱ� ���ư��� ���� �ƴϾ��ٸ�,
			flag_timer = true;
			glutTimerFunc(TimerSpeed, TimerMove, 0);
		}
		if (change_size) {
			change_size = false;
			for (int i = 0; i < rect[0].count; ++i) {
				rect[i].width = rect[i].first_width;
				rect[i].height = rect[i].first_height;
				if (rect[i].left + rect[i].width > 1.0f) {
					rect[i].left = 1.0f - rect[i].width;
					rect[i].dx *= -1;
				}
				if (rect[i].bottom + rect[i].height > 1.0f) {
					rect[i].bottom = 1.0f - rect[i].height;
					rect[i].dy *= -1;
				}
			}
		}
		else {
			change_size = true;
			count_change_size = SizeChangeNum;
		}
		break;
	case 'S':
	case 's':
		change_size = false;
		for (int i = 0; i < rect[0].count; ++i) {
			rect[i].width = rect[i].first_width;
			rect[i].height = rect[i].first_height;
			if (rect[i].left + rect[i].width > 1.0f) {
				rect[i].left = 1.0f - rect[i].width;
				rect[i].dx *= -1;
			}
			if (rect[i].bottom + rect[i].height > 1.0f) {
				rect[i].bottom = 1.0f - rect[i].height;
				rect[i].dy *= -1;
			}
		}
		move_diagonal = false;
		move_zigzag = false;
		break;
	case 'M':
	case 'm':
		change_size = false;
		move_diagonal = false;
		move_zigzag = false;
		for (int i = 0; i < rect[0].count; ++i) {
			rect[i].left = rect[i].first_left;
			rect[i].bottom = rect[i].first_bottom;
			rect[i].width = rect[i].first_width;
			rect[i].height = rect[i].first_height;
		}
		break;
	case '+':
		TimerSpeed -= 10;
		if (TimerSpeed < 50) {
			TimerSpeed = 50;
			printf("Ÿ�̸� �ӵ��� �ִ� 50ms�Դϴ�! ���̻� ������ �� �� �����ϴ�!\n");
		}
		break;
	case '-':
		TimerSpeed += 10;
		if (TimerSpeed > 200) {
			TimerSpeed = 200;
			printf("Ÿ�̸� �ӵ��� �ּ� 200ms�Դϴ�! ���̻� ������ �� �� �����ϴ�!\n");
		}
		break;
	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double w = (double)WIDTH / 2;
	double h = (double)HEIGHT / 2;
	double glut_x = (x - w) / w;
	double glut_y = ((y - h) / h) * -1;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {		//���� ���⵵��
			if (rect[0].count == MaxRectNum) {
				printf("����! - �̹� �ִ�ġ���� ������ �׷������ϴ�. ������ �������ּ���!\n");
				break;
			}
			rect[rect[0].count].CreateRect(glut_x, glut_y);
		
		}
		break;
	}
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	glutPostRedisplay();
}

GLvoid TimerMove(int value) {
	if (!move_diagonal && !move_zigzag && !change_size) {
		flag_timer = false;
		return;
	}
	
	if (move_diagonal) {
		for (int i = 0; i < rect[0].count; ++i) {
			rect[i].left += rect[i].dx;
			rect[i].bottom += rect[i].dy;
			if (rect[i].left < -1.0f) {
				rect[i].left = -1.0f;
				rect[i].dx *= -1;
			}
			if (rect[i].bottom < -1.0f) {
				rect[i].bottom = -1.0f;
				rect[i].dy *= -1;
			}
			if (rect[i].left + rect[i].width > 1.0f) {
				rect[i].left = 1.0f - rect[i].width;
				rect[i].dx *= -1;
			}
			if (rect[i].bottom + rect[i].height > 1.0f) {
				rect[i].bottom = 1.0f - rect[i].height;
				rect[i].dy *= -1;
			}
		}
	}
	else if (move_zigzag) {
		if (count_move_zigzag == -ZigzagTime * 2) {
			count_move_zigzag = ZigzagTime * 2;
		}
		if (count_move_zigzag == -ZigzagTime || count_move_zigzag == ZigzagTime) {
			for (int i = 0; i < rect[0].count; ++i) {
				rect[i].dy *= -1;
			}
		}
		
		for (int i = 0; i < rect[0].count; ++i) {
			rect[i].left += rect[i].dx;
			rect[i].bottom += rect[i].dy;
			if (rect[i].left < -1.0f) {
				rect[i].left = -1.0f;
				rect[i].dx *= -1;
			}
			if (rect[i].bottom < -1.0f) {
				rect[i].bottom = -1.0f;
			}
			if (rect[i].left + rect[i].width > 1.0f) {
				rect[i].left = 1.0f - rect[i].width;
				rect[i].dx *= -1;
			}
			if (rect[i].bottom + rect[i].height > 1.0f) {
				rect[i].bottom = 1.0f - rect[i].height;
			}
		}
		--count_move_zigzag;
		

	}
	
	static int check_count = -1;
	if(change_size) ++check_count;
	if (change_size&&check_count==2) {
		if (count_change_size == -SizeChangeNum) {	//�ʱ⼳�� ���ֱ�
			count_change_size = SizeChangeNum;
		}
		else if (count_change_size > 0) {			//Ŀ����
			for (int i = 0; i < rect[0].count; ++i) {
				rect[i].width += SizeChange;
				rect[i].height += SizeChange;
				if (rect[i].left + rect[i].width > 1.0f) {
					rect[i].left = 1.0f - rect[i].width;
				}
				if (rect[i].bottom + rect[i].height > 1.0f) {
					rect[i].bottom = 1.0f - rect[i].height;
				}
			}
			--count_change_size;
		}
		else {										//�۾�����
			for (int i = 0; i < rect[0].count; ++i) {
				rect[i].width -= SizeChange;
				rect[i].height -= SizeChange;
				if (rect[i].left + rect[i].width > 1.0f) {
					rect[i].left = 1.0f - rect[i].width;
				}
				if (rect[i].bottom + rect[i].height > 1.0f) {
					rect[i].bottom = 1.0f - rect[i].height;
				}
			}
			--count_change_size;
		}
		check_count = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, TimerMove, value);

}