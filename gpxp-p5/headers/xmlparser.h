/*
 * Created  by rbh, 30/01/11
 * Modified by nas, 18/12/16
 */

#ifndef XMLPARSER_H_RBH300111
#define XMLPARSER_H_RBH300111

#include <string>

namespace XML_Parser
{
  using std::string;

  /* Note: the current implementation is fairly crude.  In particular,
   * it does not handle nested tags of the same name.
   */

  /* Determine whether an element exists in the source string.
   */
  bool elementExists(const string & source, const string & elementName);


  /*  If elementExists(), return the whole element (including tags),
   *  otherwise return an empty string.
   */
  string getElement(const string & source, const string & elementName);


  /*  If elementExists(), return the whole element (including tags),
   *  and erase that element from the source string.
   *  Otherwise return the empty string and erase nothing.
   */
  string getAndEraseElement(string & source, const string & elementName);


  /*  Return the content (everything between the opening/closing tags)
   *  of an XML element.
   *  Requires the argument to be a valid XML element.
   */
  string getElementContent(const string & element);


  /*  Return the value of an attribute, or an empty string if the attribute
   *  cannot be found.
   *  Requires the argument to be a valid XML element.
   */
  string getElementAttribute(const string & element, const string & attributeName);
}

#endif
