clc
clear all
close all
x= [ 1 2 3 4 5 6 7 8 9 10];
w = [25 12 65 32 1 2 58 84 11 4];
w = w/sum(w);
l = cumsum(w);
x_up = zeros(10,1);
for i = 1:10
      r = rand;
      x_up(i,1) = x(find(r <= l,1));
end
x
x_up