#include "geometry.h"

void geometry_init_house(Model *model)
{
    model->vertices[0] = vec4_create(-1.0, -1.0, 1.0);
    model->vertices[1] = vec4_create(1.0, -1.0, 1.0);
    model->vertices[2] = vec4_create(1.0, 1.0, 1.0);
    model->vertices[3] = vec4_create(-1.0, 1.0, 1.0);
    model->vertices[4] = vec4_create(-1.0, -1.0, -1.0);
    model->vertices[5] = vec4_create(1.0, -1.0, -1.0);
    model->vertices[6] = vec4_create(1.0, 1.0, -1.0);
    model->vertices[7] = vec4_create(-1.0, 1.0, -1.0);
    model->vertices[8] = vec4_create(0.0, 2.0, 1.0);
    model->vertices[9] = vec4_create(0.0, 2.0, -1.0);
    model->num_vertices = HOUSE_NUM_VERTICES;
    int f = 0;
    model->faces[f].indices[0] = 0;
    model->faces[f].indices[1] = 1;
    model->faces[f].indices[2] = 2;
    model->faces[f].indices[3] = 3;
    model->faces[f].num_verts = 4;
    f++;
    model->faces[f].indices[0] = 5;
    model->faces[f].indices[1] = 4;
    model->faces[f].indices[2] = 7;
    model->faces[f].indices[3] = 6;
    model->faces[f].num_verts = 4;
    f++;
    model->faces[f].indices[0] = 4;
    model->faces[f].indices[1] = 0;
    model->faces[f].indices[2] = 3;
    model->faces[f].indices[3] = 7;
    model->faces[f].num_verts = 4;
    f++;
    model->faces[f].indices[0] = 1;
    model->faces[f].indices[1] = 5;
    model->faces[f].indices[2] = 6;
    model->faces[f].indices[3] = 2;
    model->faces[f].num_verts = 4;
    f++;
    model->faces[f].indices[0] = 4;
    model->faces[f].indices[1] = 5;
    model->faces[f].indices[2] = 1;
    model->faces[f].indices[3] = 0;
    model->faces[f].num_verts = 4;
    f++;
    model->faces[f].indices[0] = 3;
    model->faces[f].indices[1] = 2;
    model->faces[f].indices[2] = 8;
    model->faces[f].num_verts = 3;
    f++;
    model->faces[f].indices[0] = 6;
    model->faces[f].indices[1] = 7;
    model->faces[f].indices[2] = 9;
    model->faces[f].num_verts = 3;
    f++;
    model->faces[f].indices[0] = 7;
    model->faces[f].indices[1] = 3;
    model->faces[f].indices[2] = 8;
    model->faces[f].indices[3] = 9;
    model->faces[f].num_verts = 4;
    f++;
    model->faces[f].indices[0] = 2;
    model->faces[f].indices[1] = 6;
    model->faces[f].indices[2] = 9;
    model->faces[f].indices[3] = 8;
    model->faces[f].num_verts = 4;
    f++;
    model->num_faces = f;
    geometry_compute_center(model);
}

void geometry_compute_center(Model *model)
{
    double cx = 0, cy = 0, cz = 0;
    int i;
    for (i = 0; i < model->num_vertices; i++)
    {
        cx += model->vertices[i].v[0];
        cy += model->vertices[i].v[1];
        cz += model->vertices[i].v[2];
    }
    model->center_x = cx / model->num_vertices;
    model->center_y = cy / model->num_vertices;
    model->center_z = cz / model->num_vertices;
}

Vec3 geometry_face_normal(const Model *model, int face_idx)
{
    const Face *face = &model->faces[face_idx];
    const Vec4 *v0 = &model->transformed[face->indices[0]];
    const Vec4 *v1 = &model->transformed[face->indices[1]];
    const Vec4 *v2 = &model->transformed[face->indices[2]];
    Vec3 p0 = vec3_create(v0->v[0], v0->v[1], v0->v[2]);
    Vec3 p1 = vec3_create(v1->v[0], v1->v[1], v1->v[2]);
    Vec3 p2 = vec3_create(v2->v[0], v2->v[1], v2->v[2]);
    Vec3 e1 = vec3_sub(p1, p0);
    Vec3 e2 = vec3_sub(p2, p0);
    return vec3_cross(e1, e2);
}

double geometry_face_avg_z(const Model *model, int face_idx)
{
    const Face *face = &model->faces[face_idx];
    double sum_z = 0;
    int i;
    for (i = 0; i < face->num_verts; i++)
    {
        sum_z += model->transformed[face->indices[i]].v[2];
    }
    return sum_z / face->num_verts;
}
