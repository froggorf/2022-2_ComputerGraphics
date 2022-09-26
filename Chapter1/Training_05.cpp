/*
윈도우 띄우고
같은 크기의 작은 사각형 다양한 색으로 임의 위치에 100개
왼쪽 마우스 버튼을 누르면 화면의 사각형의 2배의 크기의 사각형이 그려지고
누른채로 이동시키면 이동됨
왼쪽 마우스 버튼의 사각형과 부딪힌 배경 사각형은 사라진다
R/r - 기존값 초기화
A/a - 전체 초기화
T/t - 타이머 시작
S/s - 타이머 멈춤
+ / - - 타이머 속도 증가/감소 

---------------추가목록---------------
G/g - 중력 적용
우클릭 하면 살리기
휠 누르면 물살 흐르듯이(였는데 튕겨내는 느낌으로 진행하기로)
-------------------------------------
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

	if (grab_flow) {
		glColor3f(0.0f, 0.0f, 1.0f);
		glRectf(flowRect.left, flowRect.bottom, flowRect.left + flowRect.width, flowRect.bottom + flowRect.height);
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

			for (int i = 0; i < MaxRectNum; ++i) {
				rect[i].dx = 0; rect[i].dy = 0;
			}
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
			//if (flag_timer) break;	//원래는 막아야하나 어색하므로 그냥 안막음 - 의도치않은 현상에 대한 문제점은 다소 있음
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

		{//애들 dx dy 설정
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
			rect[i].bottom += rect[i].dy;		//잘못 들어간 코드이나, 넣은 쪽이 좀 더 시원하게 떨어지는 느낌이 있어 이대로 진행
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