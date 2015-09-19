#ifndef CONFIGUREPARSER_H
#define CONFIGUREPARSER_H


///////////////////////////////////////////////////////////////////
//  ConfigureParser.h  -  header file for ConfigureParser class  //
//  ver 1.0                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  ConfigureParser.h ,Project - 2(XML Document Model)//
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////

/* Required Files:
* ---------------
*    - ConfigureParser.h,ConfigureParser.cpp
*   - xmlElementParts.h,xmlElementParts.cpp,
*    - Tokenizer.h, Tokenizer.cpp
*    - RulesAndActions.h,RulesAndActions.cpp
*    - Parser.h,Parser.cpp


Module Operations:
==================
This module builds and configures parsers.  It builds the parser
parts and configures them with application specific rules and actions.

Public Interface:
=================
bool Attach(const std::string& name, bool isFile =true)                      -   attach the XML File if isFile=true otherwise string
Parser* Build()                                                              -   builds the parser
Repository* getRepository()                                                  -   returns the pointer object of repository

Build Process:
==============
devenv XMLDocumentModel.sln /rebuild debug

Maintenance History:
====================
ver 1.1 : 19 Mar 15
- second release
ver 1.0 : 15 Mar 15
- first release

*/

#include "Parser.h"
#include "../XMLElementParts/xmlElementParts.h"
#include "../XMLElementParts/Tokenizer.h"
#include "RulesAndActions.h"


class ConfigParseToConsole
{
public:
	ConfigParseToConsole() {};
	~ConfigParseToConsole(){};
	bool Attach(const std::string& name, bool isFile =true);
	Parser* Build();
	Repository* getRepository()
	{
		return pRepo;
	}
private:
	// Builder must hold onto all the pieces
	std::vector<std::string> XMLFileContents;
	Toker* pToker;
	XmlParts* pElementParts;
	Parser* pParser;
	Repository* pRepo;
	XMLDeclarartionStatement *pDecl;
	HandleXMLDeclarartionStatement *pHDecl;
	XMLCommentElement *pComment;
	HandleXMLCommentElement *pHComment;
	XMLProcInstrElement *pProcInstr;
	HandleXMLProcInstrElement *pHProcInstr;
	XMLTaggedNonAttributeElement *pTagNoAttr;
	HandleXMLTaggedNonAttributeElement *pHTagNoAttr;
	XMLTextElement *pText;
	HandleXMLTextElement *pHText;
	XMLTaggedAttributeElement *pTagAttr;
	HandleXMLTaggedAttributeElement *pHTagAttr;
	XMLClosingTag *pClosingTag;
	HandleXMLClosingTag *pHClosingTag;
};




#endif
