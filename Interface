#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

// Define serial port parameters
const string portName = "COM1";  // Replace with your actual port name
const int baudRate = 9600;

// Function prototypes
void processData(const string& data);
void sendData(double Zmag, double Zphase);

// Define function to read data from serial port
void readData(serial_port& port) {
  // Create buffer for incoming data
  char buffer[1024];

  // Read data from serial port
  size_t bytesRead = port.read_some(buffer, sizeof(buffer));
  if (bytesRead > 0) {
    // Extract data from buffer
    string data(buffer, bytesRead);

    // Process the data
    processData(data);
  }
}

// Define function to process data
void processData(const string& data) {
  // Parse the data to extract impedance values
  stringstream ss(data);
  string realPart, imagPart;
  getline(ss, realPart, ',');
  getline(ss, imagPart);

  double Zreal = stod(realPart);
  double Zimag = stod(imagPart);

  // Calculate impedance magnitude and phase
  double Zmag = sqrt(Zreal * Zreal + Zimag * Zimag);
  double Zphase = atan2(Zimag, Zreal) * 180 / M_PI;  // Convert to degrees

  // Send impedance data to the Windows PC
  sendData(Zmag, Zphase);
}

// Define function to send data to the Windows PC
void sendData(double Zmag, double Zphase) {
  // Create TCP socket
  boost::asio::io_service ioService;
  tcp::resolver resolver(ioService);
  tcp::resolver::query query(tcp::v4(), "localhost", "8000");

  // Connect to the Windows PC
  tcp::socket socket(ioService);
  resolver::iterator endpointIterator = resolver.resolve(query);
  boost::asio::connect(socket, endpointIterator);

  // Send impedance data
  stringstream dataStream;
  dataStream << Zmag << ",";
  dataStream << Zphase;
  string data = dataStream.str();

  boost::asio::write(socket, boost::asio::buffer(data));
}

// Main function
int main() {
  // Initialize Boost.Asio
  boost::asio::io_service ioService;

  // Create serial port object
  serial_port port(ioService, portName);
  port.set_option(serial_port_base::baud_rate(baudRate));

  // Start reading data from the serial port
  while (true) {
    readData(port);
  }

  return 0;
}
