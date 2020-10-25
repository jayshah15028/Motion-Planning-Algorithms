import numpy as np


def dist_calc(x1,y1,x2,y2):
    dist=((x1-x2)**2 + (y1-y2)**2)**(1/2);
    return dist

def neighbors(x,y,xrange,map):
    k=0; 
    successor=[];
    for i in np.arange(-1,2,1):
        for j in np.arange(-1,2,1):
            if ~(i==j and i==0):
                 if (x+i<xrange and x+i>=0 and y+j<xrange and y+j>=0):
                     if map[x+i,y+j]!=0:
                         successor.append([x+i,y+j]);
                        
                         k=k+1;
    successor=np.array(successor);
    return successor

def succ_dist(x,y,successor,map,path_distance):
    count=np.array(successor.shape);
    target=np.array(np.where([map==3]));
    array=np.zeros((count[0],7));
    for i in np.arange(0,count[0]):
        array[i,0:2]=successor[i];
        array[i,2:4]=np.array([x,y]);
        array[i,4]=path_distance + dist_calc(x,y,successor[i,0],successor[i,1]);
        array[i,5]= dist_calc(successor[i,0],successor[i,1],target[0],target[1]);
        array[i,6]=array[i,4] + array[i,5];
    return array


def minimum_distance(x,y,path_distance,successor,map,visited):
    count=np.array(successor.shape);
    target=np.array(np.where([map==3]));
    target=target[1:3];
    distance=np.inf*np.ones((count[0],1));
    flag=np.zeros((count[0],1));
    for i in np.arange(0,count[0]):
        if map[successor[i,0],successor[i,1]]==3:
            node=np.array([successor[i,0],successor[i,1]]);
            node_dist=dist_calc(x,y,node[0],node[1]);
            flag[i]=1;
            break;
        
        if map[successor[i,0],successor[i,1]]==1 or map[successor[i,0],successor[i,1]]==2:
            if map[successor[i,0],successor[i,1]]==1:
                distance[i]= path_distance + dist_calc(x,y,successor[i,0],successor[i,1]) + dist_calc(target[0],target[1],successor[i,0],successor[i,1]);
#                map[successor[i,0],successor[i,1]]=2;
                
            if map[successor[i,0],successor[i,1]]==2:
                distance[i]= path_distance + dist_calc(x,y,successor[i,0],successor[i,1]) + dist_calc(target[0],target[1],successor[i,0],successor[i,1]);
                for j in np.arange(0,np.array(visited.shape[0])):
                    if (successor[i,0]==visited[j,0] and successor[i,1]==visited[j,1]):
                        if path_distance + dist_calc(x,y,successor[i,0],successor[i,1]) < visited[j,4]:
                            visited[j,4] = path_distance + dist_calc(x,y,successor[i,0],successor[i,1]);
    
    if all([ a == 0 for a in flag ]):
        index=np.argmin(distance);
        node=successor[index,:];
        node_dist=dist_calc(x,y,node[0],node[1]);
    
    return node,node_dist       
        
    
    
    