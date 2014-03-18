var standbyme = require('../lib/index');
var MusicXMLParser = new standbyme.MusicXMLParser();

MusicXMLParser.parse("Delilah.xml","testresult.svg");