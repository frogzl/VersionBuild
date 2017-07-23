#include "BuildRule_Deploy.h"

namespace DB {

	Define_Table_Constructor(BuildRule_Deploy)
		Define_Table_Constructor_End()

		Define_Table_Destructor(BuildRule_Deploy)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(BuildRule_Deploy)
		Define_Table_Create_Function_Filter_Begin(define, BuildRule_Deploy)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(deployhostid)
		Define_Table_Create_Function_Filter_String(deploypath)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(BuildRule_Deploy)
		Define_Table_Query_Function_Body(define, BuildRule_Deploy)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(BuildRule_Deploy)
		Define_Table_Remove_Function_Body(define, BuildRule_Deploy)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(BuildRule_Deploy)
		Define_Table_Update_Function_Filter_Begin(define, BuildRule_Deploy)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(deployhostid)
		Define_Table_Update_Function_Filter_String(deploypath)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(BuildRule_Deploy)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(BuildRule_Deploy)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(BuildRule_Deploy)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(BuildRule_Deploy)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(BuildRule_Deploy)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(BuildRule_Deploy)
		Define_Table_First_Function_Body(BuildRule_Deploy)
		Define_Table_First_Function_End()

		Define_Table_All_Function(BuildRule_Deploy)
		Define_Table_All_Function_Body(BuildRule_Deploy)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(BuildRule_Deploy)
		Define_Table_Exec_Function_Body(BuildRule_Deploy)
		Define_Table_Exec_Function_End()
}