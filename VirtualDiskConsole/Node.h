#ifndef ZP_NODE
#define ZP_NODE

#include "ZPDependency.h"


namespace FileSys
{
	class NodeVisitor;

	class Node
	{
	public: 

		enum NodeType{
			FILE_NODE = 1, 
			FOLDER_NODE
		};

		Node();
		virtual ~Node();

		/**
		* @brief ���ؽڵ�����
		* @return ��������
		*/
		Util::String Name() const { return m_name; }

		/**
		* @brief ���ýڵ�����
		* @param name �ڵ�����
		*/
		void Name( const Util::String& name ){ m_name = name; } 

		/**
		* @brief ��õ�ǰ�ڵ��·��ȫ��
		*/
		Util::String PathName(void) const;
		 
		/**
		* @brief ���ظ��ڵ�
		* @return ���ڵ�ָ��
		*/
		Node* Parent(void) const { return m_lp_parent; }

		/**
		* @brief ���ø��ڵ�ָ��
		* @param node ���ڵ�ָ��
		*/
		void Parent( Node* node ){ m_lp_parent = node; }

		/**
		* @brief �Ƿ�ΪҶ�ڵ�
		* @return ���ؽڵ��Ƿ�ΪҶ�ڵ�
		*/
		bool IsLeaf( void ) const { return ( m_child_nodes.Count() == 0 ); }

		/**
		* @brief �Ƿ�Ϊ���ڵ�
		* @return ���ؽڵ��Ƿ�Ϊ���ڵ�
		*/
		bool IsRoot( void ) const { return m_lp_parent == NULL; }

		/**
		* @brief �Ƿ�Ϊ�ļ�
		* @return �����Ƿ�Ϊ�ļ�
		*/
		virtual bool IsFile( void ) const { return false; }

		/**
		* @brief �Ƿ�Ϊ�ļ���
		* @return �����Ƿ�Ϊ�ļ���
		*/
		virtual bool IsFolder( void ) const { return false; }

		/**
		* @brief ����Ľڵ��Ƿ�Ϊ��ǰ�ڵ�����
		* @return �����Ƿ�Ϊ����
		* @retval true �����Ƚڵ�
		* @retval false �������Ƚڵ�
		*/
		virtual bool IsAncestor( Node* node );

		/**
		* @brief ���ҽڵ�
		* @param name Ҫ��������
		* @return ���ҵĽڵ�
		*/
		Node* FindNode( const Util::String& name  );

		Node* FindFileNodeBySpec( const Util::String& spec );

		/**
		* @brief �����ڵ�
		* @param name �ڵ�����
		* @param type �ڵ�����
		* @return ���ش����Ľڵ�
		*/
		Node* CreateNode( const Util::String& name , const NodeType type );

		/**
		* @brief ɾ��������ָ���Ľڵ�
		* @name Ҫɾ���Ľڵ�����
		* @return �����Ƿ�ɾ���ɹ�
		* @retval  true �ҵ��ڵ㲢ɾ���ɹ�
		* @retval  false	 δ�ҵ��ڵ�
		*/
		bool DeleteNode( const Util::String& name  );

		/**
		* @brief ɾ���ýڵ�������ָ�����͵Ľڵ�
		*/
		void DeleteNodeByType( const NodeType type );

		/**
		* @brief ���ٽ��������Ϣ
		*/
		virtual void Destroy( void ); 
		
		/**
		* @brief ɾ������
		*/
		virtual void DeleteThis(void){ delete this; }


		/**
		* @brief ���ַ����߷���
		* @param visitor ������
		*/
		virtual void Accept( NodeVisitor* visitor );

		virtual int Copy( const void* data  , const int size  ){ return 0; }

		virtual int Read( const int offset ,  const int size , void* data ){ return 0; } 

		virtual void ClearData( void ){ }

		/**
		* @brief �����ļ��Ƿ�Ϊ�������ļ�
		* @return �����ļ��Ƿ��Ƕ������ļ�
		* @retval true Ϊ�������ļ�
		* @retval false Ϊ�ı��ļ�
		*/
		virtual bool IsBinaryFile( void ) const { return false; }

		/**
		* @brief ���ؽڵ��������ݴ�С
		* @return �ڵ����������ݴ�С���ֽڼ�
		*/
		virtual int Size(void) const { return 0; }


		virtual int CalcTotalSize(void){ return 0; }


		virtual bool  Compare( const void* data , const int size , Util::VectorT<char>& diff1 , Util::VectorT<char>&diff2  ) const{ return false;}
	
		/**
		* @brief ��ȡ�ļ��б��ӡ�ַ���
		* @param output Ϊ���մ���ļ��б���ַ���
		* @param recursive ָʾ�Ƿ��ǵݹ���ʾ��Ŀ¼�����ļ�
		*/
		virtual void GetFileListOutputString(  Util::String& output , const bool recursive = false , const bool folder_only = false  ) const;
		  
	protected:
		Util::String m_name;								///>�ڵ����� 
		Node* m_lp_parent;										///>���ڵ�ָ��
		Util::LinkListT<Node*> m_child_nodes;	///>�ӽڵ��б�
	};

}//namespace FileSys

#endif//ZP_NODE