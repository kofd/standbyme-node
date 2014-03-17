#include <node.h>
#include <v8.h>

#include "musicxml_parser.h"

using namespace v8;

void init(Handle<Object> exports) {
  // Module::Init(exports);
  MusicXMLParser::Init(exports);
}