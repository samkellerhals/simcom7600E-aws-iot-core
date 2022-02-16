#include <iostream>
#include <windows.h>
#include <string.h>
#include "serial.h"

#define CRLF "\r\n";
const int MAX_READ_BUFFER_SIZE = 10000;

HANDLE get_serial_handle(std::string port_name) {
    LPCSTR port = port_name.c_str();

    HANDLE serial_handle = CreateFile(
        port,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);
    return serial_handle;   
}

bool is_handle_valid(std::string port_name, HANDLE serial_handle) {
    if (serial_handle == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            std::cout << "Serial port does not exist" << std::endl;
            return false;
        }
        std::cout << "Other error ocurred" << std::endl;
        return false;
    }
    else
    {
        std::cout << "Serial Port " << port_name << " Found" << std::endl;
        return true;
    }
}

void set_serial_settings(HANDLE serial_handle) {
    DCB dcb;
    COMMTIMEOUTS timeouts = {0};    

    // defining COM port settings
    if (!GetCommState(serial_handle, &dcb)) {
        std::cout << "There was an error acquiring communication state" << std::endl;
    }

    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;

    if(!SetCommState(serial_handle, &dcb)) {
        std::cout << "Error setting serial port state" << std::endl;
    }

    timeouts.ReadIntervalTimeout=50;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier=10;
    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier=10;

    if(!SetCommTimeouts(serial_handle, &timeouts)) {
        std::cout << "Error setting communication timeouts." << std::endl;
    }
}

void write_to_serial(HANDLE serial_handle, std::string data) {

    std::string to_write = data + CRLF;

    int char_size = sizeof(char);
    int string_length = to_write.size();
    int bytes_to_write = string_length * char_size; 
    DWORD bytes_written;   

    // we need to convert the string to LPCVOID to send over serial.
    LPCVOID to_write_lpc = to_write.c_str();
    
    if(!WriteFile(serial_handle, to_write_lpc, bytes_to_write, &bytes_written, NULL)) {
        std::cout << "Error writing to the serial port." << std::endl;
    } else {
        std::cout << "\nWrote " << bytes_to_write << " bytes to serial port.\n" << std::endl;
    }
}

void read_from_serial(HANDLE serial_handle) {
    char buffer[MAX_READ_BUFFER_SIZE] = {0};
    DWORD dwBytesRead = 0;
    
    if(!ReadFile(serial_handle, buffer, MAX_READ_BUFFER_SIZE, &dwBytesRead, NULL)) {
        std::cout << "Error reading from serial port.";
    }
    std::cout << buffer;
}
