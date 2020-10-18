function successor = neighbors(x,y,xrange,map)
k=1;
for i=-1:1:1
    for j=-1:1:1
        if ~(i==j && i==0)
            if (x+i<=xrange && x+i>=1 && y+j<=xrange && y+j>=1)
                if map(x+i,y+j)~=0
                    successor(k,1)=x+i;
                    successor(k,2)=y+j;
                    k=k+1;
                end
            end
        end
    end
end
end