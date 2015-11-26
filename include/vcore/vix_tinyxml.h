/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef VIX_TINYXML_H
#define VIX_TINYXML_H

#include <vix_platform.h>
#include <vix_stringutil.h>

/*include for TinyXML2*/
#include <tinyxml2.h>

typedef tinyxml2::XMLDocument XMLDOC;
typedef tinyxml2::XMLPrinter  XMLPRINT;
#ifdef VIX_SYS_LINUX
//typedef int XMLError;
#endif

namespace Vixen {

#ifdef VIX_SYS_WINDOWS
	inline
	bool VIX_API XMLErrCheck(tinyxml2::XMLError error, UString& errorMsg)
	{
		bool fail = true;
		switch (error)
		{
		case tinyxml2::XML_NO_ERROR:
			errorMsg = VTEXT("XML_NO_ERROR");
			fail = false;
			break;
		case tinyxml2::XML_NO_ATTRIBUTE:
			errorMsg = VTEXT("XML_NO_ATTRIBUTE");
			break;
		case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
			errorMsg = VTEXT("XML_WRONG_ATTRIBUTE_TYPE");
			break;
		case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
			errorMsg = VTEXT("XML_ERROR_FILE_NOT_FOUND");
			break;
		case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			errorMsg = VTEXT("XML_ERROR_FILE_COULD_NOT_BE_OPENED");
			break;
		case tinyxml2::XML_ERROR_FILE_READ_ERROR:
			errorMsg = VTEXT("XML_ERROR_FILE_READ_ERROR");
			break;
		case tinyxml2::XML_ERROR_ELEMENT_MISMATCH:
			errorMsg = VTEXT("XML_ERROR_ELEMENT_MISMATCH");
			break;
		case tinyxml2::XML_ERROR_PARSING_ELEMENT:
			errorMsg = VTEXT("XML_ERROR_PARSING_ELEMENT");
			break;
		case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
			errorMsg = VTEXT("XML_ERROR_PARSING_ATTRIBUTE");
			break;
		case tinyxml2::XML_ERROR_IDENTIFYING_TAG:
			errorMsg = VTEXT("XML_ERROR_IDENTIFYING_TAG");
			break;
		case tinyxml2::XML_ERROR_PARSING_TEXT:
			errorMsg = VTEXT("XML_ERROR_PARSING_TEXT");
			break;
		case tinyxml2::XML_ERROR_PARSING_CDATA:
			errorMsg = VTEXT("XML_ERROR_PARSING_CDATA");
			break;
		case tinyxml2::XML_ERROR_PARSING_COMMENT:
			errorMsg = VTEXT("XML_ERROR_PARSING_COMMENT");
			break;
		case tinyxml2::XML_ERROR_PARSING_DECLARATION:
			errorMsg = VTEXT("XML_ERROR_PARSING_DECLARATION");
			break;
		case tinyxml2::XML_ERROR_PARSING_UNKNOWN:
			errorMsg = VTEXT("XML_ERROR_PARSING_UNKNOWN");
			break;
		case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
			errorMsg = VTEXT("XML_ERROR_EMPTY_DOCUMENT");
			break;
		case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
			errorMsg = VTEXT("XML_ERROR_MISMATCHED_ELEMENT");
			break;
		case tinyxml2::XML_ERROR_PARSING:
			errorMsg = VTEXT("XML_ERROR_PARSING");
			break;
		case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:
			errorMsg = VTEXT("XML_CAN_NOT_CONVERT_TEXT");
			break;
		case tinyxml2::XML_NO_TEXT_NODE:
			errorMsg = VTEXT("XML_NO_TEXT_NODE");
			break;
		}

		return fail;
	}
#elif defined(VIX_SYS_LINUX)
	inline
        bool VIX_API XMLErrCheck(tinyxml2::XMLError error, UString& errMsg)
	{
	  bool fail = true;
	  switch(error) {
	case tinyxml2::XML_NO_ERROR:
	  fail = false;
	  break;
	case tinyxml2::XML_NO_ATTRIBUTE:
	  break;
	case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
	  break;
	case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
	  break;
	case tinyxml2::XML_ERROR_FILE_READ_ERROR:
	  break;
	case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:
	  break;
	case tinyxml2::XML_NO_TEXT_NODE:
	  break;
	case tinyxml2::XML_ERROR_COUNT:
	  break;
	case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
	  break;
	case tinyxml2::XML_ERROR_ELEMENT_MISMATCH:
	  break;
	case tinyxml2::XML_ERROR_PARSING_ELEMENT:
	  break;
	case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
	  break;
	case tinyxml2::XML_ERROR_IDENTIFYING_TAG:
	  break;
	case tinyxml2::XML_ERROR_PARSING_TEXT:
	  break;
	case tinyxml2::XML_ERROR_PARSING_CDATA:
	  break;
	case tinyxml2::XML_ERROR_PARSING_COMMENT:
	  break;
	case tinyxml2::XML_ERROR_PARSING_DECLARATION:
	  break;
	case tinyxml2::XML_ERROR_PARSING_UNKNOWN:
	  break;
	case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
	  break;
	case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
	  break;
	case tinyxml2::XML_ERROR_PARSING:
	  break;
	  }
	  return fail;
	}
#endif

}

#endif
