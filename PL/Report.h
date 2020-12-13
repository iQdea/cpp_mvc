#pragma once
#include "BLL.h"
using namespace BLL;

namespace ViewModel {
	class Report {
	public:
		Report(DTO::Report& item) {
			id = item.id;
			text = item.text;
			createdAt = item.createdAt;
			lastModifiedAt = item.lastModifiedAt;
			status = (int)item.status;
			type = (int)item.type;
		}

		string json() {
			stringstream res;
			res << "{"
				<< "\"entityType\":\"report\","
				<< "\"id\":\"" << id << "\","
				<< "\"createdAt\":" << createdAt << ","
				<< "\"lastModifiedAt\":" << lastModifiedAt << ","
				<< "\"status\":" << status << ","
				<< "\"type\":" << type << ","
				<< "\"text\":\"" << text << "\""
				<< "}";
			return res.str();
		}

		string id;
		string text;
		int type;
		int status;
		time_t createdAt;
		time_t lastModifiedAt;
	};
}
