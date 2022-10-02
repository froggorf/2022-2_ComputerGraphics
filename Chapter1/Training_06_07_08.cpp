//6~8번 실습에 한해서는 왼손 좌표계를 사용했으므로 참고해서 코딩하자. openGL은 오른손 좌표계인것도 기억하자.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>
#define WIDTH 800
#define HEIGHT 600
#define SizeCount 3
#define PlusSize 0.03
#define MaxTriNum 4		
#define TimerSpeed 30	
#define MaxDeltaSpeed 0.05
#define MinDeltaSpeed 0.015
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

GLboolean flag_line = false;
GLfloat plus_size = 0.1;
GLfloat rect_size = 0.4;
void ChangePlusSize();
std::random_device rd;
std::uniform_real_distribution<GLfloat> urd(0.0f, 1.0f);
std::uniform_real_distribution<GLfloat> Delta(MinDeltaSpeed, MaxDeltaSpeed);
std::uniform_int_distribution<int> uid(0, 1);

int select_training_num = 6;			
void Init_first_tri();
void TriMove(int value);
GLboolean timer_off = false;
GLboolean flag_timer = false;
GLboolean flag_outsideBounce = true;
GLboolean flag_insideBounce = true;
enum DIRECTION { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, INSIDE = 4 };

class myTriangle {
public:
	GLfloat shape[3][3];
	GLfloat x, y;
	GLfloat color[3][3] = { {urd(rd) ,urd(rd),urd(rd)},{color[0][0],color[0][1],color[0][2]},{color[0][0],color[0][1],color[0][2]} };
	GLfloat dx= 0, dy= 0;	
	GLfloat size;
	int direction = UP;
	myTriangle operator=(myTriangle other) {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				shape[i][j] = other.shape[i][j];
				color[i][j] = other.color[i][j];
			}
		}
		x = other.x;	y = other.y;
		dx = other.dx;	dy = other.dy;
		size = other.size;
		return *this;
	}
	void Init_Shape() {
		for (int i = 0; i < 3; ++i) {
			shape[i][0] = x;
			shape[i][1] = y;
			shape[i][2] = 0;
		}
		switch (direction) {
		case UP:
			shape[0][1] += size * 2;
			shape[1][0] += size;
			shape[1][1] -= size;
			shape[2][0] -= size;
			shape[2][1] -= size;
			break;
		case DOWN:
			shape[0][0] -= size;
			shape[0][1] += size;
			shape[1][0] += size;
			shape[1][1] += size;
			shape[2][1] -= size * 2;
			break;
		case LEFT:
			shape[0][0] += size;
			shape[0][1] += size;
			shape[1][0] += size;
			shape[1][1] -= size;
			shape[2][0] -= size * 2;
			break;
		case RIGHT:
			shape[0][0] -= size;
			shape[0][1] += size;
			shape[1][0] += size * 2;
			shape[2][0] -= size;
			shape[2][1] -= size;
			break;
		}
	}
	void Init(float gl_x, float gl_y,GLfloat get_size ,int get_direct) {
		x = gl_x; y = gl_y;
		size = get_size;
		direction = get_direct;
		Init_Shape();
		for (int i = 0; i < 3; ++i) {
			color[0][i] = urd(rd);
			color[1][i] = color[0][i];
			color[2][i] = color[0][i];
		}
	}
	void Init_Color(GLfloat r, GLfloat g, GLfloat b) {
		for (int i = 0; i < 3; ++i) {
			color[i][0] = r;
			color[i][1] = g;
			color[i][2] = b;
		}
	}
	
};

myTriangle tri[MaxTriNum];
GLuint VAO[MaxTriNum], VBO_shape[MaxTriNum], VBO_color[MaxTriNum];
GLuint VAO_rect, VBO_rect_shape, VBO_rect_color;
void CheckBounce(myTriangle& tri);
void CheckInside(myTriangle& tri);
void CheckZigzag(myTriangle& tri);
void main(int argc, char** argv)
{
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
	glGenVertexArrays(MaxTriNum, VAO);
	glGenBuffers(MaxTriNum, VBO_shape);
	glGenBuffers(MaxTriNum, VBO_color);
	glGenBuffers(1, &VAO_rect);
	glGenBuffers(1, &VBO_rect_shape);
	glGenBuffers(1, &VBO_rect_color);
	InitBuffer();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	Init_first_tri();


	std::cout << "현재 " << select_training_num << "번 실행중입니다.\n";
	glutMainLoop(); // 이벤트 처리 시작 
}


GLvoid drawScene() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < MaxTriNum; ++i) {
		tri[i].Init_Shape();
	}
	InitBuffer();


	for (int i = 0; i < MaxTriNum; ++i) {
		glBindVertexArray(VAO[i]);
		if (!flag_line) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glLineWidth(5.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	//-------------------------
	if (select_training_num == 8) {
		GLfloat rect_shape[4][3] = {
			{rect_size,rect_size,0.0},
			{-rect_size,rect_size,0.0},
			{-rect_size,-rect_size,0.0},
			{rect_size,-rect_size,0.0}
		};
		GLfloat rect_color[4][3] = {
			{0.0,0.0,0.0},
			{0.0,0.0,0.0},
			{0.0,0.0,0.0},
			{0.0,0.0,0.0}
		};
		glBindVertexArray(VAO_rect);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_rect_shape);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rect_shape), rect_shape, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_rect_color);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rect_color), rect_color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}
	if (select_training_num == 8) {
		glBindVertexArray(VAO_rect);
		glLineWidth(5.0);
		glDrawArrays(GL_LINE_LOOP, 0, 4);
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
	case 'T':
	case 't':
		if (select_training_num == 6) {
			printf("6번은 타이머를 실행할 수 없습니다.\n");
			break;
		} 
		if (flag_timer) break;
		flag_timer = true;
		if (select_training_num == 7) {
			for (int i = 0; i < MaxTriNum; ++i) {
				tri[i].dx = Delta(rd);
				tri[i].dy = Delta(rd);
				if (uid(rd) == 0) tri[i].dx *= -1;
				if (uid(rd) == 0) tri[i].dy *= -1;		
			}
		}
		else if (select_training_num == 8) {
			for (int i = 0; i < 2; ++i) {
				tri[i].dx = Delta(rd);
				tri[i].dy = Delta(rd);
				if (uid(rd) == 0) tri[i].dx *= -1;
				if (uid(rd) == 0) tri[i].dy *= -1;		
			}
			GLfloat temp = Delta(rd);
			tri[2].dx = temp;	tri[2].dy = 0;
			tri[3].dx = -temp;	tri[3].dy = 0;
		}
		glutTimerFunc(TimerSpeed, TriMove, select_training_num);
		break;
	case 'S':
	case 's':
		if (flag_timer) {
			timer_off = true;
		}
		else {
			printf("아직 타이머를 실행하지 않아 타이머를 종료할 수 없습니다\n");
			timer_off = false;
		}
		
		break;
	case '6':
		printf("6번 실행\n");
		if(flag_timer) timer_off = true;
		select_training_num = 6;
		plus_size = 0.1;
		Init_first_tri();
		
		break;
	case '7':
		printf("7번 실행\n");
		if (flag_timer) timer_off = true;
		select_training_num = 7;
		plus_size = 0.1;
		Init_first_tri();
		break;
	case '8':
		if (MaxTriNum <= 2) {
			printf("도형 최대 갯수가 2 이하일 경우 실행할 수 없습니다.\n");
			break;
		}
		printf("8번 실행\n");
		if (flag_timer)timer_off = true;
		select_training_num = 8;
		plus_size = 0.1;
		Init_first_tri();
		break;
	case 'O':
	case 'o':
		flag_outsideBounce = 1 - flag_outsideBounce;
		break;
	case 'I':
	case 'i':
		flag_insideBounce = 1 - flag_insideBounce;
		break;
	}

	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	double gl_x, gl_y;
	WindowCursorToGl(x, y, gl_x, gl_y);

	if (select_training_num == 6) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			for (int i = 0; i < MaxTriNum - 1; ++i) {
				tri[i] = tri[i + 1];
			}
			tri[MaxTriNum - 1].Init(gl_x, gl_y,plus_size,UP);
			ChangePlusSize();
		}
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
	for (int i = 0; i < MaxTriNum; ++i) {
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_shape[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri[i].shape), tri[i].shape, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_color[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tri[i].color), tri[i].color, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
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
	if (select_training_num == 6||select_training_num==7) {
		tri[0].Init(0.5, 0.5, plus_size, UP);
		tri[1].Init(-0.5, 0.5, plus_size, UP);
		tri[2].Init(-0.5, -0.5, plus_size, UP);
		tri[3].Init(0.5, -0.5, plus_size, UP);
		for (int i = 4; i < MaxTriNum; ++i) {
			tri[i].Init(urd(rd), urd(rd), plus_size, UP);
		}
	}
	else if (select_training_num == 8) {
		tri[0].Init(0.7, 0.7, plus_size, UP);
		tri[1].Init(-0.7, -0.7, plus_size, UP);
		tri[2].Init(rect_size-plus_size, rect_size-plus_size, plus_size, DOWN);
		tri[3].Init(-rect_size+plus_size,-rect_size+plus_size,plus_size, UP);
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
		plus_size += PlusSize;
	}
	else if (count > -SizeCount) {
		plus_size -= PlusSize;
	}
	--count;
	if (count == -SizeCount) {
		count = SizeCount;
	}

}

void TriMove(int value) {
	if (timer_off) {
		flag_timer = false;
		timer_off = false;
		return;
	}

	if (value == 7) {
		for (int i = 0; i < MaxTriNum; ++i) {
			tri[i].x += tri[i].dx;
			tri[i].y += tri[i].dy;
			CheckBounce(tri[i]);
		}
	}
	else if (value == 8) {
		if (flag_outsideBounce) {
			for (int i = 0; i < 2; ++i) {
				CheckInside(tri[i]);
				CheckBounce(tri[i]);
			}
		}
		if (flag_insideBounce) {
			for (int i = 2; i < 4; ++i) {
				CheckZigzag(tri[i]);
			}
		}
	}

	

	glutPostRedisplay();
	glutTimerFunc(TimerSpeed, TriMove, value);
}

void CheckBounce(myTriangle& tri) {
	tri.Init_Shape();
	GLboolean over_up = false, over_down = false, over_left = false, over_right = false;
	switch (tri.direction) {
	case UP:
		if (tri.shape[0][1] > 1) over_up = true;
		if (tri.shape[2][1] < -1) over_down = true;
		if (tri.shape[2][0] < -1) over_left = true;
		if (tri.shape[1][0] > 1) over_right = true;
		break;
	case DOWN:
		if (tri.shape[0][1] > 1) over_up = true;
		if (tri.shape[2][1] < -1) over_down = true;
		if (tri.shape[0][0] < -1)over_left = true;
		if (tri.shape[1][0] > 1)over_right = true;
		break;
	case RIGHT:
		if (tri.shape[0][1] > 1) over_up = true;
		if (tri.shape[2][1] < -1)over_down = true;
		if (tri.shape[0][0] < -1)over_left = true;
		if (tri.shape[1][0] > 1)over_right = true;
		break;
	case LEFT:
		if (tri.shape[0][1] > 1)over_up = true;
		if (tri.shape[1][1] < -1)over_down = true;
		if (tri.shape[2][0] < -1)over_left = true;
		if (tri.shape[0][0] > 1)over_right = true;
		break;
	}

	if (over_up) {
		tri.direction = DOWN;
		tri.Init_Shape();
		if (tri.shape[0][1] > 1) {
			tri.y -= (tri.shape[0][1] - 1);
		}
		tri.dy *= -1;
	}

	if (over_down) {
		tri.direction = UP;
		tri.Init_Shape();
		if (tri.shape[1][1] < -1) {
			tri.y += (-1 - tri.shape[1][1]);
		}
		tri.dy *= -1;
	}

	if (over_left) {
		tri.direction = RIGHT;
		tri.Init_Shape();
		if (tri.shape[0][0] < -1) {
			tri.x += (-1 - tri.shape[0][0]);
		}
		tri.dx *= -1;
	}

	if (over_right) {
		tri.direction = LEFT;
		tri.Init_Shape();
		if (tri.shape[0][0] > 1) {
			tri.x -= (tri.shape[0][0] - 1);
		}
		tri.dx *= -1;
	}
}

GLboolean myPtInRect(GLfloat x, GLfloat y, GLfloat left, GLfloat top, GLfloat right, GLfloat bottom) {
	if (left < x && x < right) {
		if (bottom < y && y < top) {
			return true;
		}
	}
	return false;
}
void CheckInside(myTriangle& tri) {
	//일단 x축으로 이동을 보낸다음에
	tri.x += tri.dx;
	tri.Init_Shape();

	//충돌했을시를 체크한다
	if (tri.dx > 0) {
		for (int i = 0; i < 3; ++i) {
			if (myPtInRect(tri.shape[i][0], tri.shape[i][1], -rect_size, rect_size, rect_size, -rect_size)) {
				tri.x = -rect_size - tri.size;
				tri.direction = LEFT;
				tri.dx *= -1;
				tri.Init_Shape();
				return;
			}
		}
	}
	else if (tri.dx < 0) {
		for (int i = 0; i < 3; ++i) {
			if (myPtInRect(tri.shape[i][0], tri.shape[i][1], -rect_size, rect_size, rect_size, -rect_size)) {
				tri.x = rect_size + tri.size;
				tri.direction = RIGHT;
				tri.dx *= -1;
				tri.Init_Shape();
				return;
			}
		}
	}

	//그러고서 y축을 이동시켜 본다음에
	tri.y += tri.dy;
	tri.Init_Shape();

	//충돌했을시를 체크한다.
	if (tri.dy>0) {
		for (int i = 0; i < 3; ++i) {
			if (myPtInRect(tri.shape[i][0], tri.shape[i][1], -rect_size, rect_size, rect_size, -rect_size)) {
				tri.y = -rect_size - tri.size;
				tri.direction = DOWN;
				tri.dy *= -1;
				tri.Init_Shape();
				return;
			}
		}
	}
	else if (tri.dy < 0) {
		for (int i = 0; i < 3; ++i) {
			if (myPtInRect(tri.shape[i][0], tri.shape[i][1], -rect_size, rect_size, rect_size, -rect_size)) {
				tri.y = rect_size + tri.size;
				tri.direction = UP;
				tri.dy *= -1;
				tri.Init_Shape();
				return;
			}
		}
	}
}

void CheckZigzag(myTriangle& tri) {
	tri.x += tri.dx;
	tri.Init_Shape();

	for (int i = 0; i < 3; ++i) {
		{//왼쪽 충돌 체크
			if (tri.direction == UP) {//밑에 삼각형
				if (tri.shape[2][0] < -rect_size) {
					tri.x = -rect_size + tri.size;
					tri.dx *= -1;
					tri.Init_Shape();
					tri.Init_Color(urd(rd), urd(rd), urd(rd));
				}
			}
			else if (tri.direction == DOWN) {	//위에 삼각형
				if (tri.shape[0][0] < -rect_size) {
					tri.x = -rect_size + tri.size;
					tri.dx *= -1;
					tri.Init_Shape();
					tri.Init_Color(urd(rd), urd(rd), urd(rd));
				}
			}
		}

		{//오른쪽 충돌 체크
			if (tri.direction == UP) {//밑에 삼각형
				if (tri.shape[1][0] > rect_size) {
					tri.x = rect_size - tri.size;
					tri.dx *= -1;
					tri.Init_Shape();
					tri.Init_Color(urd(rd), urd(rd), urd(rd));
				}
			}
			else if (tri.direction == DOWN) {	//위에 삼각형 (같긴 하지만 혹시모를 버그 수정을 위해 나눴음)
				if (tri.shape[1][0] > rect_size) {
					tri.x = rect_size - tri.size;
					tri.dx *= -1;
					tri.Init_Shape();
					tri.Init_Color(urd(rd), urd(rd), urd(rd));
				}
			}
		}
		
		
	}
}