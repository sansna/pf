#include "linklist.h"
#include "ll1.h"

int insert1() {
    linklist_append(1);
    linklist_append(1);
    linklist_append(1);
    return 0;
}

int print1() {
    linklist_print(&ll);
    return 0;
}

int free1() {
    linklist_free(&ll);
    return 0;
}
