# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS} ${OPENSSL_INCLUDES} ${PROJ_INCLUDES} ${HDF5_INCLUDES} ${GEOMODELGRIDS_INCLUDES}
AM_LDFLAGS = ${LDFLAGS} ${OPENSSL_LDFLAGS} ${PROJ_LDFLAGS} ${HDF5_LDFLAGS} ${GEOMODELGRIDS_LDFLAGS}

TARGETS = sfcvm211_query libsfcvm211.a libsfcvm211.so

all: $(TARGETS)

install:
	mkdir -p ${prefix}
	mkdir -p ${prefix}/lib
	mkdir -p ${prefix}/include
	mkdir -p ${prefix}/bin
	cp libsfcvm211.so ${prefix}/lib
	cp libsfcvm211.a ${prefix}/lib
	cp sfcvm211.h ${prefix}/include
	cp sfcvm211_query ${prefix}/bin

libsfcvm211.a: sfcvm211_static.o cJSON.o 
	$(AR) rcs $@ $^

libsfcvm211.so: sfcvm211.o cJSON.o 
	$(CC) -shared $(AM_CFLAGS) -o libsfcvm211.so $^ $(AM_LDFLAGS)

sfcvm211.o: sfcvm211.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY $(AM_CFLAGS) -o $@ -c $^ 
	
sfcvm211_static.o: sfcvm211.c
	$(CC) $(AM_CFLAGS) -o $@ -c $^ 

sfcvm211_query.o: sfcvm211_query.c 
	$(CC) $(AM_CFLAGS) -o $@ -c $^ 

sfcvm211_query : sfcvm211_query.o libsfcvm211.a
	$(CC) -o $@ $^ $(AM_LDFLAGS)

cJSON.o: cJSON.c
	$(CC) -fPIC -DDYNAMIC_LIBRARY $(AM_CFLAGS) -o $@ -c $^ 
clean:
	rm -rf $(TARGETS)
	rm -rf *.o 

