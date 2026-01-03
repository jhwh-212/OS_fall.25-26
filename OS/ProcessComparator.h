#ifndef PROCESS_COMPARATOR_H
#define PROCESS_COMPARATOR_H

#include <memory>
#include "Process.h"

/*
 * Preemptive Priority Scheduling Comparator
 * Lower numeric value = higher priority
 */
struct ProcessComparator {
    bool operator()(const std::shared_ptr<Process>& a,
                    const std::shared_ptr<Process>& b) const {
        return a->getPriority() > b->getPriority();
    }
};

#endif


