# Autoconf/automake file

# General compiler/linker flags
AM_CFLAGS = ${CFLAGS}
AM_FCFLAGS = ${FCFLAGS}
AM_LDFLAGS = ${LDFLAGS}

all:
if WITH_SFCVM211_LARGEDATA_DIR
	echo "USING WITH_SFCVM211_LARGEDATA_DIR in sfcvm211"
else
	if [ ! -d "sfcvm211" ]; then \
		./make_data_files.py; \
	fi
endif

install:
if WITH_SFCVM211_LARGEDATA_DIR
	if [ ! -d "${prefix}/data/sfcvm211" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		$(LN_S) -f $(SFCVM211_LARGEDATA_DIR) ${prefix}/data/sfcvm211; \
		echo "USING WITH_SFCVM211_LARGEDATA_DIR in sfcvm211"; \
	fi
	cp config ${prefix}/data
else
	if [ ! -d "${prefix}/data/sfcvm211" ]; then \
		$(MKDIR_P) ${prefix}/data; \
		mv sfcvm211 ${prefix}/data; \
		$(LN_S) -f ${prefix}/data/sfcvm211 .; \
	fi
	cp config ${prefix}/data
endif

clean:
	echo "clean"

dist-clean :
	rm -rf sfcvm211
