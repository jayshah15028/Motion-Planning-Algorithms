import numpy as np
from itertools import permutations

def arrange(n):
    array=[];
    for i in range(n):
        array.append(i+1);


def permute(array,ind):
    if ind==len(array)-1:
        for i in range(len(array)):
            if array[i]%(i+1)!=0 and (i+1)%array[i]!=0:
                break;
        if i=
                
        
        
        
    
    

#def arrange(n):
    
array=permute([1,2,3]);

array=[];
for i in range(3):
    array.append(i+1);