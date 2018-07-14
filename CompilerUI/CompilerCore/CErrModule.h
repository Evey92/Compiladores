#pragma once
using namespace System;

namespace CompilerCore
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


		void AddError(ERROR_PHASE p, int lineNum, String^desc, String^ line);
		int ReturnNumError();
		cli::array<String^>^ ReturnErrorString();

		void Clear();
		void AddError(ERROR_PHASE p, int lineNum, String^desc, String^ line);
		int ReturnNumErrors();
		int ReturnMaxErrors();
		cli::array<String^>^ ReturnErrorString();


		CErrModule::CErrModule()
		{
			m_maxErrors = 30;
			m_numErrorsLex = 0;
			m_errors = gcnew cli::array<String^>(m_maxErrors);
		}
		CErrModule::~CErrModule() {}

		void CErrModule::Clear()
		{
			m_errors = gcnew cli::array<String ^>(m_maxErrors);
			m_numErrorsLex = 0;
		}

		void CErrModule::AddError(ERROR_PHASE p, int lineNum, String^desc, String^ line)
		{
			m_errors[m_numErrorsLex] = (desc + "at line " + lineNum + ": " + line);
			m_numErrorsLex++;
		}

		int CErrModule::ReturnNumErrors()
		{
			return m_numErrorsLex;
		}

		int CErrModule::ReturnMaxErrors()
		{
			return m_maxErrors;
		}

		cli::array<String^>^ CErrModule::ReturnErrorString()
		{
			return m_errors;
		}
	};
}