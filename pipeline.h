#ifndef PIPELINE_H
#define PIPELINE_H

#include "geometry.h"
#include "projection.h"
#include "render.h"

typedef enum
{
    RENDER_WIREFRAME,
    RENDER_FILLED,
    RENDER_BOTH
} RenderMode;

void pipeline_render_frame(Model *model, Framebuffer *fb, const Projection *proj, double angle_y,
                           double angle_x, RenderMode mode);

#endif
