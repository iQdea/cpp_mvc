#pragma once
namespace ViewModel {
	class TaskComment {
	public:
		TaskComment(shared_ptr<DTO::TaskComment> item) {
			id = item->id;
			comment = item->comment;
		}

		string str() {
			stringstream ss;
			ss << "task-comment:" << id << "<-" << comment;
			return ss.str();
		}

		string id;
		string comment;
	};
}