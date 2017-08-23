#include "CompilingToolInstance.h"

namespace DB {

	Define_Table_Constructor(CompilingToolInstance)
		Define_Table_Constructor_End()

		Define_Table_Destructor(CompilingToolInstance)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(CompilingToolInstance)
		Define_Table_Create_Function_Filter_Begin(define, CompilingToolInstance)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(compiling_tool_id)
		Define_Table_Create_Function_Filter_String(data)
		Define_Table_Create_Function_Filter_String(compile_cmd)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(CompilingToolInstance)
		Define_Table_Query_Function_Body(define, CompilingToolInstance)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(CompilingToolInstance)
		Define_Table_Remove_Function_Body(define, CompilingToolInstance)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(CompilingToolInstance)
		Define_Table_Update_Function_Filter_Begin(define, CompilingToolInstance)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(compiling_tool_id)
		Define_Table_Update_Function_Filter_String(data)
		Define_Table_Update_Function_Filter_String(compile_cmd)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(CompilingToolInstance)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(CompilingToolInstance)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(CompilingToolInstance)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(CompilingToolInstance)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(CompilingToolInstance)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(CompilingToolInstance)
		Define_Table_First_Function_Body(CompilingToolInstance)
		Define_Table_First_Function_End()

		Define_Table_All_Function(CompilingToolInstance)
		Define_Table_All_Function_Body(CompilingToolInstance)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(CompilingToolInstance)
		Define_Table_Exec_Function_Body(CompilingToolInstance)
		Define_Table_Exec_Function_End()
}