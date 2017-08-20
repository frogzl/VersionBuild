#include "Storage.h"

namespace DB {

	Define_Table_Constructor(Storage)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Storage)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Storage)
		Define_Table_Create_Function_Filter_Begin(define, Storage)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(file_name)
		Define_Table_Create_Function_Filter_BigNumber(size)
		Define_Table_Create_Function_Filter_Number(status)
		Define_Table_Create_Function_Filter_Number(version)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Storage)
		Define_Table_Query_Function_Body(define, Storage)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Storage)
		Define_Table_Remove_Function_Body(define, Storage)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Storage)
		Define_Table_Update_Function_Filter_Begin(define, Storage)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(file_name)
		Define_Table_Update_Function_Filter_BigNumber(size)
		Define_Table_Update_Function_Filter_Number(status)
		Define_Table_Update_Function_Filter_Number(version)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Storage)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Storage)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Storage)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Storage)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Storage)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Storage)
		Define_Table_First_Function_Body(Storage)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Storage)
		Define_Table_All_Function_Body(Storage)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Storage)
		Define_Table_Exec_Function_Body(Storage)
		Define_Table_Exec_Function_End()
}