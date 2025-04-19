#include "TkGui/Backends/OpenGL/TkGui_OpenGL.hpp"
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Loader.hpp"
#include <iostream>

namespace TkGui
{
    //static Array<OpenGLGLObject> s_openGLDrawData = {};

    OpenGLGLObject::OpenGLGLObject()
        : VAO(0), VBO(0), EBO(0), TBO(0), IndexCount(0)
    {

    }

    OpenGLGLObject::OpenGLGLObject(uint32_t vertexElementArray, uint32_t vertexElementBuffer, uint32_t indexElementBuffer, uint32_t textureBuffer, uint32_t indexCount)
        : VAO(vertexElementArray), VBO(vertexElementBuffer), EBO(indexElementBuffer), TBO(textureBuffer), IndexCount(indexCount)
    {

    }

    OpenGLGLObject::~OpenGLGLObject()
    {
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        if (EBO) glDeleteBuffers(1, &EBO);
        if (TBO) glDeleteTextures(1, &TBO);
    }

    const char* vertexShaderSource = R"(
        #version 420 core
        layout(location = 0) in vec3 v_Pos;
        layout(location = 1) in vec2 v_UV;
        layout(location = 2) in vec3 v_Color;

        out vec2 TexCoord;
        out vec3 Color;

        void main()
        {
            gl_Position = vec4(v_Pos, 1.0);
            TexCoord = v_UV;
            Color = v_Color;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 420 core
        in vec2 TexCoord;
        in vec3 Color;
        layout(binding = 0) uniform sampler2D b_Texture;

        out vec4 FragColor;

        void main()
        {
            vec4 texColor = texture(b_Texture, TexCoord);
            FragColor = vec4(Color, 1.0);
        }
    )";

    GLuint shaderProgram = 0;

    GLuint CompileShader(GLenum type, const char* source)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        return shader;
    }

    void InitOpenGL(void* proc)
    {
        if (OpenGLLoadFailed(OpenGLLoader_Init_Loader(proc)))
        {
            fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        }

        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader); 
        glLinkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    GLuint VAO, VBO, EBO;

    void DrawOpenGL(const DrawData& data)
    {
        glUseProgram(shaderProgram);
        //s_openGLDrawData.clear();

        for (const Object& drawObject : data.Objects)
        {
            for (const Face& drawFace : drawObject.Faces)
            {
                GLuint VAO, VBO, EBO;
                glCreateVertexArrays(1, &VAO);
                glBindVertexArray(VAO);

                glCreateBuffers(1, &VBO);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, drawFace.Vertices.size() * sizeof(Vertex), drawFace.Vertices.data(), GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

                glCreateBuffers(1, &EBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawFace.Indeces.size() * sizeof(index_t), drawFace.Indeces.data(), GL_STATIC_DRAW);

                glDrawElements(GL_TRIANGLES, drawFace.Indeces.size(), GL_UNSIGNED_INT, 0);
            }
        }
    }

    void TerminateOpenGL()
    {
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        
        //glDeleteProgram(shaderProgram);
    }
}
