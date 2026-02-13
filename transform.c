#include "transform.h"
#include <math.h>

void transform_translation(double tx, double ty, double tz, Mat4 *out)
{
    mat4_identity(out);
    out->m[3][0] = tx;
    out->m[3][1] = ty;
    out->m[3][2] = tz;
}

void transform_scale(double sx, double sy, double sz, Mat4 *out)
{
    mat4_identity(out);
    out->m[0][0] = sx;
    out->m[1][1] = sy;
    out->m[2][2] = sz;
}

void transform_rotation_x(double theta, Mat4 *out)
{
    double c = cos(theta);
    double s = sin(theta);
    mat4_identity(out);
    out->m[1][1] = c;
    out->m[1][2] = s;
    out->m[2][1] = -s;
    out->m[2][2] = c;
}

void transform_rotation_y(double theta, Mat4 *out)
{
    double c = cos(theta);
    double s = sin(theta);
    mat4_identity(out);
    out->m[0][0] = c;
    out->m[0][2] = -s;
    out->m[2][0] = s;
    out->m[2][2] = c;
}

void transform_rotation_z(double theta, Mat4 *out)
{
    double c = cos(theta);
    double s = sin(theta);
    mat4_identity(out);
    out->m[0][0] = c;
    out->m[0][1] = s;
    out->m[1][0] = -s;
    out->m[1][1] = c;
}

void transform_rotate_y_around(double theta, double cx, double cy, double cz, Mat4 *out)
{
    Mat4 t1, r, t2, temp;
    transform_translation(-cx, -cy, -cz, &t1);
    transform_rotation_y(theta, &r);
    transform_translation(cx, cy, cz, &t2);
    mat4_multiply(&t1, &r, &temp);
    mat4_multiply(&temp, &t2, out);
}

void transform_rotate_x_around(double theta, double cx, double cy, double cz, Mat4 *out)
{
    Mat4 t1, r, t2, temp;
    transform_translation(-cx, -cy, -cz, &t1);
    transform_rotation_x(theta, &r);
    transform_translation(cx, cy, cz, &t2);
    mat4_multiply(&t1, &r, &temp);
    mat4_multiply(&temp, &t2, out);
}
