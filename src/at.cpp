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

void get_ssl_certificates(HANDLE serial_handle) {
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
    
    for (int i = 0; i < sizeof(ssl_commands); i++) {

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

    //TODO: list all certificates
}
/* TODO: add client certificate loading 

Takes certificate struct.

AT+CCERTDOWN="clientcert.pem",1220 // change size and send cetificate-pem.crt
AT+CCERTDOWN="clientkey.pem",1675 // change size and send private.pem.key
AT+CCERTDOWN="cacert.pem",1188 // change size and send AmazonRootCA1.pem

*/