#ifndef AT_H
#define AT_H
#include "serial.h"

struct ApplicationConfig {
    std::string port;
    std::string clientcert; 
    std::string clientkey;
    std::string cacert; 
    std::string awsurl;
    std::string thing_name;
    std::string topic;
    std::string willmsg;
};

void get_device_info(HANDLE serial_handle);
void get_current_operator(HANDLE serial_handle);
void get_signal_strength(HANDLE serial_handle);
void view_ssl_certificates(HANDLE serial_handle);
void setup_ssl_context(HANDLE serial_handle);
void load_certificates(HANDLE serial_handle, ApplicationConfig config);
void start_mqtt_service(HANDLE serial_handle);
void acquire_new_mqtt_client(HANDLE serial_handle, ApplicationConfig config);
void configure_client_ssl(HANDLE serial_handle);
void start_mqtt_connection(HANDLE serial_handle, ApplicationConfig config);
void subscribe_to_mqtt_topic(HANDLE serial_handle, ApplicationConfig config);
void publish_to_mqtt_topic(HANDLE serial_handle, ApplicationConfig config);
void set_will_topic(HANDLE serial_handle, ApplicationConfig config);
void set_will_msg(HANDLE serial_handle, ApplicationConfig config);
#endif