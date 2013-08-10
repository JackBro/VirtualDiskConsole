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

	/**
	* @brief ���õ�ǰ·��
	* @param curr_path ��ǰ·���ַ���
	*/
	void SetCurrPath( const Util::String& curr_path ); 

	/**
	* @brief ���õ�ǰ�����û�������Ĳ����б�
	* @param params �û�����Ĳ����б�
	*/
	void SetParamToks( const Util::LinkListT<LexerSys::Token>& params );

	/**
	* @brief ��·�����������·���б�
	* @param path Ҫ�����·��
	*/
	void AddPath( const LexerSys::SearchPath& path );

	/**
	* @brief ���õ�ǰ�����·���б�
	* @param paths Ҫ���õ�·���б�
	*/
	void SetPaths( const Util::LinkListT<LexerSys::SearchPath>& paths );

	/**
	* @brief �ж��û������·�����Ƿ��г����޶����ȵ�·��
	*/
	bool IsPathLengthOutOfLimit(void) const;

	/**
	* @brief ִ������
	* @remark ��������д�ú���
	*/
	virtual void Execute( void ){} 

	/**
	* @brief ��ý�����
	*/
	Util::String GetResultOutput( void );

	/**
	* @brief ��õ�ǰ·���ַ���
	*/
	Util::String GetCurrPath(void);

	virtual void DeleteThis(void){ delete this; }

protected:

	/**
	* @brief ���ݵ�ǰ·�������ļ�ϵͳ�ж�Ӧ���ļ��нڵ�
	* @return ָ���ҵ��ĵ�ǰ·���ڵ�ָ��
	*/
	FileSys::Node* SearchCurrPathNode(void);

	/**
	* @brief ���ָ��·�����ļ�ϵͳ�ڵ�
	* @return ָ���ҵ�·���ڵ��ָ��
	* @retval NULL ����ʧ�ܣ��ļ�ϵͳ��û�и�·������ʾ�Ľڵ�
	* @retval not NULL ���ҳɹ�
	*/
	FileSys::Node* SearchNodeByPath(  const LexerSys::SearchPath& path );

protected:  
	LexerSys::SearchPath m_curr_path;										///>��ǰ·��
	Util::LinkListT<LexerSys::Token> m_params;							///>�����б�
	Util::LinkListT<LexerSys::SearchPath> m_paths;					///>·���б�
	Util::String m_result_output;													///>�������ַ���
};

}//namespace CommandSys

#endif//ZP_CONSOLECOMMAND