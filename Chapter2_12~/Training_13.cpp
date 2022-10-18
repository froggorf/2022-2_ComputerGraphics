/*
c - 큐브 <-> 사각뿔
X/x - x축 회전(양/음)
Y/y - y축 회전(양/음)
W/w - 선/면
방향키 - 객체 이동
s - 타이머 전부 종료
S - 타이머 전부 종료 + 원래 위치로 이동
H/h - 은면 적용/해제
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#define WIDTH 800
#define HEIGHT 600
#define X 0
#define Y 1
#define RotateSpeed 4		//n도씩 애니메이션이 되도록
#define ObjectSpeed 0.05
int TimerSpeed = 50;
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid InitValue();
void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitBuffer();
GLvoid InitShader();
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
GLuint VAO_axes, VBO_axes[2];
GLuint VAO_cube, VBO_cube[2], VBO_index;
GLuint VAO_pyramid, VBO_pyramid[2], VBO_pyramid_index;
bool draw_cube = true;
GLfloat cube_rotate[2] = { 30.0,-30.0 }, pyramid_rotate[2] = { 30.0,-30.0 };
GLfloat cube_translate[2] = { 0.0,0.0 }, pyramid_translate[2] = { 0.0,0.0 };
void RotateObject(int value);
int flag_timer = 0;
int off_timer = 0;
bool flag_cull = false;
GLfloat cube_shape[8][3] = {
	-0.25,0.25,0.25,
	-0.25,0.25,-0.25,
	0.25,0.25,-0.25,
	0.25,0.25,0.25,
	-0.25,-0.25,-0.25,
	0.25,-0.25,-0.25,
	0.25,-0.25,0.25,
	-0.25,-0.25,0.25
};
unsigned int cube_idx[12][3] = {
	0,1,2,
	0,2,3,
	1,4,5,
	1,5,2,
	2,5,6,
	2,6,3,
	3,6,7,
	3,7,0,
	0,7,4,
	0,4,1,
	6,5,4,
	6,4,7
};
GLfloat pyramid_shape[5][3] = {
	0.0,0.25,0.0,
	-0.25,-0.25,-0.25,
	-0.25,-0.25,0.25,
	0.25,-0.25,0.25,
	0.25,-0.25,-0.25
};
unsigned int pyramid_index[6][3] = {
	0,2,3,
	0,3,4,
	0,4,1,
	0,1,2,
	1,4,3,
	1,3,2
};
void DrawCoordinateAxes();
void DrawCube();
void DrawPyramid();
void SpecialKey(int key, int x, int y);
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
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

	/*
	glGenVertexArrays(1, &VAO)
	glGenBuffers(2, VBO);
	*/
	InitValue();
	glGenVertexArrays(1, &VAO_axes);
	glGenBuffers(2, VBO_axes);
	glGenVertexArrays(1, &VAO_cube);
	glGenBuffers(2, VBO_cube);
	glGenBuffers(1, &VBO_index);
	glGenVertexArrays(1, &VAO_pyramid);
	glGenBuffers(2, VBO_pyramid);
	glGenBuffers(1, &VBO_pyramid_index);
	InitShader();
	InitBuffer();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);


	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {
	//--- 콜백 함수: 그리기 콜백 함수 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 바탕색을 ‘blue’ 로 지정

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다
	DrawCoordinateAxes();
	if (draw_cube) {
		DrawCube();
	}
	else {
		DrawPyramid();
	}
	

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
	case 'c':
		off_timer = flag_timer;
		draw_cube = 1 - draw_cube;
		break;
	case 'X':
		glutTimerFunc(TimerSpeed, RotateObject, 0);
		flag_timer += 1;
		break;
	case 'x':
		glutTimerFunc(TimerSpeed, RotateObject, 1);	
		flag_timer += 1;
		break;
	case 'Y':
		glutTimerFunc(TimerSpeed, RotateObject, 2);
		flag_timer += 1;
		break;
	case 'y':
		glutTimerFunc(TimerSpeed, RotateObject, 3);
		flag_timer += 1;
		break;
	case 'S':
		if (flag_timer > 0) {
			off_timer = flag_timer;
		}
		cube_translate[X] = cube_translate[Y] = pyramid_translate[X] = pyramid_translate[Y] = 0.0;
		cube_rotate[X] = pyramid_rotate[X] = 30.0;
		cube_rotate[Y] = pyramid_rotate[Y] = -30.0;
		break;
	case 's':
		if (flag_timer>0) {
			off_timer = flag_timer;
		}
		break;
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'H':
	case 'h':
		if (flag_cull)
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		flag_cull = 1 - flag_cull;
		break;
	}

	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		if (draw_cube)
			cube_translate[X] -= ObjectSpeed;
		else
			pyramid_translate[X] -= ObjectSpeed;
		break;
	case GLUT_KEY_RIGHT:
		if (draw_cube)
			cube_translate[X] += ObjectSpeed;
		else
			pyramid_translate[X] += ObjectSpeed;
		break;
	case GLUT_KEY_UP:
		if (draw_cube)
			cube_translate[Y] += ObjectSpeed;
		else
			pyramid_translate[Y] += ObjectSpeed;
		break;
	case GLUT_KEY_DOWN:
		if (draw_cube)
			cube_translate[Y] -= ObjectSpeed;
		else
			pyramid_translate[Y] -= ObjectSpeed;
		break;
	}
	glutPostRedisplay();
}

void RotateObject(int value) {
	if (off_timer>0) {
		flag_timer -= 1;
		off_timer -= 1;
		return;
	}
	switch (value) {
	case 0:
		if (draw_cube) {
			cube_rotate[X] += RotateSpeed;
			if (cube_rotate[X] > 360) cube_rotate[X] -= 360;
		}
		else {
			pyramid_rotate[X] += RotateSpeed;
			if (pyramid_rotate[X] > 360)pyramid_rotate[X] -= 360;
		}
		break;
	case 1:
		if (draw_cube) {
			cube_rotate[X] -= RotateSpeed;
			if (cube_rotate[X] < 0) cube_rotate[X] += 360;
		}
		else {
			pyramid_rotate[X] -= RotateSpeed;
			if (pyramid_rotate[X] < 0) pyramid_rotate[X] += 360;
		}
		break;
	case 2:
		if (draw_cube) {
			cube_rotate[Y] += RotateSpeed;
			if (cube_rotate[Y] > 360) cube_rotate[Y] -= 360;
		}
		else {
			pyramid_rotate[Y] += RotateSpeed;
			if (pyramid_rotate[Y] > 360) pyramid_rotate[Y] -= 360;
		}
		break;
	case 3:
		if (draw_cube) {
			cube_rotate[Y] -= RotateSpeed;
			if (cube_rotate[Y] < 0) cube_rotate[Y] += 360;
		}
		else {
			pyramid_rotate[Y] -= RotateSpeed;
			if (pyramid_rotate[Y] < 0) pyramid_rotate[Y] += 360;
		}
		break;
	}
	glutTimerFunc(TimerSpeed, RotateObject, value);
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN

	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {

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
	/*;
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), triShape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);*/
}

void DrawCube() {
	glBindVertexArray(VAO_cube);
	GLfloat cube_color[8][3] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		1.0f,1.0f,0.0f,
		1.0f,0.0f,1.0f,
		0.0f,1.0f,1.0f,
		0.5f,0.2f,0.8f,
		0.8f,0.2f,0.5f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color), cube_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_shape), cube_shape, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_idx), cube_idx, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	T = glm::translate(T, glm::vec3(cube_translate[X],cube_translate[Y],0.0));
	Rx = glm::rotate(Rx, glm::radians(cube_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(cube_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	TR = T*Ry * Rx;
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

void DrawPyramid() {
	glBindVertexArray(VAO_pyramid);
	GLfloat pyramid_color[5][3] = {
		1.0f,1.0f,1.0f,
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
		0.3f,0.7f,0.3f
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pyramid[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_color), pyramid_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_pyramid[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_shape), pyramid_shape, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_pyramid_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramid_index), pyramid_index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	T = glm::translate(T, glm::vec3(pyramid_translate[X], pyramid_translate[Y], 0.0));
	Rx = glm::rotate(Rx, glm::radians(pyramid_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(pyramid_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	TR = T* Ry * Rx;
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, NULL);
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

void DrawCoordinateAxes() {
	GLfloat point[4][3] = {
		{0.0,1.0,0.0},
		{0.0,-1.0,0.0},
		{1.0,0.0,0.0},
		{-1.0,0.0,0.0}
	};
	GLfloat color[4][3] = {
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f,
		1.0f,0.0f,0.0f
	};

	glBindVertexArray(VAO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glm::mat4 TR = glm::mat4(1.0f);
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glDrawArrays(GL_LINES, 0, 4);

}
GLvoid InitValue() {

}
