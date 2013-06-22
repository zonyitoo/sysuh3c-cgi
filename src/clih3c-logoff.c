#include "cgic/cgic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void gen_page(const char * fname) {
    if (fname == NULL) return;

    static const char *src_path = "/www/clih3c-cgi";
    char fullpath[128] = {0};
    snprintf(fullpath, sizeof(fullpath), "%s/%s", src_path, fname);

    FILE * fp = fopen(fullpath, "r");
    if (fp == NULL) return;

    char buf[256] = {0};
    cgiHeaderContentType("text/html");
    while (fgets(buf, sizeof(buf), fp)) {
        fprintf(cgiOut, "%s", buf);
    }

    fclose(fp);
}

int cgiMain() {

    if (strncmp(cgiRequestMethod, "POST", 4) == 0) {

        int ret = system("clih3c -l >> /dev/null");

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
