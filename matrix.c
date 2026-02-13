#include "matrix.h"
#include <math.h>
#include <string.h>

void mat4_identity(Mat4 *m)
{
    memset(m->m, 0, sizeof(m->m));
    m->m[0][0] = 1.0;
    m->m[1][1] = 1.0;
    m->m[2][2] = 1.0;
    m->m[3][3] = 1.0;
}

void mat4_zero(Mat4 *m)
{
    memset(m->m, 0, sizeof(m->m));
}

void mat4_copy(const Mat4 *src, Mat4 *dst)
{
    memcpy(dst->m, src->m, sizeof(src->m));
}

void mat4_multiply(const Mat4 *A, const Mat4 *B, Mat4 *result)
{
    Mat4 temp;
    int i, j, k;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp.m[i][j] = 0.0;
            for (k = 0; k < 4; k++)
            {
                temp.m[i][j] += A->m[i][k] * B->m[k][j];
            }
        }
    }
    mat4_copy(&temp, result);
}

void mat4_transform_point(const Mat4 *M, const Vec4 *p, Vec4 *result)
{
    Vec4 temp;
    int j, i;
    for (j = 0; j < 4; j++)
    {
        temp.v[j] = 0.0;
        for (i = 0; i < 4; i++)
        {
            temp.v[j] += p->v[i] * M->m[i][j];
        }
    }
    *result = temp;
}

Vec4 vec4_create(double x, double y, double z)
{
    Vec4 v;
    v.v[0] = x;
    v.v[1] = y;
    v.v[2] = z;
    v.v[3] = 1.0;
    return v;
}

Vec4 vec4_create_w(double x, double y, double z, double w)
{
    Vec4 v;
    v.v[0] = x;
    v.v[1] = y;
    v.v[2] = z;
    v.v[3] = w;
    return v;
}

Vec3 vec3_create(double x, double y, double z)
{
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

double vec3_dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_sub(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

double vec3_length(Vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3 vec3_normalize(Vec3 v)
{
    double len = vec3_length(v);
    Vec3 result;
    if (len > 1e-10)
    {
        result.x = v.x / len;
        result.y = v.y / len;
        result.z = v.z / len;
    }
    else
    {
        result.x = result.y = result.z = 0.0;
    }
    return result;
}
