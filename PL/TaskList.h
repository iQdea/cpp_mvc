#pragma once
#include "IController.h"
#include <string>
using namespace std;

namespace Controllers {
	class TaskList : public IController {
	public:
		TaskList(shared_ptr<Context> context) : IController(context) {
		}
		// добавление задачи
		void add() {
			context->task = context->sprintService->addTask();
		}

		// ѕоиск задач по ID
		void findById(string taskId) {}

		// ѕоиск задач по времени создани€
		void findByCreatedAt(time_t from, time_t to) {}

		// ѕоиск задач по времени изменени€
		void findByModifiedAt(time_t from, time_t to) {}

		// ѕоиск задач, закрепленных за пользователем
		void findByAssignedTo(string userId) {}

		// ѕоиск задач, в которые пользователь вносил изменени€
		void findByModifiedBy(string userId) {}
	};
}