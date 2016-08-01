#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H
///////////////////////////////////////////////////////////////////
// XmlDocument.h - a container of XmlElement nodes               //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Ojas Juneja, Syracuse University 
///////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package is intended to help students in CSE687 - Object Oriented Design
* get started with Project #2 - XML Document Model.  It uses C++11 constructs,
* most noteably std::shared_ptr.  The XML Document Model is essentially
* a program-friendly wrapper around an Abstract Syntax Tree (AST) used to
* contain the results of parsing XML markup.
*
* Abstract Syntax Trees, defined in this package, are unordered trees with 
* two types of nodes:
*   Terminal nodes     - nodes with no children
*   Non-Terminal nodes - nodes which may have a finite number of children
* They are often used to contain the results of parsing some language.
*
* The elements defined in the companion package, XmlElement, will be used in
* the AST defined in this package.  They are:
*   AbstractXmlElement - base for all the XML Element types
*   DocElement         - XML element with children designed to hold prologue, Xml root, and epilogue
*   TaggedElement      - XML element with tag, attributes, child elements
*   TextElement        - XML element with only text, no markup
*   CommentElement     - XML element with comment markup and text
*   ProcInstrElement   - XML element with markup and attributes but no children
*   XmlDeclarElement   - XML declaration element with attributes
*


Public Interface:
=================
XmlProcessing::XmlDocument&  findByNameAndValue(const std::string& attributeName, const std::string& value)    - find element by name-value pair                                                              
XmlProcessing::XmlDocument& findById(std::string tag)                                - find elements by ID/Tag
std::vector<std::shared_ptr<AbstractXmlElement>>find(std::shared_ptr<XmlProcessing::AbstractXmlElement>& pNode, std::string tag) - helper function of findById and findByNameValue
bool addAttribute(const std::string &name, const std::string &value)                 - add Attribute using name and value as parameters
bool addChild(std::shared_ptr<AbstractXmlElement> child)                             - add Child by passing parameters as shared pointer to 
                                                                                       element: tag/comment/text
bool removeChild(std::string childToBeRemoved)                                       - remove Child by passing tag as parameter
bool addRoot(const std::string &tag)                                                 - add Root if Tree is empty
bool removeAttribute(std::string name, std::string value)                            - remove attribute by passing name-value as parameter
std::vector<std::pair<std::string, std::string>> getAttributePairVector(std::shared_ptr < AbstractXmlElement > pTag) - get Attribute Vector 
                                                                                                                       by passing pointer the element: tag as parameter
std::vector<std::shared_ptr<AbstractXmlElement>> getChildrenVector(std::shared_ptr < AbstractXmlElement > pParent)- get Children Vector 
                                                                                                                    by passing pointer the element: tag as parameter
std::shared_ptr < AbstractXmlElement > getRoot()                                     -  returns the shared pointer to doc element
std::vector<std::shared_ptr < AbstractXmlElement >> && select()                      -  returns the vector to shared pointer to Abstract element by moving the pointer
*/


/* Required Files:
* ---------------
*     XmlDocument.h, XmlDocument.cpp, 
*     XmlElement.h, XmlElement.cpp
*     Tokenizer.h,Tokenizer.cpp
*     Rules and actions.h,Rules and actions.cpp
*     Parser.h,Parser.cpp
*     ConfigureParser.h,ConfihureParser.cpp
*
* Build Process:
* --------------
*   devenv AST.sln /debug rebuild
*
* Maintenance History:
* --------------------
* ver 1.3 : 19 Mar 15
* added functionality for AddChild,AddAttribute,RemoveChild,RemoveAttribute,FindElementById,FindElementByNameValue,also added some constructors
*and assignment operators.
* ver 1.2 : 21 Feb 15
* - modified these comments
* ver 1.1 : 14 Feb 15
* - minor changes to comments, method arguments
* Ver 1.0 : 11 Feb 15
* - first release
*
*/
#include<regex>
#include <memory>
#include <string>
#include "../XmlElement/XmlElement.h"
#include<algorithm>
using namespace XmlProcessing;
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include<stack>


namespace XmlProcessing
{
  class XmlDocument
  {
  public:
    using sPtr = std::shared_ptr < AbstractXmlElement > ;
	// --------------------Constructors and Assignment Operators Declaration----------------------------//
	XmlDocument(XmlProcessing::XmlDocument &&object);//move constructor is enabled
	XmlDocument(XmlProcessing::XmlDocument &object) = delete;//copy constructor is disabled
	XmlDocument& operator=(const XmlDocument& object) = delete;//Assignment is disabled
	XmlDocument& operator=(XmlProcessing::XmlDocument&& object);//Move Assignment is enabled
	XmlDocument(std::shared_ptr < AbstractXmlElement > &pDocElement);//promotion Constructor
	XmlDocument(); //default constructor
	// --------------------Class Functions----------------------------//
    XmlProcessing::XmlDocument&  findByNameAndValue(const std::string& attributeName, const std::string& value);
	std::vector<std::shared_ptr<AbstractXmlElement>> find(std::shared_ptr<XmlProcessing::AbstractXmlElement>& pNode, const std::string& attributeName, const std::string& value);
	XmlProcessing::XmlDocument& findById(std::string tag);
	std::vector<std::shared_ptr<AbstractXmlElement>>find(std::shared_ptr<XmlProcessing::AbstractXmlElement>& pNode, std::string tag);
	bool addAttribute(const std::string &name, const std::string &value);
	bool addChild(std::shared_ptr<AbstractXmlElement> child);
	bool removeChild(std::string childToBeRemoved);
	bool addRoot(const std::string &tag);
	bool removeAttribute(std::string name, std::string value);

	std::vector<std::pair<std::string, std::string>> getAttributePairVector(std::shared_ptr < AbstractXmlElement > pTag);
	std::vector<std::shared_ptr<AbstractXmlElement>> getChildrenVector(std::shared_ptr < AbstractXmlElement > pParent);
    std::shared_ptr < AbstractXmlElement > getRoot();
	std::vector<std::shared_ptr < AbstractXmlElement >> && select(); //This fucntion does move assignment and clears found vector
   
  private:
    sPtr pDocElement_;         // AST that holds procInstr, comments, XML root, and more comments
    std::vector<sPtr> found_;  // query results
  };
}
#endif
