#include "BuildRule.h"

namespace DB {

	Define_Table_Constructor(BuildRule)
		Define_Table_Constructor_End()

		Define_Table_Destructor(BuildRule)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(BuildRule)
		Define_Table_Create_Function_Filter_Begin(define, BuildRule)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(source_code_id)
		Define_Table_Create_Function_Filter_Number(inner_id)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_String(auto_build)
		Define_Table_Create_Function_Filter_String(proxy_host_id)
		Define_Table_Create_Function_Filter_String(server_host_id)
		Define_Table_Create_Function_Filter_String(task_id)
		Define_Table_Create_Function_Filter_String(target_file_name)
		Define_Table_Create_Function_Filter_String(target_file_path)
		Define_Table_Create_Function_Filter_String(compile_tool_ins_id)
		Define_Table_Create_Function_Filter_String(output_directory_template)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(BuildRule)
		Define_Table_Query_Function_Body(define, BuildRule)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(BuildRule)
		Define_Table_Remove_Function_Body(define, BuildRule)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(BuildRule)
		Define_Table_Update_Function_Filter_Begin(define, BuildRule)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(source_code_id)
		Define_Table_Update_Function_Filter_Number(inner_id)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_String(auto_build)
		Define_Table_Update_Function_Filter_String(proxy_host_id)
		Define_Table_Update_Function_Filter_String(server_host_id)
		Define_Table_Update_Function_Filter_String(task_id)
		Define_Table_Update_Function_Filter_String(target_file_name)
		Define_Table_Update_Function_Filter_String(target_file_path)
		Define_Table_Update_Function_Filter_String(compile_tool_ins_id)
		Define_Table_Update_Function_Filter_String(output_directory_template)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(BuildRule)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(BuildRule)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(BuildRule)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(BuildRule)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(BuildRule)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(BuildRule)
		Define_Table_First_Function_Body(BuildRule)
		Define_Table_First_Function_End()

		Define_Table_All_Function(BuildRule)
		Define_Table_All_Function_Body(BuildRule)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(BuildRule)
		Define_Table_Exec_Function_Body(BuildRule)
		Define_Table_Exec_Function_End()
}