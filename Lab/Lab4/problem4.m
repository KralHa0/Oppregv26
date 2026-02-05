%% Run init
init07

%% Init new matrices
delta_t	= 0.25;

A1 = [1 delta_t 0 0; 0 1 -delta_t*K_2, 0; 0 0 1 delta_t; 0 0 -delta_t*K_1*K_pp 1-delta_t*K_1*K_pd];
B1 = [0 0 0 delta_t * K_1*K_pp]';

Ad2 = [1 delta_t; -K_3*K_ep*delta_t 1-K_3*K_ed*delta_t];
Bd2 = [0 delta_t*K_3*K_ep]';

A2 = blkdiag(A1, Ad2);
B2 = blkdiag(B1, Bd2);

alpha = 0.2;
beta = 20;
lambdat = 2*pi / 3;

%% SQP init

% weight on input
q1 = 1; 
q2 = 1;

P1 = diag([q1 q2]);

% Number of states and inputs
mx = size(A2,2); % Number of states (number of columns in A)
mu = size(B2,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0, x5_0, x6_0]';           % Initial values

% Time horizon and initialization
N  = 40;                                % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = -60*pi/360;                   % Lower bound on control
uu 	    = 60*pi/360;                    % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N, M, xl, xu, ul, uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q2 = zeros(mx,mx);
Q2(1,1) = 1;                            % Weight on state x1
Q2(2,2) = 0;                            % Weight on state x2
Q2(3,3) = 0;                            % Weight on state x3
Q2(4,4) = 0;                            % Weight on state x4
Q2(5,5) = 0;                            % Weight on state x5
Q2(6,6) = 0;                            % Weight on state x6
Q = gen_q(Q2, P1, N, M);                % Generate Q, hint: gen_q

% Generate c
c = zeros(N* mx + M*mu, 1);

%% Generate system matrixes for linear model
Aeq2 = gen_aeq(A2, B2, N, mx, mu);     % Generate A, hint: gen_aeq
beq2 = zeros(N*mx, 1);                 % Generate b
beq2(1:mx) = A2*x0;

%% fmincon setting
nonlcon = @(z) elevation_constraints(z, N, mx, alpha, beta, lambdat);
objective_func = @(z) z' * Q * z;
options = optimoptions('fmincon', 'Display', 'iter', 'Algorithm', 'sqp', 'MaxIterations', 1000);
tic
[z_opt, fval] = fmincon(objective_func, z0, [], [], Aeq2, beq2, vlb, vub, nonlcon, options);
t_opt = toc;


fprintf('Optimization completed in %.2f seconds\n', t_opt);
fprintf('Objective value: %.4f\n', fval);

%% Extract solution
u = [z_opt(N*mx+1:N*mx+M*mu); z_opt(N*mx+M*mu)];

x1 = [x0(1); z_opt(1:mx:N*mx)];    % Lambda
x2 = [x0(2); z_opt(2:mx:N*mx)];    % r
x3 = [x0(3); z_opt(3:mx:N*mx)];    % p
x4 = [x0(4); z_opt(4:mx:N*mx)];    % p_dot
x5 = [x0(5); z_opt(5:mx:N*mx)];    % e
x6 = [x0(6); z_opt(6:mx:N*mx)];    % e_dot

% Time vector
t = 0:delta_t:delta_t*(length(x1)-1);

%% Plot results
figure(1)
subplot(3,2,1)
plot(t, x1)
grid on
ylabel('Lambda [rad]')
title('Travel')

subplot(3,2,2)
plot(t, x2)
grid on
ylabel('r [rad/s]')
title('Travel rate')

subplot(3,2,3)
plot(t, x3)
grid on
ylabel('p [rad]')
title('Pitch')

subplot(3,2,4)
plot(t, x4)
grid on
ylabel('p dot [rad/s]')
title('Pitch rate')

subplot(3,2,5)
plot(t, x5)
hold on
% Plot the elevation constraint
lambda_plot = linspace(0, pi, 100);
e_constraint = alpha * exp(-beta * (lambda_plot - lambdat).^2);
plot(lambda_plot, e_constraint, 'r--', 'LineWidth', 2)
grid on
ylabel('e [rad]')
xlabel('Time [s]')
title('Elevation')
legend('Elevation', 'Constraint')

subplot(3,2,6)
plot(t, x6)
grid on
ylabel('e dot [rad/s]')
xlabel('Time [s]')
title('Elevation rate')