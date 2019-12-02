# Real-Time Tracking Protocol C++
Welcome to Verge Inc's cpp implementation of the **Real-Time Tracking Protocol (RTTrP)** repository!

The RTTrP is a suite of protocols developed to transmit tracked motion information between systems.

RTTrP is comprised of two separate protocols which share a common header:

* RTTrPM (Real-Time Tracking Protocol - Motion)
* RTTrPL (Real-Time Tracking Protocol - Lighting) **NOT YET SUPPORTED**

This library provides a cross platform implementation of the RTTrPM protocol for creating and parsing RTTrPM messages as a pure c++11 implmentation. The library utilizes cmake to create cross-platform builds and should be portable to any c++11 compatable compiler.

## Current Limitations:
- **RTTrPL is not supported yet** but can be easily added to the framework

For further information, including packet definitions and protocol use cases, please visit the [Wiki](https://rttrp.github.io/RTTrP-Wiki/).

## Requirements
- cmake
- gtest (**for building unit tests only**)
- c++11 compiler

## Info
**author:** Tony Samaritano, Verge Inc.

# Build (POSIX)
1. Clone repo
2. Create build folder
   ```
   mkdir build
   cd build
   ```
3. run cmake
   ```
   cmake ..
   ```
4. build
   ```
   make
   ```

## Options
- Build Unit Tests: `-DRTTRPCPP_TESTS=ON`
- Debug Logging: `-DRTTRPCPP_LOG_LEVEL=<X>`
    - `-DRTTRPCPP_LOG_LEVEL=1`: print info
    - `-DRTTRPCPP_LOG_LEVEL=2`: print info and debug

# Example use (POSIX)
```cpp
#include <string>
#include <cstring>
#include <cstdio>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <rttrpcpp/RTTrPM.h>

using namespace RTTrPCpp;

void printHelp();

int main(int argc, char *argv[])
{
    uint16_t port = 24002;
    int opt;

    while ((opt = getopt(argc, argv, "p:h")) != -1)
    {
        switch (opt)
        {
            case 'p':
                port = std::stoi(optarg);
                break;
            default:
            case 'h':
                printHelp();
                return EXIT_SUCCESS;
        }
    }

    printf("Port: %u\n", port);

    int fd;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket() failed\n");
        return EXIT_FAILURE;
    }

    struct sockaddr_in addr;
    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        close(fd);
        printf("bind() failed\n");
        return EXIT_FAILURE;
    }

    int ret;
    bool shouldExit = false;
    struct timeval tv = {};
    const int maxfd = fd + 1;

    uint8_t buf[4096];
    struct sockaddr_in remaddr;
    socklen_t addrlen = sizeof(remaddr);

    while (!shouldExit)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        ret = select(maxfd, &readfds, NULL, NULL, &tv);

        if (ret == 0) continue;
        else if (ret > 0)
        {
            int recvlen = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&remaddr, &addrlen);

            /* Check Type */
            auto type = RTTrPHeader::getTypeFromBytes(buf);

            switch (type)
            {
                case RTTrPType::RTTrPM:
                {
                    RTTrPM rttrp(buf);
                    break;
                }
                default:
                    printf("Unable to deserialize packet: 0x04X\n",
                        static_cast<uint16_t>(type));
            }
        }
        else
        {
            shouldExit = true;
        }
    }

    return EXIT_SUCCESS;
}

void printHelp()
{
    fprintf(stdout,
"RTTrP Receiver Test: The purpose of this program is to test RTTrP packet\n"
"receive.\n\n"
"usage: rttrp-receiver [-p port] [-h]\n"
" -p <port>       RTTrP listening port\n"
" -h              help text\n");
}
```