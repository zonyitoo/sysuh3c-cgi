LIBS += -Lcgic -lcgic 

all: sysuh3c.cgi sysuh3c-login sysuh3c-logoff

libcgic.a:
	cd cgic && make libcgic.a

sysuh3c.cgi: sysuh3c-cgi.o libcgic.a 
	$(CC) -o $@ $< $(LIBS)

sysuh3c-login: sysuh3c-login.o libcgic.a
	$(CC) -o $@ $< $(LIBS)

sysuh3c-logoff: sysuh3c-logoff.o libcgic.a
	$(CC) -o $@ $< $(LIBS)

