#include "stdafx.h"
#include "LexicoModule.h"

using namespace compilerCore;

LexicoModule::LexicoModule(CErrModule^ err)
{
	m_err = err;
}

LexicoModule::~LexicoModule(){
}

bool LexicoModule::parseSourceCode(const char* src)
{
	int currentLineNum = 1;
	const char* currChar = src;
	const char* currLine = src;
	std::string tokenBuffer;
	m_state = LEX_STATE::START;
	clearTokens();

	while (*currChar != '\0')
	{
		switch (m_state)
		{
		case LEX_STATE::START:
			if (isalpha(*currChar) || *currChar == ' ')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_ID;
				currChar++;
			}
			else if (isdigit(*currChar))
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_INT;
				currChar++;
			}
			else if ("is STRING")
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_STRING;
				currChar++;
			}
			else if ("is KEYWORD")
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_KEYWORD;
				currChar++;
			}
			else if (*currChar == '<' || *currChar == '>' ||  *currChar == '=' || *currChar == '!')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_RELATIONAL_OP;
				currChar++;
			}
			else if (*currChar == '+' || *currChar == '-' || *currChar == '*' || *currChar == '/' || *currChar == '^' || *currChar == '%')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_ARTIHMETIC_OP;
				currChar++;
			}
			else if (*currChar == '&' || *currChar == '|' || *currChar == '!')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_LOGICAL_OP;
				currChar++;
			}
			else if (*currChar == '!' || *currChar == '-' || *currChar == '*' || *currChar == '/' || *currChar == '^' || *currChar == '%')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_NEGATION_OP;
				currChar++;
			}
			else if (*currChar == '&&' || *currChar == '||' || *currChar == '!')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_LOGICAL_OP;
				currChar++;
			}
			/*
			.
			.
			.
			*/
			else
			{
				//agrega error
			}
			break;
		case LEX_STATE::PARSING_ID:
		{
			if (isalpha(*currChar || *currChar == ' ' || isdigit(*currChar)))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				if (m_keywords.find(tokenBuffer) != m_keywords.end())
				{
					addToken(tokenBuffer, TOKEN_TYPE::KEYWORD, currentLineNum);
				}
				else
				{
					addToken(tokenBuffer, TOKEN_TYPE::ID, currentLineNum);
				}
				m_state = LEX_STATE::START;
			}
			break;
		}
		case LEX_STATE::PARSING_INT: 
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			if (*currChar == '.')
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
				LEX_STATE::PARSING_FLOAT;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::INT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
			break;
		case LEX_STATE::PARSING_FLOAT:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;
		
		case LEX_STATE::PARSING_STRING:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_KEYWORD:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_RELATIONAL_OP:
		{
			if (*currChar == '=')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_ARTIHMETIC_OP;
				currChar++;
			}
			else if (*currChar == '&&' || *currChar == '||' || *currChar == '!')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currChar, 1);
				m_state = LEX_STATE::PARSING_LOGICAL_OP;
				currChar++;
			})
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_ARTIHMETIC_OP:
		{
			if (*currChar == '+' || *currChar == '-' && *currChar == tokenBuffer.back())
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_LOGICAL_OP:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_NEGATION_OP:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_SEPARATOR:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_ASSIGN:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_DIMENSIONAL:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;

		case LEX_STATE::PARSING_GROUPING:
		{
			if (isdigit(*currChar))
			{
				tokenBuffer.append(currChar, 1);
				currChar++;
			}
			else
			{
				addToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
			}
			m_state = LEX_STATE::START;
		}
		break;


		}
	}

	//return (numErrors == 0);
}

void LexicoModule::addToken(std::string lex, TOKEN_TYPE type, int line)
{
	CToken* p = new CToken(lex, type, line);
	m_Tokens.push_back(p);
}
