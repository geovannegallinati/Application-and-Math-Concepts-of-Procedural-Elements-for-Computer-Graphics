#ifndef PROJECTION_H
#define PROJECTION_H

#include "matrix.h"

typedef enum
{
    PROJ_ORTHOGRAPHIC,
    PROJ_PERSPECTIVE
} ProjectionType;

typedef struct
{
    ProjectionType type;
    double d;
    int vp_width;
    int vp_height;
    double scale;
    double aspect_fix;
} Projection;

void projection_init_ortho(Projection *proj, int vp_width, int vp_height, double scale);
void projection_init_perspective(Projection *proj, int vp_width, int vp_height, double scale,
                                 double focal_distance);
int projection_project(const Projection *proj, const Vec4 *p3d, double *screen_x, double *screen_y);

#endif
