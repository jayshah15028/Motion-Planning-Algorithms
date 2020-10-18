function array=succ_dist(x,y,successor,map,path_distance)

count=size(successor);
[target(1),target(2)]=find(map==3);
array=zeros(count(1),7);
for i=1:count(1)
    array(i,1:2)=successor(i,:);
    array(i,3:4)=[x,y];
    array(i,5)=path_distance + dist_calc(x,y,successor(i,1),successor(i,2));    % hn
    array(i,6)= dist_calc(successor(i,1),successor(i,2),target(1),target(2));    %gn
    array(i,7)= array(i,5) + array(i,6);     %fn
end

    