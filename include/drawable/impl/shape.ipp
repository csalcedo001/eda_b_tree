#ifndef B_TREE_DRAWABLE_SHAPE_IPP_
#define B_TREE_DRAWABLE_SHAPE_IPP_

#include "drawable/shape.hpp"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/text2D.hpp>

namespace eda {

namespace drawable {

GLuint vertexbuffer;
GLuint MatrixID;
GLuint programID;
GLuint VertexArrayID;

const GLfloat square_shape[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};

void init_render() {
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    
    MatrixID = glGetUniformLocation(programID, "MVP");
    

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_shape), square_shape, GL_STATIC_DRAW);
}

void cleanup_render() {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

void render_square(double x, double y) {
    glm::mat4 translation = glm::translate(glm::mat4(), glm::vec3(x, y, 0.0f));
    glm::mat4 scaling = glm::scale(glm::vec3(0.5f, 0.5f ,0.5f));

    // Omitted rotation
    
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = translation * scaling;
    
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    
    glUseProgram(programID);
    
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    
    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

    glDisableVertexAttribArray(0);
}

void render_text(int e, double x, double y) {
    char text[256];
    sprintf(text,"%d", e );
    printText2D(text, x, y, 0.2);
}

void render_shape(int e, double x, double y) {
    render_square(x, y);
    render_text(e, x, y);
}

void render_shape(std::vector<int> &v, double x, double y) {
    for (float i = 0; i < v.size(); i++) {
        render_shape(v[i], i + x + (1 - v.size()) / 2.0f, y);
    }
}

} // namespace eda

} // namespace drawable

#endif // B_TREE_DRAWABLE_SHAPE_IPP_
