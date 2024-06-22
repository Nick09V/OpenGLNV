#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION //Add to use stb_image.h
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>
#include "image/stb_image.h" //Add to use stb_image.h
#include <iostream>
/*
* Nombre: Nick Sebastian Valverde Zavala
* Código unico: 202120523
* fecha: 12/06/24
*
*/


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& xOffset, float& yOffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



class Shader
{
public:
    unsigned int ID; // the program ID
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    //Metodos para activa el programa de shader
    void use(); // use/activate the shader
    // utility uniform functions
    
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    // Métodos para establecer uniformes
    //void setVec3(const std::string& name, float x, float y, float z) const;
};
#endif



// Constructor que lee y compila los shaders
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // asegurarse de que los objetos ifstream puedan lanzar excepciones:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // abrir archivos
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // leer el contenido de los archivos en los streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // cerrar los manejadores de archivos
        vShaderFile.close();
        fShaderFile.close();
        // convertir los streams en strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // compilar shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // imprimir errores de compilación, si los hay
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // imprimir errores de compilación, si los hay
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    // programa de shader
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // imprimir errores de enlace, si los hay
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
            << infoLog << std::endl;
    }

    // eliminar shaders ya que están adjuntos al programa de shader y no se necesitan más
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// Método para usar/activar el programa de shader
void Shader::use()
{
    glUseProgram(ID);
}

// Métodos de utilidad para establecer uniformes
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
/*
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
*/

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //versión principal de OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //versión menor de OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //usar perfil central de OpenGL

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tarea B2T1_Valverde Nick", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwMakeContextCurrent(window); // hacer que el contexto de la ventana actual de GLFW sea el contexto principal de OpenGL
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //registra la función de devolución de llamada de cambio de tamaño de la ventana

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    Shader ourShader("shaders/shader_exercise8.vs", "shaders/shader_exercise8.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices2[] = {
        // Posiciones            // Colores
          // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 

    };

    float vertices[] = {
        // Vértice 0
        -0.95f, -0.15f, 0.0f,  // Posición
        1.0f, 0.0f, 0.0f,      // Color (rojo)
		//0.25, 4.25, //coordenadas de textura


        // Vértice 1
        -0.56f, -0.15f, 0.0f,  // Posición
        0.0f, 1.0f, 0.0f,      // Color (verde)
		//0.2, 4.25, //coordenadas de textura

        // Vértice 2
        -0.40f, 0.0f, 0.0f,    // Posición
        0.0f, 0.0f, 1.0f,      // Color (azul)

        // Vértice 3
        0.0f, -0.30f, 0.0f,    // Posición
        1.0f, 1.0f, 0.0f,      // Color (amarillo)

        // Vértice 4
        0.40f, 0.0f, 0.0f,     // Posición
        0.0f, 1.0f, 1.0f,      // Color (cian)

        // Vértice 5
        0.40f, 0.10f, 0.0f,    // Posición
        1.0f, 0.0f, 1.0f,      // Color (magenta)

        // Vértice 6
        0.60f, 0.10f, 0.0f,    // Posición
        0.5f, 0.5f, 0.5f,      // Color (gris)

        // Vértice 7
        0.80f, 0.10f, 0.0f,    // Posición
        0.3f, 0.7f, 0.5f,      // Color (verde azulado)

        // Vértice 8
        0.75f, 0.15f, 0.0f,    // Posición
        0.8f, 0.2f, 0.1f,      // Color (naranja)

        // Vértice 9
        0.90f, 0.30f, 0.0f,    // Posición
        0.2f, 0.5f, 0.8f,      // Color (azul claro)

        // Vértice 10
        0.60f, 0.30f, 0.0f,    // Posición
        0.7f, 0.4f, 0.6f,      // Color (violeta)

        // Vértice 11
        0.40f, 0.30f, 0.0f,    // Posición
        0.4f, 0.3f, 0.9f,      // Color (azul oscuro)

        // Vértice 12
        0.0f, 0.0f, 0.0f,      // Posición
        0.5f, 0.5f, 0.2f,      // Color (verde oscuro)

        // Vértice 13
        -0.40f, 0.30f, 0.0f,   // Posición
        0.1f, 0.8f, 0.4f,      // Color (verde claro)

        // Vértice 14
        -0.80f, 0.0f, 0.0f,    // Posición
        0.9f, 0.1f, 0.3f       // Color (rojo claro)
    };

	unsigned int indices2[] = {
		0, 1, 3, // primer triángulo
		1, 2, 3  // segundo triángulo
	};

    unsigned int indices[] = {
        // Define el orden de los vértices para los 7 objetos
        // CUADRADO 1
        0, 1, 14,
        1, 2, 14,

        14,12,13,

        2,3,4,

        4,11,12,

        5,11,10,
        5,6,10,


        6,10,7,

        
        8,9,10,

        10,9,1
        // Triángulo 2
        // Completar...
    };

	unsigned int VBO, VAO, EBO;// reamos un buffer de vertices y un arreglo de vertices
	glGenVertexArrays(1, &VAO); //generamos uno mas VAO
	glGenBuffers(1, &VBO); //generamos un VBO
	glGenBuffers(1, &EBO); //generamos un EBO

	glBindVertexArray(VAO); // enlazamos el VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // enlazamos el buffer de vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // enlazamos el buffer de indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

    // variables para el desplazamiento
    float xOffset = 0.0f;
    float yOffset = 0.0f;

       
    // load and create a texture
        // -------------------------
        unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char* data = stbi_load(FileSystem::getPath("textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    //Cargar textura 2
    // load and create a texture
        // -------------------------
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width2, height2, nrChannels2;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char* data = stbi_load(FileSystem::getPath("textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    unsigned char* data2 = stbi_load("textures/cuadradoPatron.jpg", &width2, &height2, &nrChannels2, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    stbi_image_free(data2);

    // Activar el shader y establecer el uniforme de la textura
    ourShader.use();
    ourShader.setInt("texture1", 0); // 0 es la unidad de textura
    ourShader.setInt("texture2", 1); // 0 es la unidad de textura
    float cambioColor = 0.5f;
    // render loop
    while (!glfwWindowShouldClose(window))
    {
  
        // Input
        processInput(window, xOffset, yOffset);


        // render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // color de fondo
		glClear(GL_COLOR_BUFFER_BIT); // limpiar el buffer de color

        // bind Texture and send to the fragment shader sampler
        glBindTexture(GL_TEXTURE_2D, texture);


        // render the triangle
        ourShader.use();

        

        ourShader.setFloat("cambioColor", cambioColor);
        ourShader.setFloat("xOffset", xOffset);
        ourShader.setFloat("yOffset", yOffset);
        

        glBindVertexArray(VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, float& xOffset, float& yOffset)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        yOffset += 0.0005f; // Incrementar el desplazamiento en el eje Y
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        yOffset -= 0.0005f; // Disminuir el desplazamiento en el eje Y
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xOffset -= 0.0005f; // Disminuir el desplazamiento en el eje X
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xOffset += 0.0005f; // Incrementar el desplazamiento en el eje X
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}