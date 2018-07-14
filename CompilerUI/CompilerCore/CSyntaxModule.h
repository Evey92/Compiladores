#pragma once
#include "LexicoModule.h"
#include "CErrModule.h"
#include "CSyntaxModule.h"
#include "SyntaxStateMachine.h"

namespace CompilerCore
{
	public class CSyntaxModule
	{
	private:
		LexicoModule * m_lex;
		Symbol* m_symTable;
		msclr::gcroot<CErrModule^> m_err;

	public:
		CSyntaxModule(LexicoModule* lexicMachine, CErrModule^ errorModule, Symbol* table);
		~CSyntaxModule();
		
		void SintaxStateMachine();
		void Clear();
	};

	
	CSyntaxModule::CSyntaxModule(LexicoModule* lexicMachine, CErrModule^ errorModule, Symbol* table)
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
		SyntaxStateMachine statemodule;
		m_lex->SetTokenIterator(0);
		statemodule.Run(m_lex, m_err, m_symTable);
	}

	void CSyntaxModule::Clear()
	{
		m_symTable->Clear();
	}

}



