#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define SizeCount 5
#define MaxTriNum 4
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid WindowCursorToGl(int w_x, int w_y, double& gl_x, double& gl_y);

void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitBuffer();
GLvoid InitShader();
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
GLuint VAO[MaxTriNum], VBO_shape[MaxTriNum], VBO_color[MaxTriNum];
GLboolean flag_line = false;
GLfloat plus_size = 0.2;
void ChangePlusSize();
std::random_device rd;
std::uniform_real_distribution<GLfloat> urd(0.0f, 1.0f);

class myTriangle {
public:
	GLfloat shape[3][3];
	GLfloat color[3][3] = { {urd(rd) ,urd(rd),urd(rd)},{color[0][0],color[0][1],color[0][2]},{color[0][0],color[0][1],color[0][2]} };

	myTriangle operator=(myTriangle other) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				shape[i][j] = other.shape[i][j];
				color[i][j] = other.color[i][j];
			}
		}
		return *this;
	}
	void Init_Shape(float g_shape[3][3]) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				shape[i][j] = g_shape[i][j];
			}
		}
	}
	void Init(float gl_x, float gl_y) {
		float temp[3][3] = { {gl_x,gl_y + plus_size,0.0},{gl_x + plus_size,gl_y - plus_size ,0.0},{gl_x - plus_size,gl_y - plus_size,0.0} };
		Init_Shape(temp);
		for (int i = 0; i < 3; ++i) {
			color[0][i] = urd(rd);
			color[1][i] = color[0][i];
			color[2][i] = color[0][i];
		}

	}

};

myTriangle tri[MaxTriNum];
void Init_first_tri();
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

	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	Init_first_tri();

	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	InitBuffer();
	for (int i = 0; i < MaxTriNum; ++i) {
		glBindVertexArray(VAO[i]);
		if (!flag_line)
			glDrawArrays(GL_TRIANGLES, 0, 3);
		else {
			glLineWidth(5.0);
			glDrawArrays(GL_LINE_LOOP, 0, 3);
		}
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
	case 'a':
	case 'A':
		flag_line = 1 - flag_line;

		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double gl_x, gl_y;
	WindowCursorToGl(x, y, gl_x, gl_y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//이전것들 사라지고 배열 인덱스 옮기기
		for (int i = 0; i < MaxTriNum - 1; ++i) {
			tri[i] = tri[i + 1];
		}
		std::cout << gl_x << "," << gl_y << std::endl;
		tri[MaxTriNum - 1].Init(gl_x, gl_y);
		ChangePlusSize();
	}


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
	glGenVertexArrays(MaxTriNum, VAO);
	glGenBuffers(MaxTriNum, VBO_shape);
	glGenBuffers(MaxTriNum, VBO_color);

	for (int i = 0; i < MaxTriNum; ++i) {
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_shape[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri[0].shape), tri[i].shape, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_color[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri[i].color), tri[i].color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
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


void Init_first_tri() {
	GLfloat temp1[3][3] = { {0.5,0.5 + 0.2,0.0},{ 0.5 + 0.2 ,0.5 - 0.2,0.0 } ,{ 0.5 - 0.2,0.5 - 0.2,0.0 } };
	tri[0].Init_Shape(temp1);
	GLfloat temp2[3][3] = { {-0.5,0.5 + 0.2,0.0},{-0.5 + 0.2,0.5 - 0.2,0.0},{-0.5 - 0.2,0.5 - 0.2,0.0} };
	tri[1].Init_Shape(temp2);
	GLfloat temp3[3][3] = { {-0.5,-0.5 + 0.2,0.0},{-0.5 + 0.2,-0.5 - 0.2,0.0},{-0.5 - 0.2,-0.5 - 0.2,0.0} };
	tri[2].Init_Shape(temp3);
	GLfloat temp4[3][3] = { {0.5,-0.5 + 0.2,0.0},{0.5 + 0.2,-0.5 - 0.2,0.0},{0.5 - 0.2,-0.5 - 0.2,0.0} };
	tri[3].Init_Shape(temp4);

	for (int i = 0; i < MaxTriNum; ++i) {
		std::cout << i << "번쨰: " << tri[i].color[0] << "/" << tri[i].color[1] << "/" << tri[i].color[2] << std::endl;
	}
}

GLvoid WindowCursorToGl(int w_x, int w_y, double& gl_x, double& gl_y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	gl_x = (w_x - w) / w;
	gl_y = ((w_y - h) / h) * -1;
}

void ChangePlusSize() {
	static int count = SizeCount;
	if (count > 0) {
		plus_size += 0.05;
	}
	else if (count > -SizeCount) {
		plus_size -= 0.05;
	}
	--count;
	if (count == -SizeCount) {
		count = SizeCount;
	}

}