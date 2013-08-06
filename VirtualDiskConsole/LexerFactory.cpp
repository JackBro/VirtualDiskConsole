#include "LexerFactory.h"
#include "CmdLexer.h"
#include "PathLexer.h"

namespace Lexer_Sys
{
	 
	ILexer* Lexer_Sys::LexerFactory::CreateLexer( const LexerType type )
	{
		ILexer* lp_new_lexer = NULL;
		switch( type )
		{
		//�������������
		case LEXER_TYPE_COMMAND:
			lp_new_lexer = new CmdLexer;
			ZP_ASSERT( NULL != lp_new_lexer );
			break;
		//����·��������
		case LEXER_TYPE_PATH:
			lp_new_lexer = new PathLexer;
			ZP_ASSERT( NULL != lp_new_lexer );
			break;
		default:
			break;
		}
		return lp_new_lexer;
	}

}//namespace Lexer_Sys