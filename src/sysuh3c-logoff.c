#include "cgic/cgic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int cgiMain() {

    if (strncmp(cgiRequestMethod, "POST", 4) == 0) {

        int ret = system("sysuh3c -l >> /dev/null");

        cgiHeaderContentType("application/json");
        if (ret == 0) {
            fprintf(cgiOut, "{\"err\": false, \"msg\": \"Logoff Success\"}");
        }
        else {
            fprintf(cgiOut, "{\"err\": true, \"msg\": \"Logoff Failed\"}");
        }

    }
    else {
        cgiHeaderStatus(403, "Method Not Allowed");
    }

    return 0;
}
