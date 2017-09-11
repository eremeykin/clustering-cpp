if [ "$1" == "py" ] ; then
	python3 "/media/d_disk/projects/python/effective-clustering/eclustering/pattern_initialization/anomalous_cluster.py" "/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/tests/data/$2-points" "/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/tests/data/$2-labels"

fi
if [ "$1" == "cpp" ]; then
	/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/Release/clustering-cpp "/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/tests/data/$2-points" "/home/eremeykin/d_disk/projects/Clustering-cpp/clustering-cpp/tests/data/$2-labels"
fi