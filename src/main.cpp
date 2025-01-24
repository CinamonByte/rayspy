#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>	//header file for sonething
#include <GLFW/glfw3.h>	//window, keyboard and mouse inputs
#include <glm/glm.hpp>
#include <filesystem>
#include<iostream>
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

	window = glfwCreateWindow(1024,768, "tutorial 01", NULL, NULL);
	glfwMakeContextCurrent(window);	//assign context to current windows so other functions can work on it, you can switch context to focus on different windows
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}
	if(glewInit()!= GLEW_OK){
		fprintf(stderr, "failed to init GLEW\n");
	}

	glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

	glfwSetInputMode(window, GLFW_STICKY_KEYS,GL_TRUE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("../src/SimpleVertexShader.txt", "../src/SimpleFragmentShader.txt");


	static const GLfloat g_vertex_buffer_data[]={
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint vertexbuffer;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer); 
	glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);
	do{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programID);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0,3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();


	}while (glfwGetKey(window, GLFW_KEY_ESCAPE)!= GLFW_PRESS && glfwWindowShouldClose(window)==0);
}

