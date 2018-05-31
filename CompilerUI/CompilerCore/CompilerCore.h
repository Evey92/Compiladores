// CompilerCore.h

#pragma once
#include "Windows.h"
#include "LexicoModule.h"
#include "CErrModule.h"

using namespace System;

namespace CompilerCore {

	public ref class Manager
	{
	public:
		//ctor/dtor			
		cli::array<String^>^ compile(String^);
		~Manager();

	private:
		LexicoModule* m_lex;
		CErrModule^ m_err;
	};

	cli::array<String^>^ Manager::compile(String^ src)
	{
		cli::array<String^>^ compilationDetails;
		compilationDetails = gcnew cli::array<String^>(1);
		compilationDetails[0] = gcnew String("Hola Mundo");
		//gc new no necesita delete, new si
		return compilationDetails;
	}

}



