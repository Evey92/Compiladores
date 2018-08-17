#pragma once
#include "LexicoModule.h"
#include "CErrModule.h"
#include "CSyntaxModule.h"
#include "SyntaxStateMachine.h"
#include "CSymbolTable.h"
#include "CSemanticModule.h"
#include "CLogicExpression.h"

namespace CompilerCore
{
	public class CSyntaxModule
	{
	private:
		LexicoModule * m_lex;
		CSymbolTable* m_symTable;
		CSemanticModule* m_semantModule;
		msclr::gcroot<CErrModule^> m_err;

	public:
		CSyntaxModule(LexicoModule* lexicMachine, CErrModule^ errorModule, CSymbolTable* table);
		~CSyntaxModule();
		
		void SintaxStateMachine();
		void Clear();
	};

	
	CSyntaxModule::CSyntaxModule(LexicoModule* lexicMachine, CErrModule^ errorModule, CSymbolTable* table)
	{
		m_err = errorModule;
		m_lex= lexicMachine;
		m_symTable = table;
	}

	CSyntaxModule::~CSyntaxModule()
	{

	}

	void CSyntaxModule::SintaxStateMachine()
	{
		SyntaxStateMachine stateModule;
		m_lex->SetTokenIterator(0);
		statemodule.Run(m_lex, m_err, m_symTable);

		if (!statemodule.m_ExpPol.empty())
		{
			for (PolishExpression polExp; : m_ExpPol)
			{
				CLogicExpression* logExp = new CLogicExpression(polExp);
				m_semantModule->processingExpression.push_back(logExp);
			}

		}
	}

	void CSyntaxModule::Clear()
	{
		m_symTable->Clear();
	}

}



