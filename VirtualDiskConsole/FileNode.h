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

		virtual bool IsBinaryFile( void ) const { return m_binary_file; }

		virtual int Write( const void* data  , const int size );

		virtual int Read( const int offset , const int size , void* data  );

		virtual int Size(void) const { return m_size; }

		virtual bool  Compare( const Node* other_node , ZPUTIL::String& output)  const;

		virtual bool  Compare( const void* data , const int size , ZPUTIL::String& output  ) const;



		virtual void DeleteThis(void){ delete this; }

	protected:
		
		/**
		* @brief �жϴ���������Ƿ�Ϊ����������
		* @param data �������ݻ�����ָ��
		* @param size ���ݻ�����ʵ�����ݴ�С
		* @return �����Ƿ�Ϊ����������
		* @warning data�����ֶν�ֹ�����ָ�룬����ᴥ������
		*/
		bool IsBinaryFileData( const void* data , const int size ) const;

	private:
		bool m_binary_file;				///>�Ƿ�Ϊ�������ļ�
		unsigned char* m_data;		///>����
		int	 m_size;							///>���ݵĴ�С�����ֽڼƣ�
	};

}//namespace FileSys

#endif // ZP_FILENODE