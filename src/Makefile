LIBS += -Lcgic -lcgic 

all: clih3c-cgi 

libcgic.a:
	cd cgic && make libcgic.a

clih3c-cgi: clih3c-cgi.o libcgic.a 
	$(CC) -o $@ $< $(LIBS)

