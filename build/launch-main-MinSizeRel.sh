#!/bin/sh
bindir=$(pwd)
cd /Users/cesarsalcedo/Documents/UTEC/2020-2/EstructurasDeDatosAvanzadas/weeks/week03/btree/main/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/local/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /Users/cesarsalcedo/Documents/UTEC/2020-2/EstructurasDeDatosAvanzadas/weeks/week03/btree/build/MinSizeRel/main 
	else
		"/Users/cesarsalcedo/Documents/UTEC/2020-2/EstructurasDeDatosAvanzadas/weeks/week03/btree/build/MinSizeRel/main"  
	fi
else
	"/Users/cesarsalcedo/Documents/UTEC/2020-2/EstructurasDeDatosAvanzadas/weeks/week03/btree/build/MinSizeRel/main"  
fi
