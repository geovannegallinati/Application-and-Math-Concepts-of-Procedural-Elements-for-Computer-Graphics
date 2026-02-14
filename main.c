#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "matrix.h"
#include "geometry.h"
#include "transform.h"
#include "projection.h"
#include "render.h"
#include "pipeline.h"

#define DEFAULT_SPEED 3.0
#define FRAME_DELAY_US 33000
#define DEG_TO_RAD(d) ((d) * M_PI / 180.0)

static void sleep_ms(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

static void print_usage(const char *prog)
{
    fprintf(stderr, "Usage: %s [-w|-f|-b] [-p] [-s speed]\n", prog);
    fprintf(stderr, "\n");
    fprintf(stderr, "  -w  Wireframe only\n");
    fprintf(stderr, "  -f  Filled faces only\n");
    fprintf(stderr, "  -b  Both (wireframe + faces) [default]\n");
    fprintf(stderr, "  -p  Perspective projection (default: orthographic)\n");
    fprintf(stderr, "  -s  Rotation speed in degrees/frame (default: 3.0)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "  Ctrl+C to exit\n");
    fprintf(stderr, "\n");
}

int main(int argc, char *argv[])
{
    Model model;
    Framebuffer fb;
    Projection proj;
    RenderMode mode = RENDER_BOTH;
    int use_perspective = 0;
    double speed_deg = DEFAULT_SPEED;
    double angle_y = 0.0;
    double angle_x = DEG_TO_RAD(15.0);
    int i;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }

        if (strcmp(argv[i], "--help") == 0)
        {
            print_usage(argv[0]);
            return 0;
        }

        switch (argv[i][1])
        {
        case 'w':
            mode = RENDER_WIREFRAME;
            break;
        case 'f':
            mode = RENDER_FILLED;
            break;
        case 'b':
            mode = RENDER_BOTH;
            break;
        case 'p':
            use_perspective = 1;
            break;
        case 's':
            if (i + 1 < argc)
            {
                speed_deg = atof(argv[++i]);
            }
            break;
        case 'h':
            print_usage(argv[0]);
            return 0;
        default:
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }
    geometry_init_house(&model);
    if (use_perspective)
    {
        projection_init_perspective(&proj, FB_WIDTH, FB_HEIGHT, 5.0, 8.0);
    }
    else
    {
        projection_init_ortho(&proj, FB_WIDTH, FB_HEIGHT, 5.0);
    }
    printf("\033[2J");
    printf("\033[?25l");
    fflush(stdout);
    while (1)
    {
        fb_clear(&fb);
        pipeline_render_frame(&model, &fb, &proj, angle_y, angle_x, mode);
        fb_display(&fb);
        printf("  3D ASCII House | Ry=%.0f° Rx=%.0f° | %s | %s\n", angle_y * 180.0 / M_PI,
               angle_x * 180.0 / M_PI,
               mode == RENDER_WIREFRAME ? "Wireframe"
               : mode == RENDER_FILLED  ? "Filled"
                                        : "Both",
               use_perspective ? "Perspective" : "Orthographic");
        angle_y += DEG_TO_RAD(speed_deg);
        if (angle_y >= 2.0 * M_PI)
            angle_y -= 2.0 * M_PI;
        sleep_ms(FRAME_DELAY_US / 1000);
    }
    printf("\033[?25h");
    return 0;
}
