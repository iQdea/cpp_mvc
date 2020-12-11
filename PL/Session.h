#pragma once
namespace ViewModel {
	class Session {
	public:
		Session(shared_ptr<DTO::Session> item) {
			id = item->id;
		}

		string str() {
			stringstream ss;
			ss << "session:" << id;
			return ss.str();
		}

		string id;
	};
}
