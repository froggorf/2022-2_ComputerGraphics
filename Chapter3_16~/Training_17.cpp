///*
//단축키
//1 - 타이머 시작
//p/P - 직각/원근
//m/M - 선/채우기
//wasd휠 - 카메라 회전
//방향키 - 물체 이동 xy축
//,. - 물체이동 z축
//y/Y - 물체 y축에 대해 회전
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
//#define WorldSize 200
//
////enum
//enum RGB { R = 0,G = 1,B = 2 };
//enum XYZ { X = 0, Y = 1, Z = 2 };
//
//enum SPHERE{MAIN = 0, SUB = 1, MOON = 2};
//
//
////glut 관련 함수
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid KeyBoard(unsigned char key, int x, int y);
//GLvoid SpecialKeyBoard(int key, int x, int y);
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
//GLuint qobj_sProgram;
//
////카메라 관련 함수 및 변수
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, WorldSize / 2);
//glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//GLboolean flag_perspective_projection = true;
//
////구 관련 변수 및 함수
//GLvoid DrawSphere();
//GLfloat sphereT[3];
//GLfloat sphereR[3][3];
//GLfloat earthR[3][3];
//GLfloat moonR[3][3];
//GLfloat revolutionY;
//GLboolean draw_line = true;
//
////VAO, VBO 관련 함수 및 변수
//GLuint VAO, VBO;
//GLvoid InitBuffer();
//
////내가 만든 함수 와 변수
//GLvoid InitValue();
//
////타이머 관련
//int TimerSpeed = 30;
//GLvoid TimerFunc(int value);
//int flag_timer = 0;
//int stop_timer = 0;
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
//	InitValue();
//	InitShader();
//	InitBuffer();
//	glEnable(GL_DEPTH_TEST);
//	glutDisplayFunc(drawScene); // 출력 함수의 지정
//	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//	glutKeyboardFunc(KeyBoard);
//	glutSpecialFunc(SpecialKeyBoard);
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
//
//	DrawSphere();
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
//	case 'M':
//	case 'm':
//		if (draw_line)
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		else
//			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		draw_line = 1 - draw_line;
//		break;
//
//	case '1':
//		glutTimerFunc(TimerSpeed, TimerFunc, 0);
//		++flag_timer;
//		break;
//	case 'p':
//	case 'P':
//		flag_perspective_projection = 1 - flag_perspective_projection;
//		break;
//	case ',':
//		sphereT[Z] -= 2;
//		break;
//	case '.':
//		sphereT[Z] += 2;
//		break;
//	case 'Y':
//		revolutionY = int(revolutionY - 2) % -360;
//		std::cout <<"1:" << revolutionY << std::endl;
//		break;
//	case 'y':
//		revolutionY = int(revolutionY + 2) % 360;
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
//			std::cout << "z: " << cameraPos.z << std::endl;
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
//GLvoid SpecialKeyBoard(int key, int x, int y) {
//	switch (key) {
//	case GLUT_KEY_LEFT:
//		sphereT[X] -= 2;
//		break;
//	case GLUT_KEY_RIGHT:
//		sphereT[X] += 2;
//		break;
//	case GLUT_KEY_DOWN:
//		sphereT[Y] -= 2;
//		break;
//	case GLUT_KEY_UP:
//		sphereT[Y] += 2;
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
//
//GLvoid TimerFunc(int value) {
//	if (stop_timer != 0) {
//		--stop_timer;
//		--flag_timer;
//		return;
//	}
//
//	//sphereR[SUB][Y] = int(sphereR[SUB][Y] + 2) % 360;
//	//sphereR[MOON][Y] = int(sphereR[MOON][Y] + 2) % 360;
//	
//	earthR[0][Y] = int(earthR[0][Y] + 1) % 360;
//	earthR[1][Y] = int(earthR[1][Y] + 3) % 360;
//	earthR[2][Y] = int(earthR[2][Y] + 6) % 360;
//	
//	moonR[0][Y] = int(moonR[0][Y] + 1) % 360;
//	moonR[1][Y] = int(moonR[1][Y] + 3) % 360;
//	moonR[2][Y] = int(moonR[2][Y] + 6) % 360;
//
//	//glFrontFace(GL_CCW);
//
//
//	glutPostRedisplay();
//	glutTimerFunc(TimerSpeed, TimerFunc, 0);
//}
//
//GLvoid DrawSphere() {
//	glm::mat4 rrrrr = glm::mat4(1.0f);
//	rrrrr = glm::rotate(rrrrr, glm::radians(15.0f), glm::vec3(1.0, 0.0, 0.0));
//	glm::mat4 finaltranslate = glm::mat4(1.0f);
//	finaltranslate = glm::translate(finaltranslate, glm::vec3(sphereT[X], sphereT[Y], sphereT[Z]));
//	glm::mat4 finalrotateY = glm::mat4(1.0f);
//	finalrotateY = glm::rotate(finalrotateY, glm::radians(revolutionY), glm::vec3(0.0, 1.0, 0.0));
//	glm::mat4 projection = glm::mat4(1.0f);
//	if (flag_perspective_projection) {
//		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//	}
//	else {
//		GLfloat halfsize = WorldSize / 2;
//		projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize * 2);
//	}
//	unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//	glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//	glUseProgram(s_program);
//	{//MAIN
//
//		glm::mat4 TR = glm::mat4(1.0f);
//		glm::mat4 Rx = glm::mat4(1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		glm::mat4 T = glm::mat4(1.0f); 
//		//Rx = glm::rotate(Rx, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
//		//Ry = glm::rotate(Ry, glm::radians(+30.0f), glm::vec3(0.0, 1.0, 0.0));
//		//T = glm::translate(T, glm::vec3(0.0, 1.0,- ObjectSize - 50));
//		TR = finalrotateY * finaltranslate *rrrrr*T * Ry * Rx;
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//
//		//카메라 변환
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//		//투영변환
//		
//		
//
//		
//
//		
//		GLUquadricObj* qobj;
//		qobj = gluNewQuadric();
//
//		unsigned int r = glGetUniformLocation(s_program, "rgb");
//		glUniform3f(r,0,0,1);
//		
//		gluSphere(qobj, 15, 50, 50);
//		
//	}
//	
//	glm::vec4 point[3] = {
//		{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,0.0f,1.0f}
//	};
//	{//SUB
//		for (int i = 0; i < 3; ++i) {
//			{
//				glm::mat4 TR = glm::mat4(1.0f);
//				glm::mat4 Rx = glm::mat4(1.0f);
//				glm::mat4 Ry = glm::mat4(1.0f);
//				glm::mat4 Rz = glm::mat4(1.0f);
//				
//				glm::mat4 T = glm::mat4(1.0f);
//				GLUquadricObj* qobj1 = gluNewQuadric();
//				Rx = glm::rotate(Rx, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
//				if (i != 0)Rz = glm::rotate(Rz, glm::radians(GLfloat(90.0 * i - 45)), glm::vec3(0.0, 0.0, 1.0));
//				TR = finalrotateY * finaltranslate*rrrrr*Rz*Rx;
//				unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//				unsigned int r = glGetUniformLocation(s_program, "rgb");
//				glUniform3f(r, 1,1,1);
//				gluDisk(qobj1, 34.9,35, 100, 1);
//			}
//
//			GLUquadricObj* qobj;
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 Rx = glm::mat4(1.0f);
//			glm::mat4 Ry = glm::mat4(1.0f);
//			glm::mat4 Rz = glm::mat4(1.0f);
//			glm::mat4 T = glm::mat4(1.0f);
//			//Rx = glm::rotate(Rx, glm::radians(30.0f), glm::vec3(1.0, 0.0, 0.0));
//			{
//
//			}
//			if(i!=0)Rz = glm::rotate(Rz, glm::radians(GLfloat( 90.0*i-45)), glm::vec3(0.0, 0.0, 1.0));
//			Ry = glm::rotate(Ry, glm::radians(earthR[i][Y]), glm::vec3(0.0, 1.0, 0.0));
//			T = glm::translate(T, glm::vec3(35, 0, 0));
//			TR = finalrotateY * finaltranslate*rrrrr*Rz* Ry * T;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//
//			
//			point[i] = TR * point[i];
//				
//			
//
//			//카메라 변환
//			glm::mat4 view = glm::mat4(1.0f);
//			view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//			unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//			//투영변환
//			glm::mat4 projection = glm::mat4(1.0f);
//			//직각 투영
//			//GLfloat halfsize = WorldSize / 2;
//			//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//			//원근 투영
//			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//			projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//			unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//			//glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//			qobj = gluNewQuadric();
//			unsigned int r = glGetUniformLocation(s_program, "rgb");
//			glUniform3f(r, 0, 1, 0);
//			gluSphere(qobj, 5, 30, 30);
//		}
//	}
//
//	{//MOON
//		for (int i = 0; i < 3; ++i) {
//			{
//				glm::mat4 TR = glm::mat4(1.0f);
//				glm::mat4 Rx = glm::mat4(1.0f);
//				glm::mat4 Ry = glm::mat4(1.0f);
//				glm::mat4 T = glm::mat4(1.0f);
//				glm::mat4 pointT = glm::mat4(1.0f);
//
//				GLUquadricObj* qobj1 = gluNewQuadric();
//				Rx = glm::rotate(Ry, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
//				
//				pointT = glm::translate(pointT, glm::vec3(point[i].x, point[i].y, point[i].z));
//				TR = pointT *rrrrr*Rx;
//				unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//				unsigned int r = glGetUniformLocation(s_program, "rgb");
//				glUniform3f(r, 1, 1, 1);
//				gluDisk(qobj1, 14.9,15.1, 100, 1);
//			}
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 Rx = glm::mat4(1.0f);
//			glm::mat4 Ry = glm::mat4(1.0f);
//			glm::mat4 T = glm::mat4(1.0f);
//			glm::mat4 pointT = glm::mat4(1.0f);
//			//Rx = glm::rotate(Rx, glm::radians(sphereR[2][Xy), glm::vec3(1.0, 0.0, 0.0));
//			Ry = glm::rotate(Ry, glm::radians(moonR[i][Y]+120*i), glm::vec3(0.0, 1.0, 0.0));
//			T = glm::translate(T, glm::vec3(15,0,0));
//			pointT = glm::translate(pointT, glm::vec3(point[i].x, point[i].y, point[i].z));
//			TR = pointT*rrrrr*Ry *T ;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//
//			//카메라 변환
//			glm::mat4 view = glm::mat4(1.0f);
//			view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//			unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//			//투영변환
//			glm::mat4 projection = glm::mat4(1.0f);
//			//직각 투영
//			//GLfloat halfsize = WorldSize / 2;
//			//project = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//			//원근 투영
//			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize);
//			projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//
//			unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//			//glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//
//			GLUquadricObj* qobj;
//			qobj = gluNewQuadric();
//			unsigned int r = glGetUniformLocation(s_program, "rgb");
//			glUniform3f(r, 1, 0, 0);
//			gluSphere(qobj, 3, 50, 50);
//		}
//	}
//}
//
//GLvoid InitBuffer() {
//	/*
//	glGenVertexArrays(1, &VAO)
//	glGenBuffers(2, VBO);
//	*/
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	/*;
//	glBindVertexArray(VAO);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);*/
//}
//GLvoid InitValue() {
//	{
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		draw_line = true;
//	}
//
//	{
//		for (int i = 0; i < 3; ++i) {
//			for (int j = 0; j < 3; ++j) {
//				sphereT[i] = 0.0f;
//				sphereR[i][j] = 0.0f;
//			}
//		}
//
//	}
//	{
//		flag_perspective_projection = true;
//	}
//	{
//		revolutionY = 0.0f;
//	}
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
//	fragmentsource = filetobuf("fragment17.glsl");
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
//
//
//	/*make_vertexShaders();
//	GLchar* fragmentsource;
//
//	fragmentsource = filetobuf("fragment17.glsl");
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
//	qobj_sProgram = glCreateProgram();
//
//	glAttachShader(qobj_sProgram, vertexShader);
//	glAttachShader(qobj_sProgram, fragmentShader);
//	glLinkProgram(qobj_sProgram);
//
//	checkCompileErrors(qobj_sProgram, "PROGRAM");
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);*/
//
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