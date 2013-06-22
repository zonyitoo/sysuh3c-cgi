#include "cgic/cgic.h"
#include <stdlib.h>

void login_success() {

}

int cgiMain() {
    
    cgiHeaderContentType("text/html");

    if (cgiFormSubmitClicked("login") == cgiFormSuccess) {

        char name[17];
        char passwd[17];

        cgiFormStringNoNewlines("name", name, sizeof(name));
        cgiFormStringNoNewlines("passwd", passwd, sizeof(passwd));

        char cmd[50];
        sprintf(cmd, "clih3c -u %s -p %s -d", name, passwd);
        int ret = system(cmd);

        if (ret == 0) {
            login_success();
        }
        else {
            cgiHeaderLocation("/cgi-bin/clih3c-cgi?failed=1");
        }

    }

    return 0;

}
