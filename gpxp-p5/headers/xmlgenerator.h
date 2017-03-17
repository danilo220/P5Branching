/*
 * Created  by rbh, 21/01/11
 * Modified by nas, 07/01/17
 */

#ifndef XMLGENERATOR_H_RBH210111
#define XMLGENERATOR_H_RBH210111

#include <string>
#include <stack>

using std::string;

namespace XML_Generator
{
  string basicGPXHeader();

  void openTag(string & dest,
               string tagName,
               string tagParameters,
               string tagContent,
               std::stack<string> & closingTags);

  void openCloseTagAndValue(string & dest,
                            const string & tagName,
                            const string & tagParameters,
                            const string & tagContent);
}

#endif
