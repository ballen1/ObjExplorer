#ifndef H_OBJ_VIEWER
#define H_OBJ_VIEWER

#define OBJ_VIEWER_WINDOW_WIDTH 600
#define OBJ_VIEWER_WINDOW_HEIGHT 600 

#define OBJ_VIEWER_VIEWPORT_WIDTH OBJ_VIEWER_WINDOW_WIDTH
#define OBJ_VIEWER_VIEWPORT_HEIGHT OBJ_VIEWER_WINDOW_HEIGHT

float test_vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f 
};

unsigned int test_indices[] = {  // note that we start from 0!
    0, 1, 3,
    1, 2, 3
};

#endif
