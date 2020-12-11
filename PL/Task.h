#pragma once
#include "IController.h"
#include <string>
using namespace std;

namespace Controllers {
	class Task : public IController {
	public:
		Task(shared_ptr<Context> context) : IController(context) {
		}
		void add(string title) {}
	};
}