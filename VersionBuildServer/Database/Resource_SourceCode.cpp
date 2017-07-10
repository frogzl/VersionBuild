#include "Resource_SourceCode.h"

namespace DB {

	Define_Table_Constructor(Resource_SourceCode)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Resource_SourceCode)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Resource_SourceCode)
		Define_Table_Create_Function_Filter_Begin(define, Resource_SourceCode)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(clone_url)
		Define_Table_Create_Function_Filter_String(repertoryname)
		Define_Table_Create_Function_Filter_String(branchname)
		Define_Table_Create_Function_Filter_String(name)
		Define_Table_Create_Function_Filter_String(discription)
		Define_Table_Create_Function_Filter_String(deployid)
		Define_Table_Create_Function_Filter_Number(startversion)
		Define_Table_Create_Function_Filter_Number(currentversion)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_Number(buildstate)
		Define_Table_Create_Function_Filter_Number(buildstatemask)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Resource_SourceCode)
		Define_Table_Query_Function_Body(define, Resource_SourceCode)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Resource_SourceCode)
		Define_Table_Remove_Function_Body(define, Resource_SourceCode)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Resource_SourceCode)
		Define_Table_Update_Function_Filter_Begin(define, Resource_SourceCode)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(clone_url)
		Define_Table_Update_Function_Filter_String(repertoryname)
		Define_Table_Update_Function_Filter_String(branchname)
		Define_Table_Update_Function_Filter_String(name)
		Define_Table_Update_Function_Filter_String(discription)
		Define_Table_Update_Function_Filter_String(deployid)
		Define_Table_Update_Function_Filter_Number(startversion)
		Define_Table_Update_Function_Filter_Number(currentversion)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_Number(buildstate)
		Define_Table_Update_Function_Filter_Number(buildstatemask)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Resource_SourceCode)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Resource_SourceCode)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Resource_SourceCode)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Resource_SourceCode)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Resource_SourceCode)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Resource_SourceCode)
		Define_Table_First_Function_Body(Resource_SourceCode)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Resource_SourceCode)
		Define_Table_All_Function_Body(Resource_SourceCode)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Resource_SourceCode)
		Define_Table_Exec_Function_Body(Resource_SourceCode)
		Define_Table_Exec_Function_End()
}