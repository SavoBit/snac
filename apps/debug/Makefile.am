include ../../Make.vars 

EXTRA_DIST =\
	meta.xml

if PY_ENABLED
AM_CPPFLAGS += $(PYTHON_CPPFLAGS)
endif # PY_ENABLED 

pkglib_LTLIBRARIES =		\
	malloc_monitor.la

malloc_monitor_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/../ -I$(top_srcdir)/../ -I$(top_srcdir)/../../ -I$(top_srcdir)/../apps/
malloc_monitor_la_SOURCES = malloc_monitor.cc
malloc_monitor_la_LDFLAGS = -module -export-dynamic

NOX_RUNTIMEFILES = meta.xml	

all-local: nox-all-local
clean-local: nox-clean-local 
install-exec-hook: nox-install-local
