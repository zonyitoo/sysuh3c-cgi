LIBS += -Lcgic -lcgic 

all: clih3c.cgi clih3c-login clih3c-logoff

libcgic.a:
	cd cgic && make libcgic.a

clih3c.cgi: clih3c-cgi.o libcgic.a 
	$(CC) -o $@ $< $(LIBS)

clih3c-login: clih3c-login.o libcgic.a
	$(CC) -o $@ $< $(LIBS)

clih3c-logoff: clih3c-logoff.o libcgic.a
	$(CC) -o $@ $< $(LIBS)

