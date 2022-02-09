#include <iostream>
#include <windows.h>

using namespace std;

HANDLE hSerial;
LPCSTR DEFAULT_PORT = "COM4";
DCB dcb;
COMMTIMEOUTS timeouts = {0};

/* Useful references
http://members.ee.net/brey/Serial.pdf
https://web.archive.org/web/20120905123232/http://robbayer.com/files/serial-win.pdf
*/

#define CRLF "\r\n";

int main()
{   

    // Create serial port connection
    hSerial = CreateFile(
        DEFAULT_PORT,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cout << "Serial port does not exist" << endl;
        }
        cout << "Other error ocurred" << endl;
    }
    else
    {
        cout << "Serial Port Found" << endl;
    }

    // defining COM port settings
    if (!GetCommState(hSerial, &dcb)) {
        cout << "There was an error acquiring communication state" << endl;
    }

    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;

    if(!SetCommState(hSerial, &dcb)) {
        cout << "Error setting serial port state" << endl;
    }

    timeouts.ReadIntervalTimeout=50;
    timeouts.ReadTotalTimeoutConstant=50;
    timeouts.ReadTotalTimeoutMultiplier=10;
    timeouts.WriteTotalTimeoutConstant=50;
    timeouts.WriteTotalTimeoutMultiplier=10;

    if(!SetCommTimeouts(hSerial, &timeouts)) {
        cout << "Error setting communication timeouts." << endl;
    }


    int n = 200; // TODO: We need to read all bytes until the CRLF or endline character is found.
    // Writing data to port
    char wBuff[] = "AT+COPS?" CRLF;
    DWORD byteswritten;
    if(!WriteFile(hSerial, wBuff, 13, &byteswritten, NULL)) {    // TODO: get length of bytes from write buffer size + 1 byte.
        cout << "Error writing to serial port.";
    }
    

    // Reading data from port
    char rBuff[n + 1] = {0};
    DWORD dwBytesRead = 0;

    if(!ReadFile(hSerial, rBuff, n, &dwBytesRead, NULL)) {
        cout << "Error reading from serial port.";
    }

    cout << dwBytesRead << endl;
    cout << rBuff;


    CloseHandle(hSerial);
    return 0;
}
