/*
 * tdijkstra.h
 *
 */

#ifndef NODE_INC_YDIJKSTRA_H_
#define NODE_INC_YDIJKSTRA_H_

#include "../../dijk/inc/dijkstra.h"
#include "../../dijk/node/node.h"
#include "../../dijk/node/node_object_wrap.h"

class YDijkstra: public node::ObjectWrap
{

public:
	YDijkstra();
	virtual ~YDijkstra();
protected:
	static v8::Persistent<v8::Function> constructor;

public:
	static void InitializeModule(v8::Local<v8::Object> exports);
	static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

public:
	static void addVertex(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addEdge(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void distance(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void path(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void show(const v8::FunctionCallbackInfo<v8::Value>& args);
private:
	Graph _theGraph;
};

#endif /* NODE_INC_YDIJKSTRA_H_ */

