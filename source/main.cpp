#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLfloat points[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
};

GLfloat colors[] = {
    1.0f, 0.5f, 0.5f,
    0.5f, 1.0f, 0.5f,
    0.5f, 0.5f, 1.0f,
};

const char* vertex_shader =
"#version 430\n"
"layout (location = 0) in vec3 vertex_position;"
"layout (location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main () {"
"    color = vertex_color;"
"    gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader =
"#version 430\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main () {"
"    frag_color = vec4(color, 1.0);"
"}";

int window_sizeX = 640;
int window_sizeY = 480;

void glfw_window_increasing_size(GLFWwindow* window, int width, int height)
{
    window_sizeX = width;
    window_sizeY = height;
    glViewport(0, 0, window_sizeX, window_sizeY);
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE); 
    }
}

int main(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(window_sizeX, window_sizeY, "Battle city", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfw_window_increasing_size);
    glfwSetKeyCallback(window, glfw_key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
	{
		std::cout << "Can't load library GLAD" << std::endl;
		return -1;
	}
	
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
	glClearColor(0, 1, 0.5, 1);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program); 

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao); 
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}