#include "TkGui/Backends/OpenGL/TkGui_OpenGL.hpp"
#include "TkGui/Backends/OpenGL/TkGui_OpenGL_Loader.hpp"
#include <iostream>

namespace TkGui
{
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
            FragColor = texture(b_Texture, TexCoord) * vec4(Color, 1.0);
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

        s_openGLDrawData = { };
    }

    GLuint VAO, VBO, EBO, TBO;

    void DrawOpenGL(const DrawData& data)
    {
        glUseProgram(shaderProgram);

        for (const Object& drawObject : data.Objects)
        {
            // Tworzenie tekstury z Image (Float32x4_t)
            glCreateTextures(GL_TEXTURE_2D, 1, &TBO);
            glTextureStorage2D(TBO, 1, GL_RGBA32F, drawObject.Texture.Width, drawObject.Texture.Height);

            glTextureSubImage2D(
                TBO, 0, 0, 0,
                drawObject.Texture.Width,
                drawObject.Texture.Height,
                GL_RGBA,
                GL_FLOAT,
                drawObject.Texture.Pixels.data()
            );

            glTextureParameteri(TBO, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTextureParameteri(TBO, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            for (const Face& drawFace : drawObject.Faces)
            {
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


                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                glBindTextureUnit(0, TBO);
                glDrawElements(GL_TRIANGLES, drawFace.Indeces.size(), GL_UNSIGNED_INT, 0);
            }
        }
    }

    void BakeOpenGL(const DrawData& data)
    {
        glUseProgram(shaderProgram);

        for (const Object& drawObject : data.Objects)
        {
            for (const Face& drawFace : drawObject.Faces)
            {
                OpenGLGLObject glObject;

                glCreateTextures(GL_TEXTURE_2D, 1, &glObject.TBO);
                glTextureStorage2D(glObject.TBO, 1, GL_RGBA32F, drawObject.Texture.Width, drawObject.Texture.Height);

                glTextureSubImage2D(
                    glObject.TBO, 0, 0, 0,
                    drawObject.Texture.Width,
                    drawObject.Texture.Height,
                    GL_RGBA,
                    GL_FLOAT,
                    drawObject.Texture.Pixels.data()
                );

                glTextureParameteri(glObject.TBO, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTextureParameteri(glObject.TBO, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glCreateVertexArrays(1, &glObject.VAO);
                glBindVertexArray(glObject.VAO);

                glCreateBuffers(1, &glObject.VBO);
                glBindBuffer(GL_ARRAY_BUFFER, glObject.VBO);
                glBufferData(GL_ARRAY_BUFFER, drawFace.Vertices.size() * sizeof(Vertex), drawFace.Vertices.data(), GL_DYNAMIC_DRAW);

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, UV));

                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

                glCreateBuffers(1, &glObject.EBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glObject.EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, drawFace.Indeces.size() * sizeof(index_t), drawFace.Indeces.data(), GL_DYNAMIC_DRAW);
                glObject.IndexCount = drawFace.Indeces.size();
                s_openGLDrawData.push_back(glObject);
            }
        }
    }

    void DrawOpenGL()
    {
        for (OpenGLGLObject glObject : s_openGLDrawData)
        {
            glBindVertexArray(glObject.VAO);
            glBindBuffer(GL_ARRAY_BUFFER, glObject.VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glObject.EBO);
            glBindTextureUnit(0, glObject.TBO);
            glDrawElements(GL_TRIANGLES, glObject.IndexCount, GL_UNSIGNED_INT, 0);
        }
    }

    void TerminateOpenGL()
    {
        for (const OpenGLGLObject& glObject : s_openGLDrawData)
        {
            glDeleteTextures(1, &glObject.TBO);
            glDeleteBuffers(1, &glObject.EBO);
            glDeleteVertexArrays(1, &glObject.VAO);
            glDeleteBuffers(1, &glObject.VBO);
        }

        if (TBO) glDeleteTextures(1, &TBO);
        if (EBO) glDeleteBuffers(1, &EBO);
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        
        glDeleteProgram(shaderProgram);
    }
}
