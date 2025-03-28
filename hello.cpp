#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create the window and set the current context to the window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Window", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //initialize glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    //set the data display/coordinates setting
    glViewport(0, 0, 800, 600);

    //update the viewport when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //render loop
    while(!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //rendering code should go here
        //fill the screen with a green color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //rectangle vertices
        float vertices[] = {
            //first rectangle
            0.0f, 1.0f, 0.0f, //top right
            0.0f, 0.0f, 0.0f, //bottom right
            -1.0f, 0.0f, 0.0f, //bottom left
            -1.0f, 1.0f, 0.0f, //top left
            //second rectangle
            1.0f, 0.0f, 0.0f, //top right
            1.0f, -1.0f, 0.0f, //bottom right
            0.0f, -1.0f, 0.0f, //bottom left
            0.0f, 0.0f, 0.0f //top left
        };

        //rectangle indices
        unsigned int indices[] = {
            //first rectangle
            0, 1, 3, //first triangle
            1, 2, 3, //second triangle
            //second rectangle
            4, 5, 7, //first triangle
            5, 6, 7 //second triangle
        };

        //vertex array object
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //vertex buffer object
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //element buffer object
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //set the layout of the vertex buffer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        //vertex shader
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() {\n"
            "   gl_Position = vec4(aPos.xyz, 1.0);\n"

            "}\0";

        //compile the shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        //check for compilation errors
        int vertexSuccess;
        char vertexInfoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);

        //display errors if there were any
        if(!vertexSuccess) {
            glGetShaderInfoLog(vertexShader, 512, NULL, vertexInfoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMILOATION_FAILED\n" << vertexInfoLog << std::endl;
        }

        //fragment shader (make triangle orange)
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main() {\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";

        //compile the shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        //check for compilation errors
        int fragmentSuccess;
        char fragmentInfoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);

        //display errors if there were any
        if(!fragmentSuccess) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, fragmentInfoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragmentInfoLog << std::endl;
        }

        //create the shader program
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();

        //link the shaders to the program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        //remove the linked shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        //check for errors
        int programSuccess;
        char programInfoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);

        //display errors if there were any
        if(!programSuccess) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, programInfoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << programInfoLog << std::endl;
        }

        //specify that we want to use the newly created program
        //and draw the object stored in the VAO
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        //check/call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}