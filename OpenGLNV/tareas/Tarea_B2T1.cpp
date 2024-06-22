#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <image/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& xOffset, float& yOffset);


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
    Shader ourShader("shaders/tareaB2_T1.vs", "shaders/tareaB2_T1.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


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

		10,9,11,
    };


    float numIndices = sizeof(indices) / sizeof(indices[0]);
    std::cout << "Número de índices: " << numIndices << std::endl;


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
    // texture coord attribute
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);


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
    unsigned char* data = stbi_load("textures/flor.jpg", &width, &height, &nrChannels, 0);
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
    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window, xOffset, yOffset);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);


        //mover la figura
        ourShader.setFloat("xOffset", xOffset);
        ourShader.setFloat("yOffset", yOffset);

        // render container
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

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
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}