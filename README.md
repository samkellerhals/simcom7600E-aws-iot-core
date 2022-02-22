# SIMCOM7600 AWS IoT Core Setup

A utility to setup the SIMCOM7600 with AWS IoT Core.

This program will establish an MQTT connection between the SIMCOM7600 module and AWS IoT core, subscribe to a topic and publish a message to it.
It will then listen for incoming messages to this topic - which can be tested using the AWS IoT Core MQTT test client.

## Requirements

You need to setup a `thing` (device) on AWS IoT core, and generate the required certificates (`pem` files).
The following certificates are required in the root of this repository, and can be renamed to the following names:

- Amazon trust services endpoint certificate (Amazon Root CA 1): `cacert.pem`
- A device certificate: `clientcert.pem`
- The private key certificate: `clientkey.pem`

For more information on setting up a new device on AWS and the corresponding certificates see this article: https://www.hackster.io/victorffs/connecting-sim7600x-h-to-aws-using-mqtt-and-at-commands-2a693c

## Configuration

The application needs to be configured via the `ApplicationConfig` struct which is found in `main.cpp`.

```C++
struct ApplicationConfig {
    std::string port;
    std::string clientcert; 
    std::string clientkey;
    std::string cacert; 
    std::string awsurl;
    std::string thing_name;
    std::string topic;
    std::string willmsg;
};
```
The `awsurl` is the AWS IoT Core endpoint which can be found in settings. The `topic` represents the `MQTT` topic to subscribe and publish to, and `thing_name` is the name of the AWS IoT Core `thing` which you setup. The `willmsg` is a message which is published to the AWS IoT Core MQTT broker in case the device gets disconnected. The certificate names are the file names of the corresponding certificates, which must be stored in the root of this repository. `port` is the name of the port to which the SIMCOM module is connected to.

## Usage

This utility currently only runs on Windows operating systems as it is configured with API calls from `<windows.h>`.

Compile using `g++ src/*.cpp -o main`

Run using `./main.exe`