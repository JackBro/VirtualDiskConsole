#ifndef ZP_SEARCHPATH
#define ZP_SEARCHPATH

#include "ZPDependency.h"
#include "Token.h"

namespace LexerSys
{ 

	//·���ַ����ȵ��������
	const int PATH_LENGTH_LIMIT = 256;

	class SearchPath
	{
	public:

		/**
		* @brief Ĭ�Ϲ��캯��
		*/
		SearchPath(void);
		/**
		* @brief �������Ĺ��캯��
		* @param path Ҫ���õ�·���ַ���
		*/
		SearchPath( const Util::String path );
		/**
		* @brief �������캯��
		*/
		SearchPath( const SearchPath& path );
		/**
		* @brief ��������
		*/
		virtual ~SearchPath(void);

		/**
		* @brief ����·��
		* @param path ·���ַ���
		* @remark ������Ὣ·���ַ����ֽ�Ϊ�����ķ��š�
		*/
		void Path( const Util::String& path );

		/**
		* @brief ����·����
		*/
		Util::String Path( void ) const;

		/**
		* @brief �鿴·���Ƿ񳬹���������
		*/
		bool IsLengthOutOfLimit( void ) const;

		/**
		* @brief ����·���е��ļ�������
		*/
		bool GetFileNameToken( Token& tok );

		/**
		* @brief ����·�����е�ͨ���
		*/
		bool GetWildCardToken( Token& tok );
		/**
		* @brief �鿴��ǰ·���Ƿ�Ϊ��
		*/
		bool IsEmpty( void ) const;

		/**
		* @brief ���·��
		*/
		 void Clear( void );

		 /**
		 * @brief ����·������·��ĩβ
		 * @param path Ҫ���ӵ�·��
		 * @return ���ص�ǰ·������
		 */
		SearchPath& Append( const SearchPath& path );

		/**
		* @brief ��������λ��i���ķ���
		* @param i λ������
		* @return ����λ�õķ���
		*/
		Token& At( const int i );

		/**
		* @brief ��������λ��i���ķ���
		* @param i λ������
		* @return ����λ�õķ���
		*/
		const Token& At( const int i ) const;

		/**
		* @brief ��ǰ·���ķ�������
		* @return ��ǰ·���������ķ�����
		*/
		int TokenCount( void ) const;

		/**
		* @brief ������ǰ·���Ƿ�Ϊ����·��
		* @param toks ������·�������б�
		* @return �����Ƿ�Ϊ����·��
		*/
		 bool IsAbsolutePath( void ) const;

		 /**
		 * @brief ������·�������Ž��ʱ�ĵ�ǰ����
		 * @param ��ȡ�ĵ�ǰ����
		 * @return ��ȡ�Ƿ�ɹ�
		 * @retval true ��ȡ�ɹ�
		 * @retval false ��ȡʧ��
		 */
		bool CurrToken( Token& tok ) const;

		/**
		* @brief �Ƿ�����һ������
		*/
		bool HasNext(void) const;

		/**
		* @brief ����ǰ����λ���ƶ��������б���
		*/
		void MoveToFirstToken(void);

		/**
		* @brief ����ǰ����λ���ƶ�����һ������λ��
		*/
		void MoveToNextToken(void);

		/**
		* @brief ����ǰ����λ���ƶ������һ������λ��
		*/
		void MoveToLastToken(void);

		/**
		* @brief ��ֵ���������
		*/
		SearchPath& operator=( const SearchPath& rhs ); 

		/**
		* @brief ��ֵ���������
		*/
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