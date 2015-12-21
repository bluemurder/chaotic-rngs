clear all;
close all;
clc;

% slope
k=2-(1/8);
% init
x0=0;
% iterations
N=100000000;

n = N/100;

x=zeros(N,1);
s=false(N,1);

% number generation
x(1) = x0;
s(1) = (x(1) >= 0);
for i=2:N
    if x(i-1) < 0
        x(i) = k * x(i-1) +1;
    else
        x(i) = k * x(i-1) -1;
    end
    s(i) = (x(i) >= 0);
end

% file print

s2 = reshape(s,N/n,n);

fp = fopen([ 's' num2str(x0) '.txt'],'w');
j=0;
for i=1:(N/n)
    fprintf(fp,'%s',num2str(s2(i,:)));
    i
%     j=j+1;
%     if j >= 1000000
%         i
%         j=0;
%     end
end
% s2 = num2str(s);
% s2 = s2';
% fprintf(fp,'%s',s2);
fclose(fp);