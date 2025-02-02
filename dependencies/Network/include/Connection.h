#ifndef __NET_CONNECTION__
#define __NET_CONNECTION__

#include <UniversumLib.h>
#ifdef _WIN32
#include <SDLNet/SDL_net.h>
#else
#include <SDL/SDL_net.h>
#endif

class Connection
{
public:
    Connection(const char* url_host, int port);
    virtual ~Connection();

    //! stellt eine verbindung her
    //! \return NULL wenn keine verbindung erfolgte
    TCPsocket getSocket();

    __inline__ void setCallbackIndex(int index) {mCallbackIndex = index;};
    __inline__ int  getCallbackIndex() {return mCallbackIndex;}
    virtual UniLib::lib::BufferedNetworkPacket* send(const void* data, int length);

protected:

    DRReturn getIP();
    void splitURL_HOST(const char* url_host);

    //!
    std::string mURL;
    std::string mHOST;

    IPaddress                          mIP;
    TCPsocket                          mSocket;
	SDLNet_SocketSet				   mSocketSet;

    int                                mCallbackIndex;

private:
};

#endif // __NET_CONNECTION__
