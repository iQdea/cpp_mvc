#include <iostream>

#include "SimplePocoHandler.h"

std::string query(std::string message) {
    //const std::string correlation(uuid());
    std::string response = "";

    SimplePocoHandler handler("192.168.0.95", 5672);
    AMQP::Connection connection(&handler, AMQP::Login("qdea", "qdea12345"), "/");
    AMQP::Channel channel(&connection);

    AMQP::QueueCallback callback = [&channel,&message](const std::string& name,
        int msgcount,
        int consumercount)
    {
        AMQP::Envelope env(message.c_str(), message.length());
        //env.setCorrelationID(correlation);
        env.setReplyTo(name);
        channel.publish("", "rpc_queue", env);
        std::cout << " [x] Requesting" << std::endl;
    };
    channel.declareQueue(AMQP::exclusive).onSuccess(callback);

    auto receiveCallback = [&](const AMQP::Message& message,
        uint64_t deliveryTag,
        bool redelivered)
    {
        //if (message.correlationID() != correlation)
        //    return;

        response = std::string(message.body(), message.bodySize());

        std::cout << " [.] Got " << response << std::endl;
        handler.quit();
    };

    channel.consume("", AMQP::noack).onReceived(receiveCallback);

    handler.loop();
    return response;
}

int main(void)
{
    while (true) {
        char str[256];
        std::cin.getline(str, 256);
        std::string req = str;

        if (req == "q") break;
        std::string resp = query(req);
        std::cout << resp << std::endl;
    }
    
    return 0;
}