// TestBarcode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cairo.h>
#include <cairo-win32.h>
#include <zint.h>

int _tmain(int argc, _TCHAR* argv[])
{
	zint_symbol *barcode = ZBarcode_Create();
	if (barcode)
	{
		_tprintf(_T("Generating code...\n"));

		barcode->symbology = BARCODE_CODE128; //BARCODE_QRCODE;
		barcode->show_hrt  = FALSE;
		switch (ZBarcode_Encode(barcode, reinterpret_cast<unsigned char*>("http://christoph.stoepel.net/"), 0))
		{
			case WARN_INVALID_OPTION:	 _tprintf(_T("\tWARN_INVALID_OPTION\n"));	 break;
			case ERROR_TOO_LONG:		 _tprintf(_T("\tERROR_TOO_LONG\n"));		 break;
			case ERROR_INVALID_DATA:	 _tprintf(_T("\tERROR_INVALID_DATA\n"));	 break;
			case ERROR_INVALID_CHECK:	 _tprintf(_T("\tERROR_INVALID_CHECK\n"));	 break;
			case ERROR_INVALID_OPTION:	 _tprintf(_T("\tERROR_INVALID_OPTION\n"));	 break;
			case ERROR_ENCODING_PROBLEM: _tprintf(_T("\tERROR_ENCODING_PROBLEM\n")); break;
			case ERROR_FILE_ACCESS:		 _tprintf(_T("\tERROR_FILE_ACCESS\n"));		 break;
			case ERROR_MEMORY:			 _tprintf(_T("\tERROR_MEMORY\n"));			 break;
			default: _tprintf(_T("\tOk\n")); break;
		}
		ZBarcode_Buffer(barcode, 0);

		_tprintf(_T("Size: %d x %d\n"), barcode->bitmap_width, barcode->bitmap_height);

		cairo_surface_t *surface = cairo_image_surface_create(
			CAIRO_FORMAT_ARGB32, 
			barcode->bitmap_width * 5, 
			barcode->bitmap_height * 5);
		cairo_t *cairo = cairo_create(surface);
		cairo_set_source_rgb(cairo, 1.0, 1.0, 1.0);
		cairo_paint(cairo);
		cairo_set_source_rgb(cairo, 0.0, 0.0, 0.0);

		int idx = 0;
		for (int y=0; y<barcode->bitmap_height; y++)
			for (int x=0; x<barcode->bitmap_width; x++)
			{
				if (barcode->bitmap[idx] == 0)
				{
					cairo_rectangle(cairo, x*5, y*5, 5, 5);
					cairo_fill(cairo);
				}
				idx += 3;
			}

		cairo_destroy(cairo);
		cairo_surface_write_to_png(surface, "test-barcode.png");
		cairo_surface_destroy(surface);

		ZBarcode_Delete(barcode);
	}

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif

	return 0;
}

