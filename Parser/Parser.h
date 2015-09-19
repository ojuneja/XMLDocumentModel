#ifndef PARSER_H
#define PARSER_H


///////////////////////////////////////////////////////////////////
//  Parser.h  -  Header file for Defining rules and actions      //
//                for parser                                     //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Parser.h ,Project - 2(XML Document Model)        //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


/* Required Files:
* ---------------
*   - xmlElementParts.h,xmlElementParts.cpp,
*    - xmlElement.h,xmlElement.cpp,
*    - Tokenizer.h, Tokenizer.cpp,
*    - XMLDocument.h,XMLDocument.cpp
*    
/*
Module Operations:
==================
This module defines a Parser class.  It also defines IRule and IAction
which is used by RulesAndActions class as an interface 
Basically,It defines rules and actions for the parser so that XML or string can be parsed.


Public Interface: Parser Class
=================
bool Attach(const std::string& name, bool isFile =true)                      -   attach the XML File if isFile=true otherwise string
Parser* Build()                                                              -   builds the parser
Repository* getRepository()                                                  -   returns the pointer object of repository

Public Interface: IRule
=================
void addAction(IAction* pAction)                                            - adds action to the parser
void doActions(std::string string)                                          - calls action of IAction class when appropriate.
virtual bool doTest(ITokCollection*& pTc) = 0                               - a pure virtual function whose work,if implemented,  is to 
                                                                              detect what type of string(XML Declaration or Comment or tagged Eelement)
																			  is detected.
std::string identifyTaggedAndTextElement(std::string string)                - identifies which type of tagged and text element is there.
                                                                              This function categorizes tagged and text element into different parts.

Public Interface: IAction
 =================
virtual void doAction(std::string string) = 0                               - pure virtual function,if implemented,does actions based on 
                                                                              XML declaration,XML Comment,XML tagged Element
																			  

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

#include<iostream>
#include "../XMLElementParts/itokcollection.h"
#include "../XMLElementParts/Tokenizer.h"
#include "../XMLElementParts/xmlElementParts.h"
#include"../XMLElement/XmlElement.h"
#include"../XMLDocument/XmlDocument.h"

class Parser;

class IAction
{
public:
	virtual ~IAction() {}
	virtual void doAction(std::string string) = 0;
};



class IRule
{
public:
	virtual ~IRule() {}
	void addAction(IAction* pAction);
	void doActions(std::string string);
	virtual bool doTest(ITokCollection*& pTc) = 0;
	std::string identifyTaggedAndTextElement(std::string string);
protected:
	std::vector<IAction*> actions;
	IAction* action;


};


class Parser
{
public:
	Parser(ITokCollection* pTokCollection) :pTokColl(pTokCollection){};
	~Parser();
	bool parse();
	bool next();
	void addRule(IRule* pRule);
	ITokCollection* getTokCollection(){ return pTokColl; }
private:
	Toker* pToker;
	ITokCollection* pTokColl;
	XmlParts* pElementParts;
	std::vector<IRule*> rules;
};



#endif