#include "BuildResult.h"

namespace DB {

	Define_Table_Constructor(BuildResult)
		Define_Table_Constructor_End()

		Define_Table_Destructor(BuildResult)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(BuildResult)
		Define_Table_Create_Function_Filter_Begin(define, BuildResult)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(buildruleid)
		Define_Table_Create_Function_Filter_Number(version)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_String(log)
		Define_Table_Create_Function_Filter_String(storageid)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(BuildResult)
		Define_Table_Query_Function_Body(define, BuildResult)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(BuildResult)
		Define_Table_Remove_Function_Body(define, BuildResult)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(BuildResult)
		Define_Table_Update_Function_Filter_Begin(define, BuildResult)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(buildruleid)
		Define_Table_Update_Function_Filter_Number(version)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_String(log)
		Define_Table_Update_Function_Filter_String(storageid)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(BuildResult)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(BuildResult)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(BuildResult)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(BuildResult)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(BuildResult)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(BuildResult)
		Define_Table_First_Function_Body(BuildResult)
		Define_Table_First_Function_End()

		Define_Table_All_Function(BuildResult)
		Define_Table_All_Function_Body(BuildResult)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(BuildResult)
		Define_Table_Exec_Function_Body(BuildResult)
		Define_Table_Exec_Function_End()
}