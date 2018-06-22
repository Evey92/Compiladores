#pragma once
#include "Windows.h"
#include "vcclr.h"
#include <vector>
#include "CErrModule.h"
#include "CToken.h"

using namespace System;
using std::string;

namespace CompilerCore
{
	public enum class LEX_STATE
	{
		START,
		PARSING_ID,
		PARSING_INT,
		PARSING_FLOAT,
		PARSING_STRING,
		PARSING_KEYWORD,
		PARSING_RELATIONAL_OP,
		PARSING_ARTIHMETIC_OP,
		PARSING_LOGICAL_OP,
		PARSING_NEGATION_OP,
		PARSING_SEPARATOR,
		PARSING_ASSIGN,
		PARSING_DIMENSIONAL,
		PARSING_GROUPING,
	};

	public class LexicoModule
	{
	private:
		msclr::gcroot<CErrModule^> m_err;
		std::vector<CToken*> m_Tokens;
		std::map<string, string> m_KeyWordMap;
		int tokenIterator;

	public:

		LexicoModule(CErrModule^ err);
		~LexicoModule();
		void Clear();
		void AddToken(string tokenBufer, TOKEN_TYPE p, int currentLineNum);
		const CToken* const GetNextToken();
		const CToken* const PeekTokenAt(int offset);		
		void LexAddError(int lineNum, char* desc , const char* line);
		int GetTotalTokens();
		void ClearToken();
		bool ParseSourceCode(const char* src);
		LEX_STATE m_state;
	};

	LexicoModule::LexicoModule(CErrModule^ err)
	{
		m_err = err;
		m_KeyWordMap.clear();
		m_KeyWordMap = {
		{ "var", "var"},
		{ "int", "int" },
		{ "float", "float" },
		{ "bool", "bool" },
		{ "string", "string" },
		{ "function", "function"},
		{ "main", "main" },
		{ "if", "if" },
		{ "else", "else" },
		{ "while", "while" },
		{ "for", "for"},
		{ "switch", "switch" },
		{ "default", "default" },
		{ "return", "return" },
		{ "case", "case" }
		};
	}

	LexicoModule::~LexicoModule() {
	}

	void LexicoModule::Clear()
	{
		m_err->Clear();
		m_state = LEX_STATE::START;
		m_Tokens.clear();
		tokenIterator = -1;
	}

	void LexicoModule::AddToken(string lex, CompilerCore::TOKEN_TYPE type, int line)
	{
		CToken* p_token = new CToken(lex, type, line);
		m_Tokens.push_back(p_token);
	}

	const CToken* const LexicoModule::GetNextToken()
	{
		++tokenIterator;
		return m_Tokens[tokenIterator];
	}

	const CToken* const LexicoModule::PeekTokenAt(int offset)
	{
		return m_Tokens[offset];
	}

	void LexicoModule::LexAddError(int line_num, char* desc, const char* line)
	{
		String^ strDesc = gcnew String(desc);
		String^ strLine = gcnew String(line);
		m_err->AddError(ERROR_PHASE::LEXICO, line_num, strDesc, strLine);
	}

	int LexicoModule::GetTotalTokens()
	{
		return m_Tokens.size();
	}

	void LexicoModule::ClearToken()
	{
		m_Tokens.clear();
	}

	bool LexicoModule::ParseSourceCode(const char* src)
	{
		int currentLineNum = 1;
		const char* currChar = src;
		const char* currLine = src;
		int errorPosition = -1;
		char errorBuffer[1000];
		bool iscommentary = false, isstring = false;
		int ended = 2;
		int iCurrentLine = 1;

		std::string tokenBuffer;
		m_state = LEX_STATE::START;
		ClearToken();

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
				else if (*currChar == '<' || *currChar == '>' || *currChar == '=' || *currChar == '!')
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
				else if (*currChar == '&' || *currChar == '|' || *currChar == '!')
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
					if (m_KeyWordMap.find(tokenBuffer) != m_KeyWordMap.end())
					{
						AddToken(tokenBuffer, TOKEN_TYPE::KEYWORD, currentLineNum);
					}
					else
					{
						AddToken(tokenBuffer, TOKEN_TYPE::ID, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::INT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
				}
				m_state = LEX_STATE::START;
			}
			break;

			case LEX_STATE::PARSING_RELATIONAL_OP:
			{
				if (*currChar == '=')
				{
					tokenBuffer.append(currChar, 1);
					currChar++;
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
					m_state = LEX_STATE::START;
				}
				else 
				{
					errorPosition = currChar - currLine;
					memcpy(errorBuffer, currLine, errorPosition);
					errorBuffer[errorPosition] = '\0';
					LexAddError(iCurrentLine, "Invalid relational operators m8", cErrorBuffer);
					m_LexState = LEXIC_STATE::START;
				}
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
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
					AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
				}
				m_state = LEX_STATE::START;
			}
			break;


			}
		}

		//return (numErrors == 0);
	}
}