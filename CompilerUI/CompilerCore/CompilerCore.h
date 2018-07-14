#pragma once
#include "Windows.h"
#include "LexicoModule.h"
#include "CErrModule.h"
#include "CSyntaxModule.h"
#include "CSymbolTable.h"

using namespace System;

namespace CompilerCore {

	public ref class Manager
	{
	private:
		LexicoModule* m_lex;
		CErrModule^ m_err;
		CSymbolTable* m_symbol;
		CSyntaxModule* m_syntax;

	public:
		Manager();
		~Manager();
		cli::array<String^>^ Compile(String^);

	
	};

	Manager::Manager()
	{
		m_err = gcnew CErrModule();
		m_lex = new LexicoModule(m_err);
		m_symbol = new CSymbolTable();
		m_syntax = new CSyntaxModule(m_lex, m_err, m_symbol);
	}

	Manager::~Manager()
	{
		delete m_lex;
		delete m_symbol;
		delete m_syntax;
	}

	cli::array<String^>^ Manager::Compile(String^ src)
	{
		m_err->Clear();
		m_lex->Clear();
		m_syntax->Clear();

		cli::array<String^>^ compilationDetails;
		
		m_lex->ParseSourceCode((const char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(src).ToPointer());
		
		cli::array<String^>^ errorDetails = m_err->ReturnErrorString();

		compilationDetails = gcnew cli::array<String^>(m_lex->GetTotalTokens() + m_err->ReturnNumErrors()+1);
		for (int i = 0; i < m_err->ReturnNumErrors(); ++i)
		{
			compilationDetails[i] = errorDetails[i];
		}

		compilationDetails[m_err->ReturnNumErrors()] = "(V)(°,,,,°)(V)";
		
		for (int i = m_err->ReturnNumErrors() + 1; i < (m_lex->GetTotalTokens + m_err->ReturnNumErrors() + 1); ++i)
		{
			std::string a;
			const CToken* t = m_lex->GetNextToken();
			a = t->GetLex() + " " + t->GetType();
			compilationDetails[i] = gcnew String(a.c_str());
		}

		//Aquí deberia ir la parte de la maquina de estados del análisis sintáctico.

		return compilationDetails;
	}

}



