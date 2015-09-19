///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
//Modified:     Ojas Juneja                                      //
//              Syracuse University                              //
//              ojuneja@syr.edu, (315) 751-8944                  //
///////////////////////////////////////////////////////////////////


#include "XmlDocument.h"



XmlProcessing::XmlDocument::XmlDocument()
{
	//Default Constructor
}

XmlProcessing::XmlDocument::XmlDocument(sPtr &pDocElement) : pDocElement_(pDocElement)
{
	//Empty Constructor designed to copy Variables
}

//Move Constructor
XmlProcessing::XmlDocument::XmlDocument(XmlProcessing::XmlDocument &&object) : pDocElement_(object.pDocElement_)
{
	object.pDocElement_ = nullptr;
	std::cout << "\n" << "Move Constructor Called";
}

//Move Assignment Operator
XmlDocument& XmlProcessing::XmlDocument::operator=(XmlProcessing::XmlDocument&& object)
{
	std::cout << "\n"<<"Move Assignment Operator Called";
	if (this == &object) return *this;
	else
	{
		pDocElement_ = object.pDocElement_;
		object.pDocElement_ = nullptr;
	} 
	return *this;
}




XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::findById(std::string tag)
{
	if (tag == "")
	{
		found_.push_back(pDocElement_); // pushes results in found vector
	}
	else{
		std::vector<std::shared_ptr<AbstractXmlElement>> result_ = pDocElement_->getChildren();
		for (auto &item : result_)
		{
			found_ = find(item, tag);
		}
	}
	return *this; // return XMLDocument pointer for chaining
}


std::vector<std::shared_ptr<AbstractXmlElement>> XmlProcessing::XmlDocument::find(std::shared_ptr<XmlProcessing::AbstractXmlElement>& pNode, std::string tag)
{
	if (pNode->value() == tag)
	{
		found_.push_back(pNode); // pushes results in found vector
	}
	for (auto pChild : pNode->getChildren())
	{
		find(pChild, tag);
	}
	return found_;
}





XmlProcessing::XmlDocument& XmlProcessing::XmlDocument::findByNameAndValue(const std::string& attributeName, const std::string& value)
{
	std::vector<std::shared_ptr<AbstractXmlElement>> result_ = pDocElement_->getChildren();
	for (auto &item : result_)
	{
	found_ = find(item, attributeName, value); // pushes results in found vector
	}
	
	return *this;
}


std::vector<std::shared_ptr<AbstractXmlElement>> XmlProcessing::XmlDocument::find(std::shared_ptr<XmlProcessing::AbstractXmlElement>& pNode, const std::string& attributeName, const std::string& value)
{
	for (auto elem : pNode->getAttribute())
	{
		if (elem.first.c_str() == attributeName)
		{
			if (elem.second.c_str() == value)
			{
				found_.push_back(pNode); // pushes results in found vector and then returns so only one result is pushed
				return found_;
			}
		}
	}
	for (auto pChild : pNode->getChildren())
	{
		find(pChild, attributeName,value);
	}
	return found_;
}

std::vector<std::pair<std::string, std::string>> XmlProcessing::XmlDocument::getAttributePairVector(std::shared_ptr < AbstractXmlElement > pTag)
{
	std::vector<std::pair<std::string, std::string>> attributePair;
	attributePair = pTag->getAttribute();
	return attributePair; //returns attribute pair vector
}

std::vector<std::shared_ptr<AbstractXmlElement>> XmlProcessing::XmlDocument::getChildrenVector(std::shared_ptr < AbstractXmlElement > pParent)
{
	std::vector<std::shared_ptr < AbstractXmlElement >> childVector;
	childVector = pParent->getChildren();
	return childVector; //returns children vector
}


std::vector<std::shared_ptr < AbstractXmlElement >> && XmlProcessing::XmlDocument::select()
{
	return std::move(found_); //does move assignment operation and clears found
}




bool XmlProcessing::XmlDocument::addChild(std::shared_ptr<AbstractXmlElement> child)
{
	//adds child to the proper location in tree and returns true if addition is done
	if (found_.size() > 0)
	{
		found_[0]->addChild(child);
		found_.clear();
		return true;
	}
	else
		return false;
}


bool XmlProcessing::XmlDocument::removeChild(std::string childToBeRemoved)
{
	//removes child from the proper location in tree and returns true if removal is done
	if (found_.size() > 0)
	{
		for (auto elem : found_[0]->getChildren())
		{
			if (elem->value() == childToBeRemoved)
			{
				found_[0]->removeChild(elem);
				found_.clear();
				return true;
			}
		}
	}
		return false;
}


bool XmlProcessing::XmlDocument::removeAttribute(std::string name, std::string value)
{
	//removes attribute from the proper location in tree and returns true if removal is done
	if (found_.size() > 0)
	{
		for (auto elem : found_[0]->getAttribute())
		{
			if (elem.first.c_str() == name)
			{
				if (elem.second.c_str() == value)
				{
					found_[0]->removeAttrib(name);
					found_.clear();
					return true;
				}
			}
		}
	}
	return false;
}


bool XmlProcessing::XmlDocument::addAttribute(const std::string &name, const std::string &value)
{
	//adds attribute to the proper location in tree and returns true if addition is done
	if (found_.size() > 0)
	{
		found_[0]->addAttrib(name, value);
		found_.clear();
		return true;
	}
	else
		return false;
}



bool XmlProcessing::XmlDocument::addRoot(const std::string &tag)
{
	//adds root if the tree is empty otherwise return false
	std::_Bool flag = false;
	if (pDocElement_)
	{
		for(auto elem:pDocElement_->getChildren())
		{
			if (dynamic_cast<TaggedElement *>(elem.get()) != nullptr)
				flag = true;
		}
		if (flag)
			return false;
		else
		{
			pDocElement_ = makeDocElement();
			std::shared_ptr<AbstractXmlElement> addRoot = makeTaggedElement(tag);
			pDocElement_->addChild(addRoot);
			return true;
		}
	}
	else
	{
		pDocElement_ = makeDocElement();
		std::shared_ptr<AbstractXmlElement> addRoot = makeTaggedElement(tag);
		pDocElement_->addChild(addRoot);
		return true;
	}
}

std::shared_ptr < AbstractXmlElement > XmlProcessing::XmlDocument::getRoot()
{
	return pDocElement_;
}




#ifdef TEST_DOCUMENT
#include"../Parser/ConfigureParser.h"
int main(int argc, char *argv[])
{
	title("Testing XmlDocument class");
	std::vector<std::pair<std::string, std::string>> vectorAttributePair;
	std::vector<std::shared_ptr<AbstractXmlElement>> vectorSharedPtr;
	// build parser first
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	configure.Attach(argv[1]);
	// now that parser is built, use it
	while (pParser->next())
		pParser->parse();
	std::shared_ptr < AbstractXmlElement > pDocElement;
	XmlProcessing::XmlDocument doc(configure.getRepository()->getRoot());
	pDocElement = doc.getRoot();
	//test and then display each method one by one 
	vectorSharedPtr = doc.findByNameAndValue("course","CSE681").select();
	std::cout << "\n\n" << "Displaying Functionality of Method:'findByNameAndValue' and Method:'select'" << "\n";
	std::cout << "\n\n" << "Query is:Find Collection of Elements with Name-Value Pair: 'course = CSE681'" << "\n" << "XML Portion found with specified ID is:";
	for (auto elem : vectorSharedPtr)
	{
		std::cout << "\n" << elem->toString() << "\n" << std::string(60, '-');
	}
	//On using the function select found Vector is moved
	vectorSharedPtr = doc.findById("LectureNote").select();
	std::cout << "\n\n" << "Displaying Functionality of Method:'findById' and Method: 'select'" << "\n";
	std::cout << "\n\n" << "Query is:Find Collection of Elements with tag: LectureNote"<<"\n"<<"XML Portion found with specified ID is:";
	for (auto elem : vectorSharedPtr)
	{
		std::cout << "\n" << elem->toString() << "\n" << std::string(60, '-');
	}

	std::cout << "\n\n" << "Displaying Functionality of Method:'addAttribute'" << "\n";
	std::cout << "\n\n" << "Query is: Add attribute with Name-Value: 'name = ojas' in tag: author" << "\n" << "Modified XML is:";
	doc.findById("author").addAttribute("name","ojas");
	std::cout << "\n\n" << pDocElement->toString() << "\n"<<std::string(60, '-');

	std::cout << "\n\n" << "Displaying Functionality of Method:'removeAttribute'" << "\n";
	std::cout << "\n\n" << "Query is: remove attribute with Name-Value: 'name = ojas' in tag: author" << "\n" << "Modified XML is:";
	doc.findById("author").removeAttribute("name", "ojas");
	std::cout << "\n\n" << pDocElement->toString() << "\n" << std::string(60, '-');

	std::cout << "\n\n" << "Displaying Functionality of Method:'addChild'" << "\n";
	std::cout << "\n\n" << "Query is: Add child with tag: 'children' in parent tag: author" << "\n" << "Modified XML is:";
	std::shared_ptr < AbstractXmlElement > sharedPtr = makeTaggedElement("children");
	doc.findById("author").addChild(sharedPtr);
	std::cout << "\n\n" << pDocElement->toString() << "\n" << std::string(60, '-');

	std::cout << "\n\n" << "Displaying Functionality of Method:'removeChild'" << "\n";
	std::cout << "\n\n" << "Query is: Remove child with tag: 'children' in parent tag: author" << "\n" << "Modified XML is:";
	doc.findById("author").removeChild("children");
	std::cout << "\n\n" << pDocElement->toString() <<"\n"<< std::string(60, '-');

	std::cout << "\n\n" << "Displaying Functionality of Method:'getAttributePairVector'" << "\n";
	std::cout << "\n\n" << "Query is: get attributePair by giving pointer to the element of Tag: LectureNote";
	vectorAttributePair = doc.getAttributePairVector(vectorSharedPtr[0]);
	std::cout << "\n""\n" << "Following Name-Value Attribute Pair Found:"<< "\n";
	for (auto elem : vectorAttributePair)
	{
		std::cout << elem.first.c_str() << " = " << elem.second.c_str() << "\n";
	}
	std::cout << std::string(60, '-');


	std::cout << "\n\n" << "Displaying Functionality of Method:'getChildrenVector'" << "\n";
	std::cout << "\n\n" << "Query is: get childrens by giving pointer to the element of Tag: LectureNote";
	for (auto elem : doc.getChildrenVector(vectorSharedPtr[0]))
	{
		std::cout << elem->value()  << "\n";
	}
	std::cout<<std::string(60, '-');

	std::cout << "\n\n" << "Displaying Functionality of Method:'addRoot'" << "\n";
	std::cout << "\n\n" << "Query is: adding root after deleting all the childs"<<"\n"<<"New Root Formed with Tagged element: 'newchild' is:";
	doc.findById("").removeChild("LectureNote");
	doc.findById("").removeChild("xml declaration");
	doc.findById("").removeChild("xml declaration");
	doc.findById("").removeChild("XML test case");
	doc.addRoot("newchild");
	std::cout << "\n\n" << doc.getRoot()->toString() <<"\n"<< std::string(60, '-');

	return 0;
	
}
#endif