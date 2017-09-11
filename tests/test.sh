
cl_cpp="/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/Release/clustering-cpp"
cl_py="/home/eremeykin/d_disk/projects/python/effective-clustering/eclustering/"
path_data="/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/tests/"

echo "award |    cpp   |    py    |"
rm output/*
for x in data/test*-points; do
	y="${x%%-*}" 
	y="${y##*/}"
	points_file="${path_data}data/${y}-points"
	labels_file="${path_data}data/${y}-labels"
	count=`cat ${path_data}data/${y}-points | wc -l`
	echo -n $y
	if [ "$count" -gt 5000 ]; then
		printf '           SKIP              [%6d]\n' $count
		# echo '           SKIP              [' $count ']'
		continue
	fi

	un=`sort "$labels_file" | uniq | wc -l`
	START=$(date +%s.%N)
	$cl_cpp award "$points_file" "$labels_file" "$(($un*2/5))" > "output/award_${y}.out_cpp"
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	LC_NUMERIC="en_US.UTF-8" printf ' |  %7.4f ' $DIFF


	START=$(date +%s.%N)
	python3 "${cl_py}agglomerative/a_ward.py" "$points_file" "$labels_file" "$(($un*2/5))"  > "output/award_${y}.out_py"
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	LC_NUMERIC="en_US.UTF-8" printf '|  %7.4f |' $DIFF
	
	diff "output/award_${y}.out_cpp" "output/award_${y}.out_py" > /dev/null


	if [ "$?" -eq 0 ]; then
		printf 'PASS [%6d]\n' $count
	else
		printf '     [%6d]               FAIL\n' $count
	fi
done

echo "anomal clustering"
for x in data/test*-points; do
	y="${x%%-*}" 
	y="${y##*/}"
	points_file="${path_data}data/${y}-points"
	labels_file="${path_data}data/${y}-labels"
	count=`cat ${path_data}data/${y}-points | wc -l`
	echo -n $y
	
	START=$(date +%s.%N)
	$cl_cpp anomal "$path_data$x"  > "output/anomal_${y}.out_cpp"
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	LC_NUMERIC="en_US.UTF-8" printf ' |  %7.4f ' $DIFF


	START=$(date +%s.%N)
	python3 "${cl_py}pattern_initialization/anomalous_cluster.py" "$path_data$x" > "output/anomal_${y}.out_py"
	END=$(date +%s.%N)
	DIFF=$(echo "$END - $START" | bc)
	LC_NUMERIC="en_US.UTF-8" printf '|  %7.4f |' $DIFF
	
	diff "output/anomal_${y}.out_cpp" "output/anomal_${y}.out_py" > /dev/null

	if [ "$?" -eq 0 ]; then
		printf 'PASS [%6d]\n' $count
	else
		printf '     [%6d]               FAIL\n' $count
	fi
done