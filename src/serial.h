#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <windows.h>

HANDLE get_serial_handle(std::string port_name);

bool is_handle_valid(std::string port_name, HANDLE serial_handle);

void set_serial_settings(HANDLE serial_handle);

void write_to_serial(HANDLE serial_handle, std::string data);

void read_from_serial(HANDLE serial_handle);

void listen_for_incoming_messages(HANDLE serial_handle);

#endif