#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/shader_s.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

/*
* Nombre: Nick Valverde
* Fecha de entrega: 10/7/2024
* Tarea: B2T3
*
*/


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Exercise 12 Task 4
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Nick Valverde - 1726431164 - B2T3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    //Exercise 11 Task 3
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shaders/shader_B2T3.vs", "shaders/shader_B2T3.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        //CARA POSTERIOR
    // positions          // texture coords (reflejadas)
    -0.5f, -0.5f, -0.5f,  348.05f / 1000.0f, 510.0f / 1000.0f, // (u1, v0)
     0.5f, -0.5f, -0.5f,  144.0f / 1000.0f, 510.0f / 1000.0f,  // (u0, v1)
     0.5f,  0.5f, -0.5f,  144.0f / 1000.0f, 682.0f / 1000.0f,  // (u0, v2)
     0.5f,  0.5f, -0.5f,  144.0f / 1000.0f, 682.0f / 1000.0f,  // (u0, v2)
    -0.5f,  0.5f, -0.5f,  348.05f / 1000.0f, 682.0f / 1000.0f, // (u1, v3)
    -0.5f, -0.5f, -0.5f,  348.05f / 1000.0f, 510.0f / 1000.0f,  // (u1, v0)
    

    // CARA DELANTERA
    -0.5f, -0.5f,  0.5f,  552.00f / 1000.0f, 510.00f / 1000.0f,
     0.5f, -0.5f,  0.5f,  757.0f / 1000.0f, 510.00f / 1000.0f,
     0.5f,  0.5f,  0.5f,  757.0f / 1000.0f, 682.0f / 1000.0f,
     0.5f,  0.5f,  0.5f,  757.0f / 1000.0f, 682.0f / 1000.0f,
    -0.5f,  0.5f,  0.5f,  552.00f / 1000.0f, 682.0f / 1000.0f,
    -0.5f, -0.5f,  0.5f,  552.00f / 1000.0f, 510.00f / 1000.0f,


    //CARA IZQUIERDA DELANTERA
    -0.5f,  0.5f,  0.5f,  552.00f / 1000.0f, 682.0f / 1000.0f,  // (u2, v2)
    -0.5f,  0.5f, -0.5f,  348.05f / 1000.0f, 682.0f / 1000.0f,  // (u3, v3)
    -0.5f, -0.5f, -0.5f,  348.05f / 1000.0f, 510.0f / 1000.0f,  // (u0, v0)
    -0.5f, -0.5f, -0.5f,  348.05f / 1000.0f, 510.0f / 1000.0f,  // (u0, v0)
    -0.5f, -0.5f,  0.5f,  552.00f / 1000.0f, 510.00f / 1000.0f, // (u1, v1)
    -0.5f,  0.5f,  0.5f,  552.00f / 1000.0f, 682.0f / 1000.0f,  // (u2, v2)


	//CARA DERECHA DELANTERA
     0.5f,  0.5f,  0.5f,  757.0f / 1000.0f, 682.0f / 1000.0f,
     0.5f,  0.5f, -0.5f,  961.0f / 1000.0f, 682.0f / 1000.0f, // (u2, v2)
     0.5f, -0.5f, -0.5f,  961.0f / 1000.0f, 510.00f / 1000.0f,  // (u0, v0)
     0.5f, -0.5f, -0.5f,  961.0f / 1000.0f, 510.00f / 1000.0f,  // (u0, v0)
     0.5f, -0.5f,  0.5f,  757.0f / 1000.0f, 510.00f / 1000.0f,
     0.5f,  0.5f,  0.5f,  757.0f / 1000.0f, 682.0f / 1000.0f,
     
	 //CARA INFERIOR
    -0.5f, -0.5f, -0.5f, 552.00f / 1000.0f,295.0f / 1000.0f,
     0.5f, -0.5f, -0.5f,  757.0f / 1000.0f, 295.0f / 1000.0f,
     0.5f, -0.5f,  0.5f,  757.0f / 1000.0f, 510.00f / 1000.0f,
     0.5f, -0.5f,  0.5f,  757.0f / 1000.0f, 510.00f / 1000.0f,
    -0.5f, -0.5f,  0.5f,  552.00f / 1000.0f, 510.00f / 1000.0f,
    -0.5f, -0.5f, -0.5f,  552.00f / 1000.0f, 295.0f / 1000.0f,


	//CARA SUPERIOR
    -0.5f,  0.5f, -0.5f,  552.00f / 1000.0f, 682.0f / 1000.0f,
     0.5f,  0.5f, -0.5f,  757.0f / 1000.0f, 682.0f / 1000.0f,
     0.5f,  0.5f,  0.5f,  757.0f / 1000.0f, 847.0f / 1000.0f,
     0.5f,  0.5f,  0.5f,  757.0f / 1000.0f, 847.0f / 1000.0f,
    -0.5f,  0.5f,  0.5f,  552.00f / 1000.0f, 847.0f / 1000.0f,
    -0.5f,  0.5f, -0.5f,  552.00f / 1000.0f, 682.0f / 1000.0f
    };




    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
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

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
 

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2, texture3;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("textures/Texture7.png", &width, &height, &nrChannels, 0);    if (data)
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/Texture2.png", &width, &height, &nrChannels, 0);    if (data)
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 3
  // ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/Texture3.png", &width, &height, &nrChannels, 0);    if (data)
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); 
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    ourShader.setInt("texture3", 2);
   
    int variable = 1;
	float rotationSpeed = 20.0f; // velocidad de rotaci�n
    float radioGiro = 10.0f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
       

        
        //glClear(GL_COLOR_BUFFER_BIT);
        //Exercise 11 Task 3
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        // activate shader
        ourShader.use();
		
		//Exercise 12 Task 3
		// pass projection matrix to shader (note that in this case it could change every frame)
		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		
		 // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);


        for (unsigned int i = 0; i < 12; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            
            
			if (i == 2 || i == 4) {
				ourShader.setInt("variable", 1);

                std::cout << "Current file: " << currentFrame << std::endl;
                model = glm::rotate(model, glm::radians(currentFrame * rotationSpeed), glm::vec3(1.0f, 0.3f, 0.5f));
			}
            else {
                if (i == 3 || i == 8 || i == 10) {
                    ourShader.setInt("variable", 2);
                    model = glm::scale(model, glm::vec3(0.5f * sin(currentFrame)));
				}
				else {

                    model = glm::translate(model, glm::vec3(radioGiro * cos(currentFrame), 0.0f, radioGiro * sin(currentFrame)));
					ourShader.setInt("variable", 3);
				}

            }
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}