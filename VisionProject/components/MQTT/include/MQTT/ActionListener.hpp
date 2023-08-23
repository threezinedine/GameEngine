#pragma once
#include <string>
#include "mqtt/async_client.h"


class ActionListener : public virtual mqtt::iaction_listener
{
	public:
		ActionListener(const std::string& name) : name_(name) {}

	private:
		std::string name_;

		void on_failure(const mqtt::token& tok) override;

		void on_success(const mqtt::token& tok) override;
};