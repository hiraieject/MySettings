

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
	basename `pwd` > .targetfolder
	make REV="$(REV)" _newtree_`cat .targetfolder`
newsrc:
##	@if [ -d `cat .targetdate`_`cat .targetfolder` ] ; then \
##		echo "	================================================="; \
##		echo "	today's tree `cat .targetdate`_`cat .targetfolder` is exist"; \
##		echo "	try \"make remove_current_tree\""; \
##		echo "	================================================="; \
##		exit 1; \
##	fi
	basename `pwd` > .targetfolder
	make REV="$(REV)" _newsrc_`cat .targetfolder`

remove_current_tree:
	sudo rm -rf `cat .targetdate`_`cat .targetfolder`

## ===============================================

JW230_SVNBASE=https://jw230-wpf.svn.vserv.jp.panasonic.com/repos
VZ575N_SVNBASE=https://vz575n-nt.svn.vserv.jp.panasonic.com/repos
VZ585N_SVNBASE=https://networkpf.svn.vserv.jp.panasonic.com/repos/Sigma/products/VZ585N
2017GARNET_SVNBASE=https://fp.svn.vserv.jp.panasonic.com/repos/MAIN/2017Garnet
LF8_SVNBASE=https://fp.svn.vserv.jp.panasonic.com/repos/MAIN/LF8
2017AQUAM_SVNLOCAL=svn://192.168.0.86/repo/2017aquamarine
2018AQUAM_SVNBASE=https://fp.svn.vserv.jp.panasonic.com/repos/MAIN/2018Aqua
src_newsrc_aquam:
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
#	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	mkdir -p `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`; \
	 sudo tar xvfz ../src_170526/devfiles.tgz; \
	 sudo tar xvfz ../src_170526/ph1_dtv_Aquamarine_V0002_20170317.tgz; \
	 sudo chown -R hirai.hirai ph1; \
	 sudo mv ph1/* .; \
	 sudo mv ph1/.??* .)
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)
localsvn_newsrc_aquam:
	date +%y%m%d  > .targetdate
	echo "$(2017AQUAM_SVNLOCAL)" > .svnbase
	echo "branch" > .svnfolder
#	echo "ph1v0002" > .targetfolder
	echo "ph1v0500" > .targetfolder
	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)
official_newsrc_aquam:
	date +%y%m%d  > .targetdate
	echo "$(2018AQUAM_SVNBASE)" > .svnbase
	echo "trunk" > .svnfolder
	echo "startup" > .targetfolder
#	echo "branches" > .svnfolder
#	echo "startup_r4539" > .targetfolder
	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)

## \\10.78.112.116\common\開発資料\WM_LAN\10_2017_2_Aquamarine\SDK_v0500_add_net_comm
yama_newsrc_aquam:
	echo "yama" > .targetfolder
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
#	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	mkdir -p `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`; \
	 sudo tar xvfz ../ph1v0500_0804.tgz; \
	 sudo chown -R hirai.hirai ph1v0500; \
	 sudo mv ph1v0500/* .; \
	 sudo mv ph1v0500/.??* .)
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)

SDK_NEWSRC_ARCHIVE=sdk_ver0630_20171113/Aquamarine_V0630_20171113.tgz
SDK_NEWSRC_DEV_ARCHIVE=sdk_ver0630_20171113/Aquamarine_V0630_20171113_devfiles.tgz
sdk_newsrc_aquam:
	echo "sdk" > .targetfolder
	date +%y%m%d  > .targetdate
	mkdir -p `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`; \
	 sudo tar xvfz ../$(SDK_NEWSRC_ARCHIVE); \
	 sudo tar xvfz ../$(SDK_NEWSRC_DEV_ARCHIVE); \
	 sudo chown -R hirai.hirai ph1; \
	 sudo chmod -R og+rx ph1; \
	 sudo mv ph1/* .; \
	 sudo mv ph1/.??* .; \
	 sudo rmdir ph1)
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)

_newsrc_aquam:
#	make src_newsrc_aquam
#	make localsvn_newsrc_aquam
	make official_newsrc_aquam
#	make yama_newsrc_aquam

_newsrc_sf2:
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(2017GARNET_SVNBASE)" > .svnbase
	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`

_newsrc_lfe8:
	date +%y%m%d  > .targetdate
	echo "trunk" > .svnfolder
	echo "$(LF8_SVNBASE)" > .svnbase
	svn co `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`

_newtree_lfe8 _newtree_sf2 _newtree_aquam:
	make _newsrc_`cat .targetfolder`
	make compile_all
##	make image

newsrc_startupr5216_panaapp:
	echo 'startupr5216_panaapp' > .targetfolder
	basename `pwd` > .tksname
	date +%y%m%d  > .targetdate
	echo "branches" > .svnfolder
	echo "$(2018AQUAM_SVNBASE)" > .svnbase
	svn co $(REV) `cat .svnbase`/`cat .svnfolder`/`cat .targetfolder` `cat .targetdate`_`cat .targetfolder`
	(cd `cat .targetdate`_`cat .targetfolder`/tools; \
	 /bin/rm -f arm-2010q1; \
	 ln -s /opt/redhat/arm-2010q1 .)
newtree_startupr5216_panaapp:
	make newsrc_startupr5216_panaapp
	make compile_all
	make chg_toshiba


chg_toshiba:
	@(cd `cat .targetdate`_`cat .targetfolder`; \
	 echo -n "pwd="; pwd; \
	 tar xvfz ../toshiba_after.tgz)
	make MAKEDIR=linux MAKETARGET=clean __compile
	make MAKEDIR=. MAKETARGET=linux __compile
	make compile_all

## ===============================================

__compile:
	@(cd `cat .targetdate`_`cat .targetfolder`; \
	 echo "#!/bin/bash" > .build.sh; \
	 echo "source setup_env.sh" >> .build.sh; \
	 echo "cd usr/src" >> .build.sh; \
	 echo "source dtvrec/appli/tks_dtv/build/common/build_env lx arm ld6bref us" >> .build.sh; \
	 echo "make -C $(MAKEDIR) $(MAKETARGET)" >> .build.sh; \
	 echo "#############"; \
	 echo "#############"; \
	 echo "############# make -C $(MAKEDIR) $(MAKETARGET)"; \
	 echo "#############"; \
	 echo "#############"; \
	 bash .build.sh)
__script:
	@(cd `cat .targetdate`_`cat .targetfolder`; \
	 echo "#!/bin/bash" > .build.sh; \
	 echo "source setup_env.sh" >> .build.sh; \
	 echo "cd usr/src" >> .build.sh; \
	 echo "source dtvrec/appli/tks_dtv/build/common/build_env lx arm ld6bref us" >> .build.sh; \
	 echo "(cd $(MAKEDIR); $(SCRIPT))" >> .build.sh; \
	 echo "#############"; \
	 echo "#############"; \
	 echo "############# make -C $(MAKEDIR) $(MAKETARGET)"; \
	 echo "#############"; \
	 echo "#############"; \
	 bash .build.sh)

compile_all:
	make MAKEDIR=. MAKETARGET= __compile
	make image
#	make tftp
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

clean_kernel:
	make MAKEDIR=linux MAKETARGET="clean" __compile
distclean_kernel:
#	make MAKEDIR=linux MAKETARGET="-k clean" __compile
#	make MAKEDIR=linux MAKETARGET="-k mrproper" __compile
	make MAKEDIR=linux MAKETARGET="-k distclean" __compile
config_kernel:
	make MAKEDIR=. MAKETARGET=linux_config __compile


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
	 find . -name \*.d -exec rm \{} \; )
compile_lpad:
	@make backup_daily
##	make clean_lpad
	make MAKEDIR=. SCRIPT=./lpad_make.sh __script
	make chk_gtags
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

rootfs:
	make MAKEDIR=. MAKETARGET="rootfs" __compile
rom:
#	cp 141125_lfv70/usr/etc/php.ini `cat .targetdate`_`cat .targetfolder`/usr/etc/
#	cp -r 141125_lfv70/usr/etc/lighttpd `cat .targetdate`_`cat .targetfolder`/usr/etc/
#	cp PJMI `cat .targetdate`_`cat .targetfolder`/usr/local/userweb/htdocs/
#	make MAKEDIR=. MAKETARGET="rom rootfs u-boot-script rootfs arigato" __compile
	make MAKEDIR=../rom MAKETARGET= __compile
	make MAKEDIR=. MAKETARGET=upg __compile
	make tftp
image:
	@make rom

gtags:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc; gtags)
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; gtags)
chk_gtags:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc; \
	 if [ ! -f GTAGS ] ; then \
	 	gtags; \
	 fi)
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; \
	 if [ ! -f GTAGS ] ; then \
	 	gtags; \
	 fi)
clean_gtags:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc; rm -f G*)
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/dtvrec; rm -f G*)

##newsrc: _update_targetdate
##	@if [ -d `cat .targetdate`_`cat .targetfolder` ] ; then \
##		echo "	================================================="; \
##		echo "	today's tree `cat .targetdate`_`cat .targetfolder` is exist"; \
##		echo "	try \"make remove_current_tree\""; \
##		echo "	================================================="; \
##		exit 1; \
##	fi
##	make co
##
##newtree: _update_targetdate
##	@make newsrc
##	make compile_all
##

tftp:
	mkdir -p /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/rom/* /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/target/uImage /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/target/*.rom /var/lib/tftpboot/`cat .targetfolder`
	sudo cp -r `cat .targetdate`_`cat .targetfolder`/usr/target/*.bin /var/lib/tftpboot/`cat .targetfolder`

newsrc_lfe8:
	rm -f .targetsetting
	ln -s .target.lfe8 .targetsetting
	@make newsrc

newsrc_lfv70:
	rm -f .targetsetting
	ln -s .target.lfv70 .targetsetting
	@make newsrc

signage_copyback:
	(cd `cat .targetdate`_`cat .targetfolder`/usr/src/AppSrc/userApps/cgi_wrapper; make signage_copyback)


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
	svn co $(REV) $(URL) $(DIR)
	if [ -d $(DIR)/ArchiveFiles ] ; then \
		(cd $(DIR)/ArchiveFiles; rm -f CPU_* build_* cs_root* dcchd_* mrua* smp86xx_*;) \
	fi
	chmod -R a-w $(DIR)

## ===============================================
reference:
#	make _mk_ref_tree  REV=-r464 URL=$(JW230_SVNBASE)/branches/NEW_MULTI_LIVE_KENTOU DIR=jw230.NEW_MULTI_LIVE_KENTOU.r464.latest
#	make _mk_ref_tree  REV=-r102 URL=$(JW230_SVNBASE)/branches/NEW_MULTI_LIVE_KENTOU DIR=jw230.NEW_MULTI_LIVE_KENTOU.r102.oldest
#	make _mk_ref_tree  REV=-r194 URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.r194.1102_pairing_qrcode
#	make _mk_ref_tree  REV=-r488 URL=$(JW230_SVNBASE)/branches/NEW_MULTI_LIVE_KENTOU_revB DIR=jw230.NEW_MULTI_LIVE_KENTOU_revB.r488.mms_kashidashi_rom
#	make _mk_ref_tree  REV=-r290 URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.r290.last_week
#	make _mk_ref_tree  REV= URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.latest
#	make _mk_ref_tree  REV=-r URL=$(JW230_SVNBASE)/trunk DIR=jw230.trunk.latest

#	make _mk_ref_tree  REV= URL=$(JW230_SVNBASE)/tags/JX200_v182 DIR=JX200_v182
	make _mk_ref_tree  REV= URL=$(VZ585N_SVNBASE)/trunk DIR=vz585n.trunk.latest

