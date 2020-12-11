#pragma once
namespace ViewModel {
	class TaskStatus {
	public:
		TaskStatus(shared_ptr<DTO::TaskStatus> item) {
			id = item->id;
		}

		string str() {
			stringstream ss;
			ss << "task-status:" << id;
			return ss.str();
		}

		string id;
	};
}