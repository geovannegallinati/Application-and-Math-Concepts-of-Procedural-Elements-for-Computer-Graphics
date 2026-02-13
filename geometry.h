#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "matrix.h"

#define MAX_FACE_VERTS 4
#define HOUSE_NUM_VERTICES 10
#define HOUSE_NUM_FACES 9

typedef struct
{
    int indices[MAX_FACE_VERTS];
    int num_verts;
} Face;

typedef struct
{
    Vec4 vertices[HOUSE_NUM_VERTICES];
    Vec4 transformed[HOUSE_NUM_VERTICES];
    Face faces[HOUSE_NUM_FACES];
    int num_vertices;
    int num_faces;
    double center_x, center_y, center_z;
} Model;

void geometry_init_house(Model *model);
void geometry_compute_center(Model *model);
Vec3 geometry_face_normal(const Model *model, int face_idx);
double geometry_face_avg_z(const Model *model, int face_idx);

#endif
