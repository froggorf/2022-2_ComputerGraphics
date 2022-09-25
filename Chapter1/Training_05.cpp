/*
윈도우 띄우고
같은 크기의 작은 사각형 다양한 색으로 임의 위치에 100개
왼쪽 마우스 버튼을 누르면 화면의 사각형의 2배의 크기의 사각형이 그려지고
누른채로 이동시키면 이동됨
왼쪽 마우스 버튼의 사각형과 부딪힌 배경 사각형은 사라진다
R/r - 기존값 초기화
A/a - 전체 초기화
T/t - 타이머 시작
G/g - 중력 적용
S/s - 타이머 멈춤
+ / - - 타이머 속도 증가/감소 

우클릭 하면 살리기 -> 전부다 숨기고서 n번만에 몇개까지 찾아내는지 하는거도 만들어보기

*/

#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define MaxRectNum 100
#define RectSize 0.1
#define Delta 0.05
#define GravitySpeed -0.004
enum MovingShape{DIAGONAL = 0, GRAVITY = 1};

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
	double dx = Delta, dy = Delta;
	static int count;
	myRect() {
		left = rand_pos(rd), bottom = rand_pos(rd);
		width = RectSize, height = RectSize;
		r = rand_rgb(rd), g = rand_rgb(rd), b = rand_rgb(rd);
		live = true;
		dx = Delta, dy = Delta;
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
myRect rect[MaxRectNum];
myRect eraseRect;
myRect reviveRect;

GLboolean grab_erase = false;
GLboolean grab_revive = false;
GLboolean flag_timer = false;
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(500, 300); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성

		//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
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
	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
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
			printf("이미 타이머가 켜져있어 실행할 수 없습니다.\n");
		}
		
		break;
	case 'S':
	case 's':
		if (flag_timer) {
			stop_timer = true;
			flag_timer = false;
		}
		
		break;
	case '+':
		TimerSpeed -= 10;
		if (TimerSpeed < 50) {
			printf("주의! - 타이머 속도는 최대 50ms입니다 더이상 빠르게 진행할 수 없습니다.\n");
			TimerSpeed = 50;
		}
		break;
	case 'G':
	case 'g':	//중력 작용
		if (!flag_timer) {
			for (int i = 0; i < MaxRectNum; ++i) {
				rect[i].dx = 0;
				rect[i].dy = 0;
			}

			glutTimerFunc(TimerSpeed, RectMove, GRAVITY);
			flag_timer = true;
		}
		else {
			printf("이미 타이머가 켜져있어 실행할 수 없습니다.\n");
		}
		break;
	case '-':
		TimerSpeed += 10;
		if (TimerSpeed > 200) {
			printf("주의! - 타이머 속도는 최소 200ms입니다 더이상 느리게 진행할 수 없습니다.\n");
			TimerSpeed = 50;
		}
		break;
		
	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double w = (double) glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double) glutGet(GLUT_WINDOW_HEIGHT) / 2;
	double glut_x = (x - w) / w;
	double glut_y = ((y - h) / h) * -1;
	grab_erase = false;
	grab_revive = false;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			eraseRect.left = glut_x - RectSize;
			eraseRect.bottom = glut_y - RectSize;
			eraseRect.width = RectSize * 2;
			eraseRect.height = RectSize * 2;
			grab_erase = true;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			reviveRect.left = glut_x - RectSize;
			reviveRect.bottom = glut_y - RectSize;
			reviveRect.width = RectSize * 2;
			reviveRect.height = RectSize * 2;
			grab_revive = true;
		}
		break;
	}
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	double glut_x = (x - w) / w;
	double glut_y = ((y - h) / h) * -1;

	if (grab_erase) {
		eraseRect.left = glut_x - RectSize;
		eraseRect.bottom = glut_y - RectSize;
		eraseRect.width = RectSize * 2;
		eraseRect.height = RectSize * 2;

		for (int i = 0; i < MaxRectNum; ++i) {
			if (myIntersectRect(rect[i], eraseRect)) {
				rect[i].live = false;
			}
		}
	}
	else if (grab_revive) {
		reviveRect.left = glut_x - RectSize;
		reviveRect.bottom = glut_y - RectSize;
		reviveRect.width = RectSize * 2;
		reviveRect.height = RectSize * 2;

		for (int i = 0; i < MaxRectNum; ++i) {
			if (myIntersectRect(rect[i], reviveRect)) {
				rect[i].live = true;
			}
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
			rect[i].bottom += rect[i].dy;
			RectGravity(rect[i]);
		}
		
	}
	
	glutPostRedisplay();

	if (stop_timer) {
		stop_timer = false;
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