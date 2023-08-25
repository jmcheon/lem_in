#!/bin/bash

# define color codes
YELLOW="\033[0;38;5;220m"
GREEN="\033[0;38;5;42m"
RED="\033[0;38;5;196m"
BLUE="\033[0;38;5;21m"
PINK="\033[0;38;5;205m"
PURPLE="\033[0;38;5;93m"
ORANGE="\033[38;5;202m"
FIN="\033[0m"

script_name=$(basename "$0")
generator="./generator_linux"
program="./lem-in"
generated_map="generated_map.txt"

print_usage() {
	echo -e "Executing checker for lem-in generator.\n"
	echo -e "\tusage: ./$script_name [option] [number of iteration]"
	echo -e "\toptions:" 
	echo -e "\t\t--help : to read the manual" 
}

set_generator() {
# If operating system name contains Darwnin: MacOS. Else Linux
	if uname -s | grep -iqF Darwin; then
		echo "./generator_osx"
	else
		echo "./generator_linux"
	fi
}

run_generator() {
	# Run generator and save the output
	$generator $1 1> $generated_map 2> /dev/null

	parse_line=$(head -n 1 "$generated_map")
	num_ants=$(echo "$parse_line" | grep -oE '[0-9]+')
	if [ -z $num_ants ]; then
		print_usage
		rm "$generated_map"
		exit
	fi
	parse_line=$(tail -n 1 "$generated_map")
	required_lines=$(echo "$parse_line" | grep -oE '[0-9]+')

	#echo $result
	echo -en "${YELLOW}number of ants: $num_ants${FIN}, "
	echo -e "${ORANGE}required lines: $required_lines${FIN}"
	
	# Run the program with generated map
	time $program < $generated_map
	rm "$generated_map"
}

if [ $# -eq 0 ]; then
	print_usage

elif [ $# -eq 1 ]; then
	if [ $1 == "--help" ]; then
		generator=$(set_generator)
		$generator $1
	else
		generator=$(set_generator)
		run_generator $1
	fi

elif [ $# -eq 2 ]; then
	if [ $1 == "--help" ]; then
		generator=$(set_generator)
		$generator $1
	else
		generator=$(set_generator)
		if [[ "$2" =~ ^[0-9]+$ ]]; then
    		for ((i=0; i<$2; i++)); do
				echo -ne "\n${YELLOW}i=$i, ${FIN}"
				run_generator $1
			done
		else
			print_usage
		fi
	fi
fi
