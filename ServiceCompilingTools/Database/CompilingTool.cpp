#include "CompilingTool.h"

namespace DB {

	Define_Table_Constructor(CompilingTool)
		Define_Table_Constructor_End()

		Define_Table_Destructor(CompilingTool)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(CompilingTool)
		Define_Table_Create_Function_Filter_Begin(define, CompilingTool)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(name)
		Define_Table_Create_Function_Filter_String(discription)
		Define_Table_Create_Function_Filter_String(data_template)
		Define_Table_Create_Function_Filter_String(compile_cmd_template)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(CompilingTool)
		Define_Table_Query_Function_Body(define, CompilingTool)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(CompilingTool)
		Define_Table_Remove_Function_Body(define, CompilingTool)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(CompilingTool)
		Define_Table_Update_Function_Filter_Begin(define, CompilingTool)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(name)
		Define_Table_Update_Function_Filter_String(discription)
		Define_Table_Update_Function_Filter_String(data_template)
		Define_Table_Update_Function_Filter_String(compile_cmd_template)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(CompilingTool)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(CompilingTool)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(CompilingTool)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(CompilingTool)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(CompilingTool)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(CompilingTool)
		Define_Table_First_Function_Body(CompilingTool)
		Define_Table_First_Function_End()

		Define_Table_All_Function(CompilingTool)
		Define_Table_All_Function_Body(CompilingTool)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(CompilingTool)
		Define_Table_Exec_Function_Body(CompilingTool)
		Define_Table_Exec_Function_End()
}