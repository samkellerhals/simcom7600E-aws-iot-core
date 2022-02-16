#include <iostream>
#include <windows.h>
#include "serial.h"
#include "at.h"

struct ApplicationConfig CONFIG = {
    "COM4", 
    "clientcert.pem", 
    "clientkey.pem", 
    "cacert.pem", 
    "<enter-your-endpoint>"
    };

int main()
{   
    HANDLE serial_handle = get_serial_handle(CONFIG.port);
   
    if (is_handle_valid(CONFIG.port, serial_handle)) {

        set_serial_settings(serial_handle);        
        get_device_info(serial_handle);
        get_current_operator(serial_handle);
        get_signal_strength(serial_handle);
        load_certificates(serial_handle, CONFIG);
        
        // get_ssl_certificates(serial_handle);
        // setup_ssl_context(serial_handle);
        // TODO: start MQTTSERVICE
        // TODO: acquire MQTT client
        // TODO: enable SSL on client
        // TODO: set will topic and will msg
        // TODO: start MQTT connection
        // TODO: subscribe to MQTT topic
        // TODO: publish to MQTT topic that we are online
        // TODO: start listening to incoming MQTT messages

        CloseHandle(serial_handle);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/* Useful references
http://members.ee.net/brey/Serial.pdf
https://web.archive.org/web/20120905123232/http://robbayer.com/files/serial-win.pdf
*/
