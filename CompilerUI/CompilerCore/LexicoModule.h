#pragma once
#include "Windows.h"
#include "vcclr.h"
#include <vector>
#include "CErrModule.h"
#include "CToken.h"

using namespace System;
namespace compilerCore
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
		std::map<std::string, std::string> m_KeyWordMap;

	public:
		LexicoModule(CErrModule^ err);
		~LexicoModule();
		void addToken(std::string tokenBufer, TOKEN_TYPE p, int currentLineNum);
		bool parseSourceCode(const char* src);
		LEX_STATE m_state;
		void clearTokens();
		std::vector<CToken*> m_tokens;
		std::map<std::string, std::string> m_keywords;

	};
}
