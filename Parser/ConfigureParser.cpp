
////////////////////////////////////////////////////////////////////
//ConfigureParser.cpp-implemntation file for ConfigureParser class//
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:ConfigureParser.cpp ,Project - 2(XML Document Model)//
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


#include"ConfigureParser.h"

bool ConfigParseToConsole::Attach(const std::string& name, bool isFile)
{
	if (pToker == 0)
		return false;
	else
	{
		if (isFile == true)
		{
			pToker->attach(name, isFile);//attaches the file if isFile is true
			pToker->setMode(Toker::xml);
		}
		else
		{
			if (name.find("<?xml version") != std::string::npos && name.find(">") != std::string::npos)
			{
				pToker->attach(name, isFile);//attaches the string if isFile is false
				pToker->setMode(Toker::xml);
			}
			else
			{
				std::cout << "\n" << "Please enter valid XML String";
				return false;
			}
		}	
	}
	return true;
}

//----< Here's where alll the parts get assembled >----------------
Parser* ConfigParseToConsole::Build()
{
	try{
		pToker = new Toker;
		pElementParts = new XmlParts(pToker);
		pRepo = new Repository(pToker);
		pParser = new Parser(pElementParts);
		//- defines action and rules for XML declaration Element
		pDecl = new XMLDeclarartionStatement();
		pHDecl = new HandleXMLDeclarartionStatement(pRepo);
		pDecl->addAction(pHDecl);
		pParser->addRule(pDecl);
		//- defines action and rules for XML Comment Element
		pComment = new XMLCommentElement();
		pHComment = new HandleXMLCommentElement(pRepo);
		pComment->addAction(pHComment);
		pParser->addRule(pComment);
		//- defines action and rules for XML ProcInstr Element
		pProcInstr = new XMLProcInstrElement();
		pHProcInstr = new HandleXMLProcInstrElement(pRepo);
		pProcInstr->addAction(pHProcInstr);
		pParser->addRule(pProcInstr);
		//- defines action and rules for XML Tagged Attribute Element
		pTagAttr = new XMLTaggedAttributeElement();
		pHTagAttr = new HandleXMLTaggedAttributeElement(pRepo);
		pTagAttr->addAction(pHTagAttr);
		pParser->addRule(pTagAttr);
		//- defines action and rules for XML Tagged Non Attribute Element
		pTagNoAttr = new XMLTaggedNonAttributeElement();
		pHTagNoAttr = new HandleXMLTaggedNonAttributeElement(pRepo);
		pTagNoAttr->addAction(pHTagNoAttr);
		pParser->addRule(pTagNoAttr);
		//- defines action and rules for XML Text Element
		pText = new XMLTextElement();
		pHText = new HandleXMLTextElement(pRepo);
		pText->addAction(pHText);
		pParser->addRule(pText);
		//- defines action and rules for XML Closing Tag
		pClosingTag = new XMLClosingTag();
		pHClosingTag = new HandleXMLClosingTag(pRepo);
		pClosingTag->addAction(pHClosingTag);
		pParser->addRule(pClosingTag);
		return pParser;
	}
	catch (std::exception ee){
		ee.what();
		return 0;
	}	
}


#ifdef TEST_CONFIGUREPARSER
int main()
{
	//Test stub shows to configure parser
	std::cout << "\n\n    " << "Configuring Parser: " ;
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	try
	{
		if (pParser)
		{
			std::cout << "\n\n    " << "Parser is configured" << "\n\n";
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif
