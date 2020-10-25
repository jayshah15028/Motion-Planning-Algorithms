import numpy as np
from math import *
import matplotlib.pyplot as plt 
from astarfunctions import *


xrange=100; yrange=100;  #x and y axis limits

# 1-space(unvisited), 0-obstacles, 2-space(visited), 3-target, 4-start 

map=np.ones((xrange,yrange));  #introducing map matrix

n_obstacles=np.random.randint((((xrange)**2)/2));  #number of obstacles
n_obstacles=n_obstacles + 1;   #to avoid zero
obs_x=np.random.choice(np.arange(xrange),size=(n_obstacles));
obs_y=np.random.choice(np.arange(yrange),size=(n_obstacles));
obs=np.vstack([obs_x,obs_y]).T;   #co-ordinates of the obstacles
plt.plot([obs_x],[obs_y],'o',color='r');

for i in range(n_obstacles):
    map[obs_x[i],obs_y[i]] = 0;
    
endpoints=np.random.randint(xrange,size=(2,2));
target=endpoints[0,:];
map[target[0],target[1]]=3;
start=endpoints[1,:];
map[start[0],start[1]]=4;
plt.plot(target[0],target[1],'o');
plt.plot(start[0],start[1],'o');

current=start;

path_distance=dist_calc(start[0],start[1],current[0],current[1]);
path=current;

successor = neighbors(start[0],start[1],xrange,map);

visited=succ_dist(current[0],current[1],successor,map,path_distance);

node,node_dist=minimum_distance(current[0],current[1],path_distance,successor,map,visited);

path_distance=path_distance+node_dist;
path=np.vstack((path,node));

current=node;

counter = 0;
while map[current[0],current[1]] !=3:
    if counter>10**4:
        break;
    successor = neighbors(current[0],current[1],xrange,map);
    visit_temp=succ_dist(current[0],current[1],successor,map,path_distance);
    visited=np.vstack((visited,visit_temp));
    node,node_dist=minimum_distance(current[0],current[1],path_distance,successor,map,visited);
    path_distance=path_distance+node_dist;
    path=np.vstack((path,node));
    current=node;
    counter=counter+1;
    
plt.plot(path[:,0],path[:,1],'*');