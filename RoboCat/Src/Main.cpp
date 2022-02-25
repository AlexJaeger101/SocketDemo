
#include "RoboCatPCH.h"
#include <thread>

#if _WIN32


int main(int argc, const char** argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#else
const char** __argv;
int __argc;
int main(int argc, const char** argv)
{
	__argc = argc;
	__argv = argv;
#endif

	SocketUtil::StaticInit();

	UDPSocketPtr cliSock = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
	UDPSocketPtr srvSock = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
	
	SocketAddressPtr srvAddress = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:9001");
	{
		SocketAddressPtr cliAdress = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:9000");
		if (cliAdress == nullptr)
		{
			SocketUtil::ReportError("Create client socket");
			ExitProcess(1);
		}
		cliSock->Bind(*cliAdress);

	}

	srvSock->Bind(*srvAddress);

	std::thread srvThread([&srvSock]()
	{
			char buffer[4096];
			SocketAddress fromAddr;
			int nByteReceive = srvSock->ReceiveFrom(buffer, 4096, fromAddr);
			std::string msg(buffer, nByteReceive);
			if (nByteReceive <= 0)
			{
				SocketUtil::ReportError("Server RecieveFrom");
				return;
			}
			std::cout << "Recieve message from " << fromAddr.ToString() << ": " << msg << std::endl;
	});

	std::string msg("Hello Server!");
	int nByteSent = cliSock->SendTo(msg.c_str(), msg.length(), *srvAddress);
	if (nByteSent <= 0)
	{
		SocketUtil::ReportError("Client SentTo");
	}
	std::cout << "Sent " << nByteSent << " byts\n";

	srvThread.join();

	SocketUtil::CleanUp();

	return 0;
}
