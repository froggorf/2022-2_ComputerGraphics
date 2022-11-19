/*
현재 진행 목록

움직이는 산과 미로 만들기
• 화면에 바닥을 그린다.  - 100%
• 사용자에게 가로와 세로의 나누기 개수를 입력 받는다. - 100% (명령어 : +)
• 콘솔창에서 가로와 세로의 개수를 입력 받도록 한다. - 100%
• 나누기 개수는 5 ≤ 개수 ≤ 25으로 한다. (최대값 변경 가능) - 100% 5~30
• 입력 받은 개수 만큼으로 가로와 세로를 나누고 각 칸에 육면체를 그린다.	- 100%
• 육면체가 나타나는 애니메이션을 구현한다.• 예를 들어, 위에서 육면체가 떨어진다. 아래에서 육면체가 올라온다. - 100%
• 키보드 명령에 의해 육면체들이 다른 속도, 다른 최대/최소 높이로 움직인다.	- 100%(명령어 M/m)
• 화면의 한 부분에 탑뷰의 미니맵이 그려진다 - 100%

키보드 명령을 입력 받는다.
• o/p: 투영을 선택한다 (직각 투영 / 원근 투영) - 100% (O/o 온오프)
• z/Z: 원근 투영 시 z축으로 이동할 수 있게 한다. - 100% (마우스 휠을 통해 전체적 확대 축소 - 법선벡터 활용)
• m/M: 육면체들이 위 아래로 움직인다/멈춘다. - 100% 
• 움직이는 속도와 높이의 최대값은 다양하다. 최대/최소 높이는 본인이 정한다. - 100% 1`3인가 그럴것
• y/Y: 카메라가 바닥의 y축을 기준으로 양/음 방향으로 회전한다. - 100%
• r: 미로를 제작한다.• 가로와 세로를 나눈 등분에서 미로가 만들어지면 그 해당 칸의 육면체는 사라지고 미로가 생긴다. - 95% 혹시모를 값 초기화 안된것에 대한 처리 필요

• v: 육면체들 움직임이 멈추고 낮은 높이로 변한다. • 미로에서 움직이는 객체 확인할 수 있다. 다시 누르면 움직임 다시 시작된다. - 1005



• s: 미로에서 객체가 나타난다. - 100% (명령어: C)

• →/←/↑/↓: 객체를 앞/뒤/좌/우 이동 - 100%(명령어: I/J/K/L)
• +/-: 육면체 이동하는 속도 증가/감소 - 0% (아직 구현 안함)

• 1/3: 카메라 시점 1인칭/3인칭 변환 • 1인칭 시점 (객체 시점)/3인칭 시점 (쿼터뷰 시점) - 80%(1: 객체 생성 이후 가능 / 3인칭 : 복구) 아직 상태 이동에 따른 값 초기화가 진행 안된거같음
• c: 모든 값 초기화 - 100% (-)
• q: 프로그램 종료 - 100%
• *** 키보드 명령어를 콘솔창에 출력한다.

*******추가구현 목록
넘버패드 
   8
  456
을 이용해 맵을 기울일 수 있고 그거에 따라 움직이게 함

*/


#define _CRT_SECURE_NO_WARNINGS
//헤더 파일 목록
#include <Windows.h>
#include <iostream>
#include <gl/glew.h> 
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <random>

//define 목록
#define WIDTH 1600
#define HEIGHT 1200
#define MaxRowColumn 30
#define PillarMinHeight 5
#define PillarMaxHeight 80

#define InclineMax 25.0
//월드관련 define
#define ObjectSize 1
#define GroundSize 200
#define WorldSize 600		


//enum 관련
enum XYZ { X = 0, Y = 1, Z = 2 };
enum RGB { R = 0, G = 1, B = 2 };
enum VAOCOUNT { POS = 0, COLOR = 1, INDEX = 2 };
enum TimerFlag { IS_ON = 0, TURN_OFF = 1 };
enum CameraType{PRINT=0,MAIN = 1, UP = 2};
enum CameraInitType{FirstView = 1, ThirdView = 3};
enum PillarState{WALL=0, EMPTY=1, NOTHING = 2};
enum GOTO{PRESSI = 0, PRESSK = 1 , PRESSJ = 2, PRESSL = 3};
enum FACE { Z_DOWN = 0, Z_UP = 1, X_DOWN = 2, X_UP = 3 };
//class 관련
class Ground {
public:
	GLfloat pos[4][3];
	GLfloat color[4][3];
	GLuint index[2][3];

	GLuint VAO, VBO[3];
	void init();
	void draw();
};

class Pillar {
public:
	GLfloat first_S[3];
	GLfloat T[3];
	GLfloat temp_rgb[3];

	GLboolean start_init;	//처음 만들고 떨어질 때에 대한 체크 불리안 변수
	GLfloat updown;		//위아래 이동에 대한 체크 불리안 변수
	GLboolean state;	//WALL, EMPTY 등의 데이터를 가짐


	GLuint VAO, VBO[3];
	void init();
	void draw();
	void setting(int i, int j);
};

class Ball {
public:
	GLfloat T[3];

	GLfloat S[3];
	int Face=0;

	void draw();
};
//glut 관련 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid SpecialKeyboard(int, int, int);

//셰이더 관련 함수 및 변수
char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitShader();
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;

//VAO, VBO 관련 함수 및 변수

GLvoid InitBuffer();

//카메라 관련 함수 및 변수
glm::vec3 cameraPos[3];
glm::vec3 cameraDirection[3];
glm::vec3 cameraUp[3];
GLboolean flag_perspective_projection = true;
GLvoid CameraInit(int type);
GLvoid CameraFirstViewMove(int value);

//타이머 관련 함수
GLint TimerSpeed = 16;

GLvoid InitPillar(int value);
GLboolean flag_init_timer[2];

GLvoid PillarUpDown(int value);
GLboolean flag_pillar_updown[2];

//내가 만든 함수 와 변수
GLvoid InitValue();
GLvoid SetTransformMatrix();
GLint row, column;
GLvoid GetRowColumn();
GLvoid GetNormalVector(glm::vec3 upvector, glm::vec3 dirvector, GLfloat out[3]);
GLboolean flag_cull_face = false;
GLboolean flag_depth_test = false;
GLboolean flag_draw_line = false;

GLboolean flag_event_v = false;
GLvoid ChangeDegree(GLfloat);

GLvoid MakeMaze();


GLfloat cube_pos[8][3];
GLfloat cube_color[8][3];
GLuint cube_index[12][3];
Ground ground;
Pillar pillar[MaxRowColumn][MaxRowColumn];

//공 객체 관련
GLboolean draw_ball = false;
Ball ball;
GLboolean BallCollidePillar(int r, int c);
GLvoid BallMoveCheck(int value, GLfloat move = 0.0f);

GLfloat incline[3];
glm::vec3 gravityVector;
GLboolean flag_incline[2];
GLvoid BallGravity(int value);
GLboolean flag_firstview = false;

std::random_device rd;
std::uniform_real_distribution<GLfloat> ufd_color(0.0f, 1.0f);
std::uniform_int_distribution<int> uid(0, 1);
std::uniform_real_distribution<GLfloat> ufd_speed(0.3f, 1.8f);

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Computer Graphics 2019180031 homework");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	InitValue();
	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutSpecialFunc(SpecialKeyboard);

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{//Main Draw
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		cameraPos[PRINT] = cameraPos[MAIN];
		cameraDirection[PRINT] = cameraDirection[MAIN];
		cameraUp[PRINT] = cameraUp[MAIN];

		SetTransformMatrix();	//변환행렬들 세팅

		ground.draw();			//ground draw
		if (5 <= row and row <= MaxRowColumn and 5 <= column and column <= MaxRowColumn) {
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < column; ++j) {
					pillar[i][j].draw();
				}
			}
		}
		if (draw_ball) {
			ball.draw();
		}
	}

	{//Top View Draw
		glViewport(glutGet(GLUT_WINDOW_WIDTH)/4*3, glutGet(GLUT_WINDOW_HEIGHT)/4*3, glutGet(GLUT_WINDOW_WIDTH)/4, glutGet(GLUT_WINDOW_HEIGHT)/4);
		glDisable(GL_DEPTH_TEST);
		cameraPos[PRINT] = cameraPos[UP];
		cameraDirection[PRINT] = cameraDirection[UP];
		cameraUp[PRINT] = cameraUp[UP];

		SetTransformMatrix();	//변환행렬들 세팅

		ground.draw();			//ground draw
		if (5 <= row and row <= MaxRowColumn and 5 <= column and column <= MaxRowColumn) {
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < column; ++j) {
					pillar[i][j].draw();
				}
			}
		}
		if (draw_ball) {
			ball.draw();
		}
		glEnable(GL_DEPTH_TEST);
	}

	
	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'a':	//카메라 왼쪽 이동
	{
		GLfloat normal[3] = {0.0f,0.0f,0.0f};
		GetNormalVector(cameraUp[MAIN], cameraDirection[MAIN], normal);
	
		cameraPos[MAIN].x -= normal[X]*3;
		cameraPos[MAIN].y -= normal[Y]*3;
		cameraPos[MAIN].z -= normal[Z]*3;
	}
		
		break;
	case 'd':	//카메라 오른쪽 이동
	{
		GLfloat normal[3] = { 0.0f,0.0f,0.0f };
		GetNormalVector(cameraUp[MAIN], cameraDirection[MAIN], normal);

		cameraPos[MAIN].x += normal[X] * 3;
		cameraPos[MAIN].y += normal[Y] * 3;
		cameraPos[MAIN].z += normal[Z] * 3;
	}
		break;
	case 'w':	//카메라 위쪽 이동
		cameraPos[MAIN].y += WorldSize / 100;
		cameraPos[MAIN].x += cameraUp[MAIN][X] * 3;
		cameraPos[MAIN].y += cameraUp[MAIN][Y] * 3;
		cameraPos[MAIN].z += cameraUp[MAIN][Z] * 3;
		break;
	case 's':	//카메라 아래쪽 이동
		cameraPos[MAIN].y -= WorldSize / 100;
		break;
	case '+':
		if (flag_init_timer[IS_ON]) {
			printf("이미 제작 중입니다. 새로 변경하시려면 블럭이 다 떨어질 때 까지 기다려주세요.\n");
			break;
		}
		InitValue();
		GetRowColumn();
		if (5 <= row and row <= MaxRowColumn and 5 <= column and column <= MaxRowColumn) {
			for (int i = 0; i < MaxRowColumn; ++i) {
				for (int j = 0; j < MaxRowColumn; ++j) {
					pillar[i][j].setting(i, j);
				}
			}
		}
		glutTimerFunc(TimerSpeed, InitPillar, 0);
		flag_init_timer[IS_ON] = true;
		break;
	case '-':
		InitValue();
		break;
	case 'M':
	case 'm':
		if (flag_init_timer[IS_ON]) {
			printf("아직 기둥이 내려오는 중이라 명령어를 진행할 수 없습니다.\n");
			break;
		}
		if (5 <= row and row <= MaxRowColumn and 5 <= column and column <= MaxRowColumn) {
			if (flag_pillar_updown[IS_ON]) {
				flag_pillar_updown[TURN_OFF] = true;
			}
			else {
				flag_pillar_updown[IS_ON] = true;
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						pillar[i][j].updown = ufd_speed(rd);
					}
				}
				glutTimerFunc(TimerSpeed, PillarUpDown, 0);
			}
			

		}
		break;
	case 'o':
	case 'O':
		flag_perspective_projection = 1 - flag_perspective_projection;
		break;
	case 'y':
	{
		glm::mat4 CR = glm::mat4(1.0f);
		glm::vec4 temp;
		temp = glm::vec4(cameraPos[MAIN], 1.0f);
		CR = glm::rotate(CR, glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));
		temp = CR * temp;
		cameraPos[MAIN][X] = temp.x, cameraPos[MAIN][Y] = temp.y, cameraPos[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraDirection[MAIN], 1.0f);
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
	}
		break;
	case 'Y': 
	{
		glm::mat4 CR = glm::mat4(1.0f);
		glm::vec4 temp;
		temp = glm::vec4(cameraPos[MAIN], 1.0f);
		CR = glm::rotate(CR, glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));
		temp = CR * temp;
		cameraPos[MAIN][X] = temp.x, cameraPos[MAIN][Y] = temp.y, cameraPos[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraDirection[MAIN], 1.0f);
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
	}
		break;
	case 'V':
	case 'v':
		if (flag_init_timer[IS_ON]) {
			printf("아직 기둥이 내려오는 중이라 명령어를 진행할 수 없습니다.\n");
			break;
		}
		if (5 <= row and row <= MaxRowColumn and 5 <= column and column <= MaxRowColumn) {
			if (flag_pillar_updown[IS_ON]) {
				flag_pillar_updown[TURN_OFF] = true;
			}
			flag_event_v = 1 - flag_event_v;
		}
		break;
	case 'R':
	case 'r'://미로 만들기
		if (draw_ball) {
			printf("이미 객체가 놓여져있어 미로를 재생성 할 수 없습니다.\n");
			printf("객체를 없애고(C/c) 다시 눌러 미로를 재생성 해주세요.\n");
		}
		//InitValue();
		MakeMaze();
		break;
	case 'c':
	case 'C':
		if (flag_init_timer) {
			printf("아직 기둥이 내려가는 중이라 객체를 생성할 수 없습니다.\n");
			printf("미로를 생성 한 뒤 객체를 생성해주세요.\n");
		}
		if (draw_ball) {
			
		}
		else {
			GLfloat scale;
			if (pillar[0][1].first_S[X] <= pillar[0][1].first_S[Z])
				scale = pillar[0][1].first_S[X];
			else
				scale = pillar[0][1].first_S[Z];
			
			for (int i = 0; i < 3; ++i) {
				ball.S[i] = scale/3*2;
				ball.T[i] = pillar[0][1].T[i];
			}
			ball.T[Y] += ball.S[Y];
		}
		draw_ball = 1 - draw_ball;
		break;
	case 'i':
		if (flag_firstview) {
			CameraFirstViewMove(PRESSI);
			glm::vec4 cd = glm::vec4(cameraDirection[MAIN], 1.0f);
		
			if (cd[X] < 0) {
				BallMoveCheck(X_DOWN, cd[X] * 2);
			}
			else if (cd[X] > 0) {
				BallMoveCheck(X_UP, cd[X] * 2);
			}
			if (cd[Z] < 0) {
				BallMoveCheck(Z_DOWN, cd[Z] * 2);
			}
			else if (cd[Z] > 0) {
				BallMoveCheck(Z_UP, cd[Z] * 2);
			}
		}
		else {
			BallMoveCheck(PRESSI);
		}
		break;
	case 'j':
		if (flag_firstview) {
			CameraFirstViewMove(PRESSJ);
		}
		else {
			BallMoveCheck(PRESSJ);
		}
		break;
	case 'k':
		if (flag_firstview) {
			
		}
		else {
			BallMoveCheck(PRESSK);
		}
		break;
	case 'l':
		if (flag_firstview) {
			CameraFirstViewMove(PRESSL);
		}
		else {
			BallMoveCheck(PRESSL);
		}
		break;
	case '4':
		//Z축 양의방향 회전
		if (flag_firstview) {
			printf("1인칭 상태에선 기울일 수 없습니다.\n");
			break;
		}
		if (!flag_incline[IS_ON]) {
			flag_incline[IS_ON] = true;
			glutTimerFunc(TimerSpeed, BallGravity, 0);
		}
		incline[Z] += 1.0f;
		if (incline[Z] >= InclineMax) incline[Z] = InclineMax;
		break;
	case '5':
		//X축 양의방향 회전
		if (flag_firstview) {
			printf("1인칭 상태에선 기울일 수 없습니다.\n");
			break;
		}
		if (!flag_incline[IS_ON]) {
			flag_incline[IS_ON] = true;
			glutTimerFunc(TimerSpeed, BallGravity, 0);
		}
		incline[X] += 1.0f;
		if (incline[X] >= InclineMax) incline[X] = InclineMax;
		break;
	case '6':
		//Z축 음의방향 회전
		if (flag_firstview) {
			printf("1인칭 상태에선 기울일 수 없습니다.\n");
			break;
		}
		if (!flag_incline[IS_ON]) {
			flag_incline[IS_ON] = true;
			glutTimerFunc(TimerSpeed, BallGravity, 0);
		}
		incline[Z] -= 1.0f;
		if (incline[Z] <= -InclineMax) incline[Z] = -InclineMax;
		break;
	case '8':
		//X축 음의방향 회전
		if (flag_firstview) {
			printf("1인칭 상태에선 기울일 수 없습니다.\n");
			break;
		}
		if (!flag_incline[IS_ON]) {
			flag_incline[IS_ON] = true;
			glutTimerFunc(TimerSpeed, BallGravity, 0);
		}
		incline[X] -= 1.0f;
		if (incline[X] <= -InclineMax) incline[X] = -InclineMax;
		break;
	case '1'://1인칭 시점
		if (flag_incline[IS_ON]) {
			incline[X] = 0.0f;
			incline[Z] = 0.0f;
			flag_incline[TURN_OFF] = true;
		}
		if (!draw_ball) {
			printf("아직 객체가 없어 1인칭 시점을 사용할 수 없습니다.\n");
			break;
		}
		flag_firstview = true;
		CameraInit(FirstView);
		break;
	case '3'://3인칭 시점
		flag_firstview = false;
		CameraInit(ThirdView);
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y) {
	
	glm::mat4 CR = glm::mat4(1.0f);
	glm::vec4 temp = glm::vec4(cameraDirection[MAIN], 1.0f);
	GLfloat normal[3] = {0.0f,0.0f,0.0f};
	glm::vec3 tt;
	switch (key) {
	case GLUT_KEY_LEFT:
		CR = glm::rotate(CR, glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0)); 
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
		break;
	case GLUT_KEY_RIGHT:
		CR = glm::rotate(CR, glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
		break;
	case GLUT_KEY_UP:
		GetNormalVector(cameraUp[MAIN], cameraDirection[MAIN], normal);
		tt = glm::normalize(glm::vec3(normal[X],normal[Y],normal[Z]));
		CR = glm::rotate(CR, glm::radians(5.0f), glm::vec3(tt.x,tt.y,tt.z));
		
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
		break;
	case GLUT_KEY_DOWN:
		GetNormalVector(cameraDirection[MAIN], cameraUp[MAIN], normal);
		tt = glm::normalize(glm::vec3(normal[X], normal[Y], normal[Z]));
		CR = glm::rotate(CR, glm::radians(5.0f), glm::vec3(tt.x, tt.y, tt.z));
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
		break;

	}
	
	
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN

	std::cout << "cameraDirection[MAIN]: " << cameraDirection[MAIN].x << " / " << cameraDirection[MAIN].y << " / " << cameraDirection[MAIN].z << std::endl;
	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case 3:			//마우스휠 위로 역할
			cameraPos[MAIN].x += cameraDirection[MAIN].x * 3;
			cameraPos[MAIN].y += cameraDirection[MAIN].y * 3;
			cameraPos[MAIN].z += cameraDirection[MAIN].z * 3;
			break;
		case 4:			//마우스휠 아래로 역할
			cameraPos[MAIN].x -= cameraDirection[MAIN].x * 3;
			cameraPos[MAIN].y -= cameraDirection[MAIN].y * 3;
			cameraPos[MAIN].z -= cameraDirection[MAIN].z * 3;
			break;
		}
		break;
	case GLUT_UP:
		break;

	}
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {

	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, w, h);
}
GLvoid InitBuffer() {
	{//ground
		glGenVertexArrays(1, &ground.VAO);
		glGenBuffers(3, ground.VBO);
	}
	
	{//Pillar
		for (int i = 0; i < MaxRowColumn; ++i) {
			for (int j = 0; j < MaxRowColumn; ++j) {
				glGenVertexArrays(1, &pillar[i][j].VAO);
				glGenBuffers(3, pillar[i][j].VBO);
			}
		}
	}
}
GLvoid CameraInit(int type) {
	if (type == FirstView) {
		ball.Face = PRESSI;
		cameraPos[MAIN] = glm::vec3(ball.T[X], ball.T[Y] + 8.0f, ball.T[Z] + ball.S[Z]);
		
		cameraDirection[MAIN] = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::mat4 CR = glm::mat4(1.0f);
		CR = glm::rotate(CR, glm::radians(-20.0f), glm::vec3(1.0, 0.0, 0.0));
		glm::vec4 temp = glm::vec4(cameraDirection[MAIN], 1.0f);
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;

		cameraUp[MAIN] = glm::vec3(0.0f, 1.0f, 0.0f);
		/*CR = glm::mat4(1.0f);
		CR = glm::rotate(CR, glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;*/
	}
	else if(type == ThirdView) {
		cameraPos[MAIN] = glm::vec3(0.0f, WorldSize / 2, WorldSize/4*3);
		cameraDirection[MAIN] = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::mat4 CR = glm::mat4(1.0f);
		CR = glm::rotate(CR, glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
		glm::vec4 temp = glm::vec4(cameraDirection[MAIN], 1.0f);
		temp = CR * temp;
		cameraDirection[MAIN][X] = temp.x, cameraDirection[MAIN][Y] = temp.y, cameraDirection[MAIN][Z] = temp.z;
		cameraUp[MAIN] = glm::vec3(0.0f, 1.0f, 0.0f);
		CR = glm::mat4(1.0f);
		CR = glm::rotate(CR, glm::radians(-30.0f), glm::vec3(1.0, 0.0, 0.0));
		temp = glm::vec4(cameraUp[MAIN], 1.0f);
		temp = CR * temp;
		cameraUp[MAIN][X] = temp.x, cameraUp[MAIN][Y] = temp.y, cameraUp[MAIN][Z] = temp.z;
	}

	cameraPos[UP] = glm::vec3(0.0f, WorldSize / 2, 0.0f);
	cameraDirection[UP] = glm::vec3(0.0f, -1.0f, 0.0f);
	cameraUp[UP] = glm::vec3(0.0f, 0.0f, -1.0f);

	flag_perspective_projection = true;
	
}

GLvoid InitValue() {
	{//깊이 컬링 관련 초기화
		glEnable(GL_DEPTH_TEST);
		flag_depth_test = true;
		/*glEnable(GL_CULL_FACE);
		flag_cull_face = true;*/
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		flag_draw_line = true;*/
	}

	{//카메라 관련 초기화
		CameraInit(ThirdView);
	}

	{//Ground 관련 초기화
		ground.init();
	}

	{//Pillar 관련
		row = 0, column = 0;
		for (int i = 0; i < MaxRowColumn; ++i) {
			for (int j = 0; j < MaxRowColumn; ++j) {
				pillar[i][j].init();
			}
		}
	}

	{//cube 초기화
		if (cube_pos[0][0] == 0) {	//초기한번만 하도록
			cube_pos[0][X] = cube_pos[1][X] = cube_pos[4][X] = cube_pos[7][X] = -ObjectSize;
			cube_pos[2][X] = cube_pos[3][X] = cube_pos[5][X] = cube_pos[6][X] = ObjectSize;
			cube_pos[0][Y] = cube_pos[1][Y] = cube_pos[2][Y] = cube_pos[3][Y] = ObjectSize*2;
			cube_pos[4][Y] = cube_pos[5][Y] = cube_pos[6][Y] = cube_pos[7][Y] = 0;
			cube_pos[0][Z] = cube_pos[3][Z] = cube_pos[6][Z] = cube_pos[7][Z] = -ObjectSize;
			cube_pos[1][Z] = cube_pos[2][Z] = cube_pos[4][Z] = cube_pos[5][Z] = ObjectSize;

			cube_index[0][X] = 0, cube_index[0][Y] = 1, cube_index[0][Z] = 2;
			cube_index[1][X] = 0, cube_index[1][Y] = 2, cube_index[1][Z] = 3;
			cube_index[2][X] = 1, cube_index[2][Y] = 4, cube_index[2][Z] = 5;
			cube_index[3][X] = 1, cube_index[3][Y] = 5, cube_index[3][Z] = 2;
			cube_index[4][X] = 2, cube_index[4][Y] = 5, cube_index[4][Z] = 6;
			cube_index[5][X] = 2, cube_index[5][Y] = 6, cube_index[5][Z] = 3;
			cube_index[6][X] = 3, cube_index[6][Y] = 6, cube_index[6][Z] = 7;
			cube_index[7][X] = 3, cube_index[7][Y] = 7, cube_index[7][Z] = 0;
			cube_index[8][X] = 0, cube_index[8][Y] = 7, cube_index[8][Z] = 4;
			cube_index[9][X] = 0, cube_index[9][Y] = 4, cube_index[9][Z] = 1;
			cube_index[10][X] = 6, cube_index[10][Y] = 5, cube_index[10][Z] = 4;
			cube_index[11][X] = 6, cube_index[11][Y] = 4, cube_index[11][Z] = 7;

			cube_color[0][R] = 0.4f, cube_color[0][G] = 0.4f, cube_color[0][B] = 0.4f;
			cube_color[1][R] = 0.4f, cube_color[1][G] = 0.4f, cube_color[1][B] = 0.4f;
			cube_color[2][R] = 0.4f, cube_color[2][G] = 0.4f, cube_color[2][B] = 0.4f;
			cube_color[3][R] = 0.4f, cube_color[3][G] = 0.4f, cube_color[3][B] = 0.4f;
			cube_color[4][R] = 0.4f, cube_color[4][G] = 0.4f, cube_color[4][B] = 0.4f;
			cube_color[5][R] = 0.4f, cube_color[5][G] = 0.4f, cube_color[5][B] = 0.4f;
			cube_color[6][R] = 0.4f, cube_color[6][G] = 0.4f, cube_color[6][B] = 0.4f;
			cube_color[7][R] = 0.4f, cube_color[7][G] = 0.4f, cube_color[7][B] = 0.4f;
		}
	}


	{//경사 관련
		for (int i = 0; i < 3; ++i) {
			incline[i] = 0.0f;
		}
		gravityVector = glm::vec3(0.0f, -1.0f, 0.0f);

	}
}

GLvoid SetTransformMatrix() {
	{//model 변환
		glm::mat4 TR = glm::mat4(1.0f);
		if (flag_incline[IS_ON]) {
			glm::mat4 inclineR = glm::mat4(1.0f);
			inclineR = glm::rotate(inclineR, glm::radians(incline[X]), glm::vec3(1.0f, 0.0f, 0.0f));
			inclineR = glm::rotate(inclineR, glm::radians(incline[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
			TR = inclineR * TR;
		}
		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	}

	{//카메라 변환
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos[PRINT], cameraPos[PRINT] + cameraDirection[PRINT], cameraUp[PRINT]);
		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	}
	
	{//투영변환
		glm::mat4 projection = glm::mat4(1.0f);
		if (flag_perspective_projection) {	//원근
			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize*3);
			//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
		}
		else {	//직각
			GLfloat halfsize = WorldSize;
			projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
		}
		

		unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
	}
}

GLvoid ChangeDegree(GLfloat degree) {
	if (degree < 0.0f) {
		degree += 360.0f;
	}
	else {
		degree -= 360.0f;
	}
}









//타이머 관련 함수
GLvoid InitPillar(int value) {
	
	GLboolean escape = true;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (pillar[i][j].start_init) {
				escape = false;
				pillar[i][j].T[Y] -= 1;
				if (pillar[i][j].T[Y] <= -50) {
					pillar[i][j].T[Y] = -50;
					pillar[i][j].start_init = false;
				}
			}
		}
	}

	if (escape) {
		
		flag_init_timer[IS_ON] = false; 
		return;
	}

	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, InitPillar, 0);

}

GLvoid PillarUpDown(int value) {
	if (flag_pillar_updown[TURN_OFF]) {
		flag_pillar_updown[IS_ON] = false;
		flag_pillar_updown[TURN_OFF] = false;
		
		return;
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (0.3<= abs(pillar[i][j].updown) and abs(pillar[i][j].updown)<=1.8) {
				pillar[i][j].first_S[Y] += pillar[i][j].updown;
				if (pillar[i][j].first_S[Y] > PillarMaxHeight) {
					pillar[i][j].first_S[Y] = PillarMaxHeight;
					pillar[i][j].updown *= -1;
				}
				if (pillar[i][j].first_S[Y] < PillarMinHeight) {
					pillar[i][j].first_S[Y] = PillarMinHeight;
					pillar[i][j].updown *= -1;
				}
			}	
		}
	}


	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, PillarUpDown, 0);
}















//내가 만든 함수들 정의
GLvoid GetRowColumn() {
	while (1) {
		system("cls");
		std::cout << "가로 x 세로 : ";
		bool check_row = false, check_column = false;
		if (std::cin >> row) {
			if (5 <= row && row <= MaxRowColumn)
				check_row = true;
		}
		if (std::cin >> column) {
			if (5 <= column && column <= MaxRowColumn)
				check_column = true;
		}
		if (check_row && check_column) break;
		std::cout << "잘못된 입력 다시 입력 바람" << std::endl;
		system("pause");
	}
	std::cout << "가로: " << row << "세로: " << column << " 입력 하셨습니다." << std::endl;
}

GLvoid GetNormalVector(glm::vec3 upvector, glm::vec3 dirvector, GLfloat out[3]) {
	out[X] = dirvector[Y] * upvector[Z] - dirvector[Z] * upvector[Y];
	out[Y] = dirvector[Z] * upvector[X] - dirvector[X] * upvector[Z];
	out[Z] = dirvector[X] * upvector[Y] - dirvector[Y] * upvector[X];
}

GLvoid MakeMaze() {
	if (flag_init_timer[IS_ON]) {
		printf("블럭이 떨어진 뒤 미로를 생성할 수 있습니다.\n");
		return;
	}
	if (not (5 <= row and row <= MaxRowColumn and 5 <= column and column < MaxRowColumn)) {
		printf("아직 기둥을 생성하지 않아 미로를 만들 수 없습니다.\n");
		return;
	}
	if (flag_pillar_updown[IS_ON]) {
		flag_pillar_updown[TURN_OFF] = true;
	}
	flag_event_v = true;
	//WALL, EMPTY 뚫기
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (i == 0 || i == row-1 || j == 0 || j == column-1) {
				pillar[i][j].state = WALL;
				continue;
			}
			if (i % 2 == 0 || j % 2 == 0) {
				pillar[i][j].state = WALL;
				continue;
			}
			pillar[i][j].state = EMPTY;
		}
	}

	//뚫린곳 오른쪽 밑에 중 1 뚫기
	for (int i = 0; i < row-1; ++i) {
		for (int j = 0; j < column-1; ++j) {
			if (i%2==0||j%2==0) continue;
			if (uid(rd) == 0) {
				pillar[i + 1][j].state = EMPTY;
			}
			else {
				pillar[i][j + 1].state = EMPTY;
			}
		}
	}
	
	//외각지 벽으로
	for (int i = 0; i < row; ++i) {
		pillar[i][column - 1].state = WALL;
	}
	for (int j = 0; j < column; ++j) {
		pillar[row - 1][j].state = WALL;
	}

	//최종 길뚫기
	int i = 1, j = 1;
	while (1) {
		
		if (i == row - 2 and j == column - 2) break;
		else if (i == row - 2) {
			pillar[i][j + 1].state = EMPTY;
			j += 1;
			continue;
		}
		else if (j == column - 2) {
			pillar[i + 1][j].state = EMPTY;
			i += 1;
			continue;
		}
		if (pillar[i + 1][j].state == EMPTY) {
			i += 1;
		}
		else if(pillar[i][j + 1].state == EMPTY) {
			j += 1;
		}
	}

	//입구와 출구 뚫기
	pillar[0][1].state = EMPTY;
	pillar[row - 1][column - 2].state = EMPTY;
}







//공객체 관련 함수 정의
GLboolean BallCollidePillar(int r, int c) {
	GLboolean check_x=false, check_z=false;
	if (abs(pillar[r][c].T[X] - ball.T[X]) < abs(pillar[r][c].first_S[X] + ball.S[X])) {
		check_x = true;
	}
	if (abs(pillar[r][c].T[Z] - ball.T[Z]) < abs(pillar[r][c].first_S[Z] + ball.S[Z])) {
		check_z = true;
	}
	if (check_x && check_z) return true;
	return false;
}

GLvoid CameraFirstViewMove(int value) {
	GLfloat posrate = 0.8;
	
	cameraPos[MAIN] = glm::vec3(ball.T[X], ball.T[Y] + 8.0f, ball.T[Z]);

	glm::vec4 temp = glm::vec4(cameraDirection[MAIN], 1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	switch (value) {
	case PRESSJ:
		Ry = glm::rotate(Ry, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case PRESSL:
		Ry = glm::rotate(Ry, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	}
	temp = Ry * temp;
	cameraDirection[MAIN][X] = temp[X];
	cameraDirection[MAIN][Y] = temp[Y];
	cameraDirection[MAIN][Z] = temp[Z];
}
GLvoid BallMoveCheck(int value, GLfloat move) {
	switch (value) {
	case PRESSI:
		if (move == 0.0f) {
			ball.T[Z] -= ball.S[Z] / 5;
		}
		else {
			ball.T[Z] += move * (ball.S[X] / 5);
		}
		break;
	case PRESSK:
		if (move == 0.0f) {
			ball.T[Z] += ball.S[Z] / 5;
		}
		else {
			ball.T[Z] += move * (ball.S[X] / 5);
		}
		break;
	case PRESSJ:
		if (move == 0.0f) {
			ball.T[X] -= ball.S[X] / 5;
		}
		else {
			ball.T[X] += move * (ball.S[X] / 5);
		}
		break;
	case PRESSL:
		if (move == 0.0f) {
			ball.T[X] += ball.S[X] / 5;
		}
		else {
			ball.T[X] += move * (ball.S[X] / 5);
		}
		break;
	}


	if (ball.T[Z] + ball.S[Z] > GroundSize / 2) {
		ball.T[Z] = GroundSize / 2 - ball.S[Z];
	}
	else if (ball.T[Z] - ball.S[Z] < -GroundSize / 2) {
		ball.T[Z] = -GroundSize / 2 + ball.S[Z];
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (pillar[i][j].state == EMPTY) continue;
			if (BallCollidePillar(i, j)) {
				GLfloat gap = 0.01;
				switch (value) {
				case PRESSI:
					ball.T[Z] = pillar[i][j].T[Z] + pillar[i][j].first_S[Z] + ball.S[Z] + gap;
					break;
				case PRESSK:
					ball.T[Z] = pillar[i][j].T[Z] - pillar[i][j].first_S[Z] - ball.S[Z] - gap;

					break;
				case PRESSJ:
					ball.T[X] = pillar[i][j].T[X] + pillar[i][j].first_S[X] + ball.S[X] + gap;
					break;
				case PRESSL:
					ball.T[X] = pillar[i][j].T[X] - pillar[i][j].first_S[X] - ball.S[X] - gap;
					break;
				}

			}
		}
	}
	
	
	
}
                                        
GLvoid BallGravity(int value) {
	glm::vec4 gv = glm::vec4(gravityVector, 1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(incline[X]), glm::vec3(1.0f, 0.0f, 0.0f));
	Rz = glm::rotate(Rz, glm::radians(incline[Z]), glm::vec3(0.0f, 0.0f, 1.0f));

	gv = Rz * Rx * gv;
	if (gv[X] < 0) {	
		BallMoveCheck(PRESSL, -gv[X]*2);
	}
	else if (gv[X] > 0) {
		BallMoveCheck(PRESSJ, -gv[X]*2);
	}
	if (gv[Z] < 0) {	
		BallMoveCheck(PRESSK, -gv[Z]*2);
	}
	else if (gv[Z] > 0) {
		BallMoveCheck(PRESSI, -gv[Z]*2);
	}


	glutTimerFunc(TimerSpeed, BallGravity, 0);
	glutPostRedisplay();
}



//클래스 전역함수 정의
void Ground::init() {
	{//pos init
		pos[0][X] = -GroundSize / 2; pos[0][Y] = -50; pos[0][Z] = -GroundSize / 2;
		pos[1][X] = -GroundSize / 2; pos[1][Y] = -50; pos[1][Z] = +GroundSize / 2;
		pos[2][X] = +GroundSize / 2; pos[2][Y] = -50; pos[2][Z] = +GroundSize / 2;
		pos[3][X] = +GroundSize / 2; pos[3][Y] = -50; pos[3][Z] = -GroundSize / 2;
	}
	{//color init
		color[0][X] = 0.85f; color[0][Y] = 0.85f; color[0][Z] = 0.85f;
		color[1][X] = 0.85f; color[1][Y] = 0.85f; color[1][Z] = 0.85f;
		color[2][X] = 0.85f; color[2][Y] = 0.85f; color[2][Z] = 0.85f;
		color[3][X] = 0.85f; color[3][Y] = 0.85f; color[3][Z] = 0.85f;
	}
	{//index init
		index[0][0] = 0; index[0][1] = 1; index[0][2] = 2;
		index[1][0] = 0; index[1][1] = 2; index[1][2] = 3;
	}
}
void Ground::draw() {
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	
	glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_INT, (void*)0);
}
void Pillar::init() {
	first_S[X] = 1.0f, first_S[Y] = 1.0f, first_S[Z] = 1.0f;
	T[X] = 0.0f, T[Y] = -50.0f, T[Z] = 0.0f;
	temp_rgb[R] = 0.0f, temp_rgb[G] = 0.0f, temp_rgb[B] = 0.0f;
	updown = 0;
	state = NOTHING;
}
void Pillar::draw() {
	if (state == EMPTY) return;
	{//model 변환
		glm::mat4 TR = glm::mat4(1.0f);
		glm::mat4 S = glm::mat4(1.0f);
		glm::mat4 T = glm::mat4(1.0f);
		if (flag_event_v) {
			S = glm::scale(S, glm::vec3(first_S[X], 5.0f, first_S[Z]));
			
		}
		
		else {
			S = glm::scale(S, glm::vec3(first_S[X], first_S[Y], first_S[Z]));
		}
		
		T = glm::translate(T, glm::vec3(this->T[X], this->T[Y], this->T[Z]));
		TR = T * S;

		if (flag_incline[IS_ON]) {
			glm::mat4 inclineR = glm::mat4(1.0f);
			inclineR = glm::rotate(inclineR, glm::radians(incline[X]), glm::vec3(1.0f, 0.0f, 0.0f));
			inclineR = glm::rotate(inclineR, glm::radians(incline[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
			TR = inclineR * TR;
		}

		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	}
//	GLfloat temp_color[8][3];
	GLfloat temp_color[8][3] = { temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],};
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, (void*)0);
}
std::uniform_real_distribution<GLfloat> ufd_y(PillarMinHeight, PillarMaxHeight);
void Pillar::setting(int i, int j) {
	GLfloat length_x = GLfloat(GroundSize) / column, length_z = GLfloat(GroundSize) / row;
	
	first_S[X] = length_x/2; first_S[Z] = length_z/2;
	first_S[Y] = ufd_y(rd);
	T[Y] = 150 + (PillarMaxHeight - first_S[Y]*2);
	
	
	if (row % 2 == 0) { //row 가 짝수 일 때,
		int mid = row / 2;
		if (i < mid) {	//앞쪽
			T[Z] = length_z / 2 + length_z * (mid-i-1);
		}
		else {	//뒷쪽
			T[Z] = -length_z / 2 - length_z * (i - mid);
		}
	}
	else {	//row 가 홀수 일 때,
		int mid = row / 2;
		if (i == mid) {	//중간

		}
		else {	//뒷쪽 and 앞쪽
			T[Z] = length_z * (mid-i);
		}
	}
	if (column % 2 == 0) { //column 가 짝수 일 때,
		int mid = column / 2;
		if (i < mid) {	//앞쪽
			T[X] = length_x / 2 + length_x * (j - mid);
		}
		else {	//뒷쪽
			T[X] = -length_x / 2 - length_x * (mid - j - 1);
		}
	} 
	else {	//column 가 홀수 일 때,
		int mid = column / 2;
		if (j == mid) {	//중간

		}
		else {
			T[X] = length_x * (j - mid);
		}
	}
	temp_rgb[R] = ufd_color(rd), temp_rgb[G] = ufd_color(rd), temp_rgb[B] = ufd_color(rd);
	//TODO: 나중에 색 조정하기
	//temp_rgb[R] = 1.0f, temp_rgb[G] = 0.0f, temp_rgb[B] = 0.0f;
	start_init = true;
	updown = 0;
	state = NOTHING;
}

void Ball::draw() {
	GLUquadricObj* qobj = gluNewQuadric();
	{//model 변환
		glm::mat4 TR = glm::mat4(1.0f);
		glm::mat4 Sc = glm::mat4(1.0f);
		glm::mat4 T = glm::mat4(1.0f);
		Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
		T = glm::translate(T, glm::vec3(this->T[X], this->T[Y], this->T[Z]));
		TR = T * Sc;
		if (flag_incline[IS_ON]) {
			glm::mat4 inclineR = glm::mat4(1.0f);
			inclineR = glm::rotate(inclineR, glm::radians(incline[X]), glm::vec3(1.0f, 0.0f, 0.0f));
			inclineR = glm::rotate(inclineR, glm::radians(incline[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
			TR = inclineR * TR;
		}
		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	}
	gluSphere(qobj, 1, 50, 50);
}


void make_vertexShaders() {
	GLchar* vertexsource;

	vertexsource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexsource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorlog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShader, 512, NULL, errorlog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorlog << std::endl;
		return;
	}
}
void make_fragmentShaders() {
	GLchar* fragmentsource;

	fragmentsource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentsource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorlog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorlog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorlog << std::endl;
		return;
	}
}
GLvoid InitShader() {
	make_vertexShaders();
	make_fragmentShaders();

	s_program = glCreateProgram();

	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);

	checkCompileErrors(s_program, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(s_program);
}
void checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{ 
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}