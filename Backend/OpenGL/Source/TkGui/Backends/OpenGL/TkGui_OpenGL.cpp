#include "TkGui/Backends/OpenGL/TkGui_OpenGL.hpp"
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Loader.hpp"

namespace TkGui
{
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aUV;
        layout(location = 2) in vec3 aColor;

        out vec2 TexCoord;
        out vec3 Color;

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
            TexCoord = aUV;
            Color = aColor;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec2 TexCoord;
        in vec3 Color;

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(Color, 1.0);
        }
    )";

    GLuint VAO = 0, VBO = 0, EBO = 0;
    GLuint shaderProgram = 0;

    void CheckShader(GLuint shader, GLenum type)
    {
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            printf("[Shader Error] %s Shader:\n%s\n", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
        }
    }

    void CheckProgram(GLuint program)
    {
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            printf("[Shader Program Error] Linking:\n%s\n", infoLog);
        }
    }

    void InitOpenGL(text_t version)
    {
        // === Buffers ===
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 12, nullptr, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_t) * 6, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

        // === Shaders ===
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        CheckShader(vertexShader, GL_VERTEX_SHADER);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        CheckShader(fragmentShader, GL_FRAGMENT_SHADER);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        CheckProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void DrawOpenGL(const DrawData& data)
    {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        for (const Object& obj : data.Objects)
        {
            for (const Face& face : obj.Faces)
            {
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, face.Vertices.size() * sizeof(Vertex), face.Vertices.data(), GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, face.Indeces.size() * sizeof(index_t), face.Indeces.data(), GL_DYNAMIC_DRAW);

                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(face.Indeces.size()), GL_UNSIGNED_INT, nullptr);
            }
        }
    }

    void TerminateOpenGL()
    {
        glDeleteProgram(shaderProgram);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);

        VAO = VBO = EBO = shaderProgram = 0;
    }
}
