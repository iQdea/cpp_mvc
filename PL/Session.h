#pragma once
namespace ViewModel {
	class Session {
	public:
		Session(shared_ptr<DTO::Session> item) {
			number = item->number;
		}

		string str() {
			stringstream ss;
			ss << "session:" << number;
			return ss.str();
		}

		int number;
	};
}
