#include "SourceCode_Deploy.h"

namespace DB {

	Define_Table_Constructor(SourceCode_Deploy)
		Define_Table_Constructor_End()

		Define_Table_Destructor(SourceCode_Deploy)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(SourceCode_Deploy)
		Define_Table_Create_Function_Filter_Begin(define, SourceCode_Deploy)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(deployhostid)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(SourceCode_Deploy)
		Define_Table_Query_Function_Body(define, SourceCode_Deploy)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(SourceCode_Deploy)
		Define_Table_Remove_Function_Body(define, SourceCode_Deploy)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(SourceCode_Deploy)
		Define_Table_Update_Function_Filter_Begin(define, SourceCode_Deploy)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(deployhostid)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(SourceCode_Deploy)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(SourceCode_Deploy)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(SourceCode_Deploy)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(SourceCode_Deploy)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(SourceCode_Deploy)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(SourceCode_Deploy)
		Define_Table_First_Function_Body(SourceCode_Deploy)
		Define_Table_First_Function_End()

		Define_Table_All_Function(SourceCode_Deploy)
		Define_Table_All_Function_Body(SourceCode_Deploy)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(SourceCode_Deploy)
		Define_Table_Exec_Function_Body(SourceCode_Deploy)
		Define_Table_Exec_Function_End()
}