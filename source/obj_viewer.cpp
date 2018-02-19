#include "obj_file.h"

int
main(int argc, char** argv)
{
    obj_file my_obj("capsule.obj"); 
    my_obj.read_file();
}
