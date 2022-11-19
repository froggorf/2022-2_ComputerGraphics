///*
//
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
//#include <random>
//#include <Windows.h>
//
////define 목록
//#define WIDTH 800
//#define HEIGHT 600
//
////월드관련 define
//#define ObjectSize 50
//#define WorldSize 200		//x: -100~100 / y: -100~100 / z: 0 ~ 200
//
////enum 관련
//enum XYZ { X = 0, Y = 1, Z = 2 };
//enum RGB { R = 0, G = 1, B = 2 };
//enum VAOType { POS = 0, COLOR = 1, INDEX = 2 };
//enum Timer { IS_ON = 0, TURN_OFF = 1 };
//enum SideTimerType { OPEN = 0, CLOSE = 1 };
//enum RobotDir { LEFT = 0, RIGHT = 1 };
////클래스 관련
//class Side {
//public:
//	GLuint VAO, VBO[3];
//	GLfloat pos[4][3];
//	GLfloat color[3];
//	GLuint index[2][3];
//	
//	GLfloat R[3];
//
//
//	GLvoid init(int idx);
//	GLvoid draw();
//};
//
//
////glut 관련 함수
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//GLvoid KeyBoard(unsigned char key, int x, int y);
//GLvoid Mouse(int, int, int, int);
//GLvoid MouseMove(int, int);
//GLvoid SpecialKeyboard(int, int, int);
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
//
////VAO, VBO 관련 함수 및 변수
//
//GLvoid InitBuffer();
//
////카메라 관련 함수 및 변수
//glm::vec3 cameraPos;
//glm::vec3 cameraDirection;
//glm::vec3 cameraUp;
//GLboolean flag_perspective_projection = true;
//
////내가 만든 함수 와 변수
//GLvoid InitValue();
//GLvoid SetTransformMatrix();
//GLboolean flag_cull_face = false;
//GLboolean flag_depth_test = false;
//GLboolean flag_draw_line = false;
//GLvoid ChangeDegree(GLfloat);
//
////축 관련 함수 와 변수
//GLvoid DrawAxes();
//GLfloat cube_pos[8][3];
//GLfloat cube_color[6][3];
//GLuint cube_index[12][3];
//
//std::random_device rd;
//std::uniform_real_distribution<GLfloat> ufd(10.0f, 30.0f);
//std::uniform_int_distribution<int> uid(0, 1);
////TODO: 나중에 클래스 위치 옮기고 클래스 함수들 뺴내기
//class Block {
//public:
//	GLfloat S[3];
//	GLfloat T[3];
//	GLuint VAO, VBO[3];
//	GLvoid InitBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//	}
//	GLvoid init() {
//		S[X] = 10.0 / ObjectSize;
//		S[Y] = 4.0 / ObjectSize;
//		S[Z] = 10.0 / ObjectSize;
//		T[X] = ufd(rd), T[Y] = 0.0, T[Z] = ufd(rd);
//		if (uid(rd) == 0) T[X] *= -1;
//		if (uid(rd) == 0) T[Z] *= -1;
//		
//	}
//	GLvoid draw() {
//		glBindVertexArray(VAO);
//		GLfloat temp_color[8][3] = {0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4,0.4, };
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		{
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			
//			glm::mat4 Sc = glm::mat4(1.0f);
//			Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
//
//			glm::mat4 Trans = glm::mat4(1.0f);
//			Trans = glm::translate(Trans, glm::vec3(T[X], T[Y], T[Z]));
//			
//			TR = Trans * Sc * TR;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		}
//
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	}
//};
//GLboolean RobotCollideBlock();
//class Nose {
//public:
//	GLfloat S[3];
//	GLfloat T[3];
//	GLfloat fR[3];
//	GLfloat fT[3];
//	GLuint VAO, VBO[3];
//	GLvoid initBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//	}
//	GLvoid init() {
//		S[X] = 0.5 / ObjectSize;
//		S[Y] = 1.0 / ObjectSize;
//		S[Z] = 0.5 / ObjectSize;
//		T[X] = 0.0f, T[Y] = 28.5f, T[Z] = 3.0f;
//		fR[X] = 0.0f, fR[Y] = 0.0f, fR[Z] = 0.0f;
//		fT[X] = 0.0f, fT[Y] = 0.0f, fT[Z] = 0.0f;
//	}
//	GLvoid draw() {
//		glBindVertexArray(VAO);
//		GLfloat temp_color[8][3] = { 0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,};
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		{
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 Sc = glm::mat4(1.0f);
//			glm::mat4 Trans = glm::mat4(1.0f);
//			glm::mat4 fRot = glm::mat4(1.0f);
//			glm::mat4 fTrans = glm::mat4(1.0f);
//			fTrans = glm::translate(fTrans, glm::vec3(fT[X], fT[Y], fT[Z]));
//			Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
//
//			fRot = glm::rotate(fRot, glm::radians(fR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//			Trans = glm::translate(Trans, glm::vec3(T[X], T[Y], T[Z]));
//			TR = fTrans*fRot* Trans * Sc * TR;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		}
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	}
//};
//class Head {
//public:
//	GLfloat S[3];
//	GLfloat T[3];
//	GLfloat fR[3];
//	GLfloat fT[3];
//	Nose nose;
//	GLuint VAO, VBO[3];
//	GLvoid initBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//		nose.initBuffer();
//	}
//	GLvoid init() {
//		S[X] = 3.0 / ObjectSize;
//		S[Y] = 5.0 / ObjectSize;
//		S[Z] = 3.0 / ObjectSize;
//		T[X] = 0.0f, T[Y] = 25.0f, T[Z] = 0.0f;
//		fR[X] = 0.0f, fR[Y] = 0.0f, fR[Z] = 0.0f;
//		fT[X] = 0.0f, fT[Y] = 0.0f, fT[Z] = 0.0f;
//		nose.init();
//	}
//	GLvoid draw() {
//		glBindVertexArray(VAO);
//		GLfloat temp_color[8][3] = { 0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,0.0f,0.0f,0.5f,};
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		{
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 Sc = glm::mat4(1.0f);
//			glm::mat4 Trans = glm::mat4(1.0f);
//			glm::mat4 fRot = glm::mat4(1.0f);
//			glm::mat4 fTrans = glm::mat4(1.0f);
//			fTrans = glm::translate(fTrans, glm::vec3(fT[X], fT[Y], fT[Z]));
//			Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
//			fRot = glm::rotate(fRot, glm::radians(fR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//			Trans = glm::translate(Trans, glm::vec3(T[X], T[Y], T[Z]));
//			TR = fTrans*fRot*Trans * Sc * TR;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		}
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//
//		nose.draw();
//	}
//};
//
//class Leg {
//public:
//	GLfloat S[3];
//	GLfloat T[3];
//	GLfloat fR[3];
//	GLfloat fT[3];
//	GLfloat R[3];
//	GLuint VAO, VBO[3];
//	GLvoid initBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//	}
//
//	GLvoid init(int value) {
//		S[X] = S[Z] = 1.0/ObjectSize;
//		S[Y] = 5.0/ObjectSize;
//		if (value == LEFT) {
//			T[X] = -2.0f; T[Y] = 0.0f; T[Z] = 0.0f;
//		}
//		else if (value == RIGHT) {
//			T[X] = 2.0f; T[Y] = 0.0f; T[Z] = 0.0f;
//		}
//		fR[X] = 0.0f, fR[Y] = 0.0f, fR[Z] = 0.0f;
//		fT[X] = 0.0f, fT[Y] = 0.0f, fT[Z] = 0.0f;
//		R[X] = 0.0f, R[Y] = 0.0f, R[Z] = 0.0f;
//	}
//
//	GLvoid draw(int dir) {
//		glBindVertexArray(VAO);
//		if (dir == LEFT) {
//			GLfloat temp_color[8][3] = { 1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f };
//			glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//			glEnableVertexAttribArray(1);
//		}
//		else {
//			GLfloat temp_color[8][3] = { 0.8f,0.4f,0.357f,0.8f,0.4f,0.357f,0.8f,0.4f,0.357f,0.8f,0.4f,0.357f,0.8f,0.4f,0.357f,0.8f,0.4f,0.357f,0.8f,0.4f,0.357f,0.8f,0.4f,0.357f};
//			glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//			glEnableVertexAttribArray(1);
//		}
//		
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		{
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 Sc = glm::mat4(1.0f);
//			glm::mat4 Trans = glm::mat4(1.0f);
//			glm::mat4 fRot = glm::mat4(1.0f);
//			glm::mat4 fTrans = glm::mat4(1.0f);
//			glm::mat4 TtoAxes = glm::mat4(1.0f);
//			glm::mat4 Rx = glm::mat4(1.0f);
//			glm::mat4 TtoBack = glm::mat4(1.0f);
//			TtoAxes = glm::translate(TtoAxes, glm::vec3(0.0f,  -ObjectSize * S[Y], 0.0f));
//			Rx = glm::rotate(Rx, glm::radians(R[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//			TtoBack = glm::translate(TtoBack, glm::vec3(0.0f, ObjectSize * S[Y], 0.0f));
//
//			fTrans = glm::translate(fTrans, glm::vec3(fT[X], fT[Y], fT[Z]));
//			fRot = glm::rotate(fRot, glm::radians(fR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//			Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
//			
//			Trans = glm::translate(Trans, glm::vec3(T[X], T[Y], T[Z]));
//			TR = fTrans*fRot*Trans * (TtoBack*Rx*TtoAxes) * Sc * TR;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		}
//
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	}
//};
//
//class Arm {
//public:
//	GLfloat S[3];
//	GLfloat T[3];
//	GLfloat R[3]; 
//	GLfloat fR[3];
//	GLfloat fT[3];
//	GLuint VAO, VBO[3];
//	GLvoid initBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//	}
//
//	GLvoid init(int value) {
//		S[X] = S[Z] = 1.0 / ObjectSize;
//		S[Y] = 5.0 / ObjectSize;
//		if (value == LEFT) {
//			R[X] = 0.0f, R[Y] = 0.0f, R[Z] = -25.0f;
//			T[X] = -4.5; T[Y] = 13.0f; T[Z] = 0.0f;
//			
//		}
//		else if (value == RIGHT) {
//			R[X] = 0.0f, R[Y] = 0.0f, R[Z] = 25.0f;
//			T[X] = 4.5; T[Y] = 13.0f; T[Z] = 0.0f;
//		}
//		fR[X] = 0.0f, fR[Y] = 0.0f, fR[Z] = 0.0f;
//		fT[X] = 0.0f, fT[Y] = 0.0f, fT[Z] = 0.0f;
//
//	}
//
//	GLvoid draw(int dir) {
//		glBindVertexArray(VAO);
//		if (dir == LEFT) {
//			GLfloat temp_color[8][3] = { 0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f,0.427f, 0.16f,0.396f, };
//			glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//			glEnableVertexAttribArray(1);
//		}
//		else {
//			GLfloat temp_color[8][3] = { 0.0f,0.20f,0.345f,0.0f,0.20f,0.345f,0.0f,0.20f,0.345f,0.0f,0.20f,0.345f,0.0f,0.20f,0.345f,0.0f,0.20f,0.345f,0.0f,0.20f,0.345f,0.0f,0.20f,0.345f};
//			glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//			glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//			glEnableVertexAttribArray(1);
//		}
//
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		{
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 TtoAxes = glm::mat4(1.0f);
//			glm::mat4 Rz = glm::mat4(1.0f);
//			glm::mat4 TtoBack = glm::mat4(1.0f);
//			glm::mat4 fRot = glm::mat4(1.0f);
//			glm::mat4 fTrans = glm::mat4(1.0f);
//			fTrans = glm::translate(fTrans, glm::vec3(fT[X], fT[Y], fT[Z]));
//			fRot = glm::rotate(fRot, glm::radians(fR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//			TtoAxes = glm::translate(TtoAxes, glm::vec3(ObjectSize*S[X], -2 * ObjectSize*S[Y], 0.0f));
//			Rz = glm::rotate(Rz, glm::radians(R[Z]), glm::vec3(0.0f, 0.0f, 1.0f));
//			TtoBack = glm::translate(TtoBack, glm::vec3(-ObjectSize*S[X], +2 * ObjectSize*S[Y], 0.0f));
//			
//
//			glm::mat4 Sc = glm::mat4(1.0f);
//			glm::mat4 Trans = glm::mat4(1.0f);
//			Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
//
//			glm::mat4 TtoAxes2 = glm::mat4(1.0f);
//			glm::mat4 Rx = glm::mat4(1.0f);
//			glm::mat4 TtoBack2 = glm::mat4(1.0f);
//			TtoAxes2 = glm::translate(TtoAxes2, glm::vec3(0.0f, -2 * ObjectSize * S[Y], 0.0f));
//			Rx = glm::rotate(Rx, glm::radians(R[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//			TtoBack2 = glm::translate(TtoBack2, glm::vec3(0.0f, +2 * ObjectSize * S[Y], 0.0f));
//
//			Trans = glm::translate(Trans, glm::vec3(T[X], T[Y], T[Z]));
//			TR = fTrans*fRot*Trans * (TtoBack2*Rx*TtoAxes2) * (TtoBack * Rz * TtoAxes) * Sc * TR;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		}
//
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	}
//};
//
//class Body {
//public:
//	GLfloat S[3];
//	GLfloat T[3];
//	GLfloat fR[3];
//	GLfloat fT[3];
//	GLuint VAO, VBO[3];
//	GLvoid initBuffer() {
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(3, VBO);
//	}
//
//	GLvoid init() {
//		S[X] = 5.0 / ObjectSize;
//		S[Y] = 10.0 / ObjectSize;
//		S[Z] = 3.0 / ObjectSize;
//		T[X] = 0.0f; T[Y] = 5.0f; T[Z] = 0.0f;
//		fR[X] = 0.0f, fR[Y] = 0.0f, fR[Z] = 0.0f;
//		fT[X] = 0.0f, fT[Y] = 0.0f, fT[Z] = 0.0f;
//
//	}
//	GLvoid draw() {
//		glBindVertexArray(VAO);
//		GLfloat temp_color[8][3] = { 0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,0.55f,0.3f,0.14f,};
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glEnableVertexAttribArray(1);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos), cube_pos, GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//		glEnableVertexAttribArray(0);
//
//		{
//			//model 변환
//			glm::mat4 TR = glm::mat4(1.0f);
//			glm::mat4 Sc = glm::mat4(1.0f);
//			glm::mat4 Trans = glm::mat4(1.0f);
//			Sc = glm::scale(Sc, glm::vec3(S[X], S[Y], S[Z]));
//			glm::mat4 fRot = glm::mat4(1.0f);
//			glm::mat4 fTrans = glm::mat4(1.0f);
//			fTrans = glm::translate(fTrans, glm::vec3(fT[X], fT[Y], fT[Z]));
//			fRot = glm::rotate(fRot, glm::radians(fR[Y]), glm::vec3(0.0f, 1.0f, 0.0f));
//			Trans = glm::translate(Trans, glm::vec3(T[X], T[Y], T[Z]));
//			TR = fTrans* fRot* Trans * Sc * TR;
//			unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//		}
//
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
//	}
//};
//
//Block block;
//class Robot {
//public:
//	Head head;
//	Leg leg[2];
//	Arm arm[2];
//	Body body;
//	GLboolean armleg_forward = true;
//	GLfloat armleg_degree = 0.0f;
//	GLfloat gravity = 0.0f;
//
//	GLvoid init() {
//		head.init();
//		leg[LEFT].init(LEFT), leg[RIGHT].init(RIGHT);
//		arm[LEFT].init(LEFT), arm[RIGHT].init(RIGHT);
//		body.init();
//		armleg_forward = true;
//		armleg_degree = 0.0f;
//		gravity = 0.0f;
//	}
//	GLvoid InitBuffer() {
//		head.initBuffer();
//		leg[LEFT].initBuffer(), leg[RIGHT].initBuffer();
//		arm[LEFT].initBuffer(), arm[RIGHT].initBuffer();
//		body.initBuffer();
//
//	}
//	GLvoid draw() {
//		leg[LEFT].draw(LEFT);
//		leg[RIGHT].draw(RIGHT);
//		body.draw();
//		arm[LEFT].draw(LEFT);
//		arm[RIGHT].draw(RIGHT);
//		head.draw();
//	}
//	GLvoid Rotate(int xyz, GLfloat degree) {
//		head.fR[xyz] = degree;
//		head.nose.fR[xyz] = degree;
//		leg[LEFT].fR[xyz] =degree;
//		leg[RIGHT].fR[xyz] =degree;
//		arm[LEFT].fR[xyz] = degree;
//		arm[RIGHT].fR[xyz] = degree;
//		body.fR[xyz] = degree;
//		
//	}
//	GLvoid PlusTranslate(int xyz, GLfloat figure) {
//		head.fT[xyz] += figure;
//		head.nose.fT[xyz] += figure;
//		leg[LEFT].fT[xyz] += figure;
//		leg[RIGHT].fT[xyz] += figure;
//		arm[LEFT].fT[xyz] += figure;
//		arm[RIGHT].fT[xyz] += figure;
//		body.fT[xyz] += figure;
//
//		if (RobotCollideBlock() && xyz != Y) {
//			head.fT[xyz] -= figure;
//			head.nose.fT[xyz] -= figure;
//			leg[LEFT].fT[xyz] -= figure;
//			leg[RIGHT].fT[xyz] -= figure;
//			arm[LEFT].fT[xyz] -= figure;
//			arm[RIGHT].fT[xyz] -= figure;
//			body.fT[xyz] -= figure;
//			return;
//		}
//
//		if (head.fT[xyz] >= ObjectSize) {
//			head.fT[xyz] += -2*ObjectSize;
//			head.nose.fT[xyz] += -2*ObjectSize;
//			leg[LEFT].fT[xyz] += -2*ObjectSize;
//			leg[RIGHT].fT[xyz] += -2*ObjectSize;
//			arm[LEFT].fT[xyz] += -2*ObjectSize;
//			arm[RIGHT].fT[xyz] += -2*ObjectSize;
//			body.fT[xyz] += -2*ObjectSize;
//		}
//		else if (head.fT[xyz] <= -ObjectSize) {
//			head.fT[xyz] += 2 * ObjectSize;
//			head.nose.fT[xyz] += 2 * ObjectSize;
//			leg[LEFT].fT[xyz] += 2 * ObjectSize;
//			leg[RIGHT].fT[xyz] += 2 * ObjectSize;
//			arm[LEFT].fT[xyz] += 2 * ObjectSize;
//			arm[RIGHT].fT[xyz] += 2 * ObjectSize;
//			body.fT[xyz] += 2 * ObjectSize;
//		}
//		
//
//		if (xyz != Y) {
//			if (armleg_forward) {
//				armleg_degree += 5.0f;
//				if (armleg_degree >= 25.0f) {
//					armleg_degree = 25.0f;
//					armleg_forward = false;
//				}
//			}
//			else {
//				armleg_degree -= 5.0f;
//				if (armleg_degree <= -25.0f) {
//					armleg_degree = -25.0f;
//					armleg_forward = true;
//				}
//			}
//			arm[LEFT].R[X] = armleg_degree;
//			arm[RIGHT].R[X] = -armleg_degree;
//			leg[LEFT].R[X] = -armleg_degree;
//			leg[RIGHT].R[X] = armleg_degree;
//		}
//		
//	}
//};
//Side side[6];
//Robot robot;
////타이머 관련 변수 및 함수
//int TimerSpeed = 16;
//GLvoid MoveFrontSide(int value);
//GLboolean flag_move_front_side[2];
//GLvoid RobotGravity(int value);
//GLboolean flag_robot_gravity[2];
//GLboolean RobotCollideBlock() {
//	GLboolean check_x = false, check_y = false, check_z = false;
//
//	//std::cout << abs(block.T[X] - robot.body.fT[X]) << std::endl;
//	if (abs(block.T[X] - robot.body.fT[X]) <= abs(block.S[X] * ObjectSize + robot.body.S[X]*ObjectSize)) {
//		check_x = true;
//	}
//	if (abs(block.T[Z] - robot.body.fT[Z]) <= abs(block.S[Z] * ObjectSize + robot.body.S[Z] * ObjectSize)) {
//		check_z = true;
//	}
//	if (abs(block.T[Y] - robot.body.fT[Y]) <= abs(block.S[Y] * ObjectSize*2)) {
//		check_y = true;
//	}
//	//std::cout << "현재 로봇 높이: " << robot.body.fT[Y] << std::endl;
//	if (check_x && check_y && check_z) {
//		
//		return true;
//	}
//	return false;
//}
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
//
//
//	InitValue();
//	InitShader();
//	InitBuffer();
//
//	glutDisplayFunc(drawScene); // 출력 함수의 지정
//	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//	glutKeyboardFunc(KeyBoard);
//	glutMouseFunc(Mouse);
//	glutMotionFunc(MouseMove);
//	glutSpecialFunc(SpecialKeyboard);
//
//	glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene() {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	SetTransformMatrix();
//
//	for (int i = 0; i < 6; ++i) {
//		side[i].draw();
//	}
//	robot.draw();
//	block.draw();
//	glutSwapBuffers(); // 화면에 출력하기
//}
//
//GLvoid KeyBoard(unsigned char key, int x, int y) {
//	switch (key) {
//	case 'Q':
//	case 'q':
//		glutLeaveMainLoop();
//		break;
//	case 'x':	//카메라 왼쪽 이동
//		cameraPos.x -= WorldSize / 100;
//		std::cout << "x: " << cameraPos.x << std::endl;
//		break;
//	case 'X':	//카메라 오른쪽 이동
//		cameraPos.x += WorldSize / 100;
//		std::cout << "x: " << cameraPos.x << std::endl;
//		break;
//	case '.':	//카메라 위쪽 이동
//		cameraPos.y += WorldSize / 100;
//		std::cout << "y: " << cameraPos.y << std::endl;
//		break;
//	case '/':	//카메라 아래쪽 이동
//		cameraPos.y -= WorldSize / 100;
//		std::cout << "y: " << cameraPos.y << std::endl;
//		break;
//	case 'O':	//무대 오픈
//	case 'o':
//		if (flag_move_front_side[IS_ON]) {
//			printf("이미 무대 관련 동작이 진행중이라 진행할 수 없습니다.\n");
//			break;
//		}
//		else {
//			printf("무대 내려가기 시작\n");
//			glutTimerFunc(TimerSpeed, MoveFrontSide, OPEN);
//			flag_move_front_side[IS_ON] = true;
//		}
//		break;
//	case 'P':	//무대 닫기
//	case 'p':
//		if (flag_move_front_side[IS_ON]) {
//			printf("이미 무대 관련 동작이 진행중이라 진행할 수 없습니다.\n");
//			break;
//		}
//		else {
//			printf("무대 올라가기 시작\n");
//			glutTimerFunc(TimerSpeed, MoveFrontSide, CLOSE);
//			flag_move_front_side[IS_ON] = true;
//		}
//		break;
//	case 'Y':
//	{
//		glm::vec4 CD = glm::vec4(cameraDirection, 1.0f);
//		glm::vec4 CP = glm::vec4(cameraPos, 1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		Ry = glm::rotate(Ry, glm::radians(3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		CD = Ry * CD;
//		CP = Ry * CP;
//		cameraDirection[X] = CD[X], cameraDirection[Y] = CD[Y], cameraDirection[Z] = CD[Z];
//		cameraPos[X] = CP[X], cameraPos[Y] = CP[Y], cameraPos[Z] = CP[Z];
//	}
//		break;
//	case 'y': 
//	{
//		glm::vec4 CD = glm::vec4(cameraDirection, 1.0f);
//		glm::vec4 CP = glm::vec4(cameraPos, 1.0f);
//		glm::mat4 Ry = glm::mat4(1.0f);
//		Ry = glm::rotate(Ry, glm::radians(-3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		CD = Ry * CD;
//		CP = Ry * CP;
//		cameraDirection[X] = CD[X], cameraDirection[Y] = CD[Y], cameraDirection[Z] = CD[Z];
//		cameraPos[X] = CP[X], cameraPos[Y] = CP[Y], cameraPos[Z] = CP[Z];
//	}
//	case 'W':
//	case 'w':
//		robot.Rotate(Y, 180.0f);
//		robot.PlusTranslate(Z, -2.0f);
//		break;
//	case 'A':
//	case 'a':
//		robot.Rotate(Y, -90.0f);
//		robot.PlusTranslate(X, -2.0f);
//		break;
//	case 'S':
//	case 's':
//		robot.Rotate(Y, 0.0f);
//		robot.PlusTranslate(Z, 2.0f);
//		break;
//	case 'D':
//	case 'd':
//		robot.Rotate(Y, 90.0f);
//		robot.PlusTranslate(X, 2.0f);
//		break;
//	case 'j':
//		if (flag_robot_gravity[IS_ON]) {
//			printf("현재 로봇이 뛰고 있어 점프를 못합니다.\n");
//			break;
//		}
//		else {
//			robot.gravity = 5.0f;
//			glutTimerFunc(TimerSpeed, RobotGravity, 0);
//			flag_robot_gravity[IS_ON] = true;
//		}
//		break;
//	case 'i':
//		InitValue();
//		break;
//	}
//
//	glutPostRedisplay();
//}
//
//GLvoid SpecialKeyboard(int key, int x, int y) {
//
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
//			std::cout << "z: " << cameraPos.z << std::endl;
//			break;
//		case 4:			//마우스휠 아래로 역할
//			cameraPos.z += WorldSize / 100;	//카메라 바깥쪽으로
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
//GLvoid MouseMove(int x, int y) {
//
//	glutPostRedisplay();
//}
//
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
//{
//	glViewport(0, 0, w, h);
//}
//GLvoid InitBuffer() {
//	for (int i = 0; i < 6; ++i) {
//		glGenVertexArrays(1, &side[i].VAO);
//		glGenBuffers(3, side[i].VBO);
//	}
//	robot.InitBuffer();
//	block.InitBuffer();
//}
//GLvoid InitValue() {
//	{
//		glEnable(GL_DEPTH_TEST);
//		flag_depth_test = true;
//		/*glEnable(GL_CULL_FACE);
//		flag_cull_face = true;*/
//		/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		flag_draw_line = true;*/
//	}
//
//	{
//		cameraPos = glm::vec3(0.0f, ObjectSize, WorldSize*1.5);
//		cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
//		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//		flag_perspective_projection = true;
//	}
//
//	{//cube 초기화
//		if (cube_pos[0][0] == 0) {	//초기한번만 하도록
//			cube_pos[0][X] = cube_pos[1][X] = cube_pos[4][X] = cube_pos[7][X] = -ObjectSize;
//			cube_pos[2][X] = cube_pos[3][X] = cube_pos[5][X] = cube_pos[6][X] = ObjectSize;
//			cube_pos[0][Y] = cube_pos[1][Y] = cube_pos[2][Y] = cube_pos[3][Y] = ObjectSize*2;
//			cube_pos[4][Y] = cube_pos[5][Y] = cube_pos[6][Y] = cube_pos[7][Y] = 0;
//			cube_pos[0][Z] = cube_pos[3][Z] = cube_pos[6][Z] = cube_pos[7][Z] = -ObjectSize;
//			cube_pos[1][Z] = cube_pos[2][Z] = cube_pos[4][Z] = cube_pos[5][Z] = ObjectSize;
//	
//			cube_index[0][X] = 0, cube_index[0][Y] = 1, cube_index[0][Z] = 2;
//			cube_index[1][X] = 0, cube_index[1][Y] = 2, cube_index[1][Z] = 3;
//			cube_index[2][X] = 1, cube_index[2][Y] = 4, cube_index[2][Z] = 5;
//			cube_index[3][X] = 1, cube_index[3][Y] = 5, cube_index[3][Z] = 2;
//			cube_index[4][X] = 2, cube_index[4][Y] = 5, cube_index[4][Z] = 6;
//			cube_index[5][X] = 2, cube_index[5][Y] = 6, cube_index[5][Z] = 3;
//			cube_index[6][X] = 3, cube_index[6][Y] = 6, cube_index[6][Z] = 7;
//			cube_index[7][X] = 3, cube_index[7][Y] = 7, cube_index[7][Z] = 0;
//			cube_index[8][X] = 0, cube_index[8][Y] = 7, cube_index[8][Z] = 4;
//			cube_index[9][X] = 0, cube_index[9][Y] = 4, cube_index[9][Z] = 1;
//			cube_index[10][X] = 6, cube_index[10][Y] = 5, cube_index[10][Z] = 4;
//			cube_index[11][X] = 6, cube_index[11][Y] = 4, cube_index[11][Z] = 7;
//	
//			cube_color[0][R] = 1.0f, cube_color[0][G] = 0.0f, cube_color[0][B] = 0.0f;
//			cube_color[1][R] = 0.0f, cube_color[1][G] = 1.0f, cube_color[1][B] = 0.0f;
//			cube_color[2][R] = 0.0f, cube_color[2][G] = 0.0f, cube_color[2][B] = 1.0f;
//			cube_color[3][R] = 0.1f, cube_color[3][G] = 0.1f, cube_color[3][B] = 0.0f;
//			cube_color[4][R] = 0.0f, cube_color[4][G] = 1.0f, cube_color[4][B] = 1.0f;
//			cube_color[5][R] = 1.0f, cube_color[5][G] = 1.0f, cube_color[5][B] = 1.0f;
//			
//		}
//	}
//	
//
//	{//side init
//		for (int i = 0; i < 6; ++i) {
//			side[i].init(i);
//		}
//	}
//
//	{//robot 관련
//		robot.init();
//	}
//
//	{
//		block.init();
//	}
//
//	{
//		if (flag_robot_gravity[IS_ON]) {
//			flag_robot_gravity[TURN_OFF] = true;
//		}
//	}
//}
//
//GLvoid Side::init(int idx) {
//	switch (idx) {
//	case 0:
//		pos[0][X] = cube_pos[0][X], pos[0][Y] = cube_pos[0][Y], pos[0][Z] = cube_pos[0][Z];
//		pos[1][X] = cube_pos[1][X], pos[1][Y] = cube_pos[1][Y], pos[1][Z] = cube_pos[1][Z];
//		pos[2][X] = cube_pos[2][X], pos[2][Y] = cube_pos[2][Y], pos[2][Z] = cube_pos[2][Z];
//		pos[3][X] = cube_pos[3][X], pos[3][Y] = cube_pos[3][Y], pos[3][Z] = cube_pos[3][Z];
//		
//		break;
//	case 1:
//		pos[0][X] = cube_pos[1][X], pos[0][Y] = cube_pos[1][Y], pos[0][Z] = cube_pos[1][Z];
//		pos[1][X] = cube_pos[4][X], pos[1][Y] = cube_pos[4][Y], pos[1][Z] = cube_pos[4][Z];
//		pos[2][X] = cube_pos[5][X], pos[2][Y] = cube_pos[5][Y], pos[2][Z] = cube_pos[5][Z];
//		pos[3][X] = cube_pos[2][X], pos[3][Y] = cube_pos[2][Y], pos[3][Z] = cube_pos[2][Z];
//		R[X] = 90.0f;
//		break;
//	case 2:
//		pos[0][X] = cube_pos[2][X], pos[0][Y] = cube_pos[2][Y], pos[0][Z] = cube_pos[2][Z];
//		pos[1][X] = cube_pos[5][X], pos[1][Y] = cube_pos[5][Y], pos[1][Z] = cube_pos[5][Z];
//		pos[2][X] = cube_pos[6][X], pos[2][Y] = cube_pos[6][Y], pos[2][Z] = cube_pos[6][Z];
//		pos[3][X] = cube_pos[3][X], pos[3][Y] = cube_pos[3][Y], pos[3][Z] = cube_pos[3][Z];
//		
//		break;
//	case 3:
//		pos[0][X] = cube_pos[3][X], pos[0][Y] = cube_pos[3][Y], pos[0][Z] = cube_pos[3][Z];
//		pos[1][X] = cube_pos[6][X], pos[1][Y] = cube_pos[6][Y], pos[1][Z] = cube_pos[6][Z];
//		pos[2][X] = cube_pos[7][X], pos[2][Y] = cube_pos[7][Y], pos[2][Z] = cube_pos[7][Z];
//		pos[3][X] = cube_pos[0][X], pos[3][Y] = cube_pos[0][Y], pos[3][Z] = cube_pos[0][Z];
//		
//		break;
//	case 4:
//		pos[0][X] = cube_pos[0][X], pos[0][Y] = cube_pos[0][Y], pos[0][Z] = cube_pos[0][Z];
//		pos[1][X] = cube_pos[7][X], pos[1][Y] = cube_pos[7][Y], pos[1][Z] = cube_pos[7][Z];
//		pos[2][X] = cube_pos[4][X], pos[2][Y] = cube_pos[4][Y], pos[2][Z] = cube_pos[4][Z];
//		pos[3][X] = cube_pos[1][X], pos[3][Y] = cube_pos[1][Y], pos[3][Z] = cube_pos[1][Z];
//		
//		break;
//	case 5:
//		pos[0][X] = cube_pos[7][X], pos[0][Y] = cube_pos[7][Y], pos[0][Z] = cube_pos[7][Z];
//		pos[1][X] = cube_pos[4][X], pos[1][Y] = cube_pos[4][Y], pos[1][Z] = cube_pos[4][Z];
//		pos[2][X] = cube_pos[5][X], pos[2][Y] = cube_pos[5][Y], pos[2][Z] = cube_pos[5][Z];
//		pos[3][X] = cube_pos[6][X], pos[3][Y] = cube_pos[6][Y], pos[3][Z] = cube_pos[6][Z];
//		break;
//	}
//	for (int i = 0; i < 3; ++i) {
//		color[i] = cube_color[idx][i];
//	}
//	index[0][0] = 0, index[0][1] = 1, index[0][2] = 2;
//	index[1][0] = 0, index[1][1] = 2, index[1][2] = 3;
//
//	R[0] = 0.0f, R[1] = 0.0f, R[2] = 0.0f;
//	//TODO: 나중에 지우기
//	if (idx == 1) R[X] = 90.0f;
//}
//
//GLvoid Side::draw() {
//	glBindVertexArray(VAO);
//	GLfloat temp_color[4][3] = {
//		color[RGB::R],color[G],color[B],
//		color[RGB::R],color[G],color[B],
//		color[RGB::R],color[G],color[B],
//		color[RGB::R],color[G],color[B]
//	};
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(temp_color), temp_color, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX]);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(0);
//	
//	{
//		//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		if (R[X] != 0.0f) {
//			glm::mat4 firstT = glm::mat4(1.0f);
//			glm::mat4 backT = glm::mat4(1.0f);
//			glm::mat4 Rx = glm::mat4(1.0f);
//			
//			firstT = glm::translate(firstT, glm::vec3(0.0f, 0.0f, -ObjectSize));
//			Rx = glm::rotate(Rx, glm::radians(R[X]), glm::vec3(1.0f, 0.0f, 0.0f));
//			backT = glm::translate(backT, glm::vec3(0.0f, 0.0f, ObjectSize));
//
//			TR = backT * Rx * firstT * TR;
//		}
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//	
//	
//	glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_INT, (void*)0);
//}
//
//GLvoid ChangeDegree(GLfloat degree) {
//	if (degree < 0.0f) {
//		degree += 360.0f;
//	}
//	else {
//		degree -= 360.0f;
//	}
//}
//
//GLvoid MoveFrontSide(int value) {
//	if (flag_move_front_side[TURN_OFF]) {
//		flag_move_front_side[TURN_OFF] = false;
//		flag_move_front_side[IS_ON] = false;
//		return;
//	}
//	GLfloat rotatespeed = 0.5;
//	switch (value) {
//	case OPEN:
//		side[1].R[X] += rotatespeed;
//		if (side[1].R[X] > 90) {
//			side[1].R[X] = 90;
//			flag_move_front_side[TURN_OFF] = true;
//		}
//		break;
//
//	case CLOSE:
//		side[1].R[X] -= rotatespeed;
//		if (side[1].R[X] < 0) {
//			side[1].R[X] = 0;
//			flag_move_front_side[TURN_OFF] = true;
//		}
//		break;
//	}
//	glutPostRedisplay();
//	glutTimerFunc(TimerSpeed, MoveFrontSide, value);
//}
//
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
//	fragmentsource = filetobuf("fragment.glsl");
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
//GLvoid SetTransformMatrix() {
//	{//model 변환
//		glm::mat4 TR = glm::mat4(1.0f);
//		
//		unsigned int modelLocation = glGetUniformLocation(s_program, "model");
//		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
//	}
//
//	{//카메라 변환
//		glm::mat4 view = glm::mat4(1.0f);
//		view = glm::lookAt(cameraPos, cameraPos+ cameraDirection, cameraUp);
//		unsigned int viewLocation = glGetUniformLocation(s_program, "view");
//		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//	}
//	
//	{//투영변환
//		glm::mat4 projection = glm::mat4(1.0f);
//		if (flag_perspective_projection) {	//원근
//			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, (GLfloat)WorldSize*3);
//			//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -WorldSize / 10));
//		}
//		else {	//직각
//			GLfloat halfsize = WorldSize;
//			projection = glm::ortho(-halfsize, halfsize, -halfsize, halfsize, 0.0f, halfsize*2);
//		}
//		
//
//		unsigned int projectLoc = glGetUniformLocation(s_program, "projection");
//		glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
//	}
//}
//
//GLvoid RobotGravity(int value) {
//	if (robot.head.fT[Y] < 0) {
//		robot.PlusTranslate(Y, -robot.head.fT[Y]);
//		robot.gravity = 0.0f;
//		flag_robot_gravity[IS_ON] = false;
//		glutPostRedisplay();
//		return;
//	}
//	
//	robot.gravity -= 0.3;
//	
//	robot.PlusTranslate(Y, robot.gravity);
//	if (RobotCollideBlock()) {
//		robot.PlusTranslate(Y, -robot.gravity + 0.01);
//		robot.gravity = 0.0f;
//	}
//	glutPostRedisplay();
//	glutTimerFunc(TimerSpeed, RobotGravity, value);
//}
