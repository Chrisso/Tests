// TestV8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <v8.h>

v8::Handle<v8::Value> Log(const v8::Arguments& args)
{
	if (args.Length() == 1)
	{
		v8::HandleScope handle_scope;
		v8::String::Utf8Value s(args[0]);
		printf("Script: %s\n", (*s)? *s : "null"); 
	}
	return v8::Undefined();
}

int _tmain(int argc, _TCHAR* argv[])
{
	v8::HandleScope handle_scope;
	v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
	global->Set(v8::String::New("log"), v8::FunctionTemplate::New(Log));
	
	v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);
	v8::Context::Scope context_scope(context);

	v8::Handle<v8::String> source = v8::String::New((const uint16_t*)_T("function foo(a, b) { log('foo!'); return Math.max(a, b); }"));
	v8::Handle<v8::Script> script = v8::Script::Compile(source);
	script->Run();

	v8::Handle<v8::Value> sargv[2];
	sargv[0] = v8::Int32::New(10);
	sargv[1] = v8::Int32::New(15);

	v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(context->Global()->Get(v8::String::New("foo")));
	v8::Handle<v8::Value> result = func->Call(func, 2, sargv);

	_tprintf(_T("Function result: %d\n"), result->Int32Value());

	context.Dispose();

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif

	return 0;
}

