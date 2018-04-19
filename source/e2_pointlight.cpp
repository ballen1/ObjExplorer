#include "e2_pointlight.h"

e2_pointlight::e2_pointlight(vec3f pos, e2_colour a_col, e2_colour d_col)
{
    position = pos;
    ambient_colour = a_col;
    diffuse_colour = d_col;
}

e2_pointlight::~e2_pointlight()
{

}
