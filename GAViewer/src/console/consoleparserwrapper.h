// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2002-2009, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#include "ConsoleParser.hpp"
using namespace antlr;
#include "../state.h"

// A small wrapper around ConsoleParser that overrides the error reporting 
// member functions so that they print to the console.
class ConsoleParserWrapper : public ConsoleParser {
public:
	ConsoleParserWrapper(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer) : ConsoleParser(lexer) {};

	/** Parser error-reporting function can be overridden in subclass */
	virtual void reportError(const RecognitionException& ex)
	{
		//ANTLR_USE_NAMESPACE(std)cerr  << ex.toString().c_str() << ANTLR_USE_NAMESPACE(std)endl;
		cprintf("%s\n", ex.toString().c_str());
	}

	/** Parser error-reporting function can be overridden in subclass */
	virtual void reportError(const ANTLR_USE_NAMESPACE(std)string& s)
	{
		if ( getFilename()=="" ) {
			//ANTLR_USE_NAMESPACE(std)cerr  << "error: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
			cprintf("Error: %s\n", s.c_str());
		}
		else {
			//ANTLR_USE_NAMESPACE(std)cerr  << getFilename().c_str() << ": error: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
			cprintf("%s: error: %s\n", getFilename().c_str(), s.c_str());
		}
	}

	/** Parser warning-reporting function can be overridden in subclass */
	virtual void reportWarning(const ANTLR_USE_NAMESPACE(std)string& s)
	{
		if ( getFilename()=="" ) {
			//ANTLR_USE_NAMESPACE(std)cerr  << "warning: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
			cprintf("Warning: %s\n", s.c_str());
		}
		else {
			//ANTLR_USE_NAMESPACE(std)cerr  << getFilename().c_str() << ": warning: " << s.c_str() << ANTLR_USE_NAMESPACE(std)endl;
			cprintf("%s: warning: %s\n", getFilename().c_str(), s.c_str());
		}
	}

};
