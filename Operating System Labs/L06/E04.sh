sort -k 1 -n file.txt 

sort -k 2 file.txt

grep Frequentato file.txt

grep INF1T3 file.txt | sort -k 1 -n

grep -e '^[0-9]*2\> ' -e '^[0-9]*4\>' file.txt | sort -k 2

grep TLC1T3 file.txt | grep frequentare | sort -k1 -nr

grep -e "A..A" file.txt

grep -e "\<.A..A.\>" file.txt

cut -d ' ' -f 1 file.txt |tr -d 0 | tr 8 1 | uniq

cut -d ' ' -f 1 file.txt |tr -d 0 | tr 8 1 | uniq -cd