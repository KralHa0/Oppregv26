%% RUN MDO
MBO

%% Find K
Q_lqr = diag([1 1 1 1]);
R_lqr = 1;

K = dlqr(A1, B1, Q_lqr, R_lqr);

%%