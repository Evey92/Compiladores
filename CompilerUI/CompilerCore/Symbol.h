#pragma once

using std::string;
namespace CompilerCore
{
	enum class SYMBOLCAT
	{
		UNDEFINED = 0,
		VAR_GLOBAL,
		VAR_LOCAL,
		PARAM,
		FUNC
	};

	enum class SYMBOLTYPE
	{
		UNDEFINED = 0,
		INT = 1,
		FLOAT = 2,
		STRING = 3
	};

	public  class Symbol
	{
	public:
		string m_name;
		SYMBOLCAT m_category;
		SYMBOLTYPE m_type;
		int m_dimension;
		//vector<m_type> valor;
		Symbol* localNode;
		string functionName;
		
		Symbol();
		~Symbol();
	};

	Symbol::Symbol()
	{
		Symbol* localNode = nullptr;
	}

}
