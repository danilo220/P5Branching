/*
 * Created  by rbh, 21/01/11
 * Modified by nas, 07/01/17
 */

#include "xmlgenerator.h"

namespace XML_Generator
{
  string basicGPXHeader()
  {
      string str;
      str =  "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" standalone=\"yes\"?>";
      str += "<gpx version=\"1.1\" creator=\"GPXP\" ";
      str += "xmlns=\"http://www.topografix.com/GPX/1/1\" ";
      str += "xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" ";
      str += "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
      str += "xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\"> ";
      return str;
  }

  void openTag(string & dest, string tagName, string tagParameters, string tagContent, std::stack<string> & closingTags)
  {
      string closingTag;
      closingTag.reserve(3 + tagName.length());
      closingTag = "</";
      closingTag += tagName;
      closingTag += ">";
      closingTags.push(closingTag);

      dest += "<";
      dest += tagName;
      dest += " ";
      dest += tagParameters;
      dest += ">";
      dest += tagContent;
  }

  void openCloseTagAndValue(string & dest, const string & tagName, const string & tagParameters, const string & tagContent)
  {
      string closingTag;
      closingTag.reserve(3 + tagName.length());
      closingTag =  "</";
      closingTag += tagName;
      closingTag += ">";

      dest += "<";
      dest += tagName;
      dest += tagParameters.empty() ? "" : (string(" ")+tagParameters);
      dest += tagParameters;
      dest += ">";
      dest += tagContent;
      dest += closingTag;
  }
}
