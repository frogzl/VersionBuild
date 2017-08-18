#include "Host.h"

namespace DB {

	Define_Table_Constructor(Host)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Host)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Host)
		Define_Table_Create_Function_Filter_Begin(define, Host)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(name)
		Define_Table_Create_Function_Filter_String(ip)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Host)
		Define_Table_Query_Function_Body(define, Host)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Host)
		Define_Table_Remove_Function_Body(define, Host)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Host)
		Define_Table_Update_Function_Filter_Begin(define, Host)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(name)
		Define_Table_Update_Function_Filter_String(ip)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Host)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Host)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Host)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Host)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Host)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Host)
		Define_Table_First_Function_Body(Host)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Host)
		Define_Table_All_Function_Body(Host)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Host)
		Define_Table_Exec_Function_Body(Host)
		Define_Table_Exec_Function_End()
}