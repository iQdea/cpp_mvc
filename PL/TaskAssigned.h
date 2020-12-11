#pragma once
namespace ViewModel {
	class TaskAssigned {
	public:
		TaskAssigned(shared_ptr<DTO::TaskAssigned> item) {
			id = item->id;
		}

		string str() {
			stringstream ss;
			ss << "task-assigned:" << id;
			return ss.str();
		}

		string id;
	};
}