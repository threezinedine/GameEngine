#include <string>
#include "NTTEngineLog/NTTEngineLog.hpp"
#include "MQTT/MQTT.hpp"
#include <thread>


MQTTClient* MQTTClient::instance_ = nullptr;

MQTTClient::MQTTClient(std::string server, std::string clientId)
    : cli_(server, clientId)
{
    NTT_APPLICATION_DEBUG("Start Initialize MQTT Client");
    MQTTClient::instance_ = this;
	connOpts_.set_clean_session(false);

    cb_ = new MQTTCallback(cli_, connOpts_, clientId);
    cb_->SetQos(2);
    cb_->AddTopic("temperature", [](mqtt::const_message_ptr msg)
    {
        // MQTTWindow::temperatureValue = std::stof(msg->to_string());
    });
    cli_.set_callback(*cb_);
    NTT_APPLICATION_DEBUG("Finish Intialize MQTT Client");
}

MQTTClient::~MQTTClient()
{

}

void MQTTClient::Connect()
{
    // std::thread t([this]() {
        try {
            NTT_APPLICATION_INFO("Connecting to the MQTT server...");
            cli_.connect(connOpts_, nullptr, *cb_);
            NTT_APPLICATION_INFO("Connected Successfully...");
        }
        catch (const mqtt::exception& exc) {
            NTT_APPLICATION_ERROR("\nERROR: Unable to connect to MQTT server: '" + exc.get_message());
        }
    // });
}

void MQTTClient::Disconnect()
{
    cli_.disconnect()->wait();
}


void MQTTClient::Publish(std::string topic, std::string value)
{
    mqtt::message_ptr msg = mqtt::make_message(topic.c_str(), 
									value.c_str(),
									cb_->GetQos(), false);
	cli_.publish(msg)->wait_for(1000);
}