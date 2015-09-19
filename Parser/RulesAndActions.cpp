#include"RulesAndActions.h"

///////////////////////////////////////////////////////////////////
//  RulesAndActions.cpp  -  implementation File for testing type //
//                         of element and then doing actions     //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Parser.h ,Project - 2(XML Document Model)        //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////

// provides functionality to test whether it is XML declaration token or not.
bool XMLDeclarartionStatement::doTest(ITokCollection*& pTc)
{
    std::string string =  pTc->show();
	if (string.find(" < ? xml version")!=std::string::npos)
	{
		doActions(string);
		return true;
	}
	return false;
}

//provides functionality to test whether it is XML Comment token or not.
bool XMLCommentElement::doTest(ITokCollection*& pTc)
{
	std::string string = pTc->show();
	if (string.find("< ! -- ") != std::string::npos)
	{
		doActions(string);
		return true;
	}
	return false;
}

//provides functionality to test whether it is XML ProcInstr token or not.
bool XMLProcInstrElement::doTest(ITokCollection*& pTc)
{
	std::string string = pTc->show();
	if (string.find(" < ?") != std::string::npos)
	{
		doActions(string);
		return true;
	}
	return false;
}

//provides functionality to test whether it is XML TaggedAttribute token or not.
bool XMLTaggedAttributeElement::doTest(ITokCollection*& pTc)
{
	std::string string = pTc->show(); 
	std::string type = identifyTaggedAndTextElement(string);
	if (type == "TaggedAttributeElement" || type == "TaggedAttributeAndClosingElement")
	{
		doActions(string);
		return true;
	}
	return false;
}

//provides functionality to test whether it is XML TaggedNonAttribute token or not.
bool XMLTaggedNonAttributeElement::doTest(ITokCollection*& pTc)
{
	std::string string = pTc->show();
	std::string type = identifyTaggedAndTextElement(string);
	if (type == "TaggedNoAttributeElement")
	{
		doActions(string);
		return true;
	}
	return false;
}

//provides functionality to test whether it is XML TextAttribute token or not.
bool XMLTextElement::doTest(ITokCollection*& pTc)
{
	std::string string = pTc->show();
	std::string type = identifyTaggedAndTextElement(string);
	if (type == "TextElement")
	{
		doActions(string);
		return true;
	}
	return false;
}

//provides functionality to test whether it is XML ClosingTag token or not.
bool XMLClosingTag::doTest(ITokCollection*& pTc)
{
	std::string string = pTc->show();
	std::string type = identifyTaggedAndTextElement(string);
	if (type == "ClosingTag")
	{
		doActions(string);
		return true;
	}
	return false;
}


//performs action if XML declaration is detected.
void HandleXMLDeclarartionStatement::doAction(std::string string)
{
	std::string buf; // Have a buffer string
	std::vector<std::string> tokens; // Create vector to hold our words
	std::_Bool valueFlag = false;
	std::vector<std::string> attribute;
	std::vector<std::string> value;
	int i = 0;
	std::shared_ptr <AbstractXmlElement> xmlDeclare = makeXmlDeclarElement();
	std::stringstream ss(string);
	while (ss >> buf) // dissects the string using space as delimeter
	{
		tokens.push_back(buf); // saves each word into tokens vector
		if (buf == "=" || valueFlag == true)
		{
			if (valueFlag == false)
				attribute.push_back(tokens[i - 1]);

			if (valueFlag == true)
			{
				std::string string = tokens[i];
				string.erase(0, 1);
				string.erase(string.end() - 1, string.end());
				value.push_back(string);
				valueFlag = false;
			}
		}
		if (buf == "=")
		{
			valueFlag = true;
		}
		i++;
	}
	int j = 0;
	for (auto attributeName : attribute)
	{
		xmlDeclare->addAttrib(attributeName, value[j]);// add attributes to the docElement
		j++;
	}
	p_Repos->getRoot()->addChild(xmlDeclare); // add xmldeclaration Element to the docElement
}

//performs action if XML Comment is detected.
void HandleXMLCommentElement::doAction(std::string string)
{
	string.erase(0, 9);
	string.erase(string.end() - 5, string.end());
	std::shared_ptr <AbstractXmlElement> xmlComment = makeCommentElement(string);
	if (p_Repos->getStack().size() == 0)
	p_Repos->getRoot()->addChild(xmlComment);
	else
	p_Repos->getStack().top()->addChild(xmlComment); // add XMLComment Element to the the shared pointer of element present in top of stack
}

//performs action if XML ProcInstr is detected.
void HandleXMLProcInstrElement::doAction(std::string string)
{
	std::string buf; // Have a buffer string
	std::vector<std::string> tokens; // Create vector to hold our words
	std::_Bool valueFlag = false, styleSheetFlag = false;
	std::vector<std::string> attribute;
	std::vector<std::string> value;
	int i = 0, counter=0;
	std::stringstream ss(string);// dissects the string using space as delimeter
	while (ss >> buf)
	{
		tokens.push_back(buf);
		if (buf.find("-") != std::string::npos)
		{
			counter = i;
			styleSheetFlag = true;
		}
		if (buf == "=" || valueFlag == true)
		{
			if (valueFlag == false)
				attribute.push_back(tokens[i - 1]);
			if (valueFlag == true)
			{
				std::string string = tokens[i];
				string.erase(0, 1);
				string.erase(string.end() - 1, string.end());
				value.push_back(string);
				valueFlag = false;
			}
		}
		if (buf == "=")
		{
			valueFlag = true;
		}
		i++;
	}
	std::string strStyleSheet = tokens[2];
	if (styleSheetFlag)
	strStyleSheet = tokens[counter - 1] + "-" + tokens[counter + 1];
	std::shared_ptr <AbstractXmlElement> xmlProcInstr = makeProcInstrElement(strStyleSheet);
	int j = 0;
	for (auto attributeName : attribute)
	{
		xmlProcInstr->addAttrib(attributeName, value[j]);
		j++;
	}
	p_Repos->getRoot()->addChild(xmlProcInstr); //add xmlProcInstr to the doc element
}

//performs action if XML TaggedAttribute is detected.
void HandleXMLTaggedAttributeElement::doAction(std::string string)
{
	int incrementTokenCounter = 0;
	std::vector<std::string> tokens; // Create vector to hold our words
	std::_Bool valueFlag = false;
	std::vector<std::string> attribute;
	std::vector<std::string> value;
	int i = 0;
	tokens = processTokens(string); // process tokens based on ' and "
	for (auto elem : tokens) // dissects attribute and value of tag 
	{
		if (elem == "=")
		{
			std::string valueString = tokens[incrementTokenCounter + 1];
			attribute.push_back(tokens[incrementTokenCounter - 1]);
			valueString.erase(0, 1);
			valueString.erase(valueString.end() - 1, valueString.end());
			value.push_back(valueString);
		}
		incrementTokenCounter++;
	}
	int j = 0;
	std::shared_ptr <AbstractXmlElement>  xmlTagged = makeTaggedElement(tokens[1]);
	if (attribute.size() != 0)
	{
		for (auto attributeName : attribute)
		{
			xmlTagged->addAttrib(attributeName, value[j]); 
			j++;
		}
		if (p_Repos->getStack().size() == 0)
			p_Repos->getRoot()->addChild(xmlTagged);
		attribute.clear();
		value.clear();
	}
	if (string.find("/ >") == std::string::npos)
		p_Repos->getStack().push(xmlTagged);
	else
	{
		p_Repos->getStack().top()->addChild(xmlTagged);// add XML Tagged Element to the the shared pointer of element present in top of stack
	}
}

//process tokens based on ' and " if there space is present in values.It is a special case function
std::vector<std::string> HandleXMLTaggedAttributeElement::processTokens(std::string string)
{
	std::string buf; // Have a buffer string
	std::_Bool singleCommaFlag = false;
	std::string singleCommaText = "";
	std::_Bool doubleCommaFlag = false;
	std::string doubleCommaText = "";
	std::vector<std::string> tokens;
	std::stringstream ss(string);
	while (ss >> buf)
	{
		if (buf.find("'") != std::string::npos)
		{
			singleCommaText = singleCommaText + buf + " ";
			singleCommaFlag = true;
		}
		else if (buf.find("\"") != std::string::npos)
		{
			doubleCommaText = doubleCommaText + buf + " ";
			doubleCommaFlag = true;
		}
		else
		{
			if (singleCommaFlag == true)
			{
				singleCommaText = singleCommaText.erase(singleCommaText.size() - 1, singleCommaText.size());
				tokens.push_back(singleCommaText); // pushback value with space in which single comma is present
				singleCommaFlag = false;
			}
			if (doubleCommaFlag == true)
			{
				doubleCommaText = doubleCommaText.erase(doubleCommaText.size() - 1, doubleCommaText.size());
				tokens.push_back(doubleCommaText);// pushback value with space in which double comma is present
				doubleCommaFlag = false;
				doubleCommaText = "";
			}
			tokens.push_back(buf);
		}
	}
	return tokens; 
}

//performs action if XML tagged Non Attribute is detected.
void HandleXMLTaggedNonAttributeElement::doAction(std::string string)
{
	std::string buf; // Have a buffer string
	std::vector<std::string> tokens; // Create vector to hold our words
	int i = 0;
	std::stringstream ss(string);
	while (ss >> buf)
	{
		tokens.push_back(buf);
	}
	std::shared_ptr <AbstractXmlElement> xmlTagged = makeTaggedElement(tokens[1]);
	if (p_Repos->getStack().size() == 0)
		p_Repos->getRoot()->addChild(xmlTagged);
	if (string.find(">") != std::string::npos)
		p_Repos->getStack().push(xmlTagged);// add XML Tagged Element to the the shared pointer of element present in top of stack
	tokens.clear();
}

//performs action if XML TextAttribute is detected.
void HandleXMLTextElement::doAction(std::string string)
{
	string = string.erase(0, 2);
	std::shared_ptr <AbstractXmlElement>  xmlText = makeTextElement(string);
	p_Repos->getStack().top()->addChild(xmlText);
}

//performs action if XML ClosingTag is detected.
void HandleXMLClosingTag::doAction(std::string string)
{
    std::shared_ptr <AbstractXmlElement>  topElement = p_Repos->getStack().top();
	p_Repos->getStack().pop();
	if (p_Repos->getStack().size() == 0)
		p_Repos->getRoot()->addChild(topElement);
	else
		p_Repos->getStack().top()->addChild(topElement);
	
}

#ifdef TEST_RULESANDACTIONS
int main()
{
	std::cout << "\n  Testing ActionsAndRules class\n "<< std::string(30, '=') << std::endl;
	std::string XMLString ="< ? xml version = \"1.0\" encoding = \"utf-8\" ? >";
	XMLString += " < ? xml - stylesheet type = \"text/xsl\" href = \"style.xsl\" ? > ";
	XMLString += " < ! - - XML test case -- >";
	XMLString += "< LectureNote course = \"CSE681\" note = \"my note\" >";
	XMLString += "XML Example #1";
	XMLString += "< / LectureNote >";
	XmlParts* pElementParts;
	Parser* pParser;
	Repository* pRepo;
	Toker* pToker = new Toker;
	pToker->attach(XMLString, false);//attaching the XML String using toker pointer
	pElementParts = new XmlParts(pToker); 
	pElementParts->get();
	pRepo = new Repository(pToker);
	pParser = new Parser(pElementParts);
	ITokCollection* pTc = pParser->getTokCollection();
	XMLDeclarartionStatement *pDecl = new XMLDeclarartionStatement();
	HandleXMLDeclarartionStatement *pHDecl = new HandleXMLDeclarartionStatement(pRepo);
	pDecl->doTest(pTc); // - testing whether it is XML decaration Element or not
	pHDecl->doAction("< ? xml version = \"1.0\" encoding = \"utf-8\" ? > "); // - performing action on XML Declaration Element

	XMLProcInstrElement *pProcInstr = new XMLProcInstrElement();
	HandleXMLProcInstrElement *pHProcInstr = new HandleXMLProcInstrElement(pRepo);
	pProcInstr->doTest(pTc);
	pHProcInstr->doAction("< ? xml - stylesheet type = \"text/xsl\" href = \"style.xsl\" ? >");

	XMLCommentElement *pComment = new XMLCommentElement();
	HandleXMLCommentElement *pHComment = new HandleXMLCommentElement(pRepo);
	pComment->doTest(pTc);
	pHComment->doAction(" < ! - - XML test case -- >");
	
	XMLTaggedAttributeElement *pTagAttr = new XMLTaggedAttributeElement();
	HandleXMLTaggedAttributeElement *pHTagAttr = new HandleXMLTaggedAttributeElement(pRepo);
	pTagAttr->doTest(pTc);
	pHTagAttr->doAction("< LectureNote course = \"CSE681\" note = \"my note\" >");

	XMLTextElement *pText = new XMLTextElement();
	HandleXMLTextElement *pHText = new HandleXMLTextElement(pRepo);
	pText->doTest(pTc);
	pHText->doAction("  XML Example #1 ");

	XMLClosingTag *pClosingTag = new XMLClosingTag();
	HandleXMLClosingTag *pHClosingTag = new HandleXMLClosingTag(pRepo);
	pClosingTag->doTest(pTc);
	pHClosingTag->doAction("< / LectureNote >");
	std::cout << "\n"" Internal Tree Representation formed is: "<<std::endl<<pRepo->getRoot()->toString();
}
#endif




