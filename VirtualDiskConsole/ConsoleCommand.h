#ifndef ZP_CONSOLECOMMAND
#define ZP_CONSOLECOMMAND
#include "ZPDependency.h"
#include "Token.h"
#include "Node.h"

namespace CommandSys
{

class ConsoleCommand
{
public:
	ConsoleCommand(void);
	virtual ~ConsoleCommand(void);

	void SetCurrPath( const Util::String& curr_path ); 

	void SetParamToks( const Util::LinkListT<LexerSys::Token>& params );

	void AddPath( const Util::LinkListT<LexerSys::Token>& path );

	void SetPaths( const Util::LinkListT<Util::LinkListT<LexerSys::Token>>& paths );

	virtual void Execute( void ){} 

	Util::String GetResultOutput( void );

	Util::String GetCurrPath(void);

	virtual void DeleteThis(void){ delete this; }

protected:

	FileSys::Node* SearchCurrPathNode(void);

	FileSys::Node* SearchNodeByPathTokens( 
		const Util::LinkListT<LexerSys::Token>& path_toks );

protected: 
	Util::String	m_curr_path;													///>��ǰ·��
	Util::LinkListT<LexerSys::Token> m_curr_path_toks;				///>��ǰ·�������б�
	Util::LinkListT<LexerSys::Token> m_params;							///>�����б�
	Util::LinkListT<Util::LinkListT<LexerSys::Token>> m_paths;	///>·���б�
	Util::String m_result_output;													///>�������ַ���
};

}//namespace CommandSys

#endif//ZP_CONSOLECOMMAND