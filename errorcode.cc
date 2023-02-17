#include "errorcode.h"

namespace ZeebeCpp
{

static const char* faults[] = {
    [E_OK] = "Success",
    [E_FAIL] = "General Failed",
    [E_INNER] = "Internal error",
    [E_POINTER] = "Invalid Pointer",
    [E_INVALARG] = "Invalid argument",
    [E_NOTIMPL] = "Not implemented",
    [E_OUTOFMEM] = "Out of memory",
    [E_BUFERROR] = "Buffer error",
    [E_PERM] = "Permission denied",
    [E_TIMEOUT] = "Timed out",
    [E_NOTINIT] = "Object not init",
    [E_INITFAIL] = "Object init failed",
    [E_ALREADY] = "Operation already in progress",
    [E_INPROGRESS] = "Operation now in progress",
    [E_EXIST] = "Object exist",
    [E_NOTEXIST] = "Object not exist",
    [E_BUSY] = "Device or resource busy",
    [E_FULL] = "Device or resource full",
    [E_EMPTY] = "Device or resource empty",
    [E_OPENFAIL] = "Device or resource open failed",
    [E_READFAIL] = "Device or resource read failed",
    [E_WRITEFAIL] = "Device or resource write failed",
    [E_DELFAIL] = "Device or resource delete failed",
    [E_CODECFAIL] = "Encode or decode failed",
    [E_CRC_FAIL] = "CRC failed",
    [E_TOOMANY] = "Object too many",
    [E_TOOSMALL] = "Object too small",
    [E_NETNOTREACH] = "Network is unreachable",
    [E_NETDOWN] = "Network is down",


    // more...
};

const char* getErrorcode(int ec)
{
    if (ec < 0) ec = -ec;
    std::cout << "ec: " << ec << std::endl;
    if (ec < E_OK || ec >= E_END) return "Unknown error code";
    return faults[ec];
}

}
