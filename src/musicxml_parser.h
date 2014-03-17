#ifndef __MUSICXML_PARSER_H__
#define __MUSICXML_PARSER_H__

#include <queue>
#include <string>

#include <node.h>
#include <v8.h>
#include <node_object_wrap.h>
#include <uv.h>

#include "nan.h"

using namespace node;
using namespace v8;

class MusicXMLParser
: public ObjectWrap
{
    
public:
  MusicXMLParser();
  ~MusicXMLParser();
  
  //
  // Nodejs wrapping.
  //
  
  static void Init( Handle<Object> exports );
  static Persistent<Function> constructor;
  static NAN_METHOD(New);

  //static NAN_METHOD(method_name);
  static NAN_METHOD(parse);
  
  //static NAN_GETTER(get_name);
  
  //static NAN_SETTER(set_name);
  static NAN_SETTER(ReadOnly);
  
private:
};

#endif