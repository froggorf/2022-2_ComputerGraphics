/*
초기 배경색 흰색
R: 빨간색
G: 초록색
B: 파란색
A: 렌덤색
W: 백색
K: 검정색
T: 타이머를 설정하여 특정 시간마다 렌덤색으로 계속 바뀌게 한다.
S: 타이머 종료
Q: 프로그램 종료
*/

#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define TimerTime 100
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid TimerFunc(int);
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(500, 500); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	

	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
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