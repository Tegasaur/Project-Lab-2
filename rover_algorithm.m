clc
clear
h=inline('1./(1+exp(-x))','x');
data = load('dataset.txt');
%1. Setup: getting everything together
x=[data(:,1),data(:,2)];
y1=data(:,3);
y2=data(:,4);
y3=data(:,5);
y4=data(:,6);
m=2001;
alpha=0.3;
iter=10000;
mouse1=90;
mouse2=90;
J1=zeros(1,iter);
J2=zeros(1,iter);
J3=zeros(1,iter);
J4=zeros(1,iter);
[x, sigma, mean]=featureNormalize(x);
b=[1,(mouse1-mean(1))/sigma(1),(mouse2-mean(2))/sigma(2)];
x=[ones(2001,1),x];
disp(sigma(1));
disp(mean(1));
disp(sigma(2));
disp(mean(2));


%2. Forward conditon regression
theta=zeros(1,3);
theta=theta';
for i=1:iter
    theta=theta-(alpha*x'*(h(x*theta)-y1))/m;
    J1(i)=computeCost(x,y1,theta);
end
subplot(4,1,1); plot(J1);
disp(theta);
disp(h(b*theta));


%3. Left conditon regression
theta=zeros(1,3);
theta=theta';
for i=1:iter
    theta=theta-(alpha*x'*(h(x*theta)-y2))/m;
    J2(i)=computeCost(x,y2,theta);
end
subplot(4,1,2); plot(J2);
disp(theta);
disp(h(b*theta));


%4. Right conditon regression
theta=zeros(1,3);
theta=theta';
for i=1:iter
    theta=theta-(alpha*x'*(h(x*theta)-y3))/m;
    J3(i)=computeCost(x,y3,theta);
end
subplot(4,1,3); plot(J3);
disp(theta);
disp(h(b*theta));


%5. Stop conditon regression
theta=zeros(1,3);
theta=theta';
for i=1:iter
    theta=theta-(alpha*x'*(h(x*theta)-y4))/m;
    J4(i)=computeCost(x,y4,theta);
end
subplot(4,1,4); plot(J4);
disp(theta);
disp(h(b*theta));

