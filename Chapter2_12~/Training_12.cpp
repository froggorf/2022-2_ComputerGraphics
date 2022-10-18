/*
1~6 -> 육면체 각 면 그리기
7~0 -> 사면체 각 면 그리기
a/b/c -> 육면체 반대방향 면 그리기
e/f/g -> 사면체 반대방향 면 그리기
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
GLuint VAO_tetra, VBO_tetra[2], VBO_tetra_index;
bool print_cube[6]={true,true,true,true,true,true};
bool print_tetra[4] = { false,false,false,false };
void DrawCoordinateAxes();
void DrawCube();
void DrawTetra();
void test();
GLfloat cube_shape[8][3] = {
	-0.25,0.25,-0.25,
	-0.25,0.25,0.25,
	0.25,0.25,0.25,
	0.25,0.25,-0.25,
	-0.25,-0.25,0.25,
	0.25,-0.25,0.25,
	0.25,-0.25,-0.25,
	-0.25,-0.25,-0.25
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
GLfloat tetra_shape[4][3] = {
	0.0,0.25,0.25,
	-0.25,-0.25,-0.25,
	0.25,-0.25,-0.25,
	0.0,-0.25,0.25
};
unsigned int tetra_idx[4][3] = {
	0,2,1,
	0,1,3,
	0,3,2,
	1,2,3
};
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
	glGenVertexArrays(1, &VAO_tetra);
	glGenBuffers(2, VBO_tetra);
	glGenBuffers(1, &VBO_tetra_index);

	InitShader();
	InitBuffer();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
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
	DrawCube();
	DrawTetra();
	

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
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
		for (int i = 0; i < 4; ++i) print_tetra[i] = false;
		print_cube[key - '1'] = 1 - print_cube[key - '1'];
		break;
	case '7':
	case '8':
	case '9':
	case '0':
		for (int i = 0; i < 6; ++i) print_cube[i] = false;
		if (key != '0')
			print_tetra[key - '7'] = 1 - print_tetra[key - '7'];
		else
			print_tetra[3] = 1 - print_tetra[3];
		break;
	case 'a':
	case 'b':
	case 'c':
		for (int i = 0; i < 4; ++i) print_tetra[i] = false;
		for (int i = 0; i < 6; ++i) {
			print_cube[i] = false;
		}
		if (key == 'a') print_cube[0] = print_cube[5] = true;
		else if(key=='b')print_cube[1] = print_cube[3] = true;
		else if (key == 'c')print_cube[2] = print_cube[4] = true;
		break;
	case 'e':
	case 'f':
	case 'g':
		for (int i = 0; i < 6; ++i) print_cube[i] = false;
		for (int i = 0; i < 4; ++i) print_tetra[i] = false;
		print_tetra[3] = true;
		if (key == 'e') print_tetra[0] = true;
		if (key == 'f') print_tetra[1] = true;
		if (key == 'g') print_tetra[2] = true;
		break;
	}

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
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color), cube_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_shape), cube_shape, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_idx), cube_idx, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(-10.0f), glm::vec3(0.0, 1.0, 0.0));
	TR = Ry * Rx;
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int i = 0; i < 6; ++i) {
		if (print_cube[i]) {
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)((i * 6) * sizeof(unsigned int)));
		}
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	
}

void DrawTetra() {
	glBindVertexArray(VAO_tetra);
	GLfloat tetra_color[4][3] = {
		1.0f,1.0f,1.0f,
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tetra[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tetra_color), tetra_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_tetra[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tetra_shape), tetra_shape, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_tetra_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetra_idx), tetra_idx, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(10.0f), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(-10.0f), glm::vec3(0.0, 1.0, 0.0));
	TR = Ry * Rx;
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	std::cout << print_tetra[0] << " " << print_tetra[1] << " " << print_tetra[2] << " " << print_tetra[3] << std::endl;
	for (int i = 0; i < 4; ++i) {
		if (print_tetra[i]) {
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)((i * 3) * sizeof(unsigned int)));
		}
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
