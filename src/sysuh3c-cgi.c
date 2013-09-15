#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic/cgic.h"

void gen_page(const char * fname) {
    if (fname == NULL) return;

    static const char *src_path = "/www/sysuh3c-cgi";
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
    
    if (strncmp(cgiRequestMethod, "GET", 3) == 0) {
        FILE * fp = fopen("/var/run/sysuh3c.pid", "r");
        if (fp) {
            gen_page("logoff.html");
            fclose(fp);
        }
        else
            gen_page("login.html");
    }
    else {
        cgiHeaderStatus(403, "Method Not Allowed");
    }
    return 0;
}
