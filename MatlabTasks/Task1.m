%% Define the matrices needed for linprog
c = [2410 1630 2050 1700]';
A = [3 1 1 0];
b = 60;
Aeq = [1 1 1 1];
beq = 100;
lb = [0 0 0 0]';
ub = [inf inf inf inf]'; % No upper limits on variables

% Solve the optimization problem
[x_opt, J_opt] = linprog(c, A, b, Aeq, beq, lb, ub);

% Display the optimal solution and the optimal value of the objective function
disp('Optimal solution:');
disp(x_opt);
disp('Optimal objective function value:');
disp(J_opt);