#include <iostream>
#include <windows.h>
#include "serial.h"
#include "at.h"

std::string DEFAULT_PORT = "COM4";

int main()
{   
    HANDLE serial_handle = get_serial_handle(DEFAULT_PORT);
    
    if (is_handle_valid(DEFAULT_PORT, serial_handle)) {

        set_serial_settings(serial_handle);        
        get_device_info(serial_handle);
        get_current_operator(serial_handle);
        get_signal_strength(serial_handle);
        get_ssl_certificates(serial_handle);
        setup_ssl_context(serial_handle);

        CloseHandle(serial_handle);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/* Useful references
http://members.ee.net/brey/Serial.pdf
https://web.archive.org/web/20120905123232/http://robbayer.com/files/serial-win.pdf
*/
