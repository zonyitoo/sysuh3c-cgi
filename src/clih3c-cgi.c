#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic/cgic.h"

void gen_loginpage(int show) {
    cgiHeaderContentType("text/html");
    fprintf(cgiOut, "<html>");
    fprintf(cgiOut, "<head>");
    fprintf(cgiOut, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" >");
    fprintf(cgiOut, "<meta id=\"viewport\" name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;\"> ");
    fprintf(cgiOut, "<meta content=\"telephone=no\" name=\"format-detection\"> ");
    fprintf(cgiOut, "</head>");
    fprintf(cgiOut, "<body>");
    fprintf(cgiOut, "<h1>CLIH3C</h1>");

    if (show == 1)
        fprintf(cgiOut, "<h2> SUCCESS </h2>");
    else if (show == 2)
        fprintf(cgiOut, "<h2> FAILED </h2>");

    fprintf(cgiOut, "<form method=\"POST\" enctype=\"multipart/form-data\" action=\"/cgi-bin/clih3c.cgi\"> ");
    fprintf(cgiOut, "<p>NetID <input type=\"text\" name=\"name\"> </p> ");
    fprintf(cgiOut, "<p>Password <input type=\"password\" name=\"passwd\"> </p> ");
    fprintf(cgiOut, "<input type=\"submit\" name=\"login\" value=\"Login\"> ");
    fprintf(cgiOut, "</form>");
    fprintf(cgiOut, "</body>");
    fprintf(cgiOut, "</html>");
}

void gen_logoffpage() {
    cgiHeaderContentType("text/html");
    fprintf(cgiOut, "<html>");
    fprintf(cgiOut, "<head>");
    fprintf(cgiOut, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" >");
    fprintf(cgiOut, "<meta id=\"viewport\" name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;\"> ");
    fprintf(cgiOut, "</head>");
    fprintf(cgiOut, "<body>");
    fprintf(cgiOut, "<form method=\"POST\" enctype=\"multipart/form-data\" action=\"/cgi-bin/clih3c.cgi\"> ");
    fprintf(cgiOut, "<input type=\"submit\" name=\"logoff\" value=\"Logoff\">");
    fprintf(cgiOut, "</form>");
    fprintf(cgiOut, "</body>");
    fprintf(cgiOut, "</html>");
}

void gen_expirepage() {
    cgiHeaderContentType("text/html");
    fprintf(cgiOut, "<html>");
    fprintf(cgiOut, "<head>");
    fprintf(cgiOut, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" >");
    fprintf(cgiOut, "<meta id=\"viewport\" name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;\"> ");
    fprintf(cgiOut, "</head>");
    fprintf(cgiOut, "<body>");
    fprintf(cgiOut, "</body>");
    fprintf(cgiOut, "</html>");
}

void do_post() {
    if (cgiFormSubmitClicked("login") == cgiFormSuccess) {
        char name[17] = {0};
        char passwd[17] = {0};

        cgiFormStringNoNewlines("name", name, sizeof(name));
        cgiFormStringNoNewlines("passwd", passwd, sizeof(passwd));

        size_t namelen = strlen(name), pwdlen = strlen(passwd);
        if (namelen > 16 || namelen == 0 || pwdlen > 16 || pwdlen == 0) {
            gen_loginpage(2);
            return;
        }

        char cmd[64] = {0};
        snprintf(cmd, sizeof(cmd), "clih3c -u %s -p %s -d >> /dev/null", name, passwd);
        int ret = system(cmd);

        if (ret == 0) {
            gen_logoffpage();
        }
        else {
            gen_loginpage(2);
        }
    }
    else if (cgiFormSubmitClicked("logoff") == cgiFormSuccess) {
        system("clih3c -l");
        gen_loginpage(1);
    }
    else {
        cgiHeaderStatus(400, "Bad Request");
    }
}

void do_get() {
    FILE * clih3c_lock = fopen("/tmp/clih3c.lock", "r");
    if (clih3c_lock == NULL) {
        gen_loginpage(0);
    }
    else {
        gen_logoffpage();
        fclose(clih3c_lock);
    }
}

int cgiMain() {
    
    if (strncmp(cgiRequestMethod, "GET", 3) == 0) {
        do_get();
    }
    else if (strncmp(cgiRequestMethod, "POST", 4) == 0) {
        do_post();    
    }
    else {
        cgiHeaderStatus(403, "Method Not Allowed");
    }

    return 0;
}
