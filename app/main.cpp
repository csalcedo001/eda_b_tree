#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <array>
#include <vector>
#include <ctime>

#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/text2D.hpp>

#include "b_tree.hpp"
#include "drawable.hpp"

int main()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    //    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "BTree", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        
    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    //    glEnable(GL_CULL_FACE);
    
    eda::drawable::init_render();

    initText2D( "Holstein.DDS" );

    int i = 0;
    long long t = time(nullptr);
    
	eda::BTree<4, int> btree;

	btree.insert(1);
	btree.insert(4);
	btree.insert(5);
	btree.insert(1);
	btree.insert(-1);
	btree.insert(8);
	btree.insert(9);
	btree.insert(2);
	btree.insert(7);
    
	// using btree_int = eda::btree<int, 3>; 

	// btree_int bt;

	// for (size_t i = 0; i <= 1000; i++) {
	// 	bt.insert(i);
	// }

	// bt.print();

	// eda::btree_int::iterator begin = bt.find(100);
	// eda::btree_int::iterator end = bt.find(200);

	// for (auto iter = begin; iter != end; iter++ ) {
	// 	std::cout << *iter << std::endl;
	// }
    
    
    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        computeMatricesFromInputs();
        
        if (time(nullptr) - t >= 1) {
            btree.insert(i++);
            t += 1;
        }
        
        btree.render(0, 0);
        
        char title[] = "B TREE";
        printText2D(title, -2, 1, 0.5);
        

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO
    eda::drawable::cleanup_render();

    // Delete the text's VBO, the shader and the texture
    cleanupText2D();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
