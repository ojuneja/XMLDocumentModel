
#include"Executive.h"

Executive::Executive(std::shared_ptr<AbstractXmlElement> pDocElement) :pDocElement_(pDocElement){}

void Executive::demonstrateFindByTag( Display dp, XmlProcessing::XmlDocument &doc, const std::string tag)
{
	//demonstrates requirment by finding element using ID/Tag
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n"<< "Demonstrating Requirement 6 by finding pointers to the a collection of elements that have the tag: "+ tag +"";
	std::cout << "\n" << std::string(150, '=');
	std::vector<std::shared_ptr<AbstractXmlElement>> vectorSharedPtr;
	vectorSharedPtr = doc.findById(tag).select();
	dp.displayToConsole(vectorSharedPtr, tag);
}

void Executive::demonstrateFindByNameValue(Display dp, XmlProcessing::XmlDocument &doc, const std::string name, const std::string value)
{
	//demonstrates requirment by finding element using name value pair
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 5 by finding pointer to the element that have the specified name and value pair";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n" << "Query is: Find with name and value pair as: '" + name + " = " + value + "'"<<"\n";
	std::vector<std::shared_ptr<AbstractXmlElement>> vectorSharedPtr;
	vectorSharedPtr = doc.findByNameAndValue(name, value).select();
	dp.displayToConsole(vectorSharedPtr, name, value);
}


void Executive::demonstrateAddAttribute(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, std::string name, const std::string value)
{
	//demonstrates requirment of add child by adding attribute
	bool displayFlag = false;
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 9 by adding name and value pair that supports attributes";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n""\n" << "Query is: Add Name-Value Pair: '" << name << " = " << value << "' to Tag: " << parent << "\n";
	displayFlag = doc.findById(parent).addAttribute(name,value);
	dp.displayToConsole(pDocElement_, displayFlag, parent);
	dp.writeToOutputXML(pDocElement_, displayFlag);
}

void Executive::demonstrateAddChild(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string option)
{
	
	bool displayFlag = false;
	std::shared_ptr<AbstractXmlElement> sharedPtr;
	if (option == "comment")
	{
		//demonstrates requirment of add child by adding comment element
		std::cout << "\n""\n""\n" << std::string(150, '=');
		std::cout << "\n" << "Demonstrating Requirement 7 by adding Child Element to any Element in the tree that can hold child references found by ID or Tag.";
		std::cout << "\n" << std::string(150, '=');
		std::cout << "\n" << "Query is: Add Comment Element: 'My Comment' to the parent tag: " + parent + "" << "\n";
		sharedPtr = makeCommentElement("My Comment"); //making the pointer of comment element
		displayFlag = doc.findById(parent).addChild(sharedPtr);
		dp.displayToConsole(pDocElement_, displayFlag, parent);
		dp.writeToOutputXML(pDocElement_, displayFlag);
	}
	else if (option == "tag")
	{
		//demonstrates requirment of add child by adding tagged element
		std::cout << "\n""\n""\n" << std::string(150, '=');
		std::cout << "\n"<< "Demonstrating Requirement 7 by adding Child Element to any Element in the tree that can hold child references found by ID or Tag.";
		std::cout << "\n" << std::string(150, '=');
		std::cout << "\n" << "Query is: Add Tagged Element with tag: 'NewChild' and Name,Value Pair:'NewChildName = NewChildValue' to the parent tag: " + parent + "." << "\n";
		sharedPtr = makeTaggedElement("NewChild");
		sharedPtr->addAttrib("NewChildName", "NewChildValue");//making the pointer of tagged element
		displayFlag = doc.findById(parent).addChild(sharedPtr);
		dp.displayToConsole(pDocElement_, displayFlag, parent);
		dp.writeToOutputXML(pDocElement_, displayFlag);
	}
	else if (option == "text")
	{
		//demonstrates requirment of add child by adding text element
		std::cout << "\n""\n""\n" << std::string(150, '=');
		std::cout << "\n" << "Demonstrating Requirement 7 by adding Child Element to any Element in the tree that can hold child references found by ID or Tag.";
		std::cout << "\n" << std::string(150, '=');
		std::cout << "\n" << "Query is: Add Text Element with Text: 'NewChildText' to the parent tag: "+ parent +"."<<"\n";
		sharedPtr = makeTextElement("NewChildText");//making the pointer of text element
		displayFlag = doc.findById(parent).addChild(sharedPtr);
		dp.displayToConsole(pDocElement_, displayFlag, parent);
		dp.writeToOutputXML(pDocElement_, displayFlag);
	}
	
}

void Executive::demonstrateRemoveChild(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string elementToBeDeleted)
{
	//demonstrates requirment of remove child and then send the output to display class
	bool displayFlag = false;
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 7 by removing Child Element from any Element in the tree that can hold child references found by ID or Tag.";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n" << "Query is: :Remove Child Element with Tag: " + elementToBeDeleted + " from the parent tag: "+parent+"."<<"\n";
	displayFlag = doc.findById(parent).removeChild(elementToBeDeleted);
	dp.displayToConsole(pDocElement_, displayFlag, parent);
	dp.writeToOutputXML(pDocElement_, displayFlag);
}

void Executive::demonstrateRemoveAttribute(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent, const std::string name, const std::string value)
{
	//demonstrates requirment of remove attribute and then send the output to display class
	bool displayFlag = false;
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 9 by removing name and value pair that supports attributes";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n" << "Query is: Remove Child Attribute with Name-Value Pair: '" + name + " = " + value + "' from the tag: " + parent + "." << "\n";
	displayFlag = doc.findById(parent).removeAttribute(name, value);
	dp.displayToConsole(pDocElement_, displayFlag, parent);
	dp.writeToOutputXML(pDocElement_, displayFlag);
}

void Executive::demonstrateShowAttribute(Display dp, XmlProcessing::XmlDocument &doc,const std::string tag)
{
	//demonstrates requirment and then send the output to display class
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 8 provide a facility to return a std::vector containing all the name-value attribute pairs attached to that element";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n" << "Input is Pointer to Element: " << tag << "\n";
	std::vector<std::shared_ptr<AbstractXmlElement>> vectorSharedPtr;
	vectorSharedPtr = doc.findById(tag).select();
	if (vectorSharedPtr.size() > 0)
		dp.displayToConsole(doc.getAttributePairVector(vectorSharedPtr[0]), tag);
	else
	  std::cout <<"\n"<< "Tag: "<<tag<<" is not found in XML";

}

void Executive::demonstrateShowChildren(Display dp, XmlProcessing::XmlDocument &doc, const std::string parent)
{
	//demonstrates requirment and then send the output to display class
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 8 provide a facility to return a std::vector of pointers to all the children of a specified element.";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n" << "Input is Pointer to Element: " << parent << "\n";
	std::vector<std::shared_ptr<AbstractXmlElement>> vectorSharedPtr;
	vectorSharedPtr = doc.findById(parent).select();
	if (vectorSharedPtr.size() > 0)
	{
		dp.displayToConsole(doc.getChildrenVector(vectorSharedPtr[0]));
		dp.displayToConsole(doc.getChildrenVector(vectorSharedPtr[0]), parent);
	}
	else
	std::cout << "\n"<<"Tag: " << parent << " is not found in XML";
}

void Executive::demonstrateAddRoot(Display dp, XmlProcessing::XmlDocument &doc,const std::string root)
{
	//demonstartes add Root requirement
	bool displayFlag = false;
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstrating Requirement 7 by providing the ability to add a root element to an empty document tree";
	std::cout << "\n" << std::string(150, '=');
	std::cout << "\n" << "Query is:: Add Tagged Element: '" + root + "'id the root is empty." << "\n";
	displayFlag = doc.addRoot(root);
	if (displayFlag)
	{
		dp.displayToConsole(doc.getRoot(), displayFlag);
		dp.writeToRootXML(doc.getRoot(), displayFlag);
	}
	else
	{
		std::cout << "\n""\n" << "Cannot Form New Root because Childrens are already Present" << "\n";
	}
}

void Executive::demonstrateMoveOperation(Display dp, XmlProcessing::XmlDocument &doc)
{
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n"<<"Demonstrating Requirement 4 by moving one XML Document object to another using Move Constructor and Move Assignment Operator. ";
	std::cout << "\n" << std::string(150, '=');
	XmlProcessing::XmlDocument newDoc = std::move(doc);
	if (doc.getRoot() == nullptr)
	{
		std::cout << "\n" << "After Move Constructor operation,New object is holding the Internal Representation of Tree : ";
		std::cout << "\n" << newDoc.getRoot()->toString()<<"\n";
	}
	XmlProcessing::XmlDocument newNewDoc;
	newNewDoc = std::move(newDoc);
	if (newDoc.getRoot() == nullptr)
	{
		std::cout << "\n" << "After Move Assignment operation,New object is holding the Internal Representation of Tree : ";
		std::cout << newNewDoc.getRoot()->toString() << "\n";
	}
	dp.writeToRootXML(newNewDoc.getRoot(), true);
}

std::string makeString()
{ //make the string so that it can be parsed
	std::string XMLString =
		"<?xml version = \"1.0\" encoding = \"utf-8\"?>";
	XMLString += "<?xml-stylesheet type=\"text/xsl\" href=\"style.xsl\"?>";
		XMLString += "<!--XML test case -->";
		XMLString += "<LectureNote course = \"CSE681\" note = \"my note\">";
		XMLString += "<title>XML Example 1</title>";
		XMLString += "<reference>";
		XMLString += "<title>Programming Microsoft</title>";
		XMLString += "<author>Jeff Prosise";
		XMLString += "<TestTag tagName = \"Tester\">";
		XMLString += "<ChildTestTag tagName = \"ChildTester\">";
		XMLString += "<GreatChildTestTag tagName = \"Tester\"/>";
		XMLString += "</ChildTestTag>";
		XMLString += "</TestTag>";
		XMLString += "<note Company = 'Wintellect'></note></author>";
		XMLString += "<publisher>Microsoft Press</publisher>";
		XMLString += "</reference>";
		XMLString += "<comment>Description of PCDATA</comment>";
		XMLString += "</LectureNote>";
	return XMLString;
}


void Executive::executeCommands(ConfigParseToConsole configure)
{
	//demonstrating each requirment one by one
	Display dp;
	XmlProcessing::XmlDocument doc(configure.getRepository()->getRoot());
	std::cout << "\n""\n""\n" << std::string(150, '=');
	std::cout << "\n" << "Demonstarting Requirement 3 and 10 by parsing and thereby writing an XML File/String to corresponding Tree representation";
	std::cout << "\n" << std::string(150, '=');
	dp.displayToConsole(configure.getRepository()->getRoot(), true);
	dp.writeToOutputXML(configure.getRepository()->getRoot(), true);
	//Execute Functions:If TA supplies any new XML then he can make neccesary changes 
	demonstrateAddRoot(dp, doc, "NewRoot");
	demonstrateFindByTag(dp, doc, "title");
	demonstrateFindByTag(dp, doc, "HelloWorld");
	demonstrateFindByNameValue(dp, doc, "tagName", "Tester");
	demonstrateFindByNameValue(dp, doc, "InvalidName", "InvalidValue");
	demonstrateShowAttribute(dp, doc, "LectureNote");
	demonstrateShowChildren(dp, doc, "LectureNote");
	demonstrateAddAttribute(dp, doc, "title", "name", "ojas");
	demonstrateAddChild(dp, doc, "LectureNote", "comment");
	demonstrateAddChild(dp, doc, "LectureNote", "tag");
	demonstrateAddChild(dp, doc, "LectureNote", "text");
	demonstrateRemoveAttribute(dp, doc, "GreatChildTestTag", "tagName", "Tester");
	demonstrateRemoveChild(dp, doc, "author", "TestTag");
	doc.findById("").removeChild("LectureNote"); //removing the root from the docElement so that addRoot Functionality can be tested
	demonstrateAddRoot(dp, doc, "NewRoot");
	demonstrateMoveOperation(dp, doc);

}

void executeForXML(const std::string &name)
{
	//build parser
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	// Now parse each file
	if (pParser)
	{
		bool flag = configure.Attach(name);
		if (!flag)
			{
				std::cout << "\n  could not open file " << name << std::endl;
				return;
			}
		}
	
	else
	{
		std::cout << "\n\n  Parser not built\n\n";
		return;
	}
	// now that parser is built, use it
	Executive exec(configure.getRepository()->getRoot());
	while (pParser->next())
		pParser->parse();
		exec.executeCommands(configure);
}

void executeForString()
{
	//build parser
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	std::string string = makeString();
	if (pParser)
	{
		bool flag = configure.Attach(string, false);
		if (!flag)
		{
			std::cout << "\n  could not open file " << string << std::endl;
			return;
		}
	}

	else
	{
		std::cout << "\n\n  Parser not built\n\n";
		return;
	}
	// now that parser is built, use it
	Executive exec(configure.getRepository()->getRoot());
	while (pParser->next())
		pParser->parse();
	exec.executeCommands(configure);
}


//-------------------------------------------------------------MAIN FUNCTION--------------------------------------------------------------------
int main(int argc, char *argv[])
{
	//firstly all the operations carried out using XML and then through string
	bool xmlFlag = true;
	bool stringFlag = false;
	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}
	try
	{
		while (xmlFlag == true || stringFlag == true)
		{
			if (xmlFlag)
			{
				std::cout << "\n" << std::string(150, '=');
				std::cout << "\n" << "Demonstarting Requirement 10 by reading from XML File";
				std::cout << "\n" << std::string(150, '=');
				executeForXML(argv[1]);
				xmlFlag = false;
				stringFlag = true;
			}
			else
			{
				std::cout << "\n""\n""\n""\n""\n" << std::string(150, '=');
				std::cout << "\n" << std::string(150, '=');
				std::cout << "\n" << "Demonstarting Requirement 10 by reading from XML String" << "\n";
				std::cout << "\n" << "NOW ALL THE OPERATIONS WILL BE REPEATED FOR STRING INPUT" << "\n";
				std::cout << "\n" << std::string(150, '=') << "\n";
				std::cout << "\n" << std::string(150, '=') << "\n""\n""\n";
				executeForString();
				stringFlag = false;
			}
			}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	std::cout << "\n\n";	
}