#!/bin/bash

SCRIPT_DIR="$([ -L "$0" ] && link="$( dirname $( readlink "$0" ))"; cd "$( dirname "$0" )"/${link} && pwd )"

# env prepare
. $SCRIPT_DIR/prepare.sh

OLDGOPATH="$GOPATH"
OLDGOBIN="$GOBIN"
export GOPATH="$SCRIPT_DIR:$GOXCLIB"
export GOBIN="$SCRIPT_DIR/bin"

cd bin/
parallel go build ::: git.ixiaochuan.cn/service/worker git.ixiaochuan.cn/gateway git.ixiaochuan.cn/service/bizsrv git.ixiaochuan.cn/service/media git.ixiaochuan.cn/service/search git.ixiaochuan.cn/service/cfgcenter git.ixiaochuan.cn/service/mnstier git.ixiaochuan.cn/service/openlogin git.ixiaochuan.cn/service/logstat git.ixiaochuan.cn/service/logsink git.ixiaochuan.cn/service/lookupd git.ixiaochuan.cn/service/review/godpool git.ixiaochuan.cn/service/rss git.ixiaochuan.cn/service/post/record git.ixiaochuan.cn/xcutils/pinger git.ixiaochuan.cn/xcutils/log-cleaner git.ixiaochuan.cn/xcutils/topic/topic_update_posts git.ixiaochuan.cn/xcutils/error-alert github.com/tsenart/stress
cd ..
parallel goBuild ::: 'bin/media-gateway git.ixiaochuan.cn/media' 'bin/lookupd-win git.ixiaochuan.cn/service/lookupd/win' 'bin/review-calc git.ixiaochuan.cn/service/review/calculator' 'bin/topic-calc git.ixiaochuan.cn/service/topic/calculator' 'bin/record-score git.ixiaochuan.cn/service/post/calculator' 'bin/flowsearch_crond git.ixiaochuan.cn/xcutils/flow/flowindexer' 'bin/tester github.com/tsenart/vegeta' 
goBuild "$SCRIPT_DIR"/bin/logrouter git.ixiaochuan.cn/service/logcenter/logrouter -ldflags=-s
echo 'done'
export GOPATH="$OLDGOPATH"
export GOBIN="$OLDGOBIN"
