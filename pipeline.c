#include "pipeline.h"
#include "transform.h"
#include <stdlib.h>
#include <math.h>

static const Vec3 LIGHT_DIR = {0.5, 0.8, 0.6};

typedef struct
{
    int face_idx;
    double avg_z;
} FaceDepth;
static int compare_face_depth(const void *a, const void *b)
{
    const FaceDepth *fa = (const FaceDepth *)a;
    const FaceDepth *fb = (const FaceDepth *)b;
    if (fa->avg_z < fb->avg_z)
        return -1;
    if (fa->avg_z > fb->avg_z)
        return 1;
    return 0;
}

void pipeline_render_frame(Model *model, Framebuffer *fb, const Projection *proj, double angle_y,
                           double angle_x, RenderMode mode)
{
    Mat4 rot_y, rot_x, composite;
    int i;
    FaceDepth visible_faces[HOUSE_NUM_FACES];
    int num_visible = 0;
    transform_rotate_y_around(angle_y, model->center_x, model->center_y, model->center_z, &rot_y);
    transform_rotate_x_around(angle_x, model->center_x, model->center_y, model->center_z, &rot_x);
    mat4_multiply(&rot_y, &rot_x, &composite);
    for (i = 0; i < model->num_vertices; i++)
    {
        mat4_transform_point(&composite, &model->vertices[i], &model->transformed[i]);
    }
    for (i = 0; i < model->num_faces; i++)
    {
        Vec3 normal = geometry_face_normal(model, i);
        if (normal.z > 0)
        {
            visible_faces[num_visible].face_idx = i;
            visible_faces[num_visible].avg_z = geometry_face_avg_z(model, i);
            num_visible++;
        }
    }
    qsort(visible_faces, num_visible, sizeof(FaceDepth), compare_face_depth);
    for (i = 0; i < num_visible; i++)
    {
        int fi = visible_faces[i].face_idx;
        const Face *face = &model->faces[fi];
        double px[MAX_FACE_VERTS], py[MAX_FACE_VERTS];
        int v, valid = 1;
        for (v = 0; v < face->num_verts; v++)
        {
            int idx = face->indices[v];
            if (!projection_project(proj, &model->transformed[idx], &px[v], &py[v]))
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
            continue;
        if (mode == RENDER_FILLED || mode == RENDER_BOTH)
        {
            Vec3 normal = geometry_face_normal(model, fi);
            char shade_char = render_shade(normal, LIGHT_DIR);
            render_fill_polygon(fb, px, py, face->num_verts, shade_char);
        }
        if (mode == RENDER_WIREFRAME || mode == RENDER_BOTH)
        {
            for (v = 0; v < face->num_verts; v++)
            {
                int next = (v + 1) % face->num_verts;
                render_line(fb, px[v], py[v], px[next], py[next], WIRE_CHAR);
            }
        }
    }
}
