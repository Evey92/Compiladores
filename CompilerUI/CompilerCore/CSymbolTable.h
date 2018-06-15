#pragma once
#include <string>
#include <map>
#include "Symbol.h"

using std::string;

namespace CompilerCore
{

	public class CSymbolTable
	{
	private:
		std::map<string, Symbol*> m_SymbolHash;
		std::map<string, Symbol*>::iterator hashIt;
	public:
		CSymbolTable();
		~CSymbolTable();
		bool AddSymbol(string sym, SYMBOLCAT cat, int dimension, SYMBOLTYPE symType, int lineNum, string funcName);
		bool SymbolExists(string sym);
		bool SymbolExists(string sym, SYMBOLCAT cat);
		SYMBOLTYPE GetSymbolType(string sym, SYMBOLCAT cat);
	};
	
	bool CSymbolTable::AddSymbol(string sym, SYMBOLCAT cat, int dimension, SYMBOLTYPE symType, int lineNum, string funcName)
	{
		if (SymbolExists(sym, cat))
		{
			if (m_SymbolHash.find(sym)->second->m_category != SYMBOLCAT::VAR_GLOBAL)
			{
				Symbol* m_pGlobal = new Symbol();
				Symbol* m_pLocal = new Symbol();
				m_pGlobal->localNode = m_pLocal;
				m_SymbolHash.insert(std::make_pair(sym, m_pGlobal));
								
				m_pLocal->m_name = sym;
				m_pLocal->m_category = cat;
				m_pLocal->m_dimension = dimension;
				m_pLocal->m_type = symType;


			}
		}
		else
		{
			Symbol* m_pGlobal = new Symbol();
			m_pGlobal->m_category = cat;
			m_pGlobal->m_dimension = dimension;
			m_pGlobal->m_name = sym;
			m_pGlobal->m_type = symType;

			m_SymbolHash.insert(std::make_pair(m_pGlobal->m_name, m_pGlobal));
			return true;
		}
	}

	bool CSymbolTable::SymbolExists(string sym)
	{
		hashIt = m_SymbolHash.find(sym);
		if (hashIt != m_SymbolHash.end())
			return true;
	}

	bool CSymbolTable::SymbolExists(string sym, SYMBOLCAT cat)
	{
		hashIt = m_SymbolHash.find(sym);
		if (hashIt->first == sym && hashIt->second->m_category==cat)
			return true;
	}

	SYMBOLTYPE CSymbolTable::GetSymbolType(string sym, SYMBOLCAT cat)
	{
		for (hashIt = m_SymbolHash.find(sym); hashIt != m_SymbolHash.end ; hashIt++)
		{
			if (hashIt->first == sym && hashIt->second->m_category == cat)
			{
				return hashIt->second->m_type;
			}
		}
	}
}
