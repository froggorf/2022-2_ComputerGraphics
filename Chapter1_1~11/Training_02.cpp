/*
마우스 왼쪽클릭
	- 사각형 내부 : 사각형 색상 랜덤 변경
	- 사각형 외부 : 배경색 랜덤 변경
마우스 오른클릭
	- 사각형 내부 : 사각형 크기 확대
	- 사각형 외부 : 사각형 크기 축소
*/

#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
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
	glutMainLoop(); // 이벤트 처리 시작 
}

double rect_R=0.0f, rect_G=0.0f, rect_B = 1.0f;
GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정

	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	glColor3f(rect_R, rect_G, rect_B);
	glRectf(-length, -length, length, length);
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
			//안에있음
			rect_R = urd(rd);
			rect_G = urd(rd);
			rect_B = urd(rd);
		}
		else {
			//밖에누름
			glClearColor(urd(rd), urd(rd), urd(rd), 1.0f);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (-length <= glut_x && glut_x <= length && -length <= glut_y && glut_y <= length) {
			//안에있음
			length += 0.1;
			if (length >= 0.9) {
				length = 0.9;
				printf("주의 - 범위를 초과하였습니다 사각형 외부를 눌러주세요\n");
			}
		}
		else {
			//밖에누름
			length -= 0.1;
			if (length <= 0.1) {
				length = 0.1;
				printf("주의 - 범위를 초과하였습니다 사각형 내부를 눌러주세요\n");
			}
		}
		break;
	}
}