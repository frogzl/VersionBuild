#include "BuildRule_Depend.h"

namespace DB {

	Define_Table_Constructor(BuildRule_Depend)
		Define_Table_Constructor_End()

		Define_Table_Destructor(BuildRule_Depend)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(BuildRule_Depend)
		Define_Table_Create_Function_Filter_Begin(define, BuildRule_Depend)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(build_rule_id)
		Define_Table_Create_Function_Filter_String(depend_source_code_id)
		Define_Table_Create_Function_Filter_String(depend_build_rule_id)
		Define_Table_Create_Function_Filter_String(depend_build_result_id)
		Define_Table_Create_Function_Filter_Number(depend_usage_mode)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(BuildRule_Depend)
		Define_Table_Query_Function_Body(define, BuildRule_Depend)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(BuildRule_Depend)
		Define_Table_Remove_Function_Body(define, BuildRule_Depend)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(BuildRule_Depend)
		Define_Table_Update_Function_Filter_Begin(define, BuildRule_Depend)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(build_rule_id)
		Define_Table_Update_Function_Filter_String(depend_source_code_id)
		Define_Table_Update_Function_Filter_String(depend_build_rule_id)
		Define_Table_Update_Function_Filter_String(depend_build_result_id)
		Define_Table_Update_Function_Filter_Number(depend_usage_mode)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(BuildRule_Depend)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(BuildRule_Depend)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(BuildRule_Depend)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(BuildRule_Depend)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(BuildRule_Depend)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(BuildRule_Depend)
		Define_Table_First_Function_Body(BuildRule_Depend)
		Define_Table_First_Function_End()

		Define_Table_All_Function(BuildRule_Depend)
		Define_Table_All_Function_Body(BuildRule_Depend)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(BuildRule_Depend)
		Define_Table_Exec_Function_Body(BuildRule_Depend)
		Define_Table_Exec_Function_End()
}