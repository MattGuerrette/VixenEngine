/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
