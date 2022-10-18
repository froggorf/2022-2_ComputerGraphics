/*
https://playground10.tistory.com/289 (다각형 안에 점이 있는지 확인하는 방법)
https://tibyte.kr/23 (선분과 선분이 충돌체크 했는지 확인하는 방법)
을 보다가 어려워서
https://crazyj.tistory.com/140 로 갈아탔으나 어려워서

https://bowbowbow.tistory.com/24 를 보고 성공함
but 방식은 아직 이해가 안됨 다시 읽어보자.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define GrabSize 0.03 // 점으로 인식되는 범위 설정
#define PolygonNum 7
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid WindowCursorToGl(int w_x, int w_y, GLfloat& gl_x, GLfloat& gl_y);
GLboolean PtInPolygon(GLfloat point[3], GLfloat shape[PolygonNum][3]);

void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);

GLvoid InitBuffer();
GLvoid InitShader();
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
GLuint VAO, VBO_shape, VBO_color;
std::random_device rd;
std::uniform_real_distribution<GLfloat> urd_pos(-1.0f, 1.0f);

GLfloat shape[PolygonNum][3] = {
	{0.5,0.5,0.0},
	{-0.5,0.5,0.0},
	{-0.5,-0.5,0.0},
	{0.5,-0.5,0.0}
};
GLfloat color[PolygonNum][3] = {
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0},
	{0.0,0.0,0.0}
};

GLfloat old_x, old_y;

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

	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_shape);
	glGenBuffers(1, &VBO_color);
	
	if (PolygonNum != 4) {
		for (int i = 0; i < PolygonNum; ++i) {
			shape[i][0] = urd_pos(rd);
			shape[i][1] = urd_pos(rd);
			color[i][0] = color[i][1] = color[i][2] = 0.0;
		}
	}

	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);

	

	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 ‘blue’ 로 지정

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
	InitBuffer();

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, PolygonNum);

	glPointSize(10.0);
	glDrawArrays(GL_POINTS, 0, PolygonNum);

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
		if (PolygonNum != 4) {
			for (int i = 0; i < PolygonNum; ++i) {
				shape[i][0] = urd_pos(rd);
				shape[i][1] = urd_pos(rd);
				color[i][0] = color[i][1] = color[i][2] = 0.0;
			}
		}
		else {
			shape[0][0] = 0.5;	shape[0][1] = 0.5;
			shape[1][0] = -0.5;	shape[1][1] = 0.5;
			shape[2][0] = -0.5;	shape[2][1] = -0.5;
			shape[3][0] = 0.5;	shape[3][1] = -0.5;
		}
		break;
	}

	glutPostRedisplay();
}
int grab_num = -1;

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	grab_num = -1;
	old_x = old_y = 0;
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		GLfloat point[3]={0.0,0.0,0.0};
		WindowCursorToGl(x, y, point[0], point[1]);
		
		for (int i = 0; i < PolygonNum; ++i) {
			GLfloat dis_x = point[0] - shape[i][0], dis_y = point[1] - shape[i][1];
			if (-GrabSize <= dis_x && dis_x <= GrabSize && -GrabSize <= dis_y && dis_y <= GrabSize) {	//점 주변을 잡았을 경우
				grab_num = i;
			}
		}
		if (grab_num == -1) {
			if (PtInPolygon(point, shape)) {
				grab_num = PolygonNum;
				old_x = point[0]; old_y = point[1];
			}
		}
		
	}
	
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {
	if (0 <= grab_num && grab_num <= PolygonNum-1) {
		GLfloat gl_x, gl_y;
		WindowCursorToGl(x, y, gl_x, gl_y);
		shape[grab_num][0] = gl_x;
		shape[grab_num][1] = gl_y;
	}
	else if (grab_num == PolygonNum) {
		GLfloat new_x, new_y;
		WindowCursorToGl(x, y, new_x, new_y);
		for (int i = 0; i < PolygonNum; ++i) {
			shape[i][0] += (new_x - old_x);
			shape[i][1] += (new_y - old_y);
		}
		old_x = new_x;	old_y = new_y;
	}
	glutPostRedisplay();
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

GLvoid InitBuffer() {
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_shape);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shape), shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
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

GLvoid WindowCursorToGl(int w_x, int w_y, GLfloat& gl_x, GLfloat& gl_y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	gl_x = (w_x - w) / w;
	gl_y = ((w_y - h) / h) * -1;
}
GLboolean PtInPolygon(GLfloat point[3], GLfloat shape[PolygonNum][3]) {
	int crosses = 0;

	for (int i = 0; i < PolygonNum; ++i) {
		int j = (i + 1) % PolygonNum;  //0번째와 1번째, 1번째와 2번째, ... PolygonNum-1 번째와 0(PolygonNum%PolygonNum)번째

		if ((shape[i][1] > point[1]) != (shape[j][1] > point[1])) {		//point의 y좌표가 (shape[
			GLfloat atX = (shape[j][0] - shape[i][0]) * (point[1] - shape[i][1]) / (shape[j][1] - shape[i][1]) + shape[i][0];

			if (point[0] < atX)
				++crosses;
		}
	}
	return crosses % 2 > 0;
}