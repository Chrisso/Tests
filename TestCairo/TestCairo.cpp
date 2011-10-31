// TestCairo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cairo.h>
#include <cairo-win32.h>

#define _USE_MATH_DEFINES
#include <math.h>

int _tmain(int argc, _TCHAR* argv[])
{
	cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 256, 256);
	cairo_t *cairo = cairo_create(surface);
	cairo_set_source_rgb(cairo, 0.25, 0.25, 0.25);
	cairo_paint(cairo);
	cairo_set_source_rgb(cairo, 0.0, 1.0, 0.0);
	cairo_arc(cairo, 128.0, 128.0, 100, 0, 2*M_PI);
	cairo_fill(cairo);
	cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
	cairo_select_font_face (cairo, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cairo, 64.0);
	cairo_set_source_rgb(cairo, 0.6, 0.6, 0.6);
	cairo_move_to(cairo, 78.0, 153.0);
	cairo_show_text (cairo, "OK");
	cairo_set_source_rgb(cairo, 0.0, 0.0, 1.0);
	cairo_move_to(cairo, 75.0, 150.0);
	cairo_show_text (cairo, "OK");
	cairo_destroy(cairo);
	cairo_surface_write_to_png(surface, "test-cairo.png");
	cairo_surface_destroy(surface);

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif
	return 0;
}

