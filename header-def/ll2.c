#include "linklist.h"
#include "ll2.h"

int insert2() {
    linklist_append(2);
    linklist_append(2);
    linklist_append(2);
    return 0;
}

int print2() {
    linklist_print(&ll);
    return 0;
}

int free2() {
    linklist_free(&ll);
    return 0;
}
