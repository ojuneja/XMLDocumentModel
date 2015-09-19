#ifndef EXECUTIVE_H
#define EXECUTIVE_H


///////////////////////////////////////////////////////////////////
//  Executive.h  -  header file for Executive class              //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Executive.h ,Project - 2(XML Document Model)     //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


/* Required Files:
* ---------------
*    - ConfigureParser.h,ConfigureParser.cpp
*   - xmlDocument.h,xmlDocument.cpp
*    - Tokenizer.h,Tokenizer.cpp
*    - Display.h,display.cpp
*    - Executive.h,Executive.cpp
*    - XMLElement.h,XMLElement.cpp
*    - XMLElementParts.h,XMLElementParts.cpp
*    - Parser.h,Parser.cpp
*    - RulesAndActions.h,RulesAndActions.cpp


Module Operations:
==================
This is the main execution of Project 2
It Queries and Demonstrates the requirments

Public Interface:
=================
void demonstrateFindByTag(Display dp, XmlProcessing::XmlDocument doc, const std::string tag)         -     demonstrates requirment 6
void demonstrateFindByNameValue(Display dp, XmlProcessing::XmlDocument doc, const std::string name, const std::string value)  -  demonstrates requirment 5
void demonstrateAddAttribute(Display dp, XmlProcessing::XmlDocument doc, const std::string parent, const std::string name, const std::string value) - demonstrates requirment 9
void demonstrateAddChild(Display dp, XmlProcessing::XmlDocument doc, const std::string parent, const std::string option) - demonstrates requirment 7
void demonstrateRemoveAttribute(Display dp, XmlProcessing::XmlDocument doc, const std::string parent, const std::string name, const std::string value) - demonstrates requirment 9
void demonstrateRemoveChild(Display dp, XmlProcessing::XmlDocument doc, const std::string parent, const std::string elementToBeDeleted) - demonstrates requirment 7
void demonstrateAddRoot(Display dp, XmlProcessing::XmlDocument doc,const std::string root) - demonstrates requirment 7
void demonstrateShowAttribute(Display dp, XmlProcessing::XmlDocument doc, const std::string tag) - demonstrates requirment 8
void demonstrateShowChildren(Display dp, XmlProcessing::XmlDocument doc, const std::string parent) - demonstrates requirment 8
void demonstrateMoveOperation(Display dp, XmlProcessing::XmlDocument &doc)                         - demonstrates requirement 4
void executeCommands(ConfigParseToConsole configure)                                               - executes all demonstrate functions
std::string makeString()                                                                    - make string so that it can be passed for parsing
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
#include"../Parser/Parser.h"
#include"../Parser/ConfigureParser.h"
#include"../Parser/RulesAndActions.h"
#include"../Display/Display.h"
#include<iostream>
#include<vector>

class Executive{
public:
	Executive(std::shared_ptr<AbstractXmlElement> pDocElement);
	void demonstrateFindByTag(Display dp, XmlProcessing::XmlDocument &doc, const std::string tag);
	void demonstrateFindByNameValue(Display dp, XmlProcessing::XmlDocument &doc, const std::string name, const std::string value);
	void demonstrateAddAttribute(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string name, const std::string value);
	void demonstrateAddChild(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string option);
	void demonstrateRemoveAttribute(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string name, const std::string value);
	void demonstrateRemoveChild(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string elementToBeDeleted);
	void demonstrateAddRoot(Display dp, XmlProcessing::XmlDocument &doc,const std::string root);
	void demonstrateShowAttribute(Display dp, XmlProcessing::XmlDocument &doc, const std::string tag);
	void demonstrateShowChildren(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent);
	void demonstrateMoveOperation(Display dp, XmlProcessing::XmlDocument &doc);
	void executeCommands(ConfigParseToConsole configure);
	std::string makeString();
private:
	std::shared_ptr<AbstractXmlElement> pDocElement_;
};


#endif