#include "stdafx.h"
#include "LexicoModule.h"

using namespace CompilerCore;



void LexicoModule::addToken(std::string lex, TOKEN_TYPE type, int line)
{
	CToken* p = new CToken(lex, type, line);
	m_Tokens.push_back(p);
}
