################################################################################
# Makefile
################################################################################

# Makefile by fletcher97
# Version: 2

# This makefile can be copied to a directory and it will generate the file
# structure and initialize a git repository with the .init rule. Any variables
# and rules for the specifique project can be added in the appropriate section.

################################################################################
# Project Variables
################################################################################

# Name of a single binary. Add as many variables as required by the project
NAME1 := a
NAME2 := b

# The names of all the binaries. Add aditional variables created above separated
# by space.
NAMES := ${NAME1} ${NAME2}

################################################################################
# Configs
################################################################################

# Verbose levels
# 0: Make will be totaly silenced
# 1: Make will print echos and printf
# 2: Make will not be silenced but target commands will not be printed
# 3: Make will print each command
# 4: Make will print all debug info
#
# If no value is specified or an incorrect value is given make will print each
# command like if VERBOSE was set to 3.
VERBOSE := 1

################################################################################
# Compiler & Flags
################################################################################

CC := gcc

CFLAGS := -Wall -Wextra -Werror -Wvla
DFLAGS := -g
SANITIZE := -fsanitize=address

################################################################################
# Root Folders
################################################################################

BIN_ROOT := bin/
DEP_ROOT := dep/
INC_ROOT := inc/
LIB_ROOT := lib/
OBJ_ROOT := obj/
SRC_ROOT := src/

################################################################################
# Content Folders
################################################################################

# Lists of ':' separated folders inside SRC_ROOT containing source files. Each
# folder needs to end with a '/'. The path to the folders is relative to
# SRC_ROOTIf SRC_ROOT contains files './' needs to be in the list. Each list is
# separated by a space or by going to a new line and adding onto the var.
# Exemple:
# DIRS := folder1/:folder2/
# DIRS += folder1/:folder3/:folder4/
DIRS := a/
DIRS += b/

SRC_DIRS_LIST := $(addprefix ${SRC_ROOT},${DIRS})
SRC_DIRS_LIST := $(foreach dl,${SRC_DIRS_LIST},$(subst :,:${SRC_ROOT},${dl}))

SRC_DIRS = $(call rmdup,$(subst :,${SPACE},${SRC_DIRS_LIST}))
OBJ_DIRS = $(subst ${SRC_ROOT},${OBJ_ROOT},${SRC_DIRS})
DEP_DIRS = $(subst ${SRC_ROOT},${DEP_ROOT},${SRC_DIRS})

# List of folders with header files.Each folder needs to end with a '/'. The
# path to the folders is relative to the root of the makefile. Library includes
# can be specified here.
INC_DIRS := ${INC_ROOT} ${LIBFT_INC}

################################################################################
# Files
################################################################################

SRCS_LIST = $(foreach dl,${SRC_DIRS_LIST},$(subst ${SPACE},:,$(strip $(foreach\
	dir,$(subst :,${SPACE},${dl}),$(wildcard ${dir}*.c)))))
OBJS_LIST = $(subst ${SRC_ROOT},${OBJ_ROOT},$(subst .c,.o,${SRCS_LIST}))

SRCS = $(foreach dir,${SRC_DIRS},$(wildcard ${dir}*.c))
OBJS = $(subst ${SRC_ROOT},${OBJ_ROOT},${SRCS:.c=.o})
DEPS = $(subst ${SRC_ROOT},${DEP_ROOT},${SRCS:.c=.d})

INCS := ${addprefix -I,${INC_DIRS}}

BINS := ${addprefix ${BIN_ROOT},${NAMES}}

################################################################################
# Libraries
################################################################################

# Libft
LIBFT_ROOT := ${LIB_ROOT}libft/
LIBFT_INC := ${LIBFT_ROOT}inc/
LIBFT := ${LIBFT_ROOT}bin/libft.a

#LIBS := -L${LIBFT_ROOT}bin -lft

################################################################################
# Conditions
################################################################################

ifeq ($(shell uname), Linux)
	SED := sed -i.tmp --expression
	SED_END := && rm -f $@.tmp
else ifeq ($(shell uname), Darwin)
	SED := sed -i.tmp
	SED_END := && rm -f $@.tmp
endif

ifeq ($(VERBOSE),0)
	MAKEFLAGS += --silent
	BLOCK := &>/dev/null
else ifeq ($(VERBOSE),1)
	MAKEFLAGS += --silent
else ifeq ($(VERBOSE),2)
	AT := @
else ifeq ($(VERBOSE),4)
	MAKEFLAGS += --debug=v
endif

################################################################################
# VPATHS
################################################################################

vpath %.o $(OBJ_ROOT)
vpath %.h $(INC_ROOT)
vpath %.c $(SRC_DIRS)
vpath %.d $(DEP_DIRS)

################################################################################
# Project Target
################################################################################

all: ${BINS}

.SECONDEXPANSION:
${BIN_ROOT}${NAME1}: $$(call get_files,$${@F},$${OBJS_LIST})
	${AT}printf "\033[33m[CREATING ${@F}]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${@D} ${BLOCK}
	${AT}${CC} ${CFLAGS} ${INCS} $(call get_files,${@F},${OBJS_LIST}) ${LIBS}\
		-o $@ ${BLOCK}

${BIN_ROOT}${NAME2}: $$(call get_files,$${@F},$${OBJS_LIST})
	${AT}printf "\033[33m[CREATING ${@F}]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${@D} ${BLOCK}
	${AT}${CC} ${CFLAGS} ${INCS} $(call get_files,${@F},${OBJS_LIST}) ${LIBS}\
		-o $@ ${BLOCK}

################################################################################
# Clean Targets
################################################################################

clean:
	${AT}printf "\033[38;5;1m[REMOVING OBJECTS]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${OBJ_ROOT} ${BLOCK}
	${AT}find ${OBJ_ROOT} -type f -name "*.o" -delete ${BLOCK}

fclean: clean
	${AT}printf "\033[38;5;1m[REMOVING BINARIES]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${BIN_ROOT} ${BLOCK}
	${AT}find ${BIN_ROOT} -type f\
		$(addprefix "-name ",${NAMES}) -delete ${BLOCK}

clean_dep:
	${AT}printf "\033[38;5;1m[REMOVING DEPENDENCIES]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${DEP_ROOT} ${BLOCK}
	${AT}find ${DEP_ROOT} -type f -name "*.d" -delete ${BLOCK}

clean_all: fclean clean_dep

re: fclean all

################################################################################
# Debug Targets
################################################################################

debug_asan: CFLAGS += ${DFLAGS} ${SANITIZE}
debug_asan: all

debug: CFLAGS += ${DFLAGS}
debug: all

debug_re: fclean debug

################################################################################
# Utility Targets
################################################################################

.init:
	${AT}printf "\033[33m[CREATING FOLDER STRUCTURE]\033[0m\n" ${BLOCK}
	${AT}mkdir -p ${BIN_ROOT} ${BLOCK}
	${AT}mkdir -p ${DEP_ROOT} ${BLOCK}
	${AT}mkdir -p ${INC_ROOT} ${BLOCK}
	${AT}mkdir -p ${OBJ_ROOT} ${BLOCK}
	${AT}mkdir -p ${SRC_ROOT} ${BLOCK}
	${AT}mkdir -p ${TESTS_ROOT} ${BLOCK}
	${AT}printf "\033[33m[INITIALIZING GIT REPOSITORY]\033[0m\n" ${BLOCK}
	${AT}git init ${BLOCK}
	${AT}echo "*.o\n*.d\n.vscode\na.out\n.DS_Store" > .gitignore ${BLOCK}
	${AT}date > $@ ${BLOCK}
	${AT}printf "\033[33m[CREATING FIRST COMMIT]\033[0m\n" ${BLOCK}
	${AT}git add .gitignore ${BLOCK}
	${AT}git add $@ ${BLOCK}
	${AT}git add Makefile ${BLOCK}
	${AT}git commit -m "init" ${BLOCK}

################################################################################
# .PHONY
################################################################################

.PHONY : clean fclean clean_dep clean_all re all

################################################################################
# Constantes
################################################################################

NULL =
SPACE = ${NULL} #

################################################################################
# Functions
################################################################################

# Get the index of a given word in a list
_index = $(if $(findstring $1,$2),$(call _index,$1,\
	$(wordlist 2,$(words $2),$2),x $3),$3)
index = $(words $(call _index,$1,$2))

# Get value at the same index
lookup = $(word $(call index,$1,$2),$3)

# Remove duplicates
rmdup = $(if $1,$(firstword $1) $(call rmdup,$(filter-out $(firstword $1),$1)))

# Get files for a specific binary
get_files = $(subst :,${SPACE},$(call lookup,$1,${NAMES},$2))

################################################################################
# Target Templates
################################################################################

define make_bin
${1} : ${2}
endef

define make_obj
${1} : ${2} ${3}
	$${AT}printf "\033[38;5;14m[OBJ]: \033[38;5;47m$$@\033[0m\n" $${BLOCK}
	$${AT}mkdir -p $${@D} $${BLOCK}
	$${AT}$${CC} $${CFLAGS} $${INCS} -c $$< -o $$@ $${BLOCK}
endef

define make_dep
${1} : ${2}
	$${AT}printf "\033[38;5;13m[DEP]: \033[38;5;47m$$@\033[0m\n" $${BLOCK}
	$${AT}mkdir -p $${@D} $${BLOCK}
	$${AT}$${CC} -MM $$< $${INCS} -MF $$@ $${BLOCK}
	$${AT}$${SED} 's|:| $$@ :|' $$@ $${SED_END} $${BLOCK}
	$${AT}$${SED} '1 s|^|$${@D}/|' $$@ $${SED_END} $${BLOCK}
	$${AT}$${SED} '1 s|^$${DEP_ROOT}|$${OBJ_ROOT}|' $$@ $${SED_END} $${BLOCK}
endef

################################################################################
# Target Generator
################################################################################

$(foreach bin,${BINS},$(eval\
$(call make_bin,$(notdir ${bin}),${bin})))

$(foreach src,${SRCS},$(eval\
$(call make_dep,$(subst ${SRC_ROOT},${DEP_ROOT},${src:.c=.d}),${src})))

$(foreach src,${SRCS},$(eval\
$(call make_obj,$(subst ${SRC_ROOT},${OBJ_ROOT},${src:.c=.o}),\
${src},\
$(subst ${SRC_ROOT},${DEP_ROOT},${src:.c=.d}))))

################################################################################
# Includes
################################################################################

-include ${DEPS}
