#!/bin/bash
#
#

THREADS=1
MAGNITUDE=6
LOGFILE=factorization.log

get_rand() {
	local STRLEN=`echo $1 | wc -c`
	#echo "strlen: $STRLEN"
	local RAND_HEX=`openssl rand $STRLEN | perl -ne 'print uc(unpack("H*"))'`
	#echo "rand: $RAND_HEX"
	RAND_DEC=`echo "ibase=16;$RAND_HEX" | bc | perl -pe 's/[^0-9]//g'`
	#echo "rand_dec: $RAND_DEC"
	#echo "mod: $1"
	#echo "$RAND_DEC % $1"
	echo "$RAND_DEC % $1" | bc | perl -pe 's/[^0-9]//g'
}

process() {
	echo "Factorizing: $1"
	local LIMIT=`echo "sqrt($1)" | bc | perl -pe 's/[^0-9]//g'`
	#echo "Limit: $LIMIT"
	local FACTOR_FOUND=0

	while [ "$FACTOR_FOUND" = "0" ] ; do
		local MIN=`get_rand $LIMIT`
		local MAX=`echo "$MIN + 10^$MAGNITUDE" | bc | perl -pe 's/[^0-9]//g'`
		#echo "min: $MIN"
		#echo "max: $MAX"
		echo >>$LOGFILE
		date +"%F %T" >>$LOGFILE
		./simple-factorization --min $MIN --max $MAX $1 >>$LOGFILE 2>&1
		if [ "$?" = "0" ] ; then
			FACTOR_FOUND=1
		fi
	done

}

while [ -n "$1" ] ; do
	case "$1" in
		--threads)
			shift
			THREADS=$1
			shift
			;;
		--magnitude)
			shift
			MAGNITUDE=$1
			shift
			;;
		--logfile)
			shift
			LOGFILE=$1
			shift
			;;
		--*)
			echo "ERROR: unknown option $1"
			echo
			usage
			;;
		*)
			process $1
			shift
			;;
	esac

done

