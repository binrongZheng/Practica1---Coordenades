//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "myShader.h"
//para textura
#include <SOIL.h>
//para vector
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;
using namespace std;
const GLint WIDTH = 800, HEIGHT = 800;
bool WIREFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void DrawVAO();

GLfloat mixValor;
GLfloat radX = 0;
GLfloat radY = 0;

int main() {
	
	//initGLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	GLFWwindow* window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cout << "Error al inicializar glew" << endl;
		glfwTerminate();
		return NULL;
	}

	//set function when callback
	glfwSetKeyCallback(window, key_callback);

	//set windows and viewport
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);

	//fondo	
	
	//cargamos los shader
//	Shader myShader ("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
//	Shader myShader("./src/textureVertex.vertexshader", "./src/textureFragment.fragmentshader");
	glEnable(GL_DEPTH_TEST);
	Shader myShader("./src/coordVertex.vertexshader", "./src/coordFragment.fragmentshader");

	GLfloat VertexBufferObject[] = {//6*2*3
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

	};

	vec3 FragmentBufferObject[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Crear los VBO, VAO y EBO	//Declarar el VBO y el EBO	
	GLuint VBO, VAO;
	//declarar vector
	mat4 matriz;

	matriz = scale(matriz, vec3(0.5, -0.5, 0.5));

	
	//reservar memoria para el VAO, VBO y EBO
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	
	//Establecer el objeto
	glBindVertexArray(VAO);{
		//Enlazar el buffer con openGL
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), VertexBufferObject, GL_STATIC_DRAW);

		//Establecer las propiedades de los vertices

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		//glEnable(GL_DEPTH_TEST);
		
		//liberar el buffer
	} 
	//liberar el buffer de vertices
	glBindVertexArray(0);

	//crear textura1
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	/////////////////////////////////////////////////////////////////TEXTTURA 1////////////////////////////////////////////////////////////////
	//set texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//carga image
	int width, height;
	unsigned char* image1 = SOIL_load_image("./src/texture.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);

	//liberar la image
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);
	/////////////////////////////////////////////////////////////////TEXTTURA 2////////////////////////////////////////////////////////////////
	//Establecer las propiedades de los vertices
	GLuint texture2;
	glGenTextures(1,&texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//set texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//carga image
	int height2, width2;
	unsigned char* image2 = SOIL_load_image("./src/minecraft.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);

	//liberar la image
	SOIL_free_image_data(image2);

	//liberar el puntero
	glBindTexture(GL_TEXTURE_2D, 0);

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Establecer el color de fondo
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Camara
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);
		glUniform1i(glGetUniformLocation(myShader.Program,"ourTexture1"),0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture2"),1);

		//establecer el shader
		myShader.USE();
		mat4 proj;		mat4 view;		mat4 model;
		
		proj= perspective(45.f, (float)width / (float)height, 0.1f, 100.f);
		view = glm::translate(view, vec3(0.0f, 0.0f, -3.f));
	
		GLint modelLoc = glGetUniformLocation(myShader.Program,"model");
		GLint viewLoc = glGetUniformLocation(myShader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
		GLint projectionLoc = glGetUniformLocation(myShader.Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(proj));

		GLfloat variableShader = glGetUniformLocation(myShader.Program,"Valor");
		glUniform1f(variableShader, mixValor);

		//matrix
		GLfloat transformValor = glGetUniformLocation(myShader.Program, "transform");
		glUniformMatrix4fv(transformValor, 1, GL_FALSE, value_ptr(matriz));

		GLfloat timeValue = glfwGetTime()*100.f;
		//pintar el VAO
		glBindVertexArray(VAO); {
			for (GLuint i = 0; i < 10; i++)
			{
				if (i==0) {
					model = translate(model, FragmentBufferObject[i]);
					model = rotate(model, radX, vec3(0.0f, 1.0f, 0.0f));
					model = rotate(model, radY, vec3(1.0f, 0.0f, 0.0f));
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				else{
					mat4 model;
					model = translate(model, FragmentBufferObject[i]);
					model = rotate(model, radians(timeValue), vec3(1.0f, 0.0f, 0.0f));
					model = rotate(model, radians(timeValue), vec3(0.0f, 1.0f, 0.0f));
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	//liberar memoria texturas
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void DrawVAO() {
	
	if (WIREFRAME) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		WIREFRAME = !WIREFRAME;
	if (key == GLFW_KEY_1 && mixValor + 0.02 <= 1)
		mixValor += 0.02;
	if (key == GLFW_KEY_2 && mixValor - 0.02 >= 0)
		mixValor -= 0.02;
	if (key == GLFW_KEY_LEFT )
		radX -= 0.05;
	if (key == GLFW_KEY_RIGHT)
		radX += 0.05;
	if (key == GLFW_KEY_UP )
		radY -= 0.05;
	if (key == GLFW_KEY_DOWN )
		radY += 0.05;
}
