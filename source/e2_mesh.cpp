#include "e2_mesh.h"

#include "obj_file.h"

struct e2_quad_face
{
    float buffer[36];
};

static
e2_quad_face
create_quad_face(vec3f p1, vec3f p2, vec3f p3, vec3f p4, vec3f normal);

e2_mesh::e2_mesh(std::string file)
{
    load_mesh_from_file(file);
}

e2_mesh::e2_mesh(e2_plane plane)
{
    for (int i = 0; i < 4; i++)
    {
        e2_vertex new_vert;
        new_vert.position.x = plane.points[i].x;
        new_vert.position.y = plane.points[i].y;
        new_vert.position.z = plane.points[i].z;

        new_vert.normal.x = plane.normal.x;
        new_vert.normal.y = plane.normal.y;
        new_vert.normal.z = plane.normal.z;

        vertices.push_back(new_vert);
    }

    faces.push_back(0);
    faces.push_back(3);
    faces.push_back(2);
    faces.push_back(2);
    faces.push_back(1);
    faces.push_back(0);
}

e2_mesh::e2_mesh(e2_box box)
{
    e2_quad_face cube_faces[6];

    cube_faces[0] = create_quad_face(box.points[0], box.points[3], box.points[2], box.points[1], Vec3f(1.0, 0.0, 0.0));
    cube_faces[1] = create_quad_face(box.points[5], box.points[0], box.points[1], box.points[6], Vec3f(0.0, 0.0, 1.0));
    cube_faces[2] = create_quad_face(box.points[6], box.points[1], box.points[2], box.points[7], Vec3f(0.0, 1.0, 0.0));
    cube_faces[3] = create_quad_face(box.points[4], box.points[5], box.points[6], box.points[7], Vec3f(-1.0, 0.0, 0.0));
    cube_faces[4] = create_quad_face(box.points[3], box.points[4], box.points[7], box.points[2], Vec3f(0.0, 0.0, -1.0));
    cube_faces[5] = create_quad_face(box.points[4], box.points[3], box.points[0], box.points[5], Vec3f(0.0, -1.0, 0.0));

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            e2_vertex new_vert;
            new_vert.position.x = cube_faces[i].buffer[(j * 6)];
            new_vert.position.y = cube_faces[i].buffer[(j * 6) + 1];
            new_vert.position.z = cube_faces[i].buffer[(j * 6) + 2];

            new_vert.normal.x = cube_faces[i].buffer[(j * 6) + 3];
            new_vert.normal.y = cube_faces[i].buffer[(j * 6) + 4];
            new_vert.normal.z = cube_faces[i].buffer[(j * 6) + 5];

            vertices.push_back(new_vert);
        }
    }

    for (int i = 0; i < 36; i++)
    {
        faces.push_back(i);
    }
}

e2_mesh::~e2_mesh()
{

}

e2_vertex
e2_mesh::get_vertex(int v_idx)
{
    return vertices[v_idx]; 
}

size_t
e2_mesh::get_vertex_count()
{
    return vertices.size();
}

size_t
e2_mesh::get_face_count()
{
    // TODO: for now, just triangles
    return (faces.size() / 3);
}

size_t
e2_mesh::get_vertex_data_size()
{
    return vertices.size();
}

size_t
e2_mesh::get_face_data_size()
{
    return faces.size();
}

e2_vertex*
e2_mesh::get_raw_vertex_data()
{
    return vertices.data();
}

unsigned int*
e2_mesh::get_raw_face_data()
{
    return faces.data();
}

bool
e2_mesh::load_mesh_from_file(std::string file)
{
    obj_file model(file);

    if (!model.read_file())
    {
        return false;
    }

    vec3f *verts, *norms;
    face3f* in_faces;
    int num_verts, num_faces, num_normals;

    model.get_vertices(&verts, num_verts);
    model.get_faces(&in_faces, num_faces); 

    if (model.has_vertex_normals())
    {
        model.get_vertex_normals(&norms, num_normals);
    }

    for (int v = 0; v < num_verts; v++)
    {
        e2_vertex vert;
        vert.position.x = verts[v].x;
        vert.position.y = verts[v].y;
        vert.position.z = verts[v].z;

        if (model.has_vertex_normals())
        {
            vert.normal.x = norms[v].x;
            vert.normal.y = norms[v].y;
            vert.normal.z = norms[v].z;
        }

        vertices.push_back(vert);
    }

    for (int i = 0; i < num_faces; i++)
    {
        faces.push_back(in_faces[i].v1);
        faces.push_back(in_faces[i].v2);
        faces.push_back(in_faces[i].v3);
    }

    return true;
}

static
e2_quad_face
create_quad_face(vec3f p1, vec3f p2, vec3f p3, vec3f p4, vec3f normal)
{
    e2_quad_face quad;

    quad.buffer[0] = p1.x;
    quad.buffer[1] = p1.y;
    quad.buffer[2] = p1.z;
    quad.buffer[3] = normal.x;
    quad.buffer[4] = normal.y;
    quad.buffer[5] = normal.z;

    quad.buffer[6] = p2.x;
    quad.buffer[7] = p2.y;
    quad.buffer[8] = p2.z;
    quad.buffer[9] = normal.x;
    quad.buffer[10] = normal.y;
    quad.buffer[11] = normal.z;

    quad.buffer[12] = p3.x;
    quad.buffer[13] = p3.y;
    quad.buffer[14] = p3.z;
    quad.buffer[15] = normal.x;
    quad.buffer[16] = normal.y;
    quad.buffer[17] = normal.z;

    quad.buffer[18] = p3.x;
    quad.buffer[19] = p3.y;
    quad.buffer[20] = p3.z;
    quad.buffer[21] = normal.x;
    quad.buffer[22] = normal.y;
    quad.buffer[23] = normal.z;

    quad.buffer[24] = p4.x;
    quad.buffer[25] = p4.y;
    quad.buffer[26] = p4.z;
    quad.buffer[27] = normal.x;
    quad.buffer[28] = normal.y;
    quad.buffer[29] = normal.z;

    quad.buffer[30] = p1.x;
    quad.buffer[31] = p1.y;
    quad.buffer[32] = p1.z;
    quad.buffer[33] = normal.x;
    quad.buffer[34] = normal.y;
    quad.buffer[35] = normal.z;

    return quad;
}

