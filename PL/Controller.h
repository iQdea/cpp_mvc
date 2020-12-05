#pragma once
#include "Context.h"

namespace Controllers {
	using namespace BLL::DTO;

	class Controller {
	public:
		Controller(shared_ptr<Context> context) {
			this->context = context;
		}
	protected:
		shared_ptr<Context> context;
	};
}