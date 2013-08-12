#ifndef ZP_FILENODE
#define ZP_FILENODE

#include "Node.h"

namespace FileSys
{ 

	class FileNode : public Node
	{
	public:
		FileNode(void);
		virtual ~FileNode(void);

		/**
		* @brief �жϸýڵ��Ƿ�Ϊ�ļ�
		*/
		virtual bool IsFile( void ) const { return true; }

		/**
		* @brief �����ļ������жϵ�ǰ�ļ��Ƿ�Ϊ�������ļ�
		* @retval true ��ǰ�ļ�Ϊ�������ļ�
		* @retval false ��ǰ�ļ�Ϊ�ı��ļ�
		*/
		virtual bool IsBinaryFile( void ) const;

		/**
		* @brief ����������ݿ��������ļ�
		* @param data �����������ݻ�����ָ�룬�˻������ɸ��ļ��ڵ㸺���ͷ��ڴ�
		* @param size ���ݻ����������ݴ�С
		* @return ����ʵ�ʿ��������ݴ�С
		*/
		virtual int Copy( const void* data  , const DWORD size );

		/**
		* @brief ��ȡ����������ļ�����
		* @param offset ��ȡƫ��ֵ�����ֽڼƣ�
		* @param size Ҫ��ȡ���ݵĴ�С
		* @param data ��ȡ���ݴ�������ݻ�����ָ��
		* @return ʵ�ʶ�ȡ�����ݴ�С
		*/
		virtual int Read( const DWORD offset , const DWORD size , void* data  );

		/**
		* @brief ��սڵ��и���������
		*/
		virtual void ClearData( void );

		/**
		* @brief ���ļ��ڵ����ݵĴ�С
		* @return �����ļ��ڵ����ļ����ݵĴ�С
		*/
		virtual DWORD Size(void) const { return m_size; }

 
		virtual DWORD CalcTotalSize(void){ return Size(); }

		virtual bool  Compare( const void* data , const DWORD size  , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2    ) const;

		virtual bool  Compare( const HANDLE file , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2  ) const;
		  
		virtual void DeleteThis(void){ delete this; } 

	private:
		bool m_binary_file;				///>�Ƿ�Ϊ�������ļ�
		unsigned char* m_data;		///>����
		DWORD	 m_size;							///>���ݵĴ�С�����ֽڼƣ�
	};

	/**
	* @brief �жϵ�ǰ·�����ļ��Ƿ�Ϊ�ı��ļ�
	*/
	extern bool IsTextFilePath( const Util::String& path );

}//namespace FileSys

#endif // ZP_FILENODE