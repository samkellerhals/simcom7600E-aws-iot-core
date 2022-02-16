#include <iostream>
#include <windows.h>
#include "serial.h"
#include "at.h"
#include "utils.h"

std::string DEFAULT_PORT = "COM4";
std::string CONFIG_FILE = "config";
std::string ROOT_DIR = get_exe_root_dir();

int main()
{   
    HANDLE serial_handle = get_serial_handle(DEFAULT_PORT);
    /* TODO: Define read_config function which will read
        configuration from config into a struct to be used later.
        Key value pairs can be read based on = and \n
        Define this in utils.cpp
    */

    if (is_handle_valid(DEFAULT_PORT, serial_handle)) {

        set_serial_settings(serial_handle);        
        get_device_info(serial_handle);
        get_current_operator(serial_handle);
        get_signal_strength(serial_handle);
        
        read_txt_file(ROOT_DIR, CONFIG_FILE);
        
        /* TODO: setup AWS certificates
        - take paths to keys from config struct, load certificates from paths.
        - add read txt file into string function to utils.cpp
        - add function to at.cpp which loads certificates onto device.
        */
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
