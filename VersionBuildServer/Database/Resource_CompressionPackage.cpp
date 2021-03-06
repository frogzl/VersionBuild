#include "Resource_CompressionPackage.h"

namespace DB {

	Define_Table_Constructor(Resource_CompressionPackage)
		Define_Table_Constructor_End()

		Define_Table_Destructor(Resource_CompressionPackage)
		Define_Table_Destructor_End()

		Define_Table_Create_Function(Resource_CompressionPackage)
		Define_Table_Create_Function_Filter_Begin(define, Resource_CompressionPackage)
		Define_Table_Create_Function_Filter_String(guid)
		Define_Table_Create_Function_Filter_String(name)
		Define_Table_Create_Function_Filter_String(discription)
		Define_Table_Create_Function_Filter_String(storageid)
		Define_Table_Create_Function_Filter_End()
		Define_Table_Create_Function_End()

		Define_Table_Query_Function(Resource_CompressionPackage)
		Define_Table_Query_Function_Body(define, Resource_CompressionPackage)
		Define_Table_Query_Function_End()

		Define_Table_Remove_Function(Resource_CompressionPackage)
		Define_Table_Remove_Function_Body(define, Resource_CompressionPackage)
		Define_Table_Remove_Function_End()


		Define_Table_Update_Function(Resource_CompressionPackage)
		Define_Table_Update_Function_Filter_Begin(define, Resource_CompressionPackage)
		Define_Table_Update_Function_Filter_String(guid)
		Define_Table_Update_Function_Filter_String(name)
		Define_Table_Update_Function_Filter_String(discription)
		Define_Table_Update_Function_Filter_String(storageid)
		Define_Table_Update_Function_Filter_End()
		Define_Table_Update_Function_End()


		Define_Table_Where_Function(Resource_CompressionPackage)
		Define_Table_Where_Function_Body()
		Define_Table_Where_Function_End()

		Define_Table_Where2_Function(Resource_CompressionPackage)
		Define_Table_Where2_Function_Body()
		Define_Table_Where2_Function_End()

		Define_Table_OrderBy_Function(Resource_CompressionPackage)
		Define_Table_OrderBy_Function_Body()
		Define_Table_OrderBy_Function_End()

		Define_Table_OrderBy2_Function(Resource_CompressionPackage)
		Define_Table_OrderBy2_Function_Body()
		Define_Table_OrderBy2_Function_End()

		Define_Table_End_Function(Resource_CompressionPackage)
		Define_Table_End_Function_Body()
		Define_Table_End_Function_End()

		Define_Table_First_Function(Resource_CompressionPackage)
		Define_Table_First_Function_Body(Resource_CompressionPackage)
		Define_Table_First_Function_End()

		Define_Table_All_Function(Resource_CompressionPackage)
		Define_Table_All_Function_Body(Resource_CompressionPackage)
		Define_Table_All_Function_End()

		Define_Table_Exec_Function(Resource_CompressionPackage)
		Define_Table_Exec_Function_Body(Resource_CompressionPackage)
		Define_Table_Exec_Function_End()
}