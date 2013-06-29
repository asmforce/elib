#
# @author: Vitaliy Krutko
# @e-mail: asmforce@ukr.net asmxforce@gmail.com
# @project: elib (external library)
# @target: elib-projects
#


MAKEFILE = makefile.windows

all: elib demo

elib: src/compiled
	cd ./src && make -f $(MAKEFILE) install

demo: demo/compiled
	cd ./demo && make -f $(MAKEFILE) install

src/compiled:
	cd ./src && make -f $(MAKEFILE) all

demo/compiled:
	cd ./demo && make -f $(MAKEFILE) all

sub-clean:
	cd ./src && make -f $(MAKEFILE) clean
	cd ./demo && make -f $(MAKEFILE) clean

clean: sub-clean
	cd ./src && make -f $(MAKEFILE) uninstall
	cd ./demo && make -f $(MAKEFILE) uninstall
