#include"base_include.h"

int main()
{
	CSocketServer g_server;

	g_server.Start();

	g_server.Stop();
	
	return 0;
}