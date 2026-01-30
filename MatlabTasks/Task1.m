%% Define the matrices needed for linprog
c = []
A = []
b = []
Aeq = []
beq = []
lb = ...
ub = [inf inf inf inf]'; % No upper limits on variables

% Solve the optimization problem
[x_opt, J_opt] = linprog(c, A, b, Aeq, beq, lb, ub);