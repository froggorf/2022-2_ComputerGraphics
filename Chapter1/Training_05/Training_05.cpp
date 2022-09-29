/*
������ ����
���� ũ���� ���� �簢�� �پ��� ������ ���� ��ġ�� 100��
���� ���콺 ��ư�� ������ ȭ���� �簢���� 2���� ũ���� �簢���� �׷�����
����ä�� �̵���Ű�� �̵���
���� ���콺 ��ư�� �簢���� �ε��� ��� �簢���� �������
R/r - ������ �ʱ�ȭ
A/a - ��ü �ʱ�ȭ
T/t - Ÿ�̸� ����
S/s - Ÿ�̸� ����
+ / - - Ÿ�̸� �ӵ� ����/���� 

---------------�߰����---------------
G/g - �߷� ����
��Ŭ�� �ϸ� �츮��
�� ������ ���� �帣����(���µ� ƨ�ܳ��� �������� �����ϱ��)
-------------------------------------
*/

#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define MaxRectNum 100
#define RectSize 0.1
#define Delta 0.05
#define GravitySpeed -0.004
enum MovingShape{DIAGONAL = 0, GRAVITY = 1, FLOWING = 2};

int TimerSpeed = 50;
std::random_device rd;
std::uniform_real_distribution<double> rand_pos(-1.0f, 1.0f - RectSize);
std::uniform_real_distribution<double> rand_rgb(0.0f, 1.0f);
std::uniform_int_distribution<int> uid(0, 1);
class myRect {
public:
	double left=rand_pos(rd), bottom=rand_pos(rd);
	double width=RectSize, height= RectSize;
	double r = rand_rgb(rd), g = rand_rgb(rd), b = rand_rgb(rd);
	GLboolean live = true;
	double dx = 0, dy = 0;
	static int count;
	myRect() {
		left = rand_pos(rd), bottom = rand_pos(rd);
		width = RectSize, height = RectSize;
		r = rand_rgb(rd), g = rand_rgb(rd), b = rand_rgb(rd);
		live = true;
		dx = 0, dy = 0;
		if (uid(rd) == 0)dx *= -1;
		if (uid(rd) == 0)dy *= -1;
	}

	void initMyRect() {
		left = rand_pos(rd), bottom = rand_pos(rd);
		width = RectSize, height = RectSize;
		r = rand_rgb(rd), g = rand_rgb(rd), b = rand_rgb(rd);
		live = true;
	}
};


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLboolean myIntersectRect(myRect, myRect);
GLvoid RectMove(int);
GLvoid CheckOutOfRange(myRect&);
GLvoid RectGravity(myRect&);
GLvoid WindowCursorToGl(int w_x, int w_y, double& gl_x, double& gl_y);
GLvoid GLCursorToWindow(double gl_x, double gl_y, int& w_x, int& w_y);

myRect rect[MaxRectNum];
myRect eraseRect;
myRect reviveRect;
myRect flowRect;

double old_gl_x, old_gl_y;

GLboolean grab_erase = false;
GLboolean grab_revive = false;
GLboolean grab_flow = false;
GLboolean flag_timer = false;
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(500, 300); // �������� ��ġ ����
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
	glutMotionFunc(MouseMove);
	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}


GLvoid drawScene() {//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�
	for (int i = 0; i < MaxRectNum; ++i) {
		if (rect[i].live) {
			glColor3f(rect[i].r, rect[i].g, rect[i].b);
			glRectf(rect[i].left, rect[i].bottom, rect[i].left + rect[i].width, rect[i].bottom + rect[i].height);
		}
	}
	

	if (grab_erase) {//
		glColor3f(1.0f, 1.0f, 1.0f);
		glRectf(eraseRect.left, eraseRect.bottom, eraseRect.left + eraseRect.width, eraseRect.bottom + eraseRect.height);
	}

	if (grab_revive) {
		glColor3f(0.0f, 0.0f, 0.0f);
		glRectf(reviveRect.left, reviveRect.bottom, reviveRect.left + reviveRect.width, reviveRect.bottom + reviveRect.height);
	}

	if (grab_flow) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glRectf(flowRect.left, flowRect.bottom, flowRect.left + flowRect.width, flowRect.bottom + flowRect.height);
	}
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}

BOOL stop_timer = false;
GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'R':
	case 'r':
		for (int i = 0; i < MaxRectNum; ++i) {
			rect[i].live = true;
		}
		
		break;
	case 'A':
	case 'a':
		for (int i = 0; i < MaxRectNum; ++i) {
			rect[i].initMyRect();
			if (rect[i].dx == 0)rect[i].dy = 0;
		}
		
		break;
	case 'T':
	case 't':
		if (!flag_timer) {
			for (int i = 0; i < MaxRectNum; ++i) {
				rect[i].dx = Delta, rect[i].dy = Delta;
				if (uid(rd) == 0) rect[i].dx *= -1;
				if (uid(rd) == 0) rect[i].dy *= -1;
			}
			
			glutTimerFunc(TimerSpeed, RectMove, DIAGONAL);
			flag_timer = true;
		}
		else {
			printf("�̹� Ÿ�̸Ӱ� �����־� ������ �� �����ϴ�.\n");
		}
		
		break;
	case 'S':
	case 's':
		if (flag_timer) {
			stop_timer = true;
			flag_timer = false;

			for (int i = 0; i < MaxRectNum; ++i) {
				rect[i].dx = 0; rect[i].dy = 0;
			}
		}
		
		break;
	case '+':
		TimerSpeed -= 10;
		if (TimerSpeed < 50) {
			printf("����! - Ÿ�̸� �ӵ��� �ִ� 50ms�Դϴ� ���̻� ������ ������ �� �����ϴ�.\n");
			TimerSpeed = 50;
		}
		break;
	case 'G':
	case 'g':	//�߷� �ۿ�
		if (!flag_timer) {
			for (int i = 0; i < MaxRectNum; ++i) {
				rect[i].dx = 0;
				rect[i].dy = 0;
			}

			glutTimerFunc(TimerSpeed, RectMove, GRAVITY);
			flag_timer = true;
		}
		else {
			printf("�̹� Ÿ�̸Ӱ� �����־� ������ �� �����ϴ�.\n");
		}
		break;
	case '-':
		TimerSpeed += 10;
		if (TimerSpeed > 200) {
			printf("����! - Ÿ�̸� �ӵ��� �ּ� 200ms�Դϴ� ���̻� ������ ������ �� �����ϴ�.\n");
			TimerSpeed = 50;
		}
		break;
		
	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double gl_x, gl_y;
	WindowCursorToGl(x, y, gl_x, gl_y);
	grab_erase = false;
	grab_revive = false;
	grab_flow = false;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			eraseRect.left = gl_x - RectSize;
			eraseRect.bottom = gl_y - RectSize;
			eraseRect.width = RectSize * 2;
			eraseRect.height = RectSize * 2;
			grab_erase = true;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			reviveRect.left = gl_x - RectSize;
			reviveRect.bottom = gl_y - RectSize;
			reviveRect.width = RectSize * 2;
			reviveRect.height = RectSize * 2;
			grab_revive = true;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			//if (flag_timer) break;	//������ ���ƾ��ϳ� ����ϹǷ� �׳� �ȸ��� - �ǵ�ġ���� ���� ���� �������� �ټ� ����
			for (int i = 0; i < MaxRectNum; ++i) {
				rect[i].dx = 0; rect[i].dy = 0;
			}
			flowRect.left = gl_x - RectSize;
			flowRect.bottom = gl_y - RectSize;
			flowRect.width = RectSize * 3;
			flowRect.height = RectSize * 3;
			grab_flow = true;
			old_gl_x = gl_x, old_gl_y = gl_y;
			glutTimerFunc(TimerSpeed, RectMove, FLOWING);
			flag_timer = true;
		}

		break;
	}
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	double gl_x, gl_y;
	WindowCursorToGl(x, y, gl_x, gl_y);
	if (grab_erase) {
		eraseRect.left = gl_x - RectSize;
		eraseRect.bottom = gl_y - RectSize;
		eraseRect.width = RectSize * 2;
		eraseRect.height = RectSize * 2;

		for (int i = 0; i < MaxRectNum; ++i) {
			if (myIntersectRect(rect[i], eraseRect)) {
				rect[i].live = false;
			}
		}
	}
	else if (grab_revive) {
		reviveRect.left = gl_x - RectSize;
		reviveRect.bottom = gl_y - RectSize;
		reviveRect.width = RectSize * 2;
		reviveRect.height = RectSize * 2;

		for (int i = 0; i < MaxRectNum; ++i) {
			if (myIntersectRect(rect[i], reviveRect)) {
				rect[i].live = true;
			}
		}
	}
	else if (grab_flow) {
		flowRect.left = gl_x - RectSize;
		flowRect.bottom = gl_y - RectSize;
		flowRect.width = RectSize * 3;
		flowRect.height = RectSize * 3;

		{//�ֵ� dx dy ����
			for (int i = 0; i < MaxRectNum; ++i) {
				if (myIntersectRect(rect[i], flowRect)) {
					rect[i].dx += (gl_x - old_gl_x)/3;
					rect[i].dy += (gl_y - old_gl_y)/3;
				}
			}
			old_gl_x = gl_x;
			old_gl_y = gl_y;
		}
	}
	
	glutPostRedisplay();
}

GLvoid CheckOutOfRange(myRect& rect) {
	if (rect.left < -1.0f) {
		rect.left = -1.0f;
		rect.dx *= -1;
	}
	if (rect.bottom < -1.0f) {
		rect.bottom = -1.0f;
		rect.dy *= -1;
	}
	if (rect.left + rect.width > 1.0f) {
		rect.left = 1.0f - rect.width;
		rect.dx *= -1;
	}
	if (rect.bottom + rect.height > 1.0f) {
		rect.bottom = 1.0f - rect.height;
		rect.dy *= -1;
	}
}

GLvoid RectMove(int value) {
	if (value == DIAGONAL) {
		for (int i = 0; i < MaxRectNum; ++i) {
			rect[i].left += rect[i].dx;
			rect[i].bottom += rect[i].dy;
			CheckOutOfRange(rect[i]);
		}
	}
	else if (value == GRAVITY) {
		for (int i = 0; i < MaxRectNum; ++i) {
			rect[i].bottom += rect[i].dy;		//�߸� �� �ڵ��̳�, ���� ���� �� �� �ÿ��ϰ� �������� ������ �־� �̴�� ����
			RectGravity(rect[i]);
		}
		
	}
	else if (value == FLOWING) {
		for (int i = 0; i < MaxRectNum; ++i) {
			rect[i].left += rect[i].dx;
			rect[i].bottom += rect[i].dy;
			rect[i].dx *=0.8;
			rect[i].dy *=0.8;
			if (-0.0005 <= rect[i].dx && rect[i].dx <= 0.0005) rect[i].dx = 0;
			if (-0.0005 <= rect[i].dy && rect[i].dy <= 0.0005) rect[i].dy = 0;
			CheckOutOfRange(rect[i]);
		}
		if (!grab_flow) {
			int check = true;
			for (int i = 0; i < MaxRectNum; ++i) {
				if (rect[i].dx != 0 || rect[i].dy != 0) check = false;
			}
			if (check) stop_timer = true;
		}
	}
	
	glutPostRedisplay();

	if (stop_timer) {
		stop_timer = false;
		flag_timer = false;
		return;
	}
	glutTimerFunc(TimerSpeed, RectMove, value);
}

GLboolean myIntersectRect(myRect r1, myRect r2) {
	double r1_left = r1.left, r1_bottom = r1.bottom, r1_top = r1.bottom + r1.height, r1_right = r1.left + r1.width;
	double r2_left = r2.left, r2_bottom = r2.bottom, r2_top = r2.bottom + r2.height, r2_right = r2.left + r2.width;

	bool bVertical = false;
	bool bHorizontal = false;

	if (r1_left<r2_right&&r1_right>r2_left) {
		bVertical = true;
	}

	if (r1_top>r2_bottom&&r1_bottom<r2_top) {
		bHorizontal = true;
	}

	if (bVertical&&bHorizontal) return TRUE;
	
	return FALSE;

}

GLvoid RectGravity(myRect& rect) {
	rect.bottom += rect.dy;
	if (0 < rect.dy && rect.dy <= GravitySpeed * GravitySpeed) {
		rect.dy = 0;
		return;
	}
	if (rect.bottom - (-1.0) <= 0.01) {
		rect.bottom = -1.0;
		rect.dy *= -0.7;
	}
	else {
		rect.dy += GravitySpeed;
	}
	
	if (rect.bottom + rect.height >= 1.0) {
		rect.bottom = 1.0 - rect.height;
	}
}

GLvoid WindowCursorToGl(int w_x, int w_y, double& gl_x, double& gl_y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	gl_x = (w_x - w) / w;
	gl_y = ((w_y - h) / h) * -1;
}
GLvoid GLCursorToWindow(double gl_x, double gl_y, int& w_x, int& w_y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	w_x = gl_x * w + w;
	w_y = -gl_y * h + h;
}