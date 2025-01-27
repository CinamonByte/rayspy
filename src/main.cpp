#include <GL/glew.h>	//header file for sonething
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>	//window, keyboard and mouse inputs
#include <glm/glm.hpp>
#include <filesystem>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/transform.hpp>

using namespace glm;
#include <common/shader.hpp>
GLFWwindow* window;
int main(void){
	std::cout<<"current dir:"<<std::filesystem::current_path();

	if ( !glfwInit()){
		fprintf(stderr, "failed to initialize GLFW\n");
		return -1;

	}
	//setting glfw stuff
	glfwWindowHint(GLFW_SAMPLES,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(400,400, "RaySpy", NULL, NULL);
	glfwMakeContextCurrent(window);	//assign context to current windows so other functions can work on it, you can switch context to focus on different windows
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}
	/*glfwSetWindowSizeLimits(window, 1024, 768, 1024, 768);*/
	if(glewInit()!= GLEW_OK){
		fprintf(stderr, "failed to init GLEW\n");
	}

	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

	glfwSetInputMode(window, GLFW_STICKY_KEYS,GL_TRUE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("../shaders/SimpleVertexShader.txt", "../shaders/SimpleFragmentShader.txt");


	static const GLfloat g_vertex_buffer_data[]={
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer); 
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);

	mat4 MyMatrix;
	vec4 MyVector;
	vec4 transformed = MyMatrix * MyVector;
	do{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, (void*)0);
		//describes how the array is structured
		//position in array, no of components in aray (x,y,z), data type, if we want to normalize data, offset till next item in memory, offset location of item within the array
		glDrawArrays(GL_TRIANGLES, 0,3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();


	}while (glfwGetKey(window, GLFW_KEY_ESCAPE)!= GLFW_PRESS && glfwWindowShouldClose(window)==0);
}

