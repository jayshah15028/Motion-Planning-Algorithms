clc; clear;
xrange=100; yrange=100;    %grid coarse or fine by increasing/decreasing number of elements on map
axis([1 xrange 1 yrange]);
grid on;
hold on;
% 1-space(unvisited), 0-obstacles, 2-space(visited), 3-target, 4-start 
map=ones(xrange,yrange);
n_obstacles=randi(((xrange)^2)/2,1);  %number of obstacles
obs_x=randi(xrange,n_obstacles,1); obs_y=randi(xrange,n_obstacles,1);  %random positions of obstables
obs=[obs_x obs_y];  %obstacles coordinates
% insert obstacles in map
for i=1:n_obstacles
    map(obs_x(i),obs_y(i))=0;
end
endpoints=randi(xrange,2,2);    %target and start coordinates
target=endpoints(1,:);
map(endpoints(1,1),endpoints(1,2))=3;    %mark target coordinates on map
plot(obs_x,obs_y,'or');
start=endpoints(2,:);
map(endpoints(2,1),endpoints(2,2))=4; 

current=start;         %defining start node as the current node
path_distance = dist_calc(start(1),start(2),current(1),current(2));   %current hn
path = current;                                                       %all nodes of the path 
successor = neighbors(start(1),start(2),xrange,map);     
visited=succ_dist(current(1),current(2),successor,map,path_distance);

[node,node_dist]=minimum_distance(current(1),current(2),path_distance,successor,map,visited);

path_distance=path_distance+node_dist;
path=[path;node];

current=node;
while map(current(1),current(2))~=3
successor = neighbors(current(1),current(2),xrange,map);
visit_temp=succ_dist(current(1),current(2),successor,map,path_distance);
visited=[visited;visit_temp];
[node,node_dist]=minimum_distance(current(1),current(2),path_distance,successor,map,visited);
path_distance=path_distance+node_dist;
path=[path;node];
current=node;
end

plot(path(:,1),path(:,2),'*k');