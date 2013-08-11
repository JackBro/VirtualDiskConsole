#include "CopyCmd.h"
#include "FileSystem.h"


namespace CommandSys
{
	 
CopyCmd::CopyCmd( void )
{

}
 
CopyCmd::~CopyCmd( void )
{

}

void CommandSys::CopyCmd::Execute( void )
{
	if( IsPathLengthOutOfLimit() )
	{
		m_result_output = "·�������ܳ���256���ַ�";
		return;
	}

	if( m_params.Count() > 0 )
	{
		m_result_output = "���֧�ֲ���";
		return;
	}
	 
	if( m_paths.Count() != 2 )
	{
		m_result_output = "�����﷨����ȷ";
		return;
	}
	 
	LexerSys::SearchPath src_path = m_paths.At(0);
	LexerSys::SearchPath dst_path = m_paths.At(1);

	//����Ŀ��·���Ƿ���һ���ļ���
	BOOL src_path_is_folder = PathIsDirectory( src_path.Path().Ptr() ); 

	Util::String src_path_origin = src_path.Path();
	Util::String final_src_path = src_path_origin;

	Util::String dst_path_origin = dst_path.Path();
	if( !dst_path.IsAbsolutePath() )
	{
		dst_path_origin = m_curr_path.Path() + dst_path.Path();
	}
	Util::String final_dst_path = dst_path_origin;

	FileSys::Node* lp_search_node = SearchNodeByPath( dst_path );

	if( TRUE == src_path_is_folder )
	{
		//δ�ҵ�Ŀ���ļ��н��
		if( lp_search_node == NULL )
		{
			m_result_output = "������Ŀ���ļ��в�����";
			return;
		}else{
			//�ҵ�Ŀ��ڵ㵫����һ���ļ�
			if( lp_search_node->IsFile() )
			{
				m_result_output = "���ڿ���Դ·��ָ���ļ��У�����Ŀ��·���������ļ���";
				return;
			} //if( lp_search_node->IsFile() )
		}  
	}else{//��Ϊ���ļ����� 

		//�ص������ļ���
		final_src_path = src_path_origin.SubString( 0 , 
			src_path_origin.Length() - ( src_path_origin.Length() - src_path_origin.FindLastOf('\\') ) );
	}
	 

	WIN32_FIND_DATA find_data;
	memset( &find_data , 0 , sizeof(find_data) );
	HANDLE handle_findfile = FindFirstFile( src_path.Path().Ptr() , &find_data );
	if( INVALID_HANDLE_VALUE == handle_findfile )
	{
		m_result_output = "���ش���·����������";
		return;
	}  

	//���ұ��ش��̵�·����ָ�����ļ������ļ�·�������б�
	Util::LinkListT<Util::String>  copy_src_paths; 
	Util::LinkListT<Util::String>  copy_src_filenames;
	do{
		if( find_data.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE )
		{
			copy_src_filenames.PushBack( find_data.cFileName );
			copy_src_paths.PushBack( final_src_path + "\\" + find_data.cFileName );  
		}
	} while( FindNextFile( handle_findfile , &find_data ));

	FindClose( handle_findfile );
	handle_findfile = NULL;
	  
	Util::LinkListT<FileSys::Node*> dst_file_nodes;
	if( lp_search_node )
	{
		if( lp_search_node->IsFile() )
		{
			dst_file_nodes.PushBack( lp_search_node );
		}else{//��Ϊ�ļ���,���贴���ļ����
			Util::LinkListT<Util::String>::Iterator it = copy_src_filenames.Begin();
			while( it != copy_src_filenames.End() )
			{
				FileSys::Node* lp_new_node = lp_search_node->CreateNode( *it , FileSys::Node::FILE_NODE );
				lp_new_node->ClearData();
				dst_file_nodes.PushBack( lp_new_node );
				it.Next();
			}
		}
	}else{//��Ŀ��·����㲻����

		//������Ŀ���ļ����ϼ��ļ���
		final_dst_path = dst_path_origin.SubString( 0 , 
			dst_path_origin.Length() - ( dst_path_origin.Length() - dst_path_origin.FindLastOf('\\') ) );

		lp_search_node = SearchNodeByPath( final_dst_path );

		if( NULL == lp_search_node )
		{
			m_result_output = "������Ŀ��·���ļ��в�����!";
			return;
		}

		 int j = dst_path_origin.FindLastOf('\\');
		Util::String dst_filename = dst_path_origin.SubString(  j+1  , dst_path_origin.Length()-j-1 );
		dst_filename.Trim();
		if( dst_filename.IsEmpty() )
		{
			m_result_output = "������Ŀ��·���ļ��в�����!";
			return;
		}

		FileSys::Node* lp_new_node = lp_search_node->CreateNode( dst_filename , FileSys::Node::FILE_NODE );
		dst_file_nodes.PushBack( lp_new_node );
	}
	 

	//��һ�����ļ�
	Util::LinkListT<Util::String>::Iterator path_it = copy_src_paths.Begin();
	Util::LinkListT<FileSys::Node*>::Iterator dst_it = dst_file_nodes.Begin();
	Util::StackT<FileSys::Node*> uncopy_files;

	//ʵ�ʿ����ļ�������
	int copy_count = 0;
	while( 
		dst_it != dst_file_nodes.End() &&
		path_it != copy_src_paths.End() 
		)
	{

		HANDLE file = CreateFile( (*path_it).Ptr() , GENERIC_READ , 0 , NULL , OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL, NULL );

		//���ļ���ʧ��
		if( INVALID_HANDLE_VALUE == file )
		{
			uncopy_files.Push( *dst_it );
			m_result_output.Append( Util::StringFormat("�ļ�\"%s\"��ʧ��! \n", (*path_it).Ptr() ) );
			dst_it.Next();
			path_it.Next();
			continue;
		}

		m_result_output.Append( *path_it );
		m_result_output.Append('\n');  
		 
		LARGE_INTEGER src_file_size;  
		 
		if( TRUE == GetFileSizeEx( file , &src_file_size ) )
		{

			if( 0 != src_file_size.HighPart )
			{ 
				m_result_output.Append( "�ļ������ļ�ϵͳ��֧��!\n" );

				uncopy_files.Push( *dst_it );
				CloseHandle( file );
				file = NULL; 
				dst_it.Next();
				path_it.Next();
				continue;
			} 

			//�鿴��ǰ�ļ�ϵͳ�Ƿ����㹻�ռ����ɸ��ļ�
			if( ! FileSys::FileSystem::GetInstance()->HasEnoughSpace( src_file_size.LowPart ) )
			{
				m_result_output.Append("û���㹻�Ŀռ����ɸ��ļ���");
				m_result_output.Append(*path_it);
				m_result_output.Append('\n');

				uncopy_files.Push( *dst_it );
				CloseHandle( file );
				file = NULL; 
				dst_it.Next();
				path_it.Next();
				continue;
			}

			DWORD bytes_read = 0;
			char* lp_read_buf = NULL;

			//������Ļ���������FileNode�ͷ�
			ZP_SAFE_NEW_BUFFER( lp_read_buf , char , src_file_size.LowPart );

			ReadFile( file , lp_read_buf , src_file_size.LowPart ,  &bytes_read , NULL );

			(*dst_it)->Copy( lp_read_buf , bytes_read );
			 
			lp_read_buf = NULL;
		}else{
			m_result_output.Append( "��ȡԴ�����ļ���Сʧ��!\n" );

			uncopy_files.Push( *dst_it );
			CloseHandle( file );
			file = NULL;
			dst_it.Next();
			path_it.Next();
			continue;
		}

		CloseHandle( file );
		file = NULL;

		copy_count++;
		 
		dst_it.Next();
		path_it.Next();
	}

	m_result_output.Append( Util::StringFormat( "�ܹ�������%d���ļ�\n", 
		copy_count ) ); 
	copy_src_paths.Clear(); 


	//�������ʧ�ܵ��ļ�
	while( uncopy_files.Size() )
	{
		FileSys::Node* lp_uncopy_node = uncopy_files.Front();
		if( lp_uncopy_node->Parent() )
		{
			lp_uncopy_node->Parent()->DeleteNode( lp_uncopy_node->Name() );
			lp_uncopy_node = NULL;
		}
		uncopy_files.Pop();
	}
}


}//namespace CommandSys