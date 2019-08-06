function [X_norm, mu, sigma] = featureNormalize(X)
%FEATURENORMALIZE Normalizes the features in X 
%   FEATURENORMALIZE(X) returns a normalized version of X where
%   the mean value of each feature is 0 and the standard deviation
%   is 1. This is often a good preprocessing step to do when
%   working with learning algorithms.

% You need to set these values correctly
X_norm = X;
mu = zeros(1, size(X, 5));
sigma = zeros(1, size(X, 5));
x1=X_norm(:,1);
x2=X_norm(:,2);
%x3=X_norm(:,3);
%x4=X_norm(:,4);



mu(1)=mean(x1);
mu(2)=mean(x2);
%mu(3)=mean(x3);
%mu(4)=mean(x4);




sigma(1)=std(x1);
sigma(2)=std(x2);
%sigma(3)=std(x3);
%sigma(4)=std(x4);



X_norm(:,1)=(x1-mu(1))/sigma(1);
X_norm(:,2)=(x2-mu(2))/sigma(2);
%X_norm(:,3)=(x3-mu(3))/sigma(3);
%X_norm(:,4)=(x4-mu(4))/sigma(4);


end
