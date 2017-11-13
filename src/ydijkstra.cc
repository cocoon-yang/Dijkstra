/*
 * ydijkstra.cpp
 *
 */

#include "ydijkstra.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Array;

//#define DEBUG

Persistent<Function> YDijkstra::constructor;
YDijkstra::YDijkstra()
{
	// TODO Auto-generated constructor stub

}

YDijkstra::~YDijkstra()
{
	// TODO Auto-generated destructor stub
}

void YDijkstra::InitializeModule(Local<Object> exports)
{
	Isolate* isolate = exports->GetIsolate();

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "YDijkstra"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	NODE_SET_PROTOTYPE_METHOD(tpl, "addVertex", addVertex);
	NODE_SET_PROTOTYPE_METHOD(tpl, "addEdge", addEdge);
	NODE_SET_PROTOTYPE_METHOD(tpl, "distance", distance);
	NODE_SET_PROTOTYPE_METHOD(tpl, "path", path);
	NODE_SET_PROTOTYPE_METHOD(tpl, "show", show);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "YDijkstra"), tpl->GetFunction());
}

void YDijkstra::New(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();

	if (args.IsConstructCall())
	{
		YDijkstra* obj = new YDijkstra();
		obj->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	}
	else
	{
		// Invoked as plain function `YDijkstra(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] =
		{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
	return;
}

void YDijkstra::path(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	bool result = false;

	YDijkstra *graph = ObjectWrap::Unwrap<YDijkstra>(args.Holder());
	if (0 == graph)
	{
		std::cerr << "YDijkstra::path: object pointer invalid, return false."
				<< std::endl;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
		return;
	}

	int i;
	v8::Handle<v8::Value> arg = args[0];
	if (arg->IsInt32())
	{
		i = arg->Int32Value();
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								" path( i ): The first argument should be an integer.")));
		return;
	}

	graph->_theGraph.print_path(i);

	result = true;
	args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
	return;

}

void YDijkstra::show(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	bool result = false;

	YDijkstra *graph = ObjectWrap::Unwrap<YDijkstra>(args.Holder());
	if (0 == graph)
	{
		std::cerr << "YDijkstra::show: object pointer invalid, return false."
				<< std::endl;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
		return;
	}
	graph->_theGraph.show();

	result = true;
	args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
	return;

}

void YDijkstra::addEdge(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	bool result = false;

	YDijkstra *graph = ObjectWrap::Unwrap<YDijkstra>(args.Holder());
	if (0 == graph)
	{
		std::cerr
				<< "YDijkstra::addVertex: object pointer invalid, return false."
				<< std::endl;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
		return;
	}
	int i;
	int j;
	double weight;
	v8::Handle<v8::Value> arg = args[0];
	if (arg->IsInt32())
	{
		i = arg->Int32Value();
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								" addEdge( i, j, weight): The first argument should be an integer.")));
		return;
	}
	arg = args[1];
	if (arg->IsInt32())
	{
		j = arg->Int32Value();
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"addEdge( i, j, weight): The second argument should be an integer.")));
		return;
	}
	arg = args[2];
	if (arg->IsNumber())
	{
		weight = arg->NumberValue();
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"addEdge( i, j, weight): The third argument should be an float value.")));
		return;
	}

	graph->_theGraph.addEdge(i, j, weight);

	result = true;
	args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
	return;

}

void YDijkstra::addVertex(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	bool result = false;

	YDijkstra *graph = ObjectWrap::Unwrap<YDijkstra>(args.Holder());
	if (0 == graph)
	{
		std::cerr
				<< "YDijkstra::addVertex: object pointer invalid, return false."
				<< std::endl;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
		return;
	}
	v8::Handle<v8::Value> arg = args[0];
	if (arg->IsInt32())
	{
		int value = arg->Int32Value();
		graph->_theGraph.addVertex(value);

		result = true;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
		return;
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"addVertex( i ): The first argument should be an integer.")));
		return;
	}
}

void YDijkstra::distance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	bool result = false;

	YDijkstra *graph = ObjectWrap::Unwrap<YDijkstra>(args.Holder());
	if (0 == graph)
	{
		std::cerr
				<< "YDijkstra::distance: object pointer invalid, return false."
				<< std::endl;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
		return;
	}
	int i;
	int j;
	v8::Handle<v8::Value> arg = args[0];
	if (arg->IsInt32())
	{
		i = arg->Int32Value();
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								" distance( i, j ): The first argument should be an integer.")));
		return;
	}
	arg = args[1];
	if (arg->IsInt32())
	{
		j = arg->Int32Value();
	}
	else
	{
		// Throw an Error that is passed back to JavaScript
		isolate->ThrowException(
				v8::Exception::TypeError(
						String::NewFromUtf8(isolate,
								"distance( i, j ): The second argument should be an integer.")));
		return;
	}

	graph->_theGraph.distance(i, j);

	result = true;
	args.GetReturnValue().Set(v8::Boolean::New(isolate, result));
	return;

}

