#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace CompilerCore
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
		int m_lineNum;
		std::map<int, std::string> m_tokenMap;

	public:
		CToken(std::string lex, TOKEN_TYPE t, int lineN);
		~CToken();
		const string GetLex() const;
		const string GetType() const;
		
	};

	CToken::CToken(std::string lex, TOKEN_TYPE t, int lineN)
	{
		m_lexema = lex;
		m_type = t;
		m_lineNum = lineN;
		m_tokenMap.clear();
		m_tokenMap = {
		{ 0, "UNDEFINED" },
		{ 1, "ID" },
		{ 2, "INT" },
		{ 3, "FLOAT" },
		{ 4, "STRING" },
		{ 5, "KEYWORD" },
		{ 6, "RELATIONAL OPERATOR" },
		{ 7, "ARITHMETIC OPERATOR" },
		{ 8, "LOGICAL OPERATOR" },
		{ 9, "NEGATION OPERATOR" },
		{ 10, "SEPARATOR" },
		{ 11, "ASIGN" },
		{ 12, "DIMESIONS" },
		{ 13, "GROUPING" },
		};
	}
	CToken::~CToken()
	{

	}
	const std::string CToken::GetLex() const
	{
		return m_lexema;
	}
	const std::string CToken::GetType() const
	{
		return m_tokenMap.find((int)m_type)->second;
	}
}
