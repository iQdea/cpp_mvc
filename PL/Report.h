#pragma once
#include "BLL.h"
using namespace BLL;

namespace ViewModel {
	class Report {
	public:
		Report(DTO::Report& item) {
			id = item.id;
		}

		string str() {
			stringstream ss;
			ss << "report:" << id;
			return ss.str();
		}

		string id;
	};
}
