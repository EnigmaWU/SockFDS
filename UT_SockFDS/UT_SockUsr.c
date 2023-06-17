//connect UT_SockFDS_Srv, recv data from UT_SockFDS_Srv, stat received data, then discard it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
//inet_addr
#include <arpa/inet.h>
#include <errno.h>

#include "UT_SockFDS.h"

//parse from args: -S xxx.xxx.xxx.xxx
static const char *_mSockFDS_SrvIP = "127.0.0.1";
//parse from args: -P nnn
static int _mSockFDS_SrvPort = 63695;

//use getopts to parse args of _mSockFDS_SrvIP and _mSockFDS_SrvPort
static void __parseArgs(int argc, char *argv[])
{
    int opt = 0;
    int ret = 0;

    while ((opt = getopt(argc, argv, "S:P:")) != -1)
    {
        switch (opt)
        {
            case 'S':
                _mSockFDS_SrvIP = optarg;
                break;
            case 'P':
                ret = atoi(optarg);
                if (ret > 0)
                {
                    _mSockFDS_SrvPort = ret;
                }
                break;
            default:
                break;
        }
    }
}

static int __connectSockFDS_Srv( const char *SockFDS_SrvIP, const int SockFDS_SrvPort )
{
    int ret = 0;
    int fd = 0;
    struct sockaddr_in addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        printf("socket failed\n");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SockFDS_SrvPort);
    addr.sin_addr.s_addr = inet_addr(SockFDS_SrvIP);

    //conncet may block, consider timeout 5s
    ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));  
    if (ret < 0)
    {
        printf("connect failed, errno=%d<%s>\n", errno, strerror(errno));
        close(fd);
        return -1;
    }

    return fd;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int fd = 0;
    int len = 0;
    char buf[1024] = {0};

    fd = __connectSockFDS_Srv(_mSockFDS_SrvIP, _mSockFDS_SrvPort);
    if (fd < 0)
    {
        printf("_ failed\n");
        return -1;
    }

    while (1)
    {
        len = recv(fd, buf, sizeof(buf), 0);
        if (len < 0)
        {
            printf("recv failed\n");
            break;
        }
        else if (len == 0)
        {
            printf("peer closed\n");
            break;
        }
        else
        {
            printf("recv %d bytes\n", len);
        }
    }

    close(fd);

    return ret;
}
