#include "Task_Instance.h"

namespace DB {

	Define_Table_Constructor(Task_Instance)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Task_Instance)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Task_Instance)
		Define_Table_Create_Function_Filter_Begin(define, Task_Instance)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(plugin_task_id)
		Define_Table_Create_Function_Filter_String(plugin_deploy_id)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_String(status_description)
		Define_Table_Create_Function_Filter_String(data)
		Define_Table_Create_Function_Filter_String(processed_data)
		Define_Table_Create_Function_Filter_String(finish_url)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Task_Instance)
		Define_Table_Query_Function_Body(define, Task_Instance)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Task_Instance)
		Define_Table_Remove_Function_Body(define, Task_Instance)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Task_Instance)
		Define_Table_Update_Function_Filter_Begin(define, Task_Instance)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(plugin_task_id)
		Define_Table_Update_Function_Filter_String(plugin_deploy_id)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_String(status_description)
		Define_Table_Update_Function_Filter_String(data)
		Define_Table_Update_Function_Filter_String(processed_data)
		Define_Table_Update_Function_Filter_String(finish_url)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Task_Instance)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Task_Instance)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Task_Instance)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Task_Instance)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Task_Instance)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Task_Instance)
		Define_Table_First_Function_Body(Task_Instance)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Task_Instance)
		Define_Table_All_Function_Body(Task_Instance)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Task_Instance)
		Define_Table_Exec_Function_Body(Task_Instance)
		Define_Table_Exec_Function_End()
}