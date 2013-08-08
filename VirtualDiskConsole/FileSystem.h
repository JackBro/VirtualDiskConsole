#ifndef ZP_FILESYSTEM
#define ZP_FILESYSTEM

#include "ZPDependency.h"

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
		* @brief ���ܽڵ�����߷���
		*/
		void Accept( NodeVisitor* visitor );
		
		/**
		* @brief ����ʵ�����ļ���
		*/
		void BuildTestFileTree(void);

	private:
		Node* m_lp_root;		///>�ļ�ϵͳ���ڵ�	
	};

}//namespace FileSys

#endif //ZP_FILESYSTEM