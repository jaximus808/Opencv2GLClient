//#include"SerialPort.h"
//
//SerialPort::SerialPort(char* portName)
//{
//	errors = 0; 
//	status = { 0 };
//	connected = false; 
//
//	handleToCOM = CreateFileA(static_cast<LPCSTR>(portName), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	DWORD errMsg = GetLastError(); 
//
//	if (errMsg == 2)
//	{
//		std::cout << "The usb port is not plugged in" << std::endl;
//	}
//	else if (errMsg == 5)
//	{
//		std::cout << "acess denied" << std::endl;
//	}
//	else if (errMsg == 0)
//	{
//		DCB dcbserialParameters = { 0 };
//		if (!GetCommState(handleToCOM, &dcbserialParameters))
//		{
//			std::cout << "failed to get current aprameters" << std::endl;
//		}
//		else
//		{
//			dcbserialParameters.BaudRate = CBR_9600;
//			dcbserialParameters.ByteSize = 8;
//			dcbserialParameters.StopBits = ONESTOPBIT; 
//			dcbserialParameters.Parity = NOPARITY;
//			dcbserialParameters.fDtrControl = DTR_CONTROL_ENABLE;
//
//			if (!SetCommState(handleToCOM, &dcbserialParameters))
//			{
//				std::cout << "could not set Serial Port Parameters" << std::endl;
//			}
//			else
//			{
//				connected = true; 
//				PurgeComm(handleToCOM, PURGE_RXCLEAR | PURGE_TXCLEAR); 
//				DWORD waitTime = ARDUINO_WAIT_TIME;
//				Sleep(waitTime);
//			}
//		}
//	}
//}
//
//SerialPort::~SerialPort()
//{
//	if (connected)
//	{
//		connected = false;
//		CloseHandle(handleToCOM);
//	}
//}
//
//int SerialPort::ReadSerialPort(char* buffer, unsigned int buf_size)
//{
//	DWORD bytesRead; 
//	unsigned int toRead = 0; 
//
//	ClearCommError(handleToCOM, &errors, &status);
//
//	if (status.cbInQue > 0)
//	{
//		if (status.cbInQue > buf_size)
//		{
//			toRead = buf_size;
//		}
//		else toRead = status.cbInQue; 
//	}
//
//	if (ReadFile(handleToCOM, buffer, toRead, &bytesRead, NULL))
//	{
//		return bytesRead; 
//	}
//	return 0;
//}
//
//bool SerialPort::isConnected()
//{
//	return connected;
//}