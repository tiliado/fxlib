PROJECT=fxlib

# DIRS #
# ==== #

PEBBLE_DIR = pebble
PEBBLE_DEST = build/pebble
PEBBLE_SRC = $(PEBBLE_DEST)/src/c
PEBBLE_INCLUDE = $(PEBBLE_DEST)/include

# SOURCES #
# ======= #

BASE_FILES = README.md LICENSE
PEBBLE_FILES = $(wildcard $(PEBBLE_DIR)/*)
C_FILES = $(wildcard $(PROJECT)/*.c)
H_FILES = $(wildcard $(PROJECT)/*.h)

# PEBBLE PACKAGE #
# ============== #

PBL_C_FILES = $(patsubst $(PROJECT)/%,$(PEBBLE_SRC)/%,$(C_FILES))
PBL_H_FILES = $(patsubst $(PROJECT)/%,$(PEBBLE_INCLUDE)/%,$(H_FILES))
PBL_BASE_FILES = $(patsubst %,$(PEBBLE_DEST)/%,$(BASE_FILES))
PBL_PEBBLE_FILES = $(patsubst $(PEBBLE_DIR)/%,$(PEBBLE_DEST)/%,$(PEBBLE_FILES))
PBL_ALL_FILES = $(PBL_C_FILES) $(PBL_H_FILES) $(PBL_PEBBLE_FILES) $(PBL_BASE_FILES)
PBL_DIST_ZIP = $(PEBBLE_DEST)/dist.zip

# RULES #
# ===== #

all: $(PBL_DIST_ZIP)

$(PEBBLE_SRC)/%.c: $(PROJECT)/%.c | $(PEBBLE_SRC)
	cp -v $< $@

$(PEBBLE_INCLUDE)/%.h: $(PROJECT)/%.h | $(PEBBLE_INCLUDE)
	cp -v $< $@

$(PEBBLE_DEST)/%: ./% | $(PEBBLE_DEST)
	cp -v $< $@
	
$(PEBBLE_DEST)/%: $(PEBBLE_DIR)/% | $(PEBBLE_DEST)
	cp -v $< $@

$(PEBBLE_DEST):
	mkdir -p $@
	
$(PEBBLE_SRC):
	mkdir -p $@

$(PEBBLE_INCLUDE):
	mkdir -p $@

$(PBL_DIST_ZIP): $(PBL_ALL_FILES)
	test -e "$(PEBBLE_DEST)/$(PROJECT)" || ln -sv ./include $(PEBBLE_DEST)/$(PROJECT)
	test -e "$(PEBBLE_DEST)/src/$(PROJECT)" || ln -sv ./c $(PEBBLE_DEST)/src/$(PROJECT)
	cd $(PEBBLE_DEST) && pebble build

pebble-build: $(PBL_DIST_ZIP)
	tree build/pebble
pebble-install: pebble-build
	@echo Run \"pebble package install `pwd`/$(PEBBLE_DEST)\" in your project

pebble-clean:
	rm -rfv $(PEBBLE_DEST)

clean:
	rm -rfv build
