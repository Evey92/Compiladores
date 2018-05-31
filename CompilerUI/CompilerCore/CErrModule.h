#pragma once
using namespace System;
namespace compilerCore
{
	public enum class ERROR_PHASE
	{
		LEXICO,
		SINTACTICO,
		SEMANTICO
	};

	public ref class CErrModule
	{
	private:
		int m_maxErrors;
		int m_numErrorsLex;
		cli::array<String^>^ m_errors;
	public:
		CErrModule();
		~CErrModule();

		void  addError(ERROR_PHASE p, int lineNum, String^desc, String^ line);
	};
}

