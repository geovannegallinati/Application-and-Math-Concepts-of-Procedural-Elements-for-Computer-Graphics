#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

static const char ascii_ramp[] = ASCII_RAMP;

void fb_clear(Framebuffer *fb)
{
    int r, c;
    fb->width = FB_WIDTH;
    fb->height = FB_HEIGHT;
    for (r = 0; r < FB_HEIGHT; r++)
    {
        for (c = 0; c < FB_WIDTH; c++)
        {
            fb->buffer[r][c] = ' ';
            fb->zbuffer[r][c] = 1e30;
        }
    }
}

void fb_set(Framebuffer *fb, int col, int row, char c)
{
    if (col >= 0 && col < fb->width && row >= 0 && row < fb->height)
    {
        fb->buffer[row][col] = c;
    }
}

void fb_display(const Framebuffer *fb)
{
    int r;
    printf("\033[H");
    for (r = 0; r < fb->height; r++)
    {
        fwrite(fb->buffer[r], 1, fb->width, stdout);
        putchar('\n');
    }
    fflush(stdout);
}

void render_line(Framebuffer *fb, double x0, double y0, double x1, double y1, char c)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    int steps;
    double x_inc, y_inc;
    double x, y;
    int i;
    int abs_dx = (int)(fabs(dx) + 0.5);
    int abs_dy = (int)(fabs(dy) + 0.5);
    steps = abs_dx > abs_dy ? abs_dx : abs_dy;
    if (steps == 0)
    {
        fb_set(fb, (int)(x0 + 0.5), (int)(y0 + 0.5), c);
        return;
    }
    x_inc = dx / (double)steps;
    y_inc = dy / (double)steps;
    x = x0;
    y = y0;
    for (i = 0; i <= steps; i++)
    {
        fb_set(fb, (int)(x + 0.5), (int)(y + 0.5), c);
        x += x_inc;
        y += y_inc;
    }
}

void render_fill_polygon(Framebuffer *fb, const double *verts_x, const double *verts_y, int n,
                         char c)
{
    int i, j, y;
    double ymin_d = verts_y[0], ymax_d = verts_y[0];
    int ymin, ymax;
    double intersections[20];
    int num_intersections;
    for (i = 1; i < n; i++)
    {
        if (verts_y[i] < ymin_d)
            ymin_d = verts_y[i];
        if (verts_y[i] > ymax_d)
            ymax_d = verts_y[i];
    }
    ymin = (int)(ymin_d + 0.5);
    ymax = (int)(ymax_d + 0.5);
    if (ymin < 0)
        ymin = 0;
    if (ymax >= fb->height)
        ymax = fb->height - 1;
    for (y = ymin; y <= ymax; y++)
    {
        num_intersections = 0;
        for (i = 0; i < n; i++)
        {
            j = (i + 1) % n;
            double y1 = verts_y[i];
            double y2 = verts_y[j];
            double x1 = verts_x[i];
            double x2 = verts_x[j];
            if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y))
            {
                double t = ((double)y - y1) / (y2 - y1);
                double x_int = x1 + t * (x2 - x1);
                if (num_intersections < 20)
                {
                    intersections[num_intersections++] = x_int;
                }
            }
        }
        for (i = 1; i < num_intersections; i++)
        {
            double key = intersections[i];
            j = i - 1;
            while (j >= 0 && intersections[j] > key)
            {
                intersections[j + 1] = intersections[j];
                j--;
            }
            intersections[j + 1] = key;
        }
        for (i = 0; i + 1 < num_intersections; i += 2)
        {
            int xstart = (int)(intersections[i] + 0.5);
            int xend = (int)(intersections[i + 1] + 0.5);
            if (xstart < 0)
                xstart = 0;
            if (xend >= fb->width)
                xend = fb->width - 1;
            int col;
            for (col = xstart; col <= xend; col++)
            {
                fb->buffer[y][col] = c;
            }
        }
    }
}

char render_shade(Vec3 normal, Vec3 light_dir)
{
    Vec3 n = vec3_normalize(normal);
    Vec3 l = vec3_normalize(light_dir);
    double dot = vec3_dot(n, l);
    if (dot < 0.0)
        dot = 0.0;
    double ambient = 0.15;
    double diffuse = 0.85;
    double intensity = ambient + diffuse * dot;
    if (intensity > 1.0)
        intensity = 1.0;
    int idx = (int)(intensity * (ASCII_RAMP_LEN - 1) + 0.5);
    if (idx < 0)
        idx = 0;
    if (idx >= ASCII_RAMP_LEN)
        idx = ASCII_RAMP_LEN - 1;
    return ascii_ramp[idx];
}
