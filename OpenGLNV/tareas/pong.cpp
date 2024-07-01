#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION 
#include <image/stb_image.h>

#include <iostream>
#include <array>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& xOffset, float& yOffset, float& valorTextura);
/*
* Nombre: Nick Valverde
* Fecha: 23/6/2024
* Código unico: 202120523
*/


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "C2 Exercise 9", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/pong/vertexshaderPong.vs", "shaders/pong/fragmentshaderPong.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    float vertices[] = {
        -0.9,0.6,0.0, //A
		0.91,0.6,0.1, //color

        -0.9,0.2,0.0, //B
        0.91,0.6,0.1, //color

		-0.86,0.6,0.0, //C
		0.91,0.6,0.1, //color

		-0.86,0.2,0.0 //D
		,0.91,0.6,0.1, //color

        -0.49,0.46,0.0, //E 4
        1.0,0.0,0.0, //color

		-0.47,0.45,0.0, //F 5
		  0.0,1.0,0.0, //color

		- 0.49,0.47,0.0, //G 6
		1.0,0.0,0.0, //color

		-0.47,0.47,0.0, //H 7
		1.0,0.0,0.0, //color

		-0.5,0.44,0.0, //I 8
		1.0,0.0,0.0, //color

		-0.48,0.44,0.0, //J 9
		1.0,0.0,0.0, //color

		-0.5,0.45,0.0, //K 10 
		1.0,0.0,0.0, //color

    };



    unsigned int indices[] = {
	   0,1,2,
	   1,2,3,

	   4,5,6,
	   4,6,7,
	   4,5,8,
	   5,8,9,
		   5,9,10

       

    };


    unsigned int numIndices = 21;
    unsigned int numIndices2 = 1;
    //std::cout << "Número de índices: " << numIndices << std::endl;


    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);
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
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    // or set it via the texture class
    ourShader.setInt("texture2", 1);



    // variables para el desplazamiento
    float xOffset = 0.0f;
    float yOffset = 0.0f;
	float valorTextura = 1.0f;
    int textura = 1;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // Input
        processInput(window, xOffset, yOffset, valorTextura);
        float time = glfwGetTime();
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        ourShader.use();
        // mover la figura
        ourShader.setFloat("xOffset", xOffset);
        ourShader.setFloat("yOffset", yOffset); 
        ourShader.setFloat("time", time);


			//ourShader.setInt("textura", textura);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

           
            glDrawElements(GL_TRIANGLES, numIndices - 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, float& xOffset, float& yOffset, float& valorTextura)
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
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        valorTextura = 1.0f; // Cambiar textura J
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) 
        valorTextura = 0.0f; // Cambiar textura K
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        valorTextura = 0.0f; // comenzar a que funcione con el tiempo
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}