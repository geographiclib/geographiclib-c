function geodesicinverse(~, ~, ~)
%geodesicinverse  Solve inverse geodesic problem
%
%   [geodesic, aux] = geodesicinverse(latlong)
%   [geodesic, aux] = geodesicinverse(latlong, a, f)
%
%   latlong is an M x 4 matrix
%       latitude of point 1 = latlong(:,1) in degrees
%       longitude of point 1 = latlong(:,2) in degrees
%       latitude of point 2 = latlong(:,3) in degrees
%       longitude of point 2 = latlong(:,4) in degrees
%
%   geodesic is an M x 3 matrix
%       azimuth at point 1 = geodesic(:,1) in degrees
%       azimuth at point 2 = geodesic(:,2) in degrees
%       distance between points 1 and 2 = geodesic(:,3) in meters
%   aux is an M x 5 matrix
%       spherical arc length = aux(:,1) in degrees
%       reduced length = aux(:,2) in meters
%       geodesic scale 1 to 2 = aux(:,3)
%       geodesic scale 2 to 1 = aux(:,4)
%       area under geodesic = aux(:,5) in meters^2
%
%   a = major radius (meters)
%   f = flattening (0 means a sphere)
%   If a and f are omitted, the WGS84 values are used.
%
% The algorithm used in this function is given in
%
%     C. F. F. Karney, Algorithms for geodesics,
%     J. Geodesy 87, 43-55 (2013);
%     https://dx.doi.org/10.1007/s00190-012-0578-z
%     Addenda: http://geographiclib.sf.net/geod-addenda.html
%
% This is an interface to the GeographicLib C++ routine
%     Geodesic::Inverse
% See the documentation on this function for more information:
% http://geographiclib.sf.net/html/classGeographicLib_1_1Geodesic.html
%
% A native MATLAB implementation is available as GEODDISTANCE.
%
% See also GEODDISTANCE.

  error('Error: executing .m file instead of compiled routine');
end
% geodesicinverse.m
% Matlab .m file for solving inverse geodesic problem
%
% Copyright (c) Charles Karney (2010-2011) <charles@karney.com> and licensed
% under the MIT/X11 License.  For more information, see
% http://geographiclib.sourceforge.net/
