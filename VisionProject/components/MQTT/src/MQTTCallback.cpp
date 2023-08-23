#include <MQTT/MQTT.hpp>
#include <string>
#include <functional>


void MQTTCallback::reconnect()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
        cli_.connect(connOpts_, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        exit(1);
    }
}


void MQTTCallback::on_failure(const mqtt::token& tok)
{
    std::cout << "Connection attempt failed" << std::endl;
    if (++nretry_ > n_retry_attempt_)
        exit(1);
    reconnect();
}


void MQTTCallback::on_success(const mqtt::token& tok)
{

}

void MQTTCallback::connected(const std::string& cause)
{
    isConectedd_ = true;
    std::cout << "\nConnection success" << std::endl;
    std::cout << "\tfor client " << clientId_
        << " using QoS" << qos_ << "\n" << std::endl;

    for (const auto& pair: topics_)
    {
        const std::string& key = pair.first;
        std::cout << "Subscribe to: " << key << std::endl;
        Subscribe(key);        
    }
}

void MQTTCallback::connection_lost(const std::string& cause)
{
    std::cout << "\nConnection lost" << std::endl;
    if (!cause.empty())
        std::cout << "\tcause: " << cause << std::endl;

    std::cout << "Reconnecting..." << std::endl;
    nretry_ = 0;
    reconnect();
}

void MQTTCallback::message_arrived(mqtt::const_message_ptr msg)
{
    auto it = topics_.find(msg->get_topic());
    if (it != topics_.end())
    {
        it->second(msg);
    }
}

void MQTTCallback::delivery_complete(mqtt::delivery_token_ptr token)
{

} 

void MQTTCallback::AddTopic(const std::string& topic, std::function<void(mqtt::const_message_ptr)> callback)
{
    topics_[topic] = callback;
    Subscribe(topic);
}

void MQTTCallback::RemoveTopic(const std::string& topic)
{
    topics_.erase(topic);
    UnSubscribe(topic);
}

void MQTTCallback::Subscribe(const std::string& topic)
{
    if (isConectedd_)
    {
        std::cout << "Subscribe to topic: " << topic << std::endl;
        cli_.subscribe(topic, qos_, nullptr, subListener_);
    }
}


void MQTTCallback::UnSubscribe(const std::string& topic)
{
    if (isConectedd_)
    {
        cli_.unsubscribe(topic);
    }
}