#!/bin/csh

foreach i (1 2 3)
	echo -n "\n\nUNIX System V, Release 2.2 (pokey)\n\nlogin: "
	set N = $<
	echo -n "password: "

	if ( "X$N $<" == "X$*" ) then
		echo "\nWelcome to Unix\n\nPlease clean up your directories.  The filesystem is getting full.\nOur tcp/ip link to gamma is a little flaky, but seems to work.\nThe current version of ftp can only send files from your home\ndirectory, and deletes them after they are sent!  Be careful.\n\nNote: Restricted bourne shell in use.\n"
		exit
	else
		echo "login incorrect\n"
	endif
end

exit 2