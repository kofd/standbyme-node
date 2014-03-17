#include <node_buffer.h>

#include <stdint.h>
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include "musicxml_parser.h"
#include "SVGDevice.h"
#include "SVGSystem.h"
#include "GUIDOEngine.h"

using namespace node;
using namespace v8;

Persistent<Function> MusicXMLParser::constructor;

MusicXMLParser::MusicXMLParser()
{
    
}

MusicXMLParser::~MusicXMLParser()
{
    
}

NAN_METHOD(MusicXMLParser::New) {
  NanScope();

  if(!args.IsConstructCall()) {
    return NanThrowTypeError("Use the new operator to construct the MusicXMLParser.");
  }

  // todo: construct the parser

  NanReturnValue( args.This() );
}

NAN_METHOD(MusicXMLParser::parse) {
  NanScope();
  
  String::Utf8Value param1(args[0]->ToString());
  String::Utf8Value param2(args[1]->ToString());
  
  ARHandler arh;
  SVGSystem svgsys;
  std::ofstream outfile(*param2,std::ofstream::binary);
  std::shared_ptr<VGDevice> dev (svgsys.CreateDisplayDevice(outfile));
  
  // declare a data structure for engine initialisation
  // we'll make use of the default graphic device (embedded in the library)
  // Guido font is guido2 and text font is times
  GuidoInitDesc gd = { dev.get(), 0, "guido2", "Times" };
  GuidoOnDrawDesc desc;              // declare a data structure for drawing        
  GuidoInit (&gd);                   // Initialise the Guido Engine first
  
  // and parse the GMN file to get a GGR handle directly stored in the drawing struct
  GuidoParseFile (*param1, &arh);
  GuidoAR2GR (arh, 0, &desc.handle);
  desc.hdc = dev.get();               // we'll draw on the postscript device
  desc.page = 1;                      // draw the first page only
  desc.updateRegion.erase = true;     // and draw everything
  desc.scrollx = desc.scrolly = 0;    // from the upper left page corner
  desc.sizex = desc.sizey = 500;      // size of the drawing region
  
  GuidoOnDraw (&desc);
  
  outfile.close();
  
  NanReturnValue(Undefined());
}

/*NAN_GETTER(MusicXMLParser::get_name) {
  NanScope();

  NanReturnValue(Undefined());
}*/

/*NAN_SETTER(MusicXMLParser::set_name) {
  NanScope();

  NanReturnValue(Undefined());
}*/

NAN_SETTER(MusicXMLParser::ReadOnly) {
}


void MusicXMLParser::Init( Handle<Object> exports ) {
  Local<FunctionTemplate> tpl = FunctionTemplate::New( New );
  tpl->SetClassName( String::NewSymbol( "MusicXMLParser" ) );
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  /*tpl->PrototypeTemplate()->Set( String::NewSymbol( "method_name" ),
    FunctionTemplate::New( method_name )->GetFunction() );*/
  tpl->PrototypeTemplate()->Set( String::NewSymbol( "parse" ),
    FunctionTemplate::New( parse )->GetFunction() );
    
  //tpl->InstanceTemplate()->SetAccessor(String::New("name"), get_name, set_name);

  NanAssignPersistent(Function, constructor, tpl->GetFunction());
  exports->Set( String::NewSymbol("MusicXMLParser"), tpl->GetFunction() );
}