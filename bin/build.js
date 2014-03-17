#!/usr/bin/sh

var fs = require('fs');
var exec = require('child_process').exec;
var spawn = require('child_process').spawn;


var PROJECT_DIR = process.cwd();

var LIB_DIR = PROJECT_DIR + '/lib';
var LIB_GUIDO_DIR = LIB_DIR + '/guido-engine';


function read_stream(stream)
{
  stream.read();
  process.stdout.write('.');
}


process.env['GYP_GENERATORS'] = 'cmake';


function guido_config(callback)
{
  console.info("guido_config");
  process.stdout.write('.');

  // Directory for guidolib
  if(!fs.existsSync(LIB_GUIDO_DIR))
  {
    if(!fs.existsSync(LIB_DIR))
    {
      fs.mkdirSync(LIB_DIR);
    }

    fs.mkdirSync(LIB_GUIDO_DIR);
  }
  process.chdir(LIB_GUIDO_DIR);

  // Download guidolib
  var child = exec("git clone https://github.com/hanshoglund/guido-engine.git");
  child.on('exit', function(code, signal)
  {
    process.stdout.write('\n');
    if(0 === code && !signal)
    {
      console.log('guido-engine download complete');
      guido_build(callback);
    }
    else
    {
      console.error('guido-engine download failed:', code, signal);
    }
  });
}

function guido_build(callback)
{
  console.info("guido_build");
  process.stdout.write('.');

  process.chdir(LIB_GUIDO_DIR + "/cmake");
  console.log(LIB_GUIDO_DIR + "/cmake");

  var args = ["-G",'"Unix Makefiles"'];
  console.log(args);

  var child = spawn("cmake", args);
  child.stdout.on('readable', read_stream.bind(undefined, child.stdout));
  child.on('exit', function(code, signal)
  {
    process.stdout.write('\n');
    if(0 === code && !signal)
    {
      var args = [];
      var child = spawn("make", args);
      child.stdout.on('readable', read_stream.bind(undefined, child.stdout));
      child.on('exit', function(code, signal) {
        process.stdout.write('\n');
        if(0 === code && !signal)
        {
          var args = [];
          var child = spawn("sudo make install", args);
          child.stdout.on('readable', read_stream.bind(undefined, child.stdout));
          child.on('exit', function(code, signal) {
            process.stdout.write('\n');
            if(0 === code && !signal)
            {
              console.log('guido_build complete');
              nodegyp_build(callback);
            }
            else
            {
              console.error('guido_build failed:', code, signal);
            }
          });
        }
        else
        {
          console.error('guido_build failed:', code, signal);
        }
      });
    }
    else
    {
      console.error('guido_build failed:', code, signal);
    }
  });
}

function nodegyp_build(callback)
{
  console.info("nodegyp_build");
  process.stdout.write('.');

  process.chdir(PROJECT_DIR);

  var child = spawn("node-gyp", ["rebuild"]);
  child.stdout.on('readable', read_stream.bind(undefined, child.stdout));
  child.on('exit', function(code, signal)
  {
    process.stdout.write('\n');
    if(0 === code && !signal)
    {
      console.log('nodegyp_build complete');
      callback();
    }
    else
    {
      console.error('nodegyp_build failed:', code, signal);
    }
  });
}

nodegyp_build(function(){
  console.log('standbyme-node build complete.');
});
