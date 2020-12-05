#pragma once
#include "Controller.h"
#include <string>
using namespace std;

namespace Controllers {
	class TaskList : public Controller {
	public:
		TaskList(shared_ptr<Context> context) : Controller(context) {
		}
		// ���������� ������
		void add() {
			context->task = context->sprintService->addTask();
		}

		// ����� ����� �� ID
		void findById(string taskId) {}

		// ����� ����� �� ������� ��������
		void findByCreatedAt(time_t from, time_t to) {}

		// ����� ����� �� ������� ���������
		void findByModifiedAt(time_t from, time_t to) {}

		// ����� �����, ������������ �� �������������
		void findByAssignedTo(string userId) {}

		// ����� �����, � ������� ������������ ������ ���������
		void findByModifiedBy(string userId) {}
	};
}