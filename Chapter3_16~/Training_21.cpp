///*
//---------단축키 설명---------
//
//*/
//
//#define _CRT_SECURE_NO_WARNINGS
////헤더 파일 목록
//#include <iostream>
//#include <gl/glew.h> 
//#include<gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <gl/glm/glm.hpp>
//#include <gl/glm/ext.hpp>
//#include <gl/glm/gtc/matrix_transform.hpp>
//#include <random>
//
////define 목록
//#define WIDTH 800
//#define HEIGHT 600
//
//#define X 0
//#define Y 1
//#define Z 2
//
//#define R 0
//#define G 1
//#define B 2
//
//#define POS 0
//#define COLOR 1
//#define INDEX 2
//
//#define MaxBallNum 10
//
////월드관련 define
//#define ObjectSize 50
//#define WorldSize 200		//x: -100~100 / y: -100~100 / z: 0 ~ 200
//
////enum 관련
//enum SideState { ON = 0, OFF = 1 };
//
////클래스 관련
//class Side {
//public:
//	GLuint VAO, VBO[3];
//	GLfloat pos[4][3];
//	GLfloat color[3];
//	GLuint index[2][3];
//
//	GLboolean state;
//
//	GLfloat rot[3];
//	
//
//	GLvoid init(int idx);
//	GLvoid draw();
//};
//
//class Ball {
//public:
//	GLfloat radius;
//	GLfloat trans[3];
//	GLfloat speed;
//	GLfloat gotovector[3];
//
//	GLvoid init();
//	GLvoid draw();
//	GLvoid make();
//	GLvoid RotateGotoVector(GLfloat rotateDegree);
//};
//
//class Box {
//public:
//	GLfloat size;
//	GLfloat trans[3];
//	GLfloat speed;
//	GLfloat gotovector[3];
//	GLuint VAO, VBO[3];
//
//	GLvoid init(int idx);
//	GLvoid draw(int idx);
//	GLvoid RotateGotoVector(GLfloat rotateDegree);
//};
//
////glut 관련 함수
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid KeyBoard(unsigned char key, int x, int y);
//GLvoid Mouse(int, int, int, int);
//GLvoid MouseMove(int, int);
//GLvoid SpecialKeyboard(int, int, int);
//
////셰이더 관련 함수 및 변수
//char* filetobuf(const char* file);
//void make_vertexShaders();
//void make_fragmentShaders();
//void checkCompileErrors(unsigned int shader, std::string type);
//GLvoid InitShader();
//GLuint vertexShader;
//GLuint fragmentShader;
//GLuint s_program;
//
////VAO, VBO 관련 함수 및 변수
//
//GLvoid InitBuffer();
//
////카메라 관련 함수 및 변수
//glm::vec3 cameraPos;
//glm::vec3 cameraDirection;
//glm::vec3 cameraUp;
//GLboolean flag_perspective_projection = true;
//GLvoid SetTransformMatrix();
//
//
////내가 만든 함수 와 변수
//GLvoid InitValue();
//GLboolean flag_cull_face = false;
//GLboolean flag_depth_test = false;
//GLboolean flag_draw_line = false;
//GLvoid ChangeDegree(GLfloat);
//GLfloat cube_pos[8][3];
//GLfloat cube_color[6][3];
//GLuint cube_index[12][3];
//
//Side side[6];
//Ball ball[MaxBallNum];
//int ball_count;
//Box box[3];
//
////축 관련 함수 와 변수
//GLvoid DrawAxes();
//
////타이머 관련 함수와 변수
//enum TimerTyper { IS_ON = 0, TURN_OFF = 1 };
//enum ObjectGravityType { BALL = 0, BOX = 1 };
//GLvoid ObjectGravity(int value);
//GLboolean flag_ball_gravity[2];
//GLboolean flag_box_gravity[2];
//int TimerSpeed = 16;
//
//
//void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
//{ //--- 윈도우 생성하기
//	glutInit(&argc, argv); // glut 초기화
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitWindowPosition(500, 500);
//	glutInitWindowSize(WIDTH, HEIGHT);
//	glutCreateWindow("Example1");
//	glewExperimental = GL_TRUE;
//	if (glewInit() != GLEW_OK) {
//		std::cerr << "Unable to initialize GLEW" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	else
//		std::cout << "GLEW Initialized\n";
//
//
//	InitValue();
//	InitShader();
//	InitBuffer();
//
//	glutDisplayFunc(drawScene); // 출력 함수의 지정
//	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//	glutKeyboardFunc(KeyBoard);
//	glutMouseFunc(Mouse);
//	glutMotionFunc(MouseMove);
//	glutSpecialFunc(SpecialKeyboard);
//	glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene() {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	SetTransformMatrix();
//	for (int i = 0; i < 6; ++i) {
//		side[i].draw();
//	}
//	
//	for (int i = 0; i < 3; ++i) {
//		box[i].draw(i);
//	}
//	
//	for (int i = 0; i < ball_count; ++i) {
//		ball[i].draw();
//	}
//
//
//
//	glutSwapBuffers(); // 화면에 출력하기
//}
//
//GLvoid KeyBoard(unsigned char key, int x, int y) {
//	switch (key) {
//	case 'Q':
//	case 'q':
//		glutLeaveMainLoop();
//		break;
//	case 'a':	//카메라 왼쪽 이동
//		cameraPos.x -= WorldSize / 100;
//		std::cout << "x: " << cameraPos.x << std::endl;
//		break;
//	case 'd':	//카메라 오른쪽 이동
//		cameraPos.x += WorldSize / 100;
//		std::cout << "x: " << cameraPos.x << std::endl;
//		break;
//	case 'w':	//카메라 위쪽 이동
//		cameraPos.y += WorldSize / 100;
//		std::cout << "y: " << cameraPos.y << std::endl;
//		break;
//	case 's':	//카메라 아래쪽 이동
//		cameraPos.y -= WorldSize / 100;
//		std::cout << "y: " << cameraPos.y << std::endl;
//		break;
//	case 'Y':
//	{
//		glm::vec4 CD = glm::vec4(cameraDirection, 1.0f);
//		glm::vec4 CP = glm::vec4(cameraPos, 1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		Ry = glm::rotate(Ry, glm::radians(3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		CD = Ry * CD;
//		CP = Ry * CP;
//		cameraDirection[X] = CD[X], cameraDirection[Y] = CD[Y], cameraDirection[Z] = CD[Z];
//		cameraPos[X] = CP[X], cameraPos[Y] = CP[Y], cameraPos[Z] = CP[Z];
//	}
//		break;
//	case 'y': 
//	{
//		glm::vec4 CD = glm::vec4(cameraDirection, 1.0f);
//		glm::vec4 CP = glm::vec4(cameraPos, 1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		Ry = glm::rotate(Ry, glm::radians(-3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		CD = Ry * CD;
//		CP = Ry * CP;
//		cameraDirection[X] = CD[X], cameraDirection[Y] = CD[Y], cameraDirection[Z] = CD[Z];
//		cameraPos[X] = CP[X], cameraPos[Y] = CP[Y], cameraPos[Z] = CP[Z];
//	}
//		break;
//	case 'H':
//		for (int i = 0; i < 6; ++i) {
//			side[i].rot[Z] += 3.0f;
//			ChangeDegree(side[i].rot[Z]);
//		}
//		for (int i = 0; i < MaxBallNum; ++i) {
//			ball[i].RotateGotoVector(-3.0f);
//		}
//		for (int i = 0; i < 3; ++i) {
//			box[i].RotateGotoVector(-3.0f);
//		}
//		break;
//	case 'h':
//		for (int i = 0; i < 6; ++i) {
//			side[i].rot[Z] -= 3.0f;
//			ChangeDegree(side[i].rot[Z]);
//		}
//		for (int i = 0; i < MaxBallNum; ++i) {
//			ball[i].RotateGotoVector(3.0f);
//		}
//		for (int i = 0; i < 3; ++i) {
//			box[i].RotateGotoVector(3.0f);
//		}
//		break;
//	case 'B':
//		//공삭제
//		if (ball_count == 0) {
//			printf("현재 공이 없어 공을 삭제할 수 없습니다.\n");
//			break;
//		}
//		ball[ball_count - 1].init();
//		ball_count -= 1;
//		if (ball_count == 0) {
//			flag_ball_gravity[TURN_OFF] = true;
//		}
//		break;
//	case 'b':
//		//공추가
//		if (ball_count == MaxBallNum) {
//			printf("현재 공이 최대치까지 존재하여 추가할 수 없습니다.\n");
//			break;
//		}
//		if (ball_count == 0 && !flag_ball_gravity[IS_ON]) {
//			glutTimerFunc(TimerSpeed, ObjectGravity, BALL);
//			flag_ball_gravity[IS_ON] = true;
//		}
//		ball[ball_count].make();
//		ball_count += 1;
//		break;
//	case '0':
//	
//	case '2':
//	
//	case '4':
//	case '5':
//		if(side[key-'0'].state==ON)
//			side[key - '0'].state = OFF;
//		else
//			side[key - '0'].state = ON;
//		break;
//	}
//
//	glutPostRedisplay();
//}
//
//GLvoid SpecialKeyboard(int key, int x, int y) {
//
//}
//
//GLboolean grab_left = false;
//GLfloat old_x = 0.0f, old_y = 0.0f;
//GLfloat now_x = 0.0f, now_y = 0.0f;
//
//GLvoid Mouse(int button, int state, int x, int y) {
//	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
//	//state - GLUT_UP, GLUT_DOWN
//	if (button == GLUT_LEFT_BUTTON) {
//		if (state == GLUT_DOWN) {
//			grab_left = true;
//			old_x = x;
//			old_y = y;
//		}
//		else {
//			grab_left = false;
//			old_x = old_y = now_x = now_y = 0.0f;
//		}
//		
//		
//	}
//	
//
//	switch (state) {
//	case GLUT_DOWN:
//		switch (button) {
//		case 3:			//마우스휠 위로 역할
//			cameraPos.z -= WorldSize / 100;	//카메라 안쪽으로
//			std::cout << "z: " << cameraPos.z << std::endl;
//			break;
//		case 4:			//마우스휠 아래로 역할
//			cameraPos.z += WorldSize / 100;	//카메라 바깥쪽으로
//			std::cout << "z: " << cameraPos.z << std::endl;
//			break;
//		}
//		break;
//	case GLUT_UP:
//		break;
//
//	}
//	glutPostRedisplay();
//}
//
//GLvoid MouseMove(int x, int y) {
//	if (grab_left) {
//		now_x = x, now_y = y;
//		if (now_x - old_x > 0.1) {	//마우스 오른쪽으로
//			if (now_y - old_y > 0.1) {	//마우스 위로
//				for (int i = 0; i < 6; ++i) {
//					side[i].rot[Z] -= 1.0f;
//					ChangeDegree(side[i].rot[Z]);
//				}
//				for (int i = 0; i < MaxBallNum; ++i) {
//					ball[i].RotateGotoVector(1.0f);
//				}
//				for (int i = 0; i < 3; ++i) {
//					box[i].RotateGotoVector(1.0f);
//				}
//				printf("a");
//			}
//			else if(now_y-old_y<-0.1) {
//				for (int i = 0; i < 6; ++i) {
//					side[i].rot[Z] -= 1.0f;
//					ChangeDegree(side[i].rot[Z]);
//				}
//				for (int i = 0; i < MaxBallNum; ++i) {
//					ball[i].RotateGotoVector(1.0f);
//				}
//				for (int i = 0; i < 3; ++i) {
//					box[i].RotateGotoVector(1.0f);
//				}
//				printf("B");
//			}
//			old_x = now_x;
//			old_y = now_y;
//		}
//		else if(now_x - old_x<-0.1) {
//			if (now_y - old_y > 0.1) {
//				for (int i = 0; i < 6; ++i) {
//					side[i].rot[Z] -= 1.0f;
//					ChangeDegree(side[i].rot[Z]);
//				}
//				for (int i = 0; i < MaxBallNum; ++i) {
//					ball[i].RotateGotoVector(1.0f);
//				}
//				for (int i = 0; i < 3; ++i) {
//					box[i].RotateGotoVector(1.0f);
//				}
//				printf("c");
//			}
//			else if(now_y-old_y <-0.1) {
//				for (int i = 0; i < 6; ++i) {
//					side[i].rot[Z] -= 1.0f;
//					ChangeDegree(side[i].rot[Z]);
//				}
//				for (int i = 0; i < MaxBallNum; ++i) {
//					ball[i].RotateGotoVector(1.0f);
//				}
//				for (int i = 0; i < 3; ++i) {
//					box[i].RotateGotoVector(1.0f);
//				}
//				printf("d");
//			}
//			old_x = now_x;
//			old_y = now_y;
//		}
//	}
//	glutPostRedisplay();
//}
//
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid InitBuffer() {
//	/*glGenVertexArrays(1, &cube_VAO);
//	glGenBuffers(3, cube_VBO);
//	glGenBuffers(3, cube_VBO_for_16);*/
//
//	for (int i = 0; i < 6; ++i) {
//		glGenVertexArrays(1, &side[i].VAO);
//		glGenBuffers(3, side[i].VBO);
//	}
//
//	for (int i = 0; i < 3; ++i) {
//		glGenVertexArrays(1, &box[i].VAO);
//		glGenBuffers(3, box[i].VBO);
//	}
//
//}
//GLvoid InitValue() {
//	{
//		glEnable(GL_DEPTH_TEST);
//		flag_depth_test = true;
//		glEnable(GL_CULL_FACE);
//		flag_cull_face = true;
//		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		flag_draw_line = true;*/
//	}
//
//	{
//		cameraPos = glm::vec3(0.0f, 0.0f, WorldSize);
//		cameraDirection = glm::vec3(.0f, 0.0f, -1.0f);
//		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//		flag_perspective_projection = true;
//	}
//	
//	{//cube 초기화
//		if (cube_pos[0][0] == 0) {	//초기한번만 하도록
//			cube_pos[0][X] = cube_pos[1][X] = cube_pos[4][X] = cube_pos[7][X] = -ObjectSize;
//			cube_pos[2][X] = cube_pos[3][X] = cube_pos[5][X] = cube_pos[6][X] = ObjectSize;
//			cube_pos[0][Y] = cube_pos[1][Y] = cube_pos[2][Y] = cube_pos[3][Y] = ObjectSize;
//			cube_pos[4][Y] = cube_pos[5][Y] = cube_pos[6][Y] = cube_pos[7][Y] = -ObjectSize;
//			cube_pos[0][Z] = cube_pos[3][Z] = cube_pos[6][Z] = cube_pos[7][Z] = -ObjectSize;
//			cube_pos[1][Z] = cube_pos[2][Z] = cube_pos[4][Z] = cube_pos[5][Z] = ObjectSize;
//
//			cube_index[0][X] = 0, cube_index[0][Y] = 1, cube_index[0][Z] = 2;
//			cube_index[1][X] = 0, cube_index[1][Y] = 2, cube_index[1][Z] = 3;
//			cube_index[2][X] = 1, cube_index[2][Y] = 4, cube_index[2][Z] = 5;
//			cube_index[3][X] = 1, cube_index[3][Y] = 5, cube_index[3][Z] = 2;
//			cube_index[4][X] = 2, cube_index[4][Y] = 5, cube_index[4][Z] = 6;
//			cube_index[5][X] = 2, cube_index[5][Y] = 6, cube_index[5][Z] = 3;
//			cube_index[6][X] = 3, cube_index[6][Y] = 6, cube_index[6][Z] = 7;
//			cube_index[7][X] = 3, cube_index[7][Y] = 7, cube_index[7][Z] = 0;
//			cube_index[8][X] = 0, cube_index[8][Y] = 7, cube_index[8][Z] = 4;
//			cube_index[9][X] = 0, cube_index[9][Y] = 4, cube_index[9][Z] = 1;
//			cube_index[10][X] = 6, cube_index[10][Y] = 5, cube_index[10][Z] = 4;
//			cube_index[11][X] = 6, cube_index[11][Y] = 4, cube_index[11][Z] = 7;
//
//			cube_color[0][R] = 0.0f, cube_color[0][G] = 0.5f, cube_color[0][B] = 0.5f;
//			cube_color[1][R] = 0.0f, cube_color[1][G] = 1.0f, cube_color[1][B] = 0.0f;
//			cube_color[2][R] = 0.0f, cube_color[2][G] = 0.0f, cube_color[2][B] = 1.0f;
//			cube_color[3][R] = 1.0f, cube_color[3][G] = 1.0f, cube_color[3][B] = 0.0f;
//			cube_color[4][R] = 1.0f, cube_color[4][G] = 0.0f, cube_color[4][B] = 1.0f;
//			cube_color[5][R] = 0.0f, cube_color[5][G] = 1.0f, cube_color[5][B] = 1.0f;
//		}
//	}
//
//	{
//		for (int i = 0; i < 6; ++i) {
//			side[i].init(i);
//		}
//	}
//
//	{
//		for (int i = 0; i < MaxBallNum; ++i) {
//			ball[i].init();
//		}
//		ball_count = 0;
//	}
//	
//	{
//		for (int i = 0; i < 3; ++i) {
//			box[i].init(i);
//		}
//		if (!flag_box_gravity[IS_ON]) {
//			glutTimerFunc(TimerSpeed, ObjectGravity, BOX);
//			flag_box_gravity[IS_ON] = true;
//		}
//		
//	}
//
//	{
//		grab_left = false;
//		old_x = 0.0f, old_y = 0.0f;
//		now_x = 0.0f, now_y = 0.0f;
//	}
//}
//
//GLvoid ObjectGravity(int value) {
//	switch (value) {
//	case BALL:
//		if (flag_ball_gravity[TURN_OFF]) {
//			flag_ball_gravity[TURN_OFF] = false;
//			flag_ball_gravity[IS_ON] = false;
//			return;
//		}
//		
//		for (int i = 0; i < ball_count; ++i) {
//			
//			//x축
//			ball[i].trans[X] += ball[i].gotovector[X]*ball[i].speed;
//			if (abs(ball[i].trans[Y]) >= ObjectSize /4*5) ball[i].radius = 0;
//			if (ball[i].trans[X] - ball[i].radius < -ObjectSize && side[4].state == ON) {
//				if(-ObjectSize<=ball[i].trans[Y]-ball[i].radius && ball[i].trans[Y] + ball[i].radius <= ObjectSize)
//					ball[i].trans[X] = -ObjectSize + ball[i].radius;
//			}
//			else if (ball[i].trans[X] + ball[i].radius > ObjectSize && side[2].state == ON) {
//				if (-ObjectSize <= ball[i].trans[Y] - ball[i].radius && ball[i].trans[Y] + ball[i].radius <= ObjectSize)
//					ball[i].trans[X] = ObjectSize - ball[i].radius; 
//			}
//
//			//Y축
//			ball[i].trans[Y] += ball[i].gotovector[Y] * ball[i].speed;
//			if (abs(ball[i].trans[Y]) >= ObjectSize /4*5) ball[i].radius = 0;
//			if (ball[i].trans[Y] - ball[i].radius < -ObjectSize && side[5].state == ON) {
//				if (-ObjectSize <= ball[i].trans[X] - ball[i].radius && ball[i].trans[X] + ball[i].radius <= ObjectSize)
//					ball[i].trans[Y] = -ObjectSize + ball[i].radius;
//			}
//			else if (ball[i].trans[Y] + ball[i].radius > ObjectSize && side[0].state == ON) {
//				if (-ObjectSize <= ball[i].trans[X] - ball[i].radius && ball[i].trans[X] + ball[i].radius <= ObjectSize)
//					ball[i].trans[Y] = ObjectSize - ball[i].radius;
//			}
//
//
//		}
//
//		break;
//	case BOX:
//		for (int i = 0; i < 3; ++i) {
//			//x축
//			box[i].trans[X] += box[i].gotovector[X];
//			if (abs(box[i].trans[Y]) >= ObjectSize / 4 * 5) box[i].size = 0;
//			if (box[i].trans[X] - box[i].size < -ObjectSize && side[4].state == ON) {
//				if (-ObjectSize <= box[i].trans[Y] - box[i].size && box[i].trans[Y] + box[i].size <= ObjectSize)
//					box[i].trans[X] = -ObjectSize + box[i].size;
//			}
//			else if (box[i].trans[X] + box[i].size > ObjectSize && side[2].state == ON) {
//				if (-ObjectSize <= box[i].trans[Y] - box[i].size && box[i].trans[Y] + box[i].size <= ObjectSize)
//					box[i].trans[X] = ObjectSize - box[i].size;
//			}
//
//			//Y축
//			box[i].trans[Y] += box[i].gotovector[Y];
//			if (abs(box[i].trans[Y]) >= ObjectSize / 4 * 5) box[i].size = 0;
//			if (box[i].trans[Y] - box[i].size < -ObjectSize && side[5].state == ON) {
//				if (-ObjectSize <= box[i].trans[X] - box[i].size && box[i].trans[X] + box[i].size <= ObjectSize)
//					box[i].trans[Y] = -ObjectSize + box[i].size;
//			}
//			else if (box[i].trans[Y] + box[i].size > ObjectSize && side[0].state == ON) {
//				if (-ObjectSize <= box[i].trans[X] - box[i].size && box[i].trans[X] + box[i].size <= ObjectSize)
//					box[i].trans[Y] = ObjectSize - box[i].size;
//			}
//		}
//		break;
//	}
//	glutPostRedisplay();
//	glutTimerFunc(TimerSpeed, ObjectGravity, value);
//
//}
//
//GLvoid ChangeDegree(GLfloat degree) {
//	if (degree < 0.0f) {
//		degree += 360.0f;
//	}
//	else {
//		degree -= 360.0f;
//	}
//}
//
//GLvoid Side::init(int idx) {
//	switch (idx) {
//	case 0:
//		pos[0][X] = cube_pos[0][X], pos[0][Y] = cube_pos[0][Y], pos[0][Z] = cube_pos[0][Z];
//		pos[1][X] = cube_pos[1][X], pos[1][Y] = cube_pos[1][Y], pos[1][Z] = cube_pos[1][Z];
//		pos[2][X] = cube_pos[2][X], pos[2][Y] = cube_pos[2][Y], pos[2][Z] = cube_pos[2][Z];
//		pos[3][X] = cube_pos[3][X], pos[3][Y] = cube_pos[3][Y], pos[3][Z] = cube_pos[3][Z];
//
//		break;
//	case 1:
//		pos[0][X] = cube_pos[1][X], pos[0][Y] = cube_pos[1][Y], pos[0][Z] = cube_pos[1][Z];
//		pos[1][X] = cube_pos[4][X], pos[1][Y] = cube_pos[4][Y], pos[1][Z] = cube_pos[4][Z];
//		pos[2][X] = cube_pos[5][X], pos[2][Y] = cube_pos[5][Y], pos[2][Z] = cube_pos[5][Z];
//		pos[3][X] = cube_pos[2][X], pos[3][Y] = cube_pos[2][Y], pos[3][Z] = cube_pos[2][Z];
//		break;
//	case 2:
//		pos[0][X] = cube_pos[2][X], pos[0][Y] = cube_pos[2][Y], pos[0][Z] = cube_pos[2][Z];
//		pos[1][X] = cube_pos[5][X], pos[1][Y] = cube_pos[5][Y], pos[1][Z] = cube_pos[5][Z];
//		pos[2][X] = cube_pos[6][X], pos[2][Y] = cube_pos[6][Y], pos[2][Z] = cube_pos[6][Z];
//		pos[3][X] = cube_pos[3][X], pos[3][Y] = cube_pos[3][Y], pos[3][Z] = cube_pos[3][Z];
//
//		break;
//	case 3:
//		pos[0][X] = cube_pos[3][X], pos[0][Y] = cube_pos[3][Y], pos[0][Z] = cube_pos[3][Z];
//		pos[1][X] = cube_pos[6][X], pos[1][Y] = cube_pos[6][Y], pos[1][Z] = cube_pos[6][Z];
//		pos[2][X] = cube_pos[7][X], pos[2][Y] = cube_pos[7][Y], pos[2][Z] = cube_pos[7][Z];
//		pos[3][X] = cube_pos[0][X], pos[3][Y] = cube_pos[0][Y], pos[3][Z] = cube_pos[0][Z];
//
//		break;
//	case 4:
//		pos[0][X] = cube_pos[0][X], pos[0][Y] = cube_pos[0][Y], pos[0][Z] = cube_pos[0][Z];
//		pos[1][X] = cube_pos[7][X], pos[1][Y] = cube_pos[7][Y], pos[1][Z] = cube_pos[7][Z];
//		pos[2][X] = cube_pos[4][X], pos[2][Y] = cube_pos[4][Y], pos[2][Z] = cube_pos[4][Z];
//		pos[3][X] = cube_pos[1][X], pos[3][Y] = cube_pos[1][Y], pos[3][Z] = cube_pos[1][Z];
//
//		break;
//	case 5:
//		pos[0][X] = cube_pos[7][X], pos[0][Y] = cube_pos[7][Y], pos[0][Z] = cube_pos[7][Z];
//		pos[1][X] = cube_pos[4][X], pos[1][Y] = cube_pos[4][Y], pos[1][Z] = cube_pos[4][Z];
//		pos[2][X] = cube_pos[5][X], pos[2][Y] = cube_pos[5][Y], pos[2][Z] = cube_pos[5][Z];
//		pos[3][X] = cube_pos[6][X], pos[3][Y] = cube_pos[6][Y], pos[3][Z] = cube_pos[6][Z];
//		break;
//	}
//	for (int i = 0; i < 3; ++i) {
//		color[i] = cube_color[idx][i];
//	}
//	if (idx==5) {
//		index[0][0] = 0, index[0][1] = 1, index[0][2] = 2;
//		index[1][0] = 0, index[1][1] = 2, index[1][2] = 3;
//	}
//	else if(idx==2||idx==3||idx==4||idx==0||idx==1) {
//		index[0][0] = 0, index[0][1] = 2, index[0][2] = 1;
//		index[1][0] = 0, index[1][1] = 3, index[1][2] = 2;
//	}
//	rot[X] = 0.0f, rot[Y] = 0.0f, rot[Z] = 0.0f;
//	state = ON;
//}
//
//GLvoid Side::draw() {
//	if (state == OFF) return;
//	glBindVertexArray(VAO);
//	GLfloat temp_color[4][3] = {
//		color[R],color[G],color[B],
//		color[R],color[G],color[B],
//		color[R],color[G],color[B],
//		color[R],color[G],color[B]
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//
//	{
//		//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		glm::mat4 Rz = glm::mat4(1.0f);
//		Rz = glm::rotate(Rz, glm::radians(rot[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//		TR = Rz * TR;
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//
//
//	glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, (void*)0);
//}
//
//GLvoid Ball::init() {
//	radius = 0.0;
//	trans[X] = 0.0, trans[Y] = 0.0, trans[Z] = 0.0;
//	speed = 0.0;
//	gotovector[X] = 0.0f, gotovector[Y] = -1.0f, gotovector[Z] = 0.0f;
//}
//GLvoid Ball::draw() {
//	{
//		//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		glm::mat4 T = glm::mat4(1.0f);
//		T = glm::translate(T, glm::vec3(trans[X], trans[Y], trans[Z]));
//		glm::mat4 Rz = glm::mat4(1.0f);
//		Rz = glm::rotate(Rz, glm::radians(side[0].rot[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//		TR = Rz* T * TR;
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//
//	GLUquadricObj* qobj = gluNewQuadric();
//
//	gluSphere(qobj, radius, 50, 50);
//}
//
//std::random_device rd;
//std::uniform_real_distribution<GLfloat> ufd_radius(5.0f, 10.0f);
//std::uniform_real_distribution<GLfloat> ufd_speed(0.5f, 2.0f);
//GLvoid Ball::make() {
//	radius = ufd_radius(rd);
//	std::uniform_real_distribution<GLfloat> ufd_pos(-ObjectSize + radius, ObjectSize - radius);
//	trans[X] = ufd_pos(rd), trans[Y] = ufd_pos(rd), trans[Z] = ufd_pos(rd);
//	speed = ufd_speed(rd);
//	gotovector[X] = 0.0f, gotovector[Y] = -1.0f, gotovector[Z] = 0.0f;
//	RotateGotoVector(-side[0].rot[Z]);
//	//TODO: 공에 대해서도 최종 이동에서 Rz 만큼 회전시켜주자.
//
//
//}
//
//GLvoid Ball::RotateGotoVector(GLfloat rotateDegree) {
//	glm::vec4 tempV = glm::vec4(gotovector[X], gotovector[Y], gotovector[Z], 1.0f);
//	glm::mat4 Rz = glm::mat4(1.0f);
//	Rz = glm::rotate(Rz, glm::radians(rotateDegree), glm::vec3(0.0f, 0.0f, 1.0f));
//	tempV = Rz * tempV;
//	gotovector[X] = tempV[X], gotovector[Y] = tempV[Y], gotovector[Z] = tempV[Z];
//}
//
//GLvoid Box::init(int idx) {
//	switch (idx) {
//	case 0:
//		size = 5.0f;
//		trans[Z] = 10.0f;
//		break;
//	case 1:
//		size = 10.0f;
//		trans[Z] = -7.5f;
//		break;
//	case 2:
//		size = 15.0f;
//		trans[Z] = -35.0f;
//		break;
//	}
//	trans[X] = 0.0f, trans[Y] = -ObjectSize + size;
//	speed = 0.0;
//	gotovector[X] = 0.0f, gotovector[Y] = -1.0f, gotovector[Z] = 0.0f;
//}
//GLvoid Box::draw(int idx) {
//	glBindVertexArray(VAO);
//	switch (idx) {
//	case 0:
//	{
//		GLfloat color[8][3] = { 0.8f,0.8f,1.0f,0.8f,0.8f,1.0f,0.8f,0.8f,1.0f,0.8f,0.8f,1.0f,0.8f,0.8f,1.0f,0.8f,0.8f,1.0f,0.8f,0.8f,1.0f,0.8f,0.8f,1.0f, };
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
//
//	}
//		
//		break;
//	case 1:
//	{
//		GLfloat color[8][3] = { 0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,0.2f,0.0f,0.6f,	};
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW); 
//	}
//		break;
//	case 2:
//	{
//		GLfloat color[8][3] = { 0.2f,0.0f,0.0f,0.2f,0.0f,0.0f,0.2f,0.0f,0.0f,0.2f,0.0f,0.0f,0.2f,0.0f,0.0f,0.2f,0.0f,0.0f,0.2f,0.0f,0.0f,0.2f,0.0f,0.0f, };
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW); 
//	}
//		break;
//	}
//	
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//
//	{
//		//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//
//		glm::mat4 S = glm::mat4(1.0f);
//		S = glm::scale(S, glm::vec3(size / ObjectSize, size / ObjectSize, size / ObjectSize));
//		glm::mat4 T = glm::mat4(1.0f);
//		T = glm::translate(T, glm::vec3(trans[X], trans[Y], trans[Z]));
//		
//		glm::mat4 Rz = glm::mat4(1.0f);
//		Rz = glm::rotate(Rz, glm::radians(side[0].rot[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//		
//		TR = Rz * T *S* TR;
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//
//
//	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, (void*)0);
//
//
//
//}
//
//
//GLvoid Box::RotateGotoVector(GLfloat rotateDegree) {
//	glm::vec4 tempV = glm::vec4(gotovector[X], gotovector[Y], gotovector[Z], 1.0f);
//	glm::mat4 Rz = glm::mat4(1.0f);
//	Rz = glm::rotate(Rz, glm::radians(rotateDegree), glm::vec3(0.0f, 0.0f, 1.0f));
//	tempV = Rz * tempV;
//	gotovector[X] = tempV[X], gotovector[Y] = tempV[Y], gotovector[Z] = tempV[Z];
//}
//
//void make_vertexShaders() {
//	GLchar* vertexsource;
//
//	vertexsource = filetobuf("vertex.glsl");
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexsource, NULL);
//	glCompileShader(vertexShader);
//
//	GLint result;
//	GLchar errorlog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
//	if (!result) {
//		glGetShaderInfoLog(vertexShader, 512, NULL, errorlog);
//		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorlog << std::endl;
//		return;
//	}
//}
//void make_fragmentShaders() {
//	GLchar* fragmentsource;
//
//	fragmentsource = filetobuf("fragment.glsl");
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentsource, NULL);
//	glCompileShader(fragmentShader);
//
//	GLint result;
//	GLchar errorlog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
//	if (!result) {
//		glGetShaderInfoLog(fragmentShader, 512, NULL, errorlog);
//		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorlog << std::endl;
//		return;
//	}
//}
//GLvoid InitShader() {
//	make_vertexShaders();
//	make_fragmentShaders();
//
//	s_program = glCreateProgram();
//
//	glAttachShader(s_program, vertexShader);
//	glAttachShader(s_program, fragmentShader);
//	glLinkProgram(s_program);
//
//	checkCompileErrors(s_program, "PROGRAM");
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	glUseProgram(s_program);
//}
//void checkCompileErrors(unsigned int shader, std::string type)
//{
//	int success;
//	char infoLog[1024];
//	if (type != "PROGRAM")
//	{
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//		}
//	}
//	else
//	{
//		glGetProgramiv(shader, GL_LINK_STATUS, &success);
//		if (!success)
//		{
//			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//		}
//	}
//}
//char* filetobuf(const char* file)
//{
//	FILE* fptr;
//	long length;
//	char* buf;
//	fptr = fopen(file, "rb"); // Open file for reading
//	if (!fptr) // Return NULL on failure
//		return NULL;
//	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
//	length = ftell(fptr); // Find out how many bytes into the file we are
//	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
//	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
//	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
//	fclose(fptr); // Close the file
//	buf[length] = 0; // Null terminator
//	return buf; // Return the buffer
//}
//GLvoid SetTransformMatrix() {
//	{//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//
//	{//카메라 변환
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraPos+ cameraDirection, cameraUp);
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//	}
//	
//	{//투영변환
//		glm::mat4 projection = glm::mat4(1.0f);
//		if (flag_perspective_projection) {	//원근
//			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize*3);
//			//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//		}
//		else {	//직각
//			GLfloat halfsize = WorldSize;
//			projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//		}
//		
//
//		unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//	}
//}