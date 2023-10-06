include $(PROJ_HOME)/top.mk

# this allows sub-makes to find out if they have been invoked from this
# top-level make, or from a local make (from emacs in a source file directory,
# for example).
CALLED_FROM_TOP = true
export CALLED_FROM_TOP
    
all :
        cd dir1/src;          $(MAKE)
        cd dir2/rtv;          $(MAKE) debug=$(debug) etc