#ifndef ZP_FILESYSTEM
#define ZP_FILESYSTEM

#include "ZPDependency.h"

#define FILESYSTEM_CAPACITY  (1<<30)

namespace FileSys
{
	class Node;
	class NodeVisitor;

	class FileSystem : public Util::SingletonT<FileSystem>
	{
	public:
		FileSystem(void);
		virtual ~FileSystem(void);

		/**
		* @brief ��ȡ�ļ�ϵͳ���ڵ�
		* @return ���ڵ�
		*/
		Node* Root(void) const { return m_lp_root; }

		/**
		* @brief �����ļ�ϵͳ���ܹ�ʹ���˶����ڴ�(���ֽڼ�)
		*/
		DWORD TotalSize(void);

		/**
		* @brief �����ļ�ϵͳ���������
		*/
		DWORD Capacity( void ) const;

		/**
		* @brief �鿴���̿ռ��Ƿ��㹻����size���ֽ�
		*/
		bool HasEnoughSpace( const DWORD size );

		/**
		* @brief ���ܽڵ�����߷���
		*/
		void Accept( NodeVisitor* visitor );
		
		/**
		* @brief ����ʵ�����ļ���
		*/
		void BuildTestFileTree(void);

	private:
		Node* m_lp_root;		///>�ļ�ϵͳ���ڵ�	
		int m_capacity;			///>�ļ�ϵͳ�������
	};

}//namespace FileSys

#endif //ZP_FILESYSTEM