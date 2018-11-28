import sys

import numpy as np
import matplotlib.pyplot as plt


layer_count=13
bit_width=int( sys.argv[1])
mAP=[]
datafile = open( sys.argv[2] , "r").readlines()
for line in datafile:
	if (line.find("mAP")!=-1) : 
		 mAP.append(float( line.split(' ')[8]))


#print data
data = np.asarray(mAP ).reshape(-1,13)
fig = plt.figure(figsize=(10,10))
ax = fig.add_subplot(1,1,1)
cax = ax.matshow(data, interpolation='None',aspect="auto",cmap=plt.cm.Blues)
fig.colorbar(cax,label='mAP')

#data on graph
for i in range(0,bit_width):
    for j in range(0,layer_count):
        ax.text(x=j, y=i, s=data[i,j], va='center', ha='center',color='w',weight='bold')


#graph setting
columns = ['1','3','5','7','9','11','13','14','15','16','19','22','23']  #['A', 'B', 'C', 'D','E','F','G']
rows    = range(0,bit_width )
ax.set_xticks(np.arange(len(columns)))
ax.set_xticklabels( columns )

ax.set_yticks(np.arange(bit_width))
ax.set_yticklabels(rows)

# ax.grid(which='both',alpha=0.3)

ax.xaxis.set_label_position('top')
ax.set_xlabel("Layers")
ax.set_ylabel("Fixed_point")

#plt.grid(True)
#plt.show()
fig.savefig(  sys.argv[2].split('/')[1]+".png"   )
