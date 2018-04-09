#include "e2_mesh.h"

#include "obj_file.h"

e2_mesh::e2_mesh(std::string file)
{
    load_mesh_from_file(file);
}

e2_mesh::e2_mesh(e2_plane plane)
{
    for (int i = 0; i < 4; i++)
    {
        vertices.push_back(plane.points[i].x);
        vertices.push_back(plane.points[i].y);
        vertices.push_back(plane.points[i].z);

        normals.push_back(plane.normal.x);
        normals.push_back(plane.normal.y);
        normals.push_back(plane.normal.z);
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
    for (int i = 0; i < 6; i++)
    {

    }

    for (int i = 0; i < 36; i++)
    {
        faces.push_back(i);
    }
}

e2_mesh::~e2_mesh()
{

}

vec3f
e2_mesh::get_vertex(int v_idx)
{
    vec3f vert;

    vert.x = vertices[v_idx * E2_MESH_VERTEX_TUPLE_SIZE];
    vert.y = vertices[(v_idx * E2_MESH_VERTEX_TUPLE_SIZE) + 1];
    vert.z = vertices[(v_idx * E2_MESH_VERTEX_TUPLE_SIZE) + 2];

    return vert;
}

size_t
e2_mesh::get_vertex_count()
{
    return (vertices.size() / 3);
}

size_t
e2_mesh::get_normal_count()
{
    return (normals.size() / 3);
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
e2_mesh::get_normal_data_size()
{
    return normals.size();
}

size_t
e2_mesh::get_face_data_size()
{
    return faces.size();
}

float*
e2_mesh::get_raw_vertex_data()
{
    return vertices.data();
}

float*
e2_mesh::get_raw_normal_data()
{
    return normals.data();
}

unsigned int*
e2_mesh::get_raw_face_data()
{
    return faces.data();
}

void
e2_mesh::set_vertex_normal(int v_idx, vec3f norm)
{
    normals[v_idx * E2_MESH_VERTEX_TUPLE_SIZE] = norm.x;
    normals[(v_idx * E2_MESH_VERTEX_TUPLE_SIZE) + 1] = norm.y;
    normals[(v_idx * E2_MESH_VERTEX_TUPLE_SIZE) + 2] = norm.z;
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
    else
    {
        normals.resize(num_verts);
    }

    for (int v = 0; v < num_verts; v++)
    {
        vertices.push_back(verts[v].x);
        vertices.push_back(verts[v].y);
        vertices.push_back(verts[v].z);

        if (model.has_vertex_normals())
        {
            normals.push_back(norms[v].x);
            normals.push_back(norms[v].y);
            normals.push_back(norms[v].z);
        }
    }

    for (int i = 0; i < num_faces; i++)
    {
        faces.push_back(in_faces[i].v1);
        faces.push_back(in_faces[i].v2);
        faces.push_back(in_faces[i].v3);

        if (!model.has_vertex_normals())
        {
            vec3f v1, v2, v3;
            v1 = get_vertex(in_faces[i].v1);
            v2 = get_vertex(in_faces[i].v2);
            v3 = get_vertex(in_faces[i].v3);

            vec3f v_u = subtract(v1, v2);
            vec3f v_w = subtract(v1, v3);

            vec3f v_n = cross_product(v_u, v_w);
            v_n = normalize(v_n);

            set_vertex_normal(in_faces[i].v1, v_n);
            set_vertex_normal(in_faces[i].v2, v_n);
            set_vertex_normal(in_faces[i].v3, v_n);
        }
    }

    return true;
}
