// TestDuktape.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>

#include "duktape.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(_T("Initializing javascript vm...\n"));
	duk_context *ctx = duk_create_heap_default();

	if (ctx)
	{
		if (duk_peval_file(ctx, "test.js") == 0)
		{
			//_tprintf(_T("Stack height: %d\n"), duk_get_top(ctx));

			_tprintf(_T("Calling script function...\n"));
			duk_push_global_object(ctx);           // use global context in following operations
			duk_get_prop_string(ctx, -1, "ftest"); // find the function within global context
			duk_push_number(ctx, 4.2);             // arg
			if (duk_pcall(ctx, 1) == 0)            // call function with 1 arg (so name is at stack-2), consumes name and args
			{
				_tprintf(_T("Result: %f\n"), duk_to_number(ctx, -1));
				duk_pop(ctx); // throw result away
			}
			else
			{
				_tprintf(_T("Error calling script function!\n")); // duk_safe_to_string(ctx, -1)
				duk_pop(ctx); // throw error away
			}

			duk_pop(ctx); // throw global context away
			//_tprintf(_T("Stack height: %d\n"), duk_get_top(ctx));
		}
		else _tprintf(_T("Error loading script!\n")); // duk_safe_to_string(ctx, -1)

		duk_destroy_heap(ctx);
	}
	else _tprintf(_T("Error initializing scripting!\n"));

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif
	return 0;
}
