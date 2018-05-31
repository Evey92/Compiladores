#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace compilerCore
{
	public enum class TOKEN_TYPE
	{
		UNDEFINED = 0,
		ID,
		INT,
		FLOAT,
		STRING,
		KEYWORD,
		RELATIONAL_OP,
		ARITHMETIC_OP,
		LOGICAL_OP,
		NEGATION_OP,
		SEPARATOR,
		ASSIGN,
		DIMENSION,
		GROUPING
	};

	public class CToken
	{

	private:

		std::string m_lexema;
		TOKEN_TYPE m_type;
		int lineNum;

	public:
		CToken(std::string lex, TOKEN_TYPE t, int lineN);
		~CToken();
		std::string getLex();
		TOKEN_TYPE getType();
		int getLineNum();
	};
}
