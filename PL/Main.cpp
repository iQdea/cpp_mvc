#include "DAL.h"
#include "BLL.h"
#include <iostream>
#include "SimplePocoHandler.h"
#include "ControllerList.h"

using namespace std;

string url = "mongodb+srv://qdea:qdea12345@cluster0.oeakp.mongodb.net/sprint?retryWrites=true&w=majority";

int main() {
	DAL::Mongo::RepositoryList repositoryList(url);
	BLL::SprintService sprintService(&repositoryList);
	ControllerList controllerList(&sprintService);
	SimplePocoHandler handler("192.168.0.95", 5672);
	AMQP::Connection connection(&handler, AMQP::Login("qdea", "qdea12345"), "/");
	AMQP::Channel channel(&connection);

	channel.setQos(1);
	channel.declareQueue("rpc_queue");
	channel.consume("").onReceived(
		[&channel, &controllerList](const AMQP::Message& message,
			uint64_t deliveryTag,
			bool redelivered)
		{
			string request(message.body(), message.bodySize());
			cout << " [x] Received " << request << endl;

			string response = controllerList.route(request);
			AMQP::Envelope env(response.c_str(), response.length());

			channel.publish("", message.replyTo(), env);
			channel.ack(deliveryTag);
		});

	cout << " [*] Waiting for messages. To exit press CTRL-C\n";
	handler.loop();

	return 0;
}