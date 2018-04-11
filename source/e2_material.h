#ifndef H_E2_MATERIAL
#define H_E2_MATERIAL

#include "e2_types.h"

class e2_material
{
public:
    e2_material(e2_colour col);
    ~e2_material();

    e2_colour colour;
};

#endif
