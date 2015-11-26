close all
xy_1 = zeros(10,2);
inc = sqrt(2);
theta = 1:180;
hold on
for j=1:180
xy = [0 0];
    for i=1:10
    theta = j;
    xy(1) = xy(1) + inc*cosd(theta);
    xy(2) = xy(2) + inc*sind(theta);
    xy_1(i,:) = xy';
    end
plot(xy_1(:,1),xy_1(:,2),'bo')
end
hold off