/*
갯수 define으로 설정 가능
왼클릭 - 이동
우클릭 - 색변경
중간클릭 - 초기화
A/a - 한개 추가
D/d - 마지막에 만든것 한 개 삭제
*/


#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(500, 500); // 윈도우의 위치 지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성

		//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
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


GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정

	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	for (int i = 0; i < rect[0].count; ++i) {
		glColor3f(rect[i].r, rect[i].g, rect[i].b);
		glRectf(rect[i].left, rect[i].bottom, rect[i].left + rect[i].width, rect[i].bottom + rect[i].height);
	}


	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
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
			printf("이미 최대치까지 저장했습니다. 삭제후 진행해주세요!\n");
			break;
		}
		rect[rect[0].count].initRect();
		++rect[0].count;
		std::cout << "현재 갯수: " << rect[0].count << std::endl;
		break;
	case 'D':
	case 'd':
		if (rect[0].count == 0) {
			printf("사각형이 한개도 없어 삭제를 실패하였습니다.\n");
			break;
		}
		--rect[0].count;
		std::cout << "현재 갯수: " << rect[0].count << std::endl;
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