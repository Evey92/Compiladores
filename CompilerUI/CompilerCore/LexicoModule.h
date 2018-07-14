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
		PARSING_COMMENT,
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
		int GetTotalTokens();
		int GetTokenIterator();
		const CToken* const GetActualToken();
		void SetTokenIterator(int at);
		const CToken* const PeekTokenAt(int offset);		
		const CToken* const PeekNextToken();
		void LexAddError(int lineNum, char* desc , const char* line);
		void ClearToken();
		void ResetTokenCounter();
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

	int LexicoModule::GetTotalTokens()
	{
		return m_Tokens.size();
	}

	int LexicoModule::GetTokenIterator()
	{
		return tokenIterator;
	}

	const CToken* const  LexicoModule::GetActualToken()
	{
		return m_Tokens[tokenIterator];
	}

	void LexicoModule::SetTokenIterator(int at)
	{
		tokenIterator = at;
	}

	const CToken* const LexicoModule::PeekTokenAt(int offset)
	{
		return m_Tokens[offset];
	}

	const CToken* const LexicoModule::PeekNextToken()
	{
		return m_Tokens[tokenIterator + 1];
	}

	void LexicoModule::LexAddError(int line_num, char* desc, const char* line)
	{
		String^ strDesc = gcnew String(desc);
		String^ strLine = gcnew String(line);
		m_err->AddError(ERROR_PHASE::LEXICO, line_num, strDesc, strLine);
	}

	
	void LexicoModule::ClearToken()
	{
		m_Tokens.clear();
	}

	void LexicoModule::ResetTokenCounter()
	{
		tokenIterator = -1;
	}

	bool LexicoModule::ParseSourceCode(const char* src)
	{
		int currentLineNum = 1;
		const char* currChar = src;
		const char* currLine = src;
		int errorPosition = -1;
		char errorBuffer[1000];
		bool isComment = false, isString = false;
		int ended = 2;
		int iCurrentLine = 1;

		std::string tokenBuffer;
		m_state = LEX_STATE::START;
		ClearToken();

		memset(errorBuffer, 0, sizeof(errorBuffer));
		while (ended>0 && m_err->ReturnNumErrors <= m_err->ReturnMaxErrors())
		{
			switch (m_state)
			{
				case LEX_STATE::START:
					if (isalpha(*currChar) || *currChar == ' ')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						m_state = LEX_STATE::PARSING_ID;
					}
					else if (isdigit(*currChar))
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						m_state = LEX_STATE::PARSING_INT;

					}
					else if (*currChar == 34)
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						isString = true;
						m_state = LEX_STATE::PARSING_STRING;
					}
				
					else if (*currChar == '<' || *currChar == '>' || *currChar == '=' || *currChar == '!')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						m_state = LEX_STATE::PARSING_RELATIONAL_OP;
					}
					else if (*currChar == '+' || *currChar == '-' || *currChar == '*' || *currChar == '/' || *currChar == '^' || *currChar == '%')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						m_state = LEX_STATE::PARSING_ARTIHMETIC_OP;
						currChar++;
					}
					else if (*currChar == '&' || *currChar == '|')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						m_state = LEX_STATE::PARSING_LOGICAL_OP;
						currChar++;
					}
					else if (*currChar == '(' || *currChar == ')' || *currChar == '{' || *currChar == '}' || *currChar == '[' || *currChar == ']')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						m_state = LEX_STATE::PARSING_GROUPING;
					}
					else if (*currChar == ':' || *currChar == ',' || *currChar == ';')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						m_state = LEX_STATE::PARSING_SEPARATOR;
					}
					else if (*currChar == '.')
					{
						tokenBuffer.clear();
						tokenBuffer.append(currChar, 1);
						currChar++;
						m_state = LEX_STATE::PARSING_FLOAT;
					}
					else if (*currChar == 9)
					{
						currChar++;
					}
					else if (*currChar == '\n')
					{
						currChar++;
						iCurrentLine++;
						currLine = currChar;
					}
					else if (*currChar == 32)
					{
						currChar++;
					}
					else
					{
						errorPosition = currChar - currLine;
						memcpy(errorBuffer, currLine, errorPosition);
						errorBuffer[errorPosition] = '\0';
						LexAddError(iCurrentLine, "Carácter inválido ", errorBuffer);
						currChar++;
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
					else if (tokenBuffer.back() == '.')
					{
						//We throw an error here because it means we have a 5.a or 5.# or some shit like that
						currChar++;
						errorPosition = currChar - currLine;
						memcpy(errorBuffer, currLine, errorPosition);
						errorBuffer[errorPosition] = '\0';
						LexAddError(iCurrentLine, "ERROR: Hay dos puntos en este numero", errorBuffer);
						m_state = LEX_STATE::START;
					}
					else
					{
						AddToken(tokenBuffer, TOKEN_TYPE::FLOAT, currentLineNum);
						m_state = LEX_STATE::START;

					}
				}
				break;

				case LEX_STATE::PARSING_STRING:
				{
					if (*currChar != 34 && *currChar != '\r')
					{
						tokenBuffer.append(currChar, 1);
						currChar++;
					}
					else if (*currChar == '\r')
					{
						if (isString)
						{
							errorPosition = currChar - currLine;
							memcpy(errorBuffer, currLine, errorPosition);
							errorBuffer[errorPosition] = '\0';
							LexAddError(iCurrentLine, "ERROR: Hubo un salto de línea sin cerrar comillas de un comentario.", errorBuffer);
							currChar++;
							currChar++;
							iCurrentLine++;
							currLine = currChar;
							m_state = LEX_STATE::START;
						}
					}
					else if (*currChar == 34 && isString)
					{
						tokenBuffer.append(currChar, 1);
						currChar++;
						isString = false;
						AddToken(tokenBuffer, TOKEN_TYPE::STRING, iCurrentLine);
						m_state = LEX_STATE::START;
						tokenBuffer.clear();
					}
				}
				break;

				case LEX_STATE::PARSING_RELATIONAL_OP:
				{
					if (*currChar == '=')
					{
						if(tokenBuffer.back() == '>' || tokenBuffer.back() == '<' || tokenBuffer.back() == '=' || tokenBuffer.back() == '!')
						{
							tokenBuffer.append(currChar, 1);
							currChar++;
							AddToken(tokenBuffer, TOKEN_TYPE::RELATIONAL_OP, currentLineNum);
							m_state = LEX_STATE::START;
						}
						else
						{
							AddToken(tokenBuffer, TOKEN_TYPE::ASSIGN, iCurrentLine);
						}
					}
					else if (*currChar == '<' || *currChar == '>' || *currChar == '!')
					{
						errorPosition = currChar - currLine;
						memcpy(errorBuffer, currLine, errorPosition);
						errorBuffer[errorPosition] = '\0';
						LexAddError(iCurrentLine, "ERROR: Se detetctó <, >, o ! cuando se esperaba =", errorBuffer);
						m_state = LEX_STATE::START;
					}
					else 
					{
						if (tokenBuffer.back() == '!')
						{
							AddToken(tokenBuffer, TOKEN_TYPE::NEGATION_OP, iCurrentLine);
						}
						else
						{
							AddToken(tokenBuffer, TOKEN_TYPE::RELATIONAL_OP, iCurrentLine);
						}
						m_state = LEX_STATE::START;
					}
				}
				break;

				case LEX_STATE::PARSING_ARTIHMETIC_OP:
				{
					if (*currChar == '+' || *currChar == '-')
					{
						tokenBuffer.append(currChar, 1);
						currChar++;
						AddToken(tokenBuffer, TOKEN_TYPE::ARITHMETIC_OP, iCurrentLine);
						m_state = LEX_STATE::START;
					}
					else if (*currChar == '*' && tokenBuffer.back() == '/' && !isComment)
					{
						tokenBuffer.append(currChar, 1);
						currChar++;
						isComment = true;
						m_state = LEX_STATE::PARSING_COMMENT;
					}
					else
					{
						AddToken(tokenBuffer, TOKEN_TYPE::ARITHMETIC_OP, iCurrentLine);
						m_state = LEX_STATE::START;
					}
				}
				break;

				case LEX_STATE::PARSING_LOGICAL_OP:
				{
					if (*currChar == tokenBuffer.back())
					{
						tokenBuffer.append(currChar, 1);
						currChar++;
						AddToken(tokenBuffer, TOKEN_TYPE::LOGICAL_OP, iCurrentLine);
						m_state = LEX_STATE::START;
					}
					else
					{
						errorPosition = currChar - currLine;
						memcpy(errorBuffer, currLine, errorPosition);
						errorBuffer[errorPosition] = '\0';

						if (tokenBuffer.back() == '&')
						{
							//Throw error of invalid logical AND operator
							LexAddError(iCurrentLine, "ERROR: Operador & inválido", errorBuffer);
						}
						else if (tokenBuffer.back() == '|')
						{
							//Throw error of invalid logical OR operator
							LexAddError(iCurrentLine, "ERROR: Operador | inválido.", errorBuffer);
						}
						m_state = LEX_STATE::START;
					}
				}
				break;

				case LEX_STATE::PARSING_GROUPING:
				{
					AddToken(tokenBuffer, TOKEN_TYPE::GROUPING, iCurrentLine);
					m_state = LEX_STATE::START;
				}
				break;
			
				case LEX_STATE::PARSING_SEPARATOR:
				{
					if (*currChar != ',' || *currChar != ':' || *currChar != ';' && isalpha(*currChar) || isdigit(*currChar))
					{
						AddToken(tokenBuffer, TOKEN_TYPE::SEPARATOR, iCurrentLine);
						m_state = LEX_STATE::START;
					}
					else
					{
						errorPosition = currChar - currLine;
						memcpy(errorBuffer, currLine, errorPosition);
						errorBuffer[errorPosition] = '\0';
						LexAddError(iCurrentLine, "ERROR: Operador de separación repetido.", errorBuffer);
					}
				}
				break;
			}

			if (isString)
			{
				//We throw an error because the string was never closed
				errorPosition = currChar - currLine;
				memcpy(errorBuffer, currLine, errorPosition);
				errorBuffer[errorPosition] = '\0';
				LexAddError(iCurrentLine, "ERROR: Faltó cerrar un string con comillas", errorBuffer);
			}
			if (isComment)
			{
				//We throw an error because comment was never closed
				errorPosition = currChar - currLine;
				memcpy(errorBuffer, currLine, errorPosition);
				errorBuffer[errorPosition] = '\0';
				LexAddError(iCurrentLine, "ERROR: Nunca cerro el comentario con los operadores */", errorBuffer);
			}
			return m_err->ReturnNumErrors() == 0;
		}
	}
}