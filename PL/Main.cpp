#include "DAL.h"
#include "BLL.h"
#include <iostream>
// #include "UserList.h"
// #include "User.h"
// #include "Task.h"
#include "Context.h"
#include "SimplePocoHandler.h"
#include "ControllerList.h"

// https://github.com/erlang/otp/releases/download/OTP-23.1.5/otp_win64_23.1.5.exe
// https://github.com/Microsoft/vcpkg
// https://github.com/rabbitmq/rabbitmq-server/releases/download/v3.8.9/rabbitmq-server-windows-3.8.9.zip

using namespace std;
using namespace DAL;
using namespace BLL;

const string employerName[7] = { 
	"Steve Mathews", "Mark Smith", "Ann Philip", "Julie Ponds", "Michael Lans", "Susan Boyle", 
	"Sophie Cyrus" 
};

int main()
{
	string url = "mongodb+srv://qdea:qdea12345@cluster0.oeakp.mongodb.net/sprint?retryWrites=true&w=majority";
	shared_ptr<Mongo::RepositoryList> repositoryList(new Mongo::RepositoryList(url));

	shared_ptr<SprintService> sprintService(new SprintService(repositoryList));
	shared_ptr<Context> context(new Context(sprintService));
	shared_ptr<ControllerList> controllerList(new ControllerList(context));
	// sprintService->test1();


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
			std::cout << " [x] Received " << request << std::endl;

			std::string response = controllerList->route(request);
			AMQP::Envelope env(response.c_str(), response.length());

			channel.publish("", message.replyTo(), env);
			channel.ack(deliveryTag);
		});

	std::cout << " [*] Waiting for messages. To exit press CTRL-C\n";
	handler.loop();

	return 0;
}