#include <iostream>
#include "serial.h"
#include "utils.h"
#include <sstream>
#include "at.h"

void get_device_info(HANDLE serial_handle) {
    write_to_serial(serial_handle, "ATI");
    read_from_serial(serial_handle);
}

void get_signal_strength(HANDLE serial_handle) {
    write_to_serial(serial_handle, "AT+CSQ");
    read_from_serial(serial_handle);
}

void get_current_operator(HANDLE serial_handle) {
    write_to_serial(serial_handle, "AT+COPS?");
    read_from_serial(serial_handle);
}

void view_ssl_certificates(HANDLE serial_handle) {
    write_to_serial(serial_handle, "AT+CCERTLIST");
    read_from_serial(serial_handle);
}

void setup_ssl_context(HANDLE serial_handle) {
    std::string ssl_commands[] = {
        "\"sslversion\",0,4", 
        "\"authmode\",0,2",
        "\"cacert\",0,\"cacert.pem\"",
        "\"clientcert\",0,\"clientcert.pem\"",
        "\"clientkey\",0,\"clientkey.pem\"",
        };
    
    int num_commands = sizeof(ssl_commands)/sizeof(ssl_commands[0]);

    for (int i = 0; i < num_commands; i++) {

        std::string at_command = "AT+CSSLCFG=" + ssl_commands[i];

        write_to_serial(serial_handle, at_command);
        read_from_serial(serial_handle);
    }
}

void load_certificates(HANDLE serial_handle, ApplicationConfig config) {
    std::cout << "Loading certificates...\n";
    std::string root_dir = get_exe_root_dir();
    std::string clientcert_path = root_dir + config.clientcert;
    std::string clientkey_path = root_dir + config.clientkey;
    std::string cacert_path = root_dir + config.cacert;

    std::string clientcert = readFileIntoString(clientcert_path);
    std::string clientkey = readFileIntoString(clientkey_path);
    std::string cacert = readFileIntoString(cacert_path);

    size_t clientcert_size = clientcert.size();
    size_t clientkey_size = clientkey.size();
    size_t cacert_size = cacert.size();

    std::stringstream c1;
    c1 << "AT+CCERTDOWN=" << "\"" << config.clientcert << "\"" << "," << clientcert_size;
    std::string c1_str = c1.str();
    write_to_serial(serial_handle, c1_str);
    read_from_serial(serial_handle);
    write_to_serial(serial_handle, clientcert);
    read_from_serial(serial_handle);

    std::stringstream c2;
    c2 << "AT+CCERTDOWN=" << "\"" << config.clientkey << "\"" << "," << clientkey_size;
    std::string c2_str = c2.str();
    write_to_serial(serial_handle, c2_str);
    read_from_serial(serial_handle);
    write_to_serial(serial_handle, clientkey);
    read_from_serial(serial_handle);

    std::stringstream c3;
    c3 << "AT+CCERTDOWN=" << "\"" << config.cacert << "\"" << "," << cacert_size;
    std::string c3_str = c3.str();
    write_to_serial(serial_handle, c3_str);
    read_from_serial(serial_handle);
    write_to_serial(serial_handle, cacert);
    read_from_serial(serial_handle);
}

void start_mqtt_service(HANDLE serial_handle) {
    write_to_serial(serial_handle, "AT+CMQTTSTART");
    read_from_serial(serial_handle);
}

void acquire_new_mqtt_client(HANDLE serial_handle, ApplicationConfig config) {
    std::stringstream ss;
    ss << "AT+CMQTTACCQ=0," << "\"" << config.thing_name << "\"" << ",1";
    std::string cmd = ss.str();
    write_to_serial(serial_handle, cmd);
    read_from_serial(serial_handle);
}

void configure_client_ssl(HANDLE serial_handle) {
    write_to_serial(serial_handle, "AT+CMQTTSSLCFG=0,0");
    read_from_serial(serial_handle);
}

void start_mqtt_connection(HANDLE serial_handle, ApplicationConfig config) {
    std::stringstream ss;
    ss << "AT+CMQTTCONNECT=0," << "\"tcp://" << config.awsurl << ":8883\"" << ",60,1";
    std::string cmd = ss.str();
    write_to_serial(serial_handle, cmd);
    read_from_serial(serial_handle);
}

void subscribe_to_mqtt_topic(HANDLE serial_handle, ApplicationConfig config) {
    size_t topic_size = config.topic.size();
    std::stringstream ss;
    ss << "AT+CMQTTSUBTOPIC=0," << topic_size << ",1";
    std::string cmd = ss.str();     
    write_to_serial(serial_handle, cmd);
    read_from_serial(serial_handle);

    write_to_serial(serial_handle, config.topic);
    read_from_serial(serial_handle);

    write_to_serial(serial_handle, "AT+CMQTTSUB=0");
    read_from_serial(serial_handle);
}

void publish_to_mqtt_topic(HANDLE serial_handle, ApplicationConfig config) {
    std::stringstream init_pub_topic;
    init_pub_topic << "AT+CMQTTTOPIC=0," << config.topic.size();
    std::string init_pub_topic_cmd = init_pub_topic.str();
    write_to_serial(serial_handle, init_pub_topic_cmd);
    read_from_serial(serial_handle);

    write_to_serial(serial_handle, config.topic);
    read_from_serial(serial_handle);

    std::string payload = "{\"message\":\"MQTT connection established between SIMCOM and AWS!\"}";
    std::stringstream init_pub_payload;
    init_pub_payload << "AT+CMQTTPAYLOAD=0," << payload.size();
    std::string init_pub_payload_cmd = init_pub_payload.str();
    write_to_serial(serial_handle, init_pub_payload_cmd);
    read_from_serial(serial_handle);

    write_to_serial(serial_handle, payload);
    read_from_serial(serial_handle);

    write_to_serial(serial_handle, "AT+CMQTTPUB=0,1,60");
    read_from_serial(serial_handle);
}