#ifndef _SERVERTHREAD_H_
#define _SERVERTHREAD_H_

#include <wx/thread.h>
#include <wx/ipc.h>

class ServerThread : public wxThread
{
	public:
		ServerThread(wxServer* server);
		~ServerThread();
		void* Entry();
	private:
		wxServer* m_server;
};


#endif // _SERVERTHREAD_H_
