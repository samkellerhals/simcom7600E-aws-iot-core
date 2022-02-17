#include <iostream>
#include <windows.h>
#include "serial.h"
#include "at.h"

struct ApplicationConfig CONFIG = {
    "COM4", 
    "clientcert.pem", 
    "clientkey.pem", 
    "cacert.pem", 
    "<enter-your-aws-endpoint>", // add your aws iot core REST API endpoint
    "test_device", // add your aws iot core thing name
    "aws/things/simcom7600_device01/" // add your mqtt topic
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
        acquire_new_mqtt_client(serial_handle, CONFIG); // TODO: handle already open +CMQTTSTART: 23
        configure_client_ssl(serial_handle); // TODO: handle client already used +CMQTTACCQ: 0,19
        // TODO: set will topic and will msg
        start_mqtt_connection(serial_handle, CONFIG);
        subscribe_to_mqtt_topic(serial_handle, CONFIG); // TODO: handle not supported operation (already connected?) +CMQTTCONNECT: 0,13
        publish_to_mqtt_topic(serial_handle, CONFIG);

        // TODO: Listen to incoming MQTT messages

        CloseHandle(serial_handle);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/* Useful references
http://members.ee.net/brey/Serial.pdf
https://web.archive.org/web/20120905123232/http://robbayer.com/files/serial-win.pdf
*/
