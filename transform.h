#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"

void transform_translation(double tx, double ty, double tz, Mat4 *out);
void transform_scale(double sx, double sy, double sz, Mat4 *out);
void transform_rotation_x(double theta, Mat4 *out);
void transform_rotation_y(double theta, Mat4 *out);
void transform_rotation_z(double theta, Mat4 *out);
void transform_rotate_y_around(double theta, double cx, double cy, double cz, Mat4 *out);
void transform_rotate_x_around(double theta, double cx, double cy, double cz, Mat4 *out);

#endif
