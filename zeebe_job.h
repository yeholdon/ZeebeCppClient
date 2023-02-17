#ifndef ZEEBE_JOB_H_
#define ZEEBE_JOB_H_

#include <string>
#include <vector>
#include <sys/_types/_int32_t.h>
#include <sys/_types/_int64_t.h>

namespace ZeebeCpp {

struct ActivatedJobInfo {
    int64_t key;
    int64_t processInstanceKey;
    std::string bpmnProcessId;
    int64_t processDefinitionKey;
    int32_t processDefinitionVersion;
    std::string elementId;
    int64_t elementInstanceKey;
    std::string customHeaders;
    int32_t retries;
    int64_t deadline;
    std::string variables;
};

}

#endif // ZEEBE_JOB_H_