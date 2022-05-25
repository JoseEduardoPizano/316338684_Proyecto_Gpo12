#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(10.0f, 6.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

float tiempo;
float rotacion;


bool ventana = false;
float transVent1;
float transVent2;
float transVent3;
float transVent4;
float transVent5;
float transVent6;
float transVent7;

bool ventana2 = false;
float rotVent1;
float rotVent2;
float rotVent3;
float rotVent4;
float rotVent5;
float rotVent6;
float rotVent7;
float rotVent8;
bool ventAbrir1  = false;
bool ventCerrar1 = false;
bool ventAbrir2 = false;
bool ventCerrar2 = false;
bool ventAbrir3 = false;
bool ventCerrar3 = false;
bool ventAbrir4 = false;
bool ventCerrar4 = false;
bool ventAbrir5 = false;
bool ventCerrar5 = false;
bool ventAbrir6 = false;
bool ventCerrar6 = false;
bool ventAbrir7 = false;
bool ventCerrar7 = false;
bool ventAbrir8 = false;
bool ventCerrar8 = false;

bool puerta = false;
float rotPuerta1;
float rotPuerta2;
bool zaguanAbrir  = false;
bool zaguanCerrar = false;
bool puertaAbrir = false;
bool puertaCerrar = false;

bool piscinaEncendida = false;

float x;
float y;
float z;



// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Animacion Sencilla", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp2.vs", "Shaders/lamp2.frag");
	Shader Anim("Shaders/anim.vs", "Shaders/anim.frag");
	Shader Anim2("Shaders/anim2.vs", "Shaders/anim2.frag");
	
	Model Piso((char*)"Models/Sea/Sea.obj");
	Model SV((char*)"Models/Sea/salvavidas.obj");

	Model Barra((char*)"Models/Objetos2/Barra.obj");
	Model Casa((char*)"Models/Objetos2/Casa.obj");
	Model Mesa((char*)"Models/Objetos2/Mesa.obj");
	Model Silla((char*)"Models/Objetos2/Silla1.obj");
	Model Silla2((char*)"Models/Objetos2/Silla2.obj");
	Model SillaE((char*)"Models/Objetos2/SillaE.obj");
	Model Sofa((char*)"Models/Objetos2/Sofa.obj");
	Model MesaCentro((char*)"Models/Objetos2/MesaCentro.obj");


	Model Sillon((char*)"Models/Objetos2/Sillon.obj");
	Model Cuadro((char*)"Models/Objetos2/Cuadro.obj");
	Model Escritorio((char*)"Models/Objetos2/Escritorio.obj");
	Model SillaEscritorio((char*)"Models/Objetos2/SillaDeEscritorio.obj");
	//Model Cama((char*)"Models/Objetos2/Cama.obj");

	Model Ventana1((char*)"Models/Objetos2/Ventana1.obj");
	Model Ventana2((char*)"Models/Objetos2/Ventana2.obj");
	Model Ventana3((char*)"Models/Objetos2/Ventana3.obj");
	Model Ventana4((char*)"Models/Objetos2/Ventana4.obj");
	Model Ventana5((char*)"Models/Objetos2/Ventana5.obj");
	Model Ventana6((char*)"Models/Objetos2/Ventana6.obj");
	Model Ventana7((char*)"Models/Objetos2/Ventana7.obj");
	Model Ventana8((char*)"Models/Objetos2/Ventana8.obj");
	Model Ventana9((char*)"Models/Objetos2/Ventana9.obj");
	Model Ventana10((char*)"Models/Objetos2/Ventana10.obj");
	Model Ventana11((char*)"Models/Objetos2/Ventana11.obj");
	Model Ventana12((char*)"Models/Objetos2/Ventana12.obj");
	Model Ventana13((char*)"Models/Objetos2/Ventana13.obj");
	Model Ventana14((char*)"Models/Objetos2/Ventana14.obj");
	Model Ventana15((char*)"Models/Objetos2/Ventana15.obj");
	Model Ventana16((char*)"Models/Objetos2/Ventana16.obj");

	Model VentanaT2_1((char*)"Models/Objetos2/VentanaT2_1.obj");
	Model VentanaT2_2((char*)"Models/Objetos2/VentanaT2_2.obj");
	Model VentanaT2_3((char*)"Models/Objetos2/VentanaT2_3.obj");
	Model VentanaT2_4((char*)"Models/Objetos2/VentanaT2_4.obj");
	Model VentanaT2_5((char*)"Models/Objetos2/VentanaT2_5.obj");
	Model VentanaT2_6((char*)"Models/Objetos2/VentanaT2_6.obj");
	Model VentanaT2_7((char*)"Models/Objetos2/VentanaT2_7.obj");
	Model VentanaT2_8((char*)"Models/Objetos2/VentanaT2_8.obj");

	Model PuertaPrincipal((char*)"Models/Objetos2/PuertaPrincipal.obj");
	Model PuertaCuarto((char*)"Models/Objetos2/puertaCuarto.obj");
	Model Puerta2((char*)"Models/Objetos2/Puerta2.obj");
	Model Zaguan1((char*)"Models/Objetos2/Zaguan1.obj");
	Model Zaguan2((char*)"Models/Objetos2/Zaguan2.obj");

	Model agua((char*)"Models/Objetos2/agua.obj");






	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);



	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		//Load Model
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.1f,0.1f,0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.5f, 0.5f, 0.5f);


		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= abs(sin(glfwGetTime() *Light1.z));

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),1.8f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.17f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);
		glBindVertexArray(0);
	
		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); 
	    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f,0.1f,0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Casa.Draw(lampShader);




		model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Barra.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla.Draw(lampShader);

		model = glm::mat4(1);
		//model = glm::rotate(model, glm::radians(rotacion), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(3.3f, 0.0f, -1.45f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lampShader);

		model = glm::mat4(1);
		//model = glm::rotate(model, glm::radians(rotacion), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(3.3f, 0.0f, -2.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lampShader);

		model = glm::mat4(1);
		
		model = glm::translate(model, glm::vec3(2.1f, 0.0f, -1.45f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lampShader);

		model = glm::mat4(1);
		
		model = glm::translate(model, glm::vec3(2.1f, 0.0f, -2.4f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lampShader);

		model = glm::mat4(1);
		
		model = glm::translate(model, glm::vec3(2.7f, 0.0f, -0.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lampShader);

		model = glm::mat4(1);
		
		model = glm::translate(model, glm::vec3(2.7f, 0.0f, -2.95f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla2.Draw(lampShader);

		

		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.15f,0.0f,2.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		SillaE.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(6.3f,0.0f,2.35f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		SillaE.Draw(lampShader);

		model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MesaCentro.Draw(lampShader);

		model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sofa.Draw(lampShader);

		//Segundo piso _________________________________________________________
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Sillon.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Escritorio.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		SillaEscritorio.Draw(lampShader);

		//model = glm::mat4(1);
		////model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Cama.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuadro.Draw(lampShader);


		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "ActivaTransparencia"), 0);
		//Ventana1.Draw(lightingShader);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.25);
		Ventana1.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 

		/*model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana1.Draw(lampShader);*/
		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana2.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana3.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana4.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana5.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana6.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana7.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana8.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana9.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana10.Draw(lampShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana11.Draw(lampShader);
		glBindVertexArray(0);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana12.Draw(lampShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana13.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana14.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana15.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ventana16.Draw(lampShader);







		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.8f, 0.1f, -6.45f));
		model = glm::rotate(model, glm::radians(-rotVent1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_1.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.8f, 0.1f, -5.9f));
		model = glm::rotate(model, glm::radians(rotVent2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_2.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.7f, 0.1f, -5.05));
		model = glm::rotate(model, glm::radians(-rotVent3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_3.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.8f, 0.1f, -4.4f));
		model = glm::rotate(model, glm::radians(rotVent4), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_4.Draw(lampShader);




		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.35f, 0.1f, -2.325));
		model = glm::rotate(model, glm::radians(-rotVent5), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_5.Draw(lampShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.35f, 0.1f, -1.725f));
		model = glm::rotate(model, glm::radians(rotVent6), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_6.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.35f, 0.1f, -1.05f));
		model = glm::rotate(model, glm::radians(-rotVent7), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_7.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-12.4f, 0.1f, -0.425));
		model = glm::rotate(model, glm::radians(rotVent8), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		VentanaT2_8.Draw(lampShader);

		glBindVertexArray(0);
		Anim.Use();
		tiempo = glfwGetTime();
		modelLoc = glGetUniformLocation(Anim.Program, "model");
		viewLoc = glGetUniformLocation(Anim.Program, "view");
		projLoc = glGetUniformLocation(Anim.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		if (piscinaEncendida == true) { glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo); }
		agua.Draw(Anim);



		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.7f, 1.3f, 0.9f));
		model = glm::rotate(model, glm::radians(-rotPuerta2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Zaguan1.Draw(lampShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.7f,1.3f,3.4f));
		model = glm::rotate(model, glm::radians(rotPuerta2), glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Zaguan2.Draw(lampShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.85f, -0.1f, -3.8f));
		model = glm::rotate(model, glm::radians(rotPuerta1), glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaPrincipal.Draw(lampShader);

		model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(-10.85f, -0.1f, -3.8f));
		//model = glm::rotate(model, glm::radians(rotPuerta1), glm::vec3(0.0f, 0.1f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta2.Draw(lampShader);



		/*Anim.Use();
		tiempo = glfwGetTime();
		modelLoc = glGetUniformLocation(Anim.Program, "model");
		viewLoc = glGetUniformLocation(Anim.Program, "view");
		projLoc = glGetUniformLocation(Anim.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		Piso.Draw(Anim);


		Anim2.Use();
		tiempo = glfwGetTime();
		modelLoc = glGetUniformLocation(Anim2.Program, "model");
		viewLoc = glGetUniformLocation(Anim2.Program, "view");
		projLoc = glGetUniformLocation(Anim2.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(Anim.Program, "time"), tiempo);
		SV.Draw(Anim2);

		glBindVertexArray(0);*/
	
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}

	if (keys[GLFW_KEY_R])	{rotacion -= 0.05f;}
	if (keys[GLFW_KEY_T])	{rotacion+= 0.05f;}

	if (zaguanAbrir  == true) { if (rotPuerta2 > 90.0) { zaguanAbrir = false; } else { rotPuerta2 += 0.1f; } }
	if (zaguanCerrar == true) { if (rotPuerta2 < 0.0) { zaguanCerrar = false; } else { rotPuerta2 -= 0.1f; } }
	
	if (puertaAbrir == true) { if (rotPuerta1 > 90.0) { puertaAbrir = false; } else { rotPuerta1 += 0.1f; } }
	if (puertaCerrar == true) { if (rotPuerta1 < 0.0) { puertaCerrar = false; } else { rotPuerta1 -= 0.1f; } }




	if (ventAbrir1  == true) { if (rotVent1 > 90.0) { ventAbrir1 = false; } else { rotVent1 += 0.1f; } }
	if (ventCerrar1 == true) { if (rotVent1 < 0.0) { ventCerrar1 = false; } else { rotVent1 -= 0.1f; } }

	if (ventAbrir2  == true) { if (rotVent2 > 90.0) { ventAbrir2 = false; } else { rotVent2 += 0.1f; } }
	if (ventCerrar2 == true) { if (rotVent2 < 0.0) { ventCerrar2 = false; } else { rotVent2 -= 0.1f; } }

	if (ventAbrir3  == true) { if (rotVent3 > 90.0) { ventAbrir3 = false; } else { rotVent3 += 0.1f; } }
	if (ventCerrar3 == true) { if (rotVent3 < 0.0) { ventCerrar3 = false; } else { rotVent3 -= 0.1f; } }

	if (ventAbrir4  == true) { if (rotVent4 > 90.0) { ventAbrir4 = false; } else { rotVent4 += 0.1f; } }
	if (ventCerrar4 == true) { if (rotVent4 < 0.0) { ventCerrar4 = false; } else { rotVent4 -= 0.1f; } }

	if (ventAbrir5  == true) { if (rotVent5 > 90.0) { ventAbrir5 = false; } else { rotVent5 += 0.1f; } }
	if (ventCerrar5 == true) { if (rotVent5 < 0.0) { ventCerrar5 = false; } else { rotVent5 -= 0.1f; } }

	if (ventAbrir6  == true) { if (rotVent6 > 90.0) { ventAbrir6 = false; } else { rotVent6 += 0.1f; } }
	if (ventCerrar6 == true) { if (rotVent6 < 0.0) { ventCerrar6 = false; } else { rotVent6 -= 0.1f; } }

	if (ventAbrir7  == true) { if (rotVent7 > 90.0) { ventAbrir7 = false; } else { rotVent7 += 0.1f; } }
	if (ventCerrar7 == true) { if (rotVent7 < 0.0) { ventCerrar7 = false; } else { rotVent7 -= 0.1f; } }

	if (ventAbrir8  == true) { if (rotVent8 > 90.0) { ventAbrir8 = false; } else { rotVent8 += 0.1f; } }
	if (ventCerrar8 == true) { if (rotVent8 < 0.0) { ventCerrar8 = false; } else { rotVent8 -= 0.1f; } }



	if (keys[GLFW_KEY_1]) { x -= 0.05f;}
	if (keys[GLFW_KEY_2]) { x += 0.05f;}
	if (keys[GLFW_KEY_3]) { z -= 0.05f; }
	if (keys[GLFW_KEY_4]) { z += 0.05f; }
	if (keys[GLFW_KEY_5]) { y -= 0.05f; }
	if (keys[GLFW_KEY_6]) { y += 0.05f; }
	
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 0.2f,1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}

	if (keys[GLFW_KEY_V])
	{
		if (ventana == true) {
			printf("Ventanas 1 desactivadas\n");
			ventana = false; 
		}
		else { 
			printf("Ventanas 1 Activadas\n"); 
			ventana = true; 
		}
	}
	if (keys[GLFW_KEY_B])
	{
		if (ventana2 == true) { 
			printf("Ventanas 2 desactivadas\n");
			ventana2 = false; 
		}else { 
			printf("Ventanas 2 Activadas\n");
			ventana2 = true; 
		}
	}

	if (keys[GLFW_KEY_P])
	{
		if (puerta == true) { 
			printf("Puertas Desactivasas\n"); 
			puerta = false; }
		else { 
			printf("Puertas Activadas\n"); 
			puerta = true; }
	}
	if (keys[GLFW_KEY_N])
	{
		if (piscinaEncendida == true) {
			printf("Piscina Desactivasas\n");
			piscinaEncendida = false;
		}
		else {
			printf("Piscina Activadas\n");
			piscinaEncendida = true;
		}
	}
	

	if (ventana == true && keys[GLFW_KEY_1]) { transVent1 = 1.0; }	else { transVent1 = 0.0; }
	if (ventana == true && keys[GLFW_KEY_2]) { transVent1 = 1.0; }	else { transVent1 = 0.0; }
	if (ventana == true && keys[GLFW_KEY_3]) { transVent1 = 1.0; } 	else { transVent1 = 0.0; }
	if (ventana == true && keys[GLFW_KEY_4]) { transVent1 = 1.0; } 	else { transVent1 = 0.0; }
	if (ventana == true && keys[GLFW_KEY_5]) { transVent1 = 1.0; } 	else { transVent1 = 0.0; }
	if (ventana == true && keys[GLFW_KEY_6]) { transVent1 = 1.0; }	else { transVent1 = 0.0; }
	if (ventana == true && keys[GLFW_KEY_7]) { transVent1 = 1.0; }	else { transVent1 = 0.0; }

	if (ventana2 == true && keys[GLFW_KEY_1]) {
		if (rotVent1 > 90.0) {
			ventCerrar1 = true;
			ventAbrir1 = false;
		}
		else {
			ventCerrar1 = false;
			ventAbrir1 = true;
		}
	}

	if (ventana2 == true && keys[GLFW_KEY_2]) {
		if (rotVent2 > 90.0) {
			ventCerrar2 = true;
			ventAbrir2 = false;
		}
		else {
			ventCerrar2 = false;
			ventAbrir2 = true;
		}
	}

	if (ventana2 == true && keys[GLFW_KEY_3]) {
		if (rotVent3 > 90.0) {
			ventCerrar3 = true;
			ventAbrir3 = false;
		}
		else {
			ventCerrar3 = false;
			ventAbrir3 = true;
		}
	}
	
	if (ventana2 == true && keys[GLFW_KEY_4]) {
		if (rotVent4 > 90.0) {
			ventCerrar4 = true;
			ventAbrir4 = false;
		}
		else {
			ventCerrar4 = false;
			ventAbrir4 = true;
		}
	}
	
	if (ventana2 == true && keys[GLFW_KEY_5]) {
		if (rotVent5 > 90.0) {
			ventCerrar5 = true;
			ventAbrir5 = false;
		}
		else {
			ventCerrar5 = false;
			ventAbrir5 = true;
		}
	}
	
	if (ventana2 == true && keys[GLFW_KEY_6]) {
		if (rotVent6 > 90.0) {
			ventCerrar6 = true;
			ventAbrir6 = false;
		}
		else {
			ventCerrar6 = false;
			ventAbrir6 = true;
		}
	}
	
	if (ventana2 == true && keys[GLFW_KEY_7]) {
		if (rotVent7 > 90.0) {
			ventCerrar7 = true;
			ventAbrir7 = false;
		}
		else {
			ventCerrar7 = false;
			ventAbrir7 = true;
		}
	}
	
	if (ventana2 == true && keys[GLFW_KEY_8]) {
		if (rotVent8 > 90.0) {
			ventCerrar8 = true;
			ventAbrir8 = false;
		}
		else {
			ventCerrar8 = false;
			ventAbrir8 = true;
		}
	}








	if (puerta == true && keys[GLFW_KEY_1]) {
		if (rotPuerta1 > 90.0) {
			puertaCerrar = true;
			puertaAbrir = false;
		}
		else {
			puertaCerrar = false;
			puertaAbrir = true;
		}
	}
	
	if (puerta == true && keys[GLFW_KEY_2]) { 
		if (rotPuerta2 > 90.0) {
			zaguanCerrar = true; 
			zaguanAbrir = false; 
		} else { 
			zaguanCerrar = false;
			zaguanAbrir = true; } 
	}






	if (keys[GLFW_KEY_0]) {
		printf("\nX: %.3f,	Y: %.3f,	Z: %.3f\n", x, y, z);
	}

}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}