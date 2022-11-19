///*
//---------단축키 설명---------
//WASD휠 - 카메라 조작
//H/h - 은면 제거
//J/j - 깊이 검사
//L/l - Fill/Line
//
//1 - Y축 자전
//2 - 큐브 윗면 움직임
//3 - 큐브 앞면 움직임
//4 - 큐브 옆면 움직임
//5 - 사각뿔 움직임
//'0' - 타이머 종료
//'-' - 값 초기화
//P/p - 투영변환
//O/o - 도형바꾸기
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
////월드관련 define
//#define ObjectSize 10
//#define WorldSize 200		//x: -100~100 / y: -100~100 / z: 0 ~ 200
//
//enum CrainPart { UNDERBODY = 0, UPBODY = 1, LEFTARM = 0, RIGHTARM = 1 };
//
////큐브 관련 변수
//GLfloat cube_pos[8][3];
//GLfloat cube_color[8][3];
//unsigned int cube_idx[12][3];
//GLvoid CubeInit();
////클래스 관련
//class myObject {
//public:
//	GLfloat firstR[3] = { 0.0f,0.0f,0.0f };
//	GLfloat firstT[3] = { 0.0f,0.0f,0.0f };
//	GLfloat firstS[3] = { 1.0f,1.0f,1.0f };
//	GLfloat color[8][3];
//	GLuint VAO, VBO[3];
//	GLvoid InitBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//	}
//	GLvoid init() {
//		for (int i = 0; i < 3; ++i) {
//			firstR[i] = 0.0f;
//			firstT[i] = 0.0f;
//			firstS[i] = 1.0f;
//		}
//	}
//	GLvoid set_firstR(GLfloat x, GLfloat y, GLfloat z) {
//		firstR[X] = x, firstR[Y] = y, firstR[Z] = z;
//	}
//	GLvoid set_firstT(GLfloat x, GLfloat y, GLfloat z) {
//		firstT[X] = x, firstT[Y] = y, firstT[Z] = z;
//	}
//	GLvoid set_firstS(GLfloat x, GLfloat y, GLfloat z) {
//		firstS[X] = x, firstS[Y] = y, firstS[Z] = z;
//	}
//	GLvoid set_color(GLfloat r,GLfloat g,GLfloat b) {
//		for (int i = 0; i < 8; ++i) {
//			color[i][R] = r; color[i][G] = g; color[i][B] = b;
//		}
//	}
//	GLvoid Draw(GLfloat plusT[3], GLfloat plusR[3]);
//	GLvoid ArmDraw(GLfloat plusT[3], GLfloat plusR[3]);
//};
//class Crain {
//public:
//	myObject body[2];
//	myObject arm[2];
//	GLfloat crainR[3];
//	GLfloat crainT[3];
//	GLvoid InitBuffer() {
//		for (int i = 0; i < 2; ++i) {
//			body[i].InitBuffer();
//			arm[i].InitBuffer();
//		}
//	}
//	GLvoid init() {
//		for (int i = 0; i < 3; ++i) {
//			crainR[i] = 0.0f;
//			crainT[i] = 0.0f;
//		}
//		for (int i = 0; i < 2; ++i) {
//			body[i].init();
//			arm[i].init();
//		}
//		body[UNDERBODY].set_firstS(1.0f, 0.5f, 1.0f);
//		body[UNDERBODY].set_firstT(0.0f, ObjectSize / 2, 0.0f);
//		body[UNDERBODY].set_color(1.0,0.0,0.0);
//		body[UPBODY].set_firstS(0.5, 0.25f, 0.5);
//		body[UPBODY].set_firstT(0.0, ObjectSize+ ObjectSize/4, 0.0f);
//		body[UPBODY].set_color(0.0, 1.0, 0.0);
//		arm[LEFTARM].set_firstS(0.20, 0.8f, 0.20);
//		arm[LEFTARM].set_firstT(ObjectSize/7*2.5, ObjectSize + ObjectSize / 4+ObjectSize, 0.0f);
//		arm[LEFTARM].set_color(1.0, 1.0, 0.0);
//		arm[RIGHTARM].set_firstS(0.20, 0.8f, 0.20);
//		arm[RIGHTARM].set_firstT(-ObjectSize / 7*2.5, ObjectSize + ObjectSize / 4 + ObjectSize, 0.0f);
//		arm[RIGHTARM].set_color(1.0, 0.0, 1.0);
//		
//	}
//	GLvoid Draw() {
//		body[UNDERBODY].Draw(crainT, crainR);
//		body[UPBODY].Draw(crainT, crainR);
//		GLfloat leftplusR[3];
//		GLfloat rightplusR[3];
//		for (int i = 0; i < 3; ++i) {
//			leftplusR[i] = crainR[i] + body[UPBODY].firstR[i];
//			rightplusR[i] = crainR[i] + body[UPBODY].firstR[i];
//		}
//		arm[LEFTARM].ArmDraw(crainT, leftplusR);
//		arm[RIGHTARM].ArmDraw(crainT, rightplusR);
//	}
//};
//class Ground {
//public:
//	GLfloat pos[6][3];
//	GLfloat color[6][3];
//	
//	GLuint VAO, VBO[2];
//
//	GLvoid init();
//	GLvoid Draw();
//};
//
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
//GLfloat cameraR[3] = { 0.0,0.0,0.0 };
//GLfloat cameraRevR[3] = { 0.0,0.0,0.0 };
//
////내가 만든 함수 와 변수
//GLvoid InitValue();
//GLboolean flag_cull_face = false;
//GLboolean flag_depth_test = false;
//GLboolean flag_draw_line = false;
//GLvoid ChangeDegree(GLfloat);
//
////축 관련 함수 와 변수
//GLvoid DrawAxes();
//
//
////게임월드내 변수 및 함수
//Crain crain;
//Ground ground;
//GLboolean draw_ground = true;
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
//
//	glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene() {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	if (draw_ground)
//		ground.Draw();
//	crain.Draw();
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
//	case 'H':	//은면제거 설정 / 해제
//	case 'h':
//		if (flag_cull_face)	glDisable(GL_CULL_FACE);
//		else glEnable(GL_CULL_FACE);
//		flag_cull_face = 1 - flag_cull_face;
//		break;
//	case 'J':	//깊이검사 설정 / 해제
//	case 'j':
//		if (flag_depth_test)	glDisable(GL_DEPTH_TEST);
//		else glEnable(GL_DEPTH_TEST);
//		flag_depth_test = 1 - flag_depth_test;
//		break;
//	case 'L':
//	case 'l':
//		if (flag_draw_line)	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		flag_draw_line = 1 - flag_draw_line;
//		break;
//	case 'G':
//	case 'g':
//		draw_ground = 1 - draw_ground;
//		break;
//	case 'm':
//		crain.body[UPBODY].firstR[Y] = int(crain.body[UPBODY].firstR[Y] + 5) % 360;
//		break;
//	case 'M':
//		crain.body[UPBODY].firstR[Y] = int(crain.body[UPBODY].firstR[Y] - 5) % -360;
//		break;
//	case 'T':
//		crain.arm[LEFTARM].firstR[X] += 2;
//		if (crain.arm[LEFTARM].firstR[X] > 90) crain.arm[LEFTARM].firstR[X] = 90;
//		crain.arm[RIGHTARM].firstR[X] -= 2;
//		if (crain.arm[RIGHTARM].firstR[X] <-90) crain.arm[RIGHTARM].firstR[X] = -90;
//		break;
//	case 't':
//		crain.arm[RIGHTARM].firstR[X] += 2;
//		if (crain.arm[RIGHTARM].firstR[X] > 90) crain.arm[RIGHTARM].firstR[X] = 90;
//		crain.arm[LEFTARM].firstR[X] -= 2;
//		if (crain.arm[LEFTARM].firstR[X] < -90) crain.arm[LEFTARM].firstR[X] = -90;
//		break;
//	case 'Y':
//		cameraR[Y] = int(cameraR[Y] + 2) % 360;
//		std::cout << "카메라 자전 Y: " << cameraR[Y] << std::endl;
//		break;
//	case 'y':
//		cameraR[Y] = int(cameraR[Y] - 2) % -360;
//		std::cout << "카메라 자전 Y: " << cameraR[Y] << std::endl;
//		break;
//	case 'x':
//		cameraR[X] = int(cameraR[X]+2)%360;
//		std::cout << "카메라 자전 X: " << cameraR[X] << std::endl;
//		break;
//	case 'X':
//		cameraR[X] = int(cameraR[X] - 2) % -360;
//		std::cout << "카메라 자전 X: " << cameraR[X] << std::endl;
//		break;
//	case 'C':
//	case 'c':
//		InitValue();
//		break;
//	case 'r':
//	{
//		glm::mat4 r = glm::mat4(1.0f);
//		r = glm::rotate(r, glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));
//		std::cout << "카메라 위치: X: " << cameraPos[X] << " / Y: " << cameraPos[Y] << " / Z: " << cameraPos[Z] << std::endl;
//		glm::vec4 cp = { cameraPos,1.0 };
//		glm::vec4 cd = { cameraDirection,1.0 };
//		cp = cp * r;
//		cd = cd * r;
//		for (int i = 0; i < 3; ++i) {
//			cameraPos[i] = cp[i];
//			cameraDirection[i] = cd[i];
//		}
//	}
//		
//		break;
//	case 'R':
//		glm::mat4 r = glm::mat4(1.0f);
//		r = glm::rotate(r, glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));
//		std::cout << "카메라 위치: X: " << cameraPos[X] << " / Y: " << cameraPos[Y] << " / Z: " << cameraPos[Z] << std::endl;
//		glm::vec4 cp = { cameraPos,1.0 };
//		glm::vec4 cd = { cameraDirection,1.0 };
//		cp = cp * r;
//		cd = cd * r;
//		for (int i = 0; i < 3; ++i) {
//			cameraPos[i] = cp[i];
//			cameraDirection[i] = cd[i];
//		}
//		break;
//	}
//
//	glutPostRedisplay();
//}
//
//GLvoid SpecialKeyboard(int key, int x, int y) {
//	switch (key)
//	{
//	case GLUT_KEY_LEFT:
//		crain.crainT[X] -= 1;
//		break;
//	case GLUT_KEY_RIGHT:
//		crain.crainT[X] += 1;
//		break;
//	case GLUT_KEY_UP:
//		crain.crainT[Z] -= 1;
//		break;
//	case GLUT_KEY_DOWN:
//		crain.crainT[Z] += 1;
//		break;
//	default:
//		break;
//	}
//	glutPostRedisplay();
//}
//
//GLvoid Mouse(int button, int state, int x, int y) {
//	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
//	//state - GLUT_UP, GLUT_DOWN
//	switch (state) {
//	case GLUT_DOWN:
//		switch (button) {
//		case 3:			//마우스휠 위로 역할
//			cameraPos.z -= WorldSize / 100;	//카메라 안쪽으로
//			//if (cameraPos.z > WorldSize) cameraPos.z = WorldSize;
//			std::cout << "z: " << cameraPos.z << std::endl;
//			
//			break;
//		case 4:			//마우스휠 아래로 역할
//			cameraPos.z += WorldSize / 100;	//카메라 바깥쪽으로
//			//if (cameraPos.z < -) cameraPos.z = 0;
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
//GLvoid MouseMove(int x, int y) {
//
//	glutPostRedisplay();
//}
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid InitBuffer() {
//	glGenVertexArrays(1, &ground.VAO);
//	glGenBuffers(2, ground.VBO);
//
//	crain.InitBuffer();
//}
//GLvoid InitValue() {
//	{
//		glEnable(GL_DEPTH_TEST);
//		flag_depth_test = true;
//		/*glEnable(GL_CULL_FACE);
//		flag_cull_face = true;*/
//		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		flag_draw_line = true;*/
//	}
//	{
//		cameraPos = glm::vec3(0.0f, 10.0f, 100);
//		cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
//		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//		cameraR[X] = 0.0, cameraR[Y] = 0.0, cameraR[Z] = 0.0;
//		cameraRevR[X] = 0.0, cameraRevR[Y] = 0.0, cameraRevR[Z] = 0.0;
//		flag_perspective_projection = true;
//	}
//	{
//		CubeInit();
//	}
//	{
//		crain.init();
//	}
//	{
//		ground.init();
//		draw_ground = true;
//	}
//}
//GLvoid ChangeDegree(GLfloat degree) {
//	if (degree < 0.0f) {
//		degree += 360.0f;
//	}
//	else {
//		degree -= 360.0f;
//	}
//}
//GLvoid Ground::init() {
//	pos[0][X] = -WorldSize;	pos[0][Y] = -0;		pos[0][Z] = -WorldSize;
//	pos[1][X] = -WorldSize;	pos[1][Y] = -0;		pos[1][Z] = WorldSize;
//	pos[2][X] = WorldSize;		pos[2][Y] = -0;		pos[2][Z] = WorldSize;
//	pos[3][X] = -WorldSize;	pos[3][Y] = -0;		pos[3][Z] = -WorldSize;
//	pos[4][X] = WorldSize;		pos[4][Y] = -0;		pos[4][Z] = WorldSize;
//	pos[5][X] = WorldSize;		pos[5][Y] = -0;		pos[5][Z] = -WorldSize;
//
//	color[0][X] = 1.0;	color[0][Y] = 0.0;	color[0][Z] = 0.0;
//	color[1][X] = 0.0;	color[1][Y] = 1.0;	color[1][Z] = 0.0;
//	color[2][X] = 0.0;	color[2][Y] = 0.0;	color[2][Z] = 1.0;
//	color[3][X] = 1.0;	color[3][Y] = 0.0;	color[3][Z] = 0.0;
//	color[4][X] = 0.0;	color[4][Y] = 0.0;	color[4][Z] = 1.0;
//	color[5][X] = 0.0;	color[5][Y] = 1.0;	color[5][Z] = 1.0;
//}
//GLvoid Ground::Draw() {
//	glBindVertexArray(VAO);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
//	
//	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);*/
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//
//	//model 변환
//	glm::mat4 TR = glm::mat4(1.0f);
//	glm::mat4 Rx = glm::mat4(1.0f);
//	glm::mat4 Ry = glm::mat4(1.0f);
//	//glm::mat4 T = glm::mat4(1.0f);
//	//Rx = glm::rotate(Rx, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
//	//Ry = glm::rotate(Ry, glm::radians(+30.0f), glm::vec3(0.0, 1.0, 0.0));
//	//T = glm::translate(T, glm::vec3(0.0, 1.0,- ObjectSize - 50));
//	//TR =  Ry * Rx;
//	unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	
//	{//카메라 변환
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 Rz = glm::mat4(1.0f);
//		Rx = glm::rotate(Rx, glm::radians(cameraR[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//		Ry = glm::rotate(Ry, glm::radians(cameraR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//		Rz = glm::rotate(Rz, glm::radians(cameraR[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
//		view = (Rz * Ry * Rx) * view;
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//	}
//	//투영변환
//	glm::mat4 projection = glm::mat4(1.0f);
//	//직각 투영
//	//GLfloat halfsize = WorldSize / 2;
//	//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//	//원근 투영
//	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//	
//	unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//	
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}
//GLvoid CubeInit() {
//	cube_pos[0][X] = cube_pos[1][X] = cube_pos[4][X] = cube_pos[7][X] = -ObjectSize;
//	cube_pos[2][X] = cube_pos[3][X] = cube_pos[5][X] = cube_pos[6][X] = ObjectSize;
//	cube_pos[0][Y] = cube_pos[1][Y] = cube_pos[2][Y] = cube_pos[3][Y] = ObjectSize;
//	cube_pos[4][Y] = cube_pos[5][Y] = cube_pos[6][Y] = cube_pos[7][Y] = -ObjectSize;
//	cube_pos[0][Z] = cube_pos[3][Z] = cube_pos[6][Z] = cube_pos[7][Z] = -ObjectSize;
//	cube_pos[1][Z] = cube_pos[2][Z] = cube_pos[4][Z] = cube_pos[5][Z] = ObjectSize;
//
//	cube_idx[0][X] = 0, cube_idx[0][Y] = 1, cube_idx[0][Z] = 2;
//	cube_idx[1][X] = 0, cube_idx[1][Y] = 2, cube_idx[1][Z] = 3;
//	cube_idx[2][X] = 1, cube_idx[2][Y] = 4, cube_idx[2][Z] = 5;
//	cube_idx[3][X] = 1, cube_idx[3][Y] = 5, cube_idx[3][Z] = 2;
//	cube_idx[4][X] = 2, cube_idx[4][Y] = 5, cube_idx[4][Z] = 6;
//	cube_idx[5][X] = 2, cube_idx[5][Y] = 6, cube_idx[5][Z] = 3;
//	cube_idx[6][X] = 3, cube_idx[6][Y] = 6, cube_idx[6][Z] = 7;
//	cube_idx[7][X] = 3, cube_idx[7][Y] = 7, cube_idx[7][Z] = 0;
//	cube_idx[8][X] = 0, cube_idx[8][Y] = 7, cube_idx[8][Z] = 4;
//	cube_idx[9][X] = 0, cube_idx[9][Y] = 4, cube_idx[9][Z] = 1;
//	cube_idx[10][X] = 6, cube_idx[10][Y] = 5, cube_idx[10][Z] = 4;
//	cube_idx[11][X] = 6, cube_idx[11][Y] = 4, cube_idx[11][Z] = 7;
//
//	cube_color[0][R] = 1.0f, cube_color[0][G] = 0.0f, cube_color[0][B] = 0.0f;
//	cube_color[1][R] = 0.0f, cube_color[1][G] = 1.0f, cube_color[1][B] = 0.0f;
//	cube_color[2][R] = 0.0f, cube_color[2][G] = 0.0f, cube_color[2][B] = 1.0f;
//	cube_color[3][R] = 1.0f, cube_color[3][G] = 1.0f, cube_color[3][B] = 0.0f;
//	cube_color[4][R] = 0.0f, cube_color[4][G] = 1.0f, cube_color[4][B] = 1.0f;
//	cube_color[5][R] = 1.0f, cube_color[5][G] = 0.0f, cube_color[5][B] = 1.0f;
//	cube_color[6][R] = 1.0f, cube_color[6][G] = 1.0f, cube_color[6][B] = 1.0f;
//	cube_color[7][R] = 0.5f, cube_color[7][G] = 0.5f, cube_color[7][B] = 0.5f;
//}
//GLvoid myObject::Draw(GLfloat plusT[3], GLfloat plusR[3]) {
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//	
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_idx), cube_idx, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//
//	//model 변환
//	glm::mat4 TR = glm::mat4(1.0f);
//	glm::mat4 S = glm::mat4(1.0f);
//	glm::mat4 FRx = glm::mat4(1.0f);
//	glm::mat4 FRy = glm::mat4(1.0f);
//	glm::mat4 FRz = glm::mat4(1.0f);
//	glm::mat4 T = glm::mat4(1.0f);
//	S = glm::scale(S, glm::vec3(firstS[X], firstS[Y], firstS[Z]));
//	FRx = glm::rotate(FRx, glm::radians(firstR[X]+plusR[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//	FRy = glm::rotate(FRy, glm::radians(firstR[Y]+plusR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//	FRz = glm::rotate(FRz, glm::radians(firstR[Z]+plusR[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//	T = glm::translate(T, glm::vec3(firstT[X]+plusT[X], firstT[Y]+ plusT[Y], firstT[Z]+ plusT[Z]));
//	TR = T * (FRz * FRy * FRx) * S;
//	unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//
//	{//카메라 변환
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 Rz = glm::mat4(1.0f);
//		Rx = glm::rotate(Rx, glm::radians(cameraR[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//		Ry = glm::rotate(Ry, glm::radians(cameraR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//		Rz = glm::rotate(Rz, glm::radians(cameraR[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//		
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
//		view = (Rz * Ry * Rx) * view;
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//	}
//	//투영변환
//	glm::mat4 projection = glm::mat4(1.0f);
//	//직각 투영
//	//GLfloat halfsize = WorldSize / 2;
//	//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//	//원근 투영
//	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//	unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	//glDrawArrays(GL_LINES, 0, 8);
//	
//}
//
//GLvoid myObject::ArmDraw(GLfloat plusT[3], GLfloat plusR[3]) {
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_idx), cube_idx, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//	
//	{
//		//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		glm::mat4 S = glm::mat4(1.0f);
//		glm::mat4 FRx = glm::mat4(1.0f);
//		glm::mat4 FRy = glm::mat4(1.0f);
//		glm::mat4 FRz = glm::mat4(1.0f);
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 Rz = glm::mat4(1.0f);
//		glm::mat4 T = glm::mat4(1.0f);
//		glm::mat4 FT = glm::mat4(1.0f);
//		glm::mat4 TTTT1 = glm::mat4(1.0f);
//		glm::mat4 TTTT2 = glm::mat4(1.0f);
//		S = glm::scale(S, glm::vec3(firstS[X], firstS[Y], firstS[Z]));
//		FRx = glm::rotate(FRx, glm::radians(firstR[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//		FRy = glm::rotate(FRy, glm::radians(firstR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//		FRz = glm::rotate(FRz, glm::radians(firstR[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//		Rx = glm::rotate(Rx, glm::radians(plusR[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//		Ry = glm::rotate(Ry, glm::radians(plusR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//		Rz = glm::rotate(Rz, glm::radians(plusR[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//		T = glm::translate(T, glm::vec3(plusT[X], plusT[Y], plusT[Z]));
//		FT = glm::translate(FT, glm::vec3(firstT[X], firstT[Y], firstT[Z]));
//		TTTT1 = glm::translate(TTTT1, glm::vec3(0.0, ObjectSize / 5 * 4, 0.0));
//		TTTT2 = glm::translate(TTTT2, glm::vec3(0.0, -ObjectSize / 5 * 4, 0.0));
//		TR = T * (Rz * Ry * Rx) * FT * TTTT2 * (FRz * FRy * FRx) * TTTT1 * S;
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//	{//카메라 변환
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 Rz = glm::mat4(1.0f);
//		Rx = glm::rotate(Rx, glm::radians(cameraR[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//		Ry = glm::rotate(Ry, glm::radians(cameraR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//		Rz = glm::rotate(Rz, glm::radians(cameraR[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
//		view = (Rz * Ry * Rx) *view;
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//	}
//	
//
//	//투영변환
//	glm::mat4 projection = glm::mat4(1.0f);
//	//직각 투영
//	//GLfloat halfsize = WorldSize / 2;
//	//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//	//원근 투영
//	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//	unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	//glDrawArrays(GL_LINES, 0, 8);
//
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