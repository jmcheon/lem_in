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
generated_map="generated_map"
map_extension=".map"
output_file="output_file.txt"

print_usage() {
	echo -e "Executing checker for lem-in generator.\n"
	echo -e "\tusage: ./$script_name [option]"
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
	map="$2"
	# Run generator and save the output
	$generator $1 1> "$map" 2> /dev/null

	parse_line=$(head -n 1 "$map")
	num_ants=$(echo "$parse_line" | grep -oE '[0-9]+')
	if [ -z $num_ants ]; then
		print_usage
		rm "$map"
		exit
	fi
	parse_line=$(tail -n 1 "$map")
	required_lines=$(echo "$parse_line" | grep -oE '[0-9]+')

	#echo $result
	#echo -en "${YELLOW}number of ants: $num_ants${FIN}, "
	#echo -e "${ORANGE}required lines: $required_lines${FIN}"
	
	# Run the program with generated map
	$program < $map > $output_file
	num_lines=$(cat $output_file | grep L | wc -l)
	#echo -e "${ORANGE}number of lines: $num_lines${FIN}"

	if [ $required_lines -ge $num_lines ]; then
		echo -e "${GREEN}OK${FIN}"
	else
		echo -e "${RED}FAIL${FIN}"
	fi

	rm "$map"
	rm "$output_file"
}

if [ $# -eq 0 ]; then
	print_usage

elif [ $# -eq 1 ]; then
	if [ $1 == "--help" ]; then
		generator=$(set_generator)
		$generator $1
	elif [ $1 == "--flow-one" ]; then
		map_list=$(ls maps | grep flow-one | sort -V)
	elif [ $1 == "--flow-ten" ]; then
		map_list=$(ls maps | grep flow-ten | sort -V)
	elif [ $1 == "--flow-thousand" ]; then
		map_list=$(ls maps | grep flow-thousand | sort -V)
	elif [ $1 == "--big" ]; then
		map_list=$(ls maps | grep -E 'big[0-9]+' | sort -V)
	elif [ $1 == "--big-superposition" ]; then
		map_list=$(ls maps | grep big-super | sort -V)
	else
		print_usage
	fi

	generator=$(set_generator)
	#echo "$map_list"
	i=1
	for map in $map_list; do
		#echo "$map"
		echo -ne "\n${YELLOW}TEST $i ${FIN}"
		run_generator $1 $map
		((i++))
	done
fi
