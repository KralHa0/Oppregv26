function [c, ceq] = elevation_constraints(z, N, mx, alpha, beta, lambdat)
%ELEVATION_CONSTRAINTS
    %Init constraint vector
    c = zeros(N, 1);

    for k = 1:N
        idx = (k-1)*mx +1;
        lambda_k = z(idx);
        e_k = z(idx + 4);
    
        c(k) = alpha * exp(-beta * (lambda_k - lambdat)^2) - e_k;
    end
    
    % No equality constraints in this case
    ceq = [];

end