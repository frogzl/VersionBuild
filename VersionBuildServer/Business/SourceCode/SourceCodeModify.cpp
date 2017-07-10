#include "SourceCodeModify.h"
#include "../../Exception/HttpRequestException.h"
#include "../../SystemConfig.h"

namespace B
{
	SourceCodeModify::SourceCodeModify(Controller::Controller *pController) :SourceCodeBusiness(pController)
	{
		if (!is_input_data_ready())
			throw HttpRequestException(HTTP_INTERNAL, "1", "read request data failed!");
	}

	SourceCodeModify::~SourceCodeModify()
	{
	}

	void SourceCodeModify::process_task()
	{

	}

	void SourceCodeModify::background_process()
	{

	}
}