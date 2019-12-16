
% a usual function, which we call using its handle ( ~ function pointer )
function r=MyFunctionB01(a)
    disp('here is MyFunctionB01()');
    disp(a);
    r=1+int32(a(1));
end