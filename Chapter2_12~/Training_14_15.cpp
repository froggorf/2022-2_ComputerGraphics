/*
1 - ����
2 - �� / �� 
3 - ���� �˻�
X/x - ������ ���� x�� ��/��
Y/y - ������ ���� y�� ��/��
A/a - ���� ���� x�� ��/��
B/b - ���� ���� y�� ��/��
R/r - y�࿡ ���� ����
C/c - �ٸ� �������� ��ü
S - Ÿ�̸� ����
D - ��ü �ʱ�ȭ

----15��----
. -> ���� ���� ���
 -> ������ ���� ���

(. or / ���)  +/- -> �� ���� ���ڸ����� Ȯ��,���
(. or / ���)  [/] -> �� ���� ������ ���ؼ� Ȯ��, ���

j -> x�� ���
k -> y�� ���
l -> z�� ���
(j or k or l ���) �¿� ����Ű -> ���� ������Ʈ �� ������ �̵�
(j or k or l ���) ���� ����Ű -> ������ ������Ʈ �� ������ �̵�

T/t - ȸ���� �׸��� Ű��/����
0 - ���� �ڸ����� �� ������ �������� �̵�
9 - �� ������ ������ �ڸ��� �̵�
8 - �� ������ x���� �������� ��/�Ʒ� �̵�
7 - �� ������ z���� �������� ��/�Ʒ� �̵�
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h> //--- �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <random>
#define WIDTH 1024
#define HEIGHT 960
#define X 0
#define Y 1
#define Z 2
#define ObjectSize 0.2
#define RotateSpeed 4		//n���� �ִϸ��̼��� �ǵ���
#define ObjectSpeed 0.05
#define MoveTime 50
int TimerSpeed = 50;
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid InitValue();
GLvoid SpecialKeyboard(int, int, int);
GLvoid KeyUp(unsigned char, int, int);
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
GLuint VAO_tornado, VBO_tornado[2];

GLfloat left_first_rotate[3] = { 30.0,-30.0,0.0 };		//Rfx, Rfy, Rfz		(����)
GLfloat left_rotate[3] = { 0.0,0.0,0.0 };		//Rx, Ry			(����)
GLfloat left_first_translate[3] = { -ObjectSize * 2.5, ObjectSize,-ObjectSize };	//Tf
GLfloat left_translate[3] = { 0.0,0.0,0.0 };		//T
GLfloat left_scale[3] = { 1.0,1.0,1.0 };
GLfloat left_axes_scale[3] = { 1.0,1.0,1.0 };

GLfloat right_first_rotate[3] = { 30.0,-30.0,0.0 };		//Rfx, Rfy, Rfz		(����)
GLfloat right_rotate[3] = { 0.0,0.0,0.0 };		//Rx, Ry			(����)
GLfloat right_first_translate[3] = { ObjectSize * 2.5, ObjectSize, ObjectSize };	//Tf
GLfloat right_translate[3] = { 0.0,0.0,0.0 };		//T
GLfloat right_scale[3] = { 1.0,1.0,1.0 };
GLfloat right_axes_scale[3] = {1.0,1.0,1.0};

GLfloat axes_rotate[3] = {30.0,-30.0,0.0};

enum OBJECT {CUBE = 0, CONE, SPHERE};
int left_object = CUBE;
int right_object = SPHERE;
std::random_device rd;
std::uniform_int_distribution<int> uid(CUBE, SPHERE);
enum TIMER {
	ROTATE_LEFT_X_PLUS, ROTATE_LEFT_X_MINUS,
	ROTATE_LEFT_Y_PLUS, ROTATE_LEFT_Y_MINUS,
	ROTATE_RIGHT_X_PLUS, ROTATE_RIGHT_X_MINUS,
	ROTATE_RIGHT_Y_PLUS, ROTATE_RIGHT_Y_MINUS,
	ROTATE_Yaxes_PLUS, ROTATE_Yaxes_MINUS,
	ROTATE_TORNADO, GOTO_SOMEWHERE
};
void RotateObject(int value);
int flag_timer = 0;
int off_timer = 0;
bool flag_cull = true;
bool flag_fill = true;
bool flag_depth = true;
bool flag_x_translate = false;
bool flag_y_translate = false;
bool flag_z_translate = false;
bool flag_left_object = false;
bool flag_right_object = false;
bool flag_tornado = false;
bool flag_clockwise = false;
int tornado_time = 0;
bool flag_goto = false;
bool flag_goto_forward = true;
int goto_time = 0;
GLfloat left_goto_translate[3] = { 0.0,0.0,0.0 };
GLfloat left_goto_first_translate[3] = { 0.0,0.0,0.0 };
GLfloat right_goto_translate[3] = { 0.0,0.0,0.0 };
GLfloat right_goto_first_translate[3] = { 0.0,0.0,0.0 };

GLfloat left_before_translate[3] = { 0.0,0.0,0.0 };
GLfloat left_before_first_translate[3] = { 0.0,0.0,0.0 };
GLfloat right_before_translate[3] = { 0.0,0.0,0.0 };
GLfloat right_before_first_translate[3] = { 0.0,0.0,0.0 };

GLfloat cube_shape[8][3] = {
	-ObjectSize,ObjectSize,-ObjectSize,
	-ObjectSize,ObjectSize,ObjectSize,
	ObjectSize,ObjectSize,ObjectSize,
	ObjectSize,ObjectSize,-ObjectSize,
	-ObjectSize,-ObjectSize,ObjectSize,
	ObjectSize,-ObjectSize,ObjectSize,
	ObjectSize,-ObjectSize,-ObjectSize,
	-ObjectSize,-ObjectSize,-ObjectSize
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
void DrawCoordinateAxes();
void DrawCube(GLfloat first_translate[3], GLfloat translate[3], GLfloat first_rotate[3], GLfloat rotate[3], GLfloat scale[3], GLfloat axes_scale[3]);
void DrawObject(int, GLfloat first_translate[3], GLfloat translate[3], GLfloat first_rotate[3], GLfloat rotate[3], GLfloat sclae[3], GLfloat axes_scale[3]);
void DrawLeft();
void DrawRight();
void DrawTornado();
void ResetObject();
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(500, 500); // �������� ��ġ ����
	glutInitWindowSize(WIDTH, HEIGHT); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����

		//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
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
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	InitValue();
	
	InitShader();
	InitBuffer();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKeyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);


	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}


GLvoid drawScene() {
	//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
	glClearColor(1.0f,1.0f,1.0f, 0.0f); // �������� ��blue�� �� ����

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�

	DrawCoordinateAxes();
	DrawLeft();
	DrawRight();
	if(flag_tornado) DrawTornado();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void DrawLeft() {
	switch (left_object) {
	case CUBE:
		DrawCube(left_first_translate, left_translate, left_first_rotate, left_rotate,left_scale,left_axes_scale);
		break;
	case CONE:
	case SPHERE:
		DrawObject(left_object, left_first_translate, left_translate, left_first_rotate, left_rotate,left_scale,left_axes_scale);
		break;
	}
}
void DrawRight() {
	switch (right_object) {
	case CUBE:
		DrawCube(right_first_translate, right_translate, right_first_rotate, right_rotate,right_scale,right_axes_scale);
		break;
	case CONE:
	case SPHERE:
		DrawObject(right_object,right_first_translate, right_translate, right_first_rotate, right_rotate,right_scale,right_axes_scale);
		break;
	}
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
	glViewport(0, 0, w, h);
}

GLvoid KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'Q':
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'j':
		flag_x_translate = true;
		break;
	case 'k':
		flag_y_translate = true;
		break;
	case 'l':
		flag_z_translate = true;
		break;
	case '.':
		flag_left_object = true;
		break;
	case '/':
		flag_right_object = true;
		break;
	case '+':
	case '=':
		if (flag_left_object) {
			left_scale[X] += 0.05;
			left_scale[Y] += 0.05;
			left_scale[Z] += 0.05;
		}
		if (flag_right_object) {
			right_scale[X] += 0.05;
			right_scale[Y] += 0.05;
			right_scale[Z] += 0.05;
		}
		break;
	case '-':
		if (flag_left_object) {
			left_scale[X] -= 0.05;
			left_scale[Y] -= 0.05;
			left_scale[Z] -= 0.05;
		}
		if (flag_right_object) {
			right_scale[X] -= 0.05;
			right_scale[Y] -= 0.05;
			right_scale[Z] -= 0.05;
		}
		break;
	case '[':
		if (flag_left_object) {
			left_axes_scale[X] += 0.05;
			left_axes_scale[Y] += 0.05;
			left_axes_scale[Z] += 0.05;
		}
		if (flag_right_object) {
			right_axes_scale[X] += 0.05;
			right_axes_scale[Y] += 0.05;
			right_axes_scale[Z] += 0.05;
		}
		
		break;
	case ']':
		if (flag_left_object) {
			left_axes_scale[X] -= 0.05;
			left_axes_scale[Y] -= 0.05;
			left_axes_scale[Z] -= 0.05;
		}
		if (flag_right_object) {
			right_axes_scale[X] -= 0.05;
			right_axes_scale[Y] -= 0.05;
			right_axes_scale[Z] -= 0.05;
		}
		break;
	case '1':
		if (!flag_cull) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
		flag_cull = 1 - flag_cull;	
		break;
	case '2':
		if (!flag_fill) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		flag_fill = 1 - flag_fill;
		break;
	case '3':
		if (!flag_depth) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
		flag_depth = 1 - flag_depth;
		break;
	case '0':		//�������� �̵�
		if (flag_goto) {
			off_timer = flag_timer;
			ResetObject();
			flag_goto_forward = true;
			goto_time = 0;
		}
		else {
			for (int i = 0; i < 3; ++i) {
				left_goto_translate[i] = 0.0;
				left_goto_first_translate[i] = 0.0;
				right_goto_translate[i] = 0.0;
				right_goto_first_translate[i] = 0.0;

				left_before_translate[i] = left_translate[i];
				left_before_first_translate[i] = left_first_translate[i];
				right_before_translate[i] = right_translate[i];
				right_before_first_translate[i] = right_first_translate[i];
			}
			glutTimerFunc(TimerSpeed, RotateObject, GOTO_SOMEWHERE);
			flag_timer++;
		}
		flag_goto = 1 - flag_goto;
		break;
	case '9':		//���� ���� ��ġ�� �̵�
		if (flag_goto) {
			off_timer = flag_timer;
			ResetObject();
			flag_goto_forward = true;
			goto_time = 0;
		}
		else {
			for (int i = 0; i < 3; ++i) {
				left_goto_translate[i] = right_translate[i];
				left_goto_first_translate[i] = right_first_translate[i];
				right_goto_translate[i] = left_translate[i];
				right_goto_first_translate[i] = left_first_translate[i];

				left_before_translate[i] = left_translate[i];
				left_before_first_translate[i] = left_first_translate[i];
				right_before_translate[i] = right_translate[i];
				right_before_first_translate[i] = right_first_translate[i];
			}
			glutTimerFunc(TimerSpeed, RotateObject, GOTO_SOMEWHERE);
			flag_timer++;
		}
		flag_goto = 1 - flag_goto;
		break;
	case '8':		//�������� �̵�
		if (flag_goto) {
			off_timer = flag_timer;
			ResetObject();
			flag_goto_forward = true;
			goto_time = 0;
		}
		else {
			left_first_translate[X] = 1.0;
			left_first_translate[Y] = 0.0;
			left_first_translate[Z] = 0.0;
			right_first_translate[X] = -1.0;
			right_first_translate[Y] = 0.0;
			right_first_translate[Z] = 0.0;
			for (int i = 0; i < 3; ++i) {
				left_translate[i] = 0.0;
				right_translate[i] = 0.0;
			}
			for (int i = 0; i < 3; ++i) {
				left_goto_translate[i] = right_translate[i];
				left_goto_first_translate[i] = right_first_translate[i];
				right_goto_translate[i] = left_translate[i];
				right_goto_first_translate[i] = left_first_translate[i];

				left_before_translate[i] = left_translate[i];
				left_before_first_translate[i] = left_first_translate[i];
				right_before_translate[i] = right_translate[i];
				right_before_first_translate[i] = right_first_translate[i];
			}
			glutTimerFunc(TimerSpeed, RotateObject, GOTO_SOMEWHERE);
			flag_timer++;
		}
		flag_goto = 1 - flag_goto;
		break;
	case '7':		//�������� �̵�
		if (flag_goto) {
			off_timer = flag_timer;
			ResetObject();
			flag_goto_forward = true;
			goto_time = 0;
		}
		else {
			left_first_translate[X] = 0.0;
			left_first_translate[Y] = 0.0;
			left_first_translate[Z] = 1.0;
			right_first_translate[X] = 0.0;
			right_first_translate[Y] = 0.0;
			right_first_translate[Z] = -1.0;
			for (int i = 0; i < 3; ++i) {
				left_translate[i] = 0.0;
				right_translate[i] = 0.0;
			}
			for (int i = 0; i < 3; ++i) {
				left_goto_translate[i] = right_translate[i];
				left_goto_first_translate[i] = right_first_translate[i];
				right_goto_translate[i] = left_translate[i];
				right_goto_first_translate[i] = left_first_translate[i];

				left_before_translate[i] = left_translate[i];
				left_before_first_translate[i] = left_first_translate[i];
				right_before_translate[i] = right_translate[i];
				right_before_first_translate[i] = right_first_translate[i];
			}
			glutTimerFunc(TimerSpeed, RotateObject, GOTO_SOMEWHERE);
			flag_timer++;
		}
		flag_goto = 1 - flag_goto;
		break;

		break;
	case 'X':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_RIGHT_X_PLUS);
		flag_timer++;
		break;
	case 'x':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_RIGHT_X_MINUS);
		flag_timer++;
		break;
	case 'Y':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_RIGHT_Y_PLUS);
		flag_timer++;
		break;
	case 'y':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_RIGHT_Y_MINUS);
		flag_timer++;
		break;
	case 'A':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_LEFT_X_PLUS);
		flag_timer++;
		break;
	case 'a':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_LEFT_X_MINUS);
		flag_timer++;
		break;
	case 'B':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_LEFT_Y_PLUS);
		flag_timer++;
		break;
	case 'b':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_LEFT_Y_MINUS);
		flag_timer++;
		break;
	case 'R':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_Yaxes_PLUS);
		flag_timer++;
		break;
	case 'r':
		glutTimerFunc(TimerSpeed, RotateObject, ROTATE_Yaxes_MINUS);
		flag_timer++;
		break;
	case 'C':
	case 'c':
		left_object = uid(rd);
		right_object = uid(rd);
		break;
	case 'D':
	case 'd':
		ResetObject();
		break;
	case 'S':
	case 's':
		off_timer = flag_timer;
		break;
	case 'T':
	case 't':
		if (flag_tornado) {
			ResetObject();
			off_timer = flag_timer;
			flag_clockwise = false;
			tornado_time = 0;
		}
		else {
			left_first_rotate[X] = axes_rotate[X], left_first_rotate[Y] = axes_rotate[Y];
			left_rotate[X] = 0.0, left_rotate[Y] = 0.0, left_rotate[Z] = 0.0;
			left_first_translate[X] = 0.0, left_first_translate[Y] = 0.0, left_first_translate[Z] = 0.0;
			left_scale[X] = 0.5, left_scale[Y] = 0.5, left_scale[Z] = 0.5;
			left_axes_scale[X] = 1.0, left_axes_scale[Y] = 1.0, left_axes_scale[Z] = 1.0;

			right_first_rotate[X] = axes_rotate[X], right_first_rotate[Y] = axes_rotate[Y]+10*107;
			right_rotate[X] = 0.0, right_rotate[Y] = 0.0, right_rotate[Z] = 0.0;
			right_first_translate[X] = 0.0 + 0.02*107, right_first_translate[Y] = 0.0, right_first_translate[Z] = 0.0;
			right_scale[X] = 0.5, right_scale[Y] = 0.5, right_scale[Z] = 0.5;
			right_axes_scale[X] = 1.0, right_axes_scale[Y] = 1.0, right_axes_scale[Z] = 1.0;
			glutTimerFunc(TimerSpeed, RotateObject, ROTATE_TORNADO);
			flag_timer++;
		}
		flag_tornado = 1 - flag_tornado;
		break;
	}

	glutPostRedisplay();
}
GLvoid SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:		//���� ����
		if (flag_x_translate) {
			
			left_translate[X] += 0.05;
			std::cout << left_translate[X] << std::endl;
		}
		if (flag_y_translate) {
			left_translate[Y] += 0.05;
		}
		if (flag_z_translate) {
			left_translate[Z] += 0.05;
		}
		break;
	case GLUT_KEY_LEFT:			//���� ����
		if (flag_x_translate) {
			left_translate[X] -= 0.05;
		}
		if (flag_y_translate) {
			left_translate[Y] -= 0.05;
		}
		if (flag_z_translate) {
			left_translate[Z] -= 0.05;
		}
		break;
	case GLUT_KEY_UP:			//������ ����
		if (flag_x_translate) {
			right_translate[X] += 0.05;
		}
		if (flag_y_translate) {
			right_translate[Y] += 0.05;
		}
		if (flag_z_translate) {
			right_translate[Z] += 0.05;
		}
		break;	
	case GLUT_KEY_DOWN:			//������ ����
		if (flag_x_translate) {
			right_translate[X] -= 0.05;
		}
		if (flag_y_translate) {
			right_translate[Y] -= 0.05;
		}
		if (flag_z_translate) {
			right_translate[Z] -= 0.05;
		}
		break;
	}
	glutPostRedisplay();
}
GLvoid KeyUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'j':
		flag_x_translate = false;
		break;
	case 'k':
		flag_y_translate = false;
		break;
	case 'l':
		flag_z_translate = false;
		break;
	case '.':
		flag_left_object = false;
		break;
	case '/':
		flag_right_object = false;
		break;
	}
	glutPostRedisplay();
}
void RotateObject (int value) {
	if (off_timer > 0) {
		flag_timer -= 1;
		off_timer -= 1;
		return;
	}
	switch (value)
	{
	case ROTATE_LEFT_X_PLUS:
		left_rotate[X] += RotateSpeed;
		if (left_rotate[X] >= 360) left_rotate[X] -= 360;
		break;
	case ROTATE_LEFT_X_MINUS:
		left_rotate[X] -= RotateSpeed;
		if (left_rotate[X] <= 0) left_rotate[X] += 360;
		break;
	case ROTATE_LEFT_Y_PLUS:
		left_rotate[Y] += RotateSpeed;
		if (left_rotate[Y] >= 360) left_rotate[Y] -= 360;
		break;
	case ROTATE_LEFT_Y_MINUS:
		left_rotate[Y] -= RotateSpeed;
		if (left_rotate[Y] <= 0) left_rotate[Y] += 360;
		break;
	case ROTATE_RIGHT_X_PLUS:
		right_rotate[X] += RotateSpeed;
		if (right_rotate[X] >= 360) right_rotate[X] -= 360;
		break;
	case ROTATE_RIGHT_X_MINUS:
		right_rotate[X] -= RotateSpeed;
		if (right_rotate[X] <= 0) right_rotate[X] += 360;
		break;
	case ROTATE_RIGHT_Y_PLUS:
		right_rotate[Y] += RotateSpeed;
		if (right_rotate[Y] >= 360) right_rotate[Y] -= 360;
		break;
	case ROTATE_RIGHT_Y_MINUS:
		right_rotate[Y] -= RotateSpeed;
		if (right_rotate[Y] <= 0) right_rotate[Y] += 360;
		break;
	case ROTATE_Yaxes_PLUS:
		left_first_rotate[Y] += RotateSpeed;
		if (left_first_rotate[Y] >= 360) left_first_rotate[Y] -= 360;
		right_first_rotate[Y] += RotateSpeed;
		if (right_first_rotate[Y] >= 360) right_first_rotate[Y] -= 360;
		break;
	case ROTATE_Yaxes_MINUS:
		left_first_rotate[Y] -= RotateSpeed;
		if (left_first_rotate[Y] <= 0) left_first_rotate[Y] += 360;
		right_first_rotate[Y] -= RotateSpeed;
		if (right_first_rotate[Y] <= 0) right_first_rotate[Y] += 360;
		break;
	case ROTATE_TORNADO:
		if (flag_clockwise) {
			left_first_rotate[Y] -= 10;
			left_first_translate[X] -= 0.02;
			right_first_rotate[Y] += 10;
			right_first_translate[X] += 0.02;
		}
		else {
			left_first_rotate[Y] += 10;
			left_first_translate[X] += 0.02;
			right_first_rotate[Y] -= 10;
			right_first_translate[X] -= 0.02;
		}
		
		if (tornado_time == 107) {
			flag_clockwise = 1 - flag_clockwise;
			tornado_time = -1;
		}
		std::cout << tornado_time << std::endl;
		++tornado_time;

		break;
	case GOTO_SOMEWHERE:
		if (flag_goto_forward) {
			for (int i = 0; i < 3; ++i) {
				left_translate[i] += (left_goto_translate[i]-left_before_translate[i])/MoveTime;
				left_first_translate[i] += (left_goto_first_translate[i] - left_before_first_translate[i]) / MoveTime;
				right_translate[i] += (right_goto_translate[i] - right_before_translate[i]) / MoveTime;
				right_first_translate[i] += (right_goto_first_translate[i] - right_before_first_translate[i]) / MoveTime;
			}
		}
		else {
			for (int i = 0; i < 3; ++i) {
				left_translate[i] -= (left_goto_translate[i] - left_before_translate[i]) / MoveTime;
				left_first_translate[i] -= (left_goto_first_translate[i] - left_before_first_translate[i]) / MoveTime;
				right_translate[i] -= (right_goto_translate[i] - right_before_translate[i]) / MoveTime;
				right_first_translate[i] -= (right_goto_first_translate[i] - right_before_first_translate[i]) / MoveTime;
			}
		}
		if (goto_time >= MoveTime) {
			flag_goto_forward = 1 - flag_goto_forward;
			goto_time = -1;
		}
		goto_time++;
		break;
	default:
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

GLvoid MouseMove(int x, int y){

	glutPostRedisplay();
}

void DrawObject(int object_type, GLfloat first_translate[3], GLfloat translate[3], GLfloat first_rotate[3], GLfloat rotate[3], GLfloat scale[3], GLfloat axes_scale[3]) {
	GLUquadricObj* qobj = gluNewQuadric();
	//gluQuadricDrawStyle(qobj, GLU_LINE);
	glm::mat4 TR = glm::mat4(1.0f);		//���� ���� ���
	glm::mat4 Tf = glm::mat4(1.0f);		//ó���̵�
	glm::mat4 T = glm::mat4(1.0f);		//���� �� �̵�
	glm::mat4 Rfx = glm::mat4(1.0f);	//���� ����
	glm::mat4 Rfy = glm::mat4(1.0f);
	glm::mat4 Rfz = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);		//���� ����
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 Saxes = glm::mat4(1.0f);

	Tf = glm::translate(Tf, glm::vec3(first_translate[X], first_translate[Y], first_translate[Z]));
	T = glm::translate(T, glm::vec3(translate[X], translate[Y], translate[Z]));
	Rfx = glm::rotate(Rfx, glm::radians(first_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Rfy = glm::rotate(Rfy, glm::radians(first_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	Rfz = glm::rotate(Rfz, glm::radians(first_rotate[Z]), glm::vec3(0.0, 0.0, 1.0));
	Rx = glm::rotate(Rx, glm::radians(rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	Rz = glm::rotate(Rz, glm::radians(rotate[Z]), glm::vec3(0.0, 0.0, 1.0));
	S = glm::scale(S, glm::vec3(scale[X], scale[Y], scale[Z]));
	Saxes = glm::scale(S, glm::vec3(axes_scale[X], axes_scale[Y], axes_scale[Z]));

	//	      ����		ù �̵�		����			
	TR = (Saxes) * (Rfx * Rfy * Rfz) * (Tf) * (Rx * Ry * Rz) * T * (S);
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	if (object_type == CONE)
		gluCylinder(qobj, ObjectSize, 0.0, ObjectSize*2, 20, 8);
	else
		gluSphere(qobj, ObjectSize, 50, 50);
	
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
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorlog << std::endl;
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
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorlog << std::endl;
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
	glGenVertexArrays(1, &VAO_axes);
	glGenBuffers(2, VBO_axes);
	glGenVertexArrays(1, &VAO_cube);
	glGenBuffers(2, VBO_cube);
	glGenBuffers(1, &VBO_index);
	glGenVertexArrays(1, &VAO_tornado);
	glGenBuffers(2, VBO_tornado);
}

void DrawCube(GLfloat first_translate[3], GLfloat translate[3], GLfloat first_rotate[3], GLfloat rotate[3], GLfloat scale[3], GLfloat axes_scale[3]) {
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

	glm::mat4 TR = glm::mat4(1.0f);		//���� ���� ���
	glm::mat4 Tf = glm::mat4(1.0f);		//ó���̵�
	glm::mat4 T = glm::mat4(1.0f);		//���� �� �̵�
	glm::mat4 Rfx = glm::mat4(1.0f);	//���� ����
	glm::mat4 Rfy = glm::mat4(1.0f);
	glm::mat4 Rfz = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);		//���� ����
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 Saxes = glm::mat4(1.0f);

	Tf = glm::translate(Tf, glm::vec3(first_translate[X], first_translate[Y], first_translate[Z]));
	T = glm::translate(T, glm::vec3(translate[X], translate[Y], translate[Z]));

	Rfx = glm::rotate(Rfx, glm::radians(first_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Rfy = glm::rotate(Rfy, glm::radians(first_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	Rfz = glm::rotate(Rfz, glm::radians(first_rotate[Z]), glm::vec3(0.0, 0.0, 1.0));
	Rx = glm::rotate(Rx, glm::radians(rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	Rz = glm::rotate(Rz, glm::radians(rotate[Z]), glm::vec3(0.0, 0.0, 1.0));
	S = glm::scale(S, glm::vec3(scale[X], scale[Y], scale[Z]));
	Saxes = glm::scale(S, glm::vec3(axes_scale[X], axes_scale[Y], axes_scale[Z]));
	//	Ȯ/��� 	    ����			ù �̵�	����			
	TR = (Saxes)*(Rfx * Rfy * Rfz) * (Tf) * (Rx * Ry * Rz) *T* (S);
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
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
	GLfloat point[6][3] = {
		{0.0,1.0,0.0},
		{0.0,-1.0,0.0},
		{1.0,0.0,0.0},
		{-1.0,0.0,0.0},
		{0.0,0.0,1.0},
		{0.0,0.0,-1.0}
	};
	GLfloat color[6][3] = {
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
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
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	Rx = glm::rotate(Rx, glm::radians(axes_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Ry = glm::rotate(Ry, glm::radians(axes_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	TR = Rx * Ry;
	unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
	glDrawArrays(GL_LINES, 0, 6);

}
GLvoid InitValue() {

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

void DrawTornado() {
	glBindVertexArray(VAO_tornado);
	GLfloat point[3] = {
		0.0,0.0,0.0
	};
	GLfloat color[3] = {
		1.0,0.0,0.0
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_cube[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glm::mat4 TR = glm::mat4(1.0f);		//���� ���� ���
	glm::mat4 Tf = glm::mat4(1.0f);		//ó���̵�
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rfx = glm::mat4(1.0f);
	glm::mat4 Rfy = glm::mat4(1.0f);
	glm::mat4 Rfz = glm::mat4(1.0f);

	Rfx = glm::rotate(Rfx, glm::radians(axes_rotate[X]), glm::vec3(1.0, 0.0, 0.0));
	Rfy = glm::rotate(Rfy, glm::radians(axes_rotate[Y]), glm::vec3(0.0, 1.0, 0.0));
	Rfz = glm::rotate(Rfz, glm::radians(axes_rotate[Z]), glm::vec3(0.0, 0.0, 1.0));


	glPointSize(5.0);
	GLfloat translate = 0.0;
	GLfloat radian = 0.0;
	for (int i = 0; i < 1469; ++i) {
		Tf = glm::translate(Tf, glm::vec3(translate, 0.0, 0.0));
		Ry = glm::rotate(Ry,glm::radians(radian),glm::vec3(0.0,1.0,0.0));
		TR = (Rfx*Rfy*Rfz) * Ry * Tf;
		unsigned int modelLocation = glGetUniformLocation(s_program, "transform");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
		glDrawArrays(GL_POINTS, 0, 1);
		translate += 0.000001;
		radian += 0.001;
	}
	
	
}
void ResetObject() {
	left_first_rotate[X] = 30.0, left_first_rotate[Y] = -30.0, left_first_rotate[Z] = 0.0;
	left_rotate[X] = 0.0, left_rotate[Y] = 0.0, left_rotate[Z] = 0.0;
	left_first_translate[X] = -ObjectSize * 2.5, left_first_translate[Y] = ObjectSize, left_first_translate[Z] = -ObjectSize;
	left_translate[X] = 0.0, left_translate[Y] = 0.0, left_translate[Z] = 0.0;
	left_scale[X] = 1.0, left_scale[Y] = 1.0, left_scale[Z] = 1.0;
	left_axes_scale[X] = 1.0, left_axes_scale[Y] = 1.0, left_axes_scale[Z] = 1.0;

	right_first_rotate[X] = 30.0, right_first_rotate[Y] = -30.0, right_first_rotate[Z] = 0.0;
	right_rotate[X] = 0.0, right_rotate[Y] = 0.0, right_rotate[Z] = 0.0;
	right_first_translate[X] = ObjectSize * 2.5, right_first_translate[Y] = ObjectSize, right_first_translate[Z] = ObjectSize;
	right_translate[X] = 0.0, right_translate[Y] = 0.0, right_translate[Z] = 0.0;
	right_scale[X] = 1.0, right_scale[Y] = 1.0, right_scale[Z] = 1.0;
	right_axes_scale[X] = 1.0, right_axes_scale[Y] = 1.0, right_axes_scale[Z] = 1.0;

	left_object = CUBE;
	right_object = SPHERE;
}