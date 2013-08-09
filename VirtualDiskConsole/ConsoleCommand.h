#ifndef ZP_CONSOLECOMMAND
#define ZP_CONSOLECOMMAND
#include "ZPDependency.h"
#include "Token.h"
#include "Node.h"
#include "SearchPath.h"

namespace CommandSys
{

class ConsoleCommand
{
public:
	ConsoleCommand(void);
	virtual ~ConsoleCommand(void);

	void SetCurrPath( const Util::String& curr_path ); 

	void SetParamToks( const Util::LinkListT<LexerSys::Token>& params );

	void AddPath( const LexerSys::SearchPath& path );

	void SetPaths( const Util::LinkListT<LexerSys::SearchPath>& paths );

	virtual void Execute( void ){} 

	Util::String GetResultOutput( void );

	Util::String GetCurrPath(void);

	virtual void DeleteThis(void){ delete this; }

protected:

	FileSys::Node* SearchCurrPathNode(void);

	FileSys::Node* SearchNodeByPathTokens(  const LexerSys::SearchPath& path );

protected:  
	LexerSys::SearchPath m_curr_path;										///>��ǰ·��
	Util::LinkListT<LexerSys::Token> m_params;							///>�����б�
	Util::LinkListT<LexerSys::SearchPath> m_paths;					///>·���б�
	Util::String m_result_output;													///>�������ַ���
};

}//namespace CommandSys

#endif//ZP_CONSOLECOMMAND