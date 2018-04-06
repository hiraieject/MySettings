

##
## リビジョン指定の仕方
##   make newtree REV="-r 4007"
## リビジョン番号は、SVNメールのフォルダで、version_info.h を検索する
##

##include .targetsetting

all:
	@echo make "newtree|newsrc|compile_all|image"

newtree:
##	@if [ -d `cat .targetdate`_`cat .targetfolder` ] ; then \
##		echo "	================================================="; \
##		echo "	today's tree `cat .targetdate`_`cat .targetfolder` is exist"; \
##		echo "	try \"make remove_current_tree\""; \
##		echo "	================================================="; \
##		exit 1; \
##	fi
	echo $(SVNBASE) > .svnbase
	echo $(SVNFOLDER) > .svnfolder
	echo $(SVNTARGET) > .targetfolder
	make REV="$(REV)" _newtree

newsrc:
##	@if [ -d `cat .targetdate`_`cat .targetfolder` ] ; then \
##		echo "	================================================="; \
##		echo "	today's tree `cat .targetdate`_`cat .targetfolder` is exist"; \
##		echo "	try \"make remove_current_tree\""; \
##		echo "	================================================="; \
##		exit 1; \
##	fi
	echo $(SVNBASE) > .svnbase
	echo $(SVNFOLDER) > .svnfolder
	echo $(SVNTARGET) > .targetfolder
	make REV="$(SVNREVISION)" _newsrc

remove_current_tree:
	sudo rm -rf `cat .targetdate`_`cat .targetfolder`

## ===============================================

_newsrc:
	date +%y%m%d  > .targetdate
	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
ifeq ($(ARCH),aquamarine)
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)
endif

_newtree:
	make REV="$(REV)" _newsrc
	make compile_all

## ===============================================
##_newtree_get_src_cvs:
##	@if [ -d `cat .targetdate`_`cat .targetfolder` ] ; then \
##		echo "	================================================="; \
##		echo "	today's tree `cat .targetdate`_`cat .targetfolder` is exist"; \
##		echo "	try \"make remove_current_tree\""; \
##		echo "	================================================="; \
##		exit 1; \
##	fi
##
##	cvs -d ":pserver:hirai@asuka2:/usr/local/cvsroot" co -d `cat .targetdate`_`cat .targetfolder` `cat .targetcvs`
##
##_newsrc_lf_garnet:
##	@date +%y%m%d  > .targetdate
##	@echo "lf_garnet" > .targetcvs
##	@echo "lf_garnet" > .targetcvsdir
##	make _newtree_get_src_cvs
##	(cd `cat .targetdate`_`cat .targetfolder`; ./sym_link.sh)
##
##_newtree_lf_garnet:
##	make _newsrc_`cat .targetfolder`
##	make compile_all
##
## ===============================================

__compile:
	@(cd `cat .targetdate`_`cat .targetfolder` ; \
	  echo "make -C $(MAKEDIR) $(MAKETARGET)" > .build2.sh; \
	  chmod +x .build2.sh)
	@make MAKEDIR=. SCRIPT=../../.build2.sh __script
__script:
	@(cd `cat .targetdate`_`cat .targetfolder`; \
	 echo "#!/bin/bash" > .build.sh; \
	 echo $(BUILDENVARG1) >> .build.sh; \
	 echo "cd usr/src" >> .build.sh; \
	 echo $(BUILDENVARG2) >> .build.sh; \
	 echo "(cd $(MAKEDIR); $(SCRIPT))" >> .build.sh; \
	 echo "#############"; \
	 echo "#############"; \
	 echo "############# make -C $(MAKEDIR) $(MAKETARGET)"; \
	 echo "#############"; \
	 echo "#############"; \
	 bash .build.sh)

compile_all:
	make MAKEDIR=. MAKETARGET= __compile
ifeq ($(CHG_TOSHIBA),yes)
	make chg_toshiba
endif
	make image
	make chk_gtags
compile_AppSrc:
	@make backup_daily
	make MAKEDIR=. MAKETARGET=AppSrc __compile
	make chk_gtags
compile_PanaApps:
	@make backup_daily
	make MAKEDIR=. MAKETARGET=PanaApps __compile
	make chk_gtags
compile_userapps: compile_AppSrc

clean_AppSrc:
	make MAKEDIR=AppSrc MAKETARGET=full-clean __compile
clean_userapps: clean_AppSrc

compile_other:
	make MAKEDIR=AppSrc MAKETARGET=other __compile
	make MAKEDIR=AppSrc MAKETARGET=other-install __compile
##	$(MAKE) -C `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc other
##	$(MAKE) -C `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc other-install

clean_other:
	make MAKEDIR=AppSrc MAKETARGET=other_clean __compile
##	$(MAKE) -C `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc other-clean

distclean_other:
	make MAKEDIR=AppSrc MAKETARGET=other_distclean __compile
##	$(MAKE) -C `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc other-distclean

distclean_php:
	make MAKEDIR=AppSrc/php MAKETARGET=distclean __compile
##	$(MAKE) -C `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc/php distclean

distclean_lighttpd:
	make MAKEDIR=AppSrc/lighttpd MAKETARGET=distclean __compile
##	$(MAKE) -C `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc/lighttpd distclean
##	make compile_all MODULE=AppSrc

clean_padp:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; \
	 find . -name \*.o -exec rm \{} \; ; \
	 find . -name \*.d -exec rm \{} \; )
compile_padp:
	@make backup_daily
	make clean_padp
	make MAKEDIR=. MAKETARGET=padp __compile
	make chk_gtags

clean_lpad:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; \
	 find . -name \*.o -exec rm \{} \; ; \
	 find . -name \*.d -exec rm \{} \; ; \
	 find . -name \*.a -exec rm \{} \; ; \
	 find . -name \*.lib -exec rm \{} \; ; \
	 find . -name \lpad* -exec rm \{} \; ; \
	 svn up )
compile_lpad:
	@make backup_daily
##	make clean_lpad
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec/appli; \
	 rm -f tks_dtv/build/boot/lpad* ./tks_dtv/build/common_us/BLD_lx_common_us/lpad*)
	make MAKEDIR=. SCRIPT=./lpad_make.sh __script
	make chk_gtags
	make tftp
compile_dtvrec:
	@make compile_lpad

compile_samba:
##	make distclean_samba
	make MAKEDIR=AppSrc MAKETARGET=samba-compile __compile
distclean_samba:
	make MAKEDIR=AppSrc/samba MAKETARGET=distclean __compile
compile_uuid:
##	make distclean_samba
	make MAKEDIR=AppSrc MAKETARGET=uuid-compile __compile
distclean_uuid:
	make MAKEDIR=AppSrc/uuid MAKETARGET=distclean __compile
procps_compile:
##	make distclean_samba
	make MAKEDIR=AppSrc/procps MAKETARGET= __compile
distclean_procps:
	make MAKEDIR=AppSrc/procps MAKETARGET=distclean __compile

compile_ncurses:
##	make distclean_samba
	make MAKEDIR=AppSrc/ncurses MAKETARGET= __compile
distclean_ncurses:
	make MAKEDIR=AppSrc/ncurses MAKETARGET=distclean __compile

kernel_menuconfig:
	make MAKEDIR=linux-2.6.32-sLDx MAKETARGET=menuconfig __compile
kernel_distclean:
	make MAKEDIR=linux-2.6.32-sLDx MAKETARGET=distclean __compile

compile_ui_test:
	make MAKEDIR=dtvrec/appli/tks_dtv/ui MAKETARGET=ui_test __compile
#	make image
#	make tftp

install_gdb:
	cp 171116_sf2hr4620_wlan/usr/local/bin/gdb* `cat .targetdate`_`cat .targetfolder`/usr/local/bin

rootfs:
	make MAKEDIR=. MAKETARGET="rootfs" __compile
rom:
ifeq ($(ARCH),garnet)
	make MAKEDIR=. MAKETARGET="rom rootfs u-boot-script rootfs arigato" __compile
endif
ifeq ($(ARCH),aquamarine)
	make MAKEDIR=../rom MAKETARGET= __compile
	make MAKEDIR=. MAKETARGET=upg __compile
endif
	make tftp
image:
	@make rom

gtags:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc; gtags)
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; gtags)
	if [ -d `cat .targetdate`_`cat .targetfolder`/usr/src/PanaApps ] ; then \
		(cd `cat .targetdate`_`cat .targetfolder`/usr/src/PanaApps; gtags); \
	fi
chk_gtags:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc; \
	 if [ ! -f GTAGS ] ; then \
	 	gtags; \
	 fi)
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; \
	 if [ ! -f GTAGS ] ; then \
	 	gtags; \
	 fi)
	if [ -d `cat .targetdate`_`cat .targetfolder`/usr/src/PanaApps ] ; then \
		(cd `cat .targetdate`_`cat .targetfolder`/usr/src/PanaApps; \
	 	 if [ ! -f GTAGS ] ; then \
	 		gtags; \
	 	 fi); \
	fi
clean_gtags:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc; rm -f G*)
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; rm -f G*)


tftp:
	mkdir -p /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/rom/* /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/target/uImage /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/target/*.rom /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/target/*.bin /var/lib/tftpboot/`cat .targetfolder`


signage_copyback:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc/userApps/cgi_wrapper; make signage_copyback)



chg_toshiba:
	if [ ! -f `cat .targetdate`_`cat .targetfolder`/.chg_toshiba ] ; then \
	   (cd `cat .targetdate`_`cat .targetfolder`; \
	    echo -n "pwd="; pwd; \
	    tar xvfz $(HOME)/aquam/toshiba_after.tgz; \
	    touch .chg_toshiba); \
	   make MAKEDIR=linux MAKETARGET=clean __compile; \
	   make MAKEDIR=. MAKETARGET= __compile; \
	fi


## set crontab
## 0 10,12,14,16,18,20,22 * * * (cd /home/hirai/sf2; make backup_every_hour > .backup_every_hour_log)
## 0,10,20,30,40,50 8,9 * * * (cd /home/hirai/sf2; make backup_daily > .backup_daily_log)

backup_daily_tar:
	mkdir -p backup
	(cd `cat .targetdate`_`cat .targetfolder`; \
	 svn diff usr/src/AppSrc usr/src/dtvrec > .diff_daily.txt; \
	 echo .diff_daily.txt > .daily_files.txt; \
	 find usr/src/AppSrc -name \*.c >> .daily_files.txt; \
	 find usr/src/dtvrec -name \*.c >> .daily_files.txt; \
	 find usr/src/AppSrc -name \*.cc >> .daily_files.txt; \
	 find usr/src/dtvrec -name \*.cc >> .daily_files.txt; \
	 find usr/src/AppSrc -name \*.h >> .daily_files.txt; \
	 find usr/src/dtvrec -name \*.h >> .daily_files.txt; \
	 find usr/src/AppSrc -name \*.sh >> .daily_files.txt; \
	 find usr/src -name \*.php >> .daily_files.txt; \
	 find usr/src -name \*.conf >> .daily_files.txt; \
	 find usr/src -name \?akefile >> .daily_files.txt; \
	 echo $$HOME/garnet/Makefile >> .daily_files.txt; \
	 tar cvfz ../backup/`cat ../.backup_daily_datetime`00_daily.tar.gz -T .daily_files.txt)
	-find backup/ -mtime +20 -exec rm -f \{} \;
	make gtags
backup_daily:
	mkdir -p backup
	date +%y%m%d  > .backup_daily_datetime
	if [ ! -f backup/`cat .backup_daily_datetime`00_daily.tar.gz ] ; then \
		touch backup/`cat .backup_daily_datetime`00_daily.tar.gz; \
		make  backup_daily_tar; \
	fi

backup_every_hour_tar:
	mkdir -p backup
	(cd `cat .targetdate`_`cat .targetfolder`; \
	 svn diff usr/src/AppSrc usr/src/dtvrec > .diff_hour.txt; \
	 echo .diff_hour.txt > .daily_files.txt; \
	 find usr/src -mmin -121 -name \*.c > .files.txt; \
	 find usr/src -mmin -121 -name \*.cc > .files.txt; \
	 find usr/src -mmin -121 -name \*.h >> .files.txt; \
	 find usr/src -mmin -121 -name \*.sh >> .files.txt; \
	 find usr/src -mmin -121 -name \*.php >> .files.txt; \
	 find usr/src -mmin -121 -name \*.conf >> .files.txt; \
	 find usr/src -mmin -121 -name \?akefile >> .files.txt; \
	 echo $$HOME/garnet/Makefile >> .files.txt; \
	 touch .dummy; \
	 tar cvfz ../backup/`cat ../.backup_every_hour_datetime`_modified.tar.gz -T .files.txt)
backup_every_hour:
	date +%y%m%d%H  > .backup_every_hour_datetime
	if [ ! -f backup/`cat .backup_every_hour_datetime`_modified.tar.gz ] ; then \
		make  backup_every_hour_tar; \
	fi


mk_branch:
	svn copy -r686 \
		https://FP.svn.vserv.jp.panasonic.com/repos/MAIN/LF8/trunk/lfe8 \
		https://FP.svn.vserv.jp.panasonic.com/repos/MAIN/LF8/branches/lfe8r686_contents_up \
		-m "Make branche for contents upload, base r686"



svnci:
	(cd `cat .targetdate`_`cat .targetfolder`; svn ci \
		usr/src/dtvrec/appli/tks_dtv/mp \
		usr/src/dtvrec/appli/tks_dtv/ui \
		usr/src/dtvrec/appli/tks_dtv/mon \
		usr/src/AppSrc/userApps/script_files/lighttpd.sh \
		usr/src/AppSrc/userApps/serialcomm \
		usr/src/AppSrc/userApps/inc \
		usr/src/AppSrc/userApps/api \
		usr/src/AppSrc/userApps/sysmgr \
		usr/src/AppSrc/userApps/PHP_Interface \
		usr/src/AppSrc/make.rules \
		usr/src/AppSrc/Makefile \
		usr/src/AppSrc/lighttpd \
		usr/rom/CONTENTS.TXT \
	)

_mk_ref_tree:
	mkdir -p bak
	if [ -d bak/$(DIR) ] ; then \
		(cd bak; sudo rm -rf $(DIR)); \
	fi
	if [ -d $(DIR) ] ; then \
		chmod +w $(DIR); \
		mv $(DIR) bak/$(DIR); \
	fi
	svn co $(SVNREVISION) $(URL) $(DIR)
	if [ -d $(DIR)/ArchiveFiles ] ; then \
		(cd $(DIR)/ArchiveFiles; rm -f CPU_* build_* cs_root* dcchd_* mrua* smp86xx_*;) \
	fi
	chmod -R a-w $(DIR)

_mk_ref_tree_cvs:
	mkdir -p bak
	if [ -d bak/$(DIR) ] ; then \
		(cd bak; sudo rm -rf $(DIR)); \
	fi
	if [ -d $(DIR) ] ; then \
		chmod +w $(DIR); \
		mv $(DIR) bak/$(DIR); \
	fi
	cvs -d $(URL) co $(SVNREVISION) -d $(DIR) $(TARGET)
	if [ -d $(DIR)/ArchiveFiles ] ; then \
		(cd $(DIR)/ArchiveFiles; rm -f CPU_* build_* cs_root* dcchd_* mrua* smp86xx_*;) \
	fi
	chmod -R a-w $(DIR)

## ===============================================
BF1_SVNBASE=https://fp.svn.vserv.jp.panasonic.com/repos/PF/SIGMA
MZ670_SVNBASE=https://co-dev-networkpf.svn.vserv.jp.panasonic.com/repos/iMX6/products/MZ670/trunk
reference:
#	make _mk_ref_tree  REV=-r464 URL=$(JW230_SVNBASE)/branches/NEW_MULTI_LIVE_KENTOU DIR=jw230.NEW_MULTI_LIVE_KENTOU.r464.latest
#	make _mk_ref_tree  REV=-r102 URL=$(JW230_SVNBASE)/branches/NEW_MULTI_LIVE_KENTOU DIR=jw230.NEW_MULTI_LIVE_KENTOU.r102.oldest
#	make _mk_ref_tree  REV=-r194 URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.r194.1102_pairing_qrcode
#	make _mk_ref_tree  REV=-r488 URL=$(JW230_SVNBASE)/branches/NEW_MULTI_LIVE_KENTOU_revB DIR=jw230.NEW_MULTI_LIVE_KENTOU_revB.r488.mms_kashidashi_rom
#	make _mk_ref_tree  REV=-r290 URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.r290.last_week
#	make _mk_ref_tree  REV= URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.latest
#	make _mk_ref_tree  REV=-r URL=$(JW230_SVNBASE)/trunk DIR=jw230.trunk.latest

#	make _mk_ref_tree  REV= URL=$(JW230_SVNBASE)/tags/JX200_v182 DIR=JX200_v182
#	make _mk_ref_tree  REV= URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.latest
#	make _mk_ref_tree  REV= URL=$(BF1_SVNBASE)/trunk/bf1nw DIR=bf1nw.trunk.latest
#	make _mk_ref_tree  REV= URL=$(MZ670_SVNBASE)/trunk DIR=mz670.trunk.latest
#	make _mk_ref_tree_cvs  REV= URL=":pserver:hirai@asuka2:/usr/local/cvsroot" TARGET=sigma_lfbc70 DIR=sigma_lfbc70
#	make _mk_ref_tree_cvs  REV= URL=":pserver:hirai@asuka2:/usr/local/cvsroot" TARGET=sigma_kernel DIR=sigma_kernel
#	make _mk_ref_tree_cvs  REV= URL=":pserver:hirai@asuka2:/usr/local/cvsroot" TARGET=sigma_oss DIR=sigma_oss
#	mkdir -p sigma
	make _mk_ref_tree_cvs  REV= URL=":pserver:hirai@asuka2:/usr/local/cvsroot" TARGET=lf_garnet DIR=lf_garnet_trunk

archive:
	@(cd `cat .targetdate`_`cat .targetfolder`; \
	  tar cvfz ../lighttpd_verup.tar.gz \
		usr/rom/CONTENTS.TXT \
		usr/src/AppSrc/lighttpd/diff_lighttpd*.txt \
		usr/src/AppSrc/lighttpd/Makefile \
		usr/src/AppSrc/lighttpd/makediff.sh \
		usr/src/AppSrc/lighttpd/lighttpd-1.4.45.tar.gz)
	@(cd `cat .targetdate`_`cat .targetfolder`; \
	  tar cvfz ../valgrind_gdb_build.tar.gz \
		usr/rom/CONTENTS.TXT \
		usr/src/AppSrc/Makefile \
		usr/src/AppSrc/termcap/Makefile \
		usr/src/AppSrc/termcap/*.tar.gz \
		usr/src/AppSrc/ncurses/Makefile \
		usr/src/AppSrc/ncurses/*.tar.gz \
		usr/src/AppSrc/gdb/Makefile \
		usr/src/AppSrc/gdb/*.tar.gz \
		usr/src/AppSrc/valgrind/Makefile \
		usr/src/AppSrc/valgrind/*.tar.bz2)








JW230_SVNBASE=https://jw230-wpf.svn.vserv.jp.panasonic.com/repos
VZ575N_SVNBASE=https://vz575n-nt.svn.vserv.jp.panasonic.com/repos
VZ585N_SVNBASE=https://networkpf.svn.vserv.jp.panasonic.com/repos/Sigma/products/VZ585N
2017GARNET_SVNBASE=https://fp.svn.vserv.jp.panasonic.com/repos/MAIN/2017Garnet
LF8_SVNBASE=https://fp.svn.vserv.jp.panasonic.com/repos/MAIN/LF8


_newsrc_aquam:
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
#	svn co $(SVNREVISION) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	mkdir -p `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`; \
	 sudo tar xvfz ../src_170526/devfiles.tgz; \
	 sudo tar xvfz ../src_170526/ph1_dtv_Aquamarine_V0002_20170317.tgz; \
	 sudo chown -R hirai.hirai ph1; \
	 sudo mv ph1/* .)
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)

_newsrc_sf2:
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
	svn co $(SVNREVISION) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`

_newsrc_lfe8:
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(LF8_SVNBASE)" > .svnbase
	svn co `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`

_newtree_lfe8 _newtree_sf2:
	make _newsrc_`cat .targetfolder`
	make compile_all
##	make image

newsrc_sf2hr4620_wlan:
	echo 'sf2hr4620_wlan' > .targetfolder
	basename `pwd` > .tksname
	date +%y%m%d  > .targetdate
	echo "branches" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
	svn co $(SVNREVISION) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)
newtree_sf2hr4620_wlan:
	make newsrc_sf2hr4620_wlan
	make compile_all

newsrc_sf2hr4620_panaapp:
	echo 'sf2hr4620_panaapp' > .targetfolder
	basename `pwd` > .tksname
	date +%y%m%d  > .targetdate
	echo "branches" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
	svn co $(SVNREVISION) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)
newtree_sf2hr4620_panaapp:
	make newsrc_sf2hr4620_panaapp
	make compile_all


