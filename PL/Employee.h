#pragma once
namespace ViewModel {
	class Employee {
	public:
		Employee(shared_ptr<DTO::Employee> item) {
			id = item->id;
		}

		string str() {
			stringstream ss;
			ss << "employee:" << id;
			return ss.str();
		}

		string id;
	};
}
