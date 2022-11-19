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
//
//
////월드관련 define
//#define ObjectSize 20
//#define WorldSize 200		//x: -100~100 / y: -100~100 / z: 0 ~ 200
//
////enum 관련
//enum TIMER{ Y_ROTATE = 0, UP_FACE_ROTATE, FRONT_AND_BACK_ROTATE, SIDE_FACE_MOVE, PYRAMID_FACE_MOVE};
//
////클래스 관련
////class MyCubeFor16 {
////public:
////	GLfloat pos[8][3];
////	GLfloat color[8][3];
////
////	GLfloat move_face[6][3];
////};
//
////glut 관련 함수
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid KeyBoard(unsigned char key, int x, int y);
//GLvoid Mouse(int, int, int, int);
//GLvoid MouseMove(int, int);
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
//GLuint cube_VAO, cube_VBO[3], cube_VBO_for_16[3];
//GLuint pyramid_VAO, pyramid_VBO[3];
//GLuint axes_VAO, axes_VBO[2];
//GLvoid InitBuffer();
//
////카메라 관련 함수 및 변수
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, WorldSize/2);
//glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 1.0);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//GLboolean flag_perspective_projection = true;
//
////내가 만든 함수 와 변수
//GLvoid InitValue();
//GLboolean flag_cull_face = false;
//GLboolean flag_depth_test = false;
//GLboolean flag_draw_line = false;
//GLvoid ChangeDegree(GLfloat);
//
////축 관련 함수 와 변수
//GLfloat axes_pos[6][3];
//GLfloat axes_color[6][3];
//GLfloat axes_rotate[3];
//GLvoid DrawAxes();
//
////큐브 관련 함수 와 변수
//GLfloat cube_pos[8][3];
//unsigned int cube_idx[12][3];
//GLfloat cube_color[8][3];
//GLfloat cube_rotate[3];
//GLfloat cube_face_TR[6][3];
//GLvoid DrawCube();
//GLvoid DrawCubeForTraining16();
//GLboolean print_cube = true;
//
////사각뿔 관련 함수 와 변수
//GLfloat pyramid_pos[5][3];
//unsigned int pyramid_idx[6][3];
//GLfloat pyramid_color[5][3];
//GLfloat pyramid_rotate[3];
//GLfloat pyramid_face_TR[5][3];
//GLvoid DrawPyramidForTraining16();
//
//
////타이머 관련 함수 및 변수
//int flag_timer = 0;
//int stop_timer = 0;
//int TimerSpeed = 30;
//GLfloat up_face_rotate_degree = 0.0f;
//GLvoid Timer(int);
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
//
//	glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene() {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	DrawAxes();
//	if (print_cube)
//		DrawCubeForTraining16();
//	else
//		DrawPyramidForTraining16();
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
//		if (cameraPos.x < -WorldSize / 2) cameraPos.x = -WorldSize / 2;
//		std::cout << "x: " << cameraPos.x << std::endl;
//		break;
//	case 'd':	//카메라 오른쪽 이동
//		cameraPos.x += WorldSize / 100;
//		if (cameraPos.x > WorldSize / 2) cameraPos.x = WorldSize / 2;
//		std::cout << "x: " << cameraPos.x << std::endl;
//		break;
//	case 'w':	//카메라 위쪽 이동
//		cameraPos.y += WorldSize / 100;
//		if (cameraPos.y > WorldSize / 2) cameraPos.y = WorldSize / 2;
//		std::cout << "y: " << cameraPos.y << std::endl;
//		break;
//	case 's':	//카메라 아래쪽 이동
//		cameraPos.y -= WorldSize / 100;
//		if (cameraPos.y < -WorldSize / 2) cameraPos.y = -WorldSize / 2;
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
//	case '1':
//		glutTimerFunc(TimerSpeed, Timer, Y_ROTATE);
//		++flag_timer;
//		break;
//	case '2':
//		if (!print_cube) {
//			printf("큐브가 아니라 진행 불가합니다. 큐브 변경 - O/o\n");
//			break;
//		}
//		glutTimerFunc(TimerSpeed, Timer, UP_FACE_ROTATE);
//		++flag_timer;
//		break;
//	case '3':
//		if (!print_cube) {
//			printf("큐브가 아니라 진행 불가합니다. 큐브 변경 - O/o\n");
//			break;
//		}
//		glutTimerFunc(TimerSpeed, Timer, FRONT_AND_BACK_ROTATE);
//		++flag_timer;
//		break;
//	case '4':
//		if (!print_cube) {
//			printf("큐브가 아니라 진행 불가합니다. 큐브 변경 - O/o\n");
//			break;
//		}
//		glutTimerFunc(TimerSpeed, Timer, SIDE_FACE_MOVE);
//		++flag_timer;
//		break;
//	case '5':
//		if (print_cube) {
//			printf("사각뿔이 아니라 진행 불가합니다. 사각뿔 변경 - O/o\n");
//			break;
//		}
//		glutTimerFunc(TimerSpeed, Timer, PYRAMID_FACE_MOVE);
//		++flag_timer;
//		break;
//	case '0':
//		stop_timer = flag_timer;
//		break;
//	case '-':
//		InitValue();
//		break;
//	case 'P':
//	case 'p':
//		flag_perspective_projection = 1 - flag_perspective_projection;
//		break;
//	case 'o':
//	case 'O':
//		print_cube = 1 - print_cube;
//		stop_timer = flag_timer;
//		break;
//	}
//
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
//			if (cameraPos.z > WorldSize) cameraPos.z = WorldSize;
//			std::cout <<"z: " << cameraPos.z << std::endl;
//			break;
//		case 4:			//마우스휠 아래로 역할
//			cameraPos.z += WorldSize / 100;	//카메라 바깥쪽으로
//			if (cameraPos.z < 0) cameraPos.z = 0;
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
//
//	glutPostRedisplay();
//}
//
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid DrawCubeForTraining16() {
//	for (int i = 0; i < 6; ++i) {
//		glBindVertexArray(cube_VAO);
//		glm::mat4 TR = glm::mat4(1.0f);
//		glm::mat4 TransToAxes = glm::mat4(1.0f);
//		glm::mat4 BackToOrigin = glm::mat4(1.0f);
//		glm::mat4 RotateToAxes = glm::mat4(1.0f);
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 T = glm::mat4(1.0f);
//		switch (i) {
//		case 0:		//윗면
//			TransToAxes = glm::translate(TransToAxes, glm::vec3(0.0,-ObjectSize,0.0));
//			BackToOrigin = glm::translate(BackToOrigin, glm::vec3(0.0, +ObjectSize, 0.0));
//			RotateToAxes = glm::rotate(RotateToAxes, glm::radians(cube_face_TR[i][0]), glm::vec3(1.0f, 0.0f, 0.0f));
//			break;
//		case 1:		//앞면
//			TransToAxes = glm::translate(TransToAxes, glm::vec3(0.0, ObjectSize, -ObjectSize));
//			BackToOrigin = glm::translate(BackToOrigin, glm::vec3(0.0, -ObjectSize, ObjectSize));
//			RotateToAxes = glm::rotate(RotateToAxes, glm::radians(cube_face_TR[i][Z]), glm::vec3(1.0f, 0.0f, 0.0f));
//			break;
//		case 3:		//뒷면
//			TransToAxes = glm::translate(TransToAxes, glm::vec3(0.0, +ObjectSize, ObjectSize));
//			BackToOrigin = glm::translate(BackToOrigin, glm::vec3(0.0, -ObjectSize, -ObjectSize));
//			RotateToAxes = glm::rotate(RotateToAxes, glm::radians(cube_face_TR[i][Z]), glm::vec3(1.0f, 0.0f, 0.0f));
//			break;
//		case 2:		//오른쪽면
//		case 4:		//왼쪽면
//			TransToAxes = glm::translate(TransToAxes, glm::vec3(0.0f, cube_face_TR[i][Y], 0.0f));
//			break;
//		}
//		Rx = glm::rotate(Rx, glm::radians(cube_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
//		Ry = glm::rotate(Ry, glm::radians(cube_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
//		
//		TR = T * Ry * Rx * (BackToOrigin* RotateToAxes*TransToAxes);
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//
//		//카메라 변환
//		glm::mat4 view = glm::mat4(1.0f);
//		//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//		//cameraDirection = glm::normalize(cameraPos - cameraTarget);
//		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//
//		//투영변환
//		glm::mat4 projection = glm::mat4(1.0f);
//		//직각 투영
//		if (flag_perspective_projection) {
//			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//			projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//		}
//		else {
//			GLfloat halfsize = WorldSize / 2;
//			projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize * 2);
//		}
//		//원근 투영
//		unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//		GLfloat face_pos[6][3] = {
//			cube_pos[cube_idx[i * 2][0]][X], cube_pos[cube_idx[i * 2][0]][Y], cube_pos[cube_idx[i * 2][0]][Z],
//			cube_pos[cube_idx[i * 2][1]][X], cube_pos[cube_idx[i * 2][1]][Y], cube_pos[cube_idx[i * 2][1]][Z],
//			cube_pos[cube_idx[i * 2][2]][X], cube_pos[cube_idx[i * 2][2]][Y], cube_pos[cube_idx[i * 2][2]][Z],
//			cube_pos[cube_idx[i * 2 + 1][0]][X], cube_pos[cube_idx[i * 2 + 1][0]][Y], cube_pos[cube_idx[i * 2 + 1][0]][Z],
//			cube_pos[cube_idx[i * 2 + 1][1]][X], cube_pos[cube_idx[i * 2 + 1][1]][Y], cube_pos[cube_idx[i * 2 + 1][1]][Z],
//			cube_pos[cube_idx[i * 2 + 1][2]][X], cube_pos[cube_idx[i * 2 + 1][2]][Y], cube_pos[cube_idx[i * 2 + 1][2]][Z],
//		};
//		GLfloat face_color[6][3] = {
//			cube_color[cube_idx[i * 2][0]][X], cube_color[cube_idx[i * 2][0]][Y], cube_color[cube_idx[i * 2][0]][Z],
//			cube_color[cube_idx[i * 2][1]][X], cube_color[cube_idx[i * 2][1]][Y], cube_color[cube_idx[i * 2][1]][Z],
//			cube_color[cube_idx[i * 2][2]][X], cube_color[cube_idx[i * 2][2]][Y], cube_color[cube_idx[i * 2][2]][Z],
//			cube_color[cube_idx[i * 2 + 1][0]][X], cube_color[cube_idx[i * 2 + 1][0]][Y], cube_color[cube_idx[i * 2 + 1][0]][Z],
//			cube_color[cube_idx[i * 2 + 1][1]][X], cube_color[cube_idx[i * 2 + 1][1]][Y], cube_color[cube_idx[i * 2 + 1][1]][Z],
//			cube_color[cube_idx[i * 2 + 1][2]][X], cube_color[cube_idx[i * 2 + 1][2]][Y], cube_color[cube_idx[i * 2 + 1][2]][Z],
//		};
//		glBindBuffer(GL_ARRAY_BUFFER, cube_VBO_for_16[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(face_color), face_color, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, cube_VBO_for_16[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(face_pos), face_pos, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//	}
//}
//GLvoid DrawPyramidForTraining16() {
//	for (int i = 0; i < 6; ++i) {
//		//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 T = glm::mat4(1.0f);
//		glm::mat4 TtoAxes = glm::mat4(1.0f);
//		glm::mat4 FirstRotate = glm::mat4(1.0f);
//		glm::mat4 BackToPos = glm::mat4(1.0f);
//		Rx = glm::rotate(Rx, glm::radians(pyramid_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
//		Ry = glm::rotate(Ry, glm::radians(pyramid_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
//		//T = glm::translate(T, glm::vec3(0.0, 1.0,- ObjectSize - 50));
//		switch (i) {
//		case 0:
//			TtoAxes = glm::translate(TtoAxes, glm::vec3(0.0,0.0,-ObjectSize));
//			FirstRotate = glm::rotate(FirstRotate, glm::radians(pyramid_face_TR[0][X]), glm::vec3(1.0f, 0.0f, 0.0f));
//			BackToPos = glm::translate(BackToPos, glm::vec3(0.0, 0.0, +ObjectSize));
//			break;
//		case 1:
//			TtoAxes = glm::translate(TtoAxes, glm::vec3(-ObjectSize, 0.0, 0.0));
//			FirstRotate = glm::rotate(FirstRotate, glm::radians(pyramid_face_TR[1][Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//			BackToPos = glm::translate(BackToPos, glm::vec3(+ObjectSize, 0.0, 0.0));
//			break;
//		case 2:
//			TtoAxes = glm::translate(TtoAxes, glm::vec3(0.0, 0.0, ObjectSize));
//			FirstRotate = glm::rotate(FirstRotate, glm::radians(pyramid_face_TR[2][X]), glm::vec3(1.0f, 0.0f, 0.0f));
//			BackToPos = glm::translate(BackToPos, glm::vec3(0.0, 0.0, -ObjectSize));
//			break;
//		case 3:
//			TtoAxes = glm::translate(TtoAxes, glm::vec3(ObjectSize, 0.0, 0.0));
//			FirstRotate = glm::rotate(FirstRotate, glm::radians(pyramid_face_TR[3][Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//			BackToPos = glm::translate(BackToPos, glm::vec3(-ObjectSize, 0.0, 0.0));
//			break;
//		}
//		TR = T * Ry * Rx * (BackToPos*FirstRotate*TtoAxes);
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		//카메라 변환
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//		//투영변환
//		glm::mat4 projection = glm::mat4(1.0f);
//		//직각 투영
//		//GLfloat halfsize = WorldSize / 2;
//		//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//		//원근 투영
//		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//		unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//		GLfloat face_pos[3][3] = {
//			pyramid_pos[pyramid_idx[i][0]][X], pyramid_pos[pyramid_idx[i][0]][Y], pyramid_pos[pyramid_idx[i][0]][Z],
//			pyramid_pos[pyramid_idx[i][1]][X], pyramid_pos[pyramid_idx[i][1]][Y], pyramid_pos[pyramid_idx[i][1]][Z],
//			pyramid_pos[pyramid_idx[i][2]][X], pyramid_pos[pyramid_idx[i][2]][Y], pyramid_pos[pyramid_idx[i][2]][Z],
//		};
//		GLfloat face_color[3][3] = {
//			pyramid_color[pyramid_idx[i][0]][R], pyramid_color[pyramid_idx[i][0]][G], pyramid_color[pyramid_idx[i][0]][B],
//			pyramid_color[pyramid_idx[i][1]][R], pyramid_color[pyramid_idx[i][1]][G], pyramid_color[pyramid_idx[i][1]][B],
//			pyramid_color[pyramid_idx[i][2]][R], pyramid_color[pyramid_idx[i][2]][G], pyramid_color[pyramid_idx[i][2]][B],
//		};
//
//
//		glBindVertexArray(pyramid_VAO);
//
//		glBindBuffer(GL_ARRAY_BUFFER, pyramid_VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(face_color), face_color, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//
//		glBindBuffer(GL_ARRAY_BUFFER, pyramid_VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(face_pos), face_pos, GL_STATIC_DRAW);
//
//		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramid_VBO[INDEX]);
//		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramid_idx), pyramid_idx, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//	}
//
//
//	
//
//	
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	
//
//}
//GLvoid Timer(int value) {
//	static GLboolean FRONT_forward = true;
//	static GLboolean SIDE_forward = true;
//	static GLboolean PYRAMID_forward = true;
//	if (stop_timer != 0) {
//		--flag_timer;
//		--stop_timer;
//		FRONT_forward = true;
//		SIDE_forward = true;
//		PYRAMID_forward = true;
//		return;
//	}
//	
//	switch (value) {
//	case Y_ROTATE:
//		if (print_cube) {
//			cube_rotate[Y] += 5.0f;
//			ChangeDegree(cube_rotate[Y]);
//		}
//		else {
//			pyramid_rotate[Y] += 5.0f;
//			ChangeDegree(pyramid_rotate[Y]);
//		}
//		break;
//	case UP_FACE_ROTATE:
//		cube_face_TR[0][X] += 5;
//		ChangeDegree(cube_face_TR[0][X]);
//		break;
//	case FRONT_AND_BACK_ROTATE:
//		if (FRONT_forward) {
//			cube_face_TR[1][Z] += 5;
//			cube_face_TR[3][Z] -= 5;
//		}
//		else {
//			cube_face_TR[1][Z] -= 5;
//			cube_face_TR[3][Z] += 5;
//		}
//		if (cube_face_TR[1][Z] > 90.0f) {
//			cube_face_TR[1][Z] = 90.0f;
//			cube_face_TR[3][Z] = -90.0f;
//			FRONT_forward = 1 - FRONT_forward;
//		}
//		if (cube_face_TR[1][Z] < 0) {
//			cube_face_TR[1][Z] = 0.0f;
//			cube_face_TR[3][Z] = 0.0f;
//			FRONT_forward = 1 - FRONT_forward;
//		}
//		break;
//	case SIDE_FACE_MOVE:
//		if (SIDE_forward) {
//			cube_face_TR[2][Y] += 2;
//			cube_face_TR[4][Y] += 2;
//		}
//		else {
//			cube_face_TR[2][Y] -= 2;
//			cube_face_TR[4][Y] -= 2;
//		}
//		if (cube_face_TR[2][Y]>ObjectSize*2) {
//			cube_face_TR[2][Y] = cube_face_TR[4][Y] = ObjectSize*2;
//			SIDE_forward = 1 - SIDE_forward;
//		}
//		if(cube_face_TR[2][Y]<0) {
//			cube_face_TR[2][Y] = cube_face_TR[4][Y] = 0.0;
//			SIDE_forward = 1 - SIDE_forward;
//		}
//		break;
//	case PYRAMID_FACE_MOVE:
//		if (PYRAMID_forward) {
//			pyramid_face_TR[0][X]+=2;
//			pyramid_face_TR[1][Z]-=2;
//			pyramid_face_TR[2][X]-=2;
//			pyramid_face_TR[3][Z]+=2;
//		}
//		else {
//			pyramid_face_TR[0][X] -= 2;
//			pyramid_face_TR[1][Z] += 2;
//			pyramid_face_TR[2][X] += 2;
//			pyramid_face_TR[3][Z] -= 2;
//		}
//		if (pyramid_face_TR[0][X] > 235) {
//			pyramid_face_TR[0][X] =235;
//			pyramid_face_TR[1][Z] =-235;
//			pyramid_face_TR[2][X] =-235;
//			pyramid_face_TR[3][Z] =235;
//			PYRAMID_forward = 1 - PYRAMID_forward;
//		}
//		if (pyramid_face_TR[0][X] < 0) {
//			pyramid_face_TR[0][X] = 0;
//			pyramid_face_TR[1][Z] = 0;
//			pyramid_face_TR[2][X] = 0;
//			pyramid_face_TR[3][Z] = 0;
//			PYRAMID_forward = 1 - PYRAMID_forward;
//		}
//		
//		break;
//	}
//
//	glutTimerFunc(TimerSpeed, Timer, value);
//	glutPostRedisplay();
//
//}
//GLvoid InitBuffer() {
//	glGenVertexArrays(1, &cube_VAO);
//	glGenBuffers(3, cube_VBO);
//	glGenBuffers(3, cube_VBO_for_16);
//
//	glGenVertexArrays(1, &pyramid_VAO);
//	glGenBuffers(3, pyramid_VBO);
//
//	glGenVertexArrays(1, &axes_VAO);
//	glGenBuffers(2, axes_VBO);
//}
//GLvoid InitValue() {
//	{
//		for (int i = 0; i < 6; ++i) {
//			for (int j = 0; j < 3; ++j) {
//				axes_pos[i][j] = 0.0f;
//				axes_color[i][j] = 0.0f;
//			}
//		}
//		axes_pos[0][X] = 100;
//		axes_pos[1][X] = -100;
//		axes_pos[2][Y] = 100;
//		axes_pos[3][Y] = -100;
//		axes_pos[4][Z] = 100;
//		axes_pos[5][Z] = -100;
//		axes_color[0][R] = 1.0f;
//		axes_color[1][R] = 1.0f;
//		axes_color[2][G] = 1.0f;
//		axes_color[3][G] = 1.0f;
//		axes_color[4][B] = 1.0f;
//		axes_color[5][B] = 1.0f;
//		axes_rotate[X] = 30.0f;
//		axes_rotate[Y] = 30.0f;
//		axes_rotate[Z] = 0.0f;
//	}
//
//	{
//		cube_pos[0][X] = cube_pos[1][X] = cube_pos[4][X] = cube_pos[7][X] = -ObjectSize;
//		cube_pos[2][X] = cube_pos[3][X] = cube_pos[5][X] = cube_pos[6][X] = ObjectSize;
//		cube_pos[0][Y] = cube_pos[1][Y] = cube_pos[2][Y] = cube_pos[3][Y] = ObjectSize;
//		cube_pos[4][Y] = cube_pos[5][Y] = cube_pos[6][Y] = cube_pos[7][Y] = -ObjectSize;
//		cube_pos[0][Z] = cube_pos[3][Z] = cube_pos[6][Z] = cube_pos[7][Z] = -ObjectSize;
//		cube_pos[1][Z] = cube_pos[2][Z] = cube_pos[4][Z] = cube_pos[5][Z] = ObjectSize;
//
//		cube_idx[0][X] = 0, cube_idx[0][Y] = 1, cube_idx[0][Z] = 2;
//		cube_idx[1][X] = 0, cube_idx[1][Y] = 2, cube_idx[1][Z] = 3;
//		cube_idx[2][X] = 1, cube_idx[2][Y] = 4, cube_idx[2][Z] = 5;
//		cube_idx[3][X] = 1, cube_idx[3][Y] = 5, cube_idx[3][Z] = 2;
//		cube_idx[4][X] = 2, cube_idx[4][Y] = 5, cube_idx[4][Z] = 6;
//		cube_idx[5][X] = 2, cube_idx[5][Y] = 6, cube_idx[5][Z] = 3;
//		cube_idx[6][X] = 3, cube_idx[6][Y] = 6, cube_idx[6][Z] = 7;
//		cube_idx[7][X] = 3, cube_idx[7][Y] = 7, cube_idx[7][Z] = 0;
//		cube_idx[8][X] = 0, cube_idx[8][Y] = 7, cube_idx[8][Z] = 4;
//		cube_idx[9][X] = 0, cube_idx[9][Y] = 4, cube_idx[9][Z] = 1;
//		cube_idx[10][X] = 6, cube_idx[10][Y] = 5, cube_idx[10][Z] = 4;
//		cube_idx[11][X] = 6, cube_idx[11][Y] = 4, cube_idx[11][Z] = 7;
//
//		cube_color[0][R] = 1.0f, cube_color[0][G] = 0.0f, cube_color[0][B] = 0.0f;
//		cube_color[1][R] = 0.0f, cube_color[1][G] = 1.0f, cube_color[1][B] = 0.0f;
//		cube_color[2][R] = 0.0f, cube_color[2][G] = 0.0f, cube_color[2][B] = 1.0f;
//		cube_color[3][R] = 1.0f, cube_color[3][G] = 1.0f, cube_color[3][B] = 0.0f;
//		cube_color[4][R] = 0.0f, cube_color[4][G] = 1.0f, cube_color[4][B] = 1.0f;
//		cube_color[5][R] = 1.0f, cube_color[5][G] = 0.0f, cube_color[5][B] = 1.0f;
//		cube_color[6][R] = 1.0f, cube_color[6][G] = 1.0f, cube_color[6][B] = 1.0f;
//		cube_color[7][R] = 0.5f, cube_color[7][G] = 0.5f, cube_color[7][B] = 0.5f;
//
//		cube_rotate[X] = 30.0f;
//		cube_rotate[Y] = 30.0f;
//		cube_rotate[Z] = 0.0f;
//
//		for (int i = 0; i < 6; ++i) {
//			for (int j = 0; j < 3; ++j) {
//				cube_face_TR[i][j] = 0.0f;
//			}
//		}
//		
//		print_cube = true;
//	}
//
//	{
//		pyramid_pos[0][X]=0.0, pyramid_pos[0][Y]= ObjectSize * 2, pyramid_pos[0][Z] = 0.0;
//		pyramid_pos[1][X]=-ObjectSize, pyramid_pos[1][Y]=0.0, pyramid_pos[1][Z] = -ObjectSize;
//		pyramid_pos[2][X]=-ObjectSize, pyramid_pos[2][Y]=0.0, pyramid_pos[2][Z] = ObjectSize;
//		pyramid_pos[3][X]=ObjectSize, pyramid_pos[3][Y]=0.0, pyramid_pos[3][Z] = ObjectSize;
//		pyramid_pos[4][X]=ObjectSize, pyramid_pos[4][Y]=0.0, pyramid_pos[4][Z] = -ObjectSize;
//
//		pyramid_color[0][X]=1.0f, pyramid_color[0][Y]=1.0f, pyramid_color[0][Z] = 1.0f;
//		pyramid_color[1][X]=1.0f, pyramid_color[1][Y]=0.0f, pyramid_color[1][Z] = 0.0f;
//		pyramid_color[2][X]=0.0f, pyramid_color[2][Y]=1.0f, pyramid_color[2][Z] = 0.0f;
//		pyramid_color[3][X]=0.0f, pyramid_color[3][Y]=0.0f, pyramid_color[3][Z] = 1.0f;
//		pyramid_color[4][X]=0.0f, pyramid_color[4][Y]=1.0f, pyramid_color[4][Z] = 1.0f;
//
//		pyramid_idx[0][X]=0, pyramid_idx[0][Y]=2, pyramid_idx[0][Z] = 3;
//		pyramid_idx[1][X]=0, pyramid_idx[1][Y]=3, pyramid_idx[1][Z] = 4;
//		pyramid_idx[2][X]=0, pyramid_idx[2][Y]=4, pyramid_idx[2][Z] = 1;
//		pyramid_idx[3][X]=0, pyramid_idx[3][Y]=1, pyramid_idx[3][Z] = 2;
//		pyramid_idx[4][X]=1, pyramid_idx[4][Y]=4, pyramid_idx[4][Z] = 3;
//		pyramid_idx[5][X]=1, pyramid_idx[5][Y]=3, pyramid_idx[5][Z] = 2;
//
//		pyramid_rotate[X] = 30.0f;
//		pyramid_rotate[Y] = 30.0f;
//
//		for (int i = 0; i < 5; ++i) {
//			pyramid_face_TR[i][X] = pyramid_face_TR[i][Y] = pyramid_face_TR[i][Z] = 0.0f;
//		}
//		
//		
//	}
//
//	{
//		glEnable(GL_DEPTH_TEST);
//		flag_depth_test = true;
//		/*glEnable(GL_CULL_FACE);
//		flag_cull_face = true;*/
//		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		flag_draw_line = true;*/
//	}
//
//	{
//		stop_timer = flag_timer;
//		up_face_rotate_degree = 0.0f;
//	}
//	
//	{
//		cameraPos = glm::vec3(0.0f, 0.0f, WorldSize/2);
//		cameraDirection = glm::vec3(1.0f, 0.0f, 0.0f);
//		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//		flag_perspective_projection = true;
//	}
//	
//	
//}
//GLvoid DrawAxes() {
//	glBindVertexArray(axes_VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, axes_VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(axes_color), axes_color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, axes_VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(axes_pos), axes_pos, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//
//	//model 변환
//	glm::mat4 TR = glm::mat4(1.0f);
//	glm::mat4 Rx = glm::mat4(1.0f);
//	glm::mat4 Ry = glm::mat4(1.0f);
//	glm::mat4 T = glm::mat4(1.0f);
//	Rx = glm::rotate(Rx, glm::radians(axes_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
//	Ry = glm::rotate(Ry, glm::radians(axes_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
//	//T = glm::translate(T, glm::vec3(0.0, 1.0,- ObjectSize - 50));
//	TR = T * Ry * Rx;
//	unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	//카메라 변환
//	glm::mat4 view = glm::mat4(1.0f);
//	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//	unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//	//투영변환
//	glm::mat4 projection = glm::mat4(1.0f);
//	//직각 투영
//	//GLfloat halfsize = WorldSize / 2;
//	//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//	//원근 투영
//	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//	unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	glDrawArrays(GL_LINES, 0, 6);
//}
//GLvoid ChangeDegree(GLfloat degree) {
//	if (degree < 0.0f) {
//		degree += 360.0f;
//	}
//	else {
//		degree -= 360.0f;
//	}
//}
//
//GLvoid DrawCube() {
//	glBindVertexArray(cube_VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, cube_VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color), cube_color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, cube_VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_idx), cube_idx, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//
//	//model 변환
//	glm::mat4 TR = glm::mat4(1.0f);
//	glm::mat4 Rx = glm::mat4(1.0f);
//	glm::mat4 Ry = glm::mat4(1.0f);
//	glm::mat4 T = glm::mat4(1.0f);
//	Rx = glm::rotate(Rx, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
//	Ry = glm::rotate(Ry, glm::radians(+30.0f), glm::vec3(0.0, 1.0, 0.0));
//	//T = glm::translate(T, glm::vec3(0.0, 1.0,- ObjectSize - 50));
//	TR = T * Ry * Rx;
//	unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	//카메라 변환
//	glm::mat4 view = glm::mat4(1.0f);
//	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//	unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//	//투영변환
//	glm::mat4 projection = glm::mat4(1.0f);
//	//직각 투영
//	//GLfloat halfsize = WorldSize / 2;
//	//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//	//원근 투영
//	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//	unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//
//}
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