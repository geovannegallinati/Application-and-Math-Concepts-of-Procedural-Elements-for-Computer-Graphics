#ifndef RENDER_H
#define RENDER_H

#include "matrix.h"

#define FB_WIDTH 80
#define FB_HEIGHT 24
#define ASCII_RAMP " .,:;=+*#%@$"
#define ASCII_RAMP_LEN 12
#define WIRE_CHAR '|'

typedef struct
{
    char buffer[FB_HEIGHT][FB_WIDTH];
    double zbuffer[FB_HEIGHT][FB_WIDTH];
    int width;
    int height;
} Framebuffer;

void fb_clear(Framebuffer *fb);
void fb_set(Framebuffer *fb, int col, int row, char c);
void fb_display(const Framebuffer *fb);
void render_line(Framebuffer *fb, double x0, double y0, double x1, double y1, char c);
void render_fill_polygon(Framebuffer *fb, const double *verts_x, const double *verts_y, int n,
                         char c);
char render_shade(Vec3 normal, Vec3 light_dir);

#endif
