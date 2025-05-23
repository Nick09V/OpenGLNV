#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <chrono>
#define STB_IMAGE_IMPLEMENTATION 
#include <image/stb_image.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& xOffset, float& yOffset, float& rotar, float& escala);
/*
* Nombre: Nick Valverde
* Fecha: 30/6/2024
* C�digo unico: 202120523
* Ejercicio B2T2
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B2T2", NULL, NULL);
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
    Shader ourShader("shaders/vertexshader.vs", "shaders/fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    float vertices[] = {
        // V�rtice 0
        -0.95f, -0.15f, 0.0f,  // Posici�n
        0.404f, 0.400f, 0.800f,    // Color (rojo)
        

        // V�rtice 1
        -0.56f, -0.15f, 0.0f,  // Posici�n
        0.2039f, 0.80f, 0.4039f,  // Color (verde)

        // V�rtice 2
        -0.40f, 0.0f, 0.0f,    // Posici�n
        1.0f, 0.80f, 0.0f,      // Color (azul)

        // V�rtice 3
        0.0f, -0.30f, 0.0f,    // Posici�n
        0.60f, 0.80f, 0.1960f,     // Color (amarillo)

        // V�rtice 4
        0.40f, 0.0f, 0.0f,     // Posici�n
        1.0f, 0.4039f, 0.40f,     // Color (cian)

        // V�rtice 5
        0.40f, 0.10f, 0.0f,    // Posici�n
        0.20f, 0.60f, 1.0f,     // Color (magenta)

        // V�rtice 6
        0.60f, 0.10f, 0.0f,    // Posici�n
        1.0f, 0.60f, 0.2039f,      // Color (gris)

        // V�rtice 7
        0.80f, 0.10f, 0.0f,    // Posici�n
        0.3f, 0.7f, 0.5f,      // Color (verde azulado)

        // V�rtice 8
        0.75f, 0.15f, 0.0f,    // Posici�n
        0.8f, 0.2f, 0.1f,      // Color (naranja)

        // V�rtice 9
        0.90f, 0.30f, 0.0f,    // Posici�n
        0.2f, 0.5f, 0.8f,      // Color (azul claro)

        // V�rtice 10
        0.60f, 0.30f, 0.0f,    // Posici�n
        0.7f, 0.4f, 0.6f,      // Color (violeta)

        // V�rtice 11
        0.40f, 0.30f, 0.0f,    // Posici�n
        0.4f, 0.3f, 0.9f,      // Color (azul oscuro)

        // V�rtice 12
        0.0f, 0.0f, 0.0f,      // Posici�n
        0.5f, 0.5f, 0.2f,      // Color (verde oscuro)

        // V�rtice 13
        -0.40f, 0.30f, 0.0f,   // Posici�n
        0.1f, 0.8f, 0.4f,      // Color (verde claro)

        // V�rtice 14
        -0.80f, 0.0f, 0.0f,    // Posici�n
        0.9f, 0.1f, 0.3f       // Color (rojo claro)
    };
    unsigned int indices[] = {
        // Define el orden de los v�rtices para los 7 objetos
        // CUADRADO 1
        0, 1, 14,
        1, 2, 14,

        14,12,13,

        2,3,4,

       
        4,11,12,

        5,6,10,
        5,10,11,

        6,7,10,

        8,9,10,
    };


    unsigned int numIndices = 12 + 15;
    //std::cout << "N�mero de �ndices: " << numIndices << std::endl;


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
    float xOffset = 0.0005f;
    float yOffset = 0.0005f;
	float rotar = 1.0f;
    int textura = 1;
	float incrementoTraslacion = 0.0005f;
    float incrementoTraslacionY = 0.0005f;
	float escala = 1.0f;
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first


    std::cout << "Rotar: J aumenta y K disminuye" << std::endl;
    std::cout << "Trasladar: WASD aumenta con el tiempo" << std::endl;
    std::cout << "Escalar: Y aumenta y H disminuye" << std::endl;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // Input
        processInput(window, xOffset, yOffset, rotar, escala);
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

		incrementoTraslacion = incrementoTraslacion + xOffset;
		incrementoTraslacionY = incrementoTraslacionY + yOffset;
        transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first|

        // create transformations
        transform = glm::translate(transform, glm::vec3(incrementoTraslacion, incrementoTraslacionY, 0.0f));
        transform = glm::rotate(transform, rotar, glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(escala, escala, escala));

        // get matrix's uniform location and set matrix
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            // render Figura 1
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);



            //Dibujar figura 2
            transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX
            transform = glm::translate(transform, glm::vec3(-0.1f, 0.5f, 0.0f));
            float scale = sin(glfwGetTime());
            transform = glm::scale(transform, glm::vec3(scale, scale, scale));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, float& xOffset, float& yOffset, float& rotar, float& escala)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        yOffset += 0.0000005f; // Incrementar el desplazamiento en el eje Y
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        yOffset -= 0.0000005f; // Disminuir el desplazamiento en el eje Y
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        xOffset -= 0.0000005f; // Disminuir el desplazamiento en el eje X
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        xOffset += 0.0000005f; // Incrementar el desplazamiento en el eje X
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) 
        rotar += 0.0005f; // Cambiar rotar K
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        rotar -= 0.0005f; // Cambiar rotar inverso J
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        escala += 0.0005f; // Cambiar escala grande
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
        escala -= 0.0005f; // Cambiar escala peque�a
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}