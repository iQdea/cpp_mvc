#pragma once
namespace ViewModel {
	class Task {
	public:
		Task(shared_ptr<DTO::Task> item) {
			id = item->id;
		}

		string str() {
			stringstream ss;
			ss << "task:" << id;
			return ss.str();
		}

		string id;
	};
}
