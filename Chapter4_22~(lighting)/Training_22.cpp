/*
---------단축키 설명---------

*/

#define _CRT_SECURE_NO_WARNINGS
//헤더 파일 목록
#include <iostream>
#include <gl/glew.h> 
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

//define 목록
#define WIDTH 1600
#define HEIGHT 1200

#define X 0
#define Y 1
#define Z 2

#define R 0
#define G 1
#define B 2

#define POS 0
#define COLOR 1
#define INDEX 2


//월드관련 define
#define ObjectSize 20
#define WorldSize 200		//x: -100~100 / y: -100~100 / z: 0 ~ 200

//enum 관련

//클래스 관련
//class MyCubeFor16 {
//public:
//	GLfloat pos[8][3];
//	GLfloat color[8][3];
//
//	GLfloat move_face[6][3];
//};

//glut 관련 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid SpecialKeyboard(int, int, int);

//셰이더 관련 함수 및 변수
char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitShader();
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;

//VAO, VBO 관련 함수 및 변수

GLvoid InitBuffer();

//카메라 관련 함수 및 변수
glm::vec3 cameraPos;
glm::vec3 cameraDirection;
glm::vec3 cameraUp;
GLboolean flag_perspective_projection = true;

//내가 만든 함수 와 변수
GLvoid InitValue();
GLvoid SetTransformMatrix();
GLboolean flag_cull_face = false;
GLboolean flag_depth_test = false;
GLboolean flag_draw_line = false;
GLvoid ChangeDegree(GLfloat);

//축 관련 함수 와 변수
GLvoid DrawAxes();
GLfloat cube_vertices[] = {			//cube_pos와 cube_index 를 안쓰고 vertices를 사용
	-ObjectSize,	ObjectSize,		-ObjectSize,	ObjectSize,		ObjectSize,		-ObjectSize,	ObjectSize, ObjectSize, ObjectSize, 
	ObjectSize,		ObjectSize,		ObjectSize,		-ObjectSize,	ObjectSize,		ObjectSize,		-ObjectSize, ObjectSize, -ObjectSize,
	-ObjectSize,	-ObjectSize,	ObjectSize,		ObjectSize,		-ObjectSize,	ObjectSize,		ObjectSize, ObjectSize, ObjectSize, 
	ObjectSize,		ObjectSize,		ObjectSize,		-ObjectSize,	ObjectSize,		ObjectSize,		-ObjectSize, -ObjectSize,ObjectSize, 
	ObjectSize,		ObjectSize,		ObjectSize,		ObjectSize,		ObjectSize,		-ObjectSize,	ObjectSize, -ObjectSize, -ObjectSize, 
	ObjectSize,		-ObjectSize,	-ObjectSize,	ObjectSize,		-ObjectSize,	ObjectSize,		ObjectSize, ObjectSize, ObjectSize, 
	-ObjectSize,	-ObjectSize,	-ObjectSize,	ObjectSize,		-ObjectSize,	-ObjectSize,	ObjectSize, ObjectSize, -ObjectSize, 
	ObjectSize,		ObjectSize,		-ObjectSize,	-ObjectSize,	ObjectSize,		-ObjectSize,	-ObjectSize, -ObjectSize, -ObjectSize,
	-ObjectSize,	ObjectSize,		ObjectSize,		-ObjectSize,	ObjectSize,		-ObjectSize,	-ObjectSize, -ObjectSize, -ObjectSize,
	-ObjectSize,	-ObjectSize,	-ObjectSize,	-ObjectSize,	-ObjectSize,	ObjectSize,		-ObjectSize, ObjectSize, ObjectSize, 
	-ObjectSize,	-ObjectSize,	-ObjectSize,	ObjectSize,		-ObjectSize,	-ObjectSize,	ObjectSize, -ObjectSize, ObjectSize, 
	ObjectSize,		-ObjectSize,	ObjectSize,		-ObjectSize,	-ObjectSize,	ObjectSize,		-ObjectSize, -ObjectSize, -ObjectSize,
};
GLfloat cube_normal[36][3] = {
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,
	-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,0.0f,-1.0f,0.0f,
};

GLfloat pyramid_vertices[] = {
	0.0f,ObjectSize,0.0f,-ObjectSize,-ObjectSize ,ObjectSize,ObjectSize, -ObjectSize ,ObjectSize,
	0.0f,ObjectSize,0.0f,ObjectSize, -ObjectSize ,ObjectSize,ObjectSize,-ObjectSize ,-ObjectSize,
	0.0f,ObjectSize,0.0f,ObjectSize,-ObjectSize ,-ObjectSize,-ObjectSize, -ObjectSize ,-ObjectSize,
	0.0f,ObjectSize,0.0f,-ObjectSize, -ObjectSize ,-ObjectSize,-ObjectSize,-ObjectSize ,ObjectSize,
	 -ObjectSize, -ObjectSize,-ObjectSize, ObjectSize, -ObjectSize,ObjectSize,-ObjectSize,-ObjectSize,ObjectSize,
	-ObjectSize, -ObjectSize ,-ObjectSize,ObjectSize,-ObjectSize,-ObjectSize, ObjectSize, -ObjectSize,ObjectSize,
};

glm::vec3 pyramid_pos[5] = {
	glm::vec3(0.0f,ObjectSize/2,0.0f),
	glm::vec3(-ObjectSize,-ObjectSize / 2,ObjectSize),
	glm::vec3(ObjectSize, -ObjectSize / 2,ObjectSize),
	glm::vec3(ObjectSize,-ObjectSize / 2,-ObjectSize),
	glm::vec3(-ObjectSize, -ObjectSize / 2,-ObjectSize),
	
};
glm::vec3 pyramid_normal[18];
GLvoid DrawCube();
GLvoid DrawPyramid();
GLuint VAO, VBO[3];
glm::vec3 light_pos;
GLvoid DrawLight();
GLboolean draw_cube = true;
GLboolean on_light = true;
glm::vec3 objR;
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example1");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	InitValue();
	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutSpecialFunc(SpecialKeyboard);
	

	glutMainLoop(); // 이벤트 처리 시작 
}
GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetTransformMatrix();
	
	if(on_light)
		DrawLight();
	if(draw_cube)
		DrawCube();
	else
		DrawPyramid();

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'a':	//카메라 왼쪽 이동
		cameraPos.x -= WorldSize / 100;
		std::cout << "x: " << cameraPos.x << std::endl;
		break;
	case 'd':	//카메라 오른쪽 이동
		cameraPos.x += WorldSize / 100;
		std::cout << "x: " << cameraPos.x << std::endl;
		break;
	case 'w':	//카메라 위쪽 이동
		cameraPos.y += WorldSize / 100;
		std::cout << "y: " << cameraPos.y << std::endl;
		break;
	case 's':	//카메라 아래쪽 이동
		cameraPos.y -= WorldSize / 100;
		std::cout << "y: " << cameraPos.y << std::endl;
		break;
	case 'H':	//은면제거 설정 / 해제
	case 'h':
		if (flag_cull_face)	glDisable(GL_CULL_FACE);
		else glEnable(GL_CULL_FACE);
		flag_cull_face = 1 - flag_cull_face;
		break;
	case 'J':	//깊이검사 설정 / 해제
	case 'j':
		if (flag_depth_test)	glDisable(GL_DEPTH_TEST);
		else glEnable(GL_DEPTH_TEST);
		flag_depth_test = 1 - flag_depth_test;
		break;
	case 'L':
	case 'l':
		if (flag_draw_line)	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		flag_draw_line = 1 - flag_draw_line;
		break;
	case 'Y':
	{
		glm::mat4 Ry = glm::mat4(1.0f);
		Ry = glm::rotate(Ry, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		light_pos = glm::vec3(Ry * glm::vec4(light_pos, 1.0f));
	}
		break;
	case 'y':
	{
		glm::mat4 Ry = glm::mat4(1.0f);
		Ry = glm::rotate(Ry, glm::radians(-5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		light_pos = glm::vec3(Ry * glm::vec4(light_pos, 1.0f));
		std::cout << "light_pos: " << light_pos.x << ", " << light_pos.y << ", " << light_pos.z << std::endl;
	}
		break;
	case 'N':
	case 'n':
		draw_cube = 1 - draw_cube;
		break;
	case '-':	//x축 양
		objR.x += 5.0f;
		break;
	case '=':
	case '+':	//x축 음
		objR.x -= 5.0f;
		break;
	case '[':	//y축
		objR.y += 5.0f;
		break;
	case ']':
		objR.y -= 5.0f;
		break;
	case ',':	//z축
		objR.z += 5.0f;
		break;
	case '.':
		objR.z -= 5.0f;
		break;
	case 'Z':
		light_pos = glm::vec3(1.05,1.05,1.05) * light_pos;
		break;
	case 'z':
		light_pos = glm::vec3(0.95,0.95,0.95) * light_pos;
		break;
	case 'M':
	case 'm':
		on_light = 1 - on_light;
		break;
	}

	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		light_pos.x -= 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		light_pos.x += 1.0f;
		break;
	case GLUT_KEY_DOWN:
		light_pos.y -= 1.0f;
		break;
	case GLUT_KEY_UP:
		light_pos.y += 1.0f;
		break;
	}
	glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case 3:			//마우스휠 위로 역할
			cameraPos.z -= WorldSize / 100;	//카메라 안쪽으로
			std::cout << "z: " << cameraPos.z << std::endl;
			break;
		case 4:			//마우스휠 아래로 역할
			cameraPos.z += WorldSize / 100;	//카메라 바깥쪽으로
			std::cout << "z: " << cameraPos.z << std::endl;
			break;
		}
		break;
	case GLUT_UP:
		break;

	}
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {

	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, w, h);
}
GLvoid InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);


}
GLvoid InitValue() {
	{
		glEnable(GL_DEPTH_TEST);
		flag_depth_test = true;
		/*glEnable(GL_CULL_FACE);
		flag_cull_face = true;*/
		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		flag_draw_line = true;*/
	}

	{
		cameraPos = glm::vec3(100.0f, 70.0f, WorldSize);
		cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
		{
			glm::mat4 rot = glm::mat4(1.0f);
			rot = glm::rotate(rot, glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			rot = glm::rotate(rot, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			cameraDirection = glm::vec3(rot * glm::vec4(cameraDirection,1.0f));
		}
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		flag_perspective_projection = true;
	}

	{
		light_pos = glm::vec3(50.0f, 0.0f, 0.0f);
	}

	{
		//0번쨰 면 normal 벡터
		glm::vec3 normal_0 = glm::normalize(glm::cross(glm::vec3(pyramid_pos[0] - pyramid_pos[1]), glm::vec3(pyramid_pos[0] - pyramid_pos[2])));
		pyramid_normal[0] = normal_0;
		pyramid_normal[1] = normal_0;
		pyramid_normal[2] = normal_0;

		//1번째 면 normal
		glm::vec3 normal_1 = glm::normalize(glm::cross(glm::vec3(pyramid_pos[0] - pyramid_pos[2]), glm::vec3(pyramid_pos[0] - pyramid_pos[3])));
		pyramid_normal[3] = normal_1;
		pyramid_normal[4] = normal_1;
		pyramid_normal[5] = normal_1;

		//2번째 면 normal
		glm::vec3 normal_2 = glm::normalize(glm::cross(glm::vec3(pyramid_pos[0] - pyramid_pos[3]), glm::vec3(pyramid_pos[0] - pyramid_pos[4])));
		pyramid_normal[6] = normal_2;
		pyramid_normal[7] = normal_2;
		pyramid_normal[8] = normal_2;
		
		//3번째 면 normal
		glm::vec3 normal_3 = glm::normalize(glm::cross(glm::vec3(pyramid_pos[0] - pyramid_pos[4]), glm::vec3(pyramid_pos[0] - pyramid_pos[1])));
		pyramid_normal[9] = normal_3;
		pyramid_normal[10] = normal_3;
		pyramid_normal[11] = normal_3;
		
		//4번째 면 normal
		glm::vec3 normal_4 = glm::normalize(glm::cross(glm::vec3(pyramid_pos[4] - pyramid_pos[2]), glm::vec3(pyramid_pos[4] - pyramid_pos[1])));
		pyramid_normal[12] = normal_4;
		pyramid_normal[13] = normal_4;
		pyramid_normal[14] = normal_4;
		pyramid_normal[15] = normal_4;
		pyramid_normal[16] = normal_4;
		pyramid_normal[17] = normal_4;
		std::cout << normal_0.x << ", " << normal_0.y << ", " << normal_0.z << std::endl;
	}
	
	{
		draw_cube = true;
		objR = glm::vec3(0.0f, 0.0f, 0.0f);
		on_light = true;
	}
}
GLvoid ChangeDegree(GLfloat degree) {
	if (degree < 0.0f) {
		degree += 360.0f;
	}
	else {
		degree -= 360.0f;
	}
}

GLvoid DrawCube() {
	//model 변환
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(objR.x), glm::vec3(1.0f, 0.0f, 0.0f));
	Ry = glm::rotate(Ry, glm::radians(objR.y), glm::vec3(0.0f, 1.0f, 0.0f));
	Rz = glm::rotate(Rz, glm::radians(objR.z), glm::vec3(0.0f, 0.0f, 1.0f));

	TR = Rz*Ry * Rx * TR;

	unsigned int modelLocation = glGetUniformLocation(s_program, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	
	//	GLfloat temp_color[8][3];
	//GLfloat temp_color[8][3] = { temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B],temp_rgb[R],temp_rgb[G],temp_rgb[B], };
	glBindVertexArray(VAO);
	
	/*
	//조명 x
	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	
	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, (void*)0);*/
	
	//조명 o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);	//노말벡터에 관련된 값이오나 임시로 확인하기 위해 사용
	glm::vec3 norm[36];
	for (int i = 0; i < 36; ++i) {
		norm[i] = glm::mat3(glm::transpose(glm::inverse(TR))) * glm::vec3(cube_normal[i][X], cube_normal[i][Y], cube_normal[i][Z]);
	}
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(norm), norm, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	

	int ambientLightLocation = glGetUniformLocation(s_program, "ambientLight");
	glUniform3f(ambientLightLocation, 0.35f,0.35f,0.35f);
	if (on_light) {
		int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
		glUniform3f(lightPosLocation, light_pos.x, light_pos.y, light_pos.z);
	}
	else {
		int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
		glUniform3f(lightPosLocation, 0.0f,0.0f,0.0f);
	}
	
	
	int lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	int objColorLocation = glGetUniformLocation(s_program, "objectColor");
	glUniform3f(objColorLocation, 0.0f,1.0f,0.0f);
	unsigned int viewPosLocation = glGetUniformLocation(s_program, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
	
	glDrawArrays(GL_TRIANGLES, 0, sizeof(cube_vertices) / sizeof(cube_vertices[0]));
}
GLvoid DrawPyramid() {
	//model 변환
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(objR.x), glm::vec3(1.0f, 0.0f, 0.0f));
	Ry = glm::rotate(Ry, glm::radians(objR.y), glm::vec3(0.0f, 1.0f, 0.0f));
	Rz = glm::rotate(Rz, glm::radians(objR.z), glm::vec3(0.0f, 0.0f, 1.0f));

	TR = Rz * Ry * Rx * TR;

	unsigned int modelLocation = glGetUniformLocation(s_program, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);


	glBindVertexArray(VAO);


	//조명 o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_vertices), pyramid_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);	//노말벡터에 관련된 값이오나 임시로 확인하기 위해 사용
	glm::vec3 norm[18];
	for (int i = 0; i < 18; ++i) {
		norm[i] = glm::mat3(glm::transpose(glm::inverse(TR))) * pyramid_normal[i];
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(norm), norm, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);



	int ambientLightLocation = glGetUniformLocation(s_program, "ambientLight");
	glUniform3f(ambientLightLocation, 0.35f, 0.35f, 0.35f);
	if (on_light) {
		int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
		glUniform3f(lightPosLocation, light_pos.x, light_pos.y, light_pos.z);
	}
	else {
		int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
		glUniform3f(lightPosLocation, 0.0f, 0.0f, 0.0f);
	}

	int lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	int objColorLocation = glGetUniformLocation(s_program, "objectColor");
	glUniform3f(objColorLocation, 0.0f, 1.0f, 0.0f);
	unsigned int viewPosLocation = glGetUniformLocation(s_program, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(pyramid_vertices) / sizeof(pyramid_vertices[0]));
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
GLvoid SetTransformMatrix() {
	{//model 변환
		glm::mat4 TR = glm::mat4(1.0f);
		/*if (flag_incline[IS_ON]) {
			glm::mat4 inclineR = glm::mat4(1.0f);
			inclineR = glm::rotate(inclineR, glm::radians(incline[X]), glm::vec3(1.0f, 0.0f, 0.0f));
			inclineR = glm::rotate(inclineR, glm::radians(incline[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
			TR = inclineR * TR;
		}*/
		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	}

	{//카메라 변환
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	}
	 
	{//투영 변환
		glm::mat4 projection = glm::mat4(1.0f);
		if (flag_perspective_projection) {	//원근
			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize*3);
			//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3.0));
		}
		else {	//직각
			GLfloat halfsize = WorldSize;
			projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
		}
		

		unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
	}
}
GLvoid DrawLight() {
	GLUquadric* qobj = gluNewQuadric();

	{
		//model 변환
		glm::mat4 T = glm::mat4(1.0f);
		T = glm::translate(T, glm::vec3(light_pos.x, light_pos.y, light_pos.z));
		
		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &T[0][0]);
	
	}

	int ambientLightLocation = glGetUniformLocation(s_program, "ambientLight");
	glUniform3f(ambientLightLocation, 1.0f,1.0f,1.0f);
	int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
	glUniform3f(lightPosLocation, light_pos.x, light_pos.y, light_pos.z);
	int lightColorLocation = glGetUniformLocation(s_program, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	int objColorLocation = glGetUniformLocation(s_program, "objectColor");
	glUniform3f(objColorLocation, 1.0f, 1.0f, 1.0f);
	unsigned int viewPosLocation = glGetUniformLocation(s_program, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);

	gluSphere(qobj, 1, 50, 50);
}