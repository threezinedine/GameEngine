#pragma once
#include "ActionListener.hpp"
#include "mqtt/async_client.h"
#include <functional>
#include <map>
#include "MQTTClient.hpp"



class MQTTCallback : public virtual mqtt::callback,
					public virtual mqtt::iaction_listener
{
    public:
        MQTTCallback(mqtt::async_client& cli, mqtt::connect_options& connOpts, 
                    const std::string& clientId, int n_retry_attempt = 5)
                    : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription"),
                        clientId_(clientId), n_retry_attempt_(n_retry_attempt)
        {}

        MQTTCallback(const MQTTCallback& other)
            :nretry_(other.nretry_), cli_(other.cli_),
                connOpts_(other.connOpts_),
                subListener_(other.subListener_),
                n_retry_attempt_(other.n_retry_attempt_),
                clientId_(other.clientId_)
        {}

        inline int GetQos() const { return qos_; }
        inline void SetQos(int qos) { qos_ = qos; }
        inline std::string& GetClientId() { return clientId_; }
        inline mqtt::async_client& GetCLI() { return cli_; }
        inline mqtt::connect_options& GetConnOpts() { return connOpts_; }

        void AddTopic(const std::string& topic, 
                std::function<void(mqtt::const_message_ptr)> callback = [](mqtt::const_message_ptr msg){});
        void RemoveTopic(const std::string& topic);

        MQTTCallback& operator=(const MQTTCallback& other) 
        {
            if (this == &other) 
            {
                return *this; // Handle self-assignment
            }

            *this = MQTTCallback(other);

            return *this;
        }

    private:
        int nretry_;
        mqtt::async_client& cli_;
        mqtt::connect_options& connOpts_;
        ActionListener subListener_;
        int n_retry_attempt_ = 5;
        std::string clientId_ = "";
        int qos_ = 1;
        std::map<std::string, std::function<void(mqtt::const_message_ptr)>> topics_;
        bool isConectedd_ = false;

        void reconnect();

        void on_failure(const mqtt::token& tok) override;

        void on_success(const mqtt::token& tok) override;

        void connected(const std::string& cause) override;

        void connection_lost(const std::string& cause) override;

        void message_arrived(mqtt::const_message_ptr msg) override;

        void delivery_complete(mqtt::delivery_token_ptr token) override;

        void Subscribe(const std::string& topic);
        void UnSubscribe(const std::string& topic);
};