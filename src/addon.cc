// addon.cc
#include "ydijkstra.h"
#include "node.h"

//namespace demo {

using v8::Local;
using v8::Object;

void InitAll(Local<Object> exports) {

	YDijkstra::InitializeModule(exports);
}

NODE_MODULE(YDijkstra, InitAll)

//}  // namespace demo
