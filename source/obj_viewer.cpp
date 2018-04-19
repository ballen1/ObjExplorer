#include "obj_viewer.h"
#include "obj_file.h"
#include "BAL_ShaderUtility.h"
#include "e2_math.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "e2_mesh.h"
#include "e2_render.h"
#include "e2_render_object.h"
#include "e2_material.h"
#include "e2_types.h"

perspective_projection p;
first_person_camera camera;

float last_time = -1;
float delta_time = -1;
float last_mouse_x = -1;
float last_mouse_y = -1;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void process_input(GLFWwindow* window);

int
main(int argc, char** argv)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    last_time = glfwGetTime();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(OBJ_VIEWER_WINDOW_WIDTH, OBJ_VIEWER_WINDOW_HEIGHT,
                                "Teapot Teapot Teapot Teapot Teapot Teapot Teapot Teapot", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to get OpenGL proc address\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, OBJ_VIEWER_VIEWPORT_WIDTH, OBJ_VIEWER_VIEWPORT_HEIGHT);

    e2_render renderer;

    GLuint shader_program;
    if (CreateShaderProgram(&shader_program, "data\\shaders\\vertex.vert", "data\\shaders\\fragment.frag"))
    {
        renderer.set_shader_program(shader_program);

        vec3f light_pos;
        light_pos.x = -500;
        light_pos.y = 500;
        light_pos.z = 500;
        e2_colour light_col;
        light_col.r = 1.0;
        light_col.g = 1.0;
        light_col.b = 1.0;
        e2_pointlight main_light(light_pos, light_col);
        main_light.ambient_strength = 0.1;
        main_light.diffuse_strength = 1.0; 

        renderer.add_pointlight(&main_light);

        light_pos.x = 500;
        light_pos.y = 1500;
        light_pos.z = -500;
        light_col.r = 0.0;
        light_col.g = 1.0;
        light_col.b = 0.0;

        e2_pointlight sec_light(light_pos, light_col);
        sec_light.ambient_strength = 0.1;
        sec_light.diffuse_strength = 1.0;

        renderer.add_pointlight(&sec_light);

        e2_colour c1;
        c1.r = 0.2;
        c1.g = 1;
        c1.b = 1;

        e2_colour c2;
        c2.r = 1.0;
        c2.g = 0.2;
        c2.b = 0.8;
        
        e2_material mat1(c1);
        e2_material mat2(c2);

        e2_mesh mesh("donut5.obj");
        e2_mesh mesh2("donut5.obj");

        e2_plane myplane = define_plane(1000.0f);
        e2_mesh mesh3(myplane);
        
        e2_box mybox = define_box(200.0);
        e2_mesh mesh4(mybox);

        mat4f plane_trans = Mat4f();
        plane_trans.mat[13] = -50.0;
        e2_render_object object1(&mesh, Mat4f());

        mat4f teapot_loc = Mat4f();
        teapot_loc.mat[13] = 100.0f;

        e2_render_object object2(&mesh2, teapot_loc);
        e2_render_object object3(&mesh3, plane_trans);

        mat4f box_trans = Mat4f();
        box_trans.mat[12] = 1000.0;
        box_trans.mat[13] = 300.0;
        e2_render_object object4(&mesh4, box_trans);

        object1.assign_material(&mat1);
        object2.assign_material(&mat2);
        object3.assign_material(&mat1);
        object4.assign_material(&mat2);

        renderer.submit_render_object(&object1);
        renderer.submit_render_object(&object2);
        renderer.submit_render_object(&object3);
        renderer.submit_render_object(&object4);

        renderer.update_render_buffer();

        // Matrix stuff is gonna go here.
        mat4f model = Mat4f();

        camera.position.x = 0.0f;
        camera.position.y = 0.0f;
        camera.position.z = 250.0f;

        camera.pitch = 0.0f;
        camera.yaw = 0.0f;

        mat4f view = get_view_matrix(camera);
        
        p.width = OBJ_VIEWER_WINDOW_WIDTH;
        p.height = OBJ_VIEWER_WINDOW_HEIGHT;
        p.vertical_fov = 45.0f;
        p.near_plane = 0.1f;
        p.far_plane = 100000.0f;
        
        mat4f projection_mat = get_perspective_projection(p);

        int uniform_loc;

        uniform_loc = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, view.mat);

        uniform_loc = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, projection_mat.mat);
    
        while (!glfwWindowShouldClose(window))
        {
            float current_time = glfwGetTime();
            delta_time = current_time - last_time;
            last_time = current_time;

            process_input(window);

            view = get_view_matrix(camera);

            uniform_loc = glGetUniformLocation(shader_program, "view");
            glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, view.mat);

            projection_mat = get_perspective_projection(p);

            uniform_loc = glGetUniformLocation(shader_program, "projection");
            glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, projection_mat.mat);

            renderer.render_frame();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
}

void
framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    p.width = width;
    p.height = height;
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
    if (last_mouse_x < 0 && last_mouse_y < 0)
    {
        last_mouse_x = x_pos;
        last_mouse_y = y_pos;
    }
    else
    {
        float x_offset = x_pos - last_mouse_x;
        float y_offset = y_pos - last_mouse_y;

        camera.yaw += (x_offset * OBJ_VIEWER_CAMERA_MOUSE_SENSITIVITY * delta_time);
        camera.pitch += (y_offset * OBJ_VIEWER_CAMERA_MOUSE_SENSITIVITY * delta_time);

        last_mouse_x = x_pos;
        last_mouse_y = y_pos;
    }
}

void
process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        vec3f forward = get_first_person_camera_front(camera);
        forward = s_multiply(forward, (delta_time * OBJ_VIEWER_CAMERA_MOVEMENT_COEF));
        camera.position = add(camera.position, forward);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        vec3f forward = get_first_person_camera_front(camera);
        forward = s_multiply(forward, (delta_time * OBJ_VIEWER_CAMERA_MOVEMENT_COEF));
        camera.position = subtract(forward, camera.position);
       
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        vec3f right = get_first_person_camera_right(camera);
        right = s_multiply(right, (delta_time * OBJ_VIEWER_CAMERA_MOVEMENT_COEF));
        camera.position = subtract(right, camera.position);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        vec3f right = get_first_person_camera_right(camera);
        right = s_multiply(right, (delta_time * OBJ_VIEWER_CAMERA_MOVEMENT_COEF));
        camera.position = add(right, camera.position);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        vec3f forward = get_first_person_camera_front(camera);
        vec3f right = get_first_person_camera_right(camera);
        vec3f up = cross_product(right, forward);
        up = s_multiply(up, (delta_time * OBJ_VIEWER_CAMERA_MOVEMENT_COEF));
        camera.position = add(camera.position, up);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        vec3f forward = get_first_person_camera_front(camera);
        vec3f right = get_first_person_camera_right(camera);
        vec3f down = cross_product(forward, right);
        down = s_multiply(down, (delta_time * OBJ_VIEWER_CAMERA_MOVEMENT_COEF));
        camera.position = add(camera.position, down);
    }
}
