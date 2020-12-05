#pragma once
#include "Controller.h"
#include <string>
using namespace std;

namespace Controllers {
	class Task : public Controller {
	public:
		Task(shared_ptr<Context> context) : Controller(context) {
		}
		void add(string title) {}
	};
}