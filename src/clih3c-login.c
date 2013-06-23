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

void escape_arg(char * to, const char * from) {
    while (*from) {
        switch (*from) {
            case '\'':
            case '(':
            case ')':
            case '"':
            case '{':
            case '}':
            case '#':
            case ';':
            case '&':
            case '.':
            case '`':
            case ':':
            case '>':
            case '<':
            case '*':
            case '!':
            case '?':
            case '$':
            case '[':
            case ']':
            case ',':
            case '|':
            case '-':
            case '=':
            case '+':
            case '%':
            case '~':
            case '^':
                * to ++ = '\\';
            default:
                * to ++ = *from;
        }
        from ++;
    }
}

int cgiMain() {

    if (strncmp(cgiRequestMethod, "POST", 4) == 0) {

        char name[20] = {0};
        char passwd[20] = {0};

        cgiFormStringNoNewlines("name", name, sizeof(name));
        cgiFormStringNoNewlines("passwd", passwd, sizeof(passwd));

        size_t namelen, pwdlen;
        namelen = strlen(name);
        pwdlen = strlen(passwd);

        char esc_name[40] = {0};
        char esc_pwd[40] = {0};

        cgiHeaderContentType("application/json");
        if (namelen == 0 || namelen > 16 || pwdlen == 0 || pwdlen > 16) {
            fprintf(cgiOut, "{\"err\": true, \"msg\": \"Argument Error\"}");
            return 0;
        }
        
        escape_arg(esc_name, name);
        escape_arg(esc_pwd, passwd);

        char cmd[64] = {0};
        snprintf(cmd, sizeof(cmd), "clih3c -u %s -p %s -d >> /dev/null", esc_name, esc_pwd);
        int ret = system(cmd);

        if (ret == 0) {
            fprintf(cgiOut, "{\"err\": false, \"msg\": \"Login Success\"}");
        }
        else {
            fprintf(cgiOut, "{\"err\": true, \"msg\": \"Login Failed\"}");
        }

    }
    else {
        cgiHeaderStatus(403, "Method Not Allowed");
    }

    return 0;
}
