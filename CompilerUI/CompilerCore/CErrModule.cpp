#include "stdafx.h"
#include "CErrModule.h"

using namespace compilerCore;

CErrModule::CErrModule()
{
	m_maxErrors = 15;
}
void CErrModule::AddError(ERROR_PHASE p, int lineNum, String^desc, String^ line)
{
	m_numErrorsLex++;
}
int CErrModule::ReturnNumError()
{
	return m_numErrorsLex;
}

cli::array<String^>^ CErrModule::ReturnErrorString()
{
	cli::array<String^>^ Errorstring;
	return Errorstring;
}
