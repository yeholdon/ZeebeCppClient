#ifndef ZEEBE_TASK_H_
#define ZEEBE_TASK_H_

#include <string>
#include <vector>
#include <sys/_types/_int32_t.h>
#include <sys/_types/_int64_t.h>

namespace ZeebeCpp {

struct TaskInfo {
    std::string typeName;
    int64_t timeout;
    int32_t maxJobsToActivate;
    std::vector<std::string> fetchVariables;
    int64_t requestTimeout;
};

}

#endif // ZEEBE_TASK_H_