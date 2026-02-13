#include "projection.h"

void projection_init_ortho(Projection *proj, int vp_width, int vp_height, double scale)
{
    proj->type = PROJ_ORTHOGRAPHIC;
    proj->d = 0.0;
    proj->vp_width = vp_width;
    proj->vp_height = vp_height;
    proj->scale = scale;
    proj->aspect_fix = 2.0;
}

void projection_init_perspective(Projection *proj, int vp_width, int vp_height, double scale,
                                 double focal_distance)
{
    proj->type = PROJ_PERSPECTIVE;
    proj->d = focal_distance;
    proj->vp_width = vp_width;
    proj->vp_height = vp_height;
    proj->scale = scale;
    proj->aspect_fix = 2.0;
}

int projection_project(const Projection *proj, const Vec4 *p3d, double *screen_x, double *screen_y)
{
    double x = p3d->v[0];
    double y = p3d->v[1];
    double z = p3d->v[2];
    double x2d, y2d;
    if (proj->type == PROJ_PERSPECTIVE)
    {
        double w = 1.0 - z / proj->d;
        if (w <= 0.001)
        {
            return 0;
        }
        x2d = x / w;
        y2d = y / w;
    }
    else
    {
        x2d = x;
        y2d = y;
    }
    *screen_x = x2d * proj->scale * proj->aspect_fix + proj->vp_width / 2.0;
    *screen_y = proj->vp_height / 2.0 - y2d * proj->scale;
    return 1;
}
