#include "Task.h"
using namespace DAL::Entities;
Task::Task(database db, string id, string title) : Entity(db, id) {
	coll = db["task"];
	this->title = title;
}
void Task::setTitle(string title) {
	this->title = title;
}
string Task::getTitle() {
	return this->title;
}
void Task::create() {
	auto result = coll.insert_one(document{}
		<< "title" << this->title
		<< finalize);
	id = result->inserted_id().get_oid().value.to_string();
}
void Task::remove() {
	coll.delete_one(current());
}
void Task::update() {
	coll.update_one(current(), document{}
		<< "$set" << open_document
		<< "title" << this->title
		<< close_document  << finalize);
}
