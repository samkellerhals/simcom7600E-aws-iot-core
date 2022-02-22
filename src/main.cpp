#include <iostream>
#include <windows.h>
#include "serial.h"
#include "at.h"
#include "utils.h"

struct ApplicationConfig CONFIG = {
    "COM4", 
    "clientcert.pem", 
    "clientkey.pem", 
    "cacert.pem", 
    "<AWSURL>", // Add your AWS URL here
    "test_device",
    "aws/things/simcom7600_device01/",
    "{\"message\": \"SIMCOM7600 disconnected.\"}"
    };

int main()
{   
    HANDLE serial_handle = get_serial_handle(CONFIG.port);
   
    if (is_handle_valid(CONFIG.port, serial_handle)) {

        // SIMCOM setup
        set_serial_settings(serial_handle);        
        get_device_info(serial_handle);
        get_current_operator(serial_handle);
        get_signal_strength(serial_handle);
        load_certificates(serial_handle, CONFIG);
        view_ssl_certificates(serial_handle);
        setup_ssl_context(serial_handle);
        
        // MQTT service setup
        start_mqtt_service(serial_handle);
        acquire_new_mqtt_client(serial_handle, CONFIG); 
        configure_client_ssl(serial_handle); 
        set_will_topic(serial_handle, CONFIG);
        set_will_msg(serial_handle, CONFIG);
        start_mqtt_connection(serial_handle, CONFIG);
        subscribe_to_mqtt_topic(serial_handle, CONFIG);
        publish_to_mqtt_topic(serial_handle, CONFIG);

        // Listen to incoming MQTT messages
        listen_for_incoming_messages(serial_handle);

        CloseHandle(serial_handle);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/* Useful references
http://members.ee.net/brey/Serial.pdf
https://web.archive.org/web/20120905123232/http://robbayer.com/files/serial-win.pdf
*/
