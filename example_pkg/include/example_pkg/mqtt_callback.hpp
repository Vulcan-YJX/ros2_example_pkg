#ifndef MQTT_CALLBACK_HPP
#define MQTT_CALLBACK_HPP

#include <mqtt/async_client.h>

// {"type":"temperature","value":24.7}
class Callback : public virtual mqtt::callback {
public:
    void message_arrived(mqtt::const_message_ptr msg) override {
        try {
            std::string topic = msg->get_topic();
            std::string payload = msg->to_string();

            std::cout << "Message arrived [" << topic << "] raw: " << payload << std::endl;

            auto json_data = nlohmann::json::parse(payload);
            if (json_data.contains("type") && json_data.contains("value")) {
                std::cout << "Parsed JSON → type: " << json_data["type"]
                          << ", value: " << json_data["value"] << std::endl;
            } else {
                std::cout << "JSON missing expected fields." << std::endl;
            }
        } catch (const nlohmann::json::parse_error& e) {
            std::cerr << "JSON parse error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Message processing error: " << e.what() << std::endl;
        }
    }

    void connection_lost(const std::string &cause) override {
        std::cout << "Connection lost: " << cause << std::endl;
    }
};

#endif  // MQTT_CALLBACK_HPP
