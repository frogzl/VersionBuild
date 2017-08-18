#include "Executable_Role.h"

namespace DB {

	Define_Table_Constructor(Executable_Role)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Executable_Role)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Executable_Role)
		Define_Table_Create_Function_Filter_Begin(define, Executable_Role)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(name)
		Define_Table_Create_Function_Filter_String(description)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Executable_Role)
		Define_Table_Query_Function_Body(define, Executable_Role)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Executable_Role)
		Define_Table_Remove_Function_Body(define, Executable_Role)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Executable_Role)
		Define_Table_Update_Function_Filter_Begin(define, Executable_Role)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(name)
		Define_Table_Update_Function_Filter_String(description)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Executable_Role)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Executable_Role)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Executable_Role)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Executable_Role)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Executable_Role)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Executable_Role)
		Define_Table_First_Function_Body(Executable_Role)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Executable_Role)
		Define_Table_All_Function_Body(Executable_Role)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Executable_Role)
		Define_Table_Exec_Function_Body(Executable_Role)
		Define_Table_Exec_Function_End()
}