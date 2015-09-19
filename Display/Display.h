#ifndef DISPLAY_H
#define DISPLAY_H

///////////////////////////////////////////////////////////////////
//  Display.h  -  header file for Display class                  //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Display.h ,Project - 2(XML Document Model)       //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


/* Required Files:
* ---------------
*    - Display.h,Display.cpp
*   - xmlDocument.h,xmlDocument.cpp
*   - XMLElement.h,XMLElement.cpp


Module Operations:
==================
This module displays results and also writes the Tree into XML

Public Interface:
=================
void displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> &searchVectorDisplay,const std::string &tag)  - display search results to console
void displayToConsole(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag, const std::string parent) - display tree to console 
void displayToConsole(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag)                           - display tree to console 
void displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> &searchVectorDisplay, const std::string &name, const std::string &value) - display search results to console 
void displayToConsole(std::vector<std::pair<std::string, std::string>> vectornameValuePair, const std::string tag) - display name value pair to console
void displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> childrenDisplay)                            - display childrens to console                  
void writeToOutputXML(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag)          - writes output to Output.XML
void writeToRootXML(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag)            - writes output to Root.XML
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
#include<fstream>
#include"../XmlDocument/XmlDocument.h"
#include<vector>


	class Display
	{
	public:
		void displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> &searchVectorDisplay,const std::string &tag);
		void displayToConsole(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag, const std::string parent);
		void displayToConsole(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag);
		void displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> &searchVectorDisplay, const std::string &name, const std::string &value);
		void displayToConsole(std::vector<std::pair<std::string, std::string>> vectornameValuePair, const std::string tag);
		void displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> childrenDisplay);
		void writeToOutputXML(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag);
		void writeToRootXML(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag);
	};
#endif
