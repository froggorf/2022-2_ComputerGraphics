#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#include <cmath>
#define PI 3.141592
#define WIDTH 800
#define HEIGHT 600
#define MaxPointNum 500
#define TimerSpeed 50
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid WindowCursorToGl(int w_x, int w_y, GLfloat& gl_x, GLfloat& gl_y);
std::random_device rd;
std::uniform_real_distribution<GLfloat> urd(0.0, 1.0);
void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitBuffer();
GLvoid InitShader();
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
GLuint VAO, VBO_shape, VBO_color;
GLfloat point[MaxPointNum][3];
GLfloat colors[MaxPointNum][3];
GLboolean flag_timer = false, timer_off = false;
int pointNum = 0;

GLfloat circle_x, circle_y;
GLfloat radius;
int degree;

void TimerFunc(int);
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
	
	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < MaxPointNum; ++i) {
		colors[i][0] = 1.0;
		colors[i][1] = 1.0;
		colors[i][2] = 1.0;
	}

	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
	InitBuffer();

	glPointSize(3.0);
	if(pointNum!=0) glDrawArrays(GL_POINTS, 0, MaxPointNum);

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) 
{
	glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'S':
	case 's':
		if (flag_timer) {
			timer_off = true;
		}
		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	
	if (state == GLUT_DOWN&&button == GLUT_LEFT_BUTTON) {
		if (flag_timer) {
			printf("그림을 그리는 중이라 그리기 불가. 타이머를 종료했다가 해주세요.\n");
			return;
		}
		glClearColor(urd(rd), urd(rd), urd(rd), 1.0f);
		WindowCursorToGl(x, y, circle_x, circle_y);
		radius = 0.01;
		degree = 0;
		pointNum = 0;
		glutTimerFunc(TimerSpeed, TimerFunc, 0);
		flag_timer = true;
	}
	
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {

	glutPostRedisplay();
}

void TimerFunc(int value) {
	if (timer_off) {
		flag_timer = false;
		timer_off = false;
		return;
	}
	
	if (value == 0) {
		double radian = degree * PI / 180;
		point[pointNum][0] = circle_x + radius * cos(radian);
		point[pointNum][1] = circle_y + radius * sin(radian);

		degree += 8;
		if (degree >= 360 * 3) degree = 360 * 3;
		radius += 0.002;
		++pointNum;

		if (degree >= 360 * 3) {
			circle_x += 2*(0.002*(360*3/8))+0.002*10;
			circle_y -= 0.002 * 10;
			glutTimerFunc(TimerSpeed, TimerFunc, 1);
			degree += 180;
			degree -=8;
			//radius -= 0.002*6;
			
			return;
		}
	}
	
	if (value == 1) {
		double radian = degree * PI / 180;
		point[pointNum][0] = circle_x + radius * cos(radian);
		point[pointNum][1] = circle_y + radius * sin(radian);

		degree -= 8;
		radius -= 0.002;
		++pointNum;

		if (degree <= 180) {
			timer_off = true;
		}
	}

	glutTimerFunc(TimerSpeed, TimerFunc, value);
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
	if (pointNum == 0) return;
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_shape);
	glBufferData(GL_ARRAY_BUFFER, pointNum * 3 * sizeof(GLfloat), point, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, pointNum * 3 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
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
	double w = (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	gl_x = (w_x - w) / w;
	gl_y = ((w_y - h) / h) * -1;
}