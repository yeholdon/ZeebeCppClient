#ifndef ZEEBE_PROCESS_H_
#define ZEEBE_PROCESS_H_

#include <string>
#include <vector>
#include <sys/_types/_int32_t.h>
#include <sys/_types/_int64_t.h>

namespace ZeebeCpp
{

struct ProcessInfo {
    std::string bpmnProcessId;
    int32_t version;
    int64_t processDefinitionkey;
    std::string processName;
};

struct ProcessInstanceInfo
{
    std::string bpmnProcessId;
    int32_t version;
    int64_t processDefinitionkey;
    int64_t processInstanceKey;
};

} // namespace ZeebeCpp

#endif // ZEEBE_PROCESS_H_
