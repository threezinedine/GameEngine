#pragma once
#include <string>
#include "MQTTCallback.hpp"
#include "ActionListener.hpp"


class MQTTCallback;

class MQTTClient
{
    public:
        MQTTClient(std::string server, std::string clienId);
        ~MQTTClient();

        void Connect();
        void Disconnect();

        void Publish(std::string topic, std::string value);

        static inline MQTTClient* GetInstance() { return instance_; };

    private:
        mqtt::async_client cli_;
	    mqtt::connect_options connOpts_;
        MQTTCallback* cb_;

        static MQTTClient* instance_;
};