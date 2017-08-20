#include "Block.h"

namespace DB {

	Define_Table_Constructor(Block)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Block)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Block)
		Define_Table_Create_Function_Filter_Begin(define, Block)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(storage_id)
		Define_Table_Create_Function_Filter_BigNumber(start)
		Define_Table_Create_Function_Filter_BigNumber(end)
		Define_Table_Create_Function_Filter_String(proxy_host_id)
		Define_Table_Create_Function_Filter_String(server_host_id)
		Define_Table_Create_Function_Filter_String(path)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Block)
		Define_Table_Query_Function_Body(define, Block)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Block)
		Define_Table_Remove_Function_Body(define, Block)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Block)
		Define_Table_Update_Function_Filter_Begin(define, Block)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(storage_id)
		Define_Table_Update_Function_Filter_BigNumber(start)
		Define_Table_Update_Function_Filter_BigNumber(end)
		Define_Table_Update_Function_Filter_String(proxy_host_id)
		Define_Table_Update_Function_Filter_String(server_host_id)
		Define_Table_Update_Function_Filter_String(path)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Block)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Block)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Block)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Block)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Block)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Block)
		Define_Table_First_Function_Body(Block)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Block)
		Define_Table_All_Function_Body(Block)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Block)
		Define_Table_Exec_Function_Body(Block)
		Define_Table_Exec_Function_End()
}