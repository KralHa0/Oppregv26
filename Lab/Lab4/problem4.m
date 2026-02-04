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
Q1 = zeros(mx,mx);
Q1(1,1) = 1;                            % Weight on state x1
Q1(2,2) = 1;                            % Weight on state x2
Q1(3,3) = 1;                            % Weight on state x3
Q1(4,4) = 1;                            % Weight on state x4
Q = gen_q(Q1, P1, N, M);                % Generate Q, hint: gen_q

% Generate c
%c2mult = alpha * exp(-beta*())
c2 = c2mult * ones(N*mx + M*mu,1);
%%for 


%% Generate system matrixes for linear model
Aeq2 = gen_aeq(A2, B2, N, mx, mu);     % Generate A, hint: gen_aeq
beq2 = zeros(N*mx, 1);                 % Generate b
beq2(1:mx) = A2*x0;

