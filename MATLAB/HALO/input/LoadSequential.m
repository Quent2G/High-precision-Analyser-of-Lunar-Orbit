function [orb] = LoadSequential(orb)
%LOADSEQUENTIAL The mission's design is expressed in this function
%   The initial state and time of propagation is chosen first with the help
%   of the LoadState function
%
%   Then each sequence of the mission is a letter (alphabetic order).
%   The sequence type can be among the five following:
%
%   "Propag":       Free propagation
%                   input: span = The time of propagation
%
%   "DVPropag":     Propagation after an initial impulsive boost. The boost 
%                   allows to reach the velocity of another orbit but crossing
%                   initial position. Useful for the final boost after Lambert.
%                   input: Orbi = The position from LoadState to match velocity with
%                          span = The time of propagation
% 
%   "TBPOptim":     For a close to 3-body problem orbit, optimize the initial
%                   state to reach a converged 3-body problem orbit. 
%                   The resulting orbit is closer to periodicity in the 
%                   Earth-Moon rotational frame.
%                   input: T = Period of the orbit
% 
%   "Lambert":      Solves the Lambert problem from current state to 
%                   another one and propagates to it.
%                   input: stop = Target state from LoadState
%                          span = Propagation time of the lambert
% 
%   "LambertOptim": Given two orbits, finds the best lambert between them.
%                   The mission will then be a free propagation on the first
%                   orbit until best start, then lambert and change of
%                   orbit, then free propagation of same length as the
%                   first one.
%                   input: target = Target state from LoadState
%                          t1     = Initial time of free propagation in first orbit (also 
%                                   describe the initiale position of the lambert)
%                          t2     = Initial time of free propagation in target orbit that
%                                   describe the final position of the lambert
%                          span   = Initial propagation time of the lambert

    orb = LoadState("NRHO",orb);
    orb.seq.Time = cspice_str2et(orb.sat.t0);

    orb.seq.a.type = "TBPOptim";
    orb.seq.a.T = 5.7444e+05;

    % orb.seq.b.type = "Lambert";
    % orb.seq.b.stop = "ELFO";
    % orb.seq.b.span = 2*3600;
    % 
    % orb.seq.c.type = "DVPropag";
    % orb.seq.c.Orbi = "ELFO";
    % orb.seq.c.span = 6*3600;
end

