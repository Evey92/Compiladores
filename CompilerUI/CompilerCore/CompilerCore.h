#pragma once
#include "Windows.h"
#include "LexicoModule.h"
#include "CErrModule.h"
#include "CSyntaxModule.h"

using namespace System;

namespace CompilerCore {

	public ref class Manager
	{
	private:
		LexicoModule* m_lex;
		CErrModule^ m_err;
		CSyntaxModule* m_Syntax;

	public:
		Manager();
		~Manager();
		cli::array<String^>^ Compile(String^);

	
	};

	Manager::Manager()
	{
		m_err = gcnew CErrModule();
		m_lex = new LexicoModule(m_err);
		m_Syntax = new CSyntaxModule(m_lex);
	}

	Manager::~Manager()
	{
		delete m_lex;
	}

	cli::array<String^>^ Manager::Compile(String^ src)
	{
		m_err->Clear();
		m_lex->Clear();

		cli::array<String^>^ compilationDetails;
		cli::array<String^>^ errorDetails = m_err->ReturnErrorString();

		compilationDetails = gcnew cli::array<String^>(1);
		compilationDetails[0] = gcnew String("Hola Mundo");
		//gc new no necesita delete, new si
		return compilationDetails;
	}

}



