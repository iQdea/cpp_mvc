#pragma once
#include "IController.h"
#include "ViewModels.h"

namespace Controllers {
	class ReportController : public IController {
	public:
		ReportController(SprintService* sprintService) : IController(sprintService) {}

		string daily() {
			ViewModel::Report report(*sprintService->getDailyReport());
			return report.json();
		}

		string sprint() {
			ViewModel::Report report(*sprintService->getSprintReport());
			return report.json();
		}

		string put(string id, string text) {
			ViewModel::Report report(*sprintService->putReport(id, text));
			return report.json();
		}

		string ready(string id) {
			ViewModel::Report report(*sprintService->markReportReady(id));
			return report.json();
		}
	};
}