#ifndef H_OBJ_FILE
#define H_OBJ_FILE

#include <string>
#include <vector>

#include "obj_math.h"

class obj_file
{
public:
    obj_file();
    obj_file(std::string file_path);
    ~obj_file();

    bool read_file();

    void get_vertices(vec3f* vert_arr, int& size);
    void get_uvs(tex2f* uv_arr, int& size);
    void get_faces(face3f* face_arr, int& size);

private:
    std::string file_path;
    std::vector<vec3f> vertices;
    std::vector<tex2f> uvs;
    std::vector<face3f> faces;
};

#endif
