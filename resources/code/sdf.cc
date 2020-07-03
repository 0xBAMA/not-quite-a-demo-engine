#include "sdf.h"
#include "debug.h"
// This contains the very high level expression of what's going on

sdf::sdf()
{
    pquit = false;

    create_window();
    gl_debug_enable();
    gl_setup();

    while(!pquit)
    {
        draw_everything();
    }
}

sdf::~sdf()
{
    quit();
}
