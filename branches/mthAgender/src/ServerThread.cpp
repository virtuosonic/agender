
#include "ServerThread.h"
#include "AgenderIPC.h"

/** @brief Entry
  *
  * @todo: document this function
  */

 ServerThread::ServerThread(wxServer* server) : wxThread(wxTHREAD_DETACHED)
{
	m_server = server;
}

 ServerThread::~ServerThread()
{

}

void* ServerThread::Entry()
{
	if (!m_server->Create(IPC_Service))
		return 0;

	while (!TestDestroy())
		Sleep(100);
	/*both Yield ans Sleep don't work but Yield wastes more cpu*/
	return 0;
}
