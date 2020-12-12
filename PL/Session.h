#pragma once
#include "BLL.h"
using namespace BLL;

namespace ViewModel {
	class Session {
	public:
		Session(DTO::Session& item) {
			id = item.id;
		}

		string str() {
			stringstream ss;
			ss << "session:" << id;
			return ss.str();
		}

		string id;
	};
}
