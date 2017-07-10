#include "SourceCodeDelete.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"

namespace B
{
	SourceCodeDelete::SourceCodeDelete(Controller::Controller *pController) :SourceCodeBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	SourceCodeDelete::~SourceCodeDelete()
	{
	}

	void SourceCodeDelete::process_task()
	{

	}

	void SourceCodeDelete::background_process()
	{

	}
}