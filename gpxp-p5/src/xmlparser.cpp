/*
 * Created  by rbh, 30/01/11
 * Modified by nas, 18/12/16
 */

#include <cassert>
#include <utility>

#include "xmlparser.h"

namespace XML_Parser
{
  /* The convention for variable names in this file is for "Begin" to be the index of the
   * first character of the item, and for "End" to be the index of the first character after
   * the item.
   */

  std::pair<size_t,size_t> findElement(const string & source, const string & elementName)
  /* Returns the a pair containing <index,length> where index is the index of the start
   * of the element, and length is the length of the element.
   *
   * Note: the current implementation does not handle nested elements with the same name.
   */
  {
      using std::make_pair;

      size_t openingTagBegin;

      size_t current = 0;
      do
      {
          openingTagBegin = source.find("<" + elementName, current);
          current = openingTagBegin + elementName.length() + 1;
          if (openingTagBegin == string::npos || current >= source.length())
          {
              return make_pair(string::npos, 0);
          }
      } while (source[current] != '>' && source[current] != ' ');
        // If true we've found another tag that happens to have the "tagName" as a prefix,
        // so we need to search further.

      size_t openingTagLast = source.find(">", current);
      if (openingTagLast == string::npos) {
          return make_pair(string::npos, 0);
      }
      size_t openingTagEnd = openingTagLast + 1;
      if (source[openingTagLast - 1] == '/')
      {   // Then the opening tag is of the form <tagName />, so no closing tag.
          return make_pair(openingTagBegin, openingTagEnd - openingTagBegin);
      }

      size_t closingTagBegin = source.find("</" + elementName + ">", openingTagEnd);
      if (closingTagBegin == string::npos)
      {
          return make_pair(string::npos, 0);
      }
      size_t closingTagEnd = closingTagBegin + elementName.length() + 3;
      return make_pair(openingTagBegin, closingTagEnd - openingTagBegin);
  }

  bool elementExists(const string & source, const string & elementName)
  {
      return findElement(source,elementName).first != string::npos;
  }

  string getElement(const string & source, const string & elementName)
  {
      std::pair<size_t,size_t> p = findElement(source, elementName);
      return source.substr(p.first, p.second);
  }

  string getAndEraseElement(string & source, const string & elementName)
  {
      std::pair<size_t,size_t> p = findElement(source, elementName);
      string element = source.substr(p.first, p.second);
      source.erase(p.first, p.second);
      return element;
  }

  string getElementContent(const string & element)
  // The argument is required to be a valid XML element.
  {
      assert(element.front() == '<');
      assert(element.back()  == '>');

      size_t openingTagEnd = element.find(">") + 1;

      if (element[openingTagEnd - 2] == '/')
      {   // Has form <tagName /> so no content.
          assert(openingTagEnd == element.length());
          return "";
      }

      size_t closingTagBegin = element.rfind("</");
      assert(closingTagBegin != string::npos);

      return element.substr(openingTagEnd, closingTagBegin - openingTagEnd);
  }

  string getElementAttribute(const string & element, const string & attributeName)
  // The first argument is required to be a valid XML element.
  {
      assert(element.front() == '<');
      assert(element.back()  == '>');

      size_t attributesBegin = element.find(" ");
      size_t attributesEnd   = element.find(">");
      if (attributesBegin == string::npos || attributesBegin > attributesEnd)
      {   // Then no attributes in this tag.
          return "";
      }
      string attributes = element.substr(attributesBegin, attributesEnd - attributesBegin);

      size_t attributeNameBegin = attributes.find(attributeName + "=\"");
      if (attributeNameBegin == string::npos)
      {   // Then the attribute is not present in this tag.
          return "";
      }

      size_t attributeValueBegin = attributeNameBegin + attributeName.length() + 2;
      size_t attributeValueEnd   = attributes.find("\"",attributeValueBegin);
      assert(attributeValueEnd != string::npos);

      return attributes.substr(attributeValueBegin, attributeValueEnd - attributeValueBegin);
  }
}
