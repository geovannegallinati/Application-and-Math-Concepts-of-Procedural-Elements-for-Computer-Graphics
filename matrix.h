#ifndef MATRIX_H
#define MATRIX_H
typedef struct
{
    double m[4][4];
} Mat4;

typedef struct
{
    double v[4];
} Vec4;

typedef struct
{
    double x, y, z;
} Vec3;

void mat4_identity(Mat4 *m);
void mat4_zero(Mat4 *m);
void mat4_copy(const Mat4 *src, Mat4 *dst);
void mat4_multiply(const Mat4 *A, const Mat4 *B, Mat4 *result);
void mat4_transform_point(const Mat4 *M, const Vec4 *p, Vec4 *result);
Vec4 vec4_create(double x, double y, double z);
Vec4 vec4_create_w(double x, double y, double z, double w);
Vec3 vec3_create(double x, double y, double z);
Vec3 vec3_cross(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_normalize(Vec3 v);
double vec3_length(Vec3 v);

#endif
