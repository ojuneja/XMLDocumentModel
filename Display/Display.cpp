///////////////////////////////////////////////////////////////////
//  Display.h  -  implementation file for Display class          //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Display.cpp ,Project - 2(XML Document Model)     //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////


#include"Display.h"

void Display::displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>>& searchVectorDisplay, const std::string &tag)
{
	if (searchVectorDisplay.size() > 0)
	{
		std::cout << "\n" << "XML Portion found with ID/TAG: " << tag;
		for (auto elem : searchVectorDisplay) //displays the elements stored in searchvector that contains vector of shared pointers
		{
			std::cout << "\n" << std::string(60, '-');
			std::cout <<"\n""\n"<< elem->toString() << "\n";
		}
	}
	else
	{
		std::cout << "\n""\n" << "ID/TAG:" << tag << " is not found in XML" << "\n";
	}
}

void Display::displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> &searchVectorDisplay, const std::string &name, const std::string &value)
{
	if (searchVectorDisplay.size() > 0)
	{
		std::cout << "\n" << "XML Portion found with Key-Value Pair: " << "'" + name  + " : "+ value +"'";
		for (auto elem : searchVectorDisplay) //displays the elements stored in searchvector that contains vector of shared pointers
		{
			std::cout << "\n""\n" << elem->toString() << "\n";
		}
	}
	else
	{
		std::cout << "\n""\n"<<"Key-Value Pair:" << name << " : " << value << " is not found in XML" << "\n";
	}
}

void Display::displayToConsole(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag, const std::string parent)
{
	if (flag)
	{
		std::cout << "\n""\n" << "XML with modification: " << "\n";
		std::cout << "\n" << treeDisplay->toString() << "\n";  //displays the tree after modification if flag is true
	}
	else
	{
		std::cout << "\n""\n" << "Element with ID/Tag: "<<parent<< " is not found. "<<"\n";
	}
}

void Display::displayToConsole(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag)
{
	if (flag)
	{
		std::cout << "\n" << "Internal Tree Representation : " << "\n"<<std::string(60, '=');
		std::cout << "\n""\n" << treeDisplay->toString() << "\n"; //displays the tree after modification if flag is true
	}
	else
	{
		std::cout << "\n""\n" << "Cannot Form Internal Tree." << "\n";
	}
}


void Display::writeToOutputXML(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag)
{
	if (flag) //writes results to Output.xml if flag is true
	{
		std::ofstream outfile;
		outfile.open("Output.xml");
		std::cout << "\n""\n" << "Please Note: Output has been written in File: Output.xml" <<"\n";
		outfile << treeDisplay->toString();
		outfile.close();
	}
}

void Display::displayToConsole(std::vector<std::pair<std::string, std::string>> vectornameValuePair, const std::string tag)
{
	if (vectornameValuePair.size() > 0)
	{
		std::cout << "\n""\n" << "Following Name-Value Attribute Pair Found for pointer to the Element: " << tag << "\n";
		for (auto elem : vectornameValuePair)
		{
			std::cout <<"  "<< elem.first.c_str() <<" = "<< elem.second.c_str() << "\n"; //name-value  pair is diaplayed
		}
	}
	else
		std::cout << "\n""\n" << "Name-value pair not found for element: " << tag  << "\n";
}

void Display::writeToRootXML(std::shared_ptr<AbstractXmlElement> treeDisplay, std::_Bool flag)
{
	if (flag) //writes results to Root.xml if flag is true
	{
		std::ofstream outfile;
		outfile.open("Root.xml");
		std::cout << "\n""\n" << " Please Note: Output has been written in File: Root.xml" << "\n";
		outfile << treeDisplay->toString();
		outfile.close();
	}
}

void Display::displayToConsole(std::vector<std::shared_ptr<AbstractXmlElement>> childrenDisplay)
{
	if (childrenDisplay.size() > 0)
	{
		std::cout << "\n""\n" << "Following Children Found: " << "\n";
		for (auto elem : childrenDisplay)
		{
			std::cout << "  " << elem->value() << "\n"; //children of a particular parent is diaplayed
		}
	}
	else
		std::cout << "\n""\n" << "Children not found"<< "\n";
}


#ifdef TEST_DISPLAY
#include"../Parser/ConfigureParser.h"
int main()
{
	Display dp;
	title("Testing Display Package", '=');
	std::cout << "\n";

	//first making the XML to test Display package Functionality
	using sPtr = std::shared_ptr < AbstractXmlElement > ;
	std::vector < std::shared_ptr < AbstractXmlElement >> vectorSharepPtr;
	sPtr comment = makeCommentElement("My Comment");
	sPtr root = makeTaggedElement("root");
	root->addChild(comment);
	sPtr child = makeTaggedElement("child");
	child->addChild(makeTextElement("this is another test"));
	child->addAttrib("first", "test");
	root->addChild(child);
	sPtr docEl = makeDocElement(root);
	std::cout << " " << docEl->toString();
	std::cout << "\n\n";
	vectorSharepPtr.push_back(child);

	//checking display methods functionality
	dp.displayToConsole(vectorSharepPtr,"child");
	dp.displayToConsole(docEl, true);
	std::cout << "\n" << "doing some modification in XML by adding Tagged Element 'child2'" << "\n" << std::string(80, '=');

	//making a new tagged element and thereby modfifying the Tree.
	sPtr child2 = makeTaggedElement("child2");
	root->addChild(child2);
	vectorSharepPtr.push_back(child2);

	//checking display methods functionality
	dp.displayToConsole(root, true, "child");
	std::cout << "\n Displaying the XML Portion of attribute Name-Value Pair: 'first = test'" << "\n" << std::string(80, '=');
	dp.displayToConsole(vectorSharepPtr[0], "first","test");
	std::cout << "\n Displaying the Childrens of root: " << "\n" << std::string(80, '=');
	dp.displayToConsole(vectorSharepPtr);
	//checking display methods functionality by printing name-value pair of particular element
	std::cout << "\n Displaying the Name-Value Pair"<< "\n" << std::string(80, '=');
	dp.displayToConsole(child->getAttribute(),"child");
	std::cout << "\n Writing output to Output.XML" << "\n" << std::string(80, '=');
	dp.writeToOutputXML(docEl,true); //writing output to XML File
	return 0;
}
#endif
