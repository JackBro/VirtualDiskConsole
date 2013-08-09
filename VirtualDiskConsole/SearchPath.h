#ifndef ZP_SEARCHPATH
#define ZP_SEARCHPATH

#include "ZPDependency.h"
#include "Token.h"

namespace LexerSys
{ 
	class SearchPath
	{
	public:
		SearchPath(void);
		SearchPath( const Util::String path );
		SearchPath( const SearchPath& path );
		virtual ~SearchPath(void);

		void Path( const Util::String& path );
		Util::String Path(void) const;
		bool GetFileNameToken( Token& tok );
		bool GetWildCardToken( Token& tok );
		bool IsEmpty(void) const;
		 void Clear(void);
		SearchPath& Append( const SearchPath& path );
		Token& At( const int i );
		const Token& At( const int i ) const;
		int TokenCount(void) const;
		/**
		* @brief ������ǰ·���Ƿ�Ϊ����·��
		* @param toks ������·�������б�
		* @return �����Ƿ�Ϊ����·��
		*/
		 bool IsAbsolutePath( void ) const;
		bool CurrToken( Token& tok ) const;
		bool HasNext(void) const;
		void MoveToFirstToken(void);
		void MoveToNextToken(void);
		void MoveToLastToken(void);
		SearchPath& operator=( const SearchPath& rhs ); 
		SearchPath& operator=( const Util::String& rhs );
	protected:

		/**
		* @brief ��·�����з��������Ų����봫��ķ��������� 
		*/
		void AnalysisPath( void ); 

	private:
		typedef Util::LinkListT<Token> TokenList;
		Util::String m_path;								///>·����
		TokenList::Iterator m_curr_tok;				///>��ǰ����
		TokenList m_path_toks;							///>·�����ֽ���γɵķ����б�
	}; 
}//namespace Util

#endif//ZP_SEARCHPATH