#include"base_include.h"

int main()
{
	CSocketServer g_server;
	CPacket g_packet;

	g_server.Init(INADDR_ANY, 8000, &g_packet);

	g_packet.Start();
	g_server.Start();
	
    g_packet.Stop();
	g_server.Stop();
	
	
	return 0;
}