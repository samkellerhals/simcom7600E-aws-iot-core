#include <iostream>
#include "serial.h"

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
