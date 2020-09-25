#include <vector>
#include <cstring>
#include <stdio.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include "shader.hpp"
#include "texture.hpp"
#include <common/controls.hpp>

#include "text2D.hpp"

unsigned int Text2DTextureID;
unsigned int Text2DVertexBufferID;
unsigned int Text2DUVBufferID;
unsigned int Text2DShaderID;
unsigned int Text2DUniformID;
unsigned int Text2DMatrixID;

void initText2D(const char * texturePath){

    // Initialize texture
    Text2DTextureID = loadDDS(texturePath);

    // Initialize VBO
    glGenBuffers(1, &Text2DVertexBufferID);
    glGenBuffers(1, &Text2DUVBufferID);

    // Initialize Shader
    Text2DShaderID = LoadShaders( "TextVertexShader.vertexshader", "TextVertexShader.fragmentshader" );

    // Initialize uniforms' IDs
    Text2DUniformID = glGetUniformLocation( Text2DShaderID, "myTextureSampler" );
    Text2DMatrixID = glGetUniformLocation( Text2DShaderID, "MVP" );

}

void printText2D(const char * text, float x, float y, float size){

    unsigned int length = strlen(text);

    // Fill buffers
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> UVs;
    for ( unsigned int i=0 ; i<length ; i++ ){
        
        glm::vec3 vertex_up_left    = glm::vec3( i*size     , size , 0);
        glm::vec3 vertex_up_right   = glm::vec3( i*size+size, size , 0);
        glm::vec3 vertex_down_right = glm::vec3( i*size+size, 0      , 0);
        glm::vec3 vertex_down_left  = glm::vec3( i*size     , 0      , 0);

        vertices.push_back(vertex_up_left   );
        vertices.push_back(vertex_down_left );
        vertices.push_back(vertex_up_right  );

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        char character = text[i];
        float uv_x = (character%16)/16.0f;
        float uv_y = (character/16)/16.0f;

        glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
        glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
        glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
        glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
        UVs.push_back(uv_up_left   );
        UVs.push_back(uv_down_left );
        UVs.push_back(uv_up_right  );

        UVs.push_back(uv_down_right);
        UVs.push_back(uv_up_right);
        UVs.push_back(uv_down_left);
    }
    glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

    // Bind shader
    glUseProgram(Text2DShaderID);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    
    
    
    glm::mat4 Projection = getProjectionMatrix();
    glm::mat4 View = getViewMatrix();
    
    glm::mat4 Translation = glm::translate(glm::mat4(), glm::vec3(x - 0.4, y, 0.51f));
    glm::mat4 Scaling = glm::scale(glm::vec3(1.0f, 1.0f ,1.0f));
    
    glm::mat4 Model = Translation * Scaling;
    
    glm::mat4 MVP = Projection * View * Model;
    
//    glm::mat4 MVP(1);
    
    glUniformMatrix4fv(Text2DMatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    glUniform1i(Text2DUniformID, 0);
    

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw call
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

    glDisable(GL_BLEND);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void cleanupText2D(){

    // Delete buffers
    glDeleteBuffers(1, &Text2DVertexBufferID);
    glDeleteBuffers(1, &Text2DUVBufferID);

    // Delete texture
    glDeleteTextures(1, &Text2DTextureID);

    // Delete shader
    glDeleteProgram(Text2DShaderID);
}
