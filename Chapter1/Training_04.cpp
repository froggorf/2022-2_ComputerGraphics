/*
마우스 좌클릭을 통해서 도형 생성
도형 최대갯수 / 크기변경 횟수 및 크기 / 지그재그 횟수 조정가능

a - 대각선 이동한다/안한다
i - 사각형 지그재그로 이동한다/안한다
c - 사각형 크기 변한다/변하지않는다
s - 모든 움직임 멈춤
m - 기존 처음 위치로 이동
r - 사각형 1개 삭제
d - 사각형 전체 삭제
+/- 타이머 속도 조절

*/

#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define MaxRectNum 5
#define SizeChangeNum 5		//사이즈 변경될때 횟수 지정 n번 커지고 n번 작아지고 n번 커지고 ...
#define SizeChange 0.05
#define ZigzagTime 2		//지그재그 횟수 위2번 아래 2번 아래 2번 위 2번

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
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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

GLboolean flag_timer = false;		//타이머가 돌아가는지 체크하는 불변수
GLboolean move_diagonal = false;		//대각선 이동 판단 불변수(diagonal 은 대각선이라는 뜻이랍니다~)
GLboolean move_zigzag = false;		//지그재그 이동 판단 불변수
GLboolean change_size = false;		//크기변경 판단 불변수


int count_change_size = 10;
int count_move_zigzag = ZigzagTime*2;
GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'D':		//전체삭제
	case 'd':
		if (rect[0].count == 0) {
			printf("주의! - 도형이 0개입니다! 생성 후 삭제해주세요!\n");
			break;
		}
		rect[0].count = 0;
		printf("도형 전체 삭제 완료! 다시 진행해주세요:)\n");
		break;
	case 'R':		//1개삭제
	case 'r':
		if (rect[0].count == 0) {
			printf("주의! - 도형이 0개입니다! 생성 후 삭제해주세요!\n");
			break;
		}
		rect[0].count--;
		printf("마지막 도형 삭제 완료! 다시 진행해주세요:)\n");
		break;
	case 'A':
	case 'a':
		if (!flag_timer) {//타이머가 돌아가던 중이 아니었다면,
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
		if (!flag_timer) {//타이머가 돌아가던 중이 아니었다면,
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
		if (!flag_timer) {//타이머가 돌아가던 중이 아니었다면,
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
			printf("타이머 속도는 최대 50ms입니다! 더이상 빠르게 할 수 없습니다!\n");
		}
		break;
	case '-':
		TimerSpeed += 10;
		if (TimerSpeed > 200) {
			TimerSpeed = 200;
			printf("타이머 속도는 최소 200ms입니다! 더이상 느리게 할 수 없습니다!\n");
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
		if (state == GLUT_DOWN) {		//상자 생기도록
			if (rect[0].count == MaxRectNum) {
				printf("주의! - 이미 최대치까지 도형이 그려졌습니다. 삭제후 진행해주세요!\n");
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
		if (count_change_size == -SizeChangeNum) {	//초기설정 해주기
			count_change_size = SizeChangeNum;
		}
		else if (count_change_size > 0) {			//커지기
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
		else {										//작아지기
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