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

		virtual bool IsFile( void ) const { return true; }

		/**
		* @brief �����ļ������жϵ�ǰ�ļ��Ƿ�Ϊ�������ļ�
		* @retval true ��ǰ�ļ�Ϊ�������ļ�
		* @retval false ��ǰ�ļ�Ϊ�ı��ļ�
		*/
		virtual bool IsBinaryFile( void ) const;

		virtual int Copy( const void* data  , const int size );

		virtual int Read( const int offset , const int size , void* data  );

		virtual void ClearData( void );

		virtual int Size(void) const { return m_size; }

		virtual int CalcTotalSize(void){ return Size(); }

		virtual bool  Compare( const void* data , const int size  , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2    ) const;
		  
		virtual void DeleteThis(void){ delete this; } 

	private:
		bool m_binary_file;				///>�Ƿ�Ϊ�������ļ�
		unsigned char* m_data;		///>����
		int	 m_size;							///>���ݵĴ�С�����ֽڼƣ�
	};

	/**
	* @brief �жϵ�ǰ·�����ļ��Ƿ�Ϊ�ı��ļ�
	*/
	extern bool IsTextFilePath( const Util::String& path );

}//namespace FileSys

#endif // ZP_FILENODE