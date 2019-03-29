#!/usr/bin/env bash
#https://unix.stackexchange.com/questions/166341/constantly-check-if-file-is-modified-bash
# Provides      : Check if a file is changed
# 
# Limitations   : none
# Options       : none
# Requirements  : bash, md5sum, cut
# 
# Modified      : 11|07|2014
# Author        : ItsMe
# Reply to      : n/a in public
#
# Editor        : joe
#
#####################################
#
# OK - lets work
#


# what file do we want to monitor?
# I did not include commandline options
# but its easy to catch a command line option
# and replace the defaul given here
file="$1"

# path to file's saved md5sum
# I did not spend much effort in naming this file
# if you ahve to test multiple files
# so just use a commandline option and use the given
# file name like: filename=$(basename "$file")
fingerprintfile="$1.txt"

# does the file exist?
if [ ! -f $file ]
    then
        echo "ERROR: $file does not exist - aborting"
    exit 1
fi

while ((1 == 1))
do
	# create the md5sum from the file to check
	filemd5=`md5sum $file | cut -d " " -f1`

	# check the md5 and
	# show an error when we check an empty file
	if [ -z $filemd5 ]
		then
			echo "The file is empty - aborting"
			exit 1
		else
			# pass silent
			:
	fi

	# do we have allready an saved fingerprint of this file?
	if [ -f $fingerprintfile ]
		then
			# yup - get the saved md5
			savedmd5=`cat $fingerprintfile`

			# check again if its empty
			if [ -z $savedmd5 ]
				then
					echo "The file is empty - aborting"
					exit 1
			fi

			#compare the saved md5 with the one we have now
			if [ "$savedmd5" = "$filemd5" ]
				then
					# pass silent
					:
				else
					echo "File has been changed"

					# this does an beep on your pc speaker (probably)
					# you get this character when you do:
					# CTRL+V CTRL+G
					# this is a bit creepy so you can use the 'beep' command
					# of your distro
					# or run some command you want to
					./RUN_COMMANDS.sh
			fi

	fi

	# save the current md5
	# sure you don't have to do this when the file hasn't changed
	# but you know I'm lazy and it works...
	echo $filemd5 > $fingerprintfile
done