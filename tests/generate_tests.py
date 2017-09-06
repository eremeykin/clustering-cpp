import numpy as np

length = 30
with open("data/test1-labels", "w") as f:
	labels = ["1" if i%2==0 else "2" if i%3==0 else "0" for i in range(0,length)]
	f.write("\n".join(labels))
with open("data/test1-points","w") as f:
	strings = [" ".join([str(x) for x in np.random.uniform(0,10,4)]) for i in range(0,length)]
	f.write("\n".join(strings))



length = 10000
with open("data/test3-labels", "w") as f:
	labels = ["1" if i%2==0 else "2" if i%3==0 else "0" for i in range(0,length)]
	f.write("\n".join(labels))
with open("data/test3-points","w") as f:
	strings = [" ".join([str(x) for x in np.random.uniform(0,10,4)]) for i in range(0,length)]
	f.write("\n".join(strings))