#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 1024
#define HEIGHT 960
#define TimerSpeed 50
#define ShapeChangeStep 30	//도형 변환하는데 프레임

std::random_device rd;
std::uniform_real_distribution<GLfloat> urd_color(0.0, 1.0);

char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid WindowCursorToGl(int w_x, int w_y, GLfloat& gl_x, GLfloat& gl_y);

void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitBuffer();
GLvoid InitShapePointColor();
GLvoid DrawLine();
GLvoid DrawShape_Line();
GLvoid DrawShape_Tri();
GLvoid DrawShape_Rect();
GLvoid DrawShape_Penta();
GLvoid InitShader();
GLvoid ShapeTimer(int value);
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
GLuint fence_VAO, fence_point_VBO, fence_color_VBO;
GLuint line_VAO, line_point_VBO, line_color_VBO;
GLfloat line_shape[3][3], line_color[3][3];
GLuint tri_VAO, tri_point_VBO, tri_color_VBO;
GLfloat tri_shape[4][3], tri_color[4][3];
GLuint rect_VAO, rect_point_VBO, rect_color_VBO;
GLfloat rect_shape[5][3], rect_color[5][3];
GLuint penta_VAO, penta_point_VBO, penta_color_VBO;
GLfloat penta_shape[5][3], penta_color[5][3];

GLboolean flag_timer = false, timer_off = false;
int shapeStep = 0;
GLboolean finish_change = false;
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

	

	InitShapePointColor();

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
	DrawLine();
	DrawShape_Line();
	DrawShape_Tri();
	DrawShape_Rect();
	DrawShape_Penta();
	InitBuffer();



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
	case 'T':
	case 't':
		if (flag_timer) {
			printf("이미 타이머를 실행중입니다.\n");
			break;
		}
		
		flag_timer = true;
		glutTimerFunc(TimerSpeed, ShapeTimer, finish_change);
		break;
	case 'S':
	case 's':
		if (flag_timer) {
			timer_off = true;
			InitShapePointColor();
			shapeStep = 0;
			finish_change = 0;
			printf("타이머를 종료하였습니다.\n");
			break;
		}
		printf("타이머를 실행중이지 않아 종료할 수 없습니다.\n");
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
GLvoid ShapeTimer(int value) {
	if (timer_off) {
		timer_off = false;
		flag_timer = false;
		return;
	}

	if (value == 0) {	//도형 변경 정방향
		{//선 -> 삼각형
			line_shape[0][1] += 0.3 / ShapeChangeStep;
			line_shape[2][1] -= 0.3 / ShapeChangeStep * 2;
		}
		{//삼각형 -> 사각형
			tri_shape[1][0] -= 0.3 / ShapeChangeStep;
			tri_shape[3][0] += 0.3 / ShapeChangeStep;
		}
		{//사각형 -> 오각형
			rect_shape[1][1] += 0.1 / ShapeChangeStep;
			rect_shape[0][0] -= 0.1 / ShapeChangeStep;
			rect_shape[0][1] -= 0.2 / ShapeChangeStep;
			rect_shape[3][0] += 0.1 / ShapeChangeStep;
			rect_shape[3][1] -= 0.2 / ShapeChangeStep;
			rect_shape[2][0] += 0.1 / ShapeChangeStep;
			rect_shape[2][1] -= 0.1 / ShapeChangeStep;
			rect_shape[4][0] -= 0.1 / ShapeChangeStep;
			rect_shape[4][1] -= 0.1 / ShapeChangeStep;
		}
		{
			penta_shape[0][0] -= 0.4 / ShapeChangeStep;
			penta_shape[0][1] -= 0.1 / ShapeChangeStep;
			penta_shape[1][1] -= 0.4 / ShapeChangeStep;
			penta_shape[2][0] -= 0.2 / ShapeChangeStep;
			penta_shape[2][1] += 0.4 / ShapeChangeStep;
			penta_shape[3][0] += 0.4 / ShapeChangeStep;
			penta_shape[3][1] -= 0.1 / ShapeChangeStep;
			penta_shape[4][0] += 0.2 / ShapeChangeStep;
			penta_shape[4][1] += 0.4 / ShapeChangeStep;
		}
		if (shapeStep == ShapeChangeStep-1) {
			finish_change = true;
			timer_off = true;
			printf("정방향 완료\n");
		}
		++shapeStep;
	}
	else if (value == 1) {		//도형 변경 역방향
		{//선 -> 삼각형
			line_shape[0][1] += -0.3 / ShapeChangeStep;
			line_shape[2][1] -= -0.3 / ShapeChangeStep * 2;
		}
		{//삼각형->사각형
			tri_shape[1][0] += 0.3 / ShapeChangeStep;
			tri_shape[3][0] -= 0.3 / ShapeChangeStep;
		}
		{//사각형 -> 오각형
			rect_shape[1][1] -= 0.1 / ShapeChangeStep;
			rect_shape[0][0] += 0.1 / ShapeChangeStep;
			rect_shape[0][1] += 0.2 / ShapeChangeStep;
			rect_shape[3][0] -= 0.1 / ShapeChangeStep;
			rect_shape[3][1] += 0.2 / ShapeChangeStep;
			rect_shape[2][0] -= 0.1 / ShapeChangeStep;
			rect_shape[2][1] += 0.1 / ShapeChangeStep;
			rect_shape[4][0] += 0.1 / ShapeChangeStep;
			rect_shape[4][1] += 0.1 / ShapeChangeStep;
		}
		{
			penta_shape[0][0] += 0.4 / ShapeChangeStep;
			penta_shape[0][1] += 0.1 / ShapeChangeStep;
			penta_shape[1][1] += 0.4 / ShapeChangeStep;
			penta_shape[2][0] += 0.2 / ShapeChangeStep;
			penta_shape[2][1] -= 0.4 / ShapeChangeStep;
			penta_shape[3][0] -= 0.4 / ShapeChangeStep;
			penta_shape[3][1] += 0.1 / ShapeChangeStep;
			penta_shape[4][0] -= 0.2 / ShapeChangeStep;
			penta_shape[4][1] -= 0.4 / ShapeChangeStep;
		}
		if (shapeStep == 1) {
			finish_change = false;
			timer_off = true;
		}
		shapeStep--;
	}

	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, ShapeTimer, value);
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
	{//칸막이
		glGenVertexArrays(1, &fence_VAO);
		glGenBuffers(1, &fence_point_VBO);
		glGenBuffers(1, &fence_color_VBO);
	}
	
	{//선->삼각형
		glGenVertexArrays(1, &line_VAO);
		glGenBuffers(1, &line_point_VBO);
		glGenBuffers(1, &line_color_VBO);
	}
	
	{//삼각형->네모
		glGenVertexArrays(1, &tri_VAO);
		glGenBuffers(1, &tri_point_VBO);
		glGenBuffers(1, &tri_color_VBO);
	}
	
	{//사각형->오각형
		glGenVertexArrays(1, &rect_VAO);
		glGenBuffers(1, &rect_point_VBO);
		glGenBuffers(1, &rect_color_VBO);
	}

	{//오각형 -> 점
		glGenVertexArrays(1, &penta_VAO);
		glGenBuffers(1, &penta_point_VBO);
		glGenBuffers(1, &penta_color_VBO);
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

GLvoid WindowCursorToGl(int w_x, int w_y, GLfloat& gl_x, GLfloat& gl_y) {
	double w = (double)glutGet(GLUT_WINDOW_WIDTH) / 2;
	double h = (double)glutGet(GLUT_WINDOW_HEIGHT) / 2;
	gl_x = (w_x - w) / w;
	gl_y = ((w_y - h) / h) * -1;
}

GLvoid DrawLine() {
	glBindVertexArray(fence_VAO);

	GLfloat fence_shape[4][3] = {
		{0.0,1.0,0.0},
		{0.0,-1.0,0.0},
		{-1.0,0.0,0.0},
		{1.0,0.0,0.0}
	};
	glBindBuffer(GL_ARRAY_BUFFER, fence_point_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fence_shape), fence_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	GLfloat fence_color[4][3] = {
		{0.0,0.0,0.0},
		{0.0,0.0,0.0},
		{0.0,0.0,0.0},
		{0.0,0.0,0.0}
	};
	glBindBuffer(GL_ARRAY_BUFFER, fence_color_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fence_color), fence_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glLineWidth(1.0);
	glDrawArrays(GL_LINES, 0, 4);

}

GLvoid DrawShape_Line() {
	glBindVertexArray(line_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, line_point_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_shape), line_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, line_color_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_color), line_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	if (line_shape[0][1] == 0.5) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.0);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLvoid DrawShape_Tri() {
	glBindVertexArray(tri_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, tri_point_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_shape), tri_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, tri_color_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_color), tri_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

GLvoid DrawShape_Rect() {
	glBindVertexArray(rect_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, rect_point_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_shape), rect_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, rect_color_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_color), rect_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
}

GLvoid DrawShape_Penta() {
	glBindVertexArray(penta_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, penta_point_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(penta_shape), penta_shape, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, penta_color_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(penta_color), penta_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	if (finish_change&&shapeStep==30) {
		glPointSize(10.0);
		glDrawArrays(GL_POINTS, 0, 1);
		glPointSize(1.0);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
	}
	
}

GLvoid InitShapePointColor() {
	{//선
		line_shape[0][0] = -0.5;	line_shape[0][1] = 0.5; line_shape[0][2] = 0.0;
		line_shape[1][0] = -0.8;	line_shape[1][1] = 0.2; line_shape[1][2] = 0.0;
		line_shape[2][0] = -0.2;	line_shape[2][1] = 0.8; line_shape[2][2] = 0.0;
		for (int i = 0; i < 3; ++i) {
			GLfloat temp = urd_color(rd);
			line_color[0][i] = temp;
			line_color[1][i] = temp;
			line_color[2][i] = temp;
		}
	}
	
	{//
		tri_shape[0][0] = 0.2;	tri_shape[0][1] = 0.2; tri_shape[0][2] = 0.0;
		tri_shape[1][0] = 0.5;	tri_shape[1][1] = 0.8; tri_shape[1][2] = 0.0;
		tri_shape[2][0] = 0.8;	tri_shape[2][1] = 0.2; tri_shape[2][2] = 0.0;
		tri_shape[3][0] = 0.5;	tri_shape[3][1] = 0.8; tri_shape[3][2] = 0.0;
		for (int i = 0; i < 3; ++i) {
			GLfloat temp = urd_color(rd);
			tri_color[0][i] = temp;
			tri_color[1][i] = temp;
			tri_color[2][i] = temp;
			tri_color[3][i] = temp;
		}
	}

	{
		rect_shape[0][0] = -0.8;	rect_shape[0][1] = -0.2; rect_shape[0][2] = 0.0;
		rect_shape[1][0] = -0.5;	rect_shape[1][1] = -0.2; rect_shape[1][2] = 0.0;
		rect_shape[2][0] = -0.8;	rect_shape[2][1] = -0.8; rect_shape[2][2] = 0.0;
		rect_shape[3][0] = -0.2;	rect_shape[3][1] = -0.2; rect_shape[3][2] = 0.0;
		rect_shape[4][0] = -0.2;	rect_shape[4][1] = -0.8; rect_shape[4][2] = 0.0;
		for (int i = 0; i < 3; ++i) {
			GLfloat temp = urd_color(rd);
			rect_color[0][i] = temp;
			rect_color[1][i] = temp;
			rect_color[2][i] = temp;
			rect_color[3][i] = temp;
			rect_color[4][i] = temp;
		}
	}

	{
		penta_shape[0][0] = 0.9;	penta_shape[0][1] = -0.4; penta_shape[0][2] = 0.0;
		penta_shape[1][0] = 0.5;	penta_shape[1][1] = -0.1; penta_shape[1][2] = 0.0;
		penta_shape[2][0] = 0.7;	penta_shape[2][1] = -0.9; penta_shape[2][2] = 0.0;
		penta_shape[3][0] = 0.1;	penta_shape[3][1] = -0.4; penta_shape[3][2] = 0.0;
		penta_shape[4][0] = 0.3;	penta_shape[4][1] = -0.9; penta_shape[4][2] = 0.0;
		for (int i = 0; i < 3; ++i) {
			GLfloat temp = urd_color(rd);
			penta_color[0][i] = temp;
			penta_color[1][i] = temp;
			penta_color[2][i] = temp;
			penta_color[3][i] = temp;
			penta_color[4][i] = temp;
		}
	}
}