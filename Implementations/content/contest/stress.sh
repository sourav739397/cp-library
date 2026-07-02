# A and B are executables you want to compare, gen takes int 
# as command line arg. Usage: 'sh stress.sh'
for((i = 1; ; ++i)); do
	echo $i
	./gen $i > in
	./sol < in > outSol
	./slow < in > outSlow
	diff -w outSol outSlow || break
	# diff -w <(./A < in) <(./B < in) || break
done