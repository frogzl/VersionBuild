#include "SourceCode.h"

namespace DB {
	Define_Table_Constructor(SourceCode)
		Define_Table_Constructor_End()

		Define_Table_Destructor(SourceCode)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(SourceCode)
		Define_Table_Create_Function_Filter_Begin(define, SourceCode)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(name)
		Define_Table_Create_Function_Filter_String(discription)
		Define_Table_Create_Function_Filter_String(version_control_id)
		Define_Table_Create_Function_Filter_Number(start_version)
		Define_Table_Create_Function_Filter_Number(current_version)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_Number(build_state)
		Define_Table_Create_Function_Filter_Number(build_state_mask)
		Define_Table_Create_Function_Filter_Number(version)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(SourceCode)
		Define_Table_Query_Function_Body(define, SourceCode)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(SourceCode)
		Define_Table_Remove_Function_Body(define, SourceCode)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(SourceCode)
		Define_Table_Update_Function_Filter_Begin(define, SourceCode)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(name)
		Define_Table_Update_Function_Filter_String(discription)
		Define_Table_Update_Function_Filter_String(version_control_id)
		Define_Table_Update_Function_Filter_Number(start_version)
		Define_Table_Update_Function_Filter_Number(current_version)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_Number(build_state)
		Define_Table_Update_Function_Filter_Number(build_state_mask)
		Define_Table_Update_Function_Filter_Number(version)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(SourceCode)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(SourceCode)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(SourceCode)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(SourceCode)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(SourceCode)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(SourceCode)
		Define_Table_First_Function_Body(SourceCode)
		Define_Table_First_Function_End()

		Define_Table_All_Function(SourceCode)
		Define_Table_All_Function_Body(SourceCode)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(SourceCode)
		Define_Table_Exec_Function_Body(SourceCode)
		Define_Table_Exec_Function_End()
}