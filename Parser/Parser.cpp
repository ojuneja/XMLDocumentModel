
///////////////////////////////////////////////////////////////////
//  Parser.h  -  implementation file for Defining rules and      //
//                actions for parser                             //
//  ver 1.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 13.0                           //
//  Platform:     HP Pavilion g series, Win 7.0                  //
//Application:  Parser.h ,Project - 2(XML Document Model)        //
//  Author:       Ojas Juneja                                    //
//                Syracuse University                            //
//                ojuneja@syr.edu, (315) 751-8944                //
///////////////////////////////////////////////////////////////////



#include"Parser.h"

//----< register action with a rule >--------------------------

void IRule::addAction(IAction *pAction)
{
	actions.push_back(pAction);
}
//----< invoke all actions associated with a rule >------------

void IRule::doActions(std::string string)
{

	if (actions.size() > 0)
		for (size_t i = 0; i<actions.size(); ++i)
			actions[i]->doAction(string);
}



std::string IRule::identifyTaggedAndTextElement(std::string string)
{
	int i = 0;
	std::string buf; // Have a buffer string
	//identifying text elememt
	if (string.find("<") == std::string::npos && string.find(">") == std::string::npos)
	{
		return "TextElement";
	}
	else
	{ //identifying tagged or text or tagged Non Attribute elememt
		if (string.find("<") != std::string::npos && string.find("/ >") != std::string::npos)
			return "TaggedAttributeAndClosingElement";
		else if (string.find("< /") != std::string::npos)
			return "ClosingTag";//identifying closing tag
		else if (string.find("=") != std::string::npos)
		{
			return "TaggedAttributeElement";
		}
		else
			return "TaggedNoAttributeElement";
	}
}

//----< register parsing rule >--------------------------------

void Parser::addRule(IRule* pRule)
{
	rules.push_back(pRule); //add rules in rules vector
}

bool Parser::parse()
{ //parses the XML or string
	bool succeeded = false;
	for (size_t i = 0; i<rules.size(); ++i)
	{
		if (rules[i]->doTest(pTokColl))
		{
			succeeded = true;
			break;
		}
	}
	return succeeded;
}


bool Parser::next()
{
	//parser next string if true
	bool succeeded = pTokColl->get();
	if (!succeeded)
		return false;

	return true;
}

#ifdef TEST_PARSER


#include <string>
#include "RulesAndActions.h"
#include "ConfigureParser.h"
int main(int argc, char* argv[])
{
	std::cout << "\n  Testing Parser class\n "
		<< std::string(22, '=') << std::endl;

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	for (int i = 1; i<argc; ++i)
	{
		std::cout << "\n  Processing file " << argv[i];
		std::cout << "\n  " << std::string(16 + strlen(argv[i]), '-');
		// build parser
		ConfigParseToConsole configure;
		Parser* pParser = configure.Build();
		try
		{
			if (pParser)
			{
				if (!configure.Attach(argv[i]))
				{
					std::cout << "\n  could not open file " << argv[i] << std::endl;
					continue;
				}
			}
			else
			{
				std::cout << "\n\n  Parser not built\n\n";
				return 1;
			}
			// now that parser is built, use it

			while (pParser->next())
				pParser->parse();
			std::cout << "\n\n" << configure.getRepository()->getRoot()->toString();
		}
		catch (std::exception& ex)
		{
			std::cout << "\n\n    " << ex.what() << "\n\n";
		}
		std::cout << "\n\n";
	}
}

#endif
