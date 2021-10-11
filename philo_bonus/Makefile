APP			= philo

SRCEXT		= c
SRCDIR		= srcs
OBJDIR		= objs
BINDIR		= bin

SRCS		:= $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS		:= $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS		:= $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

UNAME		:= $(shell uname)
DEBUG		= -g
INCLUDES	= -I./includes
CFLAGS		= -Wall -Wextra -Werror -c $(DEBUG)
LDFLAGS		= -pthread #-fsanitize=address # -static-libasan

ifeq ($(SRCEXT), cpp)
CC			= $(CXX)
else
CFLAGS		+= -std=gnu99
endif

.PHONY:  all clean fclean re bonus

all : buildrepo $(BINDIR)/$(APP)
	
write_src_b : 
	@echo $(SRCS_B)

$(BINDIR)/$(APP): $(OBJS)
	@mkdir -p `dirname $@`
	@echo "$@..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.$(SRCEXT)
	@echo "Generating dependencies for $<..."
	@$(call make-depend, $<, $@, $(subst .o,.d,$@))
	@echo "Compiling $<..."
	@$(CC)  $(CFLAGS) $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) -r $(BINDIR)

re:	fclean all

buildrepo:
	@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef


usage: $(call make-depend,source-file,object-file,depend-file)
define make-depend
  $(CC) -MM       \
        -MF $3    \
        -MP       \
        -MT $2    \
        $(CFLAGS) \
        $1
endef