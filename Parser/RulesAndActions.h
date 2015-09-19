#ifndef XMLRULESANDACTIONS_H
#define XMLRULESANDACTIONS_H



///////////////////////////////////////////////////////////////////
//  RulesAndActions.h  -  Header File for testing type of        //
//                         element and then doing actions        //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Parser.h ,Project - 2(XML Document Model)        //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////



/*


Public Interface:
=================
bool doTest(ITokCollection*& pTc)                      -   test and find whether given string corresponds to XML Declaration/Comment
                                                           /TaggedAttribute/Text element/Non Tagged Attribute/Closing Tag element or not
void doAction(std::string string)                      - performs action based on detected Element
std::shared_ptr <AbstractXmlElement>&getRoot()         - returns the shared pointer of doc element.
std::shared_ptr <AbstractXmlElement>&getStack()        - returns the shared pointer of stack.

Module Operations:
==================
This module defines several action classes.  Its classes provide
specialized services needed for specific applications.  The modules
Parser, XML Element Parts, and Tokenizer, are intended to be reusable
This module provides a place to put extensions of
these facilities and is not expected to be reusable.


/* Required Files:
* ---------------
*   - Parser.h,Parser.cpp,
*
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
#include <string>
#include <sstream>


class Repository // application specific
{
	Toker* p_Toker;
	std::shared_ptr <AbstractXmlElement> pDocElement_ = makeDocElement();
	std::stack<std::shared_ptr < AbstractXmlElement >> stack;
public:
	Repository(Toker* pToker)
	{
		p_Toker = pToker;
	}
	Toker* Toker()
	{
		return p_Toker;
	}
	std::shared_ptr <AbstractXmlElement>&getRoot()
	{
		return pDocElement_;
	}
	std::stack<std::shared_ptr < AbstractXmlElement >>&getStack()
	{
		return stack;
	}

};


class XMLDeclarartionStatement :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);
};


class HandleXMLDeclarartionStatement :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLDeclarartionStatement(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);

};


class XMLCommentElement :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);
};


class HandleXMLCommentElement :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLCommentElement(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);

};


class XMLProcInstrElement :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);
};


class HandleXMLProcInstrElement :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLProcInstrElement(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);

};


class XMLTaggedAttributeElement :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);
};


class HandleXMLTaggedAttributeElement :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLTaggedAttributeElement(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);
	std::vector<std::string> processTokens(std::string);
};


class XMLTaggedNonAttributeElement :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);
};


class HandleXMLTaggedNonAttributeElement :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLTaggedNonAttributeElement(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);

};


class XMLClosingTag :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);

};


class HandleXMLClosingTag :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLClosingTag(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);

};


class XMLTextElement :public IRule
{
public:
	bool doTest(ITokCollection*& pTc);
	//std::string  identifyTaggedAndTextElement(std::string string);
};


class HandleXMLTextElement :public IAction
{
	Repository* p_Repos;
public:
	HandleXMLTextElement(Repository* pRepos)
	{
		p_Repos = pRepos;
	}
	void doAction(std::string string);

};




#endif