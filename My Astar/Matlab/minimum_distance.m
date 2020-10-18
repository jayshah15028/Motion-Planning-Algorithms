function [node,node_dist]=minimum_distance(x,y,path_distance,successor,map,visited)

count=size(successor);
[start(1),start(2)]=find(map==3);
distance=inf(count(1),1);
flag=zeros(count(1),1);
for i=1:count(1)
    if map(successor(i,1),successor(i,2))==3
            node=[successor(i,1),successor(i,2)];
            node_dist=dist_calc(x,y,node(1),node(2));
            flag(i)=1;
            break;
    end
    if (map(successor(i,1),successor(i,2))==1 || map(successor(i,1),successor(i,2))==2)
        if map(successor(i,1),successor(i,2))==1
            distance(i)= path_distance + dist_calc(x,y,successor(i,1),successor(i,2)) + dist_calc(start(1),start(2),successor(i,1),successor(i,2));
        end
        if map(successor(i,1),successor(i,2))==2
            distance(i)=path_distance + dist_calc(x,y,succesor(i,1),successor(i,2)) + dist_calc(start(1),start(2),successor(i,1),successor(i,2));
            for j=1:length(visited(1,:))
                if (successor(i,1)==visited(j,1) && successor(i,2)==visited(j,2))
                    if path_distance + dist_calc(x,y,succesor(i,1),successor(i,2)) < visited(j,5)
                        visited(j,5) = path_distance + dist_calc(x,y,succesor(i,1),successor(i,2));
                    end
                end
            end
        end
        
    end
end
if isempty(flag(flag==1))
    index=find(distance==min(distance),1);
    node=successor(index,:);
    node_dist=dist_calc(x,y,node(1),node(2));
end
end
    