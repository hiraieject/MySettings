# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific aliases and functions
export CVSROOT=":pserver:hirai@10.78.112.116:/usr/local/cvsroot"
export SVNROOT="https://133.181.137.151/FP/repos/"

export HTTP_PROXY="http://10.77.8.70:8080"
export http_proxy="http://10.77.8.70:8080"
export FTP_PROXY="http://10.77.8.70:8080"
export ftp_proxy="http://10.77.8.70:8080"
export proxy="http://10.77.8.70:8080"

export EDITOR="emacs"


alias       DIFF='touch DIFF; rm DIFF; ln -s ~/DIFF .; cvs diff -c > ~/DIFF/diff`date +%y%m%d%H%M-``(pwd | sed "s/.*\///g")`".txt"'

alias langc="export LANG=C"
alias langj="LANG=ja_JP.utf8"

export XDISPLAY86=192.168.0.86:0
alias       em86='DISPLAY=$XDISPLAY86.0; emacs &'
alias       gt86='DISPLAY=$XDISPLAY86.0; gnome-terminal &'
export XDISPLAY100=192.168.83.2:0
#export XDISPLAY100=hiraipc:0
alias       em100='DISPLAY=$XDISPLAY100.0; emacs &'
alias       em101='DISPLAY=$XDISPLAY100.1; emacs &'
alias       gt100='DISPLAY=$XDISPLAY100.0; gnome-terminal &'
alias       gt101='DISPLAY=$XDISPLAY100.1; gnome-terminal &'

alias       wk='gnome-terminal --display=$XDISPLAY100.1 --geometry=724x936+2550+670 &'

alias       eq1='cd ~/eq1'
alias       eq1src='cd ~/eq1/current_startup/usr/src/'
alias       sq1='cd ~/sq1'
alias       sq1src='cd ~/sq1/current_SQ1/usr/src/'
alias       wm='cd ~/startup_panaapp'
alias       wmsrc='cd ~/startup_panaapp/current_startupr6752_panaapp/usr/src/'
alias       wb='cd ~/startup_whiteboard'
alias       wbsrc='cd ~/startup_whiteboard/current_startupr6591_whiteboard/usr/src/'


alias       DIFF='touch DIFF; rm DIFF; ln -s ~/DIFF .; cvs diff -c > ~/DIFF/diff`date +%y%m%d%H%M-``(pwd | sed "s/.*\///g")`".txt"'
alias       SDIFF='export LANG=C; touch DIFF; rm DIFF; ln -s ~/DIFF .; svn diff > ~/DIFF/diff`date +%y%m%d%H%M-``(pwd | sed "s/.*\///g")`".txt"'
##alias       PATCH='/usr/bin/patch -p0 --binary'
## 改行コードがCRLFのファイルでも正常に当てるために binary オプションが必要
alias       PATCH='/usr/bin/patch -p0 --binary'
